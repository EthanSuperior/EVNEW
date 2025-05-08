// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File COutfResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "COutfResource.h"

#include "resource.h"
#include "CPictResource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

COutfResource::COutfResource(void)
{
	m_iDisplayWeight = 0;
	m_iMass          = 0;
	m_iTechLevel     = 0;

	int i;

	for(i = 0; i < 4; i++)
	{
		m_iModTypes[i]  = -1;
		m_iModValues[i] = 0;
	}

	m_iMaxCount = 1;

	m_iFlags = 0x0000;

	m_iCost = 0;

	memset(m_szAvailability, 0, 255 * sizeof(char));
	memset(m_szOnPurchase,   0, 255 * sizeof(char));

	for(i = 0; i < 8; i++)
	{
		m_cContribute[i] = 0x00;
		m_cRequire[i]    = 0x00;
	}

	memset(m_szOnSell, 0, 255 * sizeof(char));

	m_iItemClass = 0;

	for(i = 0; i < 2; i++)
		m_cScanMask[i] = 0x00;

	m_iBuyRandom = 100;

	memset(m_szShortName,           0, 64 * sizeof(char));
	memset(m_szLowerCaseName,       0, 64 * sizeof(char));
	memset(m_szLowerCasePluralName, 0, 65 * sizeof(char));

	m_iRequiredGovernment = -1;

	m_iEditModTypeIndex = -1;
}

COutfResource::~COutfResource(void)
{

}

int COutfResource::GetType(void)
{
	return CNR_TYPE_OUTF;
}

int COutfResource::GetSize(void)
{
	return 1028;
}

int COutfResource::GetDialogID(void)
{
	return IDD_EDIT_OUTF;
}

DLGPROCNOCALLBACK COutfResource::GetDialogProc(void)
{
	return OutfDlgProc;
}

int COutfResource::GetNumFields(void)
{
	return NUM_OUTF_FIELDS;
}

const std::string * COutfResource::GetFieldNames(void)
{
	return g_szOutfFields;
}

int COutfResource::Save(char *pOutput)
{
	SwapEndians();

	*(short *)pOutput = m_iDisplayWeight;      pOutput += sizeof(short);
	*(short *)pOutput = m_iMass;               pOutput += sizeof(short);
	*(short *)pOutput = m_iTechLevel;          pOutput += sizeof(short);
	*(short *)pOutput = m_iModTypes[0];        pOutput += sizeof(short);
	*(short *)pOutput = m_iModValues[0];       pOutput += sizeof(short);
	*(short *)pOutput = m_iMaxCount;           pOutput += sizeof(short);
	*(USHORT *)pOutput = m_iFlags;             pOutput += sizeof(USHORT);
	*(int   *)pOutput = m_iCost;               pOutput += sizeof(int);
	*(short *)pOutput = m_iModTypes[1];        pOutput += sizeof(short);
	*(short *)pOutput = m_iModValues[1];       pOutput += sizeof(short);
	*(short *)pOutput = m_iModTypes[2];        pOutput += sizeof(short);
	*(short *)pOutput = m_iModValues[2];       pOutput += sizeof(short);
	*(short *)pOutput = m_iModTypes[3];        pOutput += sizeof(short);
	*(short *)pOutput = m_iModValues[3];       pOutput += sizeof(short);

	ToMacString(m_szShortName);
	ToMacString(m_szLowerCaseName);
	ToMacString(m_szLowerCasePluralName);

	memcpy(pOutput, m_cContribute,            8 * sizeof(char)); pOutput +=   8 * sizeof(char);
	memcpy(pOutput, m_cRequire,               8 * sizeof(char)); pOutput +=   8 * sizeof(char);
	memcpy(pOutput, m_szAvailability,       255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_szOnPurchase,         255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_szOnSell,             255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_szShortName,           64 * sizeof(char)); pOutput +=  64 * sizeof(char);
	memcpy(pOutput, m_szLowerCaseName,       64 * sizeof(char)); pOutput +=  64 * sizeof(char);
	memcpy(pOutput, m_szLowerCasePluralName, 65 * sizeof(char)); pOutput +=  65 * sizeof(char);

	ToWinString(m_szShortName);
	ToWinString(m_szLowerCaseName);
	ToWinString(m_szLowerCasePluralName);

	*(short *)pOutput = m_iItemClass;          pOutput += sizeof(short);

	memcpy(pOutput, m_cScanMask, 2 * sizeof(char)); pOutput += 2 * sizeof(char);

	*(short *)pOutput = m_iBuyRandom;          pOutput += sizeof(short);
	*(short *)pOutput = m_iRequiredGovernment; pOutput += sizeof(short);

	SwapEndians();

	return 1;
}

int COutfResource::Load(char *pInput, int iSize)
{
	m_iDisplayWeight      = *(short *)pInput; pInput += sizeof(short);
	m_iMass               = *(short *)pInput; pInput += sizeof(short);
	m_iTechLevel          = *(short *)pInput; pInput += sizeof(short);
	m_iModTypes[0]        = *(short *)pInput; pInput += sizeof(short);
	m_iModValues[0]       = *(short *)pInput; pInput += sizeof(short);
	m_iMaxCount           = *(short *)pInput; pInput += sizeof(short);
	m_iFlags              = *(USHORT *)pInput; pInput += sizeof(USHORT);
	m_iCost               = *(int   *)pInput; pInput += sizeof(int);
	m_iModTypes[1]        = *(short *)pInput; pInput += sizeof(short);
	m_iModValues[1]       = *(short *)pInput; pInput += sizeof(short);
	m_iModTypes[2]        = *(short *)pInput; pInput += sizeof(short);
	m_iModValues[2]       = *(short *)pInput; pInput += sizeof(short);
	m_iModTypes[3]        = *(short *)pInput; pInput += sizeof(short);
	m_iModValues[3]       = *(short *)pInput; pInput += sizeof(short);

	memcpy(m_cContribute,           pInput,   8 * sizeof(char)); pInput +=   8 * sizeof(char);
	memcpy(m_cRequire,              pInput,   8 * sizeof(char)); pInput +=   8 * sizeof(char);
	memcpy(m_szAvailability,        pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	memcpy(m_szOnPurchase,          pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	memcpy(m_szOnSell,              pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	memcpy(m_szShortName,           pInput,  64 * sizeof(char)); pInput +=  64 * sizeof(char);
	memcpy(m_szLowerCaseName,       pInput,  64 * sizeof(char)); pInput +=  64 * sizeof(char);
	memcpy(m_szLowerCasePluralName, pInput,  65 * sizeof(char)); pInput +=  65 * sizeof(char);

	ToWinString(m_szShortName);
	ToWinString(m_szLowerCaseName);
	ToWinString(m_szLowerCasePluralName);

	m_iItemClass          = *(short *)pInput; pInput += sizeof(short);

	memcpy(m_cScanMask, pInput, 2 * sizeof(char)); pInput += 2 * sizeof(char);
	
	m_iBuyRandom          = *(short *)pInput; pInput += sizeof(short);
	m_iRequiredGovernment = *(short *)pInput; pInput += sizeof(short);

	SwapEndians();

	return 1;
}

int COutfResource::SwapEndians(void)
{
	m_iDisplayWeight      = SwapEndianShort(m_iDisplayWeight);
	m_iMass               = SwapEndianShort(m_iMass);
	m_iTechLevel          = SwapEndianShort(m_iTechLevel);
	m_iModTypes[0]        = SwapEndianShort(m_iModTypes[0]);
	m_iModValues[0]       = SwapEndianShort(m_iModValues[0]);
	m_iMaxCount           = SwapEndianShort(m_iMaxCount);
	m_iFlags              = SwapEndianShort(m_iFlags);
	m_iCost               = SwapEndianInt(m_iCost);
	m_iModTypes[1]        = SwapEndianShort(m_iModTypes[1]);
	m_iModValues[1]       = SwapEndianShort(m_iModValues[1]);
	m_iModTypes[2]        = SwapEndianShort(m_iModTypes[2]);
	m_iModValues[2]       = SwapEndianShort(m_iModValues[2]);
	m_iModTypes[3]        = SwapEndianShort(m_iModTypes[3]);
	m_iModValues[3]       = SwapEndianShort(m_iModValues[3]);
	m_iItemClass          = SwapEndianShort(m_iItemClass);
	m_iBuyRandom          = SwapEndianShort(m_iBuyRandom);
	m_iRequiredGovernment = SwapEndianShort(m_iRequiredGovernment);

	return 1;
}

int COutfResource::SaveToText(std::ostream & output)
{
	output << m_iDisplayWeight << '\t'
		   << m_iMass          << '\t'
		   << m_iTechLevel     << '\t'
		   << m_iModTypes[0]   << '\t'
		   << m_iModValues[0]  << '\t'
		   << m_iModTypes[1]   << '\t'
		   << m_iModValues[1]  << '\t'
		   << m_iModTypes[2]   << '\t'
		   << m_iModValues[2]  << '\t'
		   << m_iModTypes[3]   << '\t'
		   << m_iModValues[3]  << '\t'
		   << m_iMaxCount      << '\t'
		   << m_iCost          << '\t'
		   << m_iItemClass     << '\t';

	char c = m_cScanMask[0]; m_cScanMask[0] = m_cScanMask[1]; m_cScanMask[1] = c;

	PrintHex16Field(output, m_cScanMask, '\t');

	c = m_cScanMask[0]; m_cScanMask[0] = m_cScanMask[1]; m_cScanMask[1] = c;

	output << m_iBuyRandom << '\t';

	PrintTextField(output, m_szAvailability, '\t');
	PrintTextField(output, m_szOnPurchase,   '\t');
	PrintTextField(output, m_szOnSell,       '\t');

	PrintHex64Field(output, m_cContribute, '\t');
	PrintHex64Field(output, m_cRequire,    '\t');

	PrintTextField(output, m_szShortName,           '\t');
	PrintTextField(output, m_szLowerCaseName,       '\t');
	PrintTextField(output, m_szLowerCasePluralName, '\t');

	output << m_iRequiredGovernment << '\t';

	PrintHex16Field(output, (char *)&m_iFlags, '\t');

	return 1;
}

int COutfResource::LoadFromText(std::istream & input)
{
	input >> m_iDisplayWeight
		  >> m_iMass
		  >> m_iTechLevel
		  >> m_iModTypes[0]
		  >> m_iModValues[0]
		  >> m_iModTypes[1]
		  >> m_iModValues[1]
		  >> m_iModTypes[2]
		  >> m_iModValues[2]
		  >> m_iModTypes[3]
		  >> m_iModValues[3]
		  >> m_iMaxCount
		  >> m_iCost
		  >> m_iItemClass;

	ReadHex16Field(input, m_cScanMask);

	char c = m_cScanMask[0]; m_cScanMask[0] = m_cScanMask[1]; m_cScanMask[1] = c;

	input >> m_iBuyRandom;

	input.ignore(1);

	ReadTextField(input, m_szAvailability, 255);
	ReadTextField(input, m_szOnPurchase,   255);
	ReadTextField(input, m_szOnSell,       255);

	ReadHex64Field(input, m_cContribute);
	ReadHex64Field(input, m_cRequire);

	ReadTextField(input, m_szShortName,           64);
	ReadTextField(input, m_szLowerCaseName,       64);
	ReadTextField(input, m_szLowerCasePluralName, 65);

	input >> m_iRequiredGovernment;

	ReadHex16Field(input, (char *)&m_iFlags);

	return 1;
}

int COutfResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "outf ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_OUTF_EDIT1, CCONTROL_TYPE_INT, IDS_STRING512);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_OUTF_EDIT2, CCONTROL_TYPE_INT, IDS_STRING513);
	m_controls[1].SetInt(m_iDisplayWeight);
	m_controls[2].Create(hwnd, IDC_EDIT_OUTF_EDIT3, CCONTROL_TYPE_INT, IDS_STRING514);
	m_controls[2].SetInt(m_iMass);
	m_controls[3].Create(hwnd, IDC_EDIT_OUTF_EDIT4, CCONTROL_TYPE_INT, IDS_STRING515);
	m_controls[3].SetInt(m_iTechLevel);
	m_controls[4].Create(hwnd, IDC_EDIT_OUTF_COMBO1, CCONTROL_TYPE_COMBOBOX, IDS_STRING516);
	m_controls[4].SetComboStrings(NUM_OUTF_MODTYPE_CHOICES, g_szOutfModTypeChoices);
	m_controls[4].SetInt(ModTypeToIndex(m_iModTypes[0]));
	m_controls[5].Create(hwnd, IDC_EDIT_OUTF_EDIT6, CCONTROL_TYPE_INT, IDS_STRING516);
	m_controls[5].SetInt(m_iModValues[0]);
	m_controls[6].Create(hwnd, IDC_EDIT_OUTF_COMBO2, CCONTROL_TYPE_COMBOBOX, IDS_STRING516);
	m_controls[6].SetComboStrings(NUM_OUTF_MODTYPE_CHOICES, g_szOutfModTypeChoices);
	m_controls[6].SetInt(ModTypeToIndex(m_iModTypes[1]));
	m_controls[7].Create(hwnd, IDC_EDIT_OUTF_EDIT8, CCONTROL_TYPE_INT, IDS_STRING516);
	m_controls[7].SetInt(m_iModValues[1]);
	m_controls[8].Create(hwnd, IDC_EDIT_OUTF_COMBO3, CCONTROL_TYPE_COMBOBOX, IDS_STRING516);
	m_controls[8].SetComboStrings(NUM_OUTF_MODTYPE_CHOICES, g_szOutfModTypeChoices);
	m_controls[8].SetInt(ModTypeToIndex(m_iModTypes[2]));
	m_controls[9].Create(hwnd, IDC_EDIT_OUTF_EDIT10, CCONTROL_TYPE_INT, IDS_STRING516);
	m_controls[9].SetInt(m_iModValues[2]);
	m_controls[10].Create(hwnd, IDC_EDIT_OUTF_COMBO4, CCONTROL_TYPE_COMBOBOX, IDS_STRING516);
	m_controls[10].SetComboStrings(NUM_OUTF_MODTYPE_CHOICES, g_szOutfModTypeChoices);
	m_controls[10].SetInt(ModTypeToIndex(m_iModTypes[3]));
	m_controls[11].Create(hwnd, IDC_EDIT_OUTF_EDIT12, CCONTROL_TYPE_INT, IDS_STRING516);
	m_controls[11].SetInt(m_iModValues[3]);
	m_controls[12].Create(hwnd, IDC_EDIT_OUTF_EDIT13, CCONTROL_TYPE_INT, IDS_STRING517);
	m_controls[12].SetInt(m_iMaxCount);
	m_controls[13].Create(hwnd, IDC_EDIT_OUTF_EDIT14, CCONTROL_TYPE_INT, IDS_STRING518);
	m_controls[13].SetInt(m_iCost);
	m_controls[14].Create(hwnd, IDC_EDIT_OUTF_EDIT15, CCONTROL_TYPE_STR255, IDS_STRING519);
	m_controls[14].SetString(m_szAvailability);
	m_controls[15].Create(hwnd, IDC_EDIT_OUTF_EDIT16, CCONTROL_TYPE_STR255, IDS_STRING520);
	m_controls[15].SetString(m_szOnPurchase);
	m_controls[16].Create(hwnd, IDC_EDIT_OUTF_EDIT17, CCONTROL_TYPE_HEXINT64, IDS_STRING521);
	m_controls[16].SetString(m_cContribute);
	m_controls[17].Create(hwnd, IDC_EDIT_OUTF_EDIT18, CCONTROL_TYPE_HEXINT64, IDS_STRING522);
	m_controls[17].SetString(m_cRequire);
	m_controls[18].Create(hwnd, IDC_EDIT_OUTF_EDIT19, CCONTROL_TYPE_STR255, IDS_STRING523);
	m_controls[18].SetString(m_szOnSell);
	m_controls[19].Create(hwnd, IDC_EDIT_OUTF_EDIT20, CCONTROL_TYPE_INT, IDS_STRING524);
	m_controls[19].SetInt(m_iItemClass);
	m_controls[20].Create(hwnd, IDC_EDIT_OUTF_EDIT21, CCONTROL_TYPE_HEXINT16, IDS_STRING525);
	m_controls[20].SetString(m_cScanMask);
	m_controls[21].Create(hwnd, IDC_EDIT_OUTF_EDIT22, CCONTROL_TYPE_INT, IDS_STRING526);
	m_controls[21].SetInt(m_iBuyRandom);
	m_controls[22].Create(hwnd, IDC_EDIT_OUTF_EDIT23, CCONTROL_TYPE_STR64, IDS_STRING527);
	m_controls[22].SetString(m_szShortName);
	m_controls[23].Create(hwnd, IDC_EDIT_OUTF_EDIT24, CCONTROL_TYPE_STR64, IDS_STRING528);
	m_controls[23].SetString(m_szLowerCaseName);
	m_controls[24].Create(hwnd, IDC_EDIT_OUTF_EDIT25, CCONTROL_TYPE_STR65, IDS_STRING529);
	m_controls[24].SetString(m_szLowerCasePluralName);
	m_controls[25].Create(hwnd, IDC_EDIT_OUTF_EDIT26, CCONTROL_TYPE_INT, IDS_STRING530);
	m_controls[25].SetInt(m_iRequiredGovernment);
	m_controls[26].Create(hwnd, IDC_EDIT_OUTF_CHECK1, CCONTROL_TYPE_CHECK, IDS_STRING531);
	m_controls[26].SetInt(m_iFlags & 0x0001);
	m_controls[27].Create(hwnd, IDC_EDIT_OUTF_CHECK2, CCONTROL_TYPE_CHECK, IDS_STRING532);
	m_controls[27].SetInt(m_iFlags & 0x0002);
	m_controls[28].Create(hwnd, IDC_EDIT_OUTF_CHECK3, CCONTROL_TYPE_CHECK, IDS_STRING533);
	m_controls[28].SetInt(m_iFlags & 0x0004);
	m_controls[29].Create(hwnd, IDC_EDIT_OUTF_CHECK4, CCONTROL_TYPE_CHECK, IDS_STRING534);
	m_controls[29].SetInt(m_iFlags & 0x0008);
	m_controls[30].Create(hwnd, IDC_EDIT_OUTF_CHECK5, CCONTROL_TYPE_CHECK, IDS_STRING535);
	m_controls[30].SetInt(m_iFlags & 0x0010);
	m_controls[31].Create(hwnd, IDC_EDIT_OUTF_CHECK6, CCONTROL_TYPE_CHECK, IDS_STRING536);
	m_controls[31].SetInt(m_iFlags & 0x0020);
	m_controls[32].Create(hwnd, IDC_EDIT_OUTF_CHECK7, CCONTROL_TYPE_CHECK, IDS_STRING537);
	m_controls[32].SetInt(m_iFlags & 0x0100);
	m_controls[33].Create(hwnd, IDC_EDIT_OUTF_CHECK8, CCONTROL_TYPE_CHECK, IDS_STRING538);
	m_controls[33].SetInt(m_iFlags & 0x0200);
	m_controls[34].Create(hwnd, IDC_EDIT_OUTF_CHECK9, CCONTROL_TYPE_CHECK, IDS_STRING539);
	m_controls[34].SetInt(m_iFlags & 0x0400);
	m_controls[35].Create(hwnd, IDC_EDIT_OUTF_CHECK10, CCONTROL_TYPE_CHECK, IDS_STRING540);
	m_controls[35].SetInt(m_iFlags & 0x0800);
	m_controls[36].Create(hwnd, IDC_EDIT_OUTF_CHECK11, CCONTROL_TYPE_CHECK, IDS_STRING541);
	m_controls[36].SetInt(m_iFlags & 0x1000);
	m_controls[37].Create(hwnd, IDC_EDIT_OUTF_CHECK12, CCONTROL_TYPE_CHECK, IDS_STRING542);
	m_controls[37].SetInt(m_iFlags & 0x2000);
	m_controls[38].Create(hwnd, IDC_EDIT_OUTF_CHECK13, CCONTROL_TYPE_CHECK, IDS_STRING543);
	m_controls[38].SetInt(m_iFlags & 0x4000);
	m_controls[39].Create(hwnd, IDC_EDIT_OUTF_EDIT27, CCONTROL_TYPE_STR256, IDS_STRING2544);
	m_controls[39].SetString(m_szName);
	m_controls[40].Create(hwnd, IDC_EDIT_OUTF_BUTTON8, CCONTROL_TYPE_COLOR, -1);
	m_controls[40].SetInt(Color15To24((USHORT)m_iModValues[0]));
	m_controls[41].Create(hwnd, IDC_EDIT_OUTF_BUTTON9, CCONTROL_TYPE_COLOR, -1);
	m_controls[41].SetInt(Color15To24((USHORT)m_iModValues[1]));
	m_controls[42].Create(hwnd, IDC_EDIT_OUTF_BUTTON10, CCONTROL_TYPE_COLOR, -1);
	m_controls[42].SetInt(Color15To24((USHORT)m_iModValues[2]));
	m_controls[43].Create(hwnd, IDC_EDIT_OUTF_BUTTON11, CCONTROL_TYPE_COLOR, -1);
	m_controls[43].SetInt(Color15To24((USHORT)m_iModValues[3]));

	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_OUTF_TEXT6),  g_szOutfModValueTexts[ModTypeToIndex(m_iModTypes[0])].c_str());
	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_OUTF_TEXT8),  g_szOutfModValueTexts[ModTypeToIndex(m_iModTypes[1])].c_str());
	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_OUTF_TEXT10), g_szOutfModValueTexts[ModTypeToIndex(m_iModTypes[2])].c_str());
	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_OUTF_TEXT12), g_szOutfModValueTexts[ModTypeToIndex(m_iModTypes[3])].c_str());

	if((m_iModTypes[0] == 17) || (m_iModTypes[0] == 30))
	{
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_EDIT6),   SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON4), SW_SHOW);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON8), SW_HIDE);
	}
	else if(m_iModTypes[0] == 43)
	{
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_EDIT6),   SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON4), SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON8), SW_SHOW);
	}
	else
	{
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_EDIT6),   SW_SHOW);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON4), SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON8), SW_HIDE);
	}

	if((m_iModTypes[1] == 17) || (m_iModTypes[1] == 30) || (m_iModTypes[1] == 43))
	{
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_EDIT8),   SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON5), SW_SHOW);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON9), SW_HIDE);
	}
	else if(m_iModTypes[1] == 43)
	{
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_EDIT8),   SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON5), SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON9), SW_SHOW);
	}
	else
	{
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_EDIT8),   SW_SHOW);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON5), SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON9), SW_HIDE);
	}

	if((m_iModTypes[2] == 17) || (m_iModTypes[2] == 30))
	{
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_EDIT10),   SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON6),  SW_SHOW);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON10), SW_HIDE);
	}
	else if(m_iModTypes[2] == 43)
	{
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_EDIT10),   SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON6),  SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON10), SW_SHOW);
	}
	else
	{
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_EDIT10),   SW_SHOW);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON6),  SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON10), SW_HIDE);
	}

	if((m_iModTypes[3] == 17) || (m_iModTypes[3] == 30))
	{
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_EDIT12),   SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON7),  SW_SHOW);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON11), SW_HIDE);
	}
	else if(m_iModTypes[3] == 43)
	{
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_EDIT12),   SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON7),  SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON11), SW_SHOW);
	}
	else
	{
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_EDIT12),   SW_SHOW);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON7),  SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON11), SW_HIDE);
	}

	std::string szText = "Outfitter Desc ID: ";
	szText += ToString(m_iID + 3000 - 128);

	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_OUTF_TEXT28), szText.c_str());

	szText = "Outfitter PICT ID: ";
	szText += ToString(m_iID + 6000 - 128);

	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_OUTF_TEXT29), szText.c_str());

	return 1;
}

int COutfResource::CloseAndSave(void)
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

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[39].GetString()) != 0))
		iIDOrNameChanged = 1;

	m_iID = m_controls[0].GetInt();

	m_iDisplayWeight = m_controls[1].GetInt();
	m_iMass          = m_controls[2].GetInt();
	m_iTechLevel     = m_controls[3].GetInt();

	m_iModTypes[0]  = IndexToModType(m_controls[4].GetInt());
	m_iModValues[0] = m_controls[5].GetInt();
	m_iModTypes[1]  = IndexToModType(m_controls[6].GetInt());
	m_iModValues[1] = m_controls[7].GetInt();
	m_iModTypes[2]  = IndexToModType(m_controls[8].GetInt());
	m_iModValues[2] = m_controls[9].GetInt();
	m_iModTypes[3]  = IndexToModType(m_controls[10].GetInt());
	m_iModValues[3] = m_controls[11].GetInt();

	if(m_iModTypes[0] == 43)
		m_iModValues[0] = Color24To15(m_controls[40].GetInt());

	if(m_iModTypes[1] == 43)
		m_iModValues[1] = Color24To15(m_controls[41].GetInt());

	if(m_iModTypes[2] == 43)
		m_iModValues[2] = Color24To15(m_controls[42].GetInt());

	if(m_iModTypes[3] == 43)
		m_iModValues[3] = Color24To15(m_controls[43].GetInt());

	m_iMaxCount = m_controls[12].GetInt();

	m_iCost = m_controls[13].GetInt();

	strcpy(m_szAvailability, m_controls[14].GetString());
	strcpy(m_szOnPurchase, m_controls[15].GetString());

	memcpy(m_cContribute, m_controls[16].GetString(), 8 * sizeof(char));
	memcpy(m_cRequire,    m_controls[17].GetString(), 8 * sizeof(char));

	strcpy(m_szOnSell, m_controls[18].GetString());

	m_iItemClass = m_controls[19].GetInt();

	memcpy(m_cScanMask, m_controls[20].GetString(), 2 * sizeof(char));

	m_iBuyRandom = m_controls[21].GetInt();

	strcpy(m_szShortName, m_controls[22].GetString());
	strcpy(m_szLowerCaseName, m_controls[23].GetString());
	strcpy(m_szLowerCasePluralName, m_controls[24].GetString());

	m_iRequiredGovernment = m_controls[25].GetInt();

	m_iFlags = 0x0000;

	m_iFlags |= m_controls[26].GetInt() << 0;
	m_iFlags |= m_controls[27].GetInt() << 1;
	m_iFlags |= m_controls[28].GetInt() << 2;
	m_iFlags |= m_controls[29].GetInt() << 3;
	m_iFlags |= m_controls[30].GetInt() << 4;
	m_iFlags |= m_controls[31].GetInt() << 5;
	m_iFlags |= m_controls[32].GetInt() << 8;
	m_iFlags |= m_controls[33].GetInt() << 9;
	m_iFlags |= m_controls[34].GetInt() << 10;
	m_iFlags |= m_controls[35].GetInt() << 11;
	m_iFlags |= m_controls[36].GetInt() << 12;
	m_iFlags |= m_controls[37].GetInt() << 13;
	m_iFlags |= m_controls[38].GetInt() << 14;

	strcpy(m_szName, m_controls[39].GetString());

	int i;

	for(i = 0; i < NUM_OUTF_CONTROLS; i++)
		m_controls[i].Destroy();

	if (m_iPortExists)
	{
		qt::DestroyPortAssociation((qt::CGrafPort*)qt::GetHWNDPort(m_pWindow->GetHWND()));

		m_iPortExists = 0;
	}

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int COutfResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_OUTF_CONTROLS; i++)
		m_controls[i].Destroy();

	if (m_iPortExists)
	{
		qt::DestroyPortAssociation((qt::CGrafPort*)qt::GetHWNDPort(m_pWindow->GetHWND()));

		m_iPortExists = 0;
	}

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

short COutfResource::ModTypeToIndex(short iModType)
{
	if(iModType < 0)
		return 0;
	else if(iModType < 10)
		return (iModType);
	else if(iModType < 26)
		return (iModType - 1);
	else
		return (iModType - 2);
}

short COutfResource::IndexToModType(short iIndex)
{
	if(iIndex < 10)
		return (iIndex);
	else if(iIndex < 25)
		return (iIndex + 1);
	else
		return (iIndex + 2);
}

BOOL COutfResource::OutfDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	COutfResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (COutfResource *)pWindow->GetExtraData(2);
	int i;

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			pResource->Initialize(hwnd);

			return TRUE;

			break;
		}

		/*case WM_PAINT:
		{
			pResource->OnPaint();

			return TRUE;

			break;
		}*/

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
			int iControlID = LOWORD(wparam);

			if (iControlID == IDC_EDIT_OUTF_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if (iControlID == IDC_EDIT_OUTF_OK)
			{
				pResource->CloseAndSave();
			}
			else if (iControlID == IDC_EDIT_OUTF_BUTTON1)
			{
				char cValue[2];

				memcpy(cValue, pResource->m_controls[20].GetString(), 2);

				pResource->m_bitFieldControl.DoDialog(pResource->m_pWindow, 16, cValue);

				pResource->m_controls[20].SetString(cValue);
			}
			else if (iControlID == IDC_EDIT_OUTF_BUTTON2)
			{
				char cValue[8];

				memcpy(cValue, pResource->m_controls[16].GetString(), 8);

				pResource->m_bitFieldControl.DoDialog(pResource->m_pWindow, 64, cValue);

				pResource->m_controls[16].SetString(cValue);
			}
			else if (iControlID == IDC_EDIT_OUTF_BUTTON3)
			{
				char cValue[8];

				memcpy(cValue, pResource->m_controls[17].GetString(), 8);

				pResource->m_bitFieldControl.DoDialog(pResource->m_pWindow, 64, cValue);

				pResource->m_controls[17].SetString(cValue);
			}
			else if (iControlID == IDC_EDIT_OUTF_BUTTON4)
			{
				pResource->m_iEditModTypeIndex = 5;

				if (pResource->m_controls[4].GetInt() == 16)
					pResource->DoEditModType17();
				else
					pResource->DoEditModType30();
			}
			else if (iControlID == IDC_EDIT_OUTF_BUTTON5)
			{
				pResource->m_iEditModTypeIndex = 7;

				if (pResource->m_controls[6].GetInt() == 16)
					pResource->DoEditModType17();
				else
					pResource->DoEditModType30();
			}
			else if (iControlID == IDC_EDIT_OUTF_BUTTON6)
			{
				pResource->m_iEditModTypeIndex = 9;

				if (pResource->m_controls[8].GetInt() == 16)
					pResource->DoEditModType17();
				else
					pResource->DoEditModType30();
			}
			else if (iControlID == IDC_EDIT_OUTF_BUTTON7)
			{
				pResource->m_iEditModTypeIndex = 11;

				if (pResource->m_controls[10].GetInt() == 16)
					pResource->DoEditModType17();
				else
					pResource->DoEditModType30();
			}
			else
			{
				for (i = 0; i < NUM_OUTF_CONTROLS; i++)
				{
					if (iControlID == pResource->m_controls[i].GetControlID())
					{
						pResource->m_controls[i].ProcessMessage(iNotifyCode);

						break;
					}
				}
			}

			if ((iNotifyCode == CBN_SELCHANGE) && ((iControlID == IDC_EDIT_OUTF_COMBO1) || (iControlID == IDC_EDIT_OUTF_COMBO2) || (iControlID == IDC_EDIT_OUTF_COMBO3) || (iControlID == IDC_EDIT_OUTF_COMBO4)))
			{
				HWND hwndText;
				HWND hwndEdit;
				HWND hwndButton1;
				HWND hwndButton2;

				if (iControlID == IDC_EDIT_OUTF_COMBO1)
				{
					hwndText = GetDlgItem(hwnd, IDC_EDIT_OUTF_TEXT6);
					hwndEdit = GetDlgItem(hwnd, IDC_EDIT_OUTF_EDIT6);
					hwndButton1 = GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON4);
					hwndButton2 = GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON8);
				}
				else if (iControlID == IDC_EDIT_OUTF_COMBO2)
				{
					hwndText = GetDlgItem(hwnd, IDC_EDIT_OUTF_TEXT8);
					hwndEdit = GetDlgItem(hwnd, IDC_EDIT_OUTF_EDIT8);
					hwndButton1 = GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON5);
					hwndButton2 = GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON9);
				}
				else if (iControlID == IDC_EDIT_OUTF_COMBO3)
				{
					hwndText = GetDlgItem(hwnd, IDC_EDIT_OUTF_TEXT10);
					hwndEdit = GetDlgItem(hwnd, IDC_EDIT_OUTF_EDIT10);
					hwndButton1 = GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON6);
					hwndButton2 = GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON10);
				}
				else
				{
					hwndText = GetDlgItem(hwnd, IDC_EDIT_OUTF_TEXT12);
					hwndEdit = GetDlgItem(hwnd, IDC_EDIT_OUTF_EDIT12);
					hwndButton1 = GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON7);
					hwndButton2 = GetDlgItem(hwnd, IDC_EDIT_OUTF_BUTTON11);
				}

				int iIndex = ComboBox_GetCurSel((HWND)lparam);

				Static_SetText(hwndText, g_szOutfModValueTexts[iIndex].c_str());

				if ((iIndex == 16) || (iIndex == 28))
				{
					ShowWindow(hwndEdit, SW_HIDE);
					ShowWindow(hwndButton1, SW_SHOW);
					ShowWindow(hwndButton2, SW_HIDE);
				}
				else if (iIndex == 41)
				{
					ShowWindow(hwndEdit, SW_HIDE);
					ShowWindow(hwndButton1, SW_HIDE);
					ShowWindow(hwndButton2, SW_SHOW);
				}
				else
				{
					ShowWindow(hwndEdit, SW_SHOW);
					ShowWindow(hwndButton1, SW_HIDE);
					ShowWindow(hwndButton2, SW_HIDE);
				}
			}

			if ((iControlID == IDC_EDIT_OUTF_EDIT1) && (iNotifyCode == EN_CHANGE))
			{
				if ((pResource->m_controls[0].GetInt() >= 128) && (pResource->m_controls[0].GetInt() < 640))
				{
					std::string szText = "Outfitter Desc ID: ";
					szText += ToString(pResource->m_controls[0].GetInt() + 3000 - 128);

					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_OUTF_TEXT28), szText.c_str());

					szText = "Outfitter PICT ID: ";
					szText += ToString(pResource->m_controls[0].GetInt() + 6000 - 128) + " - ";
					szText += Workspace::RezStr(CNR_TYPE_PICT, pResource->m_controls[0].GetInt() + 6000 - 128);

					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_OUTF_TEXT29), szText.c_str());
				}
			}
			else if ((iControlID == IDC_EDIT_OUTF_BTN1) && (iNotifyCode == EN_CHANGE || iNotifyCode == EN_UPDATE))
			{
				if ((pResource->m_controls[0].GetInt() >= 128) && (pResource->m_controls[0].GetInt() < 640)) {
					short id = pResource->m_controls[0].GetInt() + 3000 - 128;
					CEditor::GetCurrentEditor()->ResourceExtra(id, std::string(pResource->m_controls[39].GetString()));
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


int COutfResource::OnPaint(void)
{
	if (!m_iPortExists)
	{
		qt::MacSetPort(qt::CreatePortAssociation(m_pWindow->GetHWND(), NULL, qt::kQTMLNoIdleEvents));
		m_iPortExists = 1;
	}
	else qt::MacSetPort(qt::GetHWNDPort(m_pWindow->GetHWND()));
	PAINTSTRUCT paintStruct;

	BeginPaint(m_pWindow->GetHWND(), &paintStruct);

	CPictResource* pict = (CPictResource*) Workspace::FindById(CNR_TYPE_PICT, m_iID + 6000 - 128);
	if (pict == NULL) {
		EndPaint(m_pWindow->GetHWND(), &paintStruct);
		return 1;
	}
	qt::Rect m_rectDest = { 0, 0, 64, 64 };
	//m_rectDest.right += m_rectDest.left;
	//m_rectDest.bottom += m_rectDest.top;
	if (pict->m_hTempPicture != NULL)
		qt::DrawPicture((qt::PicHandle)pict->m_hTempPicture, &m_rectDest);
	else if (pict->m_hPicture != NULL)
		qt::DrawPicture((qt::PicHandle)pict->m_hPicture, &m_rectDest);
	EndPaint(m_pWindow->GetHWND(), &paintStruct);

	return 1;
}

int COutfResource::DoEditModType17(void)
{
	m_wndEditModType17or30.SetExtraData(0, m_pWindow->GetExtraData(0));
	m_wndEditModType17or30.SetExtraData(1, m_pWindow->GetExtraData(1));
	m_wndEditModType17or30.SetExtraData(2, m_pWindow->GetExtraData(2));
	m_wndEditModType17or30.SetDlgProc(COutfResource::OutfEditModType17DlgProc);
	m_wndEditModType17or30.CreateAsDialog(m_pWindow->GetInstance(), IDD_EDIT_OUTF17, 1, m_pWindow);

	return 1;
}

int COutfResource::DoEditModType30(void)
{
	m_wndEditModType17or30.SetExtraData(0, m_pWindow->GetExtraData(0));
	m_wndEditModType17or30.SetExtraData(1, m_pWindow->GetExtraData(1));
	m_wndEditModType17or30.SetExtraData(2, m_pWindow->GetExtraData(2));
	m_wndEditModType17or30.SetDlgProc(COutfResource::OutfEditModType30DlgProc);
	m_wndEditModType17or30.CreateAsDialog(m_pWindow->GetInstance(), IDD_EDIT_OUTF30, 1, m_pWindow);

	return 1;
}

int COutfResource::InitModType17Controls(HWND hwnd)
{
	m_controlsModType17[0].Create(hwnd, IDC_EDIT_OUTF17_CHECK1, CCONTROL_TYPE_CHECK, -1);
	m_controlsModType17[0].SetInt(m_controls[m_iEditModTypeIndex].GetInt() & 0x0001);
	m_controlsModType17[1].Create(hwnd, IDC_EDIT_OUTF17_CHECK2, CCONTROL_TYPE_CHECK, -1);
	m_controlsModType17[1].SetInt(m_controls[m_iEditModTypeIndex].GetInt() & 0x0002);
	m_controlsModType17[2].Create(hwnd, IDC_EDIT_OUTF17_CHECK3, CCONTROL_TYPE_CHECK, -1);
	m_controlsModType17[2].SetInt(m_controls[m_iEditModTypeIndex].GetInt() & 0x0004);
	m_controlsModType17[3].Create(hwnd, IDC_EDIT_OUTF17_CHECK4, CCONTROL_TYPE_CHECK, -1);
	m_controlsModType17[3].SetInt(m_controls[m_iEditModTypeIndex].GetInt() & 0x0008);
	m_controlsModType17[4].Create(hwnd, IDC_EDIT_OUTF17_CHECK5, CCONTROL_TYPE_CHECK, -1);
	m_controlsModType17[4].SetInt(m_controls[m_iEditModTypeIndex].GetInt() & 0x1000);
	m_controlsModType17[5].Create(hwnd, IDC_EDIT_OUTF17_COMBO1, CCONTROL_TYPE_COMBOBOX, -1);
	m_controlsModType17[5].SetComboStrings(NUM_OUTF_MODTYPE17_FUELSHIELDDRAIN_CHOICES, g_szOutfModType17FuelShieldDrainChoices);
	m_controlsModType17[5].SetInt((m_controls[m_iEditModTypeIndex].GetInt() & 0x00F0) >> 4);
	m_controlsModType17[6].Create(hwnd, IDC_EDIT_OUTF17_COMBO2, CCONTROL_TYPE_COMBOBOX, -1);
	m_controlsModType17[6].SetComboStrings(NUM_OUTF_MODTYPE17_FUELSHIELDDRAIN_CHOICES, g_szOutfModType17FuelShieldDrainChoices);
	m_controlsModType17[6].SetInt((m_controls[m_iEditModTypeIndex].GetInt() & 0x0F00) >> 8);

	return 1;
}

int COutfResource::InitModType30Controls(HWND hwnd)
{
	m_controlsModType30[0].Create(hwnd, IDC_EDIT_OUTF30_CHECK1, CCONTROL_TYPE_CHECK, -1);
	m_controlsModType30[0].SetInt(m_controls[m_iEditModTypeIndex].GetInt() & 0x0001);
	m_controlsModType30[1].Create(hwnd, IDC_EDIT_OUTF30_CHECK2, CCONTROL_TYPE_CHECK, -1);
	m_controlsModType30[1].SetInt(m_controls[m_iEditModTypeIndex].GetInt() & 0x0002);
	m_controlsModType30[2].Create(hwnd, IDC_EDIT_OUTF30_CHECK3, CCONTROL_TYPE_CHECK, -1);
	m_controlsModType30[2].SetInt(m_controls[m_iEditModTypeIndex].GetInt() & 0x0004);
	m_controlsModType30[3].Create(hwnd, IDC_EDIT_OUTF30_CHECK4, CCONTROL_TYPE_CHECK, -1);
	m_controlsModType30[3].SetInt(m_controls[m_iEditModTypeIndex].GetInt() & 0x0008);

	return 1;
}

int COutfResource::ModType17CloseAndSave(void)
{
	int iValue = 0x0000;

	iValue |= m_controlsModType17[0].GetInt() << 0;
	iValue |= m_controlsModType17[1].GetInt() << 1;
	iValue |= m_controlsModType17[2].GetInt() << 2;
	iValue |= m_controlsModType17[3].GetInt() << 3;
	iValue |= m_controlsModType17[4].GetInt() << 12;

	iValue |= m_controlsModType17[5].GetInt() << 4;
	iValue |= m_controlsModType17[6].GetInt() << 8;

	m_controls[m_iEditModTypeIndex].SetInt(iValue);

	int i;

	for(i = 0; i < NUM_OUTF_MODTYPE17_CONTROLS; i++)
		m_controlsModType17[i].Destroy();

	m_wndEditModType17or30.Destroy();

	return 1;
}

int COutfResource::ModType17CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_OUTF_MODTYPE17_CONTROLS; i++)
		m_controlsModType17[i].Destroy();

	m_wndEditModType17or30.Destroy();

	return 1;
}

int COutfResource::ModType30CloseAndSave(void)
{
	int iValue = 0x0000;

	iValue |= m_controlsModType30[0].GetInt() << 0;
	iValue |= m_controlsModType30[1].GetInt() << 1;
	iValue |= m_controlsModType30[2].GetInt() << 2;
	iValue |= m_controlsModType30[3].GetInt() << 3;

	m_controls[m_iEditModTypeIndex].SetInt(iValue);

	int i;

	for(i = 0; i < NUM_OUTF_MODTYPE30_CONTROLS; i++)
		m_controlsModType30[i].Destroy();

	m_wndEditModType17or30.Destroy();

	return 1;
}

int COutfResource::ModType30CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_OUTF_MODTYPE30_CONTROLS; i++)
		m_controlsModType30[i].Destroy();

	m_wndEditModType17or30.Destroy();

	return 1;
}

BOOL COutfResource::OutfEditModType17DlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow       *pWindow;
	COutfResource *pResource = NULL;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (COutfResource *)pWindow->GetExtraData(2);

	int i;

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			pResource->InitModType17Controls(hwnd);

			return TRUE;

			break;
		}

		case WM_SYSCOMMAND:
		{
			if(wparam == SC_CLOSE)
			{
				pResource->ModType17CloseAndDontSave();

				return TRUE;
			}

			break;
		}

		case WM_COMMAND:
		{
			int iNotifyCode = HIWORD(wparam);
			int iControlID  = LOWORD(wparam);

			if(iControlID == IDC_EDIT_OUTF17_CANCEL)
			{
				pResource->ModType17CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_OUTF17_OK)
			{
				pResource->ModType17CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_OUTF_MODTYPE17_CONTROLS; i++)
				{
					if(iControlID == pResource->m_controlsModType17[i].GetControlID())
					{
						pResource->m_controlsModType17[i].ProcessMessage(iNotifyCode);

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

BOOL COutfResource::OutfEditModType30DlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow       *pWindow;
	COutfResource *pResource = NULL;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (COutfResource *)pWindow->GetExtraData(2);

	int i;

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			pResource->InitModType30Controls(hwnd);

			return TRUE;

			break;
		}

		case WM_SYSCOMMAND:
		{
			if(wparam == SC_CLOSE)
			{
				pResource->ModType30CloseAndDontSave();

				return TRUE;
			}

			break;
		}

		case WM_COMMAND:
		{
			int iNotifyCode = HIWORD(wparam);
			int iControlID  = LOWORD(wparam);

			if(iControlID == IDC_EDIT_OUTF30_CANCEL)
			{
				pResource->ModType30CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_OUTF30_OK)
			{
				pResource->ModType30CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_OUTF_MODTYPE30_CONTROLS; i++)
				{
					if(iControlID == pResource->m_controlsModType30[i].GetControlID())
					{
						pResource->m_controlsModType30[i].ProcessMessage(iNotifyCode);

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
