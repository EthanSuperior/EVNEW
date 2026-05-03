#include "CImageFormatHelper.h"

#ifndef EVNEW_PICT_TRACE
#define EVNEW_PICT_TRACE 1
#endif

#include <cstdio>
#include <cstdint>
#include <exception>
#include <gdiplus.h>
#include <memory>
#include <string>
#include <vector>

#include <libGraphite/data/data.hpp>
#include <libGraphite/quickdraw/pict.hpp>
#include <libGraphite/quickdraw/internal/surface.hpp>
#include <libGraphite/quickdraw/internal/color.hpp>

#include "CErrorLog.h"

#pragma comment(lib, "gdiplus.lib")

/// libGraphite `reader::read_bytes` forms the end pointer as `&backing[phys_end]`. If the data
/// slice ends flush with `backing.size()`, `phys_end` can equal `backing.size()` and `[]` is UB.
/// Keep logical slice sizing in `graphite::data::data`; allocate extra backing bytes beyond the slice.
static constexpr size_t kGraphiteDataSliceTrailingPad = 1u;

/// Apple QD Picture: first UInt16 (`picSize`) is the declared picture length **including** the size
/// word. Resource payloads are sometimes truncated vs that field; zeros after the payload fix reads.
///
/// Slack bytes **inside** the reader-visible slice soften `eof`/partial-read edge failures.
/// Nova PI CTs often match `picSize` == byte count yet still overrun (packed rows, regions).
static constexpr size_t kPictReadSlackMinInsideBytes =
	size_t{256} * size_t{1024};
/// Cap fits Win32 `size_t`; far more than needed for EV PI CT preview over-reads.
static constexpr size_t kPictReadSlackMaxInsideBytes =
	size_t{64} * size_t{1024} * size_t{1024};
static constexpr unsigned kPictReadSlackMultiplier = 64u;

static constexpr size_t kPictDeclaredSizeGrowCapExtraBytes = size_t{64} * size_t{1024} * size_t{1024};

static size_t PictReadSlackInsideSliceBytes(size_t contentLogicalBytes)
{
	if(contentLogicalBytes >= kPictReadSlackMaxInsideBytes)
		return kPictReadSlackMaxInsideBytes;
	size_t prop = contentLogicalBytes;
	if(prop > kPictReadSlackMaxInsideBytes / kPictReadSlackMultiplier)
		return kPictReadSlackMaxInsideBytes;
	prop *= kPictReadSlackMultiplier;
	if(prop < kPictReadSlackMinInsideBytes)
		return kPictReadSlackMinInsideBytes;
	if(prop > kPictReadSlackMaxInsideBytes)
		return kPictReadSlackMaxInsideBytes;
	return prop;
}

static int GetEncoderClsid(const WCHAR *pMimeType, CLSID *pClsid)
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

static const WCHAR *GetMimeType(CImageFormatHelper::EImageFormat iFormat)
{
	switch(iFormat)
	{
		case CImageFormatHelper::IMAGE_FORMAT_BMP:  return L"image/bmp";
		case CImageFormatHelper::IMAGE_FORMAT_PNG:  return L"image/png";
		case CImageFormatHelper::IMAGE_FORMAT_JPEG: return L"image/jpeg";
		default:                                    return L"image/tiff";
	}
}

static int LoadImageFileToSurface(
	const WCHAR *szPathW,
	CImageFormatHelper::surface &outSurface,
	int *pWidth,
	int *pHeight,
	const char *szContext);

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

static uint16_t PictReadBeU16(const UCHAR *p)
{
	return (uint16_t)(((uint16_t)p[0] << 8) | (uint16_t)p[1]);
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

/// Raw PI CT bytes -> `graphite::data::data` + `qd::pict` (same pattern as `rsrc::resource::data()` + `load_resource`).
static bool TryDecodePictResourceBytesIntoPict(
	const std::vector<UCHAR> &pictBytes,
	std::int64_t pictResourceId,
	const char *pictResourceName,
	const char *szContext,
	std::shared_ptr<graphite::qd::pict> &outPict)
{
	outPict.reset();
	if(pictBytes.empty())
	{
		LogImageError(szContext, "DecodePict(empty)", -1);
		return false;
	}
	if(PictFrameHeaderSafeForGraphite(pictBytes, szContext) == 0)
		return false;

	{
		char t[80];
		_snprintf_s(t, sizeof(t), _TRUNCATE, "Pict decode: input %zu bytes", (size_t)pictBytes.size());
		LogImageTrace(szContext, t);
	}
	const size_t nPict = pictBytes.size();

	size_t sliceContent = nPict;
	if(nPict >= 2)
	{
		const uint16_t declaredPicTotal = PictReadBeU16(&pictBytes[0]);
		if(declaredPicTotal >= 10u && declaredPicTotal > 0
		   && static_cast<size_t>(declaredPicTotal) > sliceContent
		   && static_cast<size_t>(declaredPicTotal) <= sliceContent + kPictDeclaredSizeGrowCapExtraBytes)
		{
			{
				char t[144];
				_snprintf_s(t, sizeof(t), _TRUNCATE,
					"Pict decode: picSize=%u (grow buffer %zu -> %u padded bytes)",
					(unsigned int)declaredPicTotal,
					sliceContent, (unsigned int)declaredPicTotal);
				LogImageTrace(szContext, t);
			}
			sliceContent = static_cast<size_t>(declaredPicTotal);
		}
	}

	const size_t readSlackInside = PictReadSlackInsideSliceBytes(sliceContent);
	{
		char t[128];
		_snprintf_s(t, sizeof(t), _TRUNCATE, "Pict decode: reader slack inside slice %zu bytes (logical content %zu)",
			readSlackInside, sliceContent);
		LogImageTrace(szContext, t);
	}
	if(sliceContent > (size_t)-1 - readSlackInside - kGraphiteDataSliceTrailingPad)
	{
		LogImageError(szContext, "DecodePict(oversized)", -1);
		return false;
	}
	const size_t sliceLen     = sliceContent + readSlackInside;
	const size_t backingLen = sliceLen + kGraphiteDataSliceTrailingPad;
	if(sliceLen < sliceContent || backingLen < sliceLen)
	{
		LogImageError(szContext, "DecodePict(oversized)", -1);
		return false;
	}

	std::shared_ptr<std::vector<char> > bytes(new std::vector<char>(backingLen, 0));
	for(size_t i = 0; i < nPict; i++)
		(*bytes)[i] = (char)pictBytes[i];
	LogImageTrace(szContext, "Pict decode: copied to backing buffer");

	std::shared_ptr<graphite::data::data> data(new graphite::data::data(bytes, sliceLen, 0));
	const std::string graphiteName((pictResourceName != NULL) ? pictResourceName : "");
	{
		char t[192];
		_snprintf_s(t, sizeof(t), _TRUNCATE, "Pict decode: constructing qd::pict id=%lld name=\"%s\"",
			static_cast<long long>(pictResourceId), graphiteName.c_str());
		LogImageTrace(szContext, t);
	}

	try
	{
		outPict = std::shared_ptr<graphite::qd::pict>(
			new graphite::qd::pict(data, pictResourceId, graphiteName));
		return true;
	}
	catch(const std::exception &ex)
	{
		LogImageException(szContext, ex.what());
		outPict.reset();
		return false;
	}
	catch(...)
	{
		LogImageError(szContext, "DecodePict(unknown exception)", -1);
		outPict.reset();
		return false;
	}
}

/// Decoded raster (whatever depth Graphite used) → packed 24 bpp BGR rows for BMP/DIB pipelines.
/// `surface->at(x,y)` returns normalized RGBA; preview/BMP writes BGR triples only.
static int RasterizeGraphiteSurfaceTo24bppBgr(
	const CImageFormatHelper::surface &surface,
	int &outW,
	int &outH,
	int &outStride,
	std::vector<BYTE> &outRows,
	const char *szContext)
{
	outW       = 0;
	outH       = 0;
	outStride = 0;
	outRows.clear();
	if(!surface)
	{
		LogImageError(szContext, "RasterizeSurface(surface null)", -1);
		return 0;
	}

	const graphite::qd::size sz = surface->size();
	const int w                 = (int)sz.width();
	const int h                 = (int)sz.height();
	{
		char t[96];
		_snprintf_s(t, sizeof(t), _TRUNCATE, "RasterizeSurface: %dx%d -> 24bpp BGR (via surface->at)", w, h);
		LogImageTrace(szContext, t);
	}
	if(w <= 0 || h <= 0)
	{
		LogImageError(szContext, "RasterizeSurface(size)", -1);
		return 0;
	}

	const int rowBytes = w * 3;
	outStride           = (rowBytes + 3) & ~3;
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

	outW = w;
	outH = h;
	return 1;
}

static int LoadImageFileToSurface(
	const WCHAR *szPathW,
	CImageFormatHelper::surface &outSurface,
	int *pWidth,
	int *pHeight,
	const char *szContext)
{
	outSurface.reset();

	Gdiplus::GdiplusStartupInput startupInput;
	ULONG_PTR iToken = 0;
	if(Gdiplus::GdiplusStartup(&iToken, &startupInput, NULL) != Gdiplus::Ok)
	{
		LogImageError(szContext, "LoadImageFileToSurface GdiplusStartup", -1);
		return 0;
	}

	int      ok     = 0;
	UINT     iWidth = 0;
	UINT     iHeight = 0;
	{
		Gdiplus::Bitmap sourceImage(szPathW);
		if(sourceImage.GetLastStatus() != Gdiplus::Ok)
			LogImageError(szContext, "LoadImageFileToSurface Bitmap(load)", sourceImage.GetLastStatus());
		else
		{
			iWidth  = sourceImage.GetWidth();
			iHeight = sourceImage.GetHeight();
			if(iWidth == 0 || iHeight == 0)
				LogImageError(szContext, "LoadImageFileToSurface Bitmap(size)", -1);
			else
			{
				Gdiplus::Bitmap bmp24(iWidth, iHeight, PixelFormat24bppRGB);
				Gdiplus::Graphics graphics(&bmp24);
				Gdiplus::Status dstatus = graphics.DrawImage(&sourceImage, 0, 0, iWidth, iHeight);
				if(dstatus != Gdiplus::Ok)
					LogImageError(szContext, "LoadImageFileToSurface DrawImage", dstatus);
				else
				{
					Gdiplus::Rect lockRect(0, 0, (INT)iWidth, (INT)iHeight);
					Gdiplus::BitmapData bd;
					if(bmp24.LockBits(&lockRect, Gdiplus::ImageLockModeRead, PixelFormat24bppRGB, &bd) != Gdiplus::Ok)
						LogImageError(szContext, "LoadImageFileToSurface LockBits", -1);
					else
					{
						try
						{
							CImageFormatHelper::surface s = std::make_shared<graphite::qd::surface>((int)iWidth, (int)iHeight);
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
							outSurface = std::move(s);
							ok = 1;
						}
						catch(...)
						{
							LogImageError(szContext, "LoadImageFileToSurface(surface)", -1);
						}
						bmp24.UnlockBits(&bd);
					}
				}
			}
		}
	}

	Gdiplus::GdiplusShutdown(iToken);

	if(ok == 0)
		return 0;
	if(pWidth != NULL)
		*pWidth = (int)iWidth;
	if(pHeight != NULL)
		*pHeight = (int)iHeight;
	return 1;
}

int CImageFormatHelper::PictToSurface(
	const std::vector<UCHAR> &pictBytes,
	std::int64_t pictResourceId,
	const char *pictResourceName,
	CImageFormatHelper::surface &outSurface,
	const char *szContext)
{
	outSurface.reset();
	std::shared_ptr<graphite::qd::pict> pict;
	if(!TryDecodePictResourceBytesIntoPict(pictBytes, pictResourceId, pictResourceName, szContext, pict))
		return 0;
	outSurface = pict->image_surface().lock();
	if(!outSurface)
	{
		LogImageError(szContext, "PictToSurface(image_surface)", -1);
		return 0;
	}
	return 1;
}

int CImageFormatHelper::SurfaceToPict(
	const CImageFormatHelper::surface &surf,
	std::vector<UCHAR> &outPictBytes,
	const char *szContext,
	bool rgb555)
{
	outPictBytes.clear();
	if(!surf)
	{
		LogImageError(szContext, "SurfaceToPict(null surface)", -1);
		return 0;
	}
	try
	{
		std::shared_ptr<graphite::qd::pict>              pict     = graphite::qd::pict::from_surface(surf);
		std::shared_ptr<graphite::data::data>            pictData = pict->data(rgb555);
		std::shared_ptr<std::vector<char> >             bytes    = pictData->get();
		outPictBytes.resize(pictData->size());
		for(size_t i = 0; i < pictData->size(); i++)
			outPictBytes[i] = (UCHAR)(*bytes)[i];
		return 1;
	}
	catch(const std::exception &ex)
	{
		LogImageException(szContext, ex.what());
		return 0;
	}
	catch(...)
	{
		LogImageError(szContext, "SurfaceToPict(unknown exception)", -1);
		return 0;
	}
}

int CImageFormatHelper::PreviewSurface(
	const CImageFormatHelper::surface &surf,
	HBITMAP *pOutBitmap,
	int *pWidth,
	int *pHeight,
	const char *szContext)
{
	if(pOutBitmap == NULL)
	{
		LogImageError(szContext, "PreviewSurface(null out)", -1);
		return 0;
	}

	if(*pOutBitmap != NULL)
	{
		DeleteObject(*pOutBitmap);
		*pOutBitmap = NULL;
	}

	if(!surf)
	{
		LogImageError(szContext, "PreviewSurface(null surface)", -1);
		return 0;
	}

	int               w      = 0;
	int               h      = 0;
	int               stride = 0;
	std::vector<BYTE> bgr;
	if(RasterizeGraphiteSurfaceTo24bppBgr(surf, w, h, stride, bgr, szContext) == 0)
		return 0;
	if(bgr.empty())
	{
		LogImageError(szContext, "PreviewSurface(empty bgr)", -1);
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

	HDC hdc     = GetDC(NULL);
	void *pBits = NULL;
	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pBits, NULL, 0);
	ReleaseDC(NULL, hdc);
	if(hBitmap == NULL || pBits == NULL)
	{
		LogImageError(szContext, "PreviewSurface CreateDIBSection(24)", GetLastError());
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

int CImageFormatHelper::ImportSurface(
	const char *szInputFilename,
	CImageFormatHelper::surface &outSurface,
	short *pWidth,
	short *pHeight,
	const char *szContext)
{
	outSurface.reset();
	WCHAR szPathW[MAX_PATH];
	if(MultiByteToWideChar(CP_ACP, 0, szInputFilename, -1, szPathW, MAX_PATH) == 0)
	{
		LogImageError(szContext, "ImportSurface MultiByteToWideChar", GetLastError());
		return 0;
	}

	int iw = 0;
	int ih = 0;
	if(LoadImageFileToSurface(szPathW, outSurface, &iw, &ih, szContext) == 0)
		return 0;
	if(pWidth != NULL)
		*pWidth = (short)iw;
	if(pHeight != NULL)
		*pHeight = (short)ih;
	return 1;
}

int CImageFormatHelper::ExportSurface(
	const CImageFormatHelper::surface &surf,
	const char *szOutputFilename,
	EImageFormat iFormat,
	const char *szContext)
{
	if(!surf)
	{
		LogImageError(szContext, "ExportSurface(null surface)", -1);
		return 0;
	}

	int w, h, stride;
	std::vector<BYTE> bgr;
	if(RasterizeGraphiteSurfaceTo24bppBgr(surf, w, h, stride, bgr, szContext) == 0)
		return 0;
	if(bgr.empty())
		return 0;

	WCHAR szOutW[MAX_PATH];
	if(MultiByteToWideChar(CP_ACP, 0, szOutputFilename, -1, szOutW, MAX_PATH) == 0)
	{
		LogImageError(szContext, "ExportSurface MultiByteToWideChar", GetLastError());
		return 0;
	}

	Gdiplus::GdiplusStartupInput startupInput;
	ULONG_PTR iToken = 0;
	if(Gdiplus::GdiplusStartup(&iToken, &startupInput, NULL) != Gdiplus::Ok)
	{
		LogImageError(szContext, "ExportSurface GdiplusStartup", -1);
		return 0;
	}

	int outOk = 0;
	{
		Gdiplus::Bitmap outBmp((INT)w, (INT)h, stride, PixelFormat24bppRGB, bgr.data());
		if(outBmp.GetLastStatus() != Gdiplus::Ok)
			LogImageError(szContext, "ExportSurface Bitmap(24 wrap)", outBmp.GetLastStatus());
		else
		{
			CLSID encoderClsid;
			if(GetEncoderClsid(GetMimeType(iFormat), &encoderClsid) == 0)
				LogImageError(szContext, "ExportSurface GetEncoderClsid", -1);
			else
			{
				Gdiplus::Status st = outBmp.Save(szOutW, &encoderClsid, NULL);
				if(st == Gdiplus::Ok)
					outOk = 1;
				else
					LogImageError(szContext, "ExportSurface Bitmap.Save", st);
			}
		}
	}
	Gdiplus::GdiplusShutdown(iToken);
	return outOk;
}

int CImageFormatHelper::RLEToSurface(
	const std::vector<UCHAR> & /* rleBytes */,
	std::int64_t /* rleResourceId */,
	const char * /* rleResourceName */,
	CImageFormatHelper::surface &outSurface,
	const char *szContext)
{
	outSurface.reset();
	LogImageError(szContext, "RLEToSurface(not implemented)", -1);
	return 0;
}

int CImageFormatHelper::SurfaceToRLE(
	const CImageFormatHelper::surface & /* surf */,
	std::vector<UCHAR> &outRleBytes,
	const char *szContext)
{
	outRleBytes.clear();
	LogImageError(szContext, "SurfaceToRLE(not implemented)", -1);
	return 0;
}

int CImageFormatHelper::PpatToSurface(
	const std::vector<UCHAR> & /* ppatBytes */,
	std::int64_t /* ppatResourceId */,
	const char * /* ppatResourceName */,
	CImageFormatHelper::surface &outSurface,
	const char *szContext)
{
	outSurface.reset();
	LogImageError(szContext, "PpatToSurface(not implemented)", -1);
	return 0;
}

int CImageFormatHelper::SurfaceToPpat(
	const CImageFormatHelper::surface & /* surf */,
	std::vector<UCHAR> &outPpatBytes,
	const char *szContext)
{
	outPpatBytes.clear();
	LogImageError(szContext, "SurfaceToPpat(not implemented)", -1);
	return 0;
}
