// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CIntfResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CIntfResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CIntfResource::CIntfResource(void)
{
	m_iBrightText = 0x00000000;
	m_iDimText    = 0x00000000;

	m_iRadarX1 = 0;
	m_iRadarY1 = 0;
	m_iRadarX2 = 0;
	m_iRadarY2 = 0;

	m_iBrightRadar = 0x00000000;
	m_iDimRadar    = 0x00000000;

	m_iShieldX1 = 0;
	m_iShieldY1 = 0;
	m_iShieldX2 = 0;
	m_iShieldY2 = 0;

	m_iShieldColor = 0x00000000;

	m_iArmorX1 = 0;
	m_iArmorY1 = 0;
	m_iArmorX2 = 0;
	m_iArmorY2 = 0;

	m_iArmorColor = 0x00000000;

	m_iFuelX1 = 0;
	m_iFuelY1 = 0;
	m_iFuelX2 = 0;
	m_iFuelY2 = 0;

	m_iFuelFull    = 0x00000000;
	m_iFuelPartial = 0x00000000;

	m_iNavigationX1 = 0;
	m_iNavigationY1 = 0;
	m_iNavigationX2 = 0;
	m_iNavigationY2 = 0;

	m_iWeaponX1 = 0;
	m_iWeaponY1 = 0;
	m_iWeaponX2 = 0;
	m_iWeaponY2 = 0;

	m_iTargetX1 = 0;
	m_iTargetY1 = 0;
	m_iTargetX2 = 0;
	m_iTargetY2 = 0;

	m_iCargoX1 = 0;
	m_iCargoY1 = 0;
	m_iCargoX2 = 0;
	m_iCargoY2 = 0;

	memset(m_szStatusFont, 0, 64 * sizeof(char));

	m_iStatusFontSize   = 0;
	m_iSubtitleFontSize = 0;

	m_iBackground = 128;
}

CIntfResource::~CIntfResource(void)
{

}

int CIntfResource::GetType(void)
{
	return CNR_TYPE_INTF;
}

int CIntfResource::GetSize(void)
{
	return 166;
}

int CIntfResource::GetDialogID(void)
{
	return IDD_EDIT_INTF;
}

DLGPROCNOCALLBACK CIntfResource::GetDialogProc(void)
{
	return IntfDlgProc;
}

int CIntfResource::GetNumFields(void)
{
	return NUM_INTF_FIELDS;
}

const std::string * CIntfResource::GetFieldNames(void)
{
	return g_szIntfFields;
}

int CIntfResource::Save(char *pOutput)
{
	SwapEndians();

	*(UINT  *)pOutput = m_iBrightText;       pOutput += sizeof(UINT);
	*(UINT  *)pOutput = m_iDimText;          pOutput += sizeof(UINT);
	*(short *)pOutput = m_iRadarY1;          pOutput += sizeof(short);
	*(short *)pOutput = m_iRadarX1;          pOutput += sizeof(short);
	*(short *)pOutput = m_iRadarY2;          pOutput += sizeof(short);
	*(short *)pOutput = m_iRadarX2;          pOutput += sizeof(short);
	*(UINT  *)pOutput = m_iBrightRadar;      pOutput += sizeof(UINT);
	*(UINT  *)pOutput = m_iDimRadar;         pOutput += sizeof(UINT);
	*(short *)pOutput = m_iShieldY1;         pOutput += sizeof(short);
	*(short *)pOutput = m_iShieldX1;         pOutput += sizeof(short);
	*(short *)pOutput = m_iShieldY2;         pOutput += sizeof(short);
	*(short *)pOutput = m_iShieldX2;         pOutput += sizeof(short);
	*(UINT  *)pOutput = m_iShieldColor;      pOutput += sizeof(UINT);
	*(short *)pOutput = m_iArmorY1;          pOutput += sizeof(short);
	*(short *)pOutput = m_iArmorX1;          pOutput += sizeof(short);
	*(short *)pOutput = m_iArmorY2;          pOutput += sizeof(short);
	*(short *)pOutput = m_iArmorX2;          pOutput += sizeof(short);
	*(UINT  *)pOutput = m_iArmorColor;       pOutput += sizeof(UINT);
	*(short *)pOutput = m_iFuelY1;           pOutput += sizeof(short);
	*(short *)pOutput = m_iFuelX1;           pOutput += sizeof(short);
	*(short *)pOutput = m_iFuelY2;           pOutput += sizeof(short);
	*(short *)pOutput = m_iFuelX2;           pOutput += sizeof(short);
	*(UINT  *)pOutput = m_iFuelFull;         pOutput += sizeof(UINT);
	*(UINT  *)pOutput = m_iFuelPartial;      pOutput += sizeof(UINT);
	*(short *)pOutput = m_iNavigationY1;     pOutput += sizeof(short);
	*(short *)pOutput = m_iNavigationX1;     pOutput += sizeof(short);
	*(short *)pOutput = m_iNavigationY2;     pOutput += sizeof(short);
	*(short *)pOutput = m_iNavigationX2;     pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponY1;         pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponX1;         pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponY2;         pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponX2;         pOutput += sizeof(short);
	*(short *)pOutput = m_iTargetY1;         pOutput += sizeof(short);
	*(short *)pOutput = m_iTargetX1;         pOutput += sizeof(short);
	*(short *)pOutput = m_iTargetY2;         pOutput += sizeof(short);
	*(short *)pOutput = m_iTargetX2;         pOutput += sizeof(short);
	*(short *)pOutput = m_iCargoY1;          pOutput += sizeof(short);
	*(short *)pOutput = m_iCargoX1;          pOutput += sizeof(short);
	*(short *)pOutput = m_iCargoY2;          pOutput += sizeof(short);
	*(short *)pOutput = m_iCargoX2;          pOutput += sizeof(short);

	memcpy(pOutput, m_szStatusFont, 64 * sizeof(char)); pOutput += 64 * sizeof(char);

	*(short *)pOutput = m_iStatusFontSize;   pOutput += sizeof(short);
	*(short *)pOutput = m_iSubtitleFontSize; pOutput += sizeof(short);
	*(short *)pOutput = m_iBackground;       pOutput += sizeof(short);

	SwapEndians();

	return 1;
}

int CIntfResource::Load(char *pInput, int iSize)
{
	m_iBrightText       = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iDimText          = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iRadarY1          = *(short *)pInput; pInput += sizeof(short);
	m_iRadarX1          = *(short *)pInput; pInput += sizeof(short);
	m_iRadarY2          = *(short *)pInput; pInput += sizeof(short);
	m_iRadarX2          = *(short *)pInput; pInput += sizeof(short);
	m_iBrightRadar      = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iDimRadar         = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iShieldY1         = *(short *)pInput; pInput += sizeof(short);
	m_iShieldX1         = *(short *)pInput; pInput += sizeof(short);
	m_iShieldY2         = *(short *)pInput; pInput += sizeof(short);
	m_iShieldX2         = *(short *)pInput; pInput += sizeof(short);
	m_iShieldColor      = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iArmorY1          = *(short *)pInput; pInput += sizeof(short);
	m_iArmorX1          = *(short *)pInput; pInput += sizeof(short);
	m_iArmorY2          = *(short *)pInput; pInput += sizeof(short);
	m_iArmorX2          = *(short *)pInput; pInput += sizeof(short);
	m_iArmorColor       = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iFuelY1           = *(short *)pInput; pInput += sizeof(short);
	m_iFuelX1           = *(short *)pInput; pInput += sizeof(short);
	m_iFuelY2           = *(short *)pInput; pInput += sizeof(short);
	m_iFuelX2           = *(short *)pInput; pInput += sizeof(short);
	m_iFuelFull         = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iFuelPartial      = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iNavigationY1     = *(short *)pInput; pInput += sizeof(short);
	m_iNavigationX1     = *(short *)pInput; pInput += sizeof(short);
	m_iNavigationY2     = *(short *)pInput; pInput += sizeof(short);
	m_iNavigationX2     = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponY1         = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponX1         = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponY2         = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponX2         = *(short *)pInput; pInput += sizeof(short);
	m_iTargetY1         = *(short *)pInput; pInput += sizeof(short);
	m_iTargetX1         = *(short *)pInput; pInput += sizeof(short);
	m_iTargetY2         = *(short *)pInput; pInput += sizeof(short);
	m_iTargetX2         = *(short *)pInput; pInput += sizeof(short);
	m_iCargoY1          = *(short *)pInput; pInput += sizeof(short);
	m_iCargoX1          = *(short *)pInput; pInput += sizeof(short);
	m_iCargoY2          = *(short *)pInput; pInput += sizeof(short);
	m_iCargoX2          = *(short *)pInput; pInput += sizeof(short);

	memcpy(m_szStatusFont, pInput, 64 * sizeof(char)); pInput += 64 * sizeof(char);

	m_iStatusFontSize   = *(short *)pInput; pInput += sizeof(short);
	m_iSubtitleFontSize = *(short *)pInput; pInput += sizeof(short);
	m_iBackground       = *(short *)pInput; pInput += sizeof(short);

	SwapEndians();

	return 1;
}

int CIntfResource::SwapEndians(void)
{
	m_iBrightText       = SwapEndianInt(m_iBrightText);
	m_iDimText          = SwapEndianInt(m_iDimText);
	m_iRadarY1          = SwapEndianShort(m_iRadarY1);
	m_iRadarX1          = SwapEndianShort(m_iRadarX1);
	m_iRadarY2          = SwapEndianShort(m_iRadarY2);
	m_iRadarX2          = SwapEndianShort(m_iRadarX2);
	m_iBrightRadar      = SwapEndianInt(m_iBrightRadar);
	m_iDimRadar         = SwapEndianInt(m_iDimRadar);
	m_iShieldY1         = SwapEndianShort(m_iShieldY1);
	m_iShieldX1         = SwapEndianShort(m_iShieldX1);
	m_iShieldY2         = SwapEndianShort(m_iShieldY2);
	m_iShieldX2         = SwapEndianShort(m_iShieldX2);
	m_iShieldColor      = SwapEndianInt(m_iShieldColor);
	m_iArmorY1          = SwapEndianShort(m_iArmorY1);
	m_iArmorX1          = SwapEndianShort(m_iArmorX1);
	m_iArmorY2          = SwapEndianShort(m_iArmorY2);
	m_iArmorX2          = SwapEndianShort(m_iArmorX2);
	m_iArmorColor       = SwapEndianInt(m_iArmorColor);
	m_iFuelY1           = SwapEndianShort(m_iFuelY1);
	m_iFuelX1           = SwapEndianShort(m_iFuelX1);
	m_iFuelY2           = SwapEndianShort(m_iFuelY2);
	m_iFuelX2           = SwapEndianShort(m_iFuelX2);
	m_iFuelFull         = SwapEndianInt(m_iFuelFull);
	m_iFuelPartial      = SwapEndianInt(m_iFuelPartial);
	m_iNavigationY1     = SwapEndianShort(m_iNavigationY1);
	m_iNavigationX1     = SwapEndianShort(m_iNavigationX1);
	m_iNavigationY2     = SwapEndianShort(m_iNavigationY2);
	m_iNavigationX2     = SwapEndianShort(m_iNavigationX2);
	m_iWeaponY1         = SwapEndianShort(m_iWeaponY1);
	m_iWeaponX1         = SwapEndianShort(m_iWeaponX1);
	m_iWeaponY2         = SwapEndianShort(m_iWeaponY2);
	m_iWeaponX2         = SwapEndianShort(m_iWeaponX2);
	m_iTargetY1         = SwapEndianShort(m_iTargetY1);
	m_iTargetX1         = SwapEndianShort(m_iTargetX1);
	m_iTargetY2         = SwapEndianShort(m_iTargetY2);
	m_iTargetX2         = SwapEndianShort(m_iTargetX2);
	m_iCargoY1          = SwapEndianShort(m_iCargoY1);
	m_iCargoX1          = SwapEndianShort(m_iCargoX1);
	m_iCargoY2          = SwapEndianShort(m_iCargoY2);
	m_iCargoX2          = SwapEndianShort(m_iCargoX2);
	m_iStatusFontSize   = SwapEndianShort(m_iStatusFontSize);
	m_iSubtitleFontSize = SwapEndianShort(m_iSubtitleFontSize);
	m_iBackground       = SwapEndianShort(m_iBackground);

	return 1;
}

int CIntfResource::SaveToText(std::ostream & output)
{
	PrintHex32Field(output, (char *)&m_iBrightText, '\t');
	PrintHex32Field(output, (char *)&m_iDimText,    '\t');

	output << m_iRadarX1          << '\t'
		   << m_iRadarY1          << '\t'
		   << m_iRadarX2          << '\t'
		   << m_iRadarY2          << '\t';

	PrintHex32Field(output, (char *)&m_iBrightRadar, '\t');
	PrintHex32Field(output, (char *)&m_iDimRadar,    '\t');

	output << m_iShieldX1         << '\t'
		   << m_iShieldY1         << '\t'
		   << m_iShieldX2         << '\t'
		   << m_iShieldY2         << '\t';

	PrintHex32Field(output, (char *)&m_iShieldColor, '\t');

	output << m_iArmorX1          << '\t'
		   << m_iArmorY1          << '\t'
		   << m_iArmorX2          << '\t'
		   << m_iArmorY2          << '\t';

	PrintHex32Field(output, (char *)&m_iArmorColor, '\t');

	output << m_iFuelX1           << '\t'
		   << m_iFuelY1           << '\t'
		   << m_iFuelX2           << '\t'
		   << m_iFuelY2           << '\t';

	PrintHex32Field(output, (char *)&m_iFuelFull,    '\t');
	PrintHex32Field(output, (char *)&m_iFuelPartial, '\t');

	output << m_iNavigationX1     << '\t'
		   << m_iNavigationY1     << '\t'
		   << m_iNavigationX2     << '\t'
		   << m_iNavigationY2     << '\t'
		   << m_iWeaponX1         << '\t'
		   << m_iWeaponY1         << '\t'
		   << m_iWeaponX2         << '\t'
		   << m_iWeaponY2         << '\t'
		   << m_iTargetX1         << '\t'
		   << m_iTargetY1         << '\t'
		   << m_iTargetX2         << '\t'
		   << m_iTargetY2         << '\t'
		   << m_iCargoX1          << '\t'
		   << m_iCargoY1          << '\t'
		   << m_iCargoX2          << '\t'
		   << m_iCargoY2          << '\t';

	PrintTextField(output, m_szStatusFont, '\t');

	output << m_iStatusFontSize   << '\t'
		   << m_iSubtitleFontSize << '\t'
		   << m_iBackground       << '\t';

	return 1;
}

int CIntfResource::LoadFromText(std::istream & input)
{
	ReadHex32Field(input, (char *)&m_iBrightText);
	ReadHex32Field(input, (char *)&m_iDimText);

	input >> m_iRadarX1
		  >> m_iRadarY1
		  >> m_iRadarX2
		  >> m_iRadarY2;

	ReadHex32Field(input, (char *)&m_iBrightRadar);
	ReadHex32Field(input, (char *)&m_iDimRadar);

	input >> m_iShieldX1
		  >> m_iShieldY1
		  >> m_iShieldX2
		  >> m_iShieldY2;

	ReadHex32Field(input, (char *)&m_iShieldColor);

	input >> m_iArmorX1
		  >> m_iArmorY1
		  >> m_iArmorX2
		  >> m_iArmorY2;

	ReadHex32Field(input, (char *)&m_iArmorColor);

	input >> m_iFuelX1
		  >> m_iFuelY1
		  >> m_iFuelX2
		  >> m_iFuelY2;

	ReadHex32Field(input, (char *)&m_iFuelFull);
	ReadHex32Field(input, (char *)&m_iFuelPartial);

	input >> m_iNavigationX1
		  >> m_iNavigationY1
		  >> m_iNavigationX2
		  >> m_iNavigationY2
		  >> m_iWeaponX1
		  >> m_iWeaponY1
		  >> m_iWeaponX2
		  >> m_iWeaponY2
		  >> m_iTargetX1
		  >> m_iTargetY1
		  >> m_iTargetX2
		  >> m_iTargetY2
		  >> m_iCargoX1
		  >> m_iCargoY1
		  >> m_iCargoX2
		  >> m_iCargoY2;

	input.ignore(1);

	ReadTextField(input, m_szStatusFont, 64);

	input >> m_iStatusFontSize
		  >> m_iSubtitleFontSize
		  >> m_iBackground;

	input.ignore(1);

	return 1;
}

int CIntfResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "intf ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_INTF_EDIT1, CCONTROL_TYPE_INT, IDS_STRING336);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_INTF_BUTTON2, CCONTROL_TYPE_COLOR, IDS_STRING337);
	m_controls[1].SetInt(m_iBrightText);
	m_controls[2].Create(hwnd, IDC_EDIT_INTF_BUTTON3, CCONTROL_TYPE_COLOR, IDS_STRING338);
	m_controls[2].SetInt(m_iDimText);
	m_controls[3].Create(hwnd, IDC_EDIT_INTF_EDIT4, CCONTROL_TYPE_INT, IDS_STRING339);
	m_controls[3].SetInt(m_iRadarX1);
	m_controls[4].Create(hwnd, IDC_EDIT_INTF_EDIT5, CCONTROL_TYPE_INT, IDS_STRING340);
	m_controls[4].SetInt(m_iRadarY1);
	m_controls[5].Create(hwnd, IDC_EDIT_INTF_EDIT6, CCONTROL_TYPE_INT, IDS_STRING341);
	m_controls[5].SetInt(m_iRadarX2);
	m_controls[6].Create(hwnd, IDC_EDIT_INTF_EDIT7, CCONTROL_TYPE_INT, IDS_STRING342);
	m_controls[6].SetInt(m_iRadarY2);
	m_controls[7].Create(hwnd, IDC_EDIT_INTF_BUTTON8, CCONTROL_TYPE_COLOR, IDS_STRING343);
	m_controls[7].SetInt(m_iBrightRadar);
	m_controls[8].Create(hwnd, IDC_EDIT_INTF_BUTTON9, CCONTROL_TYPE_COLOR, IDS_STRING344);
	m_controls[8].SetInt(m_iDimRadar);
	m_controls[9].Create(hwnd, IDC_EDIT_INTF_EDIT10, CCONTROL_TYPE_INT, IDS_STRING345);
	m_controls[9].SetInt(m_iShieldX1);
	m_controls[10].Create(hwnd, IDC_EDIT_INTF_EDIT11, CCONTROL_TYPE_INT, IDS_STRING346);
	m_controls[10].SetInt(m_iShieldY1);
	m_controls[11].Create(hwnd, IDC_EDIT_INTF_EDIT12, CCONTROL_TYPE_INT, IDS_STRING347);
	m_controls[11].SetInt(m_iShieldX2);
	m_controls[12].Create(hwnd, IDC_EDIT_INTF_EDIT13, CCONTROL_TYPE_INT, IDS_STRING348);
	m_controls[12].SetInt(m_iShieldY2);
	m_controls[13].Create(hwnd, IDC_EDIT_INTF_BUTTON14, CCONTROL_TYPE_COLOR, IDS_STRING349);
	m_controls[13].SetInt(m_iShieldColor);
	m_controls[14].Create(hwnd, IDC_EDIT_INTF_EDIT15, CCONTROL_TYPE_INT, IDS_STRING350);
	m_controls[14].SetInt(m_iArmorX1);
	m_controls[15].Create(hwnd, IDC_EDIT_INTF_EDIT16, CCONTROL_TYPE_INT, IDS_STRING351);
	m_controls[15].SetInt(m_iArmorY1);
	m_controls[16].Create(hwnd, IDC_EDIT_INTF_EDIT17, CCONTROL_TYPE_INT, IDS_STRING352);
	m_controls[16].SetInt(m_iArmorX2);
	m_controls[17].Create(hwnd, IDC_EDIT_INTF_EDIT18, CCONTROL_TYPE_INT, IDS_STRING353);
	m_controls[17].SetInt(m_iArmorY2);
	m_controls[18].Create(hwnd, IDC_EDIT_INTF_BUTTON19, CCONTROL_TYPE_COLOR, IDS_STRING354);
	m_controls[18].SetInt(m_iArmorColor);
	m_controls[19].Create(hwnd, IDC_EDIT_INTF_EDIT20, CCONTROL_TYPE_INT, IDS_STRING355);
	m_controls[19].SetInt(m_iFuelX1);
	m_controls[20].Create(hwnd, IDC_EDIT_INTF_EDIT21, CCONTROL_TYPE_INT, IDS_STRING356);
	m_controls[20].SetInt(m_iFuelY1);
	m_controls[21].Create(hwnd, IDC_EDIT_INTF_EDIT22, CCONTROL_TYPE_INT, IDS_STRING357);
	m_controls[21].SetInt(m_iFuelX2);
	m_controls[22].Create(hwnd, IDC_EDIT_INTF_EDIT23, CCONTROL_TYPE_INT, IDS_STRING358);
	m_controls[22].SetInt(m_iFuelY2);
	m_controls[23].Create(hwnd, IDC_EDIT_INTF_BUTTON24, CCONTROL_TYPE_COLOR, IDS_STRING359);
	m_controls[23].SetInt(m_iFuelFull);
	m_controls[24].Create(hwnd, IDC_EDIT_INTF_BUTTON25, CCONTROL_TYPE_COLOR, IDS_STRING360);
	m_controls[24].SetInt(m_iFuelPartial);
	m_controls[25].Create(hwnd, IDC_EDIT_INTF_EDIT26, CCONTROL_TYPE_INT, IDS_STRING361);
	m_controls[25].SetInt(m_iNavigationX1);
	m_controls[26].Create(hwnd, IDC_EDIT_INTF_EDIT27, CCONTROL_TYPE_INT, IDS_STRING362);
	m_controls[26].SetInt(m_iNavigationY1);
	m_controls[27].Create(hwnd, IDC_EDIT_INTF_EDIT28, CCONTROL_TYPE_INT, IDS_STRING363);
	m_controls[27].SetInt(m_iNavigationX2);
	m_controls[28].Create(hwnd, IDC_EDIT_INTF_EDIT29, CCONTROL_TYPE_INT, IDS_STRING364);
	m_controls[28].SetInt(m_iNavigationY2);
	m_controls[29].Create(hwnd, IDC_EDIT_INTF_EDIT30, CCONTROL_TYPE_INT, IDS_STRING365);
	m_controls[29].SetInt(m_iWeaponX1);
	m_controls[30].Create(hwnd, IDC_EDIT_INTF_EDIT31, CCONTROL_TYPE_INT, IDS_STRING366);
	m_controls[30].SetInt(m_iWeaponY1);
	m_controls[31].Create(hwnd, IDC_EDIT_INTF_EDIT32, CCONTROL_TYPE_INT, IDS_STRING367);
	m_controls[31].SetInt(m_iWeaponX2);
	m_controls[32].Create(hwnd, IDC_EDIT_INTF_EDIT33, CCONTROL_TYPE_INT, IDS_STRING368);
	m_controls[32].SetInt(m_iWeaponY2);
	m_controls[33].Create(hwnd, IDC_EDIT_INTF_EDIT34, CCONTROL_TYPE_INT, IDS_STRING369);
	m_controls[33].SetInt(m_iTargetX1);
	m_controls[34].Create(hwnd, IDC_EDIT_INTF_EDIT35, CCONTROL_TYPE_INT, IDS_STRING370);
	m_controls[34].SetInt(m_iTargetY1);
	m_controls[35].Create(hwnd, IDC_EDIT_INTF_EDIT36, CCONTROL_TYPE_INT, IDS_STRING371);
	m_controls[35].SetInt(m_iTargetX2);
	m_controls[36].Create(hwnd, IDC_EDIT_INTF_EDIT37, CCONTROL_TYPE_INT, IDS_STRING372);
	m_controls[36].SetInt(m_iTargetY2);
	m_controls[37].Create(hwnd, IDC_EDIT_INTF_EDIT38, CCONTROL_TYPE_INT, IDS_STRING373);
	m_controls[37].SetInt(m_iCargoX1);
	m_controls[38].Create(hwnd, IDC_EDIT_INTF_EDIT39, CCONTROL_TYPE_INT, IDS_STRING374);
	m_controls[38].SetInt(m_iCargoY1);
	m_controls[39].Create(hwnd, IDC_EDIT_INTF_EDIT40, CCONTROL_TYPE_INT, IDS_STRING375);
	m_controls[39].SetInt(m_iCargoX2);
	m_controls[40].Create(hwnd, IDC_EDIT_INTF_EDIT41, CCONTROL_TYPE_INT, IDS_STRING376);
	m_controls[40].SetInt(m_iCargoY2);
	m_controls[41].Create(hwnd, IDC_EDIT_INTF_EDIT42, CCONTROL_TYPE_STR64, IDS_STRING377);
	m_controls[41].SetString(m_szStatusFont);
	m_controls[42].Create(hwnd, IDC_EDIT_INTF_EDIT43, CCONTROL_TYPE_INT, IDS_STRING378);
	m_controls[42].SetInt(m_iStatusFontSize);
	m_controls[43].Create(hwnd, IDC_EDIT_INTF_EDIT44, CCONTROL_TYPE_INT, IDS_STRING379);
	m_controls[43].SetInt(m_iSubtitleFontSize);
	m_controls[44].Create(hwnd, IDC_EDIT_INTF_EDIT45, CCONTROL_TYPE_INT, IDS_STRING380);
	m_controls[44].SetInt(m_iBackground);
	m_controls[45].Create(hwnd, IDC_EDIT_INTF_EDIT2, CCONTROL_TYPE_STR256, IDS_STRING381);
	m_controls[45].SetString(m_szName);

	return 1;
}

int CIntfResource::CloseAndSave(void)
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

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[45].GetString()) != 0))
		iIDOrNameChanged = 1;

	m_iID         = m_controls[0].GetInt();

	m_iBrightText = m_controls[1].GetInt();
	m_iDimText    = m_controls[2].GetInt();

	m_iRadarX1 = m_controls[3].GetInt();
	m_iRadarY1 = m_controls[4].GetInt();
	m_iRadarX2 = m_controls[5].GetInt();
	m_iRadarY2 = m_controls[6].GetInt();

	m_iBrightRadar = m_controls[7].GetInt();
	m_iDimRadar    = m_controls[8].GetInt();

	m_iShieldX1 = m_controls[9].GetInt();
	m_iShieldY1 = m_controls[10].GetInt();
	m_iShieldX2 = m_controls[11].GetInt();
	m_iShieldY2 = m_controls[12].GetInt();

	m_iShieldColor = m_controls[13].GetInt();

	m_iArmorX1 = m_controls[14].GetInt();
	m_iArmorY1 = m_controls[15].GetInt();
	m_iArmorX2 = m_controls[16].GetInt();
	m_iArmorY2 = m_controls[17].GetInt();

	m_iArmorColor = m_controls[18].GetInt();

	m_iFuelX1 = m_controls[19].GetInt();
	m_iFuelY1 = m_controls[20].GetInt();
	m_iFuelX2 = m_controls[21].GetInt();
	m_iFuelY2 = m_controls[22].GetInt();

	m_iFuelFull    = m_controls[23].GetInt();
	m_iFuelPartial = m_controls[24].GetInt();

	m_iNavigationX1 = m_controls[25].GetInt();
	m_iNavigationY1 = m_controls[26].GetInt();
	m_iNavigationX2 = m_controls[27].GetInt();
	m_iNavigationY2 = m_controls[28].GetInt();

	m_iWeaponX1 = m_controls[29].GetInt();
	m_iWeaponY1 = m_controls[30].GetInt();
	m_iWeaponX2 = m_controls[31].GetInt();
	m_iWeaponY2 = m_controls[32].GetInt();

	m_iTargetX1 = m_controls[33].GetInt();
	m_iTargetY1 = m_controls[34].GetInt();
	m_iTargetX2 = m_controls[35].GetInt();
	m_iTargetY2 = m_controls[36].GetInt();

	m_iCargoX1 = m_controls[37].GetInt();
	m_iCargoY1 = m_controls[38].GetInt();
	m_iCargoX2 = m_controls[39].GetInt();
	m_iCargoY2 = m_controls[40].GetInt();

	strcpy(m_szStatusFont, m_controls[41].GetString());

	m_iStatusFontSize   = m_controls[42].GetInt();
	m_iSubtitleFontSize = m_controls[43].GetInt();

	m_iBackground = m_controls[44].GetInt();

	strcpy(m_szName, m_controls[45].GetString());

	int i;

	for(i = 0; i < NUM_INTF_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CIntfResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_INTF_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CIntfResource::IntfDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CIntfResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CIntfResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_INTF_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_INTF_OK)
			{
				pResource->CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_INTF_CONTROLS; i++)
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
