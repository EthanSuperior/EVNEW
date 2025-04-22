// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CPictResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

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

	m_iPortExists = 0;

	m_hPicture = NULL;

	m_hTempPicture = NULL;

	m_rectDest.left   = 0;
	m_rectDest.top    = 0;
	m_rectDest.right  = 0;
	m_rectDest.bottom = 0;

	m_iIsDirty = 0;
}

CPictResource::~CPictResource(void)
{
	if(m_hPicture != NULL)
		qt::DisposeHandle(m_hPicture);

	if(m_hTempPicture != NULL)
		qt::DisposeHandle(m_hTempPicture);
}

int CPictResource::GetType(void)
{
	return CNR_TYPE_PICT;
}

int CPictResource::GetSize(void)
{
	if(m_hPicture == NULL)
		return 0;
	else
		return (qt::GetHandleSize(m_hPicture));
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
	if((m_hPicture != NULL) && (qt::GetHandleSize(m_hPicture) > 0))
		output.write(*m_hPicture, qt::GetHandleSize(m_hPicture));

	return 1;
}

int CPictResource::LoadDirect(std::istream & input, int iSize)
{
	if(m_hPicture == NULL)
		m_hPicture = qt::NewHandle(iSize);
	else
		qt::SetHandleSize(m_hPicture, iSize);

	input.read(*m_hPicture, iSize);

	Load(*m_hPicture, iSize);

	return 1;
}

int CPictResource::Save(char *pOutput)
{
	if((m_hPicture != NULL) && (qt::GetHandleSize(m_hPicture) > 0))
		memcpy(pOutput, *m_hPicture, qt::GetHandleSize(m_hPicture));;

	return 1;
}

int CPictResource::Load(char *pInput, int iSize)
{
	if((m_hPicture != NULL) && (pInput != *m_hPicture))
	{
		qt::SetHandleSize(m_hPicture, iSize);

		memcpy(*m_hPicture, pInput, iSize);
	}
	else
	{
		if(m_hPicture == NULL)
		{
			m_hPicture = qt::NewHandle(iSize);

			memcpy(*m_hPicture, pInput, iSize);
		}
	}

	m_iWidth  = SwapEndianShort(*(short *)(*m_hPicture + 8)) - SwapEndianShort(*(short *)(*m_hPicture + 4));
	m_iHeight = SwapEndianShort(*(short *)(*m_hPicture + 6)) - SwapEndianShort(*(short *)(*m_hPicture + 2));

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

	strcpy_s(szFilename, szFilePath.c_str());

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

	if(m_hTempPicture != NULL)
	{
		qt::DisposeHandle(m_hTempPicture);

		m_hTempPicture = NULL;
	}

	InitializePicture(hwnd);

	m_iIsDirty = 0;

	return 1;
}

int CPictResource::InitializePicture(HWND hwnd)
{
	if(!m_iPortExists)
	{
		qt::MacSetPort(qt::CreatePortAssociation(hwnd, NULL, qt::kQTMLNoIdleEvents));

		m_iPortExists = 1;
	}
	else
		qt::MacSetPort(qt::GetHWNDPort(hwnd));

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
		fZoom *= static_cast<double>(iScreenWidth - 96) / (iWidth - 96);

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
		fZoom *= static_cast<double>(iScreenHeight - 232) / iHeight;

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

	fZoom = static_cast<double>((int)(fZoom * 10.0)) / 10.0;

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

	strcpy_s(m_szName, m_controls[1].GetString());

	if(m_hTempPicture != NULL)
	{
		if(!m_iIsDirty)
			m_iIsDirty = 1;

		if(m_hPicture != NULL)
			qt::DisposeHandle(m_hPicture);

		m_hPicture = m_hTempPicture;

		m_hTempPicture = NULL;

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

	if(m_iPortExists)
	{
		qt::DestroyPortAssociation((qt::CGrafPort *)qt::GetHWNDPort(m_pWindow->GetHWND()));

		m_iPortExists = 0;
	}

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	m_pWindow = NULL;

	return 1;
}

int CPictResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_PICT_CONTROLS; i++)
		m_controls[i].Destroy();

	if(m_iPortExists)
	{
		qt::DestroyPortAssociation((qt::CGrafPort *)qt::GetHWNDPort(m_pWindow->GetHWND()));

		m_iPortExists = 0;
	}

	if(m_hTempPicture != NULL)
	{
		qt::DisposeHandle(m_hTempPicture);

		m_hTempPicture = NULL;

		m_iTempWidth  = 0;
		m_iTempHeight = 0;
	}

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	m_pWindow = NULL;

	return 1;
}

int CPictResource::OnPaint(void)
{
	PAINTSTRUCT paintStruct;

	BeginPaint(m_pWindow->GetHWND(), &paintStruct);

	if(m_hTempPicture != NULL)
		qt::DrawPicture((qt::PicHandle)m_hTempPicture, &m_tempRectDest);
	else if(m_hPicture != NULL)
		qt::DrawPicture((qt::PicHandle)m_hPicture, &m_rectDest);

	EndPaint(m_pWindow->GetHWND(), &paintStruct);

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
		strcpy_s(szFilename2, "");

		memset(&ofn, 0, sizeof(OPENFILENAME));

		ofn.lStructSize   = sizeof(OPENFILENAME);
		ofn.nMaxFile      = MAX_PATH;
		ofn.nMaxFileTitle = MAX_PATH;
		ofn.lpstrTitle    = "Import Picture";
		ofn.lpstrFilter   = "Image Files\0*.bmp;*.png;*.jpg;*.jpeg;*.gif;*.pic;*.tiff;*.tga\0All Files (*.*)\0*.*\0";
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
		strcpy_s(szFilename2, szFilename);
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

		if(m_hTempPicture != NULL)
			qt::DisposeHandle(m_hTempPicture);

		m_hTempPicture = qt::NewHandle(iSize);

		filein.read(*m_hTempPicture, iSize);

		filein.close();

		m_iTempWidth  = SwapEndianShort(*(short *)(*m_hTempPicture + 8));
		m_iTempHeight = SwapEndianShort(*(short *)(*m_hTempPicture + 6));

		m_tempRectDest.left   = 48;
		m_tempRectDest.top    = 120;
		m_tempRectDest.right  = m_tempRectDest.left + m_iTempWidth;
		m_tempRectDest.bottom = m_tempRectDest.top  + m_iTempHeight;

		if(m_pWindow != NULL)
			InitializePicture(m_pWindow->GetHWND());

		return 1;
	}

	qt::FSSpec fileSpec1, fileSpec2;

	qt::CopyCStringToPascal(szFilename2, fileSpec1.name);

	fileSpec1.vRefNum = 0;
	fileSpec1.parID   = 0;

	qt::GraphicsImportComponent giComponent;
	qt::GraphicsExportComponent geComponent;

	qt::OSErr qtErr;

	qtErr = qt::GetGraphicsImporterForFile(&fileSpec1, &giComponent);

	if(qtErr != qt::noErr)
	{
		if(pEditor->PrefGenerateLogFile())
			*pLog << "Error: Unable to get a graphics importer for PICT resource!" << CErrorLog::endl;

		std::string szError = "\"";

		szError += szFilename2;
		szError += "\" is not a supported image file!";

		if(iShowErrorMessages)
			MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	char szTempFilename[MAX_PATH];

	strcpy_s(szTempFilename, "PICT");

//	szTempFilename = _tempnam(pEditor->GetTempFileDirectory(), "PICT");

//	if(szTempFilename == NULL)
	if(pEditor->GenerateTempFilename(szTempFilename) == 0)
	{
		if(pEditor->PrefGenerateLogFile())
			*pLog << "Error: Unable to make temporary file for importing PICT resource!" << CErrorLog::endl;

		qt::CloseComponent(giComponent);

		if(iShowErrorMessages)
			MessageBox(m_pWindow->GetHWND(), "Import failed!", "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

//	*pLog << "Temporary filename: " << szTempFilename << "\nBeginning QuickTime stuff...\n";

	qt::CopyCStringToPascal(szTempFilename, fileSpec2.name);

	fileSpec2.vRefNum = 0;
	fileSpec2.parID   = 0;

	qtErr = qt::OpenADefaultComponent(qt::GraphicsExporterComponentType, qt::kQTFileTypeBMP, &geComponent);

	if(qtErr != qt::noErr)
	{
		if(pEditor->PrefGenerateLogFile())
			*pLog << "Error: Unable to open default QuickTime bitmap component!" << CErrorLog::endl;

		qt::CloseComponent(giComponent);

		if(iShowErrorMessages)
			MessageBox(m_pWindow->GetHWND(), "Import failed!", "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

//	*pLog << "OpenADefaultComponent(): " << qtErr << '\n';

	qtErr = qt::GraphicsExportSetInputGraphicsImporter(geComponent, giComponent);

//	*pLog << "GraphicsExportSetInputGraphicsImporter(): " << qtErr << '\n';

	qtErr = qt::GraphicsExportSetOutputFile(geComponent, &fileSpec2);

//	*pLog << "GraphicsExportSetOutputFile(): " << qtErr << '\n';

	qtErr = qt::GraphicsExportSetDepth(geComponent, 24);

//	*pLog << "GraphicsExportSetDepth(): " << qtErr << '\n';

	qtErr = qt::GraphicsExportDoExport(geComponent, nil);

//	*pLog << "GraphicsExportDoExport(): " << qtErr << '\n';

	qt::CloseComponent(geComponent);
	qt::CloseComponent(giComponent);

	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;

	std::ifstream infile;

	infile.open(szTempFilename, std::ios::in | std::ios::binary);

	if(infile.is_open() == 0)
	{
		if(pEditor->PrefGenerateLogFile())
			*pLog << "Error: Unable to open temporary file for PICT resource!" << CErrorLog::endl;

		DeleteFile(szTempFilename);

//		free(szTempFilename);

		if(iShowErrorMessages)
			MessageBox(m_pWindow->GetHWND(), "Import failed!", "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

//	*pLog << "Temporary file successfully opened.\n";

	infile.read((char *)&bmfh, sizeof(BITMAPFILEHEADER));
	infile.read((char *)&bmih, sizeof(BITMAPINFOHEADER));

	m_iTempWidth  = bmih.biWidth;
	m_iTempHeight = bmih.biHeight;

	m_tempRectDest.left   = 48;
	m_tempRectDest.top    = 120;
	m_tempRectDest.right  = m_tempRectDest.left + m_iTempWidth;
	m_tempRectDest.bottom = m_tempRectDest.top  + m_iTempHeight;

	int iMaxSize = (((129 * m_iTempWidth + 127) / 128) * 3 + 2) * m_iTempHeight * 3 + 126;

	iMaxSize += (4 - (iMaxSize & 3)) & 3;

	if(m_hTempPicture != NULL)
		qt::DisposeHandle(m_hTempPicture);

	m_hTempPicture = qt::NewHandleClear(iMaxSize);

	UCHAR *pOutput = (UCHAR *)*m_hTempPicture;

	UCHAR *pPictSize = pOutput; pOutput += sizeof(USHORT);	// Picture size

	qt::Rect rectImage;

	rectImage.left   = SwapEndianShort(0x0000);
	rectImage.top    = SwapEndianShort(0x0000);
	rectImage.right  = SwapEndianShort(m_iTempWidth);
	rectImage.bottom = SwapEndianShort(m_iTempHeight);

	*(qt::Rect *)pOutput = rectImage; pOutput += sizeof(qt::Rect);	// Bounding rectangle

	*(short *)pOutput = SwapEndianShort(0x0011); pOutput += sizeof(short);	// Version opcode
	*(short *)pOutput = SwapEndianShort(0x02FF); pOutput += sizeof(short);	// Extended version 2 picture

	*(short *)pOutput = SwapEndianShort(0x0C00); pOutput += sizeof(short);	// Header opcode
	*(short *)pOutput = SwapEndianShort(0xFFFE); pOutput += sizeof(short);	// Extended version 2 picture
	*(short *)pOutput = SwapEndianShort(0x0000); pOutput += sizeof(short);	// Reserved
	*(int   *)pOutput = SwapEndianInt(0x00480000); pOutput += sizeof(int);	// Horizontal resolution (72 dpi)
	*(int   *)pOutput = SwapEndianInt(0x00480000); pOutput += sizeof(int);	// Vertical resolution (72 dpi)
	*(qt::Rect *)pOutput = rectImage;            pOutput += sizeof(qt::Rect);	// Bounding rectangle
	*(int   *)pOutput = SwapEndianInt(0x00000000); pOutput += sizeof(int);	// Reserved

	*(short *)pOutput = SwapEndianShort(0x001E); pOutput += sizeof(short);	// Default highlight opcode

	*(short *)pOutput = SwapEndianShort(0x0001); pOutput += sizeof(short);	// Clipping region opcode
	*(short *)pOutput = SwapEndianShort(0x000A); pOutput += sizeof(short);	// Clipping region size (10 bytes)
	*(qt::Rect *)pOutput = rectImage;            pOutput += sizeof(qt::Rect);	// Clipping rectangle

	*(short *)pOutput = SwapEndianShort(0x009A); pOutput += sizeof(short);	// Direct bits opcode

	*(int *)pOutput = SwapEndianInt(0x000000FF); pOutput += sizeof(int);	// PixMap.baseAddr

	USHORT iRowBytes = m_iTempWidth * 4;

	*(USHORT *)pOutput = SwapEndianShort(0x8000 | iRowBytes); pOutput += sizeof(USHORT); // PixMap.rowBytes

	*(qt::Rect *)pOutput = rectImage;            pOutput += sizeof(qt::Rect);	// PixMap.bounds
	*(short *)pOutput = SwapEndianShort(0x0000); pOutput += sizeof(short);	// PixMap.pmVersion
	*(short *)pOutput = SwapEndianShort(0x0004); pOutput += sizeof(short);	// PixMap.packType (PackBits)
	*(int   *)pOutput = SwapEndianInt(0x00000000); pOutput += sizeof(int);	// PixMap.packSize
	*(int   *)pOutput = SwapEndianInt(0x00480000); pOutput += sizeof(int);	// PixMap.hRes (72 dpi)
	*(int   *)pOutput = SwapEndianInt(0x00480000); pOutput += sizeof(int);	// PixMap.vRes (72 dpi)
	*(short *)pOutput = SwapEndianShort(0x0010); pOutput += sizeof(short);	// PixMap.pixelType (direct RGB channels)
	*(short *)pOutput = SwapEndianShort(0x0020); pOutput += sizeof(short);	// PixMap.pixelSize (32 BPP)
	*(short *)pOutput = SwapEndianShort(0x0003); pOutput += sizeof(short);	// PixMap.cmpCount (3 components, R, G, and B)
	*(short *)pOutput = SwapEndianShort(0x0008); pOutput += sizeof(short);	// PixMap.cmpSize (8 bits per component)
	*(int   *)pOutput = SwapEndianInt(0x00000000); pOutput += sizeof(int);	// PixMap.planeBytes
	*(int   *)pOutput = SwapEndianInt(0x00000000); pOutput += sizeof(int);	// PixMap.pmTable
	*(int   *)pOutput = SwapEndianInt(0x00000000); pOutput += sizeof(int);	// PixMap.pmReserved

	*(qt::Rect *)pOutput = rectImage; pOutput += sizeof(qt::Rect);	// Source rectangle
	*(qt::Rect *)pOutput = rectImage; pOutput += sizeof(qt::Rect);	// Destination rectangle

	*(short *)pOutput = SwapEndianShort(0x0000); pOutput += sizeof(short);	// Transfer mode (source copy)

	int i, j;

	std::vector<UCHAR> vBMPRow;
	std::vector<UCHAR> vBMPData;

	vBMPRow.resize(m_iTempWidth * 3);
	vBMPData.resize(m_iTempWidth * m_iTempHeight * 3);

	int iAlignment = (4 - ((m_iTempWidth * 3) & 3)) & 3;

	char szJunk[4];

	int iIndex;

	for(i = 0; i < m_iTempHeight; i++)
	{
		infile.read((char *)&vBMPRow[0], m_iTempWidth * 3);

		if(iAlignment > 0)
			infile.read(szJunk, iAlignment);

		for(j = 0; j < m_iTempWidth; j++)
		{
			iIndex = (m_iTempHeight - 1 - i) * m_iTempWidth * 3 + j;

			vBMPData[iIndex]                    = vBMPRow[3 * j + 2];
			vBMPData[iIndex + m_iTempWidth]     = vBMPRow[3 * j + 1];
			vBMPData[iIndex + m_iTempWidth * 2] = vBMPRow[3 * j];
		}
	}

	infile.close();

	UCHAR *pStartData = pOutput;

	UCHAR *pRowSize;

	UCHAR *pPixel;

	for(i = 0; i < m_iTempHeight; i++)
	{
		if(iRowBytes < 8)
		{
			for(j = 0; j < m_iTempWidth; j++)
			{
				*pOutput = 0x00;                                     pOutput++;
				*pOutput = vBMPData[(i * 3)     * m_iTempWidth + j]; pOutput++;
				*pOutput = vBMPData[(i * 3 + 1) * m_iTempWidth + j]; pOutput++;
				*pOutput = vBMPData[(i * 3 + 2) * m_iTempWidth + j]; pOutput++;
			}
		}
		else
		{
			pRowSize = pOutput;

			if(iRowBytes <= 250)
				pOutput += sizeof(UCHAR);
			else
				pOutput += sizeof(USHORT);

			for(j = 0; j < 3; j++)
			{
				pPixel = &vBMPData[(i * 3 + j) * m_iTempWidth];

				qt::PackBits((char **)&pPixel, (char **)&pOutput, m_iTempWidth);
			}

			if(iRowBytes <= 250)
				*pRowSize = static_cast<UCHAR>(pOutput - pRowSize - 1);
			else
				*(USHORT *)pRowSize = SwapEndianShort(static_cast<USHORT>(pOutput - pRowSize - 2));
		}
	}

	iAlignment = (4 - ((pOutput - pStartData) & 3)) & 3;

	for(i = 0; i < iAlignment; i++)
	{
		*pOutput = 0x00; pOutput++;
	}

	*(short *)pOutput = SwapEndianShort(0x00FF); pOutput += sizeof(short);	// End-of-picture opcode

	int iPictSize = pOutput - (UCHAR *)*m_hTempPicture;

	*(USHORT *)pPictSize = SwapEndianShort(static_cast<USHORT>(iPictSize));

	qt::SetHandleSize(m_hTempPicture, iPictSize);

	DeleteFile(szTempFilename);

//	free(szTempFilename);

	if(m_pWindow != NULL)
	{
		InitializePicture(m_pWindow->GetHWND());
	}
	else
	{
		if(m_hPicture != NULL)
			qt::DisposeHandle(m_hPicture);

		m_hPicture = m_hTempPicture;

		m_hTempPicture = NULL;

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
	if((m_hTempPicture == NULL) && (m_hPicture == NULL))
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
		strcpy_s(szFilename2, "");

		memset(&ofn, 0, sizeof(OPENFILENAME));

		ofn.lStructSize   = sizeof(OPENFILENAME);
		ofn.nMaxFile      = MAX_PATH;
		ofn.nMaxFileTitle = MAX_PATH;
		ofn.lpstrTitle    = "Export Picture";
		ofn.lpstrFilter   = "Bitmap (*.bmp)\0*.bmp\0Portable Network Graphics (*.png)\0*.png\0JPEG (*.jpg)\0*.jpg;*.jpeg\0Mac PICT (*.pic)\0*.pic\0TIFF (*.tiff)\0*.tiff\0Targa (*.tga)\0*.tga\0";
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
		strcpy_s(szFilename2, szFilename);
	}

	if(iImageType == 3)
	{
		std::ofstream outfile;

		outfile.open(szFilename2, std::ios::out | std::ios::trunc | std::ios::binary);

		char cJunk = 0x00;

		int i;

		for(i = 0; i < 512; i++)
			outfile.write(&cJunk, sizeof(char));

		if(m_hTempPicture != NULL)
			outfile.write(*m_hTempPicture, qt::GetHandleSize(m_hTempPicture));
		else
			outfile.write(*m_hPicture, qt::GetHandleSize(m_hPicture));

		outfile.close();

		return 1;
	}

	qt::FSSpec fileSpec;

	qt::OSErr qtErr;

	qt::GraphicsExportComponent geComponent;

	qt::CopyCStringToPascal(szFilename2, fileSpec.name);

	fileSpec.vRefNum = 0;
	fileSpec.parID   = 0;

	int iComponentType;

	if(iImageType == 0)
		iComponentType = qt::kQTFileTypeBMP;
	else if(iImageType == 1)
		iComponentType = qt::kQTFileTypePNG;
	else if(iImageType == 2)
		iComponentType = qt::kQTFileTypeJPEG;
	else if(iImageType == 4)
		iComponentType = qt::kQTFileTypeTIFF;
	else
		iComponentType = qt::kQTFileTypeTargaImage;

	qtErr = qt::OpenADefaultComponent(qt::GraphicsExporterComponentType, iComponentType, &geComponent);

	if(m_hTempPicture != NULL)
		qtErr = qt::GraphicsExportSetInputPicture(geComponent, (qt::PicHandle)m_hTempPicture);
	else
		qtErr = qt::GraphicsExportSetInputPicture(geComponent, (qt::PicHandle)m_hPicture);

	qtErr = qt::GraphicsExportSetOutputFile(geComponent, &fileSpec);

	qtErr = qt::GraphicsExportDoExport(geComponent, nil);

	qt::CloseComponent(geComponent);

	return 1;
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
