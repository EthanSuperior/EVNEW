#include "CImageFormatHelper.h"

#ifndef EVNEW_PICT_TRACE
#define EVNEW_PICT_TRACE 1
#endif

#include <cstdio>
#include <cstdint>
#include <exception>
#include <gdiplus.h>
#include <memory>
#include <vector>

#include <libGraphite/data/data.hpp>
#include <libGraphite/quickdraw/pict.hpp>
#include <libGraphite/quickdraw/internal/surface.hpp>
#include <libGraphite/quickdraw/internal/color.hpp>

#include "CErrorLog.h"

#pragma comment(lib, "gdiplus.lib")

namespace
{
int GetEncoderClsid(const WCHAR *pMimeType, CLSID *pClsid)
{
	UINT iNumEncoders = 0;
	UINT iEncoderInfoSize = 0;

	if(Gdiplus::GetImageEncodersSize(&iNumEncoders, &iEncoderInfoSize) != Gdiplus::Ok || iEncoderInfoSize == 0)
		return 0;

	std::vector<UCHAR> vEncoderInfo(iEncoderInfoSize);
	Gdiplus::ImageCodecInfo *pEncoderInfo = (Gdiplus::ImageCodecInfo *)&vEncoderInfo[0];

	if(Gdiplus::GetImageEncoders(iNumEncoders, iEncoderInfoSize, pEncoderInfo) != Gdiplus::Ok)
		return 0;

	for(UINT i = 0; i < iNumEncoders; i++)
	{
		if(wcscmp(pEncoderInfo[i].MimeType, pMimeType) == 0)
		{
			*pClsid = pEncoderInfo[i].Clsid;
			return 1;
		}
	}

	return 0;
}

const WCHAR *GetMimeType(CImageFormatHelper::EImageFormat iFormat)
{
	switch(iFormat)
	{
		case CImageFormatHelper::IMAGE_FORMAT_BMP:  return L"image/bmp";
		case CImageFormatHelper::IMAGE_FORMAT_PNG:  return L"image/png";
		case CImageFormatHelper::IMAGE_FORMAT_JPEG: return L"image/jpeg";
		default:                                    return L"image/tiff";
	}
}

void LogImageError(const char *szContext, const char *szStep, int iCode)
{
	char buf[1024];
	if(szContext != NULL && szContext[0] != '\0')
		_snprintf_s(buf, sizeof(buf), _TRUNCATE, "EVNEW: Image helper failure (%s) at %s [status=%d]\r\n", szContext, szStep, iCode);
	else
		_snprintf_s(buf, sizeof(buf), _TRUNCATE, "EVNEW: Image helper failure at %s [status=%d]\r\n", szStep, iCode);
	OutputDebugStringA(buf);

	CErrorLog *pLog = CErrorLog::GetCurrentErrorLog();
	if(pLog != NULL && pLog->IsLogFileOpen())
	{
		*pLog << "Image helper failure";
		if(szContext != NULL)
			*pLog << " (" << szContext << ")";
		*pLog << " at " << szStep << " [status=" << iCode << "]" << CErrorLog::endl;
		pLog->FlushLogFile();
	}
}

#if EVNEW_PICT_TRACE
/// Verbose PICT path: same destinations as other image logs when enabled.
void LogImageTrace(const char *szContext, const char *szLine)
{
	char buf[1536];
	_snprintf_s(buf, sizeof(buf), _TRUNCATE, "EVNEW: PICT trace [%s] %s\r\n",
		(szContext != NULL && szContext[0] != '\0') ? szContext : "-", szLine != NULL ? szLine : "");
	OutputDebugStringA(buf);
	CErrorLog *pLog = CErrorLog::GetCurrentErrorLog();
	if(pLog != NULL && pLog->IsLogFileOpen())
	{
		*pLog << "PICT trace";
		if(szContext != NULL)
			*pLog << " (" << szContext << ")";
		*pLog << ": " << (szLine != NULL ? szLine : "") << CErrorLog::endl;
		pLog->FlushLogFile();
	}
}
#else
static void LogImageTrace(const char * /* szContext */, const char * /* szLine */) {}
#endif

void LogImageException(const char *szContext, const char *szWhat)
{
	char buf[2048];
	_snprintf_s(buf, sizeof(buf), _TRUNCATE, "EVNEW: Image std::exception [%s] %s\r\n",
		(szContext != NULL && szContext[0] != '\0') ? szContext : "-", szWhat != NULL ? szWhat : "");
	OutputDebugStringA(buf);
	CErrorLog *pLog = CErrorLog::GetCurrentErrorLog();
	if(pLog != NULL && pLog->IsLogFileOpen())
	{
		*pLog << "Image std::exception";
		if(szContext != NULL)
			*pLog << " (" << szContext << ")";
		*pLog << ": " << (szWhat != NULL ? szWhat : "") << CErrorLog::endl;
		pLog->FlushLogFile();
	}
}

/// 16-bit big-endian (PICT on-disk layout); matches [CPictResource::Load] frame math, not a fork of libGraphite.
static int16_t PictReadBeI16(const UCHAR *p)
{
	return (int16_t)(((uint16_t)p[0] << 8) | (uint16_t)p[1]);
}

/// If the 10-byte PICT header’s QD `Rect` reports a **positive** width/height, ensure it is within editor limits
/// before `graphite::qd::pict` allocates. v2 PICTs often have 0x0 here; we do not block that.
static int PictFrameHeaderSafeForGraphite(const std::vector<UCHAR> &pictBytes, const char *szContext)
{
	if(pictBytes.size() < 10)
		return 1;
	int32_t w = (int32_t)PictReadBeI16(&pictBytes[8]) - (int32_t)PictReadBeI16(&pictBytes[4]);
	int32_t h = (int32_t)PictReadBeI16(&pictBytes[6]) - (int32_t)PictReadBeI16(&pictBytes[2]);
	if(w <= 0 || h <= 0)
		return 1;
	const int32_t kMax = 8192;
	if(w > kMax || h > kMax)
	{
		LogImageError(szContext, "PictFrameHeaderSafe(max-dim)", -1);
		return 0;
	}
	if((int64_t)w * (int64_t)h > (int64_t)kMax * kMax)
	{
		LogImageError(szContext, "PictFrameHeaderSafe(max-pixels)", -1);
		return 0;
	}
	return 1;
}

/// PICT (Graphite) -> 24bpp BGR rows. One shared representation for 24bpp BMP on disk and 24bpp DIB for GDI.
static int PictBytesTo24bppBgrImpl(
	const std::vector<UCHAR> &pictBytes, int &outW, int &outH, int &outStride, std::vector<BYTE> &outRows, const char *szContext)
{
	outW  = 0;
	outH  = 0;
	outStride = 0;
	outRows.clear();
	if(pictBytes.empty())
	{
		LogImageError(szContext, "PictBytesTo24bppBgr(empty)", -1);
		return 0;
	}
	if(PictFrameHeaderSafeForGraphite(pictBytes, szContext) == 0)
		return 0;

	{
		char t[80];
		_snprintf_s(t, sizeof(t), _TRUNCATE, "PictTo24: input %zu bytes", (size_t)pictBytes.size());
		LogImageTrace(szContext, t);
	}
	std::shared_ptr<std::vector<char> > bytes(new std::vector<char>(pictBytes.size()));
	for(size_t i = 0; i < pictBytes.size(); i++)
		(*bytes)[i] = (char)pictBytes[i];
	LogImageTrace(szContext, "PictTo24: copied to byte buffer");

	LogImageTrace(szContext, "PictTo24: constructing data slice");
	std::shared_ptr<graphite::data::data> data(new graphite::data::data(bytes, pictBytes.size(), 0));
	LogImageTrace(szContext, "PictTo24: constructing qd::pict (may throw on bad PICT)");
	std::shared_ptr<graphite::qd::pict> pict(new graphite::qd::pict(data));
	LogImageTrace(szContext, "PictTo24: locking image_surface");
	std::shared_ptr<graphite::qd::surface> surface = pict->image_surface().lock();
	if(surface == NULL)
	{
		LogImageError(szContext, "PictBytesTo24bppBgr(surface)", -1);
		return 0;
	}

	graphite::qd::size sz = surface->size();
	int w = (int)sz.width();
	int h = (int)sz.height();
	{
		char t[80];
		_snprintf_s(t, sizeof(t), _TRUNCATE, "PictTo24: surface %dx%d", w, h);
		LogImageTrace(szContext, t);
	}
	if(w <= 0 || h <= 0)
	{
		LogImageError(szContext, "PictBytesTo24bppBgr(size)", -1);
		return 0;
	}

	// `surface->raw()` is fragile on some PICTs; use `at(x,y)` (Graphite) for stable reads.
	LogImageTrace(szContext, "PictTo24: 24bpp BGR via surface->at (no raw(), no GDI+ in this path)");
	const int rowBytes = w * 3;
	outStride = (rowBytes + 3) & ~3;
	outRows.assign((size_t)outStride * (size_t)h, 0);
	for(int y = 0; y < h; y++)
	{
		BYTE *pRow = &outRows[(size_t)y * (size_t)outStride];
		for(int x = 0; x < w; x++)
		{
			const graphite::qd::color col = surface->at(x, y);
			pRow[3 * x + 0] = col.blue_component();
			pRow[3 * x + 1] = col.green_component();
			pRow[3 * x + 2] = col.red_component();
		}
	}
	LogImageTrace(szContext, "PictTo24: at() pack done");

	outW  = w;
	outH  = h;
	return 1;
}

static int PictBytesTo24bppBgr(
	const std::vector<UCHAR> &pictBytes, int &outW, int &outH, int &outStride, std::vector<BYTE> &outRows, const char *szContext)
{
	try
	{
		return PictBytesTo24bppBgrImpl(pictBytes, outW, outH, outStride, outRows, szContext);
	}
	catch(const std::exception &ex)
	{
		outW  = 0;
		outH  = 0;
		outStride = 0;
		outRows.clear();
		LogImageException(szContext, ex.what());
		return 0;
	}
	catch(...)
	{
		outW  = 0;
		outH  = 0;
		outStride = 0;
		outRows.clear();
		LogImageError(szContext, "PictBytesTo24bppBgr(unknown exception)", -1);
		return 0;
	}
}

static int ConvertBmpToPict_Inner(const char *szInputBmpFilename, std::vector<UCHAR> &outPictBytes, short *pWidth, short *pHeight, const char *szContext)
{
	outPictBytes.clear();

	WCHAR szPathW[MAX_PATH];
	if(MultiByteToWideChar(CP_ACP, 0, szInputBmpFilename, -1, szPathW, MAX_PATH) == 0)
	{
		LogImageError(szContext, "MultiByteToWideChar(bmp)", GetLastError());
		return 0;
	}

	Gdiplus::GdiplusStartupInput startupInput;
	ULONG_PTR iToken = 0;
	if(Gdiplus::GdiplusStartup(&iToken, &startupInput, NULL) != Gdiplus::Ok)
	{
		LogImageError(szContext, "GdiplusStartup", -1);
		return 0;
	}

	// GDI+ must be shut down only after all Gdiplus::Bitmap/Graphics are destroyed.
	int ok = 0;
	{
		Gdiplus::Bitmap sourceImage(szPathW);
		if(sourceImage.GetLastStatus() != Gdiplus::Ok)
		{
			LogImageError(szContext, "Bitmap(load bmp)", sourceImage.GetLastStatus());
		}
		else
		{
			UINT iWidth  = sourceImage.GetWidth();
			UINT iHeight = sourceImage.GetHeight();
			if(iWidth == 0 || iHeight == 0)
				LogImageError(szContext, "Bitmap(size)", -1);
			else
			{
				Gdiplus::Bitmap bmp24(iWidth, iHeight, PixelFormat24bppRGB);
				Gdiplus::Graphics graphics(&bmp24);
				Gdiplus::Status dstatus = graphics.DrawImage(&sourceImage, 0, 0, iWidth, iHeight);
				if(dstatus != Gdiplus::Ok)
					LogImageError(szContext, "Graphics.DrawImage(24bpp)", dstatus);
				else
				{
					Gdiplus::Rect lockRect(0, 0, (INT)iWidth, (INT)iHeight);
					Gdiplus::BitmapData bd;
					if(bmp24.LockBits(&lockRect, Gdiplus::ImageLockModeRead, PixelFormat24bppRGB, &bd) != Gdiplus::Ok)
						LogImageError(szContext, "LockBits(24bpp)", -1);
					else
					{
						try
						{
							std::shared_ptr<graphite::qd::surface> s(new graphite::qd::surface((int)iWidth, (int)iHeight));
							const BYTE *pBase = (const BYTE *)bd.Scan0;
							for(UINT y = 0; y < iHeight; y++)
							{
								const BYTE *pRow = pBase + y * (UINT)bd.Stride;
								for(UINT x = 0; x < iWidth; x++)
								{
									BYTE b = pRow[x * 3 + 0];
									BYTE g = pRow[x * 3 + 1];
									BYTE r = pRow[x * 3 + 2];
									s->set((int)x, (int)y, graphite::qd::color(r, g, b, 255));
								}
							}
							std::shared_ptr<graphite::qd::pict> pict     = graphite::qd::pict::from_surface(s);
							std::shared_ptr<graphite::data::data> pictData = pict->data(false);
							std::shared_ptr<std::vector<char> >   bytes  = pictData->get();

							outPictBytes.resize(pictData->size());
							for(size_t i = 0; i < pictData->size(); i++)
								outPictBytes[i] = (UCHAR)(*bytes)[i];

							if(pWidth != NULL)
								*pWidth = (short)iWidth;
							if(pHeight != NULL)
								*pHeight = (short)iHeight;
							ok = 1;
						}
						catch(...)
						{
							bmp24.UnlockBits(&bd);
							LogImageError(szContext, "ConvertBmpToPict(Graphite)", -1);
							// `ok` stays 0; do not return — leave block so GDI+ objects are destroyed, then shutdown.
						}
						if(ok)
							bmp24.UnlockBits(&bd);
					}
				}
			}
		}
	}

	Gdiplus::GdiplusShutdown(iToken);
	return ok;
}

}

int CImageFormatHelper::ImportToPict(const char *szInputFilename, std::vector<UCHAR> &outPictBytes, short *pWidth, short *pHeight, const char *szContext)
{
	LogImageTrace(szContext, "ImportToPict: file to PICT via temp BMP");
	char szTempDir[MAX_PATH];
	char szTempBmp[MAX_PATH];
	if(GetTempPathA(MAX_PATH, szTempDir) == 0 || GetTempFileNameA(szTempDir, "PIM", 0, szTempBmp) == 0)
	{
		LogImageError(szContext, "ImportToPict GenerateTempFilename", -1);
		return 0;
	}

	if(CImageFormatHelper::ImportToBmp(szInputFilename, szTempBmp, NULL, NULL, szContext) == 0)
	{
		DeleteFile(szTempBmp);
		return 0;
	}

	int iResult = CImageFormatHelper::ConvertBmpToPict(szTempBmp, outPictBytes, pWidth, pHeight, szContext);
	DeleteFile(szTempBmp);
	return iResult;
}

int CImageFormatHelper::ExportFromPict(const std::vector<UCHAR> &pictBytes, const char *szOutputFilename, EImageFormat iFormat, const char *szContext)
{
	{
		char t[512];
		_snprintf_s(t, sizeof(t), _TRUNCATE, "ExportFromPict: %zu bytes -> temp BMP then format %d",
			(size_t)pictBytes.size(), (int)iFormat);
		LogImageTrace(szContext, t);
	}
	char szTempDir[MAX_PATH];
	char szTempBmp[MAX_PATH];
	if(GetTempPathA(MAX_PATH, szTempDir) == 0 || GetTempFileNameA(szTempDir, "PEX", 0, szTempBmp) == 0)
	{
		LogImageError(szContext, "ExportFromPict GenerateTempFilename", -1);
		return 0;
	}

	if(CImageFormatHelper::ConvertPictToBmp(pictBytes, szTempBmp, szContext) == 0)
	{
		DeleteFile(szTempBmp);
		return 0;
	}

	int iResult = CImageFormatHelper::ExportFromBmp(szTempBmp, szOutputFilename, iFormat, szContext);
	DeleteFile(szTempBmp);
	return iResult;
}

int CImageFormatHelper::ConvertBmpToPict(const char *szInputBmpFilename, std::vector<UCHAR> &outPictBytes, short *pWidth, short *pHeight, const char *szContext)
{
	try
	{
		return ConvertBmpToPict_Inner(szInputBmpFilename, outPictBytes, pWidth, pHeight, szContext);
	}
	catch(const std::exception &ex)
	{
		outPictBytes.clear();
		LogImageException(szContext, ex.what());
		return 0;
	}
	catch(...)
	{
		outPictBytes.clear();
		LogImageError(szContext, "ConvertBmpToPict(unknown exception)", -1);
		return 0;
	}
}

int CImageFormatHelper::ConvertPictToDib(
	const std::vector<UCHAR> &pictBytes, HBITMAP *pOutBitmap, int *pWidth, int *pHeight, const char *szContext)
{
	{
		char t[128];
		_snprintf_s(t, sizeof(t), _TRUNCATE, "ConvertPictToDib: %zu bytes to 24bpp DIB", (size_t)pictBytes.size());
		LogImageTrace(szContext, t);
	}
	if(pOutBitmap == NULL)
	{
		LogImageError(szContext, "ConvertPictToDib(null out)", -1);
		return 0;
	}

	if(*pOutBitmap != NULL)
	{
		DeleteObject(*pOutBitmap);
		*pOutBitmap = NULL;
	}

	int w, h, stride;
	std::vector<BYTE> bgr;
	if(PictBytesTo24bppBgr(pictBytes, w, h, stride, bgr, szContext) == 0)
		return 0;

	if(bgr.empty())
	{
		LogImageError(szContext, "ConvertPictToDib(empty bgr)", -1);
		return 0;
	}

	BITMAPINFO bmi;
	ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth       = w;
	bmi.bmiHeader.biHeight      = -h;
	bmi.bmiHeader.biPlanes      = 1;
	bmi.bmiHeader.biBitCount    = 24;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage   = (DWORD)((DWORD)stride * (DWORD)h);

	HDC hdc   = GetDC(NULL);
	void *pBits = NULL;
	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pBits, NULL, 0);
	ReleaseDC(NULL, hdc);
	if(hBitmap == NULL || pBits == NULL)
	{
		LogImageError(szContext, "ConvertPictToDib CreateDIBSection(24)", GetLastError());
		if(hBitmap != NULL)
			DeleteObject(hBitmap);
		return 0;
	}

	memcpy(pBits, bgr.data(), bgr.size());
	*pOutBitmap = hBitmap;

	if(pWidth != NULL)
		*pWidth = w;
	if(pHeight != NULL)
		*pHeight = h;

	return 1;
}

int CImageFormatHelper::ConvertPictToBmp(
	const std::vector<UCHAR> &pictBytes, const char *szOutputBmpFilename, const char *szContext)
{
	int w, h, stride;
	std::vector<BYTE> bgr;
	if(PictBytesTo24bppBgr(pictBytes, w, h, stride, bgr, szContext) == 0)
		return 0;

	WCHAR szOutW[MAX_PATH];
	if(MultiByteToWideChar(CP_ACP, 0, szOutputBmpFilename, -1, szOutW, MAX_PATH) == 0)
	{
		LogImageError(szContext, "MultiByteToWideChar(out bmp)", GetLastError());
		return 0;
	}

	Gdiplus::GdiplusStartupInput startupInput;
	ULONG_PTR iToken  = 0;
	if(Gdiplus::GdiplusStartup(&iToken, &startupInput, NULL) != Gdiplus::Ok)
	{
		LogImageError(szContext, "GdiplusStartup", -1);
		return 0;
	}

	int outOk = 0;
	{
		Gdiplus::Bitmap outBmp((INT)w, (INT)h, stride, PixelFormat24bppRGB, bgr.data());
		if(outBmp.GetLastStatus() != Gdiplus::Ok)
			LogImageError(szContext, "ConvertPictToBmp Bitmap(24 wrap)", outBmp.GetLastStatus());
		else
		{
			CLSID bmpClsid;
			if(GetEncoderClsid(L"image/bmp", &bmpClsid) == 0)
				LogImageError(szContext, "GetEncoderClsid(image/bmp)", -1);
			else
			{
				Gdiplus::Status st = outBmp.Save(szOutW, &bmpClsid, NULL);
				if(st == Gdiplus::Ok)
					outOk = 1;
				else
					LogImageError(szContext, "Bitmap.Save(24bpp pict)", st);
			}
		}
	}
	Gdiplus::GdiplusShutdown(iToken);
	return outOk;
}

int CImageFormatHelper::ImportToBmp(const char *szInputFilename, const char *szOutputBmpFilename, int *pWidth, int *pHeight, const char *szContext)
{
	WCHAR szInputFilenameW[MAX_PATH];
	WCHAR szOutputFilenameW[MAX_PATH];

	if(MultiByteToWideChar(CP_ACP, 0, szInputFilename, -1, szInputFilenameW, MAX_PATH) == 0)
	{
		LogImageError(szContext, "MultiByteToWideChar(input)", GetLastError());
		return 0;
	}

	if(MultiByteToWideChar(CP_ACP, 0, szOutputBmpFilename, -1, szOutputFilenameW, MAX_PATH) == 0)
	{
		LogImageError(szContext, "MultiByteToWideChar(output)", GetLastError());
		return 0;
	}

	Gdiplus::GdiplusStartupInput startupInput;
	ULONG_PTR iToken = 0;
	if(Gdiplus::GdiplusStartup(&iToken, &startupInput, NULL) != Gdiplus::Ok)
	{
		LogImageError(szContext, "GdiplusStartup", -1);
		return 0;
	}

	int      outOk   = 0;
	UINT     iWidth  = 0;
	UINT     iHeight = 0;
	{
		Gdiplus::Bitmap sourceImage(szInputFilenameW);
		if(sourceImage.GetLastStatus() != Gdiplus::Ok)
			LogImageError(szContext, "Bitmap(load input)", sourceImage.GetLastStatus());
		else
		{
			iWidth  = sourceImage.GetWidth();
			iHeight = sourceImage.GetHeight();
			if((iWidth == 0) || (iHeight == 0))
				LogImageError(szContext, "Bitmap(size)", -1);
			else
			{
				Gdiplus::Bitmap bmp24(iWidth, iHeight, PixelFormat24bppRGB);
				Gdiplus::Graphics graphics(&bmp24);
				Gdiplus::Status dstatus = graphics.DrawImage(&sourceImage, 0, 0, iWidth, iHeight);
				if(dstatus != Gdiplus::Ok)
					LogImageError(szContext, "Graphics.DrawImage", dstatus);
				else
				{
					CLSID bmpClsid;
					if(GetEncoderClsid(L"image/bmp", &bmpClsid) == 0)
						LogImageError(szContext, "GetEncoderClsid(image/bmp)", -1);
					else
					{
						Gdiplus::Status st = bmp24.Save(szOutputFilenameW, &bmpClsid, NULL);
						if(st == Gdiplus::Ok)
							outOk = 1;
						else
							LogImageError(szContext, "Bitmap.Save(bmp)", st);
					}
				}
			}
		}
	}
	Gdiplus::GdiplusShutdown(iToken);
	if(outOk == 0)
		return 0;
	if(pWidth != NULL)
		*pWidth = (int)iWidth;
	if(pHeight != NULL)
		*pHeight = (int)iHeight;
	return 1;
}

int CImageFormatHelper::ExportFromBmp(const char *szInputBmpFilename, const char *szOutputFilename, EImageFormat iFormat, const char *szContext)
{
	WCHAR szInputFilenameW[MAX_PATH];
	WCHAR szOutputFilenameW[MAX_PATH];

	if(MultiByteToWideChar(CP_ACP, 0, szInputBmpFilename, -1, szInputFilenameW, MAX_PATH) == 0)
	{
		LogImageError(szContext, "MultiByteToWideChar(input bmp)", GetLastError());
		return 0;
	}

	if(MultiByteToWideChar(CP_ACP, 0, szOutputFilename, -1, szOutputFilenameW, MAX_PATH) == 0)
	{
		LogImageError(szContext, "MultiByteToWideChar(output)", GetLastError());
		return 0;
	}

	Gdiplus::GdiplusStartupInput startupInput;
	ULONG_PTR iToken = 0;
	if(Gdiplus::GdiplusStartup(&iToken, &startupInput, NULL) != Gdiplus::Ok)
	{
		LogImageError(szContext, "GdiplusStartup", -1);
		return 0;
	}

	int outOk = 0;
	{
		Gdiplus::Bitmap image(szInputFilenameW);
		if(image.GetLastStatus() != Gdiplus::Ok)
			LogImageError(szContext, "Bitmap(load bmp)", image.GetLastStatus());
		else
		{
			CLSID encoderClsid;
			if(GetEncoderClsid(GetMimeType(iFormat), &encoderClsid) == 0)
				LogImageError(szContext, "GetEncoderClsid(output)", -1);
			else
			{
				Gdiplus::Status st = image.Save(szOutputFilenameW, &encoderClsid, NULL);
				if(st == Gdiplus::Ok)
					outOk = 1;
				else
					LogImageError(szContext, "Bitmap.Save(output)", st);
			}
		}
	}
	Gdiplus::GdiplusShutdown(iToken);
	return outOk;
}
