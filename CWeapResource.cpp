// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CWeapResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CWeapResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CWeapResource::CWeapResource(void)
{
	m_iReload   = 1;
	m_iLifetime = 30;

	m_iMassDamage   = 1;
	m_iEnergyDamage = 1;

	m_iGuidance = -1;
	m_iSpeed    =  1;
	m_iAmmoType = -1;

	m_iGraphics = 0;

	m_iInaccuracy = 0;

	m_iSound = -1;

	m_iImpact          =  0;
	m_iExplosionType   = -1;
	m_iProximityRadius =  0;
	m_iBlastRadius     =  0;

	m_iSmokeSet = -1;

	m_iDecay = 0;

	m_iParticleCount    = 0;
	m_iParticleVelocity = 0;
	m_iParticleMinLife  = 0;
	m_iParticleMaxLife  = 0;
	m_iParticleColor    = 0x00000000;

	m_iBeamLength  = 0;
	m_iBeamWidth   = 0;
	m_iBeamFalloff = 0;
	m_iBeamColor   = 0x00000000;
	m_iCoronaColor = 0x00000000;

	m_iSubmunitionsCount = 0;
	m_iSubmunitionsType  = 0;
	m_iSubmunitionsAngle = 0;
	m_iSubmunitionsLimit = 0;

	m_iProximityDelay = 0;

	m_iIonization = 0;

	m_iHitParticleCount    = 0;
	m_iHitParticleLife     = 0;
	m_iHitParticleVelocity = 0;
	m_iHitParticleColor    = 0x00000000;

	m_iExitType = -1;

	m_iBurstCount  = 0;
	m_iBurstReload = 0;

	int i;

	for(i = 0; i < 4; i++)
		m_iJammingVulnerability[i] = 0;

	m_iDurability = 0;

	m_iGuidedTurnRate = 0;

	m_iMaxAmmo = 0;

	m_iRecoil = 0;

	m_iLightningDensity   = 0;
	m_iLightningAmplitude = 0;

	m_iIonizationColor = 0x00000000;

	m_iFlags1      = 0x0000;
	m_iFlags2      = 0x0000;
	m_iFlags3      = 0x0000;
	m_iSeekerFlags = 0x0000;
}

CWeapResource::~CWeapResource(void)
{

}

int CWeapResource::GetType(void)
{
	return CNR_TYPE_WEAP;
}

int CWeapResource::GetSize(void)
{
	return 134;
}

int CWeapResource::GetDialogID(void)
{
	return IDD_EDIT_WEAP;
}

DLGPROCNOCALLBACK CWeapResource::GetDialogProc(void)
{
	return WeapDlgProc;
}

int CWeapResource::GetNumFields(void)
{
	return NUM_WEAP_FIELDS;
}

const std::string * CWeapResource::GetFieldNames(void)
{
	return g_szWeapFields;
}

int CWeapResource::Save(char *pOutput)
{
	SwapEndians();

	*(short *)pOutput = m_iReload;                  pOutput += sizeof(short);
	*(short *)pOutput = m_iLifetime;                pOutput += sizeof(short);
	*(short *)pOutput = m_iMassDamage;              pOutput += sizeof(short);
	*(short *)pOutput = m_iEnergyDamage;            pOutput += sizeof(short);
	*(short *)pOutput = m_iGuidance;                pOutput += sizeof(short);
	*(short *)pOutput = m_iSpeed;                   pOutput += sizeof(short);
	*(short *)pOutput = m_iAmmoType;                pOutput += sizeof(short);
	*(short *)pOutput = m_iGraphics;                pOutput += sizeof(short);
	*(short *)pOutput = m_iInaccuracy;              pOutput += sizeof(short);
	*(short *)pOutput = m_iSound;                   pOutput += sizeof(short);
	*(short *)pOutput = m_iImpact;                  pOutput += sizeof(short);
	*(short *)pOutput = m_iExplosionType;           pOutput += sizeof(short);
	*(short *)pOutput = m_iProximityRadius;         pOutput += sizeof(short);
	*(short *)pOutput = m_iBlastRadius;             pOutput += sizeof(short);
	*(USHORT *)pOutput = m_iFlags1;                 pOutput += sizeof(USHORT);
	*(USHORT *)pOutput = m_iSeekerFlags;            pOutput += sizeof(USHORT);
	*(short *)pOutput = m_iSmokeSet;                pOutput += sizeof(short);
	*(short *)pOutput = m_iDecay;                   pOutput += sizeof(short);
	*(short *)pOutput = m_iParticleCount;           pOutput += sizeof(short);
	*(short *)pOutput = m_iParticleVelocity;        pOutput += sizeof(short);
	*(short *)pOutput = m_iParticleMinLife;         pOutput += sizeof(short);
	*(short *)pOutput = m_iParticleMaxLife;         pOutput += sizeof(short);
	*(UINT  *)pOutput = m_iParticleColor;           pOutput += sizeof(UINT);
	*(short *)pOutput = m_iBeamLength;              pOutput += sizeof(short);
	*(short *)pOutput = m_iBeamWidth;               pOutput += sizeof(short);
	*(short *)pOutput = m_iBeamFalloff;             pOutput += sizeof(short);
	*(UINT  *)pOutput = m_iBeamColor;               pOutput += sizeof(UINT);
	*(UINT  *)pOutput = m_iCoronaColor;             pOutput += sizeof(UINT);
	*(short *)pOutput = m_iSubmunitionsCount;       pOutput += sizeof(short);
	*(short *)pOutput = m_iSubmunitionsType;        pOutput += sizeof(short);
	*(short *)pOutput = m_iSubmunitionsAngle;       pOutput += sizeof(short);
	*(short *)pOutput = m_iSubmunitionsLimit;       pOutput += sizeof(short);
	*(short *)pOutput = m_iProximityDelay;          pOutput += sizeof(short);
	*(USHORT *)pOutput = m_iFlags2;                 pOutput += sizeof(USHORT);
	*(short *)pOutput = m_iIonization;              pOutput += sizeof(short);
	*(short *)pOutput = m_iHitParticleCount;        pOutput += sizeof(short);
	*(short *)pOutput = m_iHitParticleLife;         pOutput += sizeof(short);
	*(short *)pOutput = m_iHitParticleVelocity;     pOutput += sizeof(short);
	*(UINT  *)pOutput = m_iHitParticleColor;        pOutput += sizeof(UINT);
	*(short *)pOutput = m_iRecoil;                  pOutput += sizeof(short);
	*(short *)pOutput = m_iExitType;                pOutput += sizeof(short);
	*(short *)pOutput = m_iBurstCount;              pOutput += sizeof(short);
	*(short *)pOutput = m_iBurstReload;             pOutput += sizeof(short);
	*(short *)pOutput = m_iJammingVulnerability[0]; pOutput += sizeof(short);
	*(short *)pOutput = m_iJammingVulnerability[1]; pOutput += sizeof(short);
	*(short *)pOutput = m_iJammingVulnerability[2]; pOutput += sizeof(short);
	*(short *)pOutput = m_iJammingVulnerability[3]; pOutput += sizeof(short);
	*(USHORT *)pOutput = m_iFlags3;                 pOutput += sizeof(USHORT);
	*(short *)pOutput = m_iDurability;              pOutput += sizeof(short);
	*(short *)pOutput = m_iGuidedTurnRate;          pOutput += sizeof(short);
	*(short *)pOutput = m_iMaxAmmo;                 pOutput += sizeof(short);
	*(short *)pOutput = m_iLightningDensity;        pOutput += sizeof(short);
	*(short *)pOutput = m_iLightningAmplitude;      pOutput += sizeof(short);
	*(UINT  *)pOutput = m_iIonizationColor;         pOutput += sizeof(UINT);

	SwapEndians();

	return 1;
}

int CWeapResource::Load(char *pInput, int iSize)
{
	m_iReload                  = *(short *)pInput; pInput += sizeof(short);
	m_iLifetime                = *(short *)pInput; pInput += sizeof(short);
	m_iMassDamage              = *(short *)pInput; pInput += sizeof(short);
	m_iEnergyDamage            = *(short *)pInput; pInput += sizeof(short);
	m_iGuidance                = *(short *)pInput; pInput += sizeof(short);
	m_iSpeed                   = *(short *)pInput; pInput += sizeof(short);
	m_iAmmoType                = *(short *)pInput; pInput += sizeof(short);
	m_iGraphics                = *(short *)pInput; pInput += sizeof(short);
	m_iInaccuracy              = *(short *)pInput; pInput += sizeof(short);
	m_iSound                   = *(short *)pInput; pInput += sizeof(short);
	m_iImpact                  = *(short *)pInput; pInput += sizeof(short);
	m_iExplosionType           = *(short *)pInput; pInput += sizeof(short);
	m_iProximityRadius         = *(short *)pInput; pInput += sizeof(short);
	m_iBlastRadius             = *(short *)pInput; pInput += sizeof(short);
	m_iFlags1                  = *(USHORT *)pInput; pInput += sizeof(USHORT);
	m_iSeekerFlags             = *(USHORT *)pInput; pInput += sizeof(USHORT);
	m_iSmokeSet                = *(short *)pInput; pInput += sizeof(short);
	m_iDecay                   = *(short *)pInput; pInput += sizeof(short);
	m_iParticleCount           = *(short *)pInput; pInput += sizeof(short);
	m_iParticleVelocity        = *(short *)pInput; pInput += sizeof(short);
	m_iParticleMinLife         = *(short *)pInput; pInput += sizeof(short);
	m_iParticleMaxLife         = *(short *)pInput; pInput += sizeof(short);
	m_iParticleColor           = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iBeamLength              = *(short *)pInput; pInput += sizeof(short);
	m_iBeamWidth               = *(short *)pInput; pInput += sizeof(short);
	m_iBeamFalloff             = *(short *)pInput; pInput += sizeof(short);
	m_iBeamColor               = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iCoronaColor             = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iSubmunitionsCount       = *(short *)pInput; pInput += sizeof(short);
	m_iSubmunitionsType        = *(short *)pInput; pInput += sizeof(short);
	m_iSubmunitionsAngle       = *(short *)pInput; pInput += sizeof(short);
	m_iSubmunitionsLimit       = *(short *)pInput; pInput += sizeof(short);
	m_iProximityDelay          = *(short *)pInput; pInput += sizeof(short);
	m_iFlags2                  = *(USHORT *)pInput; pInput += sizeof(USHORT);
	m_iIonization              = *(short *)pInput; pInput += sizeof(short);
	m_iHitParticleCount        = *(short *)pInput; pInput += sizeof(short);
	m_iHitParticleLife         = *(short *)pInput; pInput += sizeof(short);
	m_iHitParticleVelocity     = *(short *)pInput; pInput += sizeof(short);
	m_iHitParticleColor        = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iRecoil                  = *(short *)pInput; pInput += sizeof(short);
	m_iExitType                = *(short *)pInput; pInput += sizeof(short);
	m_iBurstCount              = *(short *)pInput; pInput += sizeof(short);
	m_iBurstReload             = *(short *)pInput; pInput += sizeof(short);
	m_iJammingVulnerability[0] = *(short *)pInput; pInput += sizeof(short);
	m_iJammingVulnerability[1] = *(short *)pInput; pInput += sizeof(short);
	m_iJammingVulnerability[2] = *(short *)pInput; pInput += sizeof(short);
	m_iJammingVulnerability[3] = *(short *)pInput; pInput += sizeof(short);
	m_iFlags3                  = *(USHORT *)pInput; pInput += sizeof(USHORT);
	m_iDurability              = *(short *)pInput; pInput += sizeof(short);
	m_iGuidedTurnRate          = *(short *)pInput; pInput += sizeof(short);
	m_iMaxAmmo                 = *(short *)pInput; pInput += sizeof(short);
	m_iLightningDensity        = *(short *)pInput; pInput += sizeof(short);
	m_iLightningAmplitude      = *(short *)pInput; pInput += sizeof(short);
	m_iIonizationColor         = *(UINT  *)pInput; pInput += sizeof(UINT);

	SwapEndians();

	return 1;
}

int CWeapResource::SwapEndians(void)
{
	m_iReload                  = SwapEndianShort(m_iReload);
	m_iLifetime                = SwapEndianShort(m_iLifetime);
	m_iMassDamage              = SwapEndianShort(m_iMassDamage);
	m_iEnergyDamage            = SwapEndianShort(m_iEnergyDamage);
	m_iGuidance                = SwapEndianShort(m_iGuidance);
	m_iSpeed                   = SwapEndianShort(m_iSpeed);
	m_iAmmoType                = SwapEndianShort(m_iAmmoType);
	m_iGraphics                = SwapEndianShort(m_iGraphics);
	m_iInaccuracy              = SwapEndianShort(m_iInaccuracy);
	m_iSound                   = SwapEndianShort(m_iSound);
	m_iImpact                  = SwapEndianShort(m_iImpact);
	m_iExplosionType           = SwapEndianShort(m_iExplosionType);
	m_iProximityRadius         = SwapEndianShort(m_iProximityRadius);
	m_iBlastRadius             = SwapEndianShort(m_iBlastRadius);
	m_iFlags1                  = SwapEndianShort(m_iFlags1);
	m_iSeekerFlags             = SwapEndianShort(m_iSeekerFlags);
	m_iSmokeSet                = SwapEndianShort(m_iSmokeSet);
	m_iDecay                   = SwapEndianShort(m_iDecay);
	m_iParticleCount           = SwapEndianShort(m_iParticleCount);
	m_iParticleVelocity        = SwapEndianShort(m_iParticleVelocity);
	m_iParticleMinLife         = SwapEndianShort(m_iParticleMinLife);
	m_iParticleMaxLife         = SwapEndianShort(m_iParticleMaxLife);
	m_iParticleColor           = SwapEndianInt(m_iParticleColor);
	m_iBeamLength              = SwapEndianShort(m_iBeamLength);
	m_iBeamWidth               = SwapEndianShort(m_iBeamWidth);
	m_iBeamFalloff             = SwapEndianShort(m_iBeamFalloff);
	m_iBeamColor               = SwapEndianInt(m_iBeamColor);
	m_iCoronaColor             = SwapEndianInt(m_iCoronaColor);
	m_iSubmunitionsCount       = SwapEndianShort(m_iSubmunitionsCount);
	m_iSubmunitionsType        = SwapEndianShort(m_iSubmunitionsType);
	m_iSubmunitionsAngle       = SwapEndianShort(m_iSubmunitionsAngle);
	m_iSubmunitionsLimit       = SwapEndianShort(m_iSubmunitionsLimit);
	m_iProximityDelay          = SwapEndianShort(m_iProximityDelay);
	m_iFlags2                  = SwapEndianShort(m_iFlags2);
	m_iIonization              = SwapEndianShort(m_iIonization);
	m_iHitParticleCount        = SwapEndianShort(m_iHitParticleCount);
	m_iHitParticleLife         = SwapEndianShort(m_iHitParticleLife);
	m_iHitParticleVelocity     = SwapEndianShort(m_iHitParticleVelocity);
	m_iHitParticleColor        = SwapEndianInt(m_iHitParticleColor);
	m_iExitType                = SwapEndianShort(m_iExitType);
	m_iBurstCount              = SwapEndianShort(m_iBurstCount);
	m_iBurstReload             = SwapEndianShort(m_iBurstReload);
	m_iJammingVulnerability[0] = SwapEndianShort(m_iJammingVulnerability[0]);
	m_iJammingVulnerability[1] = SwapEndianShort(m_iJammingVulnerability[1]);
	m_iJammingVulnerability[2] = SwapEndianShort(m_iJammingVulnerability[2]);
	m_iJammingVulnerability[3] = SwapEndianShort(m_iJammingVulnerability[3]);
	m_iFlags3                  = SwapEndianShort(m_iFlags3);
	m_iDurability              = SwapEndianShort(m_iDurability);
	m_iGuidedTurnRate          = SwapEndianShort(m_iGuidedTurnRate);
	m_iMaxAmmo                 = SwapEndianShort(m_iMaxAmmo);
	m_iRecoil                  = SwapEndianShort(m_iRecoil);
	m_iLightningDensity        = SwapEndianShort(m_iLightningDensity);
	m_iLightningAmplitude      = SwapEndianShort(m_iLightningAmplitude);
	m_iIonizationColor         = SwapEndianInt(m_iIonizationColor);

	return 1;
}

int CWeapResource::SaveToText(std::ostream & output)
{
	output << m_iReload           << '\t'
		   << m_iLifetime         << '\t'
		   << m_iMassDamage       << '\t'
		   << m_iEnergyDamage     << '\t'
		   << m_iGuidance         << '\t'
		   << m_iSpeed            << '\t'
		   << m_iAmmoType         << '\t'
		   << m_iGraphics         << '\t'
		   << m_iInaccuracy       << '\t'
		   << m_iSound            << '\t'
		   << m_iImpact           << '\t'
		   << m_iExplosionType    << '\t'
		   << m_iProximityRadius  << '\t'
		   << m_iBlastRadius      << '\t'
		   << m_iSmokeSet         << '\t'
		   << m_iDecay            << '\t'
		   << m_iParticleCount    << '\t'
		   << m_iParticleVelocity << '\t'
		   << m_iParticleMinLife  << '\t'
		   << m_iParticleMaxLife  << '\t';

	PrintHex32Field(output, (char *)&m_iParticleColor, '\t');

	output << m_iBeamLength  << '\t'
		   << m_iBeamWidth   << '\t'
		   << m_iBeamFalloff << '\t';

	PrintHex32Field(output, (char *)&m_iBeamColor,   '\t');
	PrintHex32Field(output, (char *)&m_iCoronaColor, '\t');

	output << m_iSubmunitionsCount   << '\t'
		   << m_iSubmunitionsType    << '\t'
		   << m_iSubmunitionsAngle   << '\t'
		   << m_iSubmunitionsLimit   << '\t'
		   << m_iProximityDelay      << '\t'
		   << m_iIonization          << '\t'
		   << m_iHitParticleCount    << '\t'
		   << m_iHitParticleLife     << '\t'
		   << m_iHitParticleVelocity << '\t';

	PrintHex32Field(output, (char *)&m_iHitParticleColor, '\t');

	output << m_iExitType                << '\t'
		   << m_iBurstCount              << '\t'
		   << m_iBurstReload             << '\t'
		   << m_iJammingVulnerability[0] << '\t'
		   << m_iJammingVulnerability[1] << '\t'
		   << m_iJammingVulnerability[2] << '\t'
		   << m_iJammingVulnerability[3] << '\t'
		   << m_iDurability              << '\t'
		   << m_iGuidedTurnRate          << '\t'
		   << m_iMaxAmmo                 << '\t'
		   << m_iRecoil                  << '\t'
		   << m_iLightningDensity        << '\t'
		   << m_iLightningAmplitude      << '\t';

	PrintHex32Field(output, (char *)&m_iIonizationColor, '\t');

	PrintHex16Field(output, (char *)&m_iFlags1,      '\t');
	PrintHex16Field(output, (char *)&m_iFlags2,      '\t');
	PrintHex16Field(output, (char *)&m_iFlags3,      '\t');
	PrintHex16Field(output, (char *)&m_iSeekerFlags, '\t');

	return 1;
}

int CWeapResource::LoadFromText(std::istream & input)
{
	input >> m_iReload
		  >> m_iLifetime
		  >> m_iMassDamage
		  >> m_iEnergyDamage
		  >> m_iGuidance
		  >> m_iSpeed
		  >> m_iAmmoType
		  >> m_iGraphics
		  >> m_iInaccuracy
		  >> m_iSound
		  >> m_iImpact
		  >> m_iExplosionType
		  >> m_iProximityRadius
		  >> m_iBlastRadius
		  >> m_iSmokeSet
		  >> m_iDecay
		  >> m_iParticleCount
		  >> m_iParticleVelocity
		  >> m_iParticleMinLife
		  >> m_iParticleMaxLife;

	ReadHex32Field(input, (char *)&m_iParticleColor);

	input >> m_iBeamLength
		  >> m_iBeamWidth
		  >> m_iBeamFalloff;

	ReadHex32Field(input, (char *)&m_iBeamColor);
	ReadHex32Field(input, (char *)&m_iCoronaColor);

	input >> m_iSubmunitionsCount
		  >> m_iSubmunitionsType
		  >> m_iSubmunitionsAngle
		  >> m_iSubmunitionsLimit
		  >> m_iProximityDelay
		  >> m_iIonization
		  >> m_iHitParticleCount
		  >> m_iHitParticleLife
		  >> m_iHitParticleVelocity;

	ReadHex32Field(input, (char *)&m_iHitParticleColor);

	input >> m_iExitType
		  >> m_iBurstCount
		  >> m_iBurstReload
		  >> m_iJammingVulnerability[0]
		  >> m_iJammingVulnerability[1]
		  >> m_iJammingVulnerability[2]
		  >> m_iJammingVulnerability[3]
		  >> m_iDurability
		  >> m_iGuidedTurnRate
		  >> m_iMaxAmmo
		  >> m_iRecoil
		  >> m_iLightningDensity
		  >> m_iLightningAmplitude;

	ReadHex32Field(input, (char *)&m_iIonizationColor);

	ReadHex16Field(input, (char *)&m_iFlags1);
	ReadHex16Field(input, (char *)&m_iFlags2);
	ReadHex16Field(input, (char *)&m_iFlags3);
	ReadHex16Field(input, (char *)&m_iSeekerFlags);

	return 1;
}

int CWeapResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "weap ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_WEAP_EDIT1, CCONTROL_TYPE_INT, IDS_STRING864);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_WEAP_EDIT47, CCONTROL_TYPE_STR256, IDS_STRING865);
	m_controls[1].SetString(m_szName);
	m_controls[2].Create(hwnd, IDC_EDIT_WEAP_EDIT2, CCONTROL_TYPE_INT, IDS_STRING866);
	m_controls[2].SetInt(m_iReload);
	m_controls[3].Create(hwnd, IDC_EDIT_WEAP_EDIT3, CCONTROL_TYPE_INT, IDS_STRING867);
	m_controls[3].SetInt(m_iLifetime);
	m_controls[4].Create(hwnd, IDC_EDIT_WEAP_EDIT4, CCONTROL_TYPE_INT, IDS_STRING868);
	m_controls[4].SetInt(m_iMassDamage);
	m_controls[5].Create(hwnd, IDC_EDIT_WEAP_EDIT5, CCONTROL_TYPE_INT, IDS_STRING869);
	m_controls[5].SetInt(m_iEnergyDamage);
	m_controls[6].Create(hwnd, IDC_EDIT_WEAP_COMBO1, CCONTROL_TYPE_COMBOBOX, IDS_STRING870);
	m_controls[6].SetComboStrings(NUM_WEAP_GUIDANCE_CHOICES, g_szWeapGuidanceChoices);
	m_controls[7].Create(hwnd, IDC_EDIT_WEAP_EDIT7, CCONTROL_TYPE_INT, IDS_STRING871);
	m_controls[7].SetInt(m_iSpeed);
	m_controls[8].Create(hwnd, IDC_EDIT_WEAP_EDIT8, CCONTROL_TYPE_INT, IDS_STRING872);
	m_controls[8].SetInt(m_iAmmoType);
	m_controls[9].Create(hwnd, IDC_EDIT_WEAP_EDIT9, CCONTROL_TYPE_INT, IDS_STRING873);
	m_controls[9].SetInt(m_iGraphics);
	m_controls[10].Create(hwnd, IDC_EDIT_WEAP_EDIT10, CCONTROL_TYPE_INT, IDS_STRING874);
	m_controls[10].SetInt(m_iInaccuracy);
	m_controls[11].Create(hwnd, IDC_EDIT_WEAP_EDIT11, CCONTROL_TYPE_INT, IDS_STRING875);
	m_controls[11].SetInt(m_iSound);
	m_controls[12].Create(hwnd, IDC_EDIT_WEAP_EDIT12, CCONTROL_TYPE_INT, IDS_STRING876);
	m_controls[12].SetInt(m_iImpact);
	m_controls[13].Create(hwnd, IDC_EDIT_WEAP_EDIT13, CCONTROL_TYPE_INT, IDS_STRING877);
	m_controls[13].SetInt(m_iExplosionType);
	m_controls[14].Create(hwnd, IDC_EDIT_WEAP_EDIT14, CCONTROL_TYPE_INT, IDS_STRING878);
	m_controls[14].SetInt(m_iProximityRadius);
	m_controls[15].Create(hwnd, IDC_EDIT_WEAP_EDIT15, CCONTROL_TYPE_INT, IDS_STRING879);
	m_controls[15].SetInt(m_iBlastRadius);
	m_controls[16].Create(hwnd, IDC_EDIT_WEAP_EDIT16, CCONTROL_TYPE_INT, IDS_STRING880);
	m_controls[16].SetInt(m_iSmokeSet);
	m_controls[17].Create(hwnd, IDC_EDIT_WEAP_EDIT17, CCONTROL_TYPE_INT, IDS_STRING881);
	m_controls[17].SetInt(m_iDecay);
	m_controls[18].Create(hwnd, IDC_EDIT_WEAP_EDIT18, CCONTROL_TYPE_INT, IDS_STRING882);
	m_controls[18].SetInt(m_iParticleCount);
	m_controls[19].Create(hwnd, IDC_EDIT_WEAP_EDIT19, CCONTROL_TYPE_INT, IDS_STRING883);
	m_controls[19].SetInt(m_iParticleVelocity);
	m_controls[20].Create(hwnd, IDC_EDIT_WEAP_EDIT20, CCONTROL_TYPE_INT, IDS_STRING884);
	m_controls[20].SetInt(m_iParticleMinLife);
	m_controls[21].Create(hwnd, IDC_EDIT_WEAP_EDIT21, CCONTROL_TYPE_INT, IDS_STRING885);
	m_controls[21].SetInt(m_iParticleMaxLife);
	m_controls[22].Create(hwnd, IDC_EDIT_WEAP_BUTTON1, CCONTROL_TYPE_COLOR, IDS_STRING886);
	m_controls[22].SetInt(m_iParticleColor);
	m_controls[23].Create(hwnd, IDC_EDIT_WEAP_EDIT22, CCONTROL_TYPE_INT, IDS_STRING887);
	m_controls[23].SetInt(m_iBeamLength);
	m_controls[24].Create(hwnd, IDC_EDIT_WEAP_EDIT23, CCONTROL_TYPE_INT, IDS_STRING888);
	m_controls[24].SetInt(m_iBeamWidth);
	m_controls[25].Create(hwnd, IDC_EDIT_WEAP_EDIT24, CCONTROL_TYPE_INT, IDS_STRING889);
	m_controls[25].SetInt(m_iBeamFalloff);
	m_controls[26].Create(hwnd, IDC_EDIT_WEAP_BUTTON2, CCONTROL_TYPE_COLOR, IDS_STRING890);
	m_controls[26].SetInt(m_iBeamColor);
	m_controls[27].Create(hwnd, IDC_EDIT_WEAP_BUTTON3, CCONTROL_TYPE_COLOR, IDS_STRING891);
	m_controls[27].SetInt(m_iCoronaColor);
	m_controls[28].Create(hwnd, IDC_EDIT_WEAP_EDIT25, CCONTROL_TYPE_INT, IDS_STRING892);
	m_controls[28].SetInt(m_iSubmunitionsCount);
	m_controls[29].Create(hwnd, IDC_EDIT_WEAP_EDIT26, CCONTROL_TYPE_INT, IDS_STRING893);
	m_controls[29].SetInt(m_iSubmunitionsType);
	m_controls[30].Create(hwnd, IDC_EDIT_WEAP_EDIT27, CCONTROL_TYPE_INT, IDS_STRING894);
	m_controls[30].SetInt(m_iSubmunitionsAngle);
	m_controls[31].Create(hwnd, IDC_EDIT_WEAP_EDIT28, CCONTROL_TYPE_INT, IDS_STRING955);
	m_controls[31].SetInt(m_iSubmunitionsLimit);
	m_controls[32].Create(hwnd, IDC_EDIT_WEAP_EDIT29, CCONTROL_TYPE_INT, IDS_STRING895);
	m_controls[32].SetInt(m_iProximityDelay);
	m_controls[33].Create(hwnd, IDC_EDIT_WEAP_EDIT30, CCONTROL_TYPE_INT, IDS_STRING896);
	m_controls[33].SetInt(m_iIonization);
	m_controls[34].Create(hwnd, IDC_EDIT_WEAP_EDIT31, CCONTROL_TYPE_INT, IDS_STRING897);
	m_controls[34].SetInt(m_iHitParticleCount);
	m_controls[35].Create(hwnd, IDC_EDIT_WEAP_EDIT32, CCONTROL_TYPE_INT, IDS_STRING898);
	m_controls[35].SetInt(m_iHitParticleLife);
	m_controls[36].Create(hwnd, IDC_EDIT_WEAP_EDIT33, CCONTROL_TYPE_INT, IDS_STRING899);
	m_controls[36].SetInt(m_iHitParticleVelocity);
	m_controls[37].Create(hwnd, IDC_EDIT_WEAP_BUTTON4, CCONTROL_TYPE_COLOR, IDS_STRING900);
	m_controls[37].SetInt(m_iHitParticleColor);
	m_controls[38].Create(hwnd, IDC_EDIT_WEAP_COMBO2, CCONTROL_TYPE_COMBOBOX, IDS_STRING901);
	m_controls[38].SetComboStrings(NUM_WEAP_EXITTYPE_CHOICES, g_szWeapExitTypeChoices);
	m_controls[38].SetInt(m_iExitType + 1);
	m_controls[39].Create(hwnd, IDC_EDIT_WEAP_EDIT35, CCONTROL_TYPE_INT, IDS_STRING902);
	m_controls[39].SetInt(m_iBurstCount);
	m_controls[40].Create(hwnd, IDC_EDIT_WEAP_EDIT36, CCONTROL_TYPE_INT, IDS_STRING956);
	m_controls[40].SetInt(m_iBurstReload);
	m_controls[41].Create(hwnd, IDC_EDIT_WEAP_EDIT37, CCONTROL_TYPE_INT, IDS_STRING903);
	m_controls[41].SetInt(m_iJammingVulnerability[0]);
	m_controls[42].Create(hwnd, IDC_EDIT_WEAP_EDIT38, CCONTROL_TYPE_INT, IDS_STRING903);
	m_controls[42].SetInt(m_iJammingVulnerability[1]);
	m_controls[43].Create(hwnd, IDC_EDIT_WEAP_EDIT39, CCONTROL_TYPE_INT, IDS_STRING903);
	m_controls[43].SetInt(m_iJammingVulnerability[2]);
	m_controls[44].Create(hwnd, IDC_EDIT_WEAP_EDIT40, CCONTROL_TYPE_INT, IDS_STRING903);
	m_controls[44].SetInt(m_iJammingVulnerability[3]);
	m_controls[45].Create(hwnd, IDC_EDIT_WEAP_EDIT41, CCONTROL_TYPE_INT, IDS_STRING904);
	m_controls[45].SetInt(m_iDurability);
	m_controls[46].Create(hwnd, IDC_EDIT_WEAP_EDIT42, CCONTROL_TYPE_INT, IDS_STRING905);
	m_controls[46].SetInt(m_iGuidedTurnRate);
	m_controls[47].Create(hwnd, IDC_EDIT_WEAP_EDIT43, CCONTROL_TYPE_INT, IDS_STRING906);
	m_controls[47].SetInt(m_iMaxAmmo);
	m_controls[48].Create(hwnd, IDC_EDIT_WEAP_EDIT44, CCONTROL_TYPE_INT, IDS_STRING907);
	m_controls[48].SetInt(m_iRecoil);
	m_controls[49].Create(hwnd, IDC_EDIT_WEAP_EDIT45, CCONTROL_TYPE_INT, IDS_STRING908);
	m_controls[49].SetInt(m_iLightningDensity);
	m_controls[50].Create(hwnd, IDC_EDIT_WEAP_EDIT46, CCONTROL_TYPE_INT, IDS_STRING909);
	m_controls[50].SetInt(m_iLightningAmplitude);
	m_controls[51].Create(hwnd, IDC_EDIT_WEAP_BUTTON5, CCONTROL_TYPE_COLOR, IDS_STRING910);
	m_controls[51].SetInt(m_iIonizationColor);
	m_controls[52].Create(hwnd, IDC_EDIT_WEAP_CHECK1, CCONTROL_TYPE_CHECK, IDS_STRING911);
	m_controls[52].SetInt(m_iFlags1 & 0x0001);
	m_controls[53].Create(hwnd, IDC_EDIT_WEAP_CHECK2, CCONTROL_TYPE_CHECK, IDS_STRING912);
	m_controls[53].SetInt(m_iFlags1 & 0x0002);
	m_controls[54].Create(hwnd, IDC_EDIT_WEAP_CHECK3, CCONTROL_TYPE_CHECK, IDS_STRING913);
	m_controls[54].SetInt(m_iFlags1 & 0x0004);
	m_controls[55].Create(hwnd, IDC_EDIT_WEAP_CHECK4, CCONTROL_TYPE_CHECK, IDS_STRING914);
	m_controls[55].SetInt(m_iFlags1 & 0x0008);
	m_controls[56].Create(hwnd, IDC_EDIT_WEAP_CHECK5, CCONTROL_TYPE_CHECK, IDS_STRING915);
	m_controls[56].SetInt(m_iFlags1 & 0x0010);
	m_controls[57].Create(hwnd, IDC_EDIT_WEAP_CHECK6, CCONTROL_TYPE_CHECK, IDS_STRING916);
	m_controls[57].SetInt(m_iFlags1 & 0x0020);
	m_controls[58].Create(hwnd, IDC_EDIT_WEAP_CHECK7, CCONTROL_TYPE_CHECK, IDS_STRING917);
	m_controls[58].SetInt(m_iFlags1 & 0x0040);
	m_controls[59].Create(hwnd, IDC_EDIT_WEAP_CHECK8, CCONTROL_TYPE_CHECK, IDS_STRING918);
	m_controls[59].SetInt(m_iFlags1 & 0x0080);
	m_controls[60].Create(hwnd, IDC_EDIT_WEAP_CHECK9, CCONTROL_TYPE_CHECK, IDS_STRING919);
	m_controls[60].SetInt(m_iFlags1 & 0x0100);
	m_controls[61].Create(hwnd, IDC_EDIT_WEAP_CHECK10, CCONTROL_TYPE_CHECK, IDS_STRING920);
	m_controls[61].SetInt(m_iFlags1 & 0x0200);
	m_controls[62].Create(hwnd, IDC_EDIT_WEAP_CHECK11, CCONTROL_TYPE_CHECK, IDS_STRING921);
	m_controls[62].SetInt(m_iFlags1 & 0x0400);
	m_controls[63].Create(hwnd, IDC_EDIT_WEAP_CHECK12, CCONTROL_TYPE_CHECK, IDS_STRING922);
	m_controls[63].SetInt(m_iFlags1 & 0x0800);
	m_controls[64].Create(hwnd, IDC_EDIT_WEAP_CHECK13, CCONTROL_TYPE_CHECK, IDS_STRING923);
	m_controls[64].SetInt(m_iFlags1 & 0x1000);
	m_controls[65].Create(hwnd, IDC_EDIT_WEAP_CHECK14, CCONTROL_TYPE_CHECK, IDS_STRING924);
	m_controls[65].SetInt(m_iFlags1 & 0x2000);
	m_controls[66].Create(hwnd, IDC_EDIT_WEAP_CHECK15, CCONTROL_TYPE_CHECK, IDS_STRING925);
	m_controls[66].SetInt(m_iFlags1 & 0x4000);
	m_controls[67].Create(hwnd, IDC_EDIT_WEAP_CHECK16, CCONTROL_TYPE_CHECK, IDS_STRING926);
	m_controls[67].SetInt(m_iFlags1 & 0x8000);
	m_controls[68].Create(hwnd, IDC_EDIT_WEAP_CHECK17, CCONTROL_TYPE_CHECK, IDS_STRING927);
	m_controls[68].SetInt(m_iFlags2 & 0x0001);
	m_controls[69].Create(hwnd, IDC_EDIT_WEAP_CHECK18, CCONTROL_TYPE_CHECK, IDS_STRING928);
	m_controls[69].SetInt(m_iFlags2 & 0x0002);
	m_controls[70].Create(hwnd, IDC_EDIT_WEAP_CHECK19, CCONTROL_TYPE_CHECK, IDS_STRING929);
	m_controls[70].SetInt(m_iFlags2 & 0x0004);
	m_controls[71].Create(hwnd, IDC_EDIT_WEAP_CHECK20, CCONTROL_TYPE_CHECK, IDS_STRING930);
	m_controls[71].SetInt(m_iFlags2 & 0x0008);
	m_controls[72].Create(hwnd, IDC_EDIT_WEAP_CHECK21, CCONTROL_TYPE_CHECK, IDS_STRING931);
	m_controls[72].SetInt(m_iFlags2 & 0x0010);
	m_controls[73].Create(hwnd, IDC_EDIT_WEAP_CHECK22, CCONTROL_TYPE_CHECK, IDS_STRING932);
	m_controls[73].SetInt(m_iFlags2 & 0x0020);
	m_controls[74].Create(hwnd, IDC_EDIT_WEAP_CHECK23, CCONTROL_TYPE_CHECK, IDS_STRING933);
	m_controls[74].SetInt(m_iFlags2 & 0x0040);
	m_controls[75].Create(hwnd, IDC_EDIT_WEAP_CHECK24, CCONTROL_TYPE_CHECK, IDS_STRING934);
	m_controls[75].SetInt(m_iFlags2 & 0x0080);
	m_controls[76].Create(hwnd, IDC_EDIT_WEAP_CHECK25, CCONTROL_TYPE_CHECK, IDS_STRING935);
	m_controls[76].SetInt(m_iFlags2 & 0x0100);
	m_controls[77].Create(hwnd, IDC_EDIT_WEAP_CHECK26, CCONTROL_TYPE_CHECK, IDS_STRING936);
	m_controls[77].SetInt(m_iFlags2 & 0x0200);
	m_controls[78].Create(hwnd, IDC_EDIT_WEAP_CHECK27, CCONTROL_TYPE_CHECK, IDS_STRING937);
	m_controls[78].SetInt(m_iFlags2 & 0x0400);
	m_controls[79].Create(hwnd, IDC_EDIT_WEAP_CHECK28, CCONTROL_TYPE_CHECK, IDS_STRING938);
	m_controls[79].SetInt(m_iFlags2 & 0x0800);
	m_controls[80].Create(hwnd, IDC_EDIT_WEAP_CHECK29, CCONTROL_TYPE_CHECK, IDS_STRING939);
	m_controls[80].SetInt(m_iFlags2 & 0x1000);
	m_controls[81].Create(hwnd, IDC_EDIT_WEAP_CHECK30, CCONTROL_TYPE_CHECK, IDS_STRING940);
	m_controls[81].SetInt(m_iFlags2 & 0x2000);
	m_controls[82].Create(hwnd, IDC_EDIT_WEAP_CHECK31, CCONTROL_TYPE_CHECK, IDS_STRING941);
	m_controls[82].SetInt(m_iFlags2 & 0x4000);
	m_controls[83].Create(hwnd, IDC_EDIT_WEAP_CHECK32, CCONTROL_TYPE_CHECK, IDS_STRING942);
	m_controls[83].SetInt(m_iFlags2 & 0x8000);
	m_controls[84].Create(hwnd, IDC_EDIT_WEAP_CHECK33, CCONTROL_TYPE_CHECK, IDS_STRING943);
	m_controls[84].SetInt(m_iFlags3 & 0x0001);
	m_controls[85].Create(hwnd, IDC_EDIT_WEAP_CHECK34, CCONTROL_TYPE_CHECK, IDS_STRING944);
	m_controls[85].SetInt(m_iFlags3 & 0x0002);
	m_controls[86].Create(hwnd, IDC_EDIT_WEAP_CHECK35, CCONTROL_TYPE_CHECK, IDS_STRING945);
	m_controls[86].SetInt(m_iFlags3 & 0x0004);
	m_controls[87].Create(hwnd, IDC_EDIT_WEAP_CHECK36, CCONTROL_TYPE_CHECK, IDS_STRING946);
	m_controls[87].SetInt(m_iFlags3 & 0x0010);
	m_controls[88].Create(hwnd, IDC_EDIT_WEAP_CHECK37, CCONTROL_TYPE_CHECK, IDS_STRING947);
	m_controls[88].SetInt(m_iFlags3 & 0x0020);
	m_controls[89].Create(hwnd, IDC_EDIT_WEAP_CHECK38, CCONTROL_TYPE_CHECK, IDS_STRING948);
	m_controls[89].SetInt(m_iSeekerFlags & 0x0001);
	m_controls[90].Create(hwnd, IDC_EDIT_WEAP_CHECK39, CCONTROL_TYPE_CHECK, IDS_STRING949);
	m_controls[90].SetInt(m_iSeekerFlags & 0x0002);
	m_controls[91].Create(hwnd, IDC_EDIT_WEAP_CHECK40, CCONTROL_TYPE_CHECK, IDS_STRING950);
	m_controls[91].SetInt(m_iSeekerFlags & 0x0008);
	m_controls[92].Create(hwnd, IDC_EDIT_WEAP_CHECK41, CCONTROL_TYPE_CHECK, IDS_STRING951);
	m_controls[92].SetInt(m_iSeekerFlags & 0x0010);
	m_controls[93].Create(hwnd, IDC_EDIT_WEAP_CHECK42, CCONTROL_TYPE_CHECK, IDS_STRING952);
	m_controls[93].SetInt(m_iSeekerFlags & 0x0020);
	m_controls[94].Create(hwnd, IDC_EDIT_WEAP_CHECK43, CCONTROL_TYPE_CHECK, IDS_STRING953);
	m_controls[94].SetInt(m_iSeekerFlags & 0x4000);
	m_controls[95].Create(hwnd, IDC_EDIT_WEAP_CHECK44, CCONTROL_TYPE_CHECK, IDS_STRING954);
	m_controls[95].SetInt(m_iSeekerFlags & 0x8000);

	if(m_iGuidance <= 1)
		m_controls[6].SetInt(m_iGuidance + 1);
	else if(m_iGuidance <= 10)
		m_controls[6].SetInt(m_iGuidance);
	else if(m_iGuidance == 99)
		m_controls[6].SetInt(11);
	else
		m_controls[6].SetInt(0);

	if(m_iGuidance == 99)
		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_WEAP_TEXT8), "Ammo Ship ID");
	else
		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_WEAP_TEXT8), "Ammo Type");

	return 1;
}

int CWeapResource::CloseAndSave(void)
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

	strcpy(m_szName, m_controls[1].GetString());

	m_iReload   = m_controls[2].GetInt();
	m_iLifetime = m_controls[3].GetInt();

	m_iMassDamage   = m_controls[4].GetInt();
	m_iEnergyDamage = m_controls[5].GetInt();

	m_iGuidance = m_controls[6].GetInt();

	if(m_iGuidance == 11)
		m_iGuidance = 99;
	else if(m_iGuidance <= 2)
		m_iGuidance--;

	m_iSpeed    = m_controls[7].GetInt();
	m_iAmmoType = m_controls[8].GetInt();

	m_iGraphics = m_controls[9].GetInt();

	m_iInaccuracy = m_controls[10].GetInt();

	m_iSound = m_controls[11].GetInt();

	m_iImpact          = m_controls[12].GetInt();
	m_iExplosionType   = m_controls[13].GetInt();
	m_iProximityRadius = m_controls[14].GetInt();
	m_iBlastRadius     = m_controls[15].GetInt();

	m_iSmokeSet = m_controls[16].GetInt();

	m_iDecay = m_controls[17].GetInt();

	m_iParticleCount    = m_controls[18].GetInt();
	m_iParticleVelocity = m_controls[19].GetInt();
	m_iParticleMinLife  = m_controls[20].GetInt();
	m_iParticleMaxLife  = m_controls[21].GetInt();
	m_iParticleColor    = m_controls[22].GetInt();

	m_iBeamLength  = m_controls[23].GetInt();
	m_iBeamWidth   = m_controls[24].GetInt();
	m_iBeamFalloff = m_controls[25].GetInt();
	m_iBeamColor   = m_controls[26].GetInt();
	m_iCoronaColor = m_controls[27].GetInt();

	m_iSubmunitionsCount = m_controls[28].GetInt();
	m_iSubmunitionsType  = m_controls[29].GetInt();
	m_iSubmunitionsAngle = m_controls[30].GetInt();
	m_iSubmunitionsLimit = m_controls[31].GetInt();

	m_iProximityDelay = m_controls[32].GetInt();

	m_iIonization = m_controls[33].GetInt();

	m_iHitParticleCount    = m_controls[34].GetInt();
	m_iHitParticleLife     = m_controls[35].GetInt();
	m_iHitParticleVelocity = m_controls[36].GetInt();
	m_iHitParticleColor    = m_controls[37].GetInt();

	m_iExitType = m_controls[38].GetInt() - 1;

	m_iBurstCount  = m_controls[39].GetInt();
	m_iBurstReload = m_controls[40].GetInt();

	m_iJammingVulnerability[0] = m_controls[41].GetInt();
	m_iJammingVulnerability[1] = m_controls[42].GetInt();
	m_iJammingVulnerability[2] = m_controls[43].GetInt();
	m_iJammingVulnerability[3] = m_controls[44].GetInt();

	m_iDurability = m_controls[45].GetInt();

	m_iGuidedTurnRate = m_controls[46].GetInt();

	m_iMaxAmmo = m_controls[47].GetInt();

	m_iRecoil = m_controls[48].GetInt();

	m_iLightningDensity   = m_controls[49].GetInt();
	m_iLightningAmplitude = m_controls[50].GetInt();

	m_iIonizationColor = m_controls[51].GetInt();

	m_iFlags1      = 0x0000;
	m_iFlags2      = 0x0000;
	m_iFlags3      = 0x0000;
	m_iSeekerFlags = 0x0000;

	m_iFlags1 |= m_controls[52].GetInt() << 0;
	m_iFlags1 |= m_controls[53].GetInt() << 1;
	m_iFlags1 |= m_controls[54].GetInt() << 2;
	m_iFlags1 |= m_controls[55].GetInt() << 3;
	m_iFlags1 |= m_controls[56].GetInt() << 4;
	m_iFlags1 |= m_controls[57].GetInt() << 5;
	m_iFlags1 |= m_controls[58].GetInt() << 6;
	m_iFlags1 |= m_controls[59].GetInt() << 7;
	m_iFlags1 |= m_controls[60].GetInt() << 8;
	m_iFlags1 |= m_controls[61].GetInt() << 9;
	m_iFlags1 |= m_controls[62].GetInt() << 10;
	m_iFlags1 |= m_controls[63].GetInt() << 11;
	m_iFlags1 |= m_controls[64].GetInt() << 12;
	m_iFlags1 |= m_controls[65].GetInt() << 13;
	m_iFlags1 |= m_controls[66].GetInt() << 14;
	m_iFlags1 |= m_controls[67].GetInt() << 15;

	m_iFlags2 |= m_controls[68].GetInt() << 0;
	m_iFlags2 |= m_controls[69].GetInt() << 1;
	m_iFlags2 |= m_controls[70].GetInt() << 2;
	m_iFlags2 |= m_controls[71].GetInt() << 3;
	m_iFlags2 |= m_controls[72].GetInt() << 4;
	m_iFlags2 |= m_controls[73].GetInt() << 5;
	m_iFlags2 |= m_controls[74].GetInt() << 6;
	m_iFlags2 |= m_controls[75].GetInt() << 7;
	m_iFlags2 |= m_controls[76].GetInt() << 8;
	m_iFlags2 |= m_controls[77].GetInt() << 9;
	m_iFlags2 |= m_controls[78].GetInt() << 10;
	m_iFlags2 |= m_controls[79].GetInt() << 11;
	m_iFlags2 |= m_controls[80].GetInt() << 12;
	m_iFlags2 |= m_controls[81].GetInt() << 13;
	m_iFlags2 |= m_controls[82].GetInt() << 14;
	m_iFlags2 |= m_controls[83].GetInt() << 15;

	m_iFlags3 |= m_controls[84].GetInt() << 0;
	m_iFlags3 |= m_controls[85].GetInt() << 1;
	m_iFlags3 |= m_controls[86].GetInt() << 2;
	m_iFlags3 |= m_controls[87].GetInt() << 4;
	m_iFlags3 |= m_controls[88].GetInt() << 5;

	m_iSeekerFlags |= m_controls[89].GetInt() << 0;
	m_iSeekerFlags |= m_controls[90].GetInt() << 1;
	m_iSeekerFlags |= m_controls[91].GetInt() << 3;
	m_iSeekerFlags |= m_controls[92].GetInt() << 4;
	m_iSeekerFlags |= m_controls[93].GetInt() << 5;
	m_iSeekerFlags |= m_controls[94].GetInt() << 14;
	m_iSeekerFlags |= m_controls[95].GetInt() << 15;

	int i;

	for(i = 0; i < NUM_WEAP_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CWeapResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_WEAP_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CWeapResource::WeapDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CWeapResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CWeapResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_WEAP_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_WEAP_OK)
			{
				pResource->CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_WEAP_CONTROLS; i++)
				{
					if(iControlID == pResource->m_controls[i].GetControlID())
					{
						pResource->m_controls[i].ProcessMessage(iNotifyCode);

						break;
					}
				}
			}

			if((iNotifyCode == CBN_SELCHANGE) && (iControlID == IDC_EDIT_WEAP_COMBO1))
			{
				int iIndex = ComboBox_GetCurSel((HWND)lparam);

				if(iIndex == 11)
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_WEAP_TEXT8), "Ammo Ship ID");
				else
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_WEAP_TEXT8), "Ammo Type");
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
