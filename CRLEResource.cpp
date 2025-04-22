// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CRLEResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CRLEResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CRLEResource::CRLEResource(void)
{
	m_iWidth     = 0;
	m_iHeight    = 0;
	m_iBPP       = 16;
	m_iNumFrames = 0;

	m_iFramesPerRow    = 6;
	m_iFramesPerColumn = 6;

	m_iCurPage = 0;

	m_iIsDirty = 0;

	m_iImportFilter = 1;
	m_iExportFilter = 1;

	m_hbmImage = NULL;
}

CRLEResource::~CRLEResource(void)
{
	if(m_hbmImage != NULL)
		DeleteObject(m_hbmImage);
}

int CRLEResource::GetType(void)
{
	if(m_iBPP == 8)
		return CNR_TYPE_RLE8;
	else
		return CNR_TYPE_RLED;
}

int CRLEResource::GetSize(void)
{
	return (m_vData1.size());
}

int CRLEResource::GetDialogID(void)
{
	return IDD_EDIT_RLE;
}

DLGPROCNOCALLBACK CRLEResource::GetDialogProc(void)
{
	return RLEDlgProc;
}

int CRLEResource::GetNumFields(void)
{
	return NUM_RLE_FIELDS;
}

const std::string * CRLEResource::GetFieldNames(void)
{
	return g_szRleFields;
}

int CRLEResource::ShouldLoadDirect(void)
{
	return 1;
}

int CRLEResource::SaveDirect(std::ostream & output)
{
	if(m_vData1.size() > 0)
		output.write((char *)&m_vData1[0], m_vData1.size() * sizeof(UCHAR));

	return 1;
}

int CRLEResource::LoadDirect(std::istream & input, int iSize)
{
	m_vData1.resize(iSize);

	input.read((char *)&m_vData1[0], iSize);

	return 1;
}

int CRLEResource::Save(char *pOutput)
{
	if(m_vData1.size() > 0)
		memcpy(pOutput, &m_vData1[0], m_vData1.size());

	return 1;
}

int CRLEResource::Load(char *pInput, int iSize)
{
	m_vData1.resize(iSize);

	memcpy(&m_vData1[0], pInput, iSize);

	return 1;
}

int CRLEResource::SwapEndians(void)
{
	m_iWidth     = SwapEndianShort(m_iWidth);
	m_iHeight    = SwapEndianShort(m_iHeight);
	m_iBPP       = SwapEndianShort(m_iBPP);
	m_iNumFrames = SwapEndianShort(m_iNumFrames);

	return 1;
}

int CRLEResource::SaveToTextEx(std::ostream & output, std::string & szFilePath, std::string & szFilename1, std::string & szFilename2, int iParam)
{
	if(m_vData2.size() == 0)
		CompileImage();

	output << m_iWidth     << '\t'
		   << m_iHeight    << '\t'
		   << m_iNumFrames << '\t'
		   << iParam       << '\t';

	PrintTextField(output, szFilename1.c_str(), '\t');
	PrintTextField(output, szFilename2.c_str(), '\t');

	std::string szImageFilename, szMaskFilename;

	szImageFilename = szFilePath + szFilename1;
	szMaskFilename  = szFilePath + szFilename2;

	DoExport(szImageFilename.c_str(), 1, m_iNumFrames, iParam, (m_iNumFrames + iParam - 1) / iParam, 0, 0);
	DoExport(szMaskFilename.c_str(),  0, m_iNumFrames, iParam, (m_iNumFrames + iParam - 1) / iParam, 0, 0);

	m_vData2.clear();
	m_vData3.clear();

	return 1;
}

int CRLEResource::LoadFromTextEx(std::istream & input, std::string & szFilePath)
{
	int iWidth;
	int iHeight;
	int iNumFrames;
	int iFramesPerRow;

	input >> iWidth
		  >> iHeight
		  >> iNumFrames
		  >> iFramesPerRow;

	input.ignore(1);

	int iFramesPerColumn = (iNumFrames + iFramesPerRow - 1) / iFramesPerRow;

	char szImageFilename[256];
	char szMaskFilename[256];

	strcpy_s(szImageFilename, szFilePath.c_str());
	strcpy_s(szMaskFilename,  szFilePath.c_str());

	ReadTextField(input, szImageFilename + strlen(szImageFilename), 256 - strlen(szImageFilename));
	ReadTextField(input, szMaskFilename  + strlen(szMaskFilename),  256 - strlen(szMaskFilename));

	DoImport(szImageFilename, 1, iNumFrames, iWidth, iHeight, iFramesPerRow, iFramesPerColumn, 0, 0);
	DoImport(szMaskFilename,  0, iNumFrames, iWidth, iHeight, iFramesPerRow, iFramesPerColumn, 0, 0);

	DecompileImage();

	return 1;
}

int CRLEResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	if(m_iBPP == 8)
		szTitle = "rle8 ";
	else
		szTitle = "rleD ";

	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_RLE_EDIT1, CCONTROL_TYPE_INT, IDS_STRING992);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_RLE_EDIT2, CCONTROL_TYPE_STR256, IDS_STRING993);
	m_controls[1].SetString(m_szName);
	m_controls[2].Create(hwnd, IDC_EDIT_RLE_EDIT3, CCONTROL_TYPE_INT, IDS_STRING994);
	m_controls[2].SetInt(m_iFramesPerRow);
	m_controls[3].Create(hwnd, IDC_EDIT_RLE_EDIT4, CCONTROL_TYPE_INT, IDS_STRING995);
	m_controls[3].SetInt(m_iFramesPerColumn);

	HMENU hRLEMenu;
	HMENU hViewSubmenu;

	hRLEMenu     = GetMenu(hwnd);
	hViewSubmenu = GetSubMenu(hRLEMenu, 1);

	MENUITEMINFO menuItemInfo;

	memset(&menuItemInfo, 0, sizeof(MENUITEMINFO));

	menuItemInfo.cbSize = sizeof(MENUITEMINFO);
	menuItemInfo.fMask  = MIIM_STATE;

	GetMenuItemInfo(hViewSubmenu, 0, TRUE, &menuItemInfo);

	menuItemInfo.fState |= MFS_CHECKED;

	SetMenuItemInfo(hViewSubmenu, 0, TRUE, &menuItemInfo);

	GetMenuItemInfo(hViewSubmenu, 1, TRUE, &menuItemInfo);

	menuItemInfo.fState &= ~MFS_CHECKED;

	SetMenuItemInfo(hViewSubmenu, 1, TRUE, &menuItemInfo);

	std::string szText;

	if(m_vData1.size() > 0)
	{
		CompileImage();

		MakeBitmap(hwnd);

		m_controls[2].SetMinValue(1); m_controls[2].SetMaxValue(m_iNumFrames);
		m_controls[3].SetMinValue(1); m_controls[3].SetMaxValue(m_iNumFrames);
	}
	else
	{
		szText = "Page 0 of 0";
		SetWindowText(GetDlgItem(hwnd, IDC_EDIT_RLE_TEXT8), szText.c_str());
	}

	szText = "Width: ";
	szText += ToString(m_iWidth);
	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_RLE_TEXT5), szText.c_str());

	szText = "Height: ";
	szText += ToString(m_iHeight);
	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_RLE_TEXT6), szText.c_str());

	szText = "Frames: ";
	szText += ToString(m_iNumFrames);
	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_RLE_TEXT7), szText.c_str());

	m_iIsDirty = 0;

	return 1;
}

int CRLEResource::CompileImage(void)
{
	if(m_vData1.size() == 0)
		return 0;

	CEditor *pEditor = CEditor::GetCurrentEditor();
	CErrorLog *pLog  = CErrorLog::GetCurrentErrorLog();

	char *pInput = (char *)&m_vData1[0];

	m_iWidth     = *(short *)pInput; pInput += sizeof(short);
	m_iHeight    = *(short *)pInput; pInput += sizeof(short);
	m_iBPP       = *(short *)pInput; pInput += sizeof(short); pInput += 2 * sizeof(char);
	m_iNumFrames = *(short *)pInput; pInput += sizeof(short); pInput += 6 * sizeof(char);

	SwapEndians();

	if((m_iBPP != 8) && (m_iBPP != 16))
	{
		if(pEditor->PrefGenerateLogFile())
			*pLog << "Error: Invalid number of bits per pixel (" << m_iBPP << ") in RLE resource!" << CErrorLog::endl;

		return 0;
	}

	int iBytesPerRow = m_iWidth * 3;

	int i, j;

	m_vData2.resize(m_iNumFrames);
	m_vData3.resize(m_iNumFrames);

	int iTransparentColor = pEditor->PrefRLEBackgroundColor();

	for(i = 0; i < m_iNumFrames; i++)
	{
		m_vData2[i].resize(m_iWidth * m_iHeight * 3);
		m_vData3[i].resize(m_iWidth * m_iHeight * 3);

		for(j = 0; j < m_iWidth * m_iHeight; j++)
		{
			m_vData2[i][3 * j]     =  iTransparentColor        & 0xFF;
			m_vData2[i][3 * j + 1] = (iTransparentColor >>  8) & 0xFF;
			m_vData2[i][3 * j + 2] = (iTransparentColor >> 16) & 0xFF;
		}

		memset(&m_vData3[i][0], 0x00, m_vData3[i].size());
	}

	char *pRowStart = NULL;

	int iCurLine = -1;
	int iCurOffset = 0;

	char cOpCode;

	int iCount;

	UCHAR ucPixel;
	USHORT iPixel;

	int iCurFrame = 0;

	UINT iPixelRun;

	while(1)
	{
		if(pInput >= (char *)(&m_vData1[0] + m_vData1.size()))
		{
			if(pEditor->PrefGenerateLogFile())
				*pLog << "Error: Early End-of-Resource in RLE resource!" << CErrorLog::endl;

			return 0;
		}

		if((pRowStart != NULL) && ((pInput - pRowStart) & 0x03))
			pInput += 4 - ((pInput - pRowStart) & 0x03);

		iCount = *(int *)pInput; pInput += sizeof(int); iCount = SwapEndianInt(iCount);

		cOpCode = static_cast<char>((iCount & 0xFF000000) >> 24);

		iCount &= 0x00FFFFFF;

		if(cOpCode == RLE_OPCODE_ENDOFFRAME)		// End-of-frame opcode
		{
			if(iCurLine != m_iHeight - 1)
			{
				if(pEditor->PrefGenerateLogFile())
					*pLog << "Warning: Not enough scan lines in RLE resource." << CErrorLog::endl;
			}

			if(++iCurFrame >= m_iNumFrames)
				break;

			iCurLine = -1;
		}
		else if(cOpCode == RLE_OPCODE_LINESTART)	// End-of-scanline opcode
		{
			iCurLine++;

			iCurOffset = iCurLine * iBytesPerRow;

			pRowStart = pInput;
		}
		else if(cOpCode == RLE_OPCODE_PIXELDATA)	// Pixel data opcode
		{
			if(m_iBPP == 8)
			{
				for(i = 0; i < iCount; i++)
				{
					ucPixel = *(UCHAR *)pInput; pInput++;

					m_vData2[iCurFrame][iCurOffset]     = ucPixel;
					m_vData2[iCurFrame][iCurOffset + 1] = ucPixel;
					m_vData2[iCurFrame][iCurOffset + 2] = ucPixel;

					m_vData3[iCurFrame][iCurOffset]     = 0xFF;
					m_vData3[iCurFrame][iCurOffset + 1] = 0xFF;
					m_vData3[iCurFrame][iCurOffset + 2] = 0xFF;

					iCurOffset += 3;
				}
			}
			else
			{
				for(i = 0; i < iCount; i += 2)
				{
					iPixel = *(USHORT *)pInput; pInput += sizeof(USHORT); iPixel = SwapEndianShort(iPixel);

					m_vData2[iCurFrame][iCurOffset    ] = static_cast<UCHAR>((iPixel & 0x001F) << 3);
					m_vData2[iCurFrame][iCurOffset + 1] = static_cast<UCHAR>((iPixel & 0x03E0) >> 2);
					m_vData2[iCurFrame][iCurOffset + 2] = static_cast<UCHAR>((iPixel & 0x7C00) >> 7);

					m_vData3[iCurFrame][iCurOffset    ] = 0xFF;
					m_vData3[iCurFrame][iCurOffset + 1] = 0xFF;
					m_vData3[iCurFrame][iCurOffset + 2] = 0xFF;

					iCurOffset += 3;
				}
			}

			if(iCount & 0x03)
				pInput += 4 - (iCount & 0x03);
		}
		else if(cOpCode == RLE_OPCODE_TRANSPARENTRUN)	// Transparent run opcode
		{
			iCurOffset += (iCount >> ((m_iBPP >> 3) - 1)) * 3;
		}
		else if(cOpCode == RLE_OPCODE_PIXELRUN)		// Pixel run opcode
		{
			iPixelRun = SwapEndianInt(*(UINT *)pInput); pInput += sizeof(UINT);

			if(m_iBPP == 8)
			{
				for(i = 0; i < iCount; i += 4)
				{
					for(j = 0; (j < 4) && (i + j < iCount); j++)
					{
						ucPixel = static_cast<UCHAR>((iPixelRun >> ((3 - j) << 3)) & 0x000000FF);

						m_vData2[iCurFrame][iCurOffset]     = ucPixel;
						m_vData2[iCurFrame][iCurOffset + 1] = ucPixel;
						m_vData2[iCurFrame][iCurOffset + 2] = ucPixel;

						m_vData3[iCurFrame][iCurOffset]     = 0xFF;
						m_vData3[iCurFrame][iCurOffset + 1] = 0xFF;
						m_vData3[iCurFrame][iCurOffset + 2] = 0xFF;

						iCurOffset += 3;
					}
				}
			}
			else
			{
				for(i = 0; i < iCount; i += 4)
				{
					m_vData2[iCurFrame][iCurOffset    ] = static_cast<UCHAR>((iPixelRun & 0x001F0000) >> 13);
					m_vData2[iCurFrame][iCurOffset + 1] = static_cast<UCHAR>((iPixelRun & 0x03E00000) >> 18);
					m_vData2[iCurFrame][iCurOffset + 2] = static_cast<UCHAR>((iPixelRun & 0x7C000000) >> 23);

					m_vData3[iCurFrame][iCurOffset    ] = 0xFF;
					m_vData3[iCurFrame][iCurOffset + 1] = 0xFF;
					m_vData3[iCurFrame][iCurOffset + 2] = 0xFF;

					iCurOffset += 3;

					if(i + 2 < iCount)
					{
						m_vData2[iCurFrame][iCurOffset    ] = static_cast<UCHAR>((iPixelRun & 0x0000001F) << 3);
						m_vData2[iCurFrame][iCurOffset + 1] = static_cast<UCHAR>((iPixelRun & 0x000003E0) >> 2);
						m_vData2[iCurFrame][iCurOffset + 2] = static_cast<UCHAR>((iPixelRun & 0x00007C00) >> 7);

						m_vData3[iCurFrame][iCurOffset    ] = 0xFF;
						m_vData3[iCurFrame][iCurOffset + 1] = 0xFF;
						m_vData3[iCurFrame][iCurOffset + 2] = 0xFF;

						iCurOffset += 3;
					}
				}
			}
		}
		else
		{
			if(pEditor->PrefGenerateLogFile())
				*pLog << "Error: Unknown opcode in RLE resource!" << CErrorLog::endl;
		}
	}

	return 1;
}

int CRLEResource::DecompileImage(void)
{
	if(m_vData2.size() == 0)
		return 0;

	int iMaxSize = 16 + (m_iHeight * m_iNumFrames + m_iNumFrames) * 4 + (m_iWidth * m_iHeight * m_iNumFrames) * (4 + (m_iBPP >> 3));

	m_vData1.resize(iMaxSize);

	memset(&m_vData1[0], 0, iMaxSize);

	int iSize = 16;

	char *pOutput = (char *)&m_vData1[0];

	SwapEndians();

	*(short *)pOutput = m_iWidth;     pOutput += sizeof(short);
	*(short *)pOutput = m_iHeight;    pOutput += sizeof(short);
	*(short *)pOutput = m_iBPP;       pOutput += sizeof(short); pOutput += sizeof(short);
	*(short *)pOutput = m_iNumFrames; pOutput += sizeof(short); pOutput += 6 * sizeof(char);

	SwapEndians();

	int iRunState;
	int iRunCount;

	char *pLineStart;
	char *pToken;

	int iAdvance = m_iBPP >> 3;

	UCHAR ucRed, ucGreen, ucBlue;
	UCHAR ucMask;

	int i, j, k;

	for(i = 0; i < m_iNumFrames; i++)
	{
		for(j = 0; j < m_iHeight; j++)
		{
			pLineStart = pOutput; pOutput += sizeof(int);

			iSize += sizeof(int);

			iRunState = 0;	// 0 = no run state
			iRunCount = 0;

			for(k = 0; k < m_iWidth; k++)
			{
				ucMask = m_vData3[i][(j * m_iWidth + k) * 3];

				ucRed   = m_vData2[i][(j * m_iWidth + k) * 3];
				ucGreen = m_vData2[i][(j * m_iWidth + k) * 3 + 1];
				ucBlue  = m_vData2[i][(j * m_iWidth + k) * 3 + 2];

				if(ucMask == 0x00)
				{
					if(iRunState == 0)
					{
						pToken = pOutput; pOutput += sizeof(int);	// Start transparent run

						iSize += sizeof(int);

						iRunState = RLE_OPCODE_TRANSPARENTRUN;

						iRunCount = iAdvance;
					}
					else if(iRunState == RLE_OPCODE_PIXELDATA)		// End pixel run, start transparent run
					{
						*(int *)pToken = SwapEndianInt((static_cast<int>(RLE_OPCODE_PIXELDATA) << 24) | iRunCount);

						if(iRunCount & 0x03)
						{
							pOutput += 4 - (iRunCount & 0x03);

							iSize += 4 - (iRunCount & 0x03);
						}

						pToken = pOutput; pOutput += sizeof(int);

						iSize += sizeof(int);

						iRunState = RLE_OPCODE_TRANSPARENTRUN;

						iRunCount = iAdvance;
					}
					else if(iRunState == RLE_OPCODE_TRANSPARENTRUN)		// Continue transparent run
					{
						iRunCount += iAdvance;
					}
				}
				else
				{
					if(iRunState == 0)		// Start pixel run
					{
						pToken = pOutput; pOutput += sizeof(int);

						iSize += sizeof(int);

						iRunState = RLE_OPCODE_PIXELDATA;

						iRunCount = iAdvance;
					}
					else if(iRunState == RLE_OPCODE_PIXELDATA)		// Continue pixel run
					{
						iRunCount += iAdvance;
					}
					else if(iRunState == RLE_OPCODE_TRANSPARENTRUN)		// End transparent run, start pixel run
					{
						*(int *)pToken = SwapEndianInt((static_cast<int>(RLE_OPCODE_TRANSPARENTRUN) << 24) | iRunCount);

						pToken = pOutput; pOutput += sizeof(int);

						iSize += sizeof(int);

						iRunState = RLE_OPCODE_PIXELDATA;

						iRunCount = iAdvance;
					}

					if(m_iBPP == 8)
					{
						*pOutput = ucRed; pOutput++;

						iSize += sizeof(UCHAR);
					}
					else if(m_iBPP == 16)
					{
						*(USHORT *)pOutput = SwapEndianShort((ucRed >> 3) | ((ucGreen >> 3) << 5) | ((ucBlue >> 3) << 10)); pOutput += sizeof(USHORT);

						iSize += sizeof(USHORT);
					}
				}
			}

			if(iRunState == RLE_OPCODE_PIXELDATA)		// End pixel run
			{
				*(int *)pToken = SwapEndianInt((static_cast<int>(RLE_OPCODE_PIXELDATA) << 24) | iRunCount);

				if(iRunCount & 0x03)
				{
					pOutput += 4 - (iRunCount & 0x03);

					iSize += 4 - (iRunCount & 0x03);
				}
			}
			else if(iRunState == RLE_OPCODE_TRANSPARENTRUN)		// Get rid of transparent run
			{
				iSize -= pOutput - pToken;

				pOutput = pToken;
			}

			*(int *)pLineStart = SwapEndianInt((static_cast<int>(RLE_OPCODE_LINESTART) << 24) | (pOutput - pLineStart - 4));	// End scanline
		}

		*(int *)pOutput = SwapEndianInt(static_cast<int>(RLE_OPCODE_ENDOFFRAME) << 24); pOutput += sizeof(int);	// End frame

		iSize += sizeof(int);
	}

	m_vData1.resize(iSize);

	return 1;
}

int CRLEResource::MakeBitmap(HWND hwnd)
{
	if((m_iWidth == 0) || (m_iHeight == 0) || (m_iNumFrames == 0) || (hwnd == NULL))
		return 0;

	if(m_hbmImage != NULL)
		DeleteObject(m_hbmImage);

	HDC hdcDisplay;

	HDC hdcDialog;
	HDC hdcMemory;
	HBITMAP hbmDDB;

	BITMAPINFO bmpInfo;

	hdcDisplay = CreateDC("DISPLAY", NULL, NULL, NULL);

	int iScreenWidth  = GetDeviceCaps(hdcDisplay, HORZRES);
	int iScreenHeight = GetDeviceCaps(hdcDisplay, VERTRES);

	if(m_iFramesPerRow * m_iFramesPerColumn > m_iNumFrames)
	{
		m_iFramesPerColumn = (m_iNumFrames + m_iFramesPerRow - 1) / m_iFramesPerRow;

		m_controls[3].SetInt(m_iFramesPerColumn);
	}

	if(m_iFramesPerRow > m_iNumFrames)
	{
		m_iFramesPerRow = m_iNumFrames;

		m_controls[2].SetInt(m_iFramesPerRow);
	}

	if(m_iWidth * m_iFramesPerRow + 96 > iScreenWidth)
	{
		m_iFramesPerRow = (iScreenWidth - 96) / m_iWidth;

		if(m_iFramesPerRow <= 0)
			m_iFramesPerRow = 1;

		m_controls[2].SetInt(m_iFramesPerRow);
	}

	if(m_iHeight * m_iFramesPerColumn + 284 > iScreenHeight)
	{
		m_iFramesPerColumn = (iScreenHeight - 284) / m_iHeight;

		if(m_iFramesPerColumn <= 0)
			m_iFramesPerColumn = 1;

		m_controls[3].SetInt(m_iFramesPerColumn);
	}

	DeleteDC(hdcDisplay);

	hdcDialog = GetDC(hwnd);
	hdcMemory = CreateCompatibleDC(hdcDialog);
	hbmDDB    = CreateCompatibleBitmap(hdcDialog, m_iWidth, m_iHeight);

	SelectObject(hdcMemory, hbmDDB);

	int iBMPWidth  = m_iWidth  * m_iFramesPerRow;
	int iBMPHeight = m_iHeight * m_iFramesPerColumn;

	memset(&bmpInfo, 0, sizeof(BITMAPINFO));

	bmpInfo.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth       = iBMPWidth;
	bmpInfo.bmiHeader.biHeight      = iBMPHeight;
	bmpInfo.bmiHeader.biPlanes      = 1;
	bmpInfo.bmiHeader.biBitCount    = 24;
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	bmpInfo.bmiHeader.biSizeImage   = bmpInfo.bmiHeader.biWidth * bmpInfo.bmiHeader.biHeight * 3;

	iBMPWidth *= 3;
	iBMPWidth += (4 - (iBMPWidth & 3)) & 3;

	UCHAR *ppBits = NULL;

	m_hbmImage = CreateDIBSection(hdcMemory, &bmpInfo, DIB_RGB_COLORS, (void **)&ppBits, NULL, 0);

	DeleteDC(hdcMemory);

	if(m_hbmImage == NULL)
		return 0;

	int iNumCells = m_iFramesPerRow * m_iFramesPerColumn;

	if(m_iCurPage >= (m_iNumFrames + iNumCells - 1) / iNumCells)
		m_iCurPage = (m_iNumFrames + iNumCells - 1) / iNumCells - 1;

	int iCurFrame = m_iCurPage * iNumCells;

	int i, j, k;

	HMENU hRLEMenu;
	HMENU hViewSubmenu;

	hRLEMenu     = GetMenu(hwnd);
	hViewSubmenu = GetSubMenu(hRLEMenu, 1);

	if(GetMenuState(hViewSubmenu, 0, MF_BYPOSITION) & MF_CHECKED)
	{
		for(i = 0; i < m_iFramesPerColumn; i++)
		{
			for(j = 0; j < m_iFramesPerRow; j++)
			{
				if(iCurFrame < m_iNumFrames)
				{
					for(k = 0; k < m_iHeight; k++)
						memcpy(ppBits + (iBMPHeight - 1 - i * m_iHeight - k) * iBMPWidth + j * m_iWidth * 3, &m_vData2[iCurFrame][k * m_iWidth * 3], m_iWidth * 3);

					iCurFrame++;
				}
				else
				{
					for(k = 0; k < m_iHeight; k++)
						memset(ppBits + (iBMPHeight - 1 - i * m_iHeight - k) * iBMPWidth + j * m_iWidth * 3, 0x00, m_iWidth * 3);
				}
			}
		}
	}
	else
	{
		for(i = 0; i < m_iFramesPerColumn; i++)
		{
			for(j = 0; j < m_iFramesPerRow; j++)
			{
				if(iCurFrame < m_iNumFrames)
				{
					for(k = 0; k < m_iHeight; k++)
						memcpy(ppBits + (iBMPHeight - 1 - i * m_iHeight - k) * iBMPWidth + j * m_iWidth * 3, &m_vData3[iCurFrame][k * m_iWidth * 3], m_iWidth * 3);

					iCurFrame++;
				}
				else
				{
					for(k = 0; k < m_iHeight; k++)
						memset(ppBits + (iBMPHeight - 1 - i * m_iHeight - k) * iBMPWidth + j * m_iWidth * 3, 0x00, m_iWidth * 3);
				}
			}
		}
	}

	SendMessage(GetDlgItem(hwnd, IDC_EDIT_RLE_PICT1), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hbmImage);

	std::string szText = "Page ";
	szText += ToString(m_iCurPage + 1);
	szText += " of ";
	szText += ToString((m_iNumFrames + iNumCells - 1) / iNumCells);
	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_RLE_TEXT8), szText.c_str());

	int iWidth = 320;

	if(m_iWidth * m_iFramesPerRow + 96 > iWidth)
		iWidth = m_iWidth * m_iFramesPerRow + 96;

	int iHeight = m_iHeight * m_iFramesPerColumn;

	MoveWindow(hwnd,                                  m_pWindow->GetXPos(), m_pWindow->GetYPos(), iWidth, iHeight + 284, TRUE);
	MoveWindow(GetDlgItem(hwnd, IDC_EDIT_RLE_OK),     iWidth - 192,         iHeight + 196,        72,     26,            TRUE);
	MoveWindow(GetDlgItem(hwnd, IDC_EDIT_RLE_CANCEL), iWidth - 96,          iHeight + 196,        72,     26,            TRUE);

	return 1;
}

int CRLEResource::CloseAndSave(void)
{
	std::string szError;

	if(CEditor::GetCurrentEditor()->IsUniqueResourceID(this, m_controls[0].GetInt()) == 0)
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

	m_iFramesPerRow    = m_controls[2].GetInt();
	m_iFramesPerColumn = m_controls[3].GetInt();

	if(m_iIsDirty)
	{
		DecompileImage();
	}

	m_iIsDirty = 0;

	if(CEditor::GetCurrentEditor()->PrefCacheRLEs() == 0)
	{
		m_vData2.clear();
		m_vData3.clear();
	}

	int i;

	for(i = 0; i < NUM_RLE_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CRLEResource::CloseAndDontSave(void)
{
	m_iIsDirty = 0;

	if(CEditor::GetCurrentEditor()->PrefCacheRLEs() == 0)
	{
		m_vData2.clear();
		m_vData3.clear();
	}

	int i;

	for(i = 0; i < NUM_RLE_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

int CRLEResource::FileImport(void)
{
	m_wndImport.SetExtraData(0, m_pWindow->GetExtraData(0));
	m_wndImport.SetExtraData(1, m_pWindow->GetExtraData(1));
	m_wndImport.SetExtraData(2, (int)this);
	m_wndImport.SetDlgProc(CRLEResource::RLEImportDlgProc);

	m_wndImport.CreateAsDialog(m_pWindow->GetInstance(), IDD_RLE_IMPORT, 1, m_pWindow);

	return 1;
}

int CRLEResource::FileExport(void)
{
	if((m_iWidth == 0) || (m_iHeight == 0) || (m_iNumFrames == 0) || (m_vData2.size() == 0))
	{
		MessageBox(m_pWindow->GetHWND(), "No image to export.", "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	m_wndExport.SetExtraData(0, m_pWindow->GetExtraData(0));
	m_wndExport.SetExtraData(1, m_pWindow->GetExtraData(1));
	m_wndExport.SetExtraData(2, (int)this);
	m_wndExport.SetDlgProc(CRLEResource::RLEExportDlgProc);

	m_wndExport.CreateAsDialog(m_pWindow->GetInstance(), IDD_RLE_EXPORT, 1, m_pWindow);

	return 1;
}

int CRLEResource::InitImportControls(HWND hwnd)
{
	m_importControls[0].Create(hwnd, IDC_RLE_IMPORT_EDIT1, CCONTROL_TYPE_STR256, -1);
	m_importControls[1].Create(hwnd, IDC_RLE_IMPORT_RADIO1, CCONTROL_TYPE_CHECK, -1);
	m_importControls[1].SetInt(1);
	m_importControls[2].Create(hwnd, IDC_RLE_IMPORT_RADIO2, CCONTROL_TYPE_CHECK, -1);
	m_importControls[2].SetInt(0);
	m_importControls[3].Create(hwnd, IDC_RLE_IMPORT_EDIT2, CCONTROL_TYPE_INT, -1);
	m_importControls[3].SetInt(1);
	m_importControls[4].Create(hwnd, IDC_RLE_IMPORT_EDIT3, CCONTROL_TYPE_INT, -1);
	m_importControls[4].SetInt(1);
	m_importControls[5].Create(hwnd, IDC_RLE_IMPORT_EDIT4, CCONTROL_TYPE_INT, -1);
	m_importControls[5].SetInt(1);
	m_importControls[6].Create(hwnd, IDC_RLE_IMPORT_EDIT5, CCONTROL_TYPE_INT, -1);
	m_importControls[6].SetInt(1);
	m_importControls[7].Create(hwnd, IDC_RLE_IMPORT_EDIT6, CCONTROL_TYPE_INT, -1);
	m_importControls[8].Create(hwnd, IDC_RLE_IMPORT_EDIT7, CCONTROL_TYPE_INT, -1);

	if(m_iWidth != 0)
	{
		m_importControls[7].SetInt(m_iWidth);
		m_importControls[8].SetInt(m_iHeight);

		Edit_SetReadOnly(m_importControls[7].GetHWND(), TRUE);
		Edit_SetReadOnly(m_importControls[8].GetHWND(), TRUE);
	}
	else
	{
		m_importControls[7].SetInt(1);
		m_importControls[8].SetInt(1);

		m_importControls[7].SetMinValue(1);
		m_importControls[8].SetMinValue(1);
	}

	m_importControls[3].SetMinValue(1);
	m_importControls[4].SetMinValue(1);
	m_importControls[5].SetMinValue(1);
	m_importControls[6].SetMinValue(1);

	return 1;
}

int CRLEResource::InitExportControls(HWND hwnd)
{
	m_exportControls[0].Create(hwnd, IDC_RLE_EXPORT_EDIT1, CCONTROL_TYPE_STR256, -1);
	m_exportControls[1].Create(hwnd, IDC_RLE_EXPORT_RADIO1, CCONTROL_TYPE_CHECK, -1);
	m_exportControls[1].SetInt(1);
	m_exportControls[2].Create(hwnd, IDC_RLE_EXPORT_RADIO2, CCONTROL_TYPE_CHECK, -1);
	m_exportControls[2].SetInt(0);
	m_exportControls[3].Create(hwnd, IDC_RLE_EXPORT_EDIT2, CCONTROL_TYPE_INT, -1);
	m_exportControls[3].SetInt(m_iNumFrames);
	m_exportControls[4].Create(hwnd, IDC_RLE_EXPORT_EDIT3, CCONTROL_TYPE_INT, -1);
	m_exportControls[4].SetInt(6);
	m_exportControls[5].Create(hwnd, IDC_RLE_EXPORT_EDIT4, CCONTROL_TYPE_INT, -1);
	m_exportControls[5].SetInt((m_iNumFrames + 5) / 6);
	m_exportControls[6].Create(hwnd, IDC_RLE_EXPORT_EDIT5, CCONTROL_TYPE_INT, -1);
	m_exportControls[6].SetInt(1);

	m_exportControls[3].SetMinValue(1); m_exportControls[3].SetMaxValue(m_iNumFrames);
	m_exportControls[4].SetMinValue(1); m_exportControls[4].SetMaxValue(m_iNumFrames);
	m_exportControls[5].SetMinValue(1); m_exportControls[5].SetMaxValue(m_iNumFrames);
	m_exportControls[6].SetMinValue(1); m_exportControls[6].SetMaxValue(m_iNumFrames);

	return 1;
}

int CRLEResource::DoImportBrowse(void)
{
	char szFilename[MAX_PATH];

	strcpy_s(szFilename, "");

	OPENFILENAME ofn;

	memset(&ofn, 0, sizeof(OPENFILENAME));

	ofn.lStructSize   = sizeof(OPENFILENAME);
	ofn.nMaxFile      = MAX_PATH;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrTitle    = "Import RLE Resource";
	ofn.lpstrFilter   = "Image Files\0*.bmp;*.png;*.jpg;*.jpeg;*.gif;*.pic;*.tiff;*.tga\0All Files (*.*)\0*.*\0";
	ofn.nFilterIndex  = 1;
	ofn.lpstrDefExt   = "bmp";
	ofn.Flags         = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	ofn.hwndOwner     = m_wndExport.GetHWND();
	ofn.lpstrFile     = szFilename;

	if(GetOpenFileName(&ofn) == 0)
		return 0;

	m_iImportFilter = ofn.nFilterIndex;

	m_importControls[0].SetString(szFilename);

	return 1;
}

int CRLEResource::DoExportBrowse(void)
{
	char szFilename[MAX_PATH];

	strcpy_s(szFilename, "");

	OPENFILENAME ofn;

	memset(&ofn, 0, sizeof(OPENFILENAME));

	ofn.lStructSize   = sizeof(OPENFILENAME);
	ofn.nMaxFile      = MAX_PATH;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrTitle    = "Export RLE Resource";
	ofn.lpstrFilter   = "Bitmap (*.bmp)\0*.bmp\0Portable Network Graphics (*.png)\0*.png\0JPEG (*.jpg)\0*.jpg;*.jpeg\0TIFF (*.tiff)\0*.tiff\0";
	ofn.nFilterIndex  = 1;
	ofn.lpstrDefExt   = "bmp";
	ofn.Flags         = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.hwndOwner     = m_wndExport.GetHWND();
	ofn.lpstrFile     = szFilename;

	if(GetSaveFileName(&ofn) == 0)
		return 0;

	m_iExportFilter = ofn.nFilterIndex;

	m_exportControls[0].SetString(szFilename);

	return 1;
}

int CRLEResource::DoImport(const char *szFilename, int iIsImage, int iNumFramesToImport, int iWidth, int iHeight, int iFramesPerRow, int iFramesPerColumn, int iFirstFrame, int iShowErrorMessages)
{
	CEditor *pEditor = CEditor::GetCurrentEditor();
	CErrorLog *pLog  = CErrorLog::GetCurrentErrorLog();

	int i, j, k;

	if(strcmp(szFilename, "") == 0)
	{
		if(iShowErrorMessages)
			MessageBox(m_wndImport.GetHWND(), "Please enter a filename.", "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	if(((m_iWidth != 0) && (iWidth != m_iWidth)) || ((m_iHeight != 0) && (iHeight != m_iHeight)))
	{
		if(iShowErrorMessages)
			MessageBox(m_wndImport.GetHWND(), "Invalid dimensions.", "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	std::string szError;

	if((iWidth <= 0) || (iHeight <= 0) || (iFirstFrame < 0) || (iFramesPerRow <= 0) || (iFramesPerColumn <= 0) || (iNumFramesToImport <= 0))
	{
		if(iWidth <= 0)
			szError = "\"Width\"";
		else if(iHeight <= 0)
			szError = "\"Height\"";
		else if(iFirstFrame < 0)
			szError = "\"First frame\"";
		else if(iFramesPerRow <= 0)
			szError = "\"X Frames\"";
		else if(iFramesPerColumn <= 0)
			szError = "\"Y Frames\"";
		else
			szError = "\"Number of frames\"";

		szError += " contains an invalid value.";

		if(iShowErrorMessages)
			MessageBox(m_wndImport.GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	qt::FSSpec fileSpec;

	qt::OSErr qtErr;

	qt::GraphicsImportComponent giComponent;
	qt::GraphicsExportComponent geComponent;

	qt::CopyCStringToPascal(szFilename, fileSpec.name);

	fileSpec.vRefNum = 0;
	fileSpec.parID   = 0;

	qtErr = qt::GetGraphicsImporterForFile(&fileSpec, &giComponent);

	if(qtErr != qt::noErr)
	{
		if(pEditor->PrefGenerateLogFile())
			*pLog << "Error: Unable to get graphics importer for \"" << szFilename << "\" for RLE resource!" << CErrorLog::endl;

		szError = "Unable to open file \"";
		szError += szFilename;
		szError += "\"!";

		if(iShowErrorMessages)
			MessageBox(m_wndImport.GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		if(m_wndImport.IsCreated())
		{
			for(i = 0; i < NUM_RLE_IMPORT_CONTROLS; i++)
				m_importControls[i].Destroy();

			m_wndImport.Destroy();
		}

		return 0;
	}

	m_iWidth  = iWidth;
	m_iHeight = iHeight;

	if(iFirstFrame + iNumFramesToImport - 1 >= m_iNumFrames)
	{
		i = m_iNumFrames;

		m_iNumFrames = iFirstFrame + iNumFramesToImport;

		m_vData2.resize(m_iNumFrames);
		m_vData3.resize(m_iNumFrames);

		for( ; i < m_iNumFrames; i++)
		{
			m_vData2[i].resize(m_iWidth * m_iHeight * 3);
			m_vData3[i].resize(m_iWidth * m_iHeight * 3);

			memset(&m_vData2[i][0], 0x00, m_vData2[i].size());
			memset(&m_vData3[i][0], 0xFF, m_vData3[i].size());
		}
	}

	qt::Rect rectImage;

	qtErr = qt::GraphicsImportGetNaturalBounds(giComponent, &rectImage);

	rectImage.right  -= rectImage.left;
	rectImage.bottom -= rectImage.top;
	rectImage.left    = 0;
	rectImage.top     = 0;

	if(m_iWidth * iFramesPerRow > rectImage.right)
		iFramesPerRow = rectImage.right / m_iWidth;

	if(m_iHeight * iFramesPerColumn > rectImage.bottom)
		iFramesPerColumn = rectImage.bottom / m_iHeight;

	char szTempFilename[MAX_PATH];

	strcpy_s(szTempFilename, "RLE");

//	szTempFilename = _tempnam(pEditor->GetTempFileDirectory(), "RLE");

//	if(szTempFilename == NULL)
	if(pEditor->GenerateTempFilename(szTempFilename) == 0)
	{
		if(pEditor->PrefGenerateLogFile())
			*pLog << "Error: Unable to make temporary file for RLE resource!" << CErrorLog::endl;

		qt::CloseComponent(giComponent);

		if(iShowErrorMessages)
			MessageBox(m_wndImport.GetHWND(), "Import failed!", "Error", MB_OK | MB_ICONEXCLAMATION);

		if(m_wndImport.IsCreated())
		{
			for(i = 0; i < NUM_RLE_IMPORT_CONTROLS; i++)
				m_importControls[i].Destroy();

			m_wndImport.Destroy();
		}

		return 0;
	}

	qtErr = qt::OpenADefaultComponent(qt::GraphicsExporterComponentType, qt::kQTFileTypeBMP, &geComponent);

	qtErr = qt::GraphicsExportSetInputGraphicsImporter(geComponent, giComponent);

	qt::CopyCStringToPascal(szTempFilename, fileSpec.name);

	qtErr = qt::GraphicsExportSetOutputFile(geComponent, &fileSpec);

	qtErr = qt::GraphicsExportSetDepth(geComponent, 24);

	qtErr = qt::GraphicsExportDoExport(geComponent, nil);

	qt::CloseComponent(geComponent);

	qt::CloseComponent(giComponent);

	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;

	std::ifstream infile;

	infile.open(szTempFilename, std::ios::in | std::ios::binary);

	if(infile.is_open() == 0)
	{
		if(pEditor->PrefGenerateLogFile())
			*pLog << "Error: Unable to open temporary file for RLE resource!" << CErrorLog::endl;

		DeleteFile(szTempFilename);

//		free(szTempFilename);

		if(iShowErrorMessages)
			MessageBox(m_wndImport.GetHWND(), "Import failed!", "Error", MB_OK | MB_ICONEXCLAMATION);

		if(m_wndImport.IsCreated())
		{
			for(i = 0; i < NUM_RLE_IMPORT_CONTROLS; i++)
				m_importControls[i].Destroy();

			m_wndImport.Destroy();
		}

		return 0;
	}

	infile.read((char *)&bmfh, sizeof(BITMAPFILEHEADER));
	infile.read((char *)&bmih, sizeof(BITMAPINFOHEADER));

	int iAlignment = (4 - ((rectImage.right * 3) & 3)) & 3;

	for(i = iFramesPerColumn * m_iHeight; i < rectImage.bottom; i++)
		infile.seekg(rectImage.right * 3 + iAlignment, std::ios::cur);

	int iCurFrame;

	int iLastFrame = iFirstFrame + iNumFramesToImport;

	for(i = iFramesPerColumn - 1; i >= 0; i--)
	{
		for(j = m_iHeight - 1; j >= 0; j--)
		{
			for(k = 0; k < iFramesPerRow; k++)
			{
				iCurFrame = iFirstFrame + iFramesPerRow * i + k;

				if(iCurFrame < iLastFrame)
				{
					if(iIsImage)
					{
						infile.read((char *)&m_vData2[iCurFrame][j * m_iWidth * 3], m_iWidth * 3);
					}
					else
					{
						infile.read((char *)&m_vData3[iCurFrame][j * m_iWidth * 3], m_iWidth * 3);
					}
				}
				else
				{
					infile.seekg(m_iWidth * 3, std::ios::cur);
				}
			}

			infile.seekg((rectImage.right - iFramesPerRow * m_iWidth) * 3 + iAlignment, std::ios::cur);
		}
	}

	infile.close();

	DeleteFile(szTempFilename);

//	free(szTempFilename);

	UCHAR ucGrey;

	if((iIsImage) && (m_iBPP == 8))
	{
		for(i = iFirstFrame; i < iLastFrame; i++)
		{
			for(j = 0; j < m_iHeight; j++)
			{
				for(k = 0; k < m_iWidth; k++)
				{
					ucGrey = static_cast<UCHAR>(((int)m_vData2[i][(j * m_iWidth + k) * 3] +
						(int)m_vData2[i][(j * m_iWidth + k) * 3 + 1] +
						(int)m_vData2[i][(j * m_iWidth + k) * 3 + 2]) / 3);

					m_vData2[i][(j * m_iWidth + k) * 3]     = ucGrey;
					m_vData2[i][(j * m_iWidth + k) * 3 + 1] = ucGrey;
					m_vData2[i][(j * m_iWidth + k) * 3 + 2] = ucGrey;
				}
			}
		}
	}

	if(iIsImage)
	{
		for(i = iFirstFrame; i < iLastFrame; i++)
		{
			for(j = 0; j < m_iHeight; j++)
			{
				for(k = 0; k < m_iWidth; k++)
				{
					if((m_vData2[i][(j * m_iWidth + k) * 3]     == 0x00) &&
					   (m_vData2[i][(j * m_iWidth + k) * 3 + 1] == 0x00) &&
					   (m_vData2[i][(j * m_iWidth + k) * 3 + 2] == 0x00))
					{
						m_vData3[i][(j * m_iWidth + k) * 3]     = 0x00;
						m_vData3[i][(j * m_iWidth + k) * 3 + 1] = 0x00;
						m_vData3[i][(j * m_iWidth + k) * 3 + 2] = 0x00;
					}
				}
			}
		}
	}
	else
	{
		for(i = iFirstFrame; i < iLastFrame; i++)
		{
			for(j = 0; j < m_iHeight; j++)
			{
				for(k = 0; k < m_iWidth; k++)
				{
					if((m_vData3[i][(j * m_iWidth + k) * 3]     != 0x00) ||
					   (m_vData3[i][(j * m_iWidth + k) * 3 + 1] != 0x00) ||
					   (m_vData3[i][(j * m_iWidth + k) * 3 + 2] != 0x00))
					{
						m_vData3[i][(j * m_iWidth + k) * 3]     = 0xFF;
						m_vData3[i][(j * m_iWidth + k) * 3 + 1] = 0xFF;
						m_vData3[i][(j * m_iWidth + k) * 3 + 2] = 0xFF;
					}
				}
			}
		}
	}

	if(m_wndImport.IsCreated())
	{
		for(i = 0; i < NUM_RLE_IMPORT_CONTROLS; i++)
			m_importControls[i].Destroy();

		m_wndImport.Destroy();
	}

	if(m_pWindow != NULL)
	{
		MakeBitmap(m_pWindow->GetHWND());
	}

	m_iIsDirty = 1;

	return 1;
}

int CRLEResource::DoExport(const char *szFilename, int iIsImage, int iNumFramesToExport, int iFramesPerRow, int iFramesPerColumn, int iFirstFrame, int iShowErrorMessages)
{
	CEditor *pEditor = CEditor::GetCurrentEditor();
	CErrorLog *pLog  = CErrorLog::GetCurrentErrorLog();

	int i, j, k;

	const char *pExtension = strrchr(szFilename, '.');

	std::string szError;

	if(pExtension == NULL)
	{
		szError = "\"";
		szError += szFilename;
		szError += "\" contains no extension.  Please select .bmp, .png, .jpg, or .tiff.";

		if(iShowErrorMessages)
			MessageBox(m_wndExport.GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}
	else
	{
		pExtension++;

		if(_stricmp(pExtension, "bmp") == 0)
			m_iExportFilter  = 1;
		else if(_stricmp(pExtension, "png") == 0)
			m_iExportFilter = 2;
		else if((_stricmp(pExtension, "jpg") == 0) || (_stricmp(pExtension, "jpeg") == 0))
			m_iExportFilter = 3;
		else if(_stricmp(pExtension, "tiff") == 0)
			m_iExportFilter = 4;
		else
		{
			szError = "\".";
			szError += pExtension;
			szError += "\" is not a supported image format.  Please select .bmp, .png, .jpg, or .tiff.";

			if(iShowErrorMessages)
				MessageBox(m_wndExport.GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

			return 0;
		}
	}

	if(strcmp(szFilename, "") == 0)
	{
		if(iShowErrorMessages)
			MessageBox(m_wndExport.GetHWND(), "Please enter a filename.", "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	if((iFirstFrame < 0) || (iNumFramesToExport <= 0) || (iFramesPerRow <= 0) || (iFramesPerColumn <= 0))
	{
		if(iFirstFrame < 0)
			szError = "\"First frame\"";
		else if(iNumFramesToExport <= 0)
			szError = "\"Number of frames\"";
		else if(iFramesPerRow <= 0)
			szError = "\"X Frames\"";
		else
			szError = "\"Y Frames\"";

		szError += " contains an invalid value.";

		if(iShowErrorMessages)
			MessageBox(m_wndExport.GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	if(iFirstFrame + iNumFramesToExport > m_iNumFrames)
		iNumFramesToExport = m_iNumFrames - iFirstFrame;

	char szTempFilename[MAX_PATH];

	strcpy_s(szTempFilename, "RLE");

	std::ofstream outfile;

	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;

	memset(&bmfh, 0, sizeof(BITMAPFILEHEADER));
	memset(&bmih, 0, sizeof(BITMAPINFOHEADER));

	int iSizeImage = iFramesPerRow * m_iWidth * 3;
	iSizeImage += (4 - (iSizeImage & 3)) & 3;
	iSizeImage *= iFramesPerColumn * m_iHeight;

	bmfh.bfType      = 0x4D42;	// 0x4D42 = "BM"
	bmfh.bfSize      = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + iSizeImage;
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits   = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	bmih.biSize          = sizeof(BITMAPINFOHEADER);
	bmih.biWidth         = iFramesPerRow    * m_iWidth;
	bmih.biHeight        = iFramesPerColumn * m_iHeight;
	bmih.biPlanes        = 1;
	bmih.biBitCount      = 24;
	bmih.biCompression   = BI_RGB;
	bmih.biSizeImage     = iSizeImage;
	bmih.biXPelsPerMeter = 0;
	bmih.biYPelsPerMeter = 0;
	bmih.biClrUsed       = 0;
	bmih.biClrImportant  = 0;

	if(m_iExportFilter == 1)
	{
		outfile.open(szFilename, std::ios::out | std::ios::trunc | std::ios::binary);

		if(outfile.is_open() == 0)
		{
			if(pEditor->PrefGenerateLogFile())
				*pLog << "Error: Unable to open file \"" << szFilename << "\" for exporting RLE resource!" << CErrorLog::endl;

			if(iShowErrorMessages)
				MessageBox(m_wndImport.GetHWND(), "Export failed!", "Error", MB_OK | MB_ICONEXCLAMATION);

			if(m_wndExport.IsCreated())
			{
				for(i = 0; i < NUM_RLE_EXPORT_CONTROLS; i++)
					m_exportControls[i].Destroy();

				m_wndExport.Destroy();
			}

			return 0;
		}
	}
	else
	{
//		szTempFilename = _tempnam(pEditor->GetTempFileDirectory(), "RLE");

//		if(szTempFilename == NULL)
		if(pEditor->GenerateTempFilename(szTempFilename) == 0)
		{
			if(pEditor->PrefGenerateLogFile())
				*pLog << "Error: Unable to make temporary file for RLE resource!" << CErrorLog::endl;

			if(iShowErrorMessages)
				MessageBox(m_wndImport.GetHWND(), "Export failed!", "Error", MB_OK | MB_ICONEXCLAMATION);

			if(m_wndExport.IsCreated())
			{
				for(i = 0; i < NUM_RLE_EXPORT_CONTROLS; i++)
					m_exportControls[i].Destroy();

				m_wndExport.Destroy();
			}

			return 0;
		}

		outfile.open(szTempFilename, std::ios::out | std::ios::trunc | std::ios::binary);

		if(outfile.is_open() == 0)
		{
			if(pEditor->PrefGenerateLogFile())
				*pLog << "Error: Unable to open temporary file \"" << szTempFilename << "\" for exporting RLE resource!" << CErrorLog::endl;

			if(iShowErrorMessages)
				MessageBox(m_wndImport.GetHWND(), "Export failed!", "Error", MB_OK | MB_ICONEXCLAMATION);

			if(m_wndExport.IsCreated())
			{
				for(i = 0; i < NUM_RLE_EXPORT_CONTROLS; i++)
					m_exportControls[i].Destroy();

				m_wndExport.Destroy();
			}

//			free(szTempFilename);

			return 0;
		}
	}

	outfile.write((char *)&bmfh, sizeof(BITMAPFILEHEADER));
	outfile.write((char *)&bmih, sizeof(BITMAPINFOHEADER));

	std::vector<char> vJunk;

	vJunk.resize(m_iWidth * 3);

	memset(&vJunk[0], 0, vJunk.size());

	int iCurFrame;

	int iLastFrame = iFirstFrame + iNumFramesToExport;

	char szJunk2[4] = {0x00, 0x00, 0x00, 0x00};

	int iAlignment = (4 - ((iFramesPerRow * m_iWidth * 3) & 3)) & 3;

	for(i = iFramesPerColumn - 1; i >= 0; i--)
	{
		for(j = m_iHeight - 1; j >= 0; j--)
		{
			for(k = 0; k < iFramesPerRow; k++)
			{
				iCurFrame = iFirstFrame + iFramesPerRow * i + k;

				if(iCurFrame < iLastFrame)
				{
					if(iIsImage)
						outfile.write((char *)&m_vData2[iCurFrame][j * m_iWidth * 3], m_iWidth * 3);
					else
						outfile.write((char *)&m_vData3[iCurFrame][j * m_iWidth * 3], m_iWidth * 3);
				}
				else
				{
					outfile.write(&vJunk[0], m_iWidth * 3);
				}
			}

			outfile.write(szJunk2, iAlignment);
		}
	}

	outfile.close();

	if(m_iExportFilter != 1)
	{
		qt::FSSpec fileSpec;

		qt::OSErr qtErr;

		qt::GraphicsImportComponent giComponent;
		qt::GraphicsExportComponent geComponent;

		qt::CopyCStringToPascal(szTempFilename, fileSpec.name);

		fileSpec.vRefNum = 0;
		fileSpec.parID   = 0;

		qtErr = qt::GetGraphicsImporterForFile(&fileSpec, &giComponent);

		if(qtErr != qt::noErr)
		{
			if(pEditor->PrefGenerateLogFile())
				*pLog << "Error: Unable to get graphics importer for temporary BMP for RLE export!" << CErrorLog::endl;

			DeleteFile(szTempFilename);

//			free(szTempFilename);

			if(iShowErrorMessages)
				MessageBox(m_wndImport.GetHWND(), "Export failed!", "Error", MB_OK | MB_ICONEXCLAMATION);

			if(m_wndExport.IsCreated())
			{
				for(i = 0; i < NUM_RLE_EXPORT_CONTROLS; i++)
					m_exportControls[i].Destroy();

				m_wndExport.Destroy();
			}

			return 0;
		}

		int iImageType;

		if(m_iExportFilter == 2)
			iImageType = qt::kQTFileTypePNG;
		else if(m_iExportFilter == 3)
			iImageType = qt::kQTFileTypeJPEG;
		else
			iImageType = qt::kQTFileTypeTIFF;

		qtErr = qt::OpenADefaultComponent(qt::GraphicsExporterComponentType, iImageType, &geComponent);

		qtErr = qt::GraphicsExportSetInputGraphicsImporter(geComponent, giComponent);

		qt::CopyCStringToPascal(szFilename, fileSpec.name);

		qtErr = qt::GraphicsExportSetOutputFile(geComponent, &fileSpec);

		qtErr = qt::GraphicsExportDoExport(geComponent, nil);

		qt::CloseComponent(geComponent);
		qt::CloseComponent(giComponent);

		DeleteFile(szTempFilename);

//		free(szTempFilename);
	}

	if(m_wndExport.IsCreated())
	{
		for(i = 0; i < NUM_RLE_EXPORT_CONTROLS; i++)
			m_exportControls[i].Destroy();

		m_wndExport.Destroy();
	}

	return 1;
}

int CRLEResource::ImportCloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_RLE_IMPORT_CONTROLS; i++)
		m_importControls[i].Destroy();

	m_wndImport.Destroy();

	return 1;
}

int CRLEResource::ExportCloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_RLE_EXPORT_CONTROLS; i++)
		m_exportControls[i].Destroy();

	m_wndExport.Destroy();

	return 1;
}

int CRLEResource::SetBPP(short iBPP)
{
	m_iBPP = iBPP;

	return 1;
}

short CRLEResource::GetBPP(void)
{
	return m_iBPP;
}

BOOL CRLEResource::RLEDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CRLEResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CRLEResource *)pWindow->GetExtraData(2);

	int i;

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			pResource->Initialize(hwnd);

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

			if(iControlID == IDC_EDIT_RLE_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_RLE_OK)
			{
				pResource->CloseAndSave();
			}
			else if(iControlID == IDC_EDIT_RLE_UPDATE)
			{
				pResource->m_iFramesPerRow    = pResource->m_controls[2].GetInt();
				pResource->m_iFramesPerColumn = pResource->m_controls[3].GetInt();

				pResource->MakeBitmap(hwnd);
			}
			else if(iControlID == IDC_EDIT_RLE_PREVPAGE)
			{
				if(pResource->m_iCurPage > 0)
				{
					pResource->m_iCurPage--;

					pResource->MakeBitmap(hwnd);
				}
			}
			else if(iControlID == IDC_EDIT_RLE_NEXTPAGE)
			{
				int iNumCells = pResource->m_iFramesPerRow * pResource->m_iFramesPerColumn;

				if(pResource->m_iCurPage < (pResource->m_iNumFrames + iNumCells - 1) / iNumCells)
				{
					pResource->m_iCurPage++;

					pResource->MakeBitmap(hwnd);
				}
			}
			else if(iControlID == IDM_RLE_FILE_IMPORT)
			{
				pResource->FileImport();
			}
			else if(iControlID == IDM_RLE_FILE_EXPORT)
			{
				pResource->FileExport();
			}
			else if(iControlID == IDM_RLE_FILE_CLOSEANDSAVE)
			{
				pResource->CloseAndSave();
			}
			else if(iControlID == IDM_RLE_FILE_CLOSEANDDONTSAVE)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDM_RLE_VIEW_IMAGE)
			{
				HMENU hRLEMenu;
				HMENU hViewSubmenu;

				hRLEMenu     = GetMenu(hwnd);
				hViewSubmenu = GetSubMenu(hRLEMenu, 1);

				MENUITEMINFO menuItemInfo;

				memset(&menuItemInfo, 0, sizeof(MENUITEMINFO));

				menuItemInfo.cbSize = sizeof(MENUITEMINFO);
				menuItemInfo.fMask  = MIIM_STATE;

				GetMenuItemInfo(hViewSubmenu, 0, TRUE, &menuItemInfo);

				menuItemInfo.fState |= MFS_CHECKED;

				SetMenuItemInfo(hViewSubmenu, 0, TRUE, &menuItemInfo);

				GetMenuItemInfo(hViewSubmenu, 1, TRUE, &menuItemInfo);

				menuItemInfo.fState &= ~MFS_CHECKED;

				SetMenuItemInfo(hViewSubmenu, 1, TRUE, &menuItemInfo);

				pResource->MakeBitmap(hwnd);
			}
			else if(iControlID == IDM_RLE_VIEW_MASK)
			{
				HMENU hRLEMenu;
				HMENU hViewSubmenu;

				hRLEMenu     = GetMenu(hwnd);
				hViewSubmenu = GetSubMenu(hRLEMenu, 1);

				MENUITEMINFO menuItemInfo;

				memset(&menuItemInfo, 0, sizeof(MENUITEMINFO));

				menuItemInfo.cbSize = sizeof(MENUITEMINFO);
				menuItemInfo.fMask  = MIIM_STATE;

				GetMenuItemInfo(hViewSubmenu, 0, TRUE, &menuItemInfo);

				menuItemInfo.fState &= ~MFS_CHECKED;

				SetMenuItemInfo(hViewSubmenu, 0, TRUE, &menuItemInfo);

				GetMenuItemInfo(hViewSubmenu, 1, TRUE, &menuItemInfo);

				menuItemInfo.fState |= MFS_CHECKED;

				SetMenuItemInfo(hViewSubmenu, 1, TRUE, &menuItemInfo);

				pResource->MakeBitmap(hwnd);
			}
			else
			{
				for(i = 0; i < NUM_RLE_CONTROLS; i++)
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

BOOL CRLEResource::RLEImportDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CRLEResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CRLEResource *)pWindow->GetExtraData(2);

	int i;

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			pResource->InitImportControls(hwnd);

			return TRUE;

			break;
		}

		case WM_SYSCOMMAND:
		{
			if(wparam == SC_CLOSE)
			{
				pResource->ImportCloseAndDontSave();

				return TRUE;
			}

			break;
		}

		case WM_COMMAND:
		{
			int iNotifyCode = HIWORD(wparam);
			int iControlID  = LOWORD(wparam);

			if(iControlID == IDC_RLE_IMPORT_CANCEL)
			{
				pResource->ImportCloseAndDontSave();
			}
			else if(iControlID == IDC_RLE_IMPORT_OK)
			{
				pResource->DoImport(pResource->m_importControls[0].GetString(), pResource->m_importControls[1].GetInt(), pResource->m_importControls[4].GetInt(), pResource->m_importControls[7].GetInt(), pResource->m_importControls[8].GetInt(), pResource->m_importControls[5].GetInt(), pResource->m_importControls[6].GetInt(), pResource->m_importControls[3].GetInt() - 1, 1);
			}
			else if(iControlID == IDC_RLE_IMPORT_BUTTON1)
			{
				pResource->DoImportBrowse();
			}
			else
			{
				for(i = 0; i < NUM_RLE_IMPORT_CONTROLS; i++)
				{
					if(iControlID == pResource->m_importControls[i].GetControlID())
					{
						pResource->m_importControls[i].ProcessMessage(iNotifyCode);

						break;
					}
				}
			}

			if((iControlID == IDC_RLE_IMPORT_RADIO1) && (iNotifyCode == BN_CLICKED))
			{
				if(Button_GetCheck((HWND)lparam) == BST_CHECKED)
				{
					pResource->m_importControls[2].SetInt(0);
				}
			}

			if((iControlID == IDC_RLE_IMPORT_RADIO2) && (iNotifyCode == BN_CLICKED))
			{
				if(Button_GetCheck((HWND)lparam) == BST_CHECKED)
				{
					pResource->m_importControls[1].SetInt(0);
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

BOOL CRLEResource::RLEExportDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CRLEResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CRLEResource *)pWindow->GetExtraData(2);

	int i;

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			pResource->InitExportControls(hwnd);

			return TRUE;

			break;
		}

		case WM_SYSCOMMAND:
		{
			if(wparam == SC_CLOSE)
			{
				pResource->ExportCloseAndDontSave();

				return TRUE;
			}

			break;
		}

		case WM_COMMAND:
		{
			int iNotifyCode = HIWORD(wparam);
			int iControlID  = LOWORD(wparam);

			if(iControlID == IDC_RLE_EXPORT_CANCEL)
			{
				pResource->ExportCloseAndDontSave();
			}
			else if(iControlID == IDC_RLE_EXPORT_OK)
			{
				pResource->DoExport(pResource->m_exportControls[0].GetString(), pResource->m_exportControls[1].GetInt(), pResource->m_exportControls[3].GetInt(), pResource->m_exportControls[4].GetInt(), pResource->m_exportControls[5].GetInt(), pResource->m_exportControls[6].GetInt() - 1, 1);
			}
			else if(iControlID == IDC_RLE_EXPORT_BUTTON1)
			{
				pResource->DoExportBrowse();
			}
			else
			{
				for(i = 0; i < NUM_RLE_EXPORT_CONTROLS; i++)
				{
					if(iControlID == pResource->m_exportControls[i].GetControlID())
					{
						pResource->m_exportControls[i].ProcessMessage(iNotifyCode);

						break;
					}
				}
			}

			if((iControlID == IDC_RLE_EXPORT_RADIO1) && (iNotifyCode == BN_CLICKED))
			{
				if(Button_GetCheck((HWND)lparam) == BST_CHECKED)
				{
					pResource->m_exportControls[2].SetInt(0);
				}
			}

			if((iControlID == IDC_RLE_EXPORT_RADIO2) && (iNotifyCode == BN_CLICKED))
			{
				if(Button_GetCheck((HWND)lparam) == BST_CHECKED)
				{
					pResource->m_exportControls[1].SetInt(0);
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
