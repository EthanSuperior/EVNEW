// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CSpobResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CSpobResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CSpobResource::CSpobResource(void)
{
	m_iXPosition = 0;
	m_iYPosition = 0;

	m_iGraphics = 0;

	m_iTribute = 0;

	m_iTechLevel = 0;

	int i;

	for(i = 0; i < 8; i++)
		m_iSpecialTechs[i] = -1;

	m_iGovernment = -1;
	m_iMinStatus  =  0;

	m_iCustomPicture = -1;
	m_iCustomSound   = -1;

	m_iDefenseDude  = -1;
	m_iDefenseCount =  0;

	m_iAnimationDelay = 1;
	m_iFrame0Bias     = 1;

	for(i = 0; i < 8; i++)
		m_iHyperlinks[i] = -1;

	memset(m_szOnDominate, 0, 255 * sizeof(char));
	memset(m_szOnRelease,  0, 255 * sizeof(char));

	m_iLandingFee = 0;

	m_iGravity  =  0;
	m_iWeapon   = -1;
	m_iStrength =  0;

	m_iDeadType = -1;
	m_iDeadTime =  0;

	m_iExplosionType = -1;

	memset(m_szOnDestroy,    0, 255 * sizeof(char));
	memset(m_szOnRegenerate, 0, 255 * sizeof(char));

	m_iFlags1 = 0x00000000;
	m_iFlags2 = 0x0000;
}

CSpobResource::~CSpobResource(void)
= default;

int CSpobResource::GetType(void)
{
	return CNR_TYPE_SPOB;
}

int CSpobResource::GetSize(void)
{
	return 1118;
}

int CSpobResource::GetDialogID(void)
{
	return IDD_EDIT_SPOB;
}

DLGPROCNOCALLBACK CSpobResource::GetDialogProc(void)
{
	return SpobDlgProc;
}

int CSpobResource::GetNumFields(void)
{
	return NUM_SPOB_FIELDS;
}

const std::string * CSpobResource::GetFieldNames(void)
{
	return g_szSpobFields;
}

int CSpobResource::Save(char *pOutput)
{
	SwapEndians();

	*(short *)pOutput = m_iXPosition;       pOutput += sizeof(short);
	*(short *)pOutput = m_iYPosition;       pOutput += sizeof(short);
	*(short *)pOutput = m_iGraphics;        pOutput += sizeof(short);
	*(UINT  *)pOutput = m_iFlags1;          pOutput += sizeof(UINT);
	*(short *)pOutput = m_iTribute;         pOutput += sizeof(short);
	*(short *)pOutput = m_iTechLevel;       pOutput += sizeof(short);
	*(short *)pOutput = m_iSpecialTechs[0]; pOutput += sizeof(short);
	*(short *)pOutput = m_iSpecialTechs[1]; pOutput += sizeof(short);
	*(short *)pOutput = m_iSpecialTechs[2]; pOutput += sizeof(short);
	*(short *)pOutput = m_iGovernment;      pOutput += sizeof(short);
	*(short *)pOutput = m_iMinStatus;       pOutput += sizeof(short);
	*(short *)pOutput = m_iCustomPicture;   pOutput += sizeof(short);
	*(short *)pOutput = m_iCustomSound;     pOutput += sizeof(short);
	*(short *)pOutput = m_iDefenseDude;     pOutput += sizeof(short);
	*(short *)pOutput = m_iDefenseCount;    pOutput += sizeof(short);
	*(USHORT *)pOutput = m_iFlags2;         pOutput += sizeof(USHORT);
	*(short *)pOutput = m_iAnimationDelay;  pOutput += sizeof(short);
	*(short *)pOutput = m_iFrame0Bias;      pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[0];   pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[1];   pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[2];   pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[3];   pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[4];   pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[5];   pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[6];   pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[7];   pOutput += sizeof(short);

	memcpy(pOutput, m_szOnDominate, 255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_szOnRelease,  255 * sizeof(char)); pOutput += 255 * sizeof(char);
	
	*(int   *)pOutput = m_iLandingFee;      pOutput += sizeof(int);
	*(short *)pOutput = m_iGravity;         pOutput += sizeof(short);
	*(short *)pOutput = m_iWeapon;          pOutput += sizeof(short);
	*(int   *)pOutput = m_iStrength;        pOutput += sizeof(int);
	*(short *)pOutput = m_iDeadType;        pOutput += sizeof(short);
	*(short *)pOutput = m_iDeadTime;        pOutput += sizeof(short);
	*(short *)pOutput = m_iExplosionType;   pOutput += sizeof(short);
	
	memcpy(pOutput, m_szOnDestroy,    255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_szOnRegenerate, 255 * sizeof(char)); pOutput += 255 * sizeof(char);
	
	*(short *)pOutput = m_iSpecialTechs[3]; pOutput += sizeof(short);
	*(short *)pOutput = m_iSpecialTechs[4]; pOutput += sizeof(short);
	*(short *)pOutput = m_iSpecialTechs[5]; pOutput += sizeof(short);
	*(short *)pOutput = m_iSpecialTechs[6]; pOutput += sizeof(short);
	*(short *)pOutput = m_iSpecialTechs[7]; pOutput += sizeof(short);

	SwapEndians();

	return 1;
}

int CSpobResource::Load(char *pInput, int iSize)
{
	m_iXPosition       = *(short *)pInput; pInput += sizeof(short);
	m_iYPosition       = *(short *)pInput; pInput += sizeof(short);
	m_iGraphics        = *(short *)pInput; pInput += sizeof(short);
	m_iFlags1          = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iTribute         = *(short *)pInput; pInput += sizeof(short);
	m_iTechLevel       = *(short *)pInput; pInput += sizeof(short);
	m_iSpecialTechs[0] = *(short *)pInput; pInput += sizeof(short);
	m_iSpecialTechs[1] = *(short *)pInput; pInput += sizeof(short);
	m_iSpecialTechs[2] = *(short *)pInput; pInput += sizeof(short);
	m_iGovernment      = *(short *)pInput; pInput += sizeof(short);
	m_iMinStatus       = *(short *)pInput; pInput += sizeof(short);
	m_iCustomPicture   = *(short *)pInput; pInput += sizeof(short);
	m_iCustomSound     = *(short *)pInput; pInput += sizeof(short);
	m_iDefenseDude     = *(short *)pInput; pInput += sizeof(short);
	m_iDefenseCount    = *(short *)pInput; pInput += sizeof(short);
	m_iFlags2          = *(USHORT *)pInput; pInput += sizeof(USHORT);
	m_iAnimationDelay  = *(short *)pInput; pInput += sizeof(short);
	m_iFrame0Bias      = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[0]   = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[1]   = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[2]   = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[3]   = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[4]   = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[5]   = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[6]   = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[7]   = *(short *)pInput; pInput += sizeof(short);

	memcpy(m_szOnDominate, pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	memcpy(m_szOnRelease,  pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);

	m_iLandingFee      = *(short *)pInput; pInput += sizeof(int);
	m_iGravity         = *(short *)pInput; pInput += sizeof(short);
	m_iWeapon          = *(short *)pInput; pInput += sizeof(short);
	m_iStrength        = *(short *)pInput; pInput += sizeof(int);
	m_iDeadType        = *(short *)pInput; pInput += sizeof(short);
	m_iDeadTime        = *(short *)pInput; pInput += sizeof(short);
	m_iExplosionType   = *(short *)pInput; pInput += sizeof(short);
	
	memcpy(m_szOnDestroy,    pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	memcpy(m_szOnRegenerate, pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	
	m_iSpecialTechs[3] = *(short *)pInput; pInput += sizeof(short);
	m_iSpecialTechs[4] = *(short *)pInput; pInput += sizeof(short);
	m_iSpecialTechs[5] = *(short *)pInput; pInput += sizeof(short);
	m_iSpecialTechs[6] = *(short *)pInput; pInput += sizeof(short);
	m_iSpecialTechs[7] = *(short *)pInput; pInput += sizeof(short);

	SwapEndians();

	return 1;
}

int CSpobResource::SwapEndians(void)
{
	m_iXPosition       = SwapEndianShort(m_iXPosition);
	m_iYPosition       = SwapEndianShort(m_iYPosition);
	m_iGraphics        = SwapEndianShort(m_iGraphics);
	m_iFlags1          = SwapEndianInt(m_iFlags1);
	m_iTribute         = SwapEndianShort(m_iTribute);
	m_iTechLevel       = SwapEndianShort(m_iTechLevel);
	m_iSpecialTechs[0] = SwapEndianShort(m_iSpecialTechs[0]);
	m_iSpecialTechs[1] = SwapEndianShort(m_iSpecialTechs[1]);
	m_iSpecialTechs[2] = SwapEndianShort(m_iSpecialTechs[2]);
	m_iGovernment      = SwapEndianShort(m_iGovernment);
	m_iMinStatus       = SwapEndianShort(m_iMinStatus);
	m_iCustomPicture   = SwapEndianShort(m_iCustomPicture);
	m_iCustomSound     = SwapEndianShort(m_iCustomSound);
	m_iDefenseDude     = SwapEndianShort(m_iDefenseDude);
	m_iDefenseCount    = SwapEndianShort(m_iDefenseCount);
	m_iFlags2          = SwapEndianShort(m_iFlags2);
	m_iAnimationDelay  = SwapEndianShort(m_iAnimationDelay);
	m_iFrame0Bias      = SwapEndianShort(m_iFrame0Bias);
	m_iHyperlinks[0]   = SwapEndianShort(m_iHyperlinks[0]);
	m_iHyperlinks[1]   = SwapEndianShort(m_iHyperlinks[1]);
	m_iHyperlinks[2]   = SwapEndianShort(m_iHyperlinks[2]);
	m_iHyperlinks[3]   = SwapEndianShort(m_iHyperlinks[3]);
	m_iHyperlinks[4]   = SwapEndianShort(m_iHyperlinks[4]);
	m_iHyperlinks[5]   = SwapEndianShort(m_iHyperlinks[5]);
	m_iHyperlinks[6]   = SwapEndianShort(m_iHyperlinks[6]);
	m_iHyperlinks[7]   = SwapEndianShort(m_iHyperlinks[7]);
	m_iLandingFee      = SwapEndianInt(m_iLandingFee);
	m_iGravity         = SwapEndianShort(m_iGravity);
	m_iWeapon          = SwapEndianShort(m_iWeapon);
	m_iStrength        = SwapEndianInt(m_iStrength);
	m_iDeadType        = SwapEndianShort(m_iDeadType);
	m_iDeadTime        = SwapEndianShort(m_iDeadTime);
	m_iExplosionType   = SwapEndianShort(m_iExplosionType);
	m_iSpecialTechs[3] = SwapEndianShort(m_iSpecialTechs[3]);
	m_iSpecialTechs[4] = SwapEndianShort(m_iSpecialTechs[4]);
	m_iSpecialTechs[5] = SwapEndianShort(m_iSpecialTechs[5]);
	m_iSpecialTechs[6] = SwapEndianShort(m_iSpecialTechs[6]);
	m_iSpecialTechs[7] = SwapEndianShort(m_iSpecialTechs[7]);

	return 1;
}

int CSpobResource::SaveToText(std::ostream & output)
{
	output << m_iXPosition       << '\t'
		   << m_iYPosition       << '\t'
		   << m_iGraphics        << '\t'
		   << m_iTribute         << '\t'
		   << m_iTechLevel       << '\t'
		   << m_iSpecialTechs[0] << '\t'
		   << m_iSpecialTechs[1] << '\t'
		   << m_iSpecialTechs[2] << '\t'
		   << m_iSpecialTechs[3] << '\t'
		   << m_iSpecialTechs[4] << '\t'
		   << m_iSpecialTechs[5] << '\t'
		   << m_iSpecialTechs[6] << '\t'
		   << m_iSpecialTechs[7] << '\t'
		   << m_iGovernment      << '\t'
		   << m_iMinStatus       << '\t'
		   << m_iCustomPicture   << '\t'
		   << m_iCustomSound     << '\t'
		   << m_iDefenseDude     << '\t'
		   << m_iDefenseCount    << '\t'
		   << m_iAnimationDelay  << '\t'
		   << m_iFrame0Bias      << '\t'
		   << m_iHyperlinks[0]   << '\t'
		   << m_iHyperlinks[1]   << '\t'
		   << m_iHyperlinks[2]   << '\t'
		   << m_iHyperlinks[3]   << '\t'
		   << m_iHyperlinks[4]   << '\t'
		   << m_iHyperlinks[5]   << '\t'
		   << m_iHyperlinks[6]   << '\t'
		   << m_iHyperlinks[7]   << '\t';

	PrintTextField(output, m_szOnDominate, '\t');
	PrintTextField(output, m_szOnRelease,  '\t');

	output << m_iLandingFee    << '\t'
		   << m_iGravity       << '\t'
		   << m_iWeapon        << '\t'
		   << m_iStrength      << '\t'
		   << m_iDeadType      << '\t'
		   << m_iDeadTime      << '\t'
		   << m_iExplosionType << '\t';

	PrintTextField(output, m_szOnDestroy,    '\t');
	PrintTextField(output, m_szOnRegenerate, '\t');

	PrintHex32Field(output, (char *)&m_iFlags1, '\t');
	PrintHex16Field(output, (char *)&m_iFlags2, '\t');

	return 1;
}

int CSpobResource::LoadFromText(std::istream & input)
{
	input >> m_iXPosition
		  >> m_iYPosition
		  >> m_iGraphics
		  >> m_iTribute
		  >> m_iTechLevel
		  >> m_iSpecialTechs[0]
		  >> m_iSpecialTechs[1]
		  >> m_iSpecialTechs[2]
		  >> m_iSpecialTechs[3]
		  >> m_iSpecialTechs[4]
		  >> m_iSpecialTechs[5]
		  >> m_iSpecialTechs[6]
		  >> m_iSpecialTechs[7]
		  >> m_iGovernment
		  >> m_iMinStatus
		  >> m_iCustomPicture
		  >> m_iCustomSound
		  >> m_iDefenseDude
		  >> m_iDefenseCount
		  >> m_iAnimationDelay
		  >> m_iFrame0Bias
		  >> m_iHyperlinks[0]
		  >> m_iHyperlinks[1]
		  >> m_iHyperlinks[2]
		  >> m_iHyperlinks[3]
		  >> m_iHyperlinks[4]
		  >> m_iHyperlinks[5]
		  >> m_iHyperlinks[6]
		  >> m_iHyperlinks[7];

	input.ignore(1);

	ReadTextField(input, m_szOnDominate, 255);
	ReadTextField(input, m_szOnRelease,  255);

	input >> m_iLandingFee
		  >> m_iGravity
		  >> m_iWeapon
		  >> m_iStrength
		  >> m_iDeadType
		  >> m_iDeadTime
		  >> m_iExplosionType;

	input.ignore(1);

	ReadTextField(input, m_szOnDestroy,    255);
	ReadTextField(input, m_szOnRegenerate, 255);

	ReadHex32Field(input, (char *)&m_iFlags1);
	ReadHex16Field(input, (char *)&m_iFlags2);

	return 1;
}

int CSpobResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "spob ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_SPOB_EDIT1, CCONTROL_TYPE_INT, IDS_STRING736);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_SPOB_EDIT41, CCONTROL_TYPE_STR256, IDS_STRING737);
	m_controls[1].SetString(m_szName);
	m_controls[2].Create(hwnd, IDC_EDIT_SPOB_EDIT2, CCONTROL_TYPE_INT, IDS_STRING738);
	m_controls[2].SetInt(m_iXPosition);
	m_controls[3].Create(hwnd, IDC_EDIT_SPOB_EDIT3, CCONTROL_TYPE_INT, IDS_STRING739);
	m_controls[3].SetInt(m_iYPosition);
	m_controls[4].Create(hwnd, IDC_EDIT_SPOB_EDIT42, CCONTROL_TYPE_INT, IDS_STRING740);
	m_controls[4].SetInt(m_iGraphics);
	m_controls[5].Create(hwnd, IDC_EDIT_SPOB_EDIT4, CCONTROL_TYPE_INT, IDS_STRING741);
	m_controls[5].SetInt(m_iTribute);
	m_controls[6].Create(hwnd, IDC_EDIT_SPOB_EDIT5, CCONTROL_TYPE_INT, IDS_STRING742);
	m_controls[6].SetInt(m_iTechLevel);
	m_controls[7].Create(hwnd, IDC_EDIT_SPOB_EDIT6, CCONTROL_TYPE_INT, IDS_STRING743);
	m_controls[7].SetInt(m_iSpecialTechs[0]);
	m_controls[8].Create(hwnd, IDC_EDIT_SPOB_EDIT7, CCONTROL_TYPE_INT, IDS_STRING743);
	m_controls[8].SetInt(m_iSpecialTechs[1]);
	m_controls[9].Create(hwnd, IDC_EDIT_SPOB_EDIT8, CCONTROL_TYPE_INT, IDS_STRING743);
	m_controls[9].SetInt(m_iSpecialTechs[2]);
	m_controls[10].Create(hwnd, IDC_EDIT_SPOB_EDIT9, CCONTROL_TYPE_INT, IDS_STRING743);
	m_controls[10].SetInt(m_iSpecialTechs[3]);
	m_controls[11].Create(hwnd, IDC_EDIT_SPOB_EDIT10, CCONTROL_TYPE_INT, IDS_STRING743);
	m_controls[11].SetInt(m_iSpecialTechs[4]);
	m_controls[12].Create(hwnd, IDC_EDIT_SPOB_EDIT11, CCONTROL_TYPE_INT, IDS_STRING743);
	m_controls[12].SetInt(m_iSpecialTechs[5]);
	m_controls[13].Create(hwnd, IDC_EDIT_SPOB_EDIT12, CCONTROL_TYPE_INT, IDS_STRING743);
	m_controls[13].SetInt(m_iSpecialTechs[6]);
	m_controls[14].Create(hwnd, IDC_EDIT_SPOB_EDIT13, CCONTROL_TYPE_INT, IDS_STRING743);
	m_controls[14].SetInt(m_iSpecialTechs[7]);
	m_controls[15].Create(hwnd, IDC_EDIT_SPOB_EDIT14, CCONTROL_TYPE_INT, IDS_STRING744);
	m_controls[15].SetInt(m_iGovernment);
	m_controls[16].Create(hwnd, IDC_EDIT_SPOB_EDIT15, CCONTROL_TYPE_INT, IDS_STRING745);
	m_controls[16].SetInt(m_iMinStatus);
	m_controls[17].Create(hwnd, IDC_EDIT_SPOB_EDIT16, CCONTROL_TYPE_INT, IDS_STRING746);
	m_controls[17].SetInt(m_iCustomPicture);
	m_controls[18].Create(hwnd, IDC_EDIT_SPOB_EDIT17, CCONTROL_TYPE_INT, IDS_STRING747);
	m_controls[18].SetInt(m_iCustomSound);
	m_controls[19].Create(hwnd, IDC_EDIT_SPOB_EDIT18, CCONTROL_TYPE_INT, IDS_STRING748);
	m_controls[19].SetInt(m_iDefenseDude);
	m_controls[20].Create(hwnd, IDC_EDIT_SPOB_EDIT19, CCONTROL_TYPE_INT, IDS_STRING749);
	m_controls[21].Create(hwnd, IDC_EDIT_SPOB_EDIT20, CCONTROL_TYPE_INT, IDS_STRING750);
	m_controls[21].SetInt(m_iAnimationDelay);
	m_controls[22].Create(hwnd, IDC_EDIT_SPOB_EDIT21, CCONTROL_TYPE_INT, IDS_STRING751);
	m_controls[22].SetInt(m_iFrame0Bias);
	m_controls[23].Create(hwnd, IDC_EDIT_SPOB_EDIT22, CCONTROL_TYPE_INT, IDS_STRING752);
	m_controls[23].SetInt(m_iHyperlinks[0]);
	m_controls[24].Create(hwnd, IDC_EDIT_SPOB_EDIT23, CCONTROL_TYPE_INT, IDS_STRING752);
	m_controls[24].SetInt(m_iHyperlinks[1]);
	m_controls[25].Create(hwnd, IDC_EDIT_SPOB_EDIT24, CCONTROL_TYPE_INT, IDS_STRING752);
	m_controls[25].SetInt(m_iHyperlinks[2]);
	m_controls[26].Create(hwnd, IDC_EDIT_SPOB_EDIT25, CCONTROL_TYPE_INT, IDS_STRING752);
	m_controls[26].SetInt(m_iHyperlinks[3]);
	m_controls[27].Create(hwnd, IDC_EDIT_SPOB_EDIT26, CCONTROL_TYPE_INT, IDS_STRING752);
	m_controls[27].SetInt(m_iHyperlinks[4]);
	m_controls[28].Create(hwnd, IDC_EDIT_SPOB_EDIT27, CCONTROL_TYPE_INT, IDS_STRING752);
	m_controls[28].SetInt(m_iHyperlinks[5]);
	m_controls[29].Create(hwnd, IDC_EDIT_SPOB_EDIT28, CCONTROL_TYPE_INT, IDS_STRING752);
	m_controls[29].SetInt(m_iHyperlinks[6]);
	m_controls[30].Create(hwnd, IDC_EDIT_SPOB_EDIT29, CCONTROL_TYPE_INT, IDS_STRING752);
	m_controls[30].SetInt(m_iHyperlinks[7]);
	m_controls[31].Create(hwnd, IDC_EDIT_SPOB_EDIT30, CCONTROL_TYPE_STR255, IDS_STRING753);
	m_controls[31].SetString(m_szOnDominate);
	m_controls[32].Create(hwnd, IDC_EDIT_SPOB_EDIT31, CCONTROL_TYPE_STR255, IDS_STRING754);
	m_controls[32].SetString(m_szOnRelease);
	m_controls[33].Create(hwnd, IDC_EDIT_SPOB_EDIT32, CCONTROL_TYPE_INT, IDS_STRING755);
	m_controls[33].SetInt(m_iLandingFee);
	m_controls[34].Create(hwnd, IDC_EDIT_SPOB_EDIT33, CCONTROL_TYPE_INT, IDS_STRING756);
	m_controls[34].SetInt(m_iGravity);
	m_controls[35].Create(hwnd, IDC_EDIT_SPOB_EDIT34, CCONTROL_TYPE_INT, IDS_STRING757);
	m_controls[35].SetInt(m_iWeapon);
	m_controls[36].Create(hwnd, IDC_EDIT_SPOB_EDIT35, CCONTROL_TYPE_INT, IDS_STRING758);
	m_controls[36].SetInt(m_iStrength);
	m_controls[37].Create(hwnd, IDC_EDIT_SPOB_EDIT36, CCONTROL_TYPE_INT, IDS_STRING759);
	m_controls[37].SetInt(m_iDeadType);
	m_controls[38].Create(hwnd, IDC_EDIT_SPOB_EDIT37, CCONTROL_TYPE_INT, IDS_STRING760);
	m_controls[38].SetInt(m_iDeadTime);
	m_controls[39].Create(hwnd, IDC_EDIT_SPOB_EDIT38, CCONTROL_TYPE_INT, IDS_STRING761);
	m_controls[39].SetInt(m_iExplosionType);
	m_controls[40].Create(hwnd, IDC_EDIT_SPOB_EDIT39, CCONTROL_TYPE_STR255, IDS_STRING762);
	m_controls[40].SetString(m_szOnDestroy);
	m_controls[41].Create(hwnd, IDC_EDIT_SPOB_EDIT40, CCONTROL_TYPE_STR255, IDS_STRING763);
	m_controls[41].SetString(m_szOnRegenerate);
	m_controls[42].Create(hwnd, IDC_EDIT_SPOB_CHECK1, CCONTROL_TYPE_CHECK, IDS_STRING788);
	m_controls[42].SetInt(m_iFlags1 & 0x00000001);
	m_controls[43].Create(hwnd, IDC_EDIT_SPOB_CHECK2, CCONTROL_TYPE_CHECK, IDS_STRING789);
	m_controls[43].SetInt(m_iFlags1 & 0x00000002);
	m_controls[44].Create(hwnd, IDC_EDIT_SPOB_CHECK3, CCONTROL_TYPE_CHECK, IDS_STRING790);
	m_controls[44].SetInt(m_iFlags1 & 0x00000004);
	m_controls[45].Create(hwnd, IDC_EDIT_SPOB_CHECK4, CCONTROL_TYPE_CHECK, IDS_STRING791);
	m_controls[45].SetInt(m_iFlags1 & 0x00000008);
	m_controls[46].Create(hwnd, IDC_EDIT_SPOB_CHECK5, CCONTROL_TYPE_CHECK, IDS_STRING794);
	m_controls[46].SetInt(m_iFlags1 & 0x00000040);
	m_controls[47].Create(hwnd, IDC_EDIT_SPOB_CHECK6, CCONTROL_TYPE_CHECK, IDS_STRING792);
	m_controls[47].SetInt(m_iFlags1 & 0x00000010);
	m_controls[48].Create(hwnd, IDC_EDIT_SPOB_CHECK7, CCONTROL_TYPE_CHECK, IDS_STRING793);
	m_controls[48].SetInt(m_iFlags1 & 0x00000020);
	m_controls[49].Create(hwnd, IDC_EDIT_SPOB_CHECK19, CCONTROL_TYPE_CHECK, IDS_STRING795);
	m_controls[49].SetInt(m_iFlags1 & 0x00000080);
	m_controls[50].Create(hwnd, IDC_EDIT_SPOB_COMBO1, CCONTROL_TYPE_COMBOBOX, IDS_STRING764);
	m_controls[50].SetComboStrings(NUM_SPOB_COMMODITYPRICE_CHOICES, g_szSpobCommodityPriceChoices);
	m_controls[51].Create(hwnd, IDC_EDIT_SPOB_COMBO2, CCONTROL_TYPE_COMBOBOX, IDS_STRING768);
	m_controls[51].SetComboStrings(NUM_SPOB_COMMODITYPRICE_CHOICES, g_szSpobCommodityPriceChoices);
	m_controls[52].Create(hwnd, IDC_EDIT_SPOB_COMBO3, CCONTROL_TYPE_COMBOBOX, IDS_STRING772);
	m_controls[52].SetComboStrings(NUM_SPOB_COMMODITYPRICE_CHOICES, g_szSpobCommodityPriceChoices);
	m_controls[53].Create(hwnd, IDC_EDIT_SPOB_COMBO4, CCONTROL_TYPE_COMBOBOX, IDS_STRING776);
	m_controls[53].SetComboStrings(NUM_SPOB_COMMODITYPRICE_CHOICES, g_szSpobCommodityPriceChoices);
	m_controls[54].Create(hwnd, IDC_EDIT_SPOB_COMBO5, CCONTROL_TYPE_COMBOBOX, IDS_STRING780);
	m_controls[54].SetComboStrings(NUM_SPOB_COMMODITYPRICE_CHOICES, g_szSpobCommodityPriceChoices);
	m_controls[55].Create(hwnd, IDC_EDIT_SPOB_COMBO6, CCONTROL_TYPE_COMBOBOX, IDS_STRING784);
	m_controls[55].SetComboStrings(NUM_SPOB_COMMODITYPRICE_CHOICES, g_szSpobCommodityPriceChoices);
	m_controls[56].Create(hwnd, IDC_EDIT_SPOB_CHECK8, CCONTROL_TYPE_CHECK, IDS_STRING796);
	m_controls[56].SetInt(m_iFlags2 & 0x0001);
	m_controls[57].Create(hwnd, IDC_EDIT_SPOB_CHECK9, CCONTROL_TYPE_CHECK, IDS_STRING797);
	m_controls[57].SetInt(m_iFlags2 & 0x0002);
	m_controls[58].Create(hwnd, IDC_EDIT_SPOB_CHECK10, CCONTROL_TYPE_CHECK, IDS_STRING798);
	m_controls[58].SetInt(m_iFlags2 & 0x0010);
	m_controls[59].Create(hwnd, IDC_EDIT_SPOB_CHECK11, CCONTROL_TYPE_CHECK, IDS_STRING799);
	m_controls[59].SetInt(m_iFlags2 & 0x0020);
	m_controls[60].Create(hwnd, IDC_EDIT_SPOB_CHECK12, CCONTROL_TYPE_CHECK, IDS_STRING800);
	m_controls[60].SetInt(m_iFlags2 & 0x0040);
	m_controls[61].Create(hwnd, IDC_EDIT_SPOB_CHECK13, CCONTROL_TYPE_CHECK, IDS_STRING801);
	m_controls[61].SetInt(m_iFlags2 & 0x0080);
	m_controls[62].Create(hwnd, IDC_EDIT_SPOB_CHECK14, CCONTROL_TYPE_CHECK, IDS_STRING802);
	m_controls[62].SetInt(m_iFlags2 & 0x0100);
	m_controls[63].Create(hwnd, IDC_EDIT_SPOB_CHECK15, CCONTROL_TYPE_CHECK, IDS_STRING803);
	m_controls[63].SetInt(m_iFlags2 & 0x0200);
	m_controls[64].Create(hwnd, IDC_EDIT_SPOB_CHECK16, CCONTROL_TYPE_CHECK, IDS_STRING804);
	m_controls[64].SetInt(m_iFlags2 & 0x0400);
	m_controls[65].Create(hwnd, IDC_EDIT_SPOB_CHECK17, CCONTROL_TYPE_CHECK, IDS_STRING805);
	m_controls[65].SetInt(m_iFlags2 & 0x1000);
	m_controls[66].Create(hwnd, IDC_EDIT_SPOB_CHECK18, CCONTROL_TYPE_CHECK, IDS_STRING806);
	m_controls[66].SetInt(m_iFlags2 & 0x2000);
	m_controls[67].Create(hwnd, IDC_EDIT_SPOB_CHECK20, CCONTROL_TYPE_CHECK, IDS_STRING807);
	m_controls[68].Create(hwnd, IDC_EDIT_SPOB_EDIT43, CCONTROL_TYPE_INT, IDS_STRING808);

	if(m_iFlags1 & 0x10000000)
		m_controls[50].SetInt(3);
	else if(m_iFlags1 & 0x20000000)
		m_controls[50].SetInt(2);
	else if(m_iFlags1 & 0x40000000)
		m_controls[50].SetInt(1);
	else
		m_controls[50].SetInt(0);

	if(m_iFlags1 & 0x01000000)
		m_controls[51].SetInt(3);
	else if(m_iFlags1 & 0x02000000)
		m_controls[51].SetInt(2);
	else if(m_iFlags1 & 0x04000000)
		m_controls[51].SetInt(1);
	else
		m_controls[51].SetInt(0);

	if(m_iFlags1 & 0x00100000)
		m_controls[52].SetInt(3);
	else if(m_iFlags1 & 0x00200000)
		m_controls[52].SetInt(2);
	else if(m_iFlags1 & 0x00400000)
		m_controls[52].SetInt(1);
	else
		m_controls[52].SetInt(0);

	if(m_iFlags1 & 0x00010000)
		m_controls[53].SetInt(3);
	else if(m_iFlags1 & 0x00020000)
		m_controls[53].SetInt(2);
	else if(m_iFlags1 & 0x00040000)
		m_controls[53].SetInt(1);
	else
		m_controls[53].SetInt(0);

	if(m_iFlags1 & 0x00001000)
		m_controls[54].SetInt(3);
	else if(m_iFlags1 & 0x00002000)
		m_controls[54].SetInt(2);
	else if(m_iFlags1 & 0x00004000)
		m_controls[54].SetInt(1);
	else
		m_controls[54].SetInt(0);

	if(m_iFlags1 & 0x00000100)
		m_controls[55].SetInt(3);
	else if(m_iFlags1 & 0x00000200)
		m_controls[55].SetInt(2);
	else if(m_iFlags1 & 0x00000400)
		m_controls[55].SetInt(1);
	else
		m_controls[55].SetInt(0);

	if(m_iDefenseCount >= 1000)
	{
		m_controls[20].SetInt(m_iDefenseCount / 10 - 100);
		m_controls[67].SetInt(1);
		m_controls[68].SetInt(m_iDefenseCount % 10);

		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_SPOB_TEXT23), SW_SHOW);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_SPOB_EDIT43), SW_SHOW);
	}
	else
	{
		m_controls[20].SetInt(m_iDefenseCount);
		m_controls[67].SetInt(0);
		m_controls[68].SetInt(0);

		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_SPOB_TEXT23), SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_SPOB_EDIT43), SW_HIDE);
	}

	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SPOB_TEXT9),  ToString(m_iID).c_str());
	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SPOB_TEXT10), ToString(m_iID + 10000 - 128).c_str());

	if(m_iFlags1 & 0x00000040)
	{
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_SPOB_TEXT8),  SW_SHOW);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_SPOB_TEXT10), SW_SHOW);
	}
	else
	{
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_SPOB_TEXT8),  SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDC_EDIT_SPOB_TEXT10), SW_HIDE);
	}

	return 1;
}

int CSpobResource::CloseAndSave(void)
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

	m_iXPosition = m_controls[2].GetInt();
	m_iYPosition = m_controls[3].GetInt();

	m_iGraphics  = m_controls[4].GetInt();

	m_iTribute   = m_controls[5].GetInt();

	m_iTechLevel = m_controls[6].GetInt();

	m_iSpecialTechs[0] = m_controls[7].GetInt();
	m_iSpecialTechs[1] = m_controls[8].GetInt();
	m_iSpecialTechs[2] = m_controls[9].GetInt();
	m_iSpecialTechs[3] = m_controls[10].GetInt();
	m_iSpecialTechs[4] = m_controls[11].GetInt();
	m_iSpecialTechs[5] = m_controls[12].GetInt();
	m_iSpecialTechs[6] = m_controls[13].GetInt();
	m_iSpecialTechs[7] = m_controls[14].GetInt();

	m_iGovernment = m_controls[15].GetInt();
	m_iMinStatus  = m_controls[16].GetInt();

	m_iCustomPicture = m_controls[17].GetInt();
	m_iCustomSound   = m_controls[18].GetInt();

	m_iDefenseDude  = m_controls[19].GetInt();
	m_iDefenseCount = m_controls[20].GetInt();

	m_iAnimationDelay = m_controls[21].GetInt();
	m_iFrame0Bias     = m_controls[22].GetInt();

	m_iHyperlinks[0] = m_controls[23].GetInt();
	m_iHyperlinks[1] = m_controls[24].GetInt();
	m_iHyperlinks[2] = m_controls[25].GetInt();
	m_iHyperlinks[3] = m_controls[26].GetInt();
	m_iHyperlinks[4] = m_controls[27].GetInt();
	m_iHyperlinks[5] = m_controls[28].GetInt();
	m_iHyperlinks[6] = m_controls[29].GetInt();
	m_iHyperlinks[7] = m_controls[30].GetInt();

	strcpy_s(m_szOnDominate, m_controls[31].GetString());
	strcpy_s(m_szOnRelease,  m_controls[32].GetString());

	m_iLandingFee = m_controls[33].GetInt();

	m_iGravity  = m_controls[34].GetInt();
	m_iWeapon   = m_controls[35].GetInt();
	m_iStrength = m_controls[36].GetInt();

	m_iDeadType = m_controls[37].GetInt();
	m_iDeadTime = m_controls[38].GetInt();

	m_iExplosionType = m_controls[39].GetInt();

	strcpy_s(m_szOnDestroy,    m_controls[40].GetString());
	strcpy_s(m_szOnRegenerate, m_controls[41].GetString());

	m_iFlags1 = 0x00000000;
	m_iFlags2 = 0x0000;

	m_iFlags1 |= m_controls[42].GetInt() << 0;
	m_iFlags1 |= m_controls[43].GetInt() << 1;
	m_iFlags1 |= m_controls[44].GetInt() << 2;
	m_iFlags1 |= m_controls[45].GetInt() << 3;
	m_iFlags1 |= m_controls[46].GetInt() << 6;
	m_iFlags1 |= m_controls[47].GetInt() << 4;
	m_iFlags1 |= m_controls[48].GetInt() << 5;
	m_iFlags1 |= m_controls[49].GetInt() << 7;

	if(m_controls[50].GetInt() == 1)
		m_iFlags1 |= 0x40000000;
	else if(m_controls[50].GetInt() == 2)
		m_iFlags1 |= 0x20000000;
	else if(m_controls[50].GetInt() == 3)
		m_iFlags1 |= 0x10000000;

	if(m_controls[51].GetInt() == 1)
		m_iFlags1 |= 0x04000000;
	else if(m_controls[51].GetInt() == 2)
		m_iFlags1 |= 0x02000000;
	else if(m_controls[51].GetInt() == 3)
		m_iFlags1 |= 0x01000000;

	if(m_controls[52].GetInt() == 1)
		m_iFlags1 |= 0x00400000;
	else if(m_controls[52].GetInt() == 2)
		m_iFlags1 |= 0x00200000;
	else if(m_controls[52].GetInt() == 3)
		m_iFlags1 |= 0x00100000;

	if(m_controls[53].GetInt() == 1)
		m_iFlags1 |= 0x00040000;
	else if(m_controls[53].GetInt() == 2)
		m_iFlags1 |= 0x00020000;
	else if(m_controls[53].GetInt() == 3)
		m_iFlags1 |= 0x00010000;

	if(m_controls[54].GetInt() == 1)
		m_iFlags1 |= 0x00004000;
	else if(m_controls[54].GetInt() == 2)
		m_iFlags1 |= 0x00002000;
	else if(m_controls[54].GetInt() == 3)
		m_iFlags1 |= 0x00001000;

	if(m_controls[55].GetInt() == 1)
		m_iFlags1 |= 0x00000400;
	else if(m_controls[55].GetInt() == 2)
		m_iFlags1 |= 0x00000200;
	else if(m_controls[55].GetInt() == 3)
		m_iFlags1 |= 0x00000100;

	m_iFlags2 |= m_controls[56].GetInt() << 0;
	m_iFlags2 |= m_controls[57].GetInt() << 1;
	m_iFlags2 |= m_controls[58].GetInt() << 4;
	m_iFlags2 |= m_controls[59].GetInt() << 5;
	m_iFlags2 |= m_controls[60].GetInt() << 6;
	m_iFlags2 |= m_controls[61].GetInt() << 7;
	m_iFlags2 |= m_controls[62].GetInt() << 8;
	m_iFlags2 |= m_controls[63].GetInt() << 9;
	m_iFlags2 |= m_controls[64].GetInt() << 10;
	m_iFlags2 |= m_controls[65].GetInt() << 12;
	m_iFlags2 |= m_controls[66].GetInt() << 13;

	if(m_controls[67].GetInt() == 1)
		m_iDefenseCount = 10 * m_iDefenseCount + (m_controls[68].GetInt() % 10) + 1000;
	else
		m_iDefenseCount %= 1000;

	int i;

	for(i = 0; i < NUM_SPOB_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CSpobResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_SPOB_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CSpobResource::SpobDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CSpobResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CSpobResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_SPOB_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_SPOB_OK)
			{
				pResource->CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_SPOB_CONTROLS; i++)
				{
					if(iControlID == pResource->m_controls[i].GetControlID())
					{
						pResource->m_controls[i].ProcessMessage(iNotifyCode);

						break;
					}
				}
			}

			if((iControlID == IDC_EDIT_SPOB_EDIT1) && (iNotifyCode == EN_CHANGE))
			{
				if((pResource->m_controls[0].GetInt() >= 128) && (pResource->m_controls[0].GetInt() < 2176))
				{
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SPOB_TEXT9),  ToString(pResource->m_controls[0].GetInt()).c_str());
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SPOB_TEXT10), ToString(pResource->m_controls[0].GetInt() + 10000 - 128).c_str());
				}
			}

			if((iControlID == IDC_EDIT_SPOB_CHECK20) && (iNotifyCode == BN_CLICKED))
			{
				if(Button_GetCheck((HWND)lparam) == BST_CHECKED)
				{
					ShowWindow(GetDlgItem(hwnd, IDC_EDIT_SPOB_TEXT23), SW_SHOW);
					ShowWindow(GetDlgItem(hwnd, IDC_EDIT_SPOB_EDIT43), SW_SHOW);
				}
				else
				{
					ShowWindow(GetDlgItem(hwnd, IDC_EDIT_SPOB_TEXT23), SW_HIDE);
					ShowWindow(GetDlgItem(hwnd, IDC_EDIT_SPOB_EDIT43), SW_HIDE);
				}
			}

			if((iControlID == IDC_EDIT_SPOB_CHECK5) && (iNotifyCode == BN_CLICKED))
			{
				if(Button_GetCheck((HWND)lparam) == BST_CHECKED)
				{
					ShowWindow(GetDlgItem(hwnd, IDC_EDIT_SPOB_TEXT8),  SW_SHOW);
					ShowWindow(GetDlgItem(hwnd, IDC_EDIT_SPOB_TEXT10), SW_SHOW);
				}
				else
				{
					ShowWindow(GetDlgItem(hwnd, IDC_EDIT_SPOB_TEXT8),  SW_HIDE);
					ShowWindow(GetDlgItem(hwnd, IDC_EDIT_SPOB_TEXT10), SW_HIDE);
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
