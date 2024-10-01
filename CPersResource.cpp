// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CPersResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CPersResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CPersResource::CPersResource(void)
{
	m_iSystem     = -1;
	m_iGovernment = -1;

	m_iAIType = 1;

	m_iAggressiveness = 1;
	m_iCowardice      = 0;

	m_iShipType = 128;

	int i;

	for(i = 0; i < 4; i++)
	{
		m_iWeaponTypes[i]  = -1;
		m_iWeaponCounts[i] =  0;
		m_iWeaponAmmos[i]  =  0;
	}

	m_iCredits = 0;

	m_iShieldMod = 100;

	m_iHailPicture = -1;
	m_iCommQuote   = -1;
	m_iHailQuote   = -1;

	m_iLinkedMission = -1;

	m_iFlags1 = 0x0000;

	memset(m_szActiveOn, 0, 256 * sizeof(char));

	m_iGrantClass  = -1;
	m_iGrantCount  =  0;
	m_iGrantRandom =  0;

	memset(m_szSubtitle, 0, 64 * sizeof(char));

	m_iColor = 0x00000000;

	m_iFlags2 = 0x0000;
}

CPersResource::~CPersResource(void)
{

}

int CPersResource::GetType(void)
{
	return CNR_TYPE_PERS;
}

int CPersResource::GetSize(void)
{
	return 400;
}

int CPersResource::GetDialogID(void)
{
	return IDD_EDIT_PERS;
}

DLGPROCNOCALLBACK CPersResource::GetDialogProc(void)
{
	return PersDlgProc;
}

int CPersResource::GetNumFields(void)
{
	return NUM_PERS_FIELDS;
}

const std::string * CPersResource::GetFieldNames(void)
{
	return g_szPersFields;
}

int CPersResource::Save(char *pOutput)
{
	SwapEndians();

	*(short *)pOutput = m_iSystem;          pOutput += sizeof(short);
	*(short *)pOutput = m_iGovernment;      pOutput += sizeof(short);
	*(short *)pOutput = m_iAIType;          pOutput += sizeof(short);
	*(short *)pOutput = m_iAggressiveness;  pOutput += sizeof(short);
	*(short *)pOutput = m_iCowardice;       pOutput += sizeof(short);
	*(short *)pOutput = m_iShipType;        pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponTypes[0];  pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponTypes[1];  pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponTypes[2];  pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponTypes[3];  pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponCounts[0]; pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponCounts[1]; pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponCounts[2]; pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponCounts[3]; pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponAmmos[0];  pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponAmmos[1];  pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponAmmos[2];  pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponAmmos[3];  pOutput += sizeof(short);
	*(int   *)pOutput = m_iCredits;         pOutput += sizeof(int);
	*(short *)pOutput = m_iShieldMod;       pOutput += sizeof(short);
	*(short *)pOutput = m_iHailPicture;     pOutput += sizeof(short);
	*(short *)pOutput = m_iCommQuote;       pOutput += sizeof(short);
	*(short *)pOutput = m_iHailQuote;       pOutput += sizeof(short);
	*(short *)pOutput = m_iLinkedMission;   pOutput += sizeof(short);
	*(USHORT *)pOutput = m_iFlags1;         pOutput += sizeof(USHORT);

	memcpy(pOutput, m_szActiveOn, 256 * sizeof(char)); pOutput += 256 * sizeof(char);

	*(short *)pOutput = m_iGrantClass;      pOutput += sizeof(short);
	*(short *)pOutput = m_iGrantCount;      pOutput += sizeof(short);
	*(short *)pOutput = m_iGrantRandom;     pOutput += sizeof(short);

	ToMacString(m_szSubtitle);

	memcpy(pOutput, m_szSubtitle, 64 * sizeof(char)); pOutput += 64 * sizeof(char);

	ToWinString(m_szSubtitle);

	*(UINT  *)pOutput = m_iColor;           pOutput += sizeof(UINT);
	*(USHORT *)pOutput = m_iFlags2;         pOutput += sizeof(USHORT);

	SwapEndians();

	return 1;
}

int CPersResource::Load(char *pInput, int iSize)
{
	m_iSystem          = *(short *)pInput; pInput += sizeof(short);
	m_iGovernment      = *(short *)pInput; pInput += sizeof(short);
	m_iAIType          = *(short *)pInput; pInput += sizeof(short);
	m_iAggressiveness  = *(short *)pInput; pInput += sizeof(short);
	m_iCowardice       = *(short *)pInput; pInput += sizeof(short);
	m_iShipType        = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponTypes[0]  = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponTypes[1]  = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponTypes[2]  = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponTypes[3]  = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponCounts[0] = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponCounts[1] = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponCounts[2] = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponCounts[3] = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponAmmos[0]  = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponAmmos[1]  = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponAmmos[2]  = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponAmmos[3]  = *(short *)pInput; pInput += sizeof(short);
	m_iCredits         = *(int   *)pInput; pInput += sizeof(int);
	m_iShieldMod       = *(short *)pInput; pInput += sizeof(short);
	m_iHailPicture     = *(short *)pInput; pInput += sizeof(short);
	m_iCommQuote       = *(short *)pInput; pInput += sizeof(short);
	m_iHailQuote       = *(short *)pInput; pInput += sizeof(short);
	m_iLinkedMission   = *(short *)pInput; pInput += sizeof(short);
	m_iFlags1          = *(USHORT *)pInput; pInput += sizeof(USHORT);

	memcpy(m_szActiveOn, pInput, 256 * sizeof(char)); pInput += 256 * sizeof(char);

	m_iGrantClass      = *(short *)pInput; pInput += sizeof(short);
	m_iGrantCount      = *(short *)pInput; pInput += sizeof(short);
	m_iGrantRandom     = *(short *)pInput; pInput += sizeof(short);
	
	memcpy(m_szSubtitle, pInput, 64 * sizeof(char)); pInput += 64 * sizeof(char);

	ToWinString(m_szSubtitle);

	m_iColor           = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iFlags2          = *(USHORT *)pInput; pInput += sizeof(USHORT);

	SwapEndians();

	return 1;
}

int CPersResource::SwapEndians(void)
{
	m_iSystem          = SwapEndianShort(m_iSystem);
	m_iGovernment      = SwapEndianShort(m_iGovernment);
	m_iAIType          = SwapEndianShort(m_iAIType);
	m_iAggressiveness  = SwapEndianShort(m_iAggressiveness);
	m_iCowardice       = SwapEndianShort(m_iCowardice);
	m_iShipType        = SwapEndianShort(m_iShipType);
	m_iWeaponTypes[0]  = SwapEndianShort(m_iWeaponTypes[0]);
	m_iWeaponTypes[1]  = SwapEndianShort(m_iWeaponTypes[1]);
	m_iWeaponTypes[2]  = SwapEndianShort(m_iWeaponTypes[2]);
	m_iWeaponTypes[3]  = SwapEndianShort(m_iWeaponTypes[3]);
	m_iWeaponCounts[0] = SwapEndianShort(m_iWeaponCounts[0]);
	m_iWeaponCounts[1] = SwapEndianShort(m_iWeaponCounts[1]);
	m_iWeaponCounts[2] = SwapEndianShort(m_iWeaponCounts[2]);
	m_iWeaponCounts[3] = SwapEndianShort(m_iWeaponCounts[3]);
	m_iWeaponAmmos[0]  = SwapEndianShort(m_iWeaponAmmos[0]);
	m_iWeaponAmmos[1]  = SwapEndianShort(m_iWeaponAmmos[1]);
	m_iWeaponAmmos[2]  = SwapEndianShort(m_iWeaponAmmos[2]);
	m_iWeaponAmmos[3]  = SwapEndianShort(m_iWeaponAmmos[3]);
	m_iCredits         = SwapEndianInt(m_iCredits);
	m_iShieldMod       = SwapEndianShort(m_iShieldMod);
	m_iHailPicture     = SwapEndianShort(m_iHailPicture);
	m_iCommQuote       = SwapEndianShort(m_iCommQuote);
	m_iHailQuote       = SwapEndianShort(m_iHailQuote);
	m_iLinkedMission   = SwapEndianShort(m_iLinkedMission);
	m_iFlags1          = SwapEndianShort(m_iFlags1);
	m_iGrantClass      = SwapEndianShort(m_iGrantClass);
	m_iGrantRandom     = SwapEndianShort(m_iGrantRandom);
	m_iGrantCount      = SwapEndianShort(m_iGrantCount);
	m_iColor           = SwapEndianInt(m_iColor);
	m_iFlags2          = SwapEndianShort(m_iFlags2);

	return 1;
}

int CPersResource::SaveToText(std::ostream & output)
{
	output << m_iSystem         << '\t'
		   << m_iGovernment     << '\t'
		   << m_iAIType         << '\t'
		   << m_iAggressiveness << '\t'
		   << m_iCowardice      << '\t'
		   << m_iShipType       << '\t'
		   << m_iCredits        << '\t'
		   << m_iShieldMod      << '\t'
		   << m_iHailPicture    << '\t'
		   << m_iCommQuote      << '\t'
		   << m_iHailQuote      << '\t'
		   << m_iLinkedMission  << '\t';

	PrintTextField(output, m_szActiveOn, '\t');

	output << m_iGrantClass  << '\t'
		   << m_iGrantCount  << '\t'
		   << m_iGrantRandom << '\t';

	PrintTextField(output, m_szSubtitle, '\t');

	PrintHex32Field(output, (char *)&m_iColor, '\t');

	output << m_iWeaponTypes[0]  << '\t'
		   << m_iWeaponTypes[1]  << '\t'
		   << m_iWeaponTypes[2]  << '\t'
		   << m_iWeaponTypes[3]  << '\t'
		   << m_iWeaponCounts[0] << '\t'
		   << m_iWeaponCounts[1] << '\t'
		   << m_iWeaponCounts[2] << '\t'
		   << m_iWeaponCounts[3] << '\t'
		   << m_iWeaponAmmos[0]  << '\t'
		   << m_iWeaponAmmos[1]  << '\t'
		   << m_iWeaponAmmos[2]  << '\t'
		   << m_iWeaponAmmos[3]  << '\t';

	PrintHex16Field(output, (char *)&m_iFlags1, '\t');
	PrintHex16Field(output, (char *)&m_iFlags2, '\t');

	return 1;
}

int CPersResource::LoadFromText(std::istream & input)
{
	input >> m_iSystem
		  >> m_iGovernment
		  >> m_iAIType
		  >> m_iAggressiveness
		  >> m_iCowardice
		  >> m_iShipType
		  >> m_iCredits
		  >> m_iShieldMod
		  >> m_iHailPicture
		  >> m_iCommQuote
		  >> m_iHailQuote
		  >> m_iLinkedMission;

	input.ignore(1);

	ReadTextField(input, m_szActiveOn, 256);

	input >> m_iGrantClass
		  >> m_iGrantCount
		  >> m_iGrantRandom;

	input.ignore(1);

	ReadTextField(input, m_szSubtitle, 64);

	ReadHex32Field(input, (char *)&m_iColor);

	input >> m_iWeaponTypes[0]
		  >> m_iWeaponTypes[1]
		  >> m_iWeaponTypes[2]
		  >> m_iWeaponTypes[3]
		  >> m_iWeaponCounts[0]
		  >> m_iWeaponCounts[1]
		  >> m_iWeaponCounts[2]
		  >> m_iWeaponCounts[3]
		  >> m_iWeaponAmmos[0]
		  >> m_iWeaponAmmos[1]
		  >> m_iWeaponAmmos[2]
		  >> m_iWeaponAmmos[3];

	ReadHex16Field(input, (char *)&m_iFlags1);
	ReadHex16Field(input, (char *)&m_iFlags2);

	return 1;
}

int CPersResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "pers ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_PERS_EDIT1, CCONTROL_TYPE_INT, IDS_STRING544);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_PERS_EDIT2, CCONTROL_TYPE_INT, IDS_STRING545);
	m_controls[1].SetInt(m_iSystem);
	m_controls[2].Create(hwnd, IDC_EDIT_PERS_EDIT3, CCONTROL_TYPE_INT, IDS_STRING546);
	m_controls[2].SetInt(m_iGovernment);
	m_controls[3].Create(hwnd, IDC_EDIT_PERS_COMBO1, CCONTROL_TYPE_COMBOBOX, IDS_STRING547);
	m_controls[3].SetComboStrings(NUM_AITYPE_CHOICES, g_szAITypeChoices);
	m_controls[3].SetInt(m_iAIType - 1);
	m_controls[4].Create(hwnd, IDC_EDIT_PERS_COMBO2, CCONTROL_TYPE_COMBOBOX, IDS_STRING548);
	m_controls[4].SetComboStrings(NUM_PERS_AGGRESSION_CHOICES, g_szPersAggressionChoices);
	m_controls[4].SetInt(m_iAggressiveness - 1);
	m_controls[5].Create(hwnd, IDC_EDIT_PERS_EDIT6, CCONTROL_TYPE_INT, IDS_STRING549);
	m_controls[5].SetInt(m_iCowardice);
	m_controls[6].Create(hwnd, IDC_EDIT_PERS_EDIT7, CCONTROL_TYPE_INT, IDS_STRING550);
	m_controls[6].SetInt(m_iShipType);
	m_controls[7].Create(hwnd, IDC_EDIT_PERS_EDIT8, CCONTROL_TYPE_INT, IDS_STRING551);
	m_controls[7].SetInt(m_iWeaponTypes[0]);
	m_controls[8].Create(hwnd, IDC_EDIT_PERS_EDIT9, CCONTROL_TYPE_INT, IDS_STRING551);
	m_controls[8].SetInt(m_iWeaponTypes[1]);
	m_controls[9].Create(hwnd, IDC_EDIT_PERS_EDIT10, CCONTROL_TYPE_INT, IDS_STRING551);
	m_controls[9].SetInt(m_iWeaponTypes[2]);
	m_controls[10].Create(hwnd, IDC_EDIT_PERS_EDIT11, CCONTROL_TYPE_INT, IDS_STRING551);
	m_controls[10].SetInt(m_iWeaponTypes[3]);
	m_controls[11].Create(hwnd, IDC_EDIT_PERS_EDIT16, CCONTROL_TYPE_INT, IDS_STRING552);
	m_controls[11].SetInt(m_iWeaponCounts[0]);
	m_controls[12].Create(hwnd, IDC_EDIT_PERS_EDIT17, CCONTROL_TYPE_INT, IDS_STRING552);
	m_controls[12].SetInt(m_iWeaponCounts[1]);
	m_controls[13].Create(hwnd, IDC_EDIT_PERS_EDIT18, CCONTROL_TYPE_INT, IDS_STRING552);
	m_controls[13].SetInt(m_iWeaponCounts[2]);
	m_controls[14].Create(hwnd, IDC_EDIT_PERS_EDIT19, CCONTROL_TYPE_INT, IDS_STRING552);
	m_controls[14].SetInt(m_iWeaponCounts[3]);
	m_controls[15].Create(hwnd, IDC_EDIT_PERS_EDIT24, CCONTROL_TYPE_INT, IDS_STRING553);
	m_controls[15].SetInt(m_iWeaponAmmos[0]);
	m_controls[16].Create(hwnd, IDC_EDIT_PERS_EDIT25, CCONTROL_TYPE_INT, IDS_STRING553);
	m_controls[16].SetInt(m_iWeaponAmmos[1]);
	m_controls[17].Create(hwnd, IDC_EDIT_PERS_EDIT26, CCONTROL_TYPE_INT, IDS_STRING553);
	m_controls[17].SetInt(m_iWeaponAmmos[2]);
	m_controls[18].Create(hwnd, IDC_EDIT_PERS_EDIT27, CCONTROL_TYPE_INT, IDS_STRING553);
	m_controls[18].SetInt(m_iWeaponAmmos[3]);
	m_controls[19].Create(hwnd, IDC_EDIT_PERS_EDIT32, CCONTROL_TYPE_INT, IDS_STRING554);
	m_controls[19].SetInt(m_iCredits);
	m_controls[20].Create(hwnd, IDC_EDIT_PERS_EDIT33, CCONTROL_TYPE_INT, IDS_STRING555);
	m_controls[20].SetInt(m_iShieldMod);
	m_controls[21].Create(hwnd, IDC_EDIT_PERS_EDIT34, CCONTROL_TYPE_INT, IDS_STRING556);
	m_controls[21].SetInt(m_iHailPicture);
	m_controls[22].Create(hwnd, IDC_EDIT_PERS_EDIT35, CCONTROL_TYPE_INT, IDS_STRING557);
	m_controls[22].SetInt(m_iCommQuote);
	m_controls[23].Create(hwnd, IDC_EDIT_PERS_EDIT36, CCONTROL_TYPE_INT, IDS_STRING558);
	m_controls[23].SetInt(m_iHailQuote);
	m_controls[24].Create(hwnd, IDC_EDIT_PERS_EDIT37, CCONTROL_TYPE_INT, IDS_STRING559);
	m_controls[24].SetInt(m_iLinkedMission);
	m_controls[25].Create(hwnd, IDC_EDIT_PERS_EDIT38, CCONTROL_TYPE_STR255, IDS_STRING560);
	m_controls[25].SetString(m_szActiveOn);
	m_controls[26].Create(hwnd, IDC_EDIT_PERS_EDIT39, CCONTROL_TYPE_INT, IDS_STRING561);
	m_controls[26].SetInt(m_iGrantClass);
	m_controls[27].Create(hwnd, IDC_EDIT_PERS_EDIT41, CCONTROL_TYPE_INT, IDS_STRING563);
	m_controls[27].SetInt(m_iGrantCount);
	m_controls[28].Create(hwnd, IDC_EDIT_PERS_EDIT40, CCONTROL_TYPE_INT, IDS_STRING562);
	m_controls[28].SetInt(m_iGrantRandom);
	m_controls[29].Create(hwnd, IDC_EDIT_PERS_BUTTON1, CCONTROL_TYPE_COLOR, IDS_STRING564);
	m_controls[29].SetInt(m_iColor);
	m_controls[30].Create(hwnd, IDC_EDIT_PERS_CHECK1, CCONTROL_TYPE_CHECK, IDS_STRING565);
	m_controls[30].SetInt(m_iFlags1 & 0x0001);
	m_controls[31].Create(hwnd, IDC_EDIT_PERS_CHECK2, CCONTROL_TYPE_CHECK, IDS_STRING566);
	m_controls[31].SetInt(m_iFlags1 & 0x0002);
	m_controls[32].Create(hwnd, IDC_EDIT_PERS_CHECK3, CCONTROL_TYPE_CHECK, IDS_STRING567);
	m_controls[32].SetInt(m_iFlags1 & 0x0004);
	m_controls[33].Create(hwnd, IDC_EDIT_PERS_CHECK4, CCONTROL_TYPE_CHECK, IDS_STRING568);
	m_controls[33].SetInt(m_iFlags1 & 0x0008);
	m_controls[34].Create(hwnd, IDC_EDIT_PERS_CHECK5, CCONTROL_TYPE_CHECK, IDS_STRING569);
	m_controls[34].SetInt(m_iFlags1 & 0x0010);
	m_controls[35].Create(hwnd, IDC_EDIT_PERS_CHECK6, CCONTROL_TYPE_CHECK, IDS_STRING570);
	m_controls[35].SetInt(m_iFlags1 & 0x0020);
	m_controls[36].Create(hwnd, IDC_EDIT_PERS_CHECK7, CCONTROL_TYPE_CHECK, IDS_STRING571);
	m_controls[36].SetInt(m_iFlags1 & 0x0040);
	m_controls[37].Create(hwnd, IDC_EDIT_PERS_CHECK8, CCONTROL_TYPE_CHECK, IDS_STRING572);
	m_controls[37].SetInt(m_iFlags1 & 0x0080);
	m_controls[38].Create(hwnd, IDC_EDIT_PERS_CHECK9, CCONTROL_TYPE_CHECK, IDS_STRING573);
	m_controls[38].SetInt(m_iFlags1 & 0x0100);
	m_controls[39].Create(hwnd, IDC_EDIT_PERS_CHECK10, CCONTROL_TYPE_CHECK, IDS_STRING574);
	m_controls[39].SetInt(m_iFlags1 & 0x0200);
	m_controls[40].Create(hwnd, IDC_EDIT_PERS_CHECK11, CCONTROL_TYPE_CHECK, IDS_STRING575);
	m_controls[40].SetInt(m_iFlags1 & 0x0400);
	m_controls[41].Create(hwnd, IDC_EDIT_PERS_CHECK12, CCONTROL_TYPE_CHECK, IDS_STRING576);
	m_controls[41].SetInt(m_iFlags1 & 0x0800);
	m_controls[42].Create(hwnd, IDC_EDIT_PERS_CHECK13, CCONTROL_TYPE_CHECK, IDS_STRING577);
	m_controls[42].SetInt(m_iFlags1 & 0x1000);
	m_controls[43].Create(hwnd, IDC_EDIT_PERS_CHECK14, CCONTROL_TYPE_CHECK, IDS_STRING578);
	m_controls[43].SetInt(m_iFlags1 & 0x2000);
	m_controls[44].Create(hwnd, IDC_EDIT_PERS_CHECK15, CCONTROL_TYPE_CHECK, IDS_STRING579);
	m_controls[44].SetInt(m_iFlags1 & 0x4000);
	m_controls[45].Create(hwnd, IDC_EDIT_PERS_CHECK16, CCONTROL_TYPE_CHECK, IDS_STRING580);
	m_controls[45].SetInt(m_iFlags1 & 0x8000);
	m_controls[46].Create(hwnd, IDC_EDIT_PERS_CHECK17, CCONTROL_TYPE_CHECK, IDS_STRING581);
	m_controls[46].SetInt(m_iFlags2 & 0x0001);
	m_controls[47].Create(hwnd, IDC_EDIT_PERS_EDIT42, CCONTROL_TYPE_STR256, IDS_STRING582);
	m_controls[47].SetString(m_szName);
	m_controls[48].Create(hwnd, IDC_EDIT_PERS_EDIT43, CCONTROL_TYPE_STR64, IDS_STRING583);
	m_controls[48].SetString(m_szSubtitle);

	return 1;
}

int CPersResource::CloseAndSave(void)
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

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[47].GetString()) != 0))
		iIDOrNameChanged = 1;

	m_iID = m_controls[0].GetInt();

	m_iSystem     = m_controls[1].GetInt();
	m_iGovernment = m_controls[2].GetInt();

	m_iAIType = m_controls[3].GetInt() + 1;

	m_iAggressiveness = m_controls[4].GetInt() + 1;
	m_iCowardice      = m_controls[5].GetInt();

	m_iShipType = m_controls[6].GetInt();

	m_iWeaponTypes[0]  = m_controls[7].GetInt();
	m_iWeaponTypes[1]  = m_controls[8].GetInt();
	m_iWeaponTypes[2]  = m_controls[9].GetInt();
	m_iWeaponTypes[3]  = m_controls[10].GetInt();
	m_iWeaponCounts[0] = m_controls[11].GetInt();
	m_iWeaponCounts[1] = m_controls[12].GetInt();
	m_iWeaponCounts[2] = m_controls[13].GetInt();
	m_iWeaponCounts[3] = m_controls[14].GetInt();
	m_iWeaponAmmos[0]  = m_controls[15].GetInt();
	m_iWeaponAmmos[1]  = m_controls[16].GetInt();
	m_iWeaponAmmos[2]  = m_controls[17].GetInt();
	m_iWeaponAmmos[3]  = m_controls[18].GetInt();

	m_iCredits = m_controls[19].GetInt();

	m_iShieldMod = m_controls[20].GetInt();

	m_iHailPicture = m_controls[21].GetInt();
	m_iCommQuote   = m_controls[22].GetInt();
	m_iHailQuote   = m_controls[23].GetInt();

	m_iLinkedMission = m_controls[24].GetInt();

	strcpy_s(m_szActiveOn, m_controls[25].GetString());

	m_iGrantClass  = m_controls[26].GetInt();
	m_iGrantCount  = m_controls[27].GetInt();
	m_iGrantRandom = m_controls[28].GetInt();

	m_iColor = m_controls[29].GetInt();

	m_iFlags1 = 0x0000;
	m_iFlags2 = 0x0000;

	m_iFlags1 |= m_controls[30].GetInt() << 0;
	m_iFlags1 |= m_controls[31].GetInt() << 1;
	m_iFlags1 |= m_controls[32].GetInt() << 2;
	m_iFlags1 |= m_controls[33].GetInt() << 3;
	m_iFlags1 |= m_controls[34].GetInt() << 4;
	m_iFlags1 |= m_controls[35].GetInt() << 5;
	m_iFlags1 |= m_controls[36].GetInt() << 6;
	m_iFlags1 |= m_controls[37].GetInt() << 7;
	m_iFlags1 |= m_controls[38].GetInt() << 8;
	m_iFlags1 |= m_controls[39].GetInt() << 9;
	m_iFlags1 |= m_controls[40].GetInt() << 10;
	m_iFlags1 |= m_controls[41].GetInt() << 11;
	m_iFlags1 |= m_controls[42].GetInt() << 12;
	m_iFlags1 |= m_controls[43].GetInt() << 13;
	m_iFlags1 |= m_controls[44].GetInt() << 14;
	m_iFlags1 |= m_controls[45].GetInt() << 15;

	m_iFlags2 |= m_controls[46].GetInt() << 0;

	strcpy_s(m_szName,     m_controls[47].GetString());
	strcpy_s(m_szSubtitle, m_controls[48].GetString());

	int i;

	for(i = 0; i < NUM_PERS_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CPersResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_PERS_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CPersResource::PersDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CPersResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CPersResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_PERS_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_PERS_OK)
			{
				pResource->CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_PERS_CONTROLS; i++)
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
