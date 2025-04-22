// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CMisnResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CMisnResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CMisnResource::CMisnResource(void)
{
	m_iAvailableStellar  =  -1;
	m_iAvailableLocation =   1;
	m_iAvailableRecord   =   0;
	m_iAvailableRating   =  -1;
	m_iAvailableRandom   = 100;

	m_iTravelStellar = -1;
	m_iReturnStellar = -1;

	m_iCargoType    = -1;
	m_iCargoAmount  = -1;
	m_iCargoPickup  = -1;
	m_iCargoDropoff = -1;

	int i;

	for(i = 0; i < 2; i++)
		m_cScanMask[i] = 0x00;

	m_iPayValue = 0;

	m_iShipCount    = -1;
	m_iShipSystem   = -1;
	m_iShipDude     = -1;
	m_iShipGoal     = -1;
	m_iShipBehavior = -1;
	m_iShipName     = -1;
	m_iShipStart    =  0;

	m_iCompletionGovernment = 196;
	m_iCompletionReward     =  1;

	m_iShipSubtitle = -1;

	m_iBriefingDesc     = -1;
	m_iQuickBriefDesc   = -1;
	m_iLoadCargoDesc    = -1;
	m_iDropoffCargoDesc = -1;
	m_iCompletionDesc   = -1;
	m_iFailDesc         = -1;
	m_iShipDoneDesc     = -1;

	m_iCanAbort = 1;

	m_iTimeLimit = -1;

	m_iAuxShipCount = -1;
	m_iAuxShipDude  = -1;
	m_iAuxShipSyst  = -1;

	m_iFlags1 = 0x0000;
	m_iFlags2 = 0x0000;

	m_iAvailableShipType = -1;

	m_iRefuseDesc = -1;

	memset(m_szAvailableBits, 0, 255 * sizeof(char));
	memset(m_szOnAccept,      0, 255 * sizeof(char));
	memset(m_szOnRefuse,      0, 255 * sizeof(char));
	memset(m_szOnSuccess,     0, 255 * sizeof(char));
	memset(m_szOnFailure,     0, 255 * sizeof(char));
	memset(m_szOnAbort,       0, 255 * sizeof(char));
	memset(m_szOnShipDone,    0, 255 * sizeof(char));

	for(i = 0; i < 8; i++)
		m_cRequire[i] = 0x00;

	m_iDateIncrement = 0;

	memset(m_szAcceptButton, 0, 32 * sizeof(char));
	memset(m_szRefuseButton, 0, 33 * sizeof(char));

	m_iDisplayWeight = 0;
}

CMisnResource::~CMisnResource(void)
{

}

int CMisnResource::GetType(void)
{
	return CNR_TYPE_MISN;
}

int CMisnResource::GetSize(void)
{
	return 1970;
}

int CMisnResource::GetDialogID(void)
{
	return IDD_EDIT_MISN;
}

DLGPROCNOCALLBACK CMisnResource::GetDialogProc(void)
{
	return MisnDlgProc;
}

int CMisnResource::GetNumFields(void)
{
	return NUM_MISN_FIELDS;
}

const std::string * CMisnResource::GetFieldNames(void)
{
	return g_szMisnFields;
}

int CMisnResource::Save(char *pOutput)
{
	SwapEndians();

	*(short *)pOutput = m_iAvailableStellar;     pOutput += sizeof(short); pOutput += 2 * sizeof(char);
	*(short *)pOutput = m_iAvailableLocation;    pOutput += sizeof(short);
	*(short *)pOutput = m_iAvailableRecord;      pOutput += sizeof(short);
	*(short *)pOutput = m_iAvailableRating;      pOutput += sizeof(short);
	*(short *)pOutput = m_iAvailableRandom;      pOutput += sizeof(short);
	*(short *)pOutput = m_iTravelStellar;        pOutput += sizeof(short);
	*(short *)pOutput = m_iReturnStellar;        pOutput += sizeof(short);
	*(short *)pOutput = m_iCargoType;            pOutput += sizeof(short);
	*(short *)pOutput = m_iCargoAmount;          pOutput += sizeof(short);
	*(short *)pOutput = m_iCargoPickup;          pOutput += sizeof(short);
	*(short *)pOutput = m_iCargoDropoff;         pOutput += sizeof(short);

	memcpy(pOutput, m_cScanMask, 2 * sizeof(char)); pOutput += 2 * sizeof(char); pOutput += 2 * sizeof(char);

	*(int   *)pOutput = m_iPayValue;             pOutput += sizeof(int);
	*(short *)pOutput = m_iShipCount;            pOutput += sizeof(short);
	*(short *)pOutput = m_iShipSystem;           pOutput += sizeof(short);
	*(short *)pOutput = m_iShipDude;             pOutput += sizeof(short);
	*(short *)pOutput = m_iShipGoal;             pOutput += sizeof(short);
	*(short *)pOutput = m_iShipBehavior;         pOutput += sizeof(short);
	*(short *)pOutput = m_iShipName;             pOutput += sizeof(short);
	*(short *)pOutput = m_iShipStart;            pOutput += sizeof(short);
	*(short *)pOutput = m_iCompletionGovernment; pOutput += sizeof(short);
	*(short *)pOutput = m_iCompletionReward;     pOutput += sizeof(short);
	*(short *)pOutput = m_iShipSubtitle;         pOutput += sizeof(short);
	*(short *)pOutput = m_iBriefingDesc;         pOutput += sizeof(short);
	*(short *)pOutput = m_iQuickBriefDesc;       pOutput += sizeof(short);
	*(short *)pOutput = m_iLoadCargoDesc;        pOutput += sizeof(short);
	*(short *)pOutput = m_iDropoffCargoDesc;     pOutput += sizeof(short);
	*(short *)pOutput = m_iCompletionDesc;       pOutput += sizeof(short);
	*(short *)pOutput = m_iFailDesc;             pOutput += sizeof(short);
	*(short *)pOutput = m_iTimeLimit;            pOutput += sizeof(short);
	*(short *)pOutput = m_iCanAbort;             pOutput += sizeof(short);
	*(short *)pOutput = m_iShipDoneDesc;         pOutput += sizeof(short); pOutput += 2 * sizeof(char);
	*(short *)pOutput = m_iAuxShipCount;         pOutput += sizeof(short);
	*(short *)pOutput = m_iAuxShipDude;          pOutput += sizeof(short);
	*(short *)pOutput = m_iAuxShipSyst;          pOutput += sizeof(short); pOutput += 2 * sizeof(char);
	*(USHORT *)pOutput = m_iFlags1;              pOutput += sizeof(USHORT);
	*(USHORT *)pOutput = m_iFlags2;              pOutput += sizeof(USHORT); pOutput += 4 * sizeof(char);
	*(short *)pOutput = m_iRefuseDesc;           pOutput += sizeof(short);
	*(short *)pOutput = m_iAvailableShipType;    pOutput += sizeof(short);

	memcpy(pOutput, m_szAvailableBits, 255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_szOnAccept,      255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_szOnRefuse,      255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_szOnSuccess,     255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_szOnFailure,     255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_szOnAbort,       255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_cRequire,          8 * sizeof(char)); pOutput +=   8 * sizeof(char);

	*(short *)pOutput = m_iDateIncrement;        pOutput += sizeof(short);

	ToMacString(m_szAcceptButton);
	ToMacString(m_szRefuseButton);

	memcpy(pOutput, m_szOnShipDone,  255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_szAcceptButton, 32 * sizeof(char)); pOutput +=  32 * sizeof(char);
	memcpy(pOutput, m_szRefuseButton, 33 * sizeof(char)); pOutput +=  33 * sizeof(char);

	ToWinString(m_szAcceptButton);
	ToWinString(m_szRefuseButton);

	*(short *)pOutput = m_iDisplayWeight;        pOutput += sizeof(short);

	SwapEndians();

	return 1;
}

int CMisnResource::Load(char *pInput, int iSize)
{
	m_iAvailableStellar     = *(short *)pInput; pInput += sizeof(short); pInput += 2 * sizeof(char);
	m_iAvailableLocation    = *(short *)pInput; pInput += sizeof(short);
	m_iAvailableRecord      = *(short *)pInput; pInput += sizeof(short);
	m_iAvailableRating      = *(short *)pInput; pInput += sizeof(short);
	m_iAvailableRandom      = *(short *)pInput; pInput += sizeof(short);
	m_iTravelStellar        = *(short *)pInput; pInput += sizeof(short);
	m_iReturnStellar        = *(short *)pInput; pInput += sizeof(short);
	m_iCargoType            = *(short *)pInput; pInput += sizeof(short);
	m_iCargoAmount          = *(short *)pInput; pInput += sizeof(short);
	m_iCargoPickup          = *(short *)pInput; pInput += sizeof(short);
	m_iCargoDropoff         = *(short *)pInput; pInput += sizeof(short);

	memcpy(m_cScanMask, pInput, 2 * sizeof(char)); pInput += 2 * sizeof(char); pInput += 2 * sizeof(char);

	m_iPayValue             = *(int   *)pInput; pInput += sizeof(int);
	m_iShipCount            = *(short *)pInput; pInput += sizeof(short);
	m_iShipSystem           = *(short *)pInput; pInput += sizeof(short);
	m_iShipDude             = *(short *)pInput; pInput += sizeof(short);
	m_iShipGoal             = *(short *)pInput; pInput += sizeof(short);
	m_iShipBehavior         = *(short *)pInput; pInput += sizeof(short);
	m_iShipName             = *(short *)pInput; pInput += sizeof(short);
	m_iShipStart            = *(short *)pInput; pInput += sizeof(short);
	m_iCompletionGovernment = *(short *)pInput; pInput += sizeof(short);
	m_iCompletionReward     = *(short *)pInput; pInput += sizeof(short);
	m_iShipSubtitle         = *(short *)pInput; pInput += sizeof(short);
	m_iBriefingDesc         = *(short *)pInput; pInput += sizeof(short);
	m_iQuickBriefDesc       = *(short *)pInput; pInput += sizeof(short);
	m_iLoadCargoDesc        = *(short *)pInput; pInput += sizeof(short);
	m_iDropoffCargoDesc     = *(short *)pInput; pInput += sizeof(short);
	m_iCompletionDesc       = *(short *)pInput; pInput += sizeof(short);
	m_iFailDesc             = *(short *)pInput; pInput += sizeof(short);
	m_iTimeLimit            = *(short *)pInput; pInput += sizeof(short);
	m_iCanAbort             = *(short *)pInput; pInput += sizeof(short);
	m_iShipDoneDesc         = *(short *)pInput; pInput += sizeof(short); pInput += 2 * sizeof(char);
	m_iAuxShipCount         = *(short *)pInput; pInput += sizeof(short);
	m_iAuxShipDude          = *(short *)pInput; pInput += sizeof(short);
	m_iAuxShipSyst          = *(short *)pInput; pInput += sizeof(short); pInput += 2 * sizeof(char);
	m_iFlags1               = *(USHORT *)pInput; pInput += sizeof(USHORT);
	m_iFlags2               = *(USHORT *)pInput; pInput += sizeof(USHORT); pInput += 4 * sizeof(char);
	m_iRefuseDesc           = *(short *)pInput; pInput += sizeof(short);
	m_iAvailableShipType    = *(short *)pInput; pInput += sizeof(short);

	memcpy(m_szAvailableBits, pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	memcpy(m_szOnAccept,      pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	memcpy(m_szOnRefuse,      pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	memcpy(m_szOnSuccess,     pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	memcpy(m_szOnFailure,     pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	memcpy(m_szOnAbort,       pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	memcpy(m_cRequire,        pInput,   8 * sizeof(char)); pInput +=   8 * sizeof(char);

	m_iDateIncrement        = *(short *)pInput; pInput += sizeof(short);

	memcpy(m_szOnShipDone,   pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	memcpy(m_szAcceptButton, pInput,  32 * sizeof(char)); pInput +=  32 * sizeof(char);
	memcpy(m_szRefuseButton, pInput,  33 * sizeof(char)); pInput +=  33 * sizeof(char);

	ToWinString(m_szAcceptButton);
	ToWinString(m_szRefuseButton);

	m_iDisplayWeight        = *(short *)pInput; pInput += sizeof(short);

	SwapEndians();

	return 1;
}

int CMisnResource::SwapEndians(void)
{
	m_iAvailableStellar     = SwapEndianShort(m_iAvailableStellar);
	m_iAvailableLocation    = SwapEndianShort(m_iAvailableLocation);
	m_iAvailableRecord      = SwapEndianShort(m_iAvailableRecord);
	m_iAvailableRating      = SwapEndianShort(m_iAvailableRating);
	m_iAvailableRandom      = SwapEndianShort(m_iAvailableRandom);
	m_iTravelStellar        = SwapEndianShort(m_iTravelStellar);
	m_iReturnStellar        = SwapEndianShort(m_iReturnStellar);
	m_iCargoType            = SwapEndianShort(m_iCargoType);
	m_iCargoAmount          = SwapEndianShort(m_iCargoAmount);
	m_iCargoPickup          = SwapEndianShort(m_iCargoPickup);
	m_iCargoDropoff         = SwapEndianShort(m_iCargoDropoff);
	m_iPayValue             = SwapEndianInt(m_iPayValue);
	m_iShipCount            = SwapEndianShort(m_iShipCount);
	m_iShipSystem           = SwapEndianShort(m_iShipSystem);
	m_iShipDude             = SwapEndianShort(m_iShipDude);
	m_iShipGoal             = SwapEndianShort(m_iShipGoal);
	m_iShipBehavior         = SwapEndianShort(m_iShipBehavior);
	m_iShipName             = SwapEndianShort(m_iShipName);
	m_iShipStart            = SwapEndianShort(m_iShipStart);
	m_iCompletionGovernment = SwapEndianShort(m_iCompletionGovernment);
	m_iCompletionReward     = SwapEndianShort(m_iCompletionReward);
	m_iShipSubtitle         = SwapEndianShort(m_iShipSubtitle);
	m_iBriefingDesc         = SwapEndianShort(m_iBriefingDesc);
	m_iQuickBriefDesc       = SwapEndianShort(m_iQuickBriefDesc);
	m_iLoadCargoDesc        = SwapEndianShort(m_iLoadCargoDesc);
	m_iDropoffCargoDesc     = SwapEndianShort(m_iDropoffCargoDesc);
	m_iCompletionDesc       = SwapEndianShort(m_iCompletionDesc);
	m_iFailDesc             = SwapEndianShort(m_iFailDesc);
	m_iTimeLimit            = SwapEndianShort(m_iTimeLimit);
	m_iCanAbort             = SwapEndianShort(m_iCanAbort);
	m_iShipDoneDesc         = SwapEndianShort(m_iShipDoneDesc);
	m_iAuxShipCount         = SwapEndianShort(m_iAuxShipCount);
	m_iAuxShipDude          = SwapEndianShort(m_iAuxShipDude);
	m_iAuxShipSyst          = SwapEndianShort(m_iAuxShipSyst);
	m_iFlags1               = SwapEndianShort(m_iFlags1);
	m_iFlags2               = SwapEndianShort(m_iFlags2);
	m_iRefuseDesc           = SwapEndianShort(m_iRefuseDesc);
	m_iAvailableShipType    = SwapEndianShort(m_iAvailableShipType);
	m_iDateIncrement        = SwapEndianShort(m_iDateIncrement);
	m_iDisplayWeight        = SwapEndianShort(m_iDisplayWeight);

	return 1;
}

int CMisnResource::SaveToText(std::ostream & output)
{
	output << m_iAvailableStellar  << '\t'
		   << m_iAvailableLocation << '\t'
		   << m_iAvailableRecord   << '\t'
		   << m_iAvailableRating   << '\t'
		   << m_iAvailableRandom   << '\t'
		   << m_iTravelStellar     << '\t'
		   << m_iReturnStellar     << '\t'
		   << m_iCargoType         << '\t'
		   << m_iCargoAmount       << '\t'
		   << m_iCargoPickup       << '\t'
		   << m_iCargoDropoff      << '\t';

	char c = m_cScanMask[0]; m_cScanMask[0] = m_cScanMask[1]; m_cScanMask[1] = c;

	PrintHex16Field(output, m_cScanMask, '\t');

	c = m_cScanMask[0]; m_cScanMask[0] = m_cScanMask[1]; m_cScanMask[1] = c;

	output << m_iPayValue             << '\t'
		   << m_iShipCount            << '\t'
		   << m_iShipSystem           << '\t'
		   << m_iShipDude             << '\t'
		   << m_iShipGoal             << '\t'
		   << m_iShipBehavior         << '\t'
		   << m_iShipName             << '\t'
		   << m_iShipStart            << '\t'
		   << m_iCompletionGovernment << '\t'
		   << m_iCompletionReward     << '\t'
		   << m_iShipSubtitle         << '\t'
		   << m_iBriefingDesc         << '\t'
		   << m_iQuickBriefDesc       << '\t'
		   << m_iLoadCargoDesc        << '\t'
		   << m_iDropoffCargoDesc     << '\t'
		   << m_iCompletionDesc       << '\t'
		   << m_iFailDesc             << '\t'
		   << m_iShipDoneDesc         << '\t'
		   << m_iRefuseDesc           << '\t'
		   << m_iTimeLimit            << '\t'
		   << m_iAuxShipCount         << '\t'
		   << m_iAuxShipDude          << '\t'
		   << m_iAuxShipSyst          << '\t'
		   << m_iAvailableShipType    << '\t';

	PrintTextField(output, m_szAvailableBits, '\t');
	PrintTextField(output, m_szOnAccept,      '\t');
	PrintTextField(output, m_szOnRefuse,      '\t');
	PrintTextField(output, m_szOnSuccess,     '\t');
	PrintTextField(output, m_szOnFailure,     '\t');
	PrintTextField(output, m_szOnAbort,       '\t');
	PrintTextField(output, m_szOnShipDone,    '\t');

	PrintHex64Field(output, m_cRequire, '\t');

	output << m_iDateIncrement << '\t';

	PrintTextField(output, m_szAcceptButton, '\t');
	PrintTextField(output, m_szRefuseButton, '\t');

	output << m_iDisplayWeight << '\t'
		   << m_iCanAbort      << '\t';

	PrintHex16Field(output, (char *)&m_iFlags1, '\t');
	PrintHex16Field(output, (char *)&m_iFlags2, '\t');

	return 1;
}

int CMisnResource::LoadFromText(std::istream & input)
{
	input >> m_iAvailableStellar
		  >> m_iAvailableLocation
		  >> m_iAvailableRecord
		  >> m_iAvailableRating
		  >> m_iAvailableRandom
		  >> m_iTravelStellar
		  >> m_iReturnStellar
		  >> m_iCargoType
		  >> m_iCargoAmount
		  >> m_iCargoPickup
		  >> m_iCargoDropoff;

	ReadHex16Field(input, m_cScanMask);

	char c = m_cScanMask[0]; m_cScanMask[0] = m_cScanMask[1]; m_cScanMask[1] = c;

	input >> m_iPayValue
		  >> m_iShipCount
		  >> m_iShipSystem
		  >> m_iShipDude
		  >> m_iShipGoal
		  >> m_iShipBehavior
		  >> m_iShipName
		  >> m_iShipStart
		  >> m_iCompletionGovernment
		  >> m_iCompletionReward
		  >> m_iShipSubtitle
		  >> m_iBriefingDesc
		  >> m_iQuickBriefDesc
		  >> m_iLoadCargoDesc
		  >> m_iDropoffCargoDesc
		  >> m_iCompletionDesc
		  >> m_iFailDesc
		  >> m_iShipDoneDesc
		  >> m_iRefuseDesc
		  >> m_iTimeLimit
		  >> m_iAuxShipCount
		  >> m_iAuxShipDude
		  >> m_iAuxShipSyst
		  >> m_iAvailableShipType;

	input.ignore(1);

	ReadTextField(input, m_szAvailableBits, 255);
	ReadTextField(input, m_szOnAccept,      255);
	ReadTextField(input, m_szOnRefuse,      255);
	ReadTextField(input, m_szOnSuccess,     255);
	ReadTextField(input, m_szOnFailure,     255);
	ReadTextField(input, m_szOnAbort,       255);
	ReadTextField(input, m_szOnShipDone,    255);

	ReadHex64Field(input, m_cRequire);

	input >> m_iDateIncrement;

	input.ignore(1);

	ReadTextField(input, m_szAcceptButton, 32);
	ReadTextField(input, m_szRefuseButton, 33);

	input >> m_iDisplayWeight
		  >> m_iCanAbort;

	ReadHex16Field(input, (char *)&m_iFlags1);
	ReadHex16Field(input, (char *)&m_iFlags2);

	return 1;
}

int CMisnResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "misn ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_MISN_EDIT1, CCONTROL_TYPE_INT, IDS_STRING400);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_MISN_EDIT2, CCONTROL_TYPE_INT, IDS_STRING401);
	m_controls[1].SetInt(m_iAvailableStellar);
	m_controls[2].Create(hwnd, IDC_EDIT_MISN_COMBO2, CCONTROL_TYPE_COMBOBOX, IDS_STRING402);
	m_controls[2].SetComboStrings(NUM_MISN_AVAILLOCATION_CHOICES, g_szMisnAvailLocationChoices);
	m_controls[2].SetInt(m_iAvailableLocation);
	m_controls[3].Create(hwnd, IDC_EDIT_MISN_EDIT4, CCONTROL_TYPE_INT, IDS_STRING403);
	m_controls[3].SetInt(m_iAvailableRecord);
	m_controls[4].Create(hwnd, IDC_EDIT_MISN_EDIT5, CCONTROL_TYPE_INT, IDS_STRING404);
	m_controls[4].SetInt(m_iAvailableRating);
	m_controls[5].Create(hwnd, IDC_EDIT_MISN_EDIT6, CCONTROL_TYPE_INT, IDS_STRING405);
	m_controls[5].SetInt(m_iAvailableRandom);
	m_controls[6].Create(hwnd, IDC_EDIT_MISN_EDIT7, CCONTROL_TYPE_INT, IDS_STRING406);
	m_controls[6].SetInt(m_iTravelStellar);
	m_controls[7].Create(hwnd, IDC_EDIT_MISN_EDIT8, CCONTROL_TYPE_INT, IDS_STRING407);
	m_controls[7].SetInt(m_iReturnStellar);
	m_controls[8].Create(hwnd, IDC_EDIT_MISN_EDIT9, CCONTROL_TYPE_INT, IDS_STRING408);
	m_controls[8].SetInt(m_iCargoType);
	m_controls[9].Create(hwnd, IDC_EDIT_MISN_EDIT10, CCONTROL_TYPE_INT, IDS_STRING409);
	m_controls[9].SetInt(m_iCargoAmount);
	m_controls[10].Create(hwnd, IDC_EDIT_MISN_COMBO5, CCONTROL_TYPE_COMBOBOX, IDS_STRING410);
	m_controls[10].SetComboStrings(NUM_MISN_CARGOPICKUPMODE_CHOICES, g_szMisnCargoPickupModeChoices);
	m_controls[10].SetInt(m_iCargoPickup + 1);
	m_controls[11].Create(hwnd, IDC_EDIT_MISN_COMBO6, CCONTROL_TYPE_COMBOBOX, IDS_STRING411);
	m_controls[11].SetComboStrings(NUM_MISN_CARGODROPOFFMODE_CHOICES, g_szMisnCargoDropoffModeChoices);
	m_controls[11].SetInt(m_iCargoDropoff + 1);
	m_controls[12].Create(hwnd, IDC_EDIT_MISN_EDIT13, CCONTROL_TYPE_HEXINT16, IDS_STRING412);
	m_controls[12].SetString(m_cScanMask);
	m_controls[13].Create(hwnd, IDC_EDIT_MISN_EDIT14, CCONTROL_TYPE_INT, IDS_STRING413);
	m_controls[13].SetInt(m_iPayValue);
	m_controls[14].Create(hwnd, IDC_EDIT_MISN_EDIT15, CCONTROL_TYPE_INT, IDS_STRING414);
	m_controls[14].SetInt(m_iShipCount);
	m_controls[15].Create(hwnd, IDC_EDIT_MISN_EDIT16, CCONTROL_TYPE_INT, IDS_STRING415);
	m_controls[15].SetInt(m_iShipSystem);
	m_controls[16].Create(hwnd, IDC_EDIT_MISN_EDIT17, CCONTROL_TYPE_INT, IDS_STRING416);
	m_controls[16].SetInt(m_iShipDude);
	m_controls[17].Create(hwnd, IDC_EDIT_MISN_COMBO9, CCONTROL_TYPE_COMBOBOX, IDS_STRING417);
	m_controls[17].SetComboStrings(NUM_MISN_SHIPGOAL_CHOICES, g_szMisnShipGoalChoices);
	m_controls[17].SetInt(m_iShipGoal + 1);
	m_controls[18].Create(hwnd, IDC_EDIT_MISN_COMBO10, CCONTROL_TYPE_COMBOBOX, IDS_STRING418);
	m_controls[18].SetComboStrings(NUM_MISN_SHIPBEHAVIOR_CHOICES, g_szMisnShipBehaviorChoices);
	m_controls[18].SetInt(m_iShipBehavior + 1);
	m_controls[19].Create(hwnd, IDC_EDIT_MISN_EDIT20, CCONTROL_TYPE_INT, IDS_STRING419);
	m_controls[19].SetInt(m_iShipName);
	m_controls[20].Create(hwnd, IDC_EDIT_MISN_COMBO11, CCONTROL_TYPE_COMBOBOX, IDS_STRING420);
	m_controls[20].SetComboStrings(NUM_MISN_SHIPSTART_CHOICES, g_szMisnShipStartChoices);
	m_controls[20].SetInt(m_iShipStart + 4);
	m_controls[21].Create(hwnd, IDC_EDIT_MISN_EDIT22, CCONTROL_TYPE_INT, IDS_STRING421);
	m_controls[21].SetInt(m_iCompletionGovernment);
	m_controls[22].Create(hwnd, IDC_EDIT_MISN_EDIT23, CCONTROL_TYPE_INT, IDS_STRING422);
	m_controls[22].SetInt(m_iCompletionReward);
	m_controls[23].Create(hwnd, IDC_EDIT_MISN_EDIT24, CCONTROL_TYPE_INT, IDS_STRING423);
	m_controls[23].SetInt(m_iShipSubtitle);
	m_controls[24].Create(hwnd, IDC_EDIT_MISN_EDIT25, CCONTROL_TYPE_INT, IDS_STRING424);
	m_controls[24].SetInt(m_iBriefingDesc);
	m_controls[25].Create(hwnd, IDC_EDIT_MISN_EDIT26, CCONTROL_TYPE_INT, IDS_STRING425);
	m_controls[25].SetInt(m_iQuickBriefDesc);
	m_controls[26].Create(hwnd, IDC_EDIT_MISN_EDIT27, CCONTROL_TYPE_INT, IDS_STRING426);
	m_controls[26].SetInt(m_iLoadCargoDesc);
	m_controls[27].Create(hwnd, IDC_EDIT_MISN_EDIT28, CCONTROL_TYPE_INT, IDS_STRING427);
	m_controls[27].SetInt(m_iDropoffCargoDesc);
	m_controls[28].Create(hwnd, IDC_EDIT_MISN_EDIT29, CCONTROL_TYPE_INT, IDS_STRING428);
	m_controls[28].SetInt(m_iCompletionDesc);
	m_controls[29].Create(hwnd, IDC_EDIT_MISN_EDIT30, CCONTROL_TYPE_INT, IDS_STRING429);
	m_controls[29].SetInt(m_iFailDesc);
	m_controls[30].Create(hwnd, IDC_EDIT_MISN_EDIT31, CCONTROL_TYPE_INT, IDS_STRING430);
	m_controls[30].SetInt(m_iShipDoneDesc);
	m_controls[31].Create(hwnd, IDC_EDIT_MISN_CHECK19, CCONTROL_TYPE_CHECK, IDS_STRING431);
	m_controls[31].SetInt(m_iCanAbort);
	m_controls[32].Create(hwnd, IDC_EDIT_MISN_EDIT33, CCONTROL_TYPE_INT, IDS_STRING432);
	m_controls[32].SetInt(m_iTimeLimit);
	m_controls[33].Create(hwnd, IDC_EDIT_MISN_EDIT34, CCONTROL_TYPE_INT, IDS_STRING433);
	m_controls[33].SetInt(m_iAuxShipCount);
	m_controls[34].Create(hwnd, IDC_EDIT_MISN_EDIT35, CCONTROL_TYPE_INT, IDS_STRING434);
	m_controls[34].SetInt(m_iAuxShipDude);
	m_controls[35].Create(hwnd, IDC_EDIT_MISN_EDIT36, CCONTROL_TYPE_INT, IDS_STRING435);
	m_controls[35].SetInt(m_iAuxShipSyst);
	m_controls[36].Create(hwnd, IDC_EDIT_MISN_EDIT37, CCONTROL_TYPE_INT, IDS_STRING436);
	m_controls[36].SetInt(m_iAvailableShipType);
	m_controls[37].Create(hwnd, IDC_EDIT_MISN_EDIT38, CCONTROL_TYPE_INT, IDS_STRING437);
	m_controls[37].SetInt(m_iRefuseDesc);
	m_controls[38].Create(hwnd, IDC_EDIT_MISN_EDIT39, CCONTROL_TYPE_STR255, IDS_STRING438);
	m_controls[38].SetString(m_szAvailableBits);
	m_controls[39].Create(hwnd, IDC_EDIT_MISN_EDIT40, CCONTROL_TYPE_STR255, IDS_STRING439);
	m_controls[39].SetString(m_szOnAccept);
	m_controls[40].Create(hwnd, IDC_EDIT_MISN_EDIT41, CCONTROL_TYPE_STR255, IDS_STRING440);
	m_controls[40].SetString(m_szOnRefuse);
	m_controls[41].Create(hwnd, IDC_EDIT_MISN_EDIT42, CCONTROL_TYPE_STR255, IDS_STRING441);
	m_controls[41].SetString(m_szOnSuccess);
	m_controls[42].Create(hwnd, IDC_EDIT_MISN_EDIT43, CCONTROL_TYPE_STR255, IDS_STRING442);
	m_controls[42].SetString(m_szOnFailure);
	m_controls[43].Create(hwnd, IDC_EDIT_MISN_EDIT44, CCONTROL_TYPE_STR255, IDS_STRING443);
	m_controls[43].SetString(m_szOnAbort);
	m_controls[44].Create(hwnd, IDC_EDIT_MISN_EDIT45, CCONTROL_TYPE_STR255, IDS_STRING444);
	m_controls[44].SetString(m_szOnShipDone);
	m_controls[45].Create(hwnd, IDC_EDIT_MISN_EDIT46, CCONTROL_TYPE_HEXINT64, IDS_STRING445);
	m_controls[45].SetString(m_cRequire);
	m_controls[46].Create(hwnd, IDC_EDIT_MISN_EDIT47, CCONTROL_TYPE_INT, IDS_STRING446);
	m_controls[46].SetInt(m_iDateIncrement);
	m_controls[47].Create(hwnd, IDC_EDIT_MISN_EDIT48, CCONTROL_TYPE_STR32, IDS_STRING447);
	m_controls[47].SetString(m_szAcceptButton);
	m_controls[48].Create(hwnd, IDC_EDIT_MISN_EDIT49, CCONTROL_TYPE_STR33, IDS_STRING448);
	m_controls[48].SetString(m_szRefuseButton);
	m_controls[49].Create(hwnd, IDC_EDIT_MISN_EDIT50, CCONTROL_TYPE_INT, IDS_STRING449);
	m_controls[49].SetInt(m_iDisplayWeight);
	m_controls[50].Create(hwnd, IDC_EDIT_MISN_CHECK1, CCONTROL_TYPE_CHECK, IDS_STRING450);
	m_controls[50].SetInt(m_iFlags1 & 0x0001);
	m_controls[51].Create(hwnd, IDC_EDIT_MISN_CHECK2, CCONTROL_TYPE_CHECK, IDS_STRING451);
	m_controls[51].SetInt(m_iFlags1 & 0x0002);
	m_controls[52].Create(hwnd, IDC_EDIT_MISN_CHECK3, CCONTROL_TYPE_CHECK, IDS_STRING452);
	m_controls[52].SetInt(m_iFlags1 & 0x0004);
	m_controls[53].Create(hwnd, IDC_EDIT_MISN_CHECK4, CCONTROL_TYPE_CHECK, IDS_STRING453);
	m_controls[53].SetInt(m_iFlags1 & 0x0008);
	m_controls[54].Create(hwnd, IDC_EDIT_MISN_CHECK5, CCONTROL_TYPE_CHECK, IDS_STRING454);
	m_controls[54].SetInt(m_iFlags1 & 0x0010);
	m_controls[55].Create(hwnd, IDC_EDIT_MISN_CHECK6, CCONTROL_TYPE_CHECK, IDS_STRING455);
	m_controls[55].SetInt(m_iFlags1 & 0x0020);
	m_controls[56].Create(hwnd, IDC_EDIT_MISN_CHECK7, CCONTROL_TYPE_CHECK, IDS_STRING456);
	m_controls[56].SetInt(m_iFlags1 & 0x0040);
	m_controls[57].Create(hwnd, IDC_EDIT_MISN_CHECK8, CCONTROL_TYPE_CHECK, IDS_STRING457);
	m_controls[57].SetInt(m_iFlags1 & 0x0080);
	m_controls[58].Create(hwnd, IDC_EDIT_MISN_CHECK9, CCONTROL_TYPE_CHECK, IDS_STRING458);
	m_controls[58].SetInt(m_iFlags1 & 0x0100);
	m_controls[59].Create(hwnd, IDC_EDIT_MISN_CHECK10, CCONTROL_TYPE_CHECK, IDS_STRING459);
	m_controls[59].SetInt(m_iFlags1 & 0x0200);
	m_controls[60].Create(hwnd, IDC_EDIT_MISN_CHECK11, CCONTROL_TYPE_CHECK, IDS_STRING460);
	m_controls[60].SetInt(m_iFlags1 & 0x0400);
	m_controls[61].Create(hwnd, IDC_EDIT_MISN_CHECK12, CCONTROL_TYPE_CHECK, IDS_STRING461);
	m_controls[61].SetInt(m_iFlags1 & 0x0800);
	m_controls[62].Create(hwnd, IDC_EDIT_MISN_CHECK13, CCONTROL_TYPE_CHECK, IDS_STRING462);
	m_controls[62].SetInt(m_iFlags1 & 0x2000);
	m_controls[63].Create(hwnd, IDC_EDIT_MISN_CHECK14, CCONTROL_TYPE_CHECK, IDS_STRING463);
	m_controls[63].SetInt(m_iFlags1 & 0x4000);
	m_controls[64].Create(hwnd, IDC_EDIT_MISN_CHECK15, CCONTROL_TYPE_CHECK, IDS_STRING464);
	m_controls[64].SetInt(m_iFlags1 & 0x8000);
	m_controls[65].Create(hwnd, IDC_EDIT_MISN_CHECK16, CCONTROL_TYPE_CHECK, IDS_STRING465);
	m_controls[65].SetInt(m_iFlags2 & 0x0001);
	m_controls[66].Create(hwnd, IDC_EDIT_MISN_CHECK17, CCONTROL_TYPE_CHECK, IDS_STRING466);
	m_controls[66].SetInt(m_iFlags2 & 0x0002);
	m_controls[67].Create(hwnd, IDC_EDIT_MISN_CHECK18, CCONTROL_TYPE_CHECK, IDS_STRING467);
	m_controls[67].SetInt(m_iFlags2 & 0x0004);
	m_controls[68].Create(hwnd, IDC_EDIT_MISN_EDIT51, CCONTROL_TYPE_STR256, IDS_STRING468);
	m_controls[68].SetString(m_szName);

	UpdateDynamicDefaults(m_controls, -1, m_iID);

	std::string szText = "Introduction Text:\t";
	szText += ToString(m_iID + 4000 - 128);

	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_MISN_TEXT32), szText.c_str());

	return 1;
}

int CMisnResource::CloseAndSave(void)
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

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[68].GetString()) != 0))
		iIDOrNameChanged = 1;

	m_iID = m_controls[0].GetInt();

	m_iAvailableStellar  = m_controls[1].GetInt();
	m_iAvailableLocation = m_controls[2].GetInt();
	m_iAvailableRecord   = m_controls[3].GetInt();
	m_iAvailableRating   = m_controls[4].GetInt();
	m_iAvailableRandom   = m_controls[5].GetInt();

	m_iTravelStellar = m_controls[6].GetInt();
	m_iReturnStellar = m_controls[7].GetInt();

	m_iCargoType    = m_controls[8].GetInt();
	m_iCargoAmount  = m_controls[9].GetInt();
	m_iCargoPickup  = m_controls[10].GetInt() - 1;
	m_iCargoDropoff = m_controls[11].GetInt() - 1;

	memcpy(m_cScanMask, m_controls[12].GetString(), 2 * sizeof(char));

	m_iPayValue = m_controls[13].GetInt();

	m_iShipCount    = m_controls[14].GetInt();
	m_iShipSystem   = m_controls[15].GetInt();
	m_iShipDude     = m_controls[16].GetInt();
	m_iShipGoal     = m_controls[17].GetInt() - 1;
	m_iShipBehavior = m_controls[18].GetInt() - 1;
	m_iShipName     = m_controls[19].GetInt();
	m_iShipStart    = m_controls[20].GetInt() - 4;

	m_iCompletionGovernment = m_controls[21].GetInt();
	m_iCompletionReward     = m_controls[22].GetInt();

	m_iShipSubtitle = m_controls[23].GetInt();

	m_iBriefingDesc     = m_controls[24].GetInt();
	m_iQuickBriefDesc   = m_controls[25].GetInt();
	m_iLoadCargoDesc    = m_controls[26].GetInt();
	m_iDropoffCargoDesc = m_controls[27].GetInt();
	m_iCompletionDesc   = m_controls[28].GetInt();
	m_iFailDesc         = m_controls[29].GetInt();
	m_iShipDoneDesc     = m_controls[30].GetInt();

	m_iCanAbort = m_controls[31].GetInt();

	m_iTimeLimit = m_controls[32].GetInt();

	m_iAuxShipCount = m_controls[33].GetInt();
	m_iAuxShipDude  = m_controls[34].GetInt();
	m_iAuxShipSyst  = m_controls[35].GetInt();

	m_iAvailableShipType = m_controls[36].GetInt();

	m_iRefuseDesc = m_controls[37].GetInt();

	strcpy(m_szAvailableBits, m_controls[38].GetString());
	strcpy(m_szOnAccept,      m_controls[39].GetString());
	strcpy(m_szOnRefuse,      m_controls[40].GetString());
	strcpy(m_szOnSuccess,     m_controls[41].GetString());
	strcpy(m_szOnFailure,     m_controls[42].GetString());
	strcpy(m_szOnAbort,       m_controls[43].GetString());
	strcpy(m_szOnShipDone,    m_controls[44].GetString());

	memcpy(m_cRequire, m_controls[45].GetString(), 8 * sizeof(char));

	m_iDateIncrement = m_controls[46].GetInt();

	strcpy(m_szAcceptButton, m_controls[47].GetString());
	strcpy(m_szRefuseButton, m_controls[48].GetString());

	m_iDisplayWeight = m_controls[49].GetInt();

	m_iFlags1 = 0x0000;
	m_iFlags2 = 0x0000;

	m_iFlags1 |= m_controls[50].GetInt() << 0;
	m_iFlags1 |= m_controls[51].GetInt() << 1;
	m_iFlags1 |= m_controls[52].GetInt() << 2;
	m_iFlags1 |= m_controls[53].GetInt() << 3;
	m_iFlags1 |= m_controls[54].GetInt() << 4;
	m_iFlags1 |= m_controls[55].GetInt() << 5;
	m_iFlags1 |= m_controls[56].GetInt() << 6;
	m_iFlags1 |= m_controls[57].GetInt() << 7;
	m_iFlags1 |= m_controls[58].GetInt() << 8;
	m_iFlags1 |= m_controls[59].GetInt() << 9;
	m_iFlags1 |= m_controls[60].GetInt() << 10;
	m_iFlags1 |= m_controls[61].GetInt() << 11;
	m_iFlags1 |= m_controls[62].GetInt() << 13;
	m_iFlags1 |= m_controls[63].GetInt() << 14;
	m_iFlags1 |= m_controls[64].GetInt() << 15;

	m_iFlags2 |= m_controls[65].GetInt() << 0;
	m_iFlags2 |= m_controls[66].GetInt() << 1;
	m_iFlags2 |= m_controls[67].GetInt() << 2;

	strcpy(m_szName, m_controls[68].GetString());

	int i;

	for(i = 0; i < NUM_MISN_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CMisnResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_MISN_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CMisnResource::MisnDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CMisnResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CMisnResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_MISN_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_MISN_OK)
			{
				pResource->CloseAndSave();
			}
			else if(iControlID == IDC_EDIT_MISN_BUTTON1)
			{
				char cValue[2];

				memcpy(cValue, pResource->m_controls[12].GetString(), 2);

				pResource->m_bitFieldControl.DoDialog(pResource->m_pWindow, 16, cValue);

				pResource->m_controls[12].SetString(cValue);
			}
			else if(iControlID == IDC_EDIT_MISN_BUTTON2)
			{
				char cValue[8];

				memcpy(cValue, pResource->m_controls[45].GetString(), 8);

				pResource->m_bitFieldControl.DoDialog(pResource->m_pWindow, 64, cValue);

				pResource->m_controls[45].SetString(cValue);
			}
			else
			{
				for(i = 0; i < NUM_MISN_CONTROLS; i++)
				{
					if(iControlID == pResource->m_controls[i].GetControlID())
					{
						pResource->m_controls[i].ProcessMessage(iNotifyCode);

						break;
					}
				}
			}

			if ((iControlID == IDC_EDIT_DESC_BTN1)) {
				short id = pResource->m_controls[0].GetInt() + 4000 - 128;
				CEditor::GetCurrentEditor()->ResourceExtra(id, std::string("OFFER: ") + pResource->m_controls[68].GetString());
			}
			else if ((iControlID == IDC_EDIT_DESC_BTN2)) {
				short id = pResource->m_controls[0].GetInt() + 5000 - 128;
				CEditor::GetCurrentEditor()->ResourceExtra(id, std::string("BREIF: ") + pResource->m_controls[68].GetString());
			}
			else if ((iControlID == IDC_EDIT_DESC_BTN3)) {
				short id = pResource->m_controls[0].GetInt() + 6000 - 128;
				CEditor::GetCurrentEditor()->ResourceExtra(id, std::string("QUICK: ") + pResource->m_controls[68].GetString());
			}
			else if ((iControlID == IDC_EDIT_DESC_BTN4)) {
				short id = pResource->m_controls[0].GetInt() + 7000 - 128;
				CEditor::GetCurrentEditor()->ResourceExtra(id, std::string("LOAD: ") + pResource->m_controls[68].GetString());
			}
			else if ((iControlID == IDC_EDIT_DESC_BTN5)) {
				short id = pResource->m_controls[0].GetInt() + 8000 - 128;
				CEditor::GetCurrentEditor()->ResourceExtra(id, std::string("DROP: ") + pResource->m_controls[68].GetString());
			}
			else if ((iControlID == IDC_EDIT_DESC_BTN6)) {
				short id = pResource->m_controls[0].GetInt() + 9000 - 128;
				CEditor::GetCurrentEditor()->ResourceExtra(id, std::string("DONE: ") + pResource->m_controls[68].GetString());
			}
			else if ((iControlID == IDC_EDIT_DESC_BTN7)) {
				short id = pResource->m_controls[0].GetInt() + 15000 - 128;
				CEditor::GetCurrentEditor()->ResourceExtra(id, std::string("FAIL: ") + pResource->m_controls[68].GetString());
			}
			else if ((iControlID == IDC_EDIT_DESC_BTN8)) {
				short id = pResource->m_controls[0].GetInt() + 16000 - 128;
				CEditor::GetCurrentEditor()->ResourceExtra(id, std::string("SHIP: ") + pResource->m_controls[68].GetString());
			}
			else if ((iControlID == IDC_EDIT_DESC_BTN9)) {
				short id = pResource->m_controls[0].GetInt() + 17000 - 128;
				CEditor::GetCurrentEditor()->ResourceExtra(id, std::string("RJCT: ") + pResource->m_controls[68].GetString());
			}

			if((iControlID == IDC_EDIT_MISN_EDIT1) && (iNotifyCode == EN_CHANGE))
			{
				if((pResource->m_controls[0].GetInt() >= 128) && (pResource->m_controls[0].GetInt() < 1128))
				{
					char* inStr = new char[255];
					Static_GetText(GetDlgItem(hwnd, IDC_EDIT_MISN_TEXT32), inStr, 255);
					short oldV = (strcmp(inStr, "Introduction Text:") != 0) ? std::stoi(inStr + 19) - 4000 + 128 : -1;

					short newId = pResource->m_controls[0].GetInt();
					UpdateDynamicDefaults(pResource->m_controls, oldV, newId);
					std::string szText = "Introduction Text:\t";
					szText += ToString(newId + 4000 - 128);

					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_MISN_TEXT32), szText.c_str());
				}
			}
			else if (iControlID == IDC_EDIT_MISN_EDIT2 ) {
				//ID = IDC_EDIT_MISN_EDIT2; Txt=IDC_EDIT_MISN_TEXT52
//"Which stellars the mission is available from.  Possible values are:\r\n-1: Any stellar\r\n128-2175: ID of a specific stellar\r\n5000-7047: Stellar in a system adjacent to a specific system\r\n10000-10255: Any stellar belonging to this government\r\n15000-15255: Any stellar belonging to an ally of this government\r\n20000-20255: Any stellar not belonging to this government\r\n25000-25255: Any stellar belonging to an enemy of this government\r\n30000-30255: Any stellar belonging to this government or any of its classmates\r\n31000-31255: Any stellar not of this government nor any of its classmates"

				int id = pResource->m_controls[1].GetInt();
				//std::ofstream outputFile("log.txt", std::ios_base::app);
				//outputFile << inStr << std::endl;
				std::string rezName = "None";
				if (id == -1) rezName = "Any Stellar";
				else if (id >= 128 && id <= 2175) rezName = NovaLib::RezStr(CNR_TYPE_SPOB, id);
				else if (id >= 5000 && id <= 7047)
					rezName = "AdjTo" + NovaLib::RezStr(CNR_TYPE_SYST, id - 5000, true);
				else if (id >= 10000 && id <= 10255)
					rezName = NovaLib::RezStr(CNR_TYPE_GOVT, id - 10000, true);
				else if (id >= 15000 && id <= 15255)
					rezName = "AllyOf" + NovaLib::RezStr(CNR_TYPE_GOVT, id - 15000);
				else if (id >= 20000 && id <= 20255)
					rezName = "Not" + NovaLib::RezStr(CNR_TYPE_GOVT, id - 20000);
				else if (id >= 25000 && id <= 25255)
					rezName = "EnemyOf" + NovaLib::RezStr(CNR_TYPE_GOVT, id - 25000);
				else if (id >= 30000 && id <= 30255)
					rezName = "ClassOf" + NovaLib::RezStr(CNR_TYPE_GOVT, id - 30000);
				else if (id >= 31000 && id <= 31255)
					rezName = "!ClassOf" + NovaLib::RezStr(CNR_TYPE_GOVT, id - 31000);

				Static_SetText(GetDlgItem(hwnd, IDC_EDIT_MISN_TEXT52), rezName.c_str());
			} 
			else if (iControlID == IDC_EDIT_MISN_EDIT7) {
				int id = pResource->m_controls[6].GetInt();
				std::string rezName = "None";

				if (id == -2) rezName = "Rand Inhabited";
				else if (id == -3) rezName = "Rand Uninhabited";
				else if (id >= 128 && id <= 2175) rezName = NovaLib::RezStr(CNR_TYPE_SPOB, id);
				else if (id >= 10000 && id <= 10255)
					rezName = "Rand " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 10000);
				else if (id >= 15000 && id <= 15255)
					rezName = "Random AllyOf " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 15000);
				else if (id >= 20000 && id <= 20255)
					rezName = "Random Not " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 20000);
				else if (id >= 25000 && id <= 25255)
					rezName = "Random EnemyOf " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 25000);
				else if (id >= 30000 && id <= 30255)
					rezName = "Random ClassOf " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 30000);
				else if (id >= 31000 && id <= 31255)
					rezName = "Random !ClassOf " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 31000);

				Static_SetText(GetDlgItem(hwnd, IDC_EDIT_MISN_TEXT56), rezName.c_str());
			}
			else if (iControlID == IDC_EDIT_MISN_EDIT8) {
				int id = pResource->m_controls[7].GetInt();
				std::string rezName = "None";

				if (id == -2) rezName = "Rand Inhabited";
				else if (id == -3) rezName = "Rand Uninhabited";
				else if (id == -4) rezName = "Initial Stellar";
				else if (id >= 128 && id <= 2175) rezName = NovaLib::RezStr(CNR_TYPE_SPOB, id);
				else if (id >= 10000 && id <= 10255)
					rezName = "Random " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 10000, true);
				else if (id >= 15000 && id <= 15255)
					rezName = "Random AllyOf " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 15000);
				else if (id >= 20000 && id <= 20255)
					rezName = "Random Not " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 20000);
				else if (id >= 25000 && id <= 25255)
					rezName = "Random EnemyOf " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 25000);
				else if (id >= 30000 && id <= 30255)
					rezName = "Random ClassOf " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 30000);
				else if (id >= 31000 && id <= 31255)
					rezName = "Random !ClassOf " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 31000);

				Static_SetText(GetDlgItem(hwnd, IDC_EDIT_MISN_TEXT57), rezName.c_str());
			}
			else if (iControlID == IDC_EDIT_MISN_EDIT9) {
				int id = pResource->m_controls[8].GetInt();
				std::string rezName = "None";

				if (id == 1000) rezName = "Random Cargo";
				else if (id >= 0 && id <= 255) rezName = NovaLib::RezStr(CNR_TYPE_JUNK, id);

				Static_SetText(GetDlgItem(hwnd, IDC_EDIT_MISN_TEXT58), rezName.c_str());
			}
			else if (iControlID == IDC_EDIT_MISN_EDIT16) {
				int id = pResource->m_controls[15].GetInt();
				std::string rezName = "Initial";

				if (id == -2) rezName = "Rand System";
				else if (id == -3) rezName = "Travel Stellar";
				else if (id == -4) rezName = "Return Stellar";
				else if (id == -5) rezName = "Adjacent System";
				else if (id == -6) rezName = "Follow Player";
				else if (id >= 128 && id <= 2175) rezName = NovaLib::RezStr(CNR_TYPE_SYST, id);
				else if (id >= 10000 && id <= 10255)
					rezName = "Random " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 10000, true);
				else if (id >= 15000 && id <= 15255)
					rezName = "Random AllyOf " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 15000);
				else if (id >= 20000 && id <= 20255)
					rezName = "Random Not " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 20000);
				else if (id >= 25000 && id <= 25255)
					rezName = "Random EnemyOf " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 25000);
				else if (id >= 30000 && id <= 30255)
					rezName = "Random ClassOf " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 30000);
				else if (id >= 31000 && id <= 31255)
					rezName = "Random !ClassOf " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 31000);

				Static_SetText(GetDlgItem(hwnd, IDC_EDIT_MISN_TEXT62), rezName.c_str());
			}
			else if (iControlID == IDC_EDIT_MISN_EDIT17) {
				int id = pResource->m_controls[16].GetInt();
				std::string rezName = "None";

				if (id >= 128 && id <= 639) rezName = NovaLib::RezStr(CNR_TYPE_DUDE, id);

				Static_SetText(GetDlgItem(hwnd, IDC_EDIT_MISN_TEXT63), rezName.c_str());
			}
			else if (iControlID == IDC_EDIT_MISN_EDIT35) {
				int id = pResource->m_controls[34].GetInt();
				std::string rezName = "None";

				if (id >= 128 && id <= 639) rezName = NovaLib::RezStr(CNR_TYPE_DUDE, id);

				Static_SetText(GetDlgItem(hwnd, IDC_EDIT_MISN_TEXT68), rezName.c_str());
			}
			else if (iControlID == IDC_EDIT_MISN_EDIT36) {
				int id = pResource->m_controls[35].GetInt();
				std::string rezName = "Follow Player";

				if (id == -2) rezName = "Travel System";
				else if (id == -3) rezName = "Return System";
				else if (id >= 128 && id <= 2175) rezName = NovaLib::RezStr(CNR_TYPE_SYST, id);
				else if (id >= 10000 && id <= 10255)
					rezName = "Rand " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 10000, true);
				else if (id >= 15000 && id <= 15255)
					rezName = "Rand AllyOf " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 15000);
				else if (id >= 20000 && id <= 20255)
					rezName = "Rand Not " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 20000);
				else if (id >= 25000 && id <= 25255)
					rezName = "Rand EnemyOf " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 25000);
				else if (id >= 30000 && id <= 30255)
					rezName = "Rand ClassOf " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 30000);
				else if (id >= 31000 && id <= 31255)
					rezName = "Rand !ClassOf " + NovaLib::RezStr(CNR_TYPE_GOVT, id - 31000);

				Static_SetText(GetDlgItem(hwnd, IDC_EDIT_MISN_TEXT69), rezName.c_str());
			}
			else if (iControlID == IDC_EDIT_MISN_EDIT37) {
				int id = pResource->m_controls[36].GetInt();
				std::string rezName = "Any Ship";

				if (id >= 128 && id <= 255)	rezName = NovaLib::RezStr(CNR_TYPE_SHIP, id);
				else if (id >= 1128 && id <= 1255) rezName = "Not" + NovaLib::RezStr(CNR_TYPE_SHIP, id - 1000);
				else if (id >= 2128 && id <= 2255)
					rezName = "GovtOf" + NovaLib::RezStr(CNR_TYPE_GOVT, id - 2000);
				else if (id >= 3128 && id <= 3255)
					rezName = "NotGovtOf" + NovaLib::RezStr(CNR_TYPE_GOVT, id - 3000);

				Static_SetText(GetDlgItem(hwnd, IDC_EDIT_MISN_TEXT70), rezName.c_str());
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


void CMisnResource::UpdateDynamicDefaults(CControl* controls, short oldId, short newId)
{
	SetIfDefaultInt(controls, 24, oldId, newId, 5000 - 128);
	SetIfDefaultInt(controls, 25, oldId, newId, 6000 - 128);
	SetIfDefaultInt(controls, 26, oldId, newId, 7000 - 128);
	SetIfDefaultInt(controls, 27, oldId, newId, 8000 - 128);
	SetIfDefaultInt(controls, 28, oldId, newId, 9000 - 128);
	SetIfDefaultInt(controls, 29, oldId, newId, 15000 - 128);
	SetIfDefaultInt(controls, 30, oldId, newId, 16000 - 128);
	SetIfDefaultInt(controls, 37, oldId, newId, 17000 - 128);
	SetIfDefaultStr(controls, 38, oldId + 1100, newId + 1100);
	SetIfDefaultStr(controls, 41, oldId + 1100, newId + 1100);
	if (oldId != -1) return;

	controls[1].SetInt(162);
	controls[38].SetString(("!b" + std::to_string(newId + 1100)).c_str());
	controls[41].SetString(("b" + std::to_string(newId + 1100)+ " o368").c_str());
	controls[68].SetString("New Name; $¢ M");
} 