// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CGovtResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CGovtResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CGovtResource::CGovtResource(void)
{
	m_iVoiceType = -1;

	m_iCrimeTolerance = 0;

	m_iFlags1 = 0x0000;
	m_iFlags2 = 0x0000;

	m_iScanFine         = 0;
	m_iSmugglingPenalty = 0;
	m_iDisablingPenalty = 0;
	m_iBoardingPenalty  = 0;
	m_iKillingPenalty   = 0;
	m_iShootingPenalty  = 0;
	m_iInitialRecord    = 0;

	m_iMaxOdds = 100;

	int i;

	for(i = 0; i < 4; i++)
	{
		m_iClasses[i] = -1;
		m_iAllies[i]  = -1;
		m_iEnemies[i] = -1;
	}

	m_iInterface   =  128;
	m_iNewsPicture = 9000;

	m_iSkillMultiplier = 100;

	for(i = 0; i < 2; i++)
		m_cScanMask[i] = 0x00;

	for(i = 0; i < 8; i++)
		m_cRequire[i] = 0x00;

	for(i = 0; i < 4; i++)
		m_iInherentJamming[i] = 0;

	memset(m_szMediumName, 0, 64 * sizeof(char));

	m_iColor     = 0x00000000;
	m_iShipColor = 0x00000000;

	memset(m_szCommName,   0, 16 * sizeof(char));
	memset(m_szTargetName, 0, 16 * sizeof(char));
}

CGovtResource::~CGovtResource(void)
{

}

int CGovtResource::GetType(void)
{
	return CNR_TYPE_GOVT;
}

int CGovtResource::GetSize(void)
{
	return 192;
}

int CGovtResource::GetDialogID(void)
{
	return IDD_EDIT_GOVT;
}

DLGPROCNOCALLBACK CGovtResource::GetDialogProc(void)
{
	return GovtDlgProc;
}

int CGovtResource::GetNumFields(void)
{
	return NUM_GOVT_FIELDS;
}

const std::string * CGovtResource::GetFieldNames(void)
{
	return g_szGovtFields;
}

int CGovtResource::Save(char *pOutput)
{
	SwapEndians();

	*(short *)pOutput = m_iVoiceType;          pOutput += sizeof(short);
	*(USHORT *)pOutput = m_iFlags1;            pOutput += sizeof(USHORT);
	*(USHORT *)pOutput = m_iFlags2;            pOutput += sizeof(USHORT);
	*(short *)pOutput = m_iScanFine;           pOutput += sizeof(short);
	*(short *)pOutput = m_iCrimeTolerance;     pOutput += sizeof(short);
	*(short *)pOutput = m_iSmugglingPenalty;   pOutput += sizeof(short);
	*(short *)pOutput = m_iDisablingPenalty;   pOutput += sizeof(short);
	*(short *)pOutput = m_iBoardingPenalty;    pOutput += sizeof(short);
	*(short *)pOutput = m_iKillingPenalty;     pOutput += sizeof(short);
	*(short *)pOutput = m_iShootingPenalty;    pOutput += sizeof(short);
	*(short *)pOutput = m_iInitialRecord;      pOutput += sizeof(short);
	*(short *)pOutput = m_iMaxOdds;            pOutput += sizeof(short);
	*(short *)pOutput = m_iClasses[0];         pOutput += sizeof(short);
	*(short *)pOutput = m_iClasses[1];         pOutput += sizeof(short);
	*(short *)pOutput = m_iClasses[2];         pOutput += sizeof(short);
	*(short *)pOutput = m_iClasses[3];         pOutput += sizeof(short);
	*(short *)pOutput = m_iAllies[0];          pOutput += sizeof(short);
	*(short *)pOutput = m_iAllies[1];          pOutput += sizeof(short);
	*(short *)pOutput = m_iAllies[2];          pOutput += sizeof(short);
	*(short *)pOutput = m_iAllies[3];          pOutput += sizeof(short);
	*(short *)pOutput = m_iEnemies[0];         pOutput += sizeof(short);
	*(short *)pOutput = m_iEnemies[1];         pOutput += sizeof(short);
	*(short *)pOutput = m_iEnemies[2];         pOutput += sizeof(short);
	*(short *)pOutput = m_iEnemies[3];         pOutput += sizeof(short);
	*(short *)pOutput = m_iSkillMultiplier;    pOutput += sizeof(short);

	ToMacString(m_szCommName);
	ToMacString(m_szTargetName);

	memcpy(pOutput, m_cScanMask,     2 * sizeof(char)); pOutput +=  2 * sizeof(char);
	memcpy(pOutput, m_szCommName,   16 * sizeof(char)); pOutput += 16 * sizeof(char);
	memcpy(pOutput, m_szTargetName, 16 * sizeof(char)); pOutput += 16 * sizeof(char);
	memcpy(pOutput, m_cRequire,      8 * sizeof(char)); pOutput +=  8 * sizeof(char);

	ToWinString(m_szCommName);
	ToWinString(m_szTargetName);

	*(short *)pOutput = m_iInherentJamming[0]; pOutput += sizeof(short);
	*(short *)pOutput = m_iInherentJamming[1]; pOutput += sizeof(short);
	*(short *)pOutput = m_iInherentJamming[2]; pOutput += sizeof(short);
	*(short *)pOutput = m_iInherentJamming[3]; pOutput += sizeof(short);

	ToMacString(m_szMediumName);

	memcpy(pOutput, m_szMediumName, 64 * sizeof(char)); pOutput += 64 * sizeof(char);

	ToWinString(m_szMediumName);

	*(UINT  *)pOutput = m_iColor;              pOutput += sizeof(UINT);
	*(UINT  *)pOutput = m_iShipColor;          pOutput += sizeof(UINT);
	*(short *)pOutput = m_iInterface;          pOutput += sizeof(short);
	*(short *)pOutput = m_iNewsPicture;        pOutput += sizeof(short);

	SwapEndians();

	return 1;
}

int CGovtResource::Load(char *pInput, int iSize)
{
	m_iVoiceType          = *(short *)pInput; pInput += sizeof(short);
	m_iFlags1             = *(short *)pInput; pInput += sizeof(USHORT);
	m_iFlags2             = *(short *)pInput; pInput += sizeof(USHORT);
	m_iScanFine           = *(short *)pInput; pInput += sizeof(short);
	m_iCrimeTolerance     = *(short *)pInput; pInput += sizeof(short);
	m_iSmugglingPenalty   = *(short *)pInput; pInput += sizeof(short);
	m_iDisablingPenalty   = *(short *)pInput; pInput += sizeof(short);
	m_iBoardingPenalty    = *(short *)pInput; pInput += sizeof(short);
	m_iKillingPenalty     = *(short *)pInput; pInput += sizeof(short);
	m_iShootingPenalty    = *(short *)pInput; pInput += sizeof(short);
	m_iInitialRecord      = *(short *)pInput; pInput += sizeof(short);
	m_iMaxOdds            = *(short *)pInput; pInput += sizeof(short);
	m_iClasses[0]         = *(short *)pInput; pInput += sizeof(short);
	m_iClasses[1]         = *(short *)pInput; pInput += sizeof(short);
	m_iClasses[2]         = *(short *)pInput; pInput += sizeof(short);
	m_iClasses[3]         = *(short *)pInput; pInput += sizeof(short);
	m_iAllies[0]          = *(short *)pInput; pInput += sizeof(short);
	m_iAllies[1]          = *(short *)pInput; pInput += sizeof(short);
	m_iAllies[2]          = *(short *)pInput; pInput += sizeof(short);
	m_iAllies[3]          = *(short *)pInput; pInput += sizeof(short);
	m_iEnemies[0]         = *(short *)pInput; pInput += sizeof(short);
	m_iEnemies[1]         = *(short *)pInput; pInput += sizeof(short);
	m_iEnemies[2]         = *(short *)pInput; pInput += sizeof(short);
	m_iEnemies[3]         = *(short *)pInput; pInput += sizeof(short);
	m_iSkillMultiplier    = *(short *)pInput; pInput += sizeof(short);

	memcpy(m_cScanMask,    pInput,  2 * sizeof(char)); pInput +=  2 * sizeof(char);
	memcpy(m_szCommName,   pInput, 16 * sizeof(char)); pInput += 16 * sizeof(char);
	memcpy(m_szTargetName, pInput, 16 * sizeof(char)); pInput += 16 * sizeof(char);
	memcpy(m_cRequire,     pInput,  8 * sizeof(char)); pInput +=  8 * sizeof(char);

	ToWinString(m_szCommName);
	ToWinString(m_szTargetName);

	m_iInherentJamming[0] = *(short *)pInput; pInput += sizeof(short);
	m_iInherentJamming[1] = *(short *)pInput; pInput += sizeof(short);
	m_iInherentJamming[2] = *(short *)pInput; pInput += sizeof(short);
	m_iInherentJamming[3] = *(short *)pInput; pInput += sizeof(short);

	memcpy(m_szMediumName, pInput, 64 * sizeof(char)); pInput += 64 * sizeof(char);

	ToWinString(m_szMediumName);

	m_iColor              = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iShipColor          = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iInterface          = *(short *)pInput; pInput += sizeof(short);
	m_iNewsPicture        = *(short *)pInput; pInput += sizeof(short);

	SwapEndians();

	return 1;
}

int CGovtResource::SwapEndians(void)
{
	m_iVoiceType          = SwapEndianShort(m_iVoiceType);
	m_iFlags1             = SwapEndianShort(m_iFlags1);
	m_iFlags2             = SwapEndianShort(m_iFlags2);
	m_iScanFine           = SwapEndianShort(m_iScanFine);
	m_iCrimeTolerance     = SwapEndianShort(m_iCrimeTolerance);
	m_iSmugglingPenalty   = SwapEndianShort(m_iSmugglingPenalty);
	m_iDisablingPenalty   = SwapEndianShort(m_iDisablingPenalty);
	m_iBoardingPenalty    = SwapEndianShort(m_iBoardingPenalty);
	m_iKillingPenalty     = SwapEndianShort(m_iKillingPenalty);
	m_iShootingPenalty    = SwapEndianShort(m_iShootingPenalty);
	m_iInitialRecord      = SwapEndianShort(m_iInitialRecord);
	m_iMaxOdds            = SwapEndianShort(m_iMaxOdds);
	m_iClasses[0]         = SwapEndianShort(m_iClasses[0]);
	m_iClasses[1]         = SwapEndianShort(m_iClasses[1]);
	m_iClasses[2]         = SwapEndianShort(m_iClasses[2]);
	m_iClasses[3]         = SwapEndianShort(m_iClasses[3]);
	m_iAllies[0]          = SwapEndianShort(m_iAllies[0]);
	m_iAllies[1]          = SwapEndianShort(m_iAllies[1]);
	m_iAllies[2]          = SwapEndianShort(m_iAllies[2]);
	m_iAllies[3]          = SwapEndianShort(m_iAllies[3]);
	m_iEnemies[0]         = SwapEndianShort(m_iEnemies[0]);
	m_iEnemies[1]         = SwapEndianShort(m_iEnemies[1]);
	m_iEnemies[2]         = SwapEndianShort(m_iEnemies[2]);
	m_iEnemies[3]         = SwapEndianShort(m_iEnemies[3]);
	m_iSkillMultiplier    = SwapEndianShort(m_iSkillMultiplier);
	m_iInherentJamming[0] = SwapEndianShort(m_iInherentJamming[0]);
	m_iInherentJamming[1] = SwapEndianShort(m_iInherentJamming[1]);
	m_iInherentJamming[2] = SwapEndianShort(m_iInherentJamming[2]);
	m_iInherentJamming[3] = SwapEndianShort(m_iInherentJamming[3]);
	m_iColor              = SwapEndianInt(m_iColor);
	m_iShipColor          = SwapEndianInt(m_iShipColor);
	m_iInterface          = SwapEndianShort(m_iInterface);
	m_iNewsPicture        = SwapEndianShort(m_iNewsPicture);

	return 1;
}

int CGovtResource::SaveToText(std::ostream & output)
{
	output << m_iVoiceType        << '\t'
		   << m_iScanFine         << '\t'
		   << m_iCrimeTolerance   << '\t'
		   << m_iSmugglingPenalty << '\t'
		   << m_iDisablingPenalty << '\t'
		   << m_iBoardingPenalty  << '\t'
		   << m_iKillingPenalty   << '\t'
		   << m_iShootingPenalty  << '\t'
		   << m_iInitialRecord    << '\t'
		   << m_iMaxOdds          << '\t'
		   << m_iClasses[0]       << '\t'
		   << m_iClasses[1]       << '\t'
		   << m_iClasses[2]       << '\t'
		   << m_iClasses[3]       << '\t'
		   << m_iAllies[0]        << '\t'
		   << m_iAllies[1]        << '\t'
		   << m_iAllies[2]        << '\t'
		   << m_iAllies[3]        << '\t'
		   << m_iEnemies[0]       << '\t'
		   << m_iEnemies[1]       << '\t'
		   << m_iEnemies[2]       << '\t'
		   << m_iEnemies[3]       << '\t'
		   << m_iInterface        << '\t'
		   << m_iNewsPicture      << '\t'
		   << m_iSkillMultiplier  << '\t';

	char c = m_cScanMask[0]; m_cScanMask[0] = m_cScanMask[1]; m_cScanMask[1] = c;

	PrintHex16Field(output, m_cScanMask, '\t');

	c = m_cScanMask[0]; m_cScanMask[0] = m_cScanMask[1]; m_cScanMask[1] = c;

	PrintHex64Field(output, m_cRequire,  '\t');

	output << m_iInherentJamming[0] << '\t'
		   << m_iInherentJamming[1] << '\t'
		   << m_iInherentJamming[2] << '\t'
		   << m_iInherentJamming[3] << '\t';

	PrintTextField(output, m_szMediumName, '\t');

	PrintHex32Field(output, (char *)&m_iColor,     '\t');
	PrintHex32Field(output, (char *)&m_iShipColor, '\t');

	PrintTextField(output, m_szCommName,   '\t');
	PrintTextField(output, m_szTargetName, '\t');

	PrintHex16Field(output, (char *)&m_iFlags1, '\t');
	PrintHex16Field(output, (char *)&m_iFlags2, '\t');

	return 1;
}

int CGovtResource::LoadFromText(std::istream & input)
{
	input >> m_iVoiceType
		  >> m_iScanFine
		  >> m_iCrimeTolerance
		  >> m_iSmugglingPenalty
		  >> m_iDisablingPenalty
		  >> m_iBoardingPenalty
		  >> m_iKillingPenalty
		  >> m_iShootingPenalty
		  >> m_iInitialRecord
		  >> m_iMaxOdds
		  >> m_iClasses[0]
		  >> m_iClasses[1]
		  >> m_iClasses[2]
		  >> m_iClasses[3]
		  >> m_iAllies[0]
		  >> m_iAllies[1]
		  >> m_iAllies[2]
		  >> m_iAllies[3]
		  >> m_iEnemies[0]
		  >> m_iEnemies[1]
		  >> m_iEnemies[2]
		  >> m_iEnemies[3]
		  >> m_iInterface
		  >> m_iNewsPicture
		  >> m_iSkillMultiplier;

	input.ignore(1);

	ReadHex16Field(input, m_cScanMask);

	char c = m_cScanMask[0]; m_cScanMask[0] = m_cScanMask[1]; m_cScanMask[1] = c;

	ReadHex64Field(input, m_cRequire);

	input >> m_iInherentJamming[0]
		  >> m_iInherentJamming[1]
		  >> m_iInherentJamming[2]
		  >> m_iInherentJamming[3];

	input.ignore(1);

	ReadTextField(input, m_szMediumName, 64);

	ReadHex32Field(input, (char *)&m_iColor);
	ReadHex32Field(input, (char *)&m_iShipColor);

	ReadTextField(input, m_szCommName,   16);
	ReadTextField(input, m_szTargetName, 16);

	ReadHex16Field(input, (char *)&m_iFlags1);
	ReadHex16Field(input, (char *)&m_iFlags2);

	return 1;
}

int CGovtResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "govt ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_GOVT_EDIT1, CCONTROL_TYPE_INT, IDS_STRING272);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_GOVT_EDIT2, CCONTROL_TYPE_INT, IDS_STRING273);
	m_controls[1].SetInt(m_iVoiceType);
	m_controls[2].Create(hwnd, IDC_EDIT_GOVT_EDIT3, CCONTROL_TYPE_INT, IDS_STRING274);
	m_controls[2].SetInt(m_iCrimeTolerance);
	m_controls[3].Create(hwnd, IDC_EDIT_GOVT_EDIT4, CCONTROL_TYPE_INT, IDS_STRING275);
	m_controls[3].SetInt(m_iScanFine);
	m_controls[4].Create(hwnd, IDC_EDIT_GOVT_EDIT5, CCONTROL_TYPE_INT, IDS_STRING276);
	m_controls[4].SetInt(m_iSmugglingPenalty);
	m_controls[5].Create(hwnd, IDC_EDIT_GOVT_EDIT6, CCONTROL_TYPE_INT, IDS_STRING277);
	m_controls[5].SetInt(m_iDisablingPenalty);
	m_controls[6].Create(hwnd, IDC_EDIT_GOVT_EDIT7, CCONTROL_TYPE_INT, IDS_STRING278);
	m_controls[6].SetInt(m_iBoardingPenalty);
	m_controls[7].Create(hwnd, IDC_EDIT_GOVT_EDIT8, CCONTROL_TYPE_INT, IDS_STRING279);
	m_controls[7].SetInt(m_iKillingPenalty);
	m_controls[8].Create(hwnd, IDC_EDIT_GOVT_EDIT9, CCONTROL_TYPE_INT, IDS_STRING280);
	m_controls[8].SetInt(m_iShootingPenalty);
	m_controls[9].Create(hwnd, IDC_EDIT_GOVT_EDIT10, CCONTROL_TYPE_INT, IDS_STRING281);
	m_controls[9].SetInt(m_iInitialRecord);
	m_controls[10].Create(hwnd, IDC_EDIT_GOVT_EDIT11, CCONTROL_TYPE_INT, IDS_STRING282);
	m_controls[10].SetInt(m_iMaxOdds);
	m_controls[11].Create(hwnd, IDC_EDIT_GOVT_EDIT12, CCONTROL_TYPE_INT, IDS_STRING283);
	m_controls[11].SetInt(m_iClasses[0]);
	m_controls[12].Create(hwnd, IDC_EDIT_GOVT_EDIT13, CCONTROL_TYPE_INT, IDS_STRING283);
	m_controls[12].SetInt(m_iClasses[1]);
	m_controls[13].Create(hwnd, IDC_EDIT_GOVT_EDIT14, CCONTROL_TYPE_INT, IDS_STRING283);
	m_controls[13].SetInt(m_iClasses[2]);
	m_controls[14].Create(hwnd, IDC_EDIT_GOVT_EDIT15, CCONTROL_TYPE_INT, IDS_STRING283);
	m_controls[14].SetInt(m_iClasses[3]);
	m_controls[15].Create(hwnd, IDC_EDIT_GOVT_EDIT16, CCONTROL_TYPE_INT, IDS_STRING284);
	m_controls[15].SetInt(m_iAllies[0]);
	m_controls[16].Create(hwnd, IDC_EDIT_GOVT_EDIT17, CCONTROL_TYPE_INT, IDS_STRING284);
	m_controls[16].SetInt(m_iAllies[1]);
	m_controls[17].Create(hwnd, IDC_EDIT_GOVT_EDIT18, CCONTROL_TYPE_INT, IDS_STRING284);
	m_controls[17].SetInt(m_iAllies[2]);
	m_controls[18].Create(hwnd, IDC_EDIT_GOVT_EDIT19, CCONTROL_TYPE_INT, IDS_STRING284);
	m_controls[18].SetInt(m_iAllies[3]);
	m_controls[19].Create(hwnd, IDC_EDIT_GOVT_EDIT20, CCONTROL_TYPE_INT, IDS_STRING285);
	m_controls[19].SetInt(m_iEnemies[0]);
	m_controls[20].Create(hwnd, IDC_EDIT_GOVT_EDIT21, CCONTROL_TYPE_INT, IDS_STRING285);
	m_controls[20].SetInt(m_iEnemies[1]);
	m_controls[21].Create(hwnd, IDC_EDIT_GOVT_EDIT22, CCONTROL_TYPE_INT, IDS_STRING285);
	m_controls[21].SetInt(m_iEnemies[2]);
	m_controls[22].Create(hwnd, IDC_EDIT_GOVT_EDIT23, CCONTROL_TYPE_INT, IDS_STRING285);
	m_controls[22].SetInt(m_iEnemies[3]);
	m_controls[23].Create(hwnd, IDC_EDIT_GOVT_EDIT24, CCONTROL_TYPE_INT, IDS_STRING286);
	m_controls[23].SetInt(m_iInterface);
	m_controls[24].Create(hwnd, IDC_EDIT_GOVT_EDIT25, CCONTROL_TYPE_INT, IDS_STRING287);
	m_controls[24].SetInt(m_iNewsPicture);
	m_controls[25].Create(hwnd, IDC_EDIT_GOVT_EDIT26, CCONTROL_TYPE_INT, IDS_STRING288);
	m_controls[25].SetInt(m_iSkillMultiplier);
	m_controls[26].Create(hwnd, IDC_EDIT_GOVT_EDIT27, CCONTROL_TYPE_HEXINT16, IDS_STRING289);
	m_controls[26].SetString(m_cScanMask);
	m_controls[27].Create(hwnd, IDC_EDIT_GOVT_EDIT28, CCONTROL_TYPE_HEXINT64, IDS_STRING290);
	m_controls[27].SetString(m_cRequire);
	m_controls[28].Create(hwnd, IDC_EDIT_GOVT_EDIT29, CCONTROL_TYPE_INT, IDS_STRING291);
	m_controls[28].SetInt(m_iInherentJamming[0]);
	m_controls[29].Create(hwnd, IDC_EDIT_GOVT_EDIT30, CCONTROL_TYPE_INT, IDS_STRING291);
	m_controls[29].SetInt(m_iInherentJamming[1]);
	m_controls[30].Create(hwnd, IDC_EDIT_GOVT_EDIT31, CCONTROL_TYPE_INT, IDS_STRING291);
	m_controls[30].SetInt(m_iInherentJamming[2]);
	m_controls[31].Create(hwnd, IDC_EDIT_GOVT_EDIT32, CCONTROL_TYPE_INT, IDS_STRING291);
	m_controls[31].SetInt(m_iInherentJamming[3]);
	m_controls[32].Create(hwnd, IDC_EDIT_GOVT_EDIT33, CCONTROL_TYPE_STR64, IDS_STRING292);
	m_controls[32].SetString(m_szMediumName);
	m_controls[33].Create(hwnd, IDC_EDIT_GOVT_BUTTON34, CCONTROL_TYPE_COLOR, IDS_STRING293);
	m_controls[33].SetInt(m_iColor);
	m_controls[34].Create(hwnd, IDC_EDIT_GOVT_BUTTON35, CCONTROL_TYPE_COLOR, IDS_STRING294);
	m_controls[34].SetInt(m_iShipColor);
	m_controls[35].Create(hwnd, IDC_EDIT_GOVT_EDIT36, CCONTROL_TYPE_STR16, IDS_STRING295);
	m_controls[35].SetString(m_szCommName);
	m_controls[36].Create(hwnd, IDC_EDIT_GOVT_EDIT37, CCONTROL_TYPE_STR16, IDS_STRING296);
	m_controls[36].SetString(m_szTargetName);
	m_controls[37].Create(hwnd, IDC_EDIT_GOVT_CHECK1, CCONTROL_TYPE_CHECK, IDS_STRING297);
	m_controls[37].SetInt(m_iFlags1 & 0x0001);
	m_controls[38].Create(hwnd, IDC_EDIT_GOVT_CHECK2, CCONTROL_TYPE_CHECK, IDS_STRING298);
	m_controls[38].SetInt(m_iFlags1 & 0x0002);
	m_controls[39].Create(hwnd, IDC_EDIT_GOVT_CHECK3, CCONTROL_TYPE_CHECK, IDS_STRING299);
	m_controls[39].SetInt(m_iFlags1 & 0x0004);
	m_controls[40].Create(hwnd, IDC_EDIT_GOVT_CHECK4, CCONTROL_TYPE_CHECK, IDS_STRING300);
	m_controls[40].SetInt(m_iFlags1 & 0x0008);
	m_controls[41].Create(hwnd, IDC_EDIT_GOVT_CHECK5, CCONTROL_TYPE_CHECK, IDS_STRING301);
	m_controls[41].SetInt(m_iFlags1 & 0x0010);
	m_controls[42].Create(hwnd, IDC_EDIT_GOVT_CHECK6, CCONTROL_TYPE_CHECK, IDS_STRING302);
	m_controls[42].SetInt(m_iFlags1 & 0x0020);
	m_controls[43].Create(hwnd, IDC_EDIT_GOVT_CHECK7, CCONTROL_TYPE_CHECK, IDS_STRING303);
	m_controls[43].SetInt(m_iFlags1 & 0x0040);
	m_controls[44].Create(hwnd, IDC_EDIT_GOVT_CHECK8, CCONTROL_TYPE_CHECK, IDS_STRING304);
	m_controls[44].SetInt(m_iFlags1 & 0x0080);
	m_controls[45].Create(hwnd, IDC_EDIT_GOVT_CHECK9, CCONTROL_TYPE_CHECK, IDS_STRING305);
	m_controls[45].SetInt(m_iFlags1 & 0x0100);
	m_controls[46].Create(hwnd, IDC_EDIT_GOVT_CHECK10, CCONTROL_TYPE_CHECK, IDS_STRING306);
	m_controls[46].SetInt(m_iFlags1 & 0x0200);
	m_controls[47].Create(hwnd, IDC_EDIT_GOVT_CHECK11, CCONTROL_TYPE_CHECK, IDS_STRING307);
	m_controls[47].SetInt(m_iFlags1 & 0x0400);
	m_controls[48].Create(hwnd, IDC_EDIT_GOVT_CHECK12, CCONTROL_TYPE_CHECK, IDS_STRING308);
	m_controls[48].SetInt(m_iFlags1 & 0x0800);
	m_controls[49].Create(hwnd, IDC_EDIT_GOVT_CHECK13, CCONTROL_TYPE_CHECK, IDS_STRING309);
	m_controls[49].SetInt(m_iFlags1 & 0x1000);
	m_controls[50].Create(hwnd, IDC_EDIT_GOVT_CHECK14, CCONTROL_TYPE_CHECK, IDS_STRING310);
	m_controls[50].SetInt(m_iFlags1 & 0x2000);
	m_controls[51].Create(hwnd, IDC_EDIT_GOVT_CHECK15, CCONTROL_TYPE_CHECK, IDS_STRING311);
	m_controls[51].SetInt(m_iFlags1 & 0x4000);
	m_controls[52].Create(hwnd, IDC_EDIT_GOVT_CHECK16, CCONTROL_TYPE_CHECK, IDS_STRING312);
	m_controls[52].SetInt(m_iFlags1 & 0x8000);
	m_controls[53].Create(hwnd, IDC_EDIT_GOVT_CHECK17, CCONTROL_TYPE_CHECK, IDS_STRING313);
	m_controls[53].SetInt(m_iFlags2 & 0x0001);
	m_controls[54].Create(hwnd, IDC_EDIT_GOVT_CHECK18, CCONTROL_TYPE_CHECK, IDS_STRING314);
	m_controls[54].SetInt(m_iFlags2 & 0x0002);
	m_controls[55].Create(hwnd, IDC_EDIT_GOVT_CHECK19, CCONTROL_TYPE_CHECK, IDS_STRING315);
	m_controls[55].SetInt(m_iFlags2 & 0x0004);
	m_controls[56].Create(hwnd, IDC_EDIT_GOVT_CHECK20, CCONTROL_TYPE_CHECK, IDS_STRING316);
	m_controls[56].SetInt(m_iFlags2 & 0x0008);
	m_controls[57].Create(hwnd, IDC_EDIT_GOVT_CHECK21, CCONTROL_TYPE_CHECK, IDS_STRING317);
	m_controls[57].SetInt(m_iFlags2 & 0x0010);
	m_controls[58].Create(hwnd, IDC_EDIT_GOVT_CHECK22, CCONTROL_TYPE_CHECK, IDS_STRING318);
	m_controls[58].SetInt(m_iFlags2 & 0x0020);
	m_controls[59].Create(hwnd, IDC_EDIT_GOVT_CHECK23, CCONTROL_TYPE_CHECK, IDS_STRING319);
	m_controls[59].SetInt(m_iFlags2 & 0x0040);
	m_controls[60].Create(hwnd, IDC_EDIT_GOVT_CHECK24, CCONTROL_TYPE_CHECK, IDS_STRING320);
	m_controls[60].SetInt(m_iFlags2 & 0x0080);
	m_controls[61].Create(hwnd, IDC_EDIT_GOVT_EDIT34, CCONTROL_TYPE_STR256, IDS_STRING321);
	m_controls[61].SetString(m_szName);

	return 1;
}

int CGovtResource::CloseAndSave(void)
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

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[61].GetString()) != 0))
		iIDOrNameChanged = 1;

	m_iID = m_controls[0].GetInt();

	m_iVoiceType = m_controls[1].GetInt();

	m_iCrimeTolerance   = m_controls[2].GetInt();
	m_iScanFine         = m_controls[3].GetInt();
	m_iSmugglingPenalty = m_controls[4].GetInt();
	m_iDisablingPenalty = m_controls[5].GetInt();
	m_iBoardingPenalty  = m_controls[6].GetInt();
	m_iKillingPenalty   = m_controls[7].GetInt();
	m_iShootingPenalty  = m_controls[8].GetInt();
	m_iInitialRecord    = m_controls[9].GetInt();

	m_iMaxOdds = m_controls[10].GetInt();

	m_iClasses[0] = m_controls[11].GetInt();
	m_iClasses[1] = m_controls[12].GetInt();
	m_iClasses[2] = m_controls[13].GetInt();
	m_iClasses[3] = m_controls[14].GetInt();
	m_iAllies[0]  = m_controls[15].GetInt();
	m_iAllies[1]  = m_controls[16].GetInt();
	m_iAllies[2]  = m_controls[17].GetInt();
	m_iAllies[3]  = m_controls[18].GetInt();
	m_iEnemies[0] = m_controls[19].GetInt();
	m_iEnemies[1] = m_controls[20].GetInt();
	m_iEnemies[2] = m_controls[21].GetInt();
	m_iEnemies[3] = m_controls[22].GetInt();

	m_iInterface   = m_controls[23].GetInt();
	m_iNewsPicture = m_controls[24].GetInt();

	m_iSkillMultiplier = m_controls[25].GetInt();

	strcpy(m_cScanMask, m_controls[26].GetString());
	strcpy(m_cRequire,  m_controls[27].GetString());

	m_iInherentJamming[0] = m_controls[28].GetInt();
	m_iInherentJamming[1] = m_controls[29].GetInt();
	m_iInherentJamming[2] = m_controls[30].GetInt();
	m_iInherentJamming[3] = m_controls[31].GetInt();

	strcpy(m_szMediumName, m_controls[32].GetString());

	m_iColor     = m_controls[33].GetInt();
	m_iShipColor = m_controls[34].GetInt();

	strcpy(m_szCommName,   m_controls[35].GetString());
	strcpy(m_szTargetName, m_controls[36].GetString());

	m_iFlags1 = 0x0000;
	m_iFlags2 = 0x0000;

	m_iFlags1 |= m_controls[37].GetInt() << 0;
	m_iFlags1 |= m_controls[38].GetInt() << 1;
	m_iFlags1 |= m_controls[39].GetInt() << 2;
	m_iFlags1 |= m_controls[40].GetInt() << 3;
	m_iFlags1 |= m_controls[41].GetInt() << 4;
	m_iFlags1 |= m_controls[42].GetInt() << 5;
	m_iFlags1 |= m_controls[43].GetInt() << 6;
	m_iFlags1 |= m_controls[44].GetInt() << 7;
	m_iFlags1 |= m_controls[45].GetInt() << 8;
	m_iFlags1 |= m_controls[46].GetInt() << 9;
	m_iFlags1 |= m_controls[47].GetInt() << 10;
	m_iFlags1 |= m_controls[48].GetInt() << 11;
	m_iFlags1 |= m_controls[49].GetInt() << 12;
	m_iFlags1 |= m_controls[50].GetInt() << 13;
	m_iFlags1 |= m_controls[51].GetInt() << 14;
	m_iFlags1 |= m_controls[52].GetInt() << 15;

	m_iFlags2 |= m_controls[53].GetInt() << 0;
	m_iFlags2 |= m_controls[54].GetInt() << 1;
	m_iFlags2 |= m_controls[55].GetInt() << 2;
	m_iFlags2 |= m_controls[56].GetInt() << 3;
	m_iFlags2 |= m_controls[57].GetInt() << 4;
	m_iFlags2 |= m_controls[58].GetInt() << 5;
	m_iFlags2 |= m_controls[59].GetInt() << 6;
	m_iFlags2 |= m_controls[60].GetInt() << 7;

	strcpy(m_szName, m_controls[61].GetString());

	int i;

	for(i = 0; i < NUM_GOVT_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CGovtResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_GOVT_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CGovtResource::GovtDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CGovtResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CGovtResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_GOVT_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_GOVT_OK)
			{
				pResource->CloseAndSave();
			}
			else if(iControlID == IDC_EDIT_GOVT_BUTTON1)
			{
				char cValue[2];

				memcpy(cValue, pResource->m_controls[26].GetString(), 2);

				pResource->m_bitFieldControl.DoDialog(pResource->m_pWindow, 16, cValue);

				pResource->m_controls[26].SetString(cValue);
			}
			else if(iControlID == IDC_EDIT_GOVT_BUTTON2)
			{
				char cValue[8];

				memcpy(cValue, pResource->m_controls[27].GetString(), 8);

				pResource->m_bitFieldControl.DoDialog(pResource->m_pWindow, 64, cValue);

				pResource->m_controls[27].SetString(cValue);
			}
			else
			{
				for(i = 0; i < NUM_GOVT_CONTROLS; i++)
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
