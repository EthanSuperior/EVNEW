// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CColrResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CColrResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CColrResource::CColrResource(void)
{
	m_iButtonUp   = 0x00000000;
	m_iButtonDown = 0x00000000;
	m_iButtonGrey = 0x00000000;

	memset(m_szMenuFont, 0, 64 * sizeof(char));
	m_iMenuFontSize = 0;
	m_iMenuColor1   = 0x00000000;
	m_iMenuColor2   = 0x00000000;

	m_iGridBright = 0x00000000;
	m_iGridDim    = 0x00000000;

	m_iProgressBarX1   = 0;
	m_iProgressBarY1   = 0;
	m_iProgressBarX2   = 0;
	m_iProgressBarY2   = 0;
	m_iProgressBright  = 0x00000000;
	m_iProgressDim     = 0x00000000;
	m_iProgressOutline = 0x00000000;

	m_iButton1X = 0;
	m_iButton1Y = 0;
	m_iButton2X = 0;
	m_iButton2Y = 0;
	m_iButton3X = 0;
	m_iButton3Y = 0;
	m_iButton4X = 0;
	m_iButton4Y = 0;
	m_iButton5X = 0;
	m_iButton5Y = 0;
	m_iButton6X = 0;
	m_iButton6Y = 0;

	m_iFloatingMap     = 0x00000000;
	m_iListText        = 0x00000000;
	m_iListBackground  = 0x00000000;
	m_iListHighlight   = 0x00000000;
	m_iEscortHighlight = 0x00000000;

	memset(m_szButtonFont, 0, 64 * sizeof(char));
	m_iButtonFontSize = 0;

	m_iLogoX     = 0;
	m_iLogoY     = 0;
	m_iRolloverX = 0;
	m_iRolloverY = 0;
	m_iSlide1X   = 0;
	m_iSlide1Y   = 0;
	m_iSlide2X   = 0;
	m_iSlide2Y   = 0;
	m_iSlide3X   = 0;
	m_iSlide3Y   = 0;
}

CColrResource::~CColrResource(void)
{

}

int CColrResource::GetType(void)
{
	return CNR_TYPE_COLR;
}

int CColrResource::GetSize(void)
{
	return 244;
}

int CColrResource::GetDialogID(void)
{
	return IDD_EDIT_COLR;
}

DLGPROCNOCALLBACK CColrResource::GetDialogProc(void)
{
	return ColrDlgProc;
}

int CColrResource::GetNumFields(void)
{
	return NUM_COLR_FIELDS;
}

const std::string * CColrResource::GetFieldNames(void)
{
	return g_szColrFields;
}

int CColrResource::Save(char *pOutput)
{
	SwapEndians();

	*(UINT  *)pOutput = m_iButtonUp;        pOutput += sizeof(UINT);
	*(UINT  *)pOutput = m_iButtonDown;      pOutput += sizeof(UINT);
	*(UINT  *)pOutput = m_iButtonGrey;      pOutput += sizeof(UINT);

	memcpy(pOutput, m_szMenuFont, 64 * sizeof(char)); pOutput += 64 * sizeof(char);

	*(short *)pOutput = m_iMenuFontSize;    pOutput += sizeof(short);
	*(UINT  *)pOutput = m_iMenuColor1;      pOutput += sizeof(UINT);
	*(UINT  *)pOutput = m_iMenuColor2;      pOutput += sizeof(UINT);
	*(UINT  *)pOutput = m_iGridBright;      pOutput += sizeof(UINT);
	*(UINT  *)pOutput = m_iGridDim;         pOutput += sizeof(UINT);
	*(short *)pOutput = m_iProgressBarY1;   pOutput += sizeof(short);
	*(short *)pOutput = m_iProgressBarX1;   pOutput += sizeof(short);
	*(short *)pOutput = m_iProgressBarY2;   pOutput += sizeof(short);
	*(short *)pOutput = m_iProgressBarX2;   pOutput += sizeof(short);
	*(UINT  *)pOutput = m_iProgressBright;  pOutput += sizeof(UINT);
	*(UINT  *)pOutput = m_iProgressDim;     pOutput += sizeof(UINT);
	*(UINT  *)pOutput = m_iProgressOutline; pOutput += sizeof(UINT);
	*(short *)pOutput = m_iButton1X;        pOutput += sizeof(short);
	*(short *)pOutput = m_iButton1Y;        pOutput += sizeof(short);
	*(short *)pOutput = m_iButton2X;        pOutput += sizeof(short);
	*(short *)pOutput = m_iButton2Y;        pOutput += sizeof(short);
	*(short *)pOutput = m_iButton3X;        pOutput += sizeof(short);
	*(short *)pOutput = m_iButton3Y;        pOutput += sizeof(short);
	*(short *)pOutput = m_iButton4X;        pOutput += sizeof(short);
	*(short *)pOutput = m_iButton4Y;        pOutput += sizeof(short);
	*(short *)pOutput = m_iButton5X;        pOutput += sizeof(short);
	*(short *)pOutput = m_iButton5Y;        pOutput += sizeof(short);
	*(short *)pOutput = m_iButton6X;        pOutput += sizeof(short);
	*(short *)pOutput = m_iButton6Y;        pOutput += sizeof(short);
	*(UINT  *)pOutput = m_iFloatingMap;     pOutput += sizeof(UINT);
	*(UINT  *)pOutput = m_iListText;        pOutput += sizeof(UINT);
	*(UINT  *)pOutput = m_iListBackground;  pOutput += sizeof(UINT);
	*(UINT  *)pOutput = m_iListHighlight;   pOutput += sizeof(UINT);
	*(UINT  *)pOutput = m_iEscortHighlight; pOutput += sizeof(UINT);

	memcpy(pOutput, m_szButtonFont, 64 * sizeof(char)); pOutput += 64 * sizeof(char);

	*(short *)pOutput = m_iButtonFontSize;  pOutput += sizeof(short);
	*(short *)pOutput = m_iLogoX;           pOutput += sizeof(short);
	*(short *)pOutput = m_iLogoY;           pOutput += sizeof(short);
	*(short *)pOutput = m_iRolloverX;       pOutput += sizeof(short);
	*(short *)pOutput = m_iRolloverY;       pOutput += sizeof(short);
	*(short *)pOutput = m_iSlide1X;         pOutput += sizeof(short);
	*(short *)pOutput = m_iSlide1Y;         pOutput += sizeof(short);
	*(short *)pOutput = m_iSlide2X;         pOutput += sizeof(short);
	*(short *)pOutput = m_iSlide2Y;         pOutput += sizeof(short);
	*(short *)pOutput = m_iSlide3X;         pOutput += sizeof(short);
	*(short *)pOutput = m_iSlide3Y;         pOutput += sizeof(short);

	SwapEndians();

	return 1;
}

int CColrResource::Load(char *pInput, int iSize)
{
	m_iButtonUp        = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iButtonDown      = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iButtonGrey      = *(UINT  *)pInput; pInput += sizeof(UINT);

	memcpy(m_szMenuFont, pInput, 64 * sizeof(char)); pInput += 64 * sizeof(char);

	m_iMenuFontSize    = *(short *)pInput; pInput += sizeof(short);
	m_iMenuColor1      = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iMenuColor2      = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iGridBright      = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iGridDim         = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iProgressBarY1   = *(short *)pInput; pInput += sizeof(short);
	m_iProgressBarX1   = *(short *)pInput; pInput += sizeof(short);
	m_iProgressBarY2   = *(short *)pInput; pInput += sizeof(short);
	m_iProgressBarX2   = *(short *)pInput; pInput += sizeof(short);
	m_iProgressBright  = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iProgressDim     = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iProgressOutline = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iButton1X        = *(short *)pInput; pInput += sizeof(short);
	m_iButton1Y        = *(short *)pInput; pInput += sizeof(short);
	m_iButton2X        = *(short *)pInput; pInput += sizeof(short);
	m_iButton2Y        = *(short *)pInput; pInput += sizeof(short);
	m_iButton3X        = *(short *)pInput; pInput += sizeof(short);
	m_iButton3Y        = *(short *)pInput; pInput += sizeof(short);
	m_iButton4X        = *(short *)pInput; pInput += sizeof(short);
	m_iButton4Y        = *(short *)pInput; pInput += sizeof(short);
	m_iButton5X        = *(short *)pInput; pInput += sizeof(short);
	m_iButton5Y        = *(short *)pInput; pInput += sizeof(short);
	m_iButton6X        = *(short *)pInput; pInput += sizeof(short);
	m_iButton6Y        = *(short *)pInput; pInput += sizeof(short);
	m_iFloatingMap     = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iListText        = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iListBackground  = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iListHighlight   = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iEscortHighlight = *(UINT  *)pInput; pInput += sizeof(UINT);

	memcpy(m_szButtonFont, pInput, 64 * sizeof(char)); pInput += 64 * sizeof(char);

	m_iButtonFontSize  = *(short *)pInput; pInput += sizeof(short);
	m_iLogoX           = *(short *)pInput; pInput += sizeof(short);
	m_iLogoY           = *(short *)pInput; pInput += sizeof(short);
	m_iRolloverX       = *(short *)pInput; pInput += sizeof(short);
	m_iRolloverY       = *(short *)pInput; pInput += sizeof(short);
	m_iSlide1X         = *(short *)pInput; pInput += sizeof(short);
	m_iSlide1Y         = *(short *)pInput; pInput += sizeof(short);
	m_iSlide2X         = *(short *)pInput; pInput += sizeof(short);
	m_iSlide2Y         = *(short *)pInput; pInput += sizeof(short);
	m_iSlide3X         = *(short *)pInput; pInput += sizeof(short);
	m_iSlide3Y         = *(short *)pInput; pInput += sizeof(short);

	SwapEndians();

	return 1;
}

int CColrResource::SwapEndians(void)
{
	m_iButtonUp        = SwapEndianInt(m_iButtonUp);
	m_iButtonDown      = SwapEndianInt(m_iButtonDown);
	m_iButtonGrey      = SwapEndianInt(m_iButtonGrey);
	m_iMenuFontSize    = SwapEndianShort(m_iMenuFontSize);
	m_iMenuColor1      = SwapEndianInt(m_iMenuColor1);
	m_iMenuColor2      = SwapEndianInt(m_iMenuColor2);
	m_iGridBright      = SwapEndianInt(m_iGridBright);
	m_iGridDim         = SwapEndianInt(m_iGridDim);
	m_iProgressBarX1   = SwapEndianShort(m_iProgressBarX1);
	m_iProgressBarY1   = SwapEndianShort(m_iProgressBarY1);
	m_iProgressBarX2   = SwapEndianShort(m_iProgressBarX2);
	m_iProgressBarY2   = SwapEndianShort(m_iProgressBarY2);
	m_iProgressBright  = SwapEndianInt(m_iProgressBright);
	m_iProgressDim     = SwapEndianInt(m_iProgressDim);
	m_iProgressOutline = SwapEndianInt(m_iProgressOutline);
	m_iButton1X        = SwapEndianShort(m_iButton1X);
	m_iButton1Y        = SwapEndianShort(m_iButton1Y);
	m_iButton2X        = SwapEndianShort(m_iButton2X);
	m_iButton2Y        = SwapEndianShort(m_iButton2Y);
	m_iButton3X        = SwapEndianShort(m_iButton3X);
	m_iButton3Y        = SwapEndianShort(m_iButton3Y);
	m_iButton4X        = SwapEndianShort(m_iButton4X);
	m_iButton4Y        = SwapEndianShort(m_iButton4Y);
	m_iButton5X        = SwapEndianShort(m_iButton5X);
	m_iButton5Y        = SwapEndianShort(m_iButton5Y);
	m_iButton6X        = SwapEndianShort(m_iButton6X);
	m_iButton6Y        = SwapEndianShort(m_iButton6Y);
	m_iFloatingMap     = SwapEndianInt(m_iFloatingMap);
	m_iListText        = SwapEndianInt(m_iListText);
	m_iListBackground  = SwapEndianInt(m_iListBackground);
	m_iListHighlight   = SwapEndianInt(m_iListHighlight);
	m_iEscortHighlight = SwapEndianInt(m_iEscortHighlight);
	m_iButtonFontSize  = SwapEndianShort(m_iButtonFontSize);
	m_iLogoX           = SwapEndianShort(m_iLogoX);
	m_iLogoY           = SwapEndianShort(m_iLogoY);
	m_iRolloverX       = SwapEndianShort(m_iRolloverX);
	m_iRolloverY       = SwapEndianShort(m_iRolloverY);
	m_iSlide1X         = SwapEndianShort(m_iSlide1X);
	m_iSlide1Y         = SwapEndianShort(m_iSlide1Y);
	m_iSlide2X         = SwapEndianShort(m_iSlide2X);
	m_iSlide2Y         = SwapEndianShort(m_iSlide2Y);
	m_iSlide3X         = SwapEndianShort(m_iSlide3X);
	m_iSlide3Y         = SwapEndianShort(m_iSlide3Y);

	return 1;
}

int CColrResource::SaveToText(std::ostream & output)
{
	PrintHex32Field(output, (char *)&m_iButtonUp,   '\t');
	PrintHex32Field(output, (char *)&m_iButtonDown, '\t');
	PrintHex32Field(output, (char *)&m_iButtonGrey, '\t');

	PrintTextField(output, m_szMenuFont, '\t');

	output << m_iMenuFontSize << '\t';

	PrintHex32Field(output, (char *)&m_iMenuColor1, '\t');
	PrintHex32Field(output, (char *)&m_iMenuColor2, '\t');
	PrintHex32Field(output, (char *)&m_iGridBright, '\t');
	PrintHex32Field(output, (char *)&m_iGridDim,    '\t');

	output << m_iProgressBarX1   << '\t'
		   << m_iProgressBarY1   << '\t'
		   << m_iProgressBarX2   << '\t'
		   << m_iProgressBarY2   << '\t';

	PrintHex32Field(output, (char *)&m_iProgressBright,  '\t');
	PrintHex32Field(output, (char *)&m_iProgressDim,     '\t');
	PrintHex32Field(output, (char *)&m_iProgressOutline, '\t');

	output << m_iButton1X        << '\t'
		   << m_iButton1Y        << '\t'
		   << m_iButton2X        << '\t'
		   << m_iButton2Y        << '\t'
		   << m_iButton3X        << '\t'
		   << m_iButton3Y        << '\t'
		   << m_iButton4X        << '\t'
		   << m_iButton4Y        << '\t'
		   << m_iButton5X        << '\t'
		   << m_iButton5Y        << '\t'
		   << m_iButton6X        << '\t'
		   << m_iButton6Y        << '\t';

	PrintHex32Field(output, (char *)&m_iFloatingMap,     '\t');
	PrintHex32Field(output, (char *)&m_iListText,        '\t');
	PrintHex32Field(output, (char *)&m_iListBackground,  '\t');
	PrintHex32Field(output, (char *)&m_iListHighlight,   '\t');
	PrintHex32Field(output, (char *)&m_iEscortHighlight, '\t');

	PrintTextField(output, m_szButtonFont, '\t');

	output << m_iButtonFontSize  << '\t'
		   << m_iLogoX           << '\t'
		   << m_iLogoY           << '\t'
		   << m_iRolloverX       << '\t'
		   << m_iRolloverY       << '\t'
		   << m_iSlide1X         << '\t'
		   << m_iSlide1Y         << '\t'
		   << m_iSlide2X         << '\t'
		   << m_iSlide2Y         << '\t'
		   << m_iSlide3X         << '\t'
		   << m_iSlide3Y         << '\t';

	return 1;
}

int CColrResource::LoadFromText(std::istream & input)
{
	ReadHex32Field(input, (char *)&m_iButtonUp);
	ReadHex32Field(input, (char *)&m_iButtonDown);
	ReadHex32Field(input, (char *)&m_iButtonGrey);

	ReadTextField(input, m_szMenuFont, 64);

	input >> m_iMenuFontSize;

	ReadHex32Field(input, (char *)&m_iMenuColor1);
	ReadHex32Field(input, (char *)&m_iMenuColor2);
	ReadHex32Field(input, (char *)&m_iGridBright);
	ReadHex32Field(input, (char *)&m_iGridDim);

	input >> m_iProgressBarX1
		  >> m_iProgressBarY1
		  >> m_iProgressBarX2
		  >> m_iProgressBarY2;

	ReadHex32Field(input, (char *)&m_iProgressBright);
	ReadHex32Field(input, (char *)&m_iProgressDim);
	ReadHex32Field(input, (char *)&m_iProgressOutline);

	input >> m_iButton1X
		  >> m_iButton1Y
		  >> m_iButton2X
		  >> m_iButton2Y
		  >> m_iButton3X
		  >> m_iButton3Y
		  >> m_iButton4X
		  >> m_iButton4Y
		  >> m_iButton5X
		  >> m_iButton5Y
		  >> m_iButton6X
		  >> m_iButton6Y;

	ReadHex32Field(input, (char *)&m_iFloatingMap);
	ReadHex32Field(input, (char *)&m_iListText);
	ReadHex32Field(input, (char *)&m_iListBackground);
	ReadHex32Field(input, (char *)&m_iListHighlight);
	ReadHex32Field(input, (char *)&m_iEscortHighlight);

	ReadTextField(input, m_szButtonFont, 64);

	input >> m_iButtonFontSize
		  >> m_iLogoX
		  >> m_iLogoY
		  >> m_iRolloverX
		  >> m_iRolloverY
		  >> m_iSlide1X
		  >> m_iSlide1Y
		  >> m_iSlide2X
		  >> m_iSlide2Y
		  >> m_iSlide3X
		  >> m_iSlide3Y;

	input.ignore(1);

	return 1;
}

int CColrResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "colr ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_COLR_EDIT1, CCONTROL_TYPE_INT, IDS_STRING128);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_COLR_BUTTON2, CCONTROL_TYPE_COLOR, IDS_STRING129);
	m_controls[1].SetInt(m_iButtonUp);
	m_controls[2].Create(hwnd, IDC_EDIT_COLR_BUTTON3, CCONTROL_TYPE_COLOR, IDS_STRING130);
	m_controls[2].SetInt(m_iButtonDown);
	m_controls[3].Create(hwnd, IDC_EDIT_COLR_BUTTON4, CCONTROL_TYPE_COLOR, IDS_STRING131);
	m_controls[3].SetInt(m_iButtonGrey);
	m_controls[4].Create(hwnd, IDC_EDIT_COLR_EDIT5, CCONTROL_TYPE_STR64, IDS_STRING132);
	m_controls[4].SetString(m_szMenuFont);
	m_controls[5].Create(hwnd, IDC_EDIT_COLR_EDIT6, CCONTROL_TYPE_INT, IDS_STRING133);
	m_controls[5].SetInt(m_iMenuFontSize);
	m_controls[6].Create(hwnd, IDC_EDIT_COLR_BUTTON7, CCONTROL_TYPE_COLOR, IDS_STRING134);
	m_controls[6].SetInt(m_iMenuColor1);
	m_controls[7].Create(hwnd, IDC_EDIT_COLR_BUTTON8, CCONTROL_TYPE_COLOR, IDS_STRING135);
	m_controls[7].SetInt(m_iMenuColor2);
	m_controls[8].Create(hwnd, IDC_EDIT_COLR_BUTTON10, CCONTROL_TYPE_COLOR, IDS_STRING137);
	m_controls[8].SetInt(m_iGridBright);
	m_controls[9].Create(hwnd, IDC_EDIT_COLR_BUTTON9, CCONTROL_TYPE_COLOR, IDS_STRING136);
	m_controls[9].SetInt(m_iGridDim);
	m_controls[10].Create(hwnd, IDC_EDIT_COLR_EDIT11, CCONTROL_TYPE_INT, IDS_STRING138);
	m_controls[10].SetInt(m_iProgressBarX1);
	m_controls[11].Create(hwnd, IDC_EDIT_COLR_EDIT12, CCONTROL_TYPE_INT, IDS_STRING139);
	m_controls[11].SetInt(m_iProgressBarY1);
	m_controls[12].Create(hwnd, IDC_EDIT_COLR_EDIT13, CCONTROL_TYPE_INT, IDS_STRING140);
	m_controls[12].SetInt(m_iProgressBarX2);
	m_controls[13].Create(hwnd, IDC_EDIT_COLR_EDIT14, CCONTROL_TYPE_INT, IDS_STRING141);
	m_controls[13].SetInt(m_iProgressBarY2);
	m_controls[14].Create(hwnd, IDC_EDIT_COLR_BUTTON15, CCONTROL_TYPE_COLOR, IDS_STRING142);
	m_controls[14].SetInt(m_iProgressBright);
	m_controls[15].Create(hwnd, IDC_EDIT_COLR_BUTTON16, CCONTROL_TYPE_COLOR, IDS_STRING143);
	m_controls[15].SetInt(m_iProgressDim);
	m_controls[16].Create(hwnd, IDC_EDIT_COLR_BUTTON17, CCONTROL_TYPE_COLOR, IDS_STRING144);
	m_controls[16].SetInt(m_iProgressOutline);
	m_controls[17].Create(hwnd, IDC_EDIT_COLR_EDIT18, CCONTROL_TYPE_INT, IDS_STRING145);
	m_controls[17].SetInt(m_iButton1X);
	m_controls[18].Create(hwnd, IDC_EDIT_COLR_EDIT19, CCONTROL_TYPE_INT, IDS_STRING146);
	m_controls[18].SetInt(m_iButton1Y);
	m_controls[19].Create(hwnd, IDC_EDIT_COLR_EDIT20, CCONTROL_TYPE_INT, IDS_STRING147);
	m_controls[19].SetInt(m_iButton2X);
	m_controls[20].Create(hwnd, IDC_EDIT_COLR_EDIT21, CCONTROL_TYPE_INT, IDS_STRING148);
	m_controls[20].SetInt(m_iButton2Y);
	m_controls[21].Create(hwnd, IDC_EDIT_COLR_EDIT22, CCONTROL_TYPE_INT, IDS_STRING149);
	m_controls[21].SetInt(m_iButton3X);
	m_controls[22].Create(hwnd, IDC_EDIT_COLR_EDIT23, CCONTROL_TYPE_INT, IDS_STRING150);
	m_controls[22].SetInt(m_iButton3Y);
	m_controls[23].Create(hwnd, IDC_EDIT_COLR_EDIT24, CCONTROL_TYPE_INT, IDS_STRING151);
	m_controls[23].SetInt(m_iButton4X);
	m_controls[24].Create(hwnd, IDC_EDIT_COLR_EDIT25, CCONTROL_TYPE_INT, IDS_STRING152);
	m_controls[24].SetInt(m_iButton4Y);
	m_controls[25].Create(hwnd, IDC_EDIT_COLR_EDIT26, CCONTROL_TYPE_INT, IDS_STRING153);
	m_controls[25].SetInt(m_iButton5X);
	m_controls[26].Create(hwnd, IDC_EDIT_COLR_EDIT27, CCONTROL_TYPE_INT, IDS_STRING154);
	m_controls[26].SetInt(m_iButton5Y);
	m_controls[27].Create(hwnd, IDC_EDIT_COLR_EDIT28, CCONTROL_TYPE_INT, IDS_STRING155);
	m_controls[27].SetInt(m_iButton6X);
	m_controls[28].Create(hwnd, IDC_EDIT_COLR_EDIT29, CCONTROL_TYPE_INT, IDS_STRING156);
	m_controls[28].SetInt(m_iButton6Y);
	m_controls[29].Create(hwnd, IDC_EDIT_COLR_BUTTON30, CCONTROL_TYPE_COLOR, IDS_STRING157);
	m_controls[29].SetInt(m_iFloatingMap);
	m_controls[30].Create(hwnd, IDC_EDIT_COLR_BUTTON31, CCONTROL_TYPE_COLOR, IDS_STRING158);
	m_controls[30].SetInt(m_iListText);
	m_controls[31].Create(hwnd, IDC_EDIT_COLR_BUTTON32, CCONTROL_TYPE_COLOR, IDS_STRING159);
	m_controls[31].SetInt(m_iListBackground);
	m_controls[32].Create(hwnd, IDC_EDIT_COLR_BUTTON33, CCONTROL_TYPE_COLOR, IDS_STRING160);
	m_controls[32].SetInt(m_iListHighlight);
	m_controls[33].Create(hwnd, IDC_EDIT_COLR_BUTTON34, CCONTROL_TYPE_COLOR, IDS_STRING161);
	m_controls[33].SetInt(m_iEscortHighlight);
	m_controls[34].Create(hwnd, IDC_EDIT_COLR_EDIT35, CCONTROL_TYPE_STR64, IDS_STRING162);
	m_controls[34].SetString(m_szButtonFont);
	m_controls[35].Create(hwnd, IDC_EDIT_COLR_EDIT36, CCONTROL_TYPE_INT, IDS_STRING163);
	m_controls[35].SetInt(m_iButtonFontSize);
	m_controls[36].Create(hwnd, IDC_EDIT_COLR_EDIT37, CCONTROL_TYPE_INT, IDS_STRING164);
	m_controls[36].SetInt(m_iLogoX);
	m_controls[37].Create(hwnd, IDC_EDIT_COLR_EDIT38, CCONTROL_TYPE_INT, IDS_STRING165);
	m_controls[37].SetInt(m_iLogoY);
	m_controls[38].Create(hwnd, IDC_EDIT_COLR_EDIT39, CCONTROL_TYPE_INT, IDS_STRING166);
	m_controls[38].SetInt(m_iRolloverX);
	m_controls[39].Create(hwnd, IDC_EDIT_COLR_EDIT40, CCONTROL_TYPE_INT, IDS_STRING167);
	m_controls[39].SetInt(m_iRolloverY);
	m_controls[40].Create(hwnd, IDC_EDIT_COLR_EDIT41, CCONTROL_TYPE_INT, IDS_STRING168);
	m_controls[40].SetInt(m_iSlide1X);
	m_controls[41].Create(hwnd, IDC_EDIT_COLR_EDIT42, CCONTROL_TYPE_INT, IDS_STRING169);
	m_controls[41].SetInt(m_iSlide1Y);
	m_controls[42].Create(hwnd, IDC_EDIT_COLR_EDIT43, CCONTROL_TYPE_INT, IDS_STRING170);
	m_controls[42].SetInt(m_iSlide2X);
	m_controls[43].Create(hwnd, IDC_EDIT_COLR_EDIT44, CCONTROL_TYPE_INT, IDS_STRING171);
	m_controls[43].SetInt(m_iSlide2Y);
	m_controls[44].Create(hwnd, IDC_EDIT_COLR_EDIT45, CCONTROL_TYPE_INT, IDS_STRING172);
	m_controls[44].SetInt(m_iSlide3X);
	m_controls[45].Create(hwnd, IDC_EDIT_COLR_EDIT46, CCONTROL_TYPE_INT, IDS_STRING173);
	m_controls[45].SetInt(m_iSlide3Y);
	m_controls[46].Create(hwnd, IDC_EDIT_COLR_EDIT2, CCONTROL_TYPE_STR256, IDS_STRING174);
	m_controls[46].SetString(m_szName);

	return 1;
}

int CColrResource::CloseAndSave(void)
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

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[46].GetString()) != 0))
		iIDOrNameChanged = 1;

	m_iID         = m_controls[0].GetInt();
	m_iButtonUp   = m_controls[1].GetInt();
	m_iButtonDown = m_controls[2].GetInt();
	m_iButtonGrey = m_controls[3].GetInt();

	strcpy(m_szMenuFont, m_controls[4].GetString());

	m_iMenuFontSize    = m_controls[5].GetInt();
	m_iMenuColor1      = m_controls[6].GetInt();
	m_iMenuColor2      = m_controls[7].GetInt();
	m_iGridBright      = m_controls[8].GetInt();
	m_iGridDim         = m_controls[9].GetInt();
	m_iProgressBarX1   = m_controls[10].GetInt();
	m_iProgressBarY1   = m_controls[11].GetInt();
	m_iProgressBarX2   = m_controls[12].GetInt();
	m_iProgressBarY2   = m_controls[13].GetInt();
	m_iProgressBright  = m_controls[14].GetInt();
	m_iProgressDim     = m_controls[15].GetInt();
	m_iProgressOutline = m_controls[16].GetInt();
	m_iButton1X        = m_controls[17].GetInt();
	m_iButton1Y        = m_controls[18].GetInt();
	m_iButton2X        = m_controls[19].GetInt();
	m_iButton2Y        = m_controls[20].GetInt();
	m_iButton3X        = m_controls[21].GetInt();
	m_iButton3Y        = m_controls[22].GetInt();
	m_iButton4X        = m_controls[23].GetInt();
	m_iButton4Y        = m_controls[24].GetInt();
	m_iButton5X        = m_controls[25].GetInt();
	m_iButton5Y        = m_controls[26].GetInt();
	m_iButton6X        = m_controls[27].GetInt();
	m_iButton6Y        = m_controls[28].GetInt();
	m_iFloatingMap     = m_controls[29].GetInt();
	m_iListText        = m_controls[30].GetInt();
	m_iListBackground  = m_controls[31].GetInt();
	m_iListHighlight   = m_controls[32].GetInt();
	m_iEscortHighlight = m_controls[33].GetInt();

	strcpy(m_szButtonFont, m_controls[34].GetString());

	m_iButtonFontSize = m_controls[35].GetInt();
	m_iLogoX          = m_controls[36].GetInt();
	m_iLogoY          = m_controls[37].GetInt();
	m_iRolloverX      = m_controls[38].GetInt();
	m_iRolloverY      = m_controls[39].GetInt();
	m_iSlide1X        = m_controls[40].GetInt();
	m_iSlide1Y        = m_controls[41].GetInt();
	m_iSlide2X        = m_controls[42].GetInt();
	m_iSlide2Y        = m_controls[43].GetInt();
	m_iSlide3X        = m_controls[44].GetInt();
	m_iSlide3Y        = m_controls[45].GetInt();

	strcpy(m_szName, m_controls[46].GetString());

	int i;

	for(i = 0; i < NUM_COLR_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CColrResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_COLR_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CColrResource::ColrDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CColrResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CColrResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_COLR_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_COLR_OK)
			{
				pResource->CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_COLR_CONTROLS; i++)
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
