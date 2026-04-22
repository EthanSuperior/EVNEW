// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CPictResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>
#include <gdiplus.h>
#include <memory>
#include <vector>

#pragma comment(lib, "gdiplus.lib")

#include <libGraphite/data/data.hpp>
#include <libGraphite/quickdraw/pict.hpp>
#include <libGraphite/quickdraw/internal/surface.hpp>
#include <libGraphite/quickdraw/internal/color.hpp>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CPictResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CPictResource::CPictResource(void)
{
	m_iWidth  = 0;
	m_iHeight = 0;

	m_hPreviewBitmap = NULL;

	m_rectDest.left   = 0;
	m_rectDest.top    = 0;
	m_rectDest.right  = 0;
	m_rectDest.bottom = 0;

	m_iIsDirty = 0;
}

CPictResource::~CPictResource(void)
{
	if(m_hPreviewBitmap != NULL)
		DeleteObject(m_hPreviewBitmap);
}

int CPictResource::GetType(void)
{
	return CNR_TYPE_PICT;
}

int CPictResource::GetSize(void)
{
	return (int)m_vPicture.size();
}

int CPictResource::GetDialogID(void)
{
	return IDD_EDIT_PICT;
}

DLGPROCNOCALLBACK CPictResource::GetDialogProc(void)
{
	return PictDlgProc;
}

int CPictResource::GetNumFields(void)
{
	return NUM_PICT_FIELDS;
}

const std::string * CPictResource::GetFieldNames(void)
{
	return g_szPictFields;
}

int CPictResource::ShouldLoadDirect(void)
{
	return 1;
}

int CPictResource::SaveDirect(std::ostream & output)
{
	if(m_vPicture.size() > 0)
		output.write((char *)&m_vPicture[0], m_vPicture.size());

	return 1;
}

int CPictResource::LoadDirect(std::istream & input, int iSize)
{
	m_vPicture.resize(iSize);

	input.read((char *)&m_vPicture[0], iSize);

	Load((char *)&m_vPicture[0], iSize);

	return 1;
}

int CPictResource::Save(char *pOutput)
{
	if(m_vPicture.size() > 0)
		memcpy(pOutput, &m_vPicture[0], m_vPicture.size());

	return 1;
}

int CPictResource::Load(char *pInput, int iSize)
{
	if(m_vPicture.empty() || pInput != (char *)&m_vPicture[0] || m_vPicture.size() != (size_t)iSize)
	{
		m_vPicture.resize(iSize);

		if(pInput != (char *)&m_vPicture[0])
			memcpy(&m_vPicture[0], pInput, iSize);
	}

	if(m_vPicture.size() >= 10)
	{
		m_iWidth  = SwapEndianShort(*(short *)(&m_vPicture[0] + 8)) - SwapEndianShort(*(short *)(&m_vPicture[0] + 4));
		m_iHeight = SwapEndianShort(*(short *)(&m_vPicture[0] + 6)) - SwapEndianShort(*(short *)(&m_vPicture[0] + 2));
	}

	m_rectDest.left   = 48;
	m_rectDest.top    = 120;
	m_rectDest.right  = m_rectDest.left + m_iWidth;
	m_rectDest.bottom = m_rectDest.top  + m_iHeight;

	return 1;
}

int CPictResource::SaveToTextEx(std::ostream & output, std::string & szFilePath, std::string & szFilename1, std::string & szFilename2, int iParam)
{
	output << m_iWidth  << '\t'
		   << m_iHeight << '\t';

	PrintTextField(output, szFilename1.c_str(), '\t');

	std::string szFilename = szFilePath + szFilename1;

	FileExport(szFilename.c_str(), iParam, 0);

	return 1;
}

int CPictResource::LoadFromTextEx(std::istream & input, std::string & szFilePath)
{
	short iWidth, iHeight;

	char szFilename[MAX_PATH];

	input >> iWidth
		  >> iHeight;

	input.ignore(1);

	strcpy(szFilename, szFilePath.c_str());

	ReadTextField(input, szFilename + strlen(szFilename), MAX_PATH - strlen(szFilename));

	FileImport(szFilename, 0);

	return 1;
}

int CPictResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "pict ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_PICT_EDIT1, CCONTROL_TYPE_INT, IDS_STRING1008);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_PICT_EDIT2, CCONTROL_TYPE_STR256, IDS_STRING1009);
	m_controls[1].SetString(m_szName);

	m_iTempWidth  = 0;
	m_iTempHeight = 0;

	m_vTempPicture.clear();

	InitializePicture(hwnd);

	m_iIsDirty = 0;

	return 1;
}

int CPictResource::InitializePicture(HWND hwnd)
{
	std::string szText = "Width: ";

	if(m_iTempWidth == 0)
		szText += ToString(m_iWidth);
	else
		szText += ToString(m_iTempWidth);

	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_PICT_TEXT3), szText.c_str());

	szText = "Height: ";

	if(m_iTempHeight == 0)
		szText += ToString(m_iHeight);
	else
		szText += ToString(m_iTempHeight);

	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_PICT_TEXT4), szText.c_str());

	int iWidth = 264;
	int iHeight;

	if(m_iTempWidth == 0)
	{
		if(m_iWidth + 96 > iWidth)
			iWidth = m_iWidth + 96;
	}
	else
	{
		if(m_iTempWidth + 96 > iWidth)
			iWidth = m_iTempWidth + 96;
	}

	if(m_iTempHeight == 0)
		iHeight = m_iHeight;
	else
		iHeight = m_iTempHeight;

	HDC hdcDisplay;

	hdcDisplay = CreateDC("DISPLAY", NULL, NULL, NULL);

	int iScreenWidth  = GetDeviceCaps(hdcDisplay, HORZRES);
	int iScreenHeight = GetDeviceCaps(hdcDisplay, VERTRES);

	DeleteDC(hdcDisplay);

	if(m_iTempWidth == 0)
	{
		m_rectDest.left   = 48;
		m_rectDest.top    = 120;
		m_rectDest.right  = m_rectDest.left + m_iWidth;
		m_rectDest.bottom = m_rectDest.top  + m_iHeight;
	}
	else
	{
		m_tempRectDest.left   = 48;
		m_tempRectDest.top    = 120;
		m_tempRectDest.right  = m_tempRectDest.left + m_iTempWidth;
		m_tempRectDest.bottom = m_tempRectDest.top  + m_iTempHeight;
	}

	double fZoom = 100.0;

	if(iWidth > iScreenWidth)
	{
		fZoom *= (double)(iScreenWidth - 96) / (iWidth - 96);

		if(m_iTempWidth == 0)
		{
			m_rectDest.right  = ((m_rectDest.right  -  48) * (iScreenWidth - 96)) / (iWidth - 96) + 48;
			m_rectDest.bottom = ((m_rectDest.bottom - 120) * (iScreenWidth - 96)) / (iWidth - 96) + 120;
		}
		else
		{
			m_tempRectDest.right  = ((m_tempRectDest.right  -  48) * (iScreenWidth - 96)) / (iWidth - 96) + 48;
			m_tempRectDest.bottom = ((m_tempRectDest.bottom - 120) * (iScreenWidth - 96)) / (iWidth - 96) + 120;
		}

		iHeight = ((iHeight - 232) * (iScreenWidth - 96)) / (iWidth - 96) + 232;

		iWidth = iScreenWidth;
	}

	if(iHeight + 232 > iScreenHeight)
	{
		fZoom *= (double)(iScreenHeight - 232) / iHeight;

		if(m_iTempWidth == 0)
		{
			m_rectDest.right  = ((m_rectDest.right  -  48) * (iScreenHeight - 232)) / iHeight + 48;
			m_rectDest.bottom = ((m_rectDest.bottom - 120) * (iScreenHeight - 232)) / iHeight + 120;
		}
		else
		{
			m_tempRectDest.right  = ((m_tempRectDest.right  -  48) * (iScreenHeight - 232)) / iHeight + 48;
			m_tempRectDest.bottom = ((m_tempRectDest.bottom - 120) * (iScreenHeight - 232)) / iHeight + 120;
		}

		iWidth = ((iWidth - 96) * (iScreenHeight - 232)) / iHeight + 96;

		iHeight = iScreenHeight - 232;
	}

	fZoom = (double)(int)(fZoom * 10.0) / 10.0;

	std::string szZoom = "Zoom: ";
	szZoom += ToString(fZoom);
	szZoom += "%";

	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_PICT_TEXT5), szZoom.c_str());

	MoveWindow(hwnd,                                   m_pWindow->GetXPos(), m_pWindow->GetYPos(), iWidth, iHeight + 232, TRUE);
	MoveWindow(GetDlgItem(hwnd, IDC_EDIT_PICT_OK),     iWidth - 192,         iHeight + 144,        72,     26,            TRUE);
	MoveWindow(GetDlgItem(hwnd, IDC_EDIT_PICT_CANCEL), iWidth - 96,          iHeight + 144,        72,     26,            TRUE);

	return 1;
}

int CPictResource::CloseAndSave(void)
{
	CEditor *pEditor = CEditor::GetCurrentEditor();
	CErrorLog *pLog  = CErrorLog::GetCurrentErrorLog();

	std::string szError;

	if(pEditor->IsUniqueResourceID(this, m_controls[0].GetInt()) == 0)
	{
		szError = ToString(m_controls[0].GetInt());
		szError += " is not a unique ";
		szError += g_szResourceTypes[GetType()];
		szError += " ID.  Please enter a unique ID.";

		MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}
	else if((m_controls[0].GetInt() < 128) || (m_controls[0].GetInt() > 32767))
	{
		szError = ToString(m_controls[0].GetInt());
		szError += " is not a valid ID.  Please enter an ID between 128 and 32767 inclusive.";

		MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	int iIDOrNameChanged = 0;

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[1].GetString()) != 0))
		iIDOrNameChanged = 1;

	m_iID = m_controls[0].GetInt();

	strcpy(m_szName, m_controls[1].GetString());

	if(!m_vTempPicture.empty())
	{
		if(!m_iIsDirty)
			m_iIsDirty = 1;

		m_vPicture.swap(m_vTempPicture);
		m_vTempPicture.clear();

		m_iWidth  = m_iTempWidth;
		m_iHeight = m_iTempHeight;

		m_rectDest = m_tempRectDest;

		m_iTempWidth  = 0;
		m_iTempHeight = 0;
	}

	if(m_iIsDirty)
	{
		CEditor::GetCurrentEditor()->SetDirty();

		m_iIsDirty = 0;
	}

	int i;

	for(i = 0; i < NUM_PICT_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	InvalidatePictPreview();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	m_pWindow = NULL;

	return 1;
}

int CPictResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_PICT_CONTROLS; i++)
		m_controls[i].Destroy();

	InvalidatePictPreview();

	m_vTempPicture.clear();

	m_iTempWidth  = 0;
	m_iTempHeight = 0;

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	m_pWindow = NULL;

	return 1;
}

void CPictResource::InvalidatePictPreview(void)
{
	if(m_hPreviewBitmap != NULL)
	{
		DeleteObject(m_hPreviewBitmap);
		m_hPreviewBitmap = NULL;
	}
}

int CPictResource::EnsurePictPreview(void)
{
	if(m_hPreviewBitmap != NULL)
		return 1;

	const std::vector<UCHAR> *pPict = !m_vTempPicture.empty() ? &m_vTempPicture : (!m_vPicture.empty() ? &m_vPicture : NULL);

	if(pPict == NULL)
		return 0;

	CEditor *pEditor = CEditor::GetCurrentEditor();

	if(pEditor == NULL)
		return 0;

	CErrorLog *pLog  = CErrorLog::GetCurrentErrorLog();

	try
	{
		std::shared_ptr<std::vector<char> > bytes(new std::vector<char>(pPict->size()));
		for(size_t i = 0; i < pPict->size(); i++)
			(*bytes)[i] = (char)(*pPict)[i];

		std::shared_ptr<graphite::data::data> data(new graphite::data::data(bytes, pPict->size(), 0));
		std::shared_ptr<graphite::qd::pict> pict(new graphite::qd::pict(data));
		std::shared_ptr<graphite::qd::surface> surface = pict->image_surface().lock();

		if(surface == NULL)
			return 0;

		graphite::qd::size sz = surface->size();
		std::vector<uint32_t> raw = surface->raw();

		BITMAPINFO bmi;
		ZeroMemory(&bmi, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = sz.width();
		bmi.bmiHeader.biHeight = -sz.height();
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;

		HDC hdc = GetDC(m_pWindow->GetHWND());
		void *pBits = NULL;
		m_hPreviewBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pBits, NULL, 0);
		ReleaseDC(m_pWindow->GetHWND(), hdc);

		if(m_hPreviewBitmap == NULL || pBits == NULL)
			return 0;

		memcpy(pBits, &raw[0], raw.size() * sizeof(uint32_t));
	}
	catch(...)
	{
		if(pEditor->PrefGenerateLogFile())
			*pLog << "Error: Unable to rasterize PICT with Graphite for preview." << CErrorLog::endl;

		return 0;
	}

	return m_hPreviewBitmap != NULL;
}

int CPictResource::OnPaint(void)
{
	PAINTSTRUCT ps;

	BeginPaint(m_pWindow->GetHWND(), &ps);

	if(m_vTempPicture.empty() && m_vPicture.empty())
	{
		EndPaint(m_pWindow->GetHWND(), &ps);
		return 1;
	}

	MacPictRect const *pR = !m_vTempPicture.empty() ? &m_tempRectDest : &m_rectDest;

	RECT rcDest;
	rcDest.left   = (LONG)pR->left;
	rcDest.top    = (LONG)pR->top;
	rcDest.right  = (LONG)pR->right;
	rcDest.bottom = (LONG)pR->bottom;

	if(EnsurePictPreview() == 0 || m_hPreviewBitmap == NULL)
	{
		EndPaint(m_pWindow->GetHWND(), &ps);
		return 1;
	}

	BITMAP bm;

	ZeroMemory(&bm, sizeof(bm));

	GetObject(m_hPreviewBitmap, sizeof(bm), &bm);

	int destW = (int)rcDest.right  - (int)rcDest.left;
	int destH = (int)rcDest.bottom - (int)rcDest.top;

	if(destW > 0 && destH > 0)
	{
		HDC hdc   = ps.hdc;
		HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP hOld = (HBITMAP)SelectObject(hdcMem, m_hPreviewBitmap);
		int oldMode = SetStretchBltMode(hdc, HALFTONE);
		SetBrushOrgEx(hdc, 0, 0, NULL);
		StretchBlt(hdc, rcDest.left, rcDest.top, destW, destH, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
		SetStretchBltMode(hdc, oldMode);
		SelectObject(hdcMem, hOld);
		DeleteDC(hdcMem);
	}

	EndPaint(m_pWindow->GetHWND(), &ps);

	return 1;
}

int CPictResource::FileImport(char *szFilename, int iShowErrorMessages)
{
	CEditor *pEditor = CEditor::GetCurrentEditor();
	CErrorLog *pLog  = CErrorLog::GetCurrentErrorLog();

	OPENFILENAME ofn;

	char szFilename2[MAX_PATH];

	if(szFilename == NULL)
	{
		strcpy(szFilename2, "");

		memset(&ofn, 0, sizeof(OPENFILENAME));

		ofn.lStructSize   = sizeof(OPENFILENAME);
		ofn.nMaxFile      = MAX_PATH;
		ofn.nMaxFileTitle = MAX_PATH;
		ofn.lpstrTitle    = "Import Picture";
		ofn.lpstrFilter   = "Image Files\0*.bmp;*.png;*.jpg;*.jpeg;*.gif;*.pic;*.tiff\0All Files (*.*)\0*.*\0";
		ofn.nFilterIndex  = 1;
		ofn.lpstrDefExt   = "bmp";
		ofn.Flags         = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
		ofn.hwndOwner     = m_pWindow->GetHWND();
		ofn.lpstrFile     = szFilename2;

		if(GetOpenFileName(&ofn) == 0)
			return 0;
	}
	else
	{
		strcpy(szFilename2, szFilename);
	}

	char *pExtension = strrchr(szFilename2, '.');

	if(pExtension == NULL)
		pExtension = szFilename2;
	else
		pExtension++;

//	*pLog << "Importing PICT\nFilename: " << szFilename2 << "\nExtension: " << pExtension << '\n';

	if(strcmp(pExtension, "pic") == 0)
	{
		int iSize;

		std::ifstream filein;

		filein.open(szFilename2, std::ios::in | std::ios::binary);

		if(filein.is_open() == 0)
		{
			if(pEditor->PrefGenerateLogFile())
				*pLog << "Error: Unable to load file \"" << szFilename2 << "\"!" << CErrorLog::endl;

			std::string szError = "Unable to open \"";

			szError += szFilename2;
			szError += "\"!";

			if(iShowErrorMessages)
				MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

			return 0;
		}

		filein.seekg(0, std::ios::end);

		iSize = filein.tellg();
		iSize -= 512;

		filein.seekg(512, std::ios::beg);

		m_vTempPicture.resize(iSize);

		filein.read((char *)&m_vTempPicture[0], iSize);

		filein.close();

		m_iTempWidth  = SwapEndianShort(*(short *)(&m_vTempPicture[0] + 8));
		m_iTempHeight = SwapEndianShort(*(short *)(&m_vTempPicture[0] + 6));

		m_tempRectDest.left   = 48;
		m_tempRectDest.top    = 120;
		m_tempRectDest.right  = m_tempRectDest.left + m_iTempWidth;
		m_tempRectDest.bottom = m_tempRectDest.top  + m_iTempHeight;

		InvalidatePictPreview();

		if(m_pWindow != NULL)
			InitializePicture(m_pWindow->GetHWND());

		return 1;
	}

	WCHAR szFilenameW[MAX_PATH];

	if(MultiByteToWideChar(CP_ACP, 0, szFilename2, -1, szFilenameW, MAX_PATH) == 0)
		return 0;

	try
	{
		Gdiplus::GdiplusStartupInput startupInput;
		ULONG_PTR iToken = 0;

		if(Gdiplus::GdiplusStartup(&iToken, &startupInput, NULL) != Gdiplus::Ok)
			return 0;

		Gdiplus::Bitmap sourceImage(szFilenameW);
		if(sourceImage.GetLastStatus() != Gdiplus::Ok)
		{
			Gdiplus::GdiplusShutdown(iToken);
			return 0;
		}

		UINT iWidth = sourceImage.GetWidth();
		UINT iHeight = sourceImage.GetHeight();

		std::shared_ptr<graphite::qd::surface> surface(new graphite::qd::surface((int)iWidth, (int)iHeight));

		for(UINT y = 0; y < iHeight; y++)
		{
			for(UINT x = 0; x < iWidth; x++)
			{
				Gdiplus::Color c;
				sourceImage.GetPixel(x, y, &c);
				surface->set((int)x, (int)y, graphite::qd::color(c.GetR(), c.GetG(), c.GetB(), c.GetA()));
			}
		}

		std::shared_ptr<graphite::qd::pict> pict = graphite::qd::pict::from_surface(surface);
		std::shared_ptr<graphite::data::data> pictData = pict->data(false);
		std::shared_ptr<std::vector<char> > bytes = pictData->get();

		m_vTempPicture.resize(pictData->size());
		for(size_t i = 0; i < pictData->size(); i++)
			m_vTempPicture[i] = (UCHAR)(*bytes)[i];

		Gdiplus::GdiplusShutdown(iToken);

		m_iTempWidth = (short)iWidth;
		m_iTempHeight = (short)iHeight;
		m_tempRectDest.left   = 48;
		m_tempRectDest.top    = 120;
		m_tempRectDest.right  = m_tempRectDest.left + m_iTempWidth;
		m_tempRectDest.bottom = m_tempRectDest.top  + m_iTempHeight;
	}
	catch(...)
	{
		if(pEditor->PrefGenerateLogFile())
			*pLog << "Error: Unable to load image \"" << szFilename2 << "\" for PICT resource using Graphite!" << CErrorLog::endl;

		if(iShowErrorMessages)
		{
			std::string szError = "\"";
			szError += szFilename2;
			szError += "\" is not a supported image file!";
			MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);
		}
		return 0;
	}

	InvalidatePictPreview();

	if(m_pWindow != NULL)
		InitializePicture(m_pWindow->GetHWND());
	else
	{
		m_vPicture.swap(m_vTempPicture);
		m_vTempPicture.clear();
		m_iWidth  = m_iTempWidth;
		m_iHeight = m_iTempHeight;
		m_rectDest = m_tempRectDest;
		m_iTempWidth  = 0;
		m_iTempHeight = 0;
	}

	m_iIsDirty = 1;
	return 1;
}

int CPictResource::FileExport(const char *szFilename, int iImageType, int iShowErrorMessages)
{
	if(m_vTempPicture.empty() && m_vPicture.empty())
	{
		if(iShowErrorMessages)
			MessageBox(m_pWindow->GetHWND(), "No picture to export.", "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	CEditor *pEditor = CEditor::GetCurrentEditor();
	CErrorLog *pLog  = CErrorLog::GetCurrentErrorLog();

	OPENFILENAME ofn;

	char szFilename2[MAX_PATH];

	if(szFilename == NULL)
	{
		strcpy(szFilename2, "");

		memset(&ofn, 0, sizeof(OPENFILENAME));

		ofn.lStructSize   = sizeof(OPENFILENAME);
		ofn.nMaxFile      = MAX_PATH;
		ofn.nMaxFileTitle = MAX_PATH;
		ofn.lpstrTitle    = "Export Picture";
		ofn.lpstrFilter   = "Bitmap (*.bmp)\0*.bmp\0Portable Network Graphics (*.png)\0*.png\0JPEG (*.jpg)\0*.jpg;*.jpeg\0TIFF (*.tiff)\0*.tiff\0";
		ofn.nFilterIndex  = 1;
		ofn.lpstrDefExt   = "bmp";
		ofn.Flags         = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
		ofn.hwndOwner     = m_pWindow->GetHWND();
		ofn.lpstrFile     = szFilename2;

		if(GetSaveFileName(&ofn) == 0)
			return 0;

		iImageType = ofn.nFilterIndex - 1;
	}
	else
	{
		strcpy(szFilename2, szFilename);
	}

	const std::vector<UCHAR> &pictRef = !m_vTempPicture.empty() ? m_vTempPicture : m_vPicture;

	try
	{
		std::shared_ptr<std::vector<char> > bytes(new std::vector<char>(pictRef.size()));
		for(size_t i = 0; i < pictRef.size(); i++)
			(*bytes)[i] = (char)pictRef[i];

		std::shared_ptr<graphite::data::data> data(new graphite::data::data(bytes, pictRef.size(), 0));
		std::shared_ptr<graphite::qd::pict> pict(new graphite::qd::pict(data));
		std::shared_ptr<graphite::qd::surface> surface = pict->image_surface().lock();

		if(surface == NULL)
			return 0;

		graphite::qd::size sz = surface->size();
		std::vector<uint32_t> raw = surface->raw();

		WCHAR szFilenameW[MAX_PATH];
		if(MultiByteToWideChar(CP_ACP, 0, szFilename2, -1, szFilenameW, MAX_PATH) == 0)
			return 0;

		Gdiplus::GdiplusStartupInput startupInput;
		ULONG_PTR iToken = 0;
		if(Gdiplus::GdiplusStartup(&iToken, &startupInput, NULL) != Gdiplus::Ok)
			return 0;

		Gdiplus::Bitmap image((INT)sz.width(), (INT)sz.height(), (INT)(sz.width() * sizeof(uint32_t)), PixelFormat32bppARGB, (BYTE *)&raw[0]);

		CLSID encoderClsid;
		UINT iNumEncoders = 0;
		UINT iEncoderInfoSize = 0;
		if(Gdiplus::GetImageEncodersSize(&iNumEncoders, &iEncoderInfoSize) != Gdiplus::Ok || iEncoderInfoSize == 0)
		{
			Gdiplus::GdiplusShutdown(iToken);
			return 0;
		}

		std::vector<UCHAR> vEncoderInfo(iEncoderInfoSize);
		Gdiplus::ImageCodecInfo *pEncoderInfo = (Gdiplus::ImageCodecInfo *)&vEncoderInfo[0];
		if(Gdiplus::GetImageEncoders(iNumEncoders, iEncoderInfoSize, pEncoderInfo) != Gdiplus::Ok)
		{
			Gdiplus::GdiplusShutdown(iToken);
			return 0;
		}

		const WCHAR *pMimeType = L"image/bmp";
		if(iImageType == 1)
			pMimeType = L"image/png";
		else if(iImageType == 2)
			pMimeType = L"image/jpeg";
		else if(iImageType == 3)
			pMimeType = L"image/tiff";

		bool bFound = false;
		for(UINT i = 0; i < iNumEncoders; i++)
		{
			if(wcscmp(pEncoderInfo[i].MimeType, pMimeType) == 0)
			{
				encoderClsid = pEncoderInfo[i].Clsid;
				bFound = true;
				break;
			}
		}

		if(!bFound || image.Save(szFilenameW, &encoderClsid, NULL) != Gdiplus::Ok)
		{
			Gdiplus::GdiplusShutdown(iToken);
			return 0;
		}

		Gdiplus::GdiplusShutdown(iToken);
		return 1;
	}
	catch(...)
	{
		if(pEditor->PrefGenerateLogFile())
			*pLog << "Error: Unable to export PICT using Graphite!" << CErrorLog::endl;

		if(iShowErrorMessages)
			MessageBox(m_pWindow->GetHWND(), "Export failed!", "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}
}

BOOL CPictResource::PictDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CPictResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CPictResource *)pWindow->GetExtraData(2);

	int i;

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			if(pResource->Initialize(hwnd) == 0)
			{
				std::string szBuffer = "PICT initialization failed.";

				if(((CEditor *)pWindow->GetExtraData(0))->PrefGenerateLogFile())
					szBuffer += "  See log.txt for more information.";

				MessageBox(pWindow->GetHWND(), szBuffer.c_str(), "Error", MB_OK);
			}

			return TRUE;

			break;
		}

		case WM_PAINT:
		{
			pResource->OnPaint();

			return TRUE;

			break;
		}

		case WM_SYSCOMMAND:
		{
			if(wparam == SC_CLOSE)
			{
				pResource->CloseAndDontSave();

				return TRUE;
			}

			break;
		}

		case WM_COMMAND:
		{
			int iNotifyCode = HIWORD(wparam);
			int iControlID  = LOWORD(wparam);

			if(iControlID == IDC_EDIT_PICT_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_PICT_OK)
			{
				pResource->CloseAndSave();
			}
			else if(iControlID == IDM_PICT_FILE_IMPORT)
			{
				pResource->FileImport(NULL, 1);
			}
			else if(iControlID == IDM_PICT_FILE_EXPORT)
			{
				pResource->FileExport(NULL, -1, 1);
			}
			else if(iControlID == IDM_PICT_FILE_CLOSEANDSAVE)
			{
				pResource->CloseAndSave();
			}
			else if(iControlID == IDM_PICT_FILE_CLOSEANDDONTSAVE)
			{
				pResource->CloseAndDontSave();
			}
			else
			{
				for(i = 0; i < NUM_PICT_CONTROLS; i++)
				{
					if(iControlID == pResource->m_controls[i].GetControlID())
					{
						pResource->m_controls[i].ProcessMessage(iNotifyCode);

						break;
					}
				}
			}

			return TRUE;

			break;
		}

		default:
		{
			break;
		}
	}

	return FALSE;
}
