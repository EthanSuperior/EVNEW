// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CShanResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CShanResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CShanResource::CShanResource(void)
{
	m_iBaseImage        = 0;
	m_iBaseMask         = 0;
	m_iBaseSetCount     = 0;
	m_iBaseXSize        = 0;
	m_iBaseYSize        = 0;
	m_iBaseTransparency = 0;

	m_iAltImage    = 0;
	m_iAltMask     = 0;
	m_iAltSetCount = 0;
	m_iAltXSize    = 0;
	m_iAltYSize    = 0;

	m_iGlowImage = 0;
	m_iGlowMask  = 0;
	m_iGlowXSize = 0;
	m_iGlowYSize = 0;

	m_iLightsImage = 0;
	m_iLightsMask  = 0;
	m_iLightsXSize = 0;
	m_iLightsYSize = 0;

	m_iWeaponImage = 0;
	m_iWeaponMask  = 0;
	m_iWeaponXSize = 0;
	m_iWeaponYSize = 0;

	m_iShieldImage = 0;
	m_iShieldMask  = 0;
	m_iShieldXSize = 0;
	m_iShieldYSize = 0;

	m_iFlags = 0x0000;

	m_iAnimationDelay = 0;
	m_iWeaponDecay    = 0;

	m_iRotationFrames = 0;

	m_iBlinkMode   = 0;
	m_iBlinkValueA = 0;
	m_iBlinkValueB = 0;
	m_iBlinkValueC = 0;
	m_iBlinkValueD = 0;

	int i;

	for(i = 0; i < 4; i++)
	{
		m_iGunPosX[i]    = 0;
		m_iGunPosY[i]    = 0;
		m_iTurretPosX[i] = 0;
		m_iTurretPosY[i] = 0;
		m_iGuidedPosX[i] = 0;
		m_iGuidedPosY[i] = 0;
		m_iBeamPosX[i]   = 0;
		m_iBeamPosY[i]   = 0;
	}

	m_iUpCompressX   = 0;
	m_iUpCompressY   = 0;
	m_iDownCompressX = 0;
	m_iDownCompressY = 0;

	for(i = 0; i < 4; i++)
	{
		m_iGunPosZ[i]    = 0;
		m_iTurretPosZ[i] = 0;
		m_iGuidedPosZ[i] = 0;
		m_iBeamPosZ[i]   = 0;
	}
}

CShanResource::~CShanResource(void)
= default;

int CShanResource::GetType(void)
{
	return CNR_TYPE_SHAN;
}

int CShanResource::GetSize(void)
{
	return 192;
}

int CShanResource::GetDialogID(void)
{
	return IDD_EDIT_SHAN;
}

DLGPROCNOCALLBACK CShanResource::GetDialogProc(void)
{
	return ShanDlgProc;
}

int CShanResource::GetNumFields(void)
{
	return NUM_SHAN_FIELDS;
}

const std::string * CShanResource::GetFieldNames(void)
{
	return g_szShanFields;
}

int CShanResource::Save(char *pOutput)
{
	SwapEndians();

	*(short *)pOutput = m_iBaseImage;        pOutput += sizeof(short);
	*(short *)pOutput = m_iBaseMask;         pOutput += sizeof(short);
	*(short *)pOutput = m_iBaseSetCount;     pOutput += sizeof(short);
	*(short *)pOutput = m_iBaseXSize;        pOutput += sizeof(short);
	*(short *)pOutput = m_iBaseYSize;        pOutput += sizeof(short);
	*(short *)pOutput = m_iBaseTransparency; pOutput += sizeof(short);
	*(short *)pOutput = m_iAltImage;         pOutput += sizeof(short);
	*(short *)pOutput = m_iAltMask;          pOutput += sizeof(short);
	*(short *)pOutput = m_iAltSetCount;      pOutput += sizeof(short);
	*(short *)pOutput = m_iAltXSize;         pOutput += sizeof(short);
	*(short *)pOutput = m_iAltYSize;         pOutput += sizeof(short);
	*(short *)pOutput = m_iGlowImage;        pOutput += sizeof(short);
	*(short *)pOutput = m_iGlowMask;         pOutput += sizeof(short);
	*(short *)pOutput = m_iGlowXSize;        pOutput += sizeof(short);
	*(short *)pOutput = m_iGlowYSize;        pOutput += sizeof(short);
	*(short *)pOutput = m_iLightsImage;      pOutput += sizeof(short);
	*(short *)pOutput = m_iLightsMask;       pOutput += sizeof(short);
	*(short *)pOutput = m_iLightsXSize;      pOutput += sizeof(short);
	*(short *)pOutput = m_iLightsYSize;      pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponImage;      pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponMask;       pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponXSize;      pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponYSize;      pOutput += sizeof(short);
	*(USHORT *)pOutput = m_iFlags;           pOutput += sizeof(USHORT);
	*(short *)pOutput = m_iAnimationDelay;   pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponDecay;      pOutput += sizeof(short);
	*(short *)pOutput = m_iRotationFrames;   pOutput += sizeof(short);
	*(short *)pOutput = m_iBlinkMode;        pOutput += sizeof(short);
	*(short *)pOutput = m_iBlinkValueA;      pOutput += sizeof(short);
	*(short *)pOutput = m_iBlinkValueB;      pOutput += sizeof(short);
	*(short *)pOutput = m_iBlinkValueC;      pOutput += sizeof(short);
	*(short *)pOutput = m_iBlinkValueD;      pOutput += sizeof(short);
	*(short *)pOutput = m_iShieldImage;      pOutput += sizeof(short);
	*(short *)pOutput = m_iShieldMask;       pOutput += sizeof(short);
	*(short *)pOutput = m_iShieldXSize;      pOutput += sizeof(short);
	*(short *)pOutput = m_iShieldYSize;      pOutput += sizeof(short);
	*(short *)pOutput = m_iGunPosX[0];       pOutput += sizeof(short);
	*(short *)pOutput = m_iGunPosX[1];       pOutput += sizeof(short);
	*(short *)pOutput = m_iGunPosX[2];       pOutput += sizeof(short);
	*(short *)pOutput = m_iGunPosX[3];       pOutput += sizeof(short);
	*(short *)pOutput = m_iGunPosY[0];       pOutput += sizeof(short);
	*(short *)pOutput = m_iGunPosY[1];       pOutput += sizeof(short);
	*(short *)pOutput = m_iGunPosY[2];       pOutput += sizeof(short);
	*(short *)pOutput = m_iGunPosY[3];       pOutput += sizeof(short);
	*(short *)pOutput = m_iTurretPosX[0];    pOutput += sizeof(short);
	*(short *)pOutput = m_iTurretPosX[1];    pOutput += sizeof(short);
	*(short *)pOutput = m_iTurretPosX[2];    pOutput += sizeof(short);
	*(short *)pOutput = m_iTurretPosX[3];    pOutput += sizeof(short);
	*(short *)pOutput = m_iTurretPosY[0];    pOutput += sizeof(short);
	*(short *)pOutput = m_iTurretPosY[1];    pOutput += sizeof(short);
	*(short *)pOutput = m_iTurretPosY[2];    pOutput += sizeof(short);
	*(short *)pOutput = m_iTurretPosY[3];    pOutput += sizeof(short);
	*(short *)pOutput = m_iGuidedPosX[0];    pOutput += sizeof(short);
	*(short *)pOutput = m_iGuidedPosX[1];    pOutput += sizeof(short);
	*(short *)pOutput = m_iGuidedPosX[2];    pOutput += sizeof(short);
	*(short *)pOutput = m_iGuidedPosX[3];    pOutput += sizeof(short);
	*(short *)pOutput = m_iGuidedPosY[0];    pOutput += sizeof(short);
	*(short *)pOutput = m_iGuidedPosY[1];    pOutput += sizeof(short);
	*(short *)pOutput = m_iGuidedPosY[2];    pOutput += sizeof(short);
	*(short *)pOutput = m_iGuidedPosY[3];    pOutput += sizeof(short);
	*(short *)pOutput = m_iBeamPosX[0];      pOutput += sizeof(short);
	*(short *)pOutput = m_iBeamPosX[1];      pOutput += sizeof(short);
	*(short *)pOutput = m_iBeamPosX[2];      pOutput += sizeof(short);
	*(short *)pOutput = m_iBeamPosX[3];      pOutput += sizeof(short);
	*(short *)pOutput = m_iBeamPosY[0];      pOutput += sizeof(short);
	*(short *)pOutput = m_iBeamPosY[1];      pOutput += sizeof(short);
	*(short *)pOutput = m_iBeamPosY[2];      pOutput += sizeof(short);
	*(short *)pOutput = m_iBeamPosY[3];      pOutput += sizeof(short);
	*(short *)pOutput = m_iUpCompressX;      pOutput += sizeof(short);
	*(short *)pOutput = m_iUpCompressY;      pOutput += sizeof(short);
	*(short *)pOutput = m_iDownCompressX;    pOutput += sizeof(short);
	*(short *)pOutput = m_iDownCompressY;    pOutput += sizeof(short);
	*(short *)pOutput = m_iGunPosZ[0];       pOutput += sizeof(short);
	*(short *)pOutput = m_iGunPosZ[1];       pOutput += sizeof(short);
	*(short *)pOutput = m_iGunPosZ[2];       pOutput += sizeof(short);
	*(short *)pOutput = m_iGunPosZ[3];       pOutput += sizeof(short);
	*(short *)pOutput = m_iTurretPosZ[0];    pOutput += sizeof(short);
	*(short *)pOutput = m_iTurretPosZ[1];    pOutput += sizeof(short);
	*(short *)pOutput = m_iTurretPosZ[2];    pOutput += sizeof(short);
	*(short *)pOutput = m_iTurretPosZ[3];    pOutput += sizeof(short);
	*(short *)pOutput = m_iGuidedPosZ[0];    pOutput += sizeof(short);
	*(short *)pOutput = m_iGuidedPosZ[1];    pOutput += sizeof(short);
	*(short *)pOutput = m_iGuidedPosZ[2];    pOutput += sizeof(short);
	*(short *)pOutput = m_iGuidedPosZ[3];    pOutput += sizeof(short);
	*(short *)pOutput = m_iBeamPosZ[0];      pOutput += sizeof(short);
	*(short *)pOutput = m_iBeamPosZ[1];      pOutput += sizeof(short);
	*(short *)pOutput = m_iBeamPosZ[2];      pOutput += sizeof(short);
	*(short *)pOutput = m_iBeamPosZ[3];      pOutput += sizeof(short);

	SwapEndians();

	return 1;
}

int CShanResource::Load(char *pInput, int iSize)
{
	m_iBaseImage        = *(short *)pInput; pInput += sizeof(short);
	m_iBaseMask         = *(short *)pInput; pInput += sizeof(short);
	m_iBaseSetCount     = *(short *)pInput; pInput += sizeof(short);
	m_iBaseXSize        = *(short *)pInput; pInput += sizeof(short);
	m_iBaseYSize        = *(short *)pInput; pInput += sizeof(short);
	m_iBaseTransparency = *(short *)pInput; pInput += sizeof(short);
	m_iAltImage         = *(short *)pInput; pInput += sizeof(short);
	m_iAltMask          = *(short *)pInput; pInput += sizeof(short);
	m_iAltSetCount      = *(short *)pInput; pInput += sizeof(short);
	m_iAltXSize         = *(short *)pInput; pInput += sizeof(short);
	m_iAltYSize         = *(short *)pInput; pInput += sizeof(short);
	m_iGlowImage        = *(short *)pInput; pInput += sizeof(short);
	m_iGlowMask         = *(short *)pInput; pInput += sizeof(short);
	m_iGlowXSize        = *(short *)pInput; pInput += sizeof(short);
	m_iGlowYSize        = *(short *)pInput; pInput += sizeof(short);
	m_iLightsImage      = *(short *)pInput; pInput += sizeof(short);
	m_iLightsMask       = *(short *)pInput; pInput += sizeof(short);
	m_iLightsXSize      = *(short *)pInput; pInput += sizeof(short);
	m_iLightsYSize      = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponImage      = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponMask       = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponXSize      = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponYSize      = *(short *)pInput; pInput += sizeof(short);
	m_iFlags            = *(USHORT *)pInput; pInput += sizeof(USHORT);
	m_iAnimationDelay   = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponDecay      = *(short *)pInput; pInput += sizeof(short);
	m_iRotationFrames   = *(short *)pInput; pInput += sizeof(short);
	m_iBlinkMode        = *(short *)pInput; pInput += sizeof(short);
	m_iBlinkValueA      = *(short *)pInput; pInput += sizeof(short);
	m_iBlinkValueB      = *(short *)pInput; pInput += sizeof(short);
	m_iBlinkValueC      = *(short *)pInput; pInput += sizeof(short);
	m_iBlinkValueD      = *(short *)pInput; pInput += sizeof(short);
	m_iShieldImage      = *(short *)pInput; pInput += sizeof(short);
	m_iShieldMask       = *(short *)pInput; pInput += sizeof(short);
	m_iShieldXSize      = *(short *)pInput; pInput += sizeof(short);
	m_iShieldYSize      = *(short *)pInput; pInput += sizeof(short);
	m_iGunPosX[0]       = *(short *)pInput; pInput += sizeof(short);
	m_iGunPosX[1]       = *(short *)pInput; pInput += sizeof(short);
	m_iGunPosX[2]       = *(short *)pInput; pInput += sizeof(short);
	m_iGunPosX[3]       = *(short *)pInput; pInput += sizeof(short);
	m_iGunPosY[0]       = *(short *)pInput; pInput += sizeof(short);
	m_iGunPosY[1]       = *(short *)pInput; pInput += sizeof(short);
	m_iGunPosY[2]       = *(short *)pInput; pInput += sizeof(short);
	m_iGunPosY[3]       = *(short *)pInput; pInput += sizeof(short);
	m_iTurretPosX[0]    = *(short *)pInput; pInput += sizeof(short);
	m_iTurretPosX[1]    = *(short *)pInput; pInput += sizeof(short);
	m_iTurretPosX[2]    = *(short *)pInput; pInput += sizeof(short);
	m_iTurretPosX[3]    = *(short *)pInput; pInput += sizeof(short);
	m_iTurretPosY[0]    = *(short *)pInput; pInput += sizeof(short);
	m_iTurretPosY[1]    = *(short *)pInput; pInput += sizeof(short);
	m_iTurretPosY[2]    = *(short *)pInput; pInput += sizeof(short);
	m_iTurretPosY[3]    = *(short *)pInput; pInput += sizeof(short);
	m_iGuidedPosX[0]    = *(short *)pInput; pInput += sizeof(short);
	m_iGuidedPosX[1]    = *(short *)pInput; pInput += sizeof(short);
	m_iGuidedPosX[2]    = *(short *)pInput; pInput += sizeof(short);
	m_iGuidedPosX[3]    = *(short *)pInput; pInput += sizeof(short);
	m_iGuidedPosY[0]    = *(short *)pInput; pInput += sizeof(short);
	m_iGuidedPosY[1]    = *(short *)pInput; pInput += sizeof(short);
	m_iGuidedPosY[2]    = *(short *)pInput; pInput += sizeof(short);
	m_iGuidedPosY[3]    = *(short *)pInput; pInput += sizeof(short);
	m_iBeamPosX[0]      = *(short *)pInput; pInput += sizeof(short);
	m_iBeamPosX[1]      = *(short *)pInput; pInput += sizeof(short);
	m_iBeamPosX[2]      = *(short *)pInput; pInput += sizeof(short);
	m_iBeamPosX[3]      = *(short *)pInput; pInput += sizeof(short);
	m_iBeamPosY[0]      = *(short *)pInput; pInput += sizeof(short);
	m_iBeamPosY[1]      = *(short *)pInput; pInput += sizeof(short);
	m_iBeamPosY[2]      = *(short *)pInput; pInput += sizeof(short);
	m_iBeamPosY[3]      = *(short *)pInput; pInput += sizeof(short);
	m_iUpCompressX      = *(short *)pInput; pInput += sizeof(short);
	m_iUpCompressY      = *(short *)pInput; pInput += sizeof(short);
	m_iDownCompressX    = *(short *)pInput; pInput += sizeof(short);
	m_iDownCompressY    = *(short *)pInput; pInput += sizeof(short);
	m_iGunPosZ[0]       = *(short *)pInput; pInput += sizeof(short);
	m_iGunPosZ[1]       = *(short *)pInput; pInput += sizeof(short);
	m_iGunPosZ[2]       = *(short *)pInput; pInput += sizeof(short);
	m_iGunPosZ[3]       = *(short *)pInput; pInput += sizeof(short);
	m_iTurretPosZ[0]    = *(short *)pInput; pInput += sizeof(short);
	m_iTurretPosZ[1]    = *(short *)pInput; pInput += sizeof(short);
	m_iTurretPosZ[2]    = *(short *)pInput; pInput += sizeof(short);
	m_iTurretPosZ[3]    = *(short *)pInput; pInput += sizeof(short);
	m_iGuidedPosZ[0]    = *(short *)pInput; pInput += sizeof(short);
	m_iGuidedPosZ[1]    = *(short *)pInput; pInput += sizeof(short);
	m_iGuidedPosZ[2]    = *(short *)pInput; pInput += sizeof(short);
	m_iGuidedPosZ[3]    = *(short *)pInput; pInput += sizeof(short);
	m_iBeamPosZ[0]      = *(short *)pInput; pInput += sizeof(short);
	m_iBeamPosZ[1]      = *(short *)pInput; pInput += sizeof(short);
	m_iBeamPosZ[2]      = *(short *)pInput; pInput += sizeof(short);
	m_iBeamPosZ[3]      = *(short *)pInput; pInput += sizeof(short);

	SwapEndians();

	return 1;
}

int CShanResource::SwapEndians(void)
{
	m_iBaseImage        = SwapEndianShort(m_iBaseImage);
	m_iBaseMask         = SwapEndianShort(m_iBaseMask);
	m_iBaseSetCount     = SwapEndianShort(m_iBaseSetCount);
	m_iBaseXSize        = SwapEndianShort(m_iBaseXSize);
	m_iBaseYSize        = SwapEndianShort(m_iBaseYSize);
	m_iBaseTransparency = SwapEndianShort(m_iBaseTransparency);
	m_iAltImage         = SwapEndianShort(m_iAltImage);
	m_iAltMask          = SwapEndianShort(m_iAltMask);
	m_iAltSetCount      = SwapEndianShort(m_iAltSetCount);
	m_iAltXSize         = SwapEndianShort(m_iAltXSize);
	m_iAltYSize         = SwapEndianShort(m_iAltYSize);
	m_iGlowImage        = SwapEndianShort(m_iGlowImage);
	m_iGlowMask         = SwapEndianShort(m_iGlowMask);
	m_iGlowXSize        = SwapEndianShort(m_iGlowXSize);
	m_iGlowYSize        = SwapEndianShort(m_iGlowYSize);
	m_iLightsImage      = SwapEndianShort(m_iLightsImage);
	m_iLightsMask       = SwapEndianShort(m_iLightsMask);
	m_iLightsXSize      = SwapEndianShort(m_iLightsXSize);
	m_iLightsYSize      = SwapEndianShort(m_iLightsYSize);
	m_iWeaponImage      = SwapEndianShort(m_iWeaponImage);
	m_iWeaponMask       = SwapEndianShort(m_iWeaponMask);
	m_iWeaponXSize      = SwapEndianShort(m_iWeaponXSize);
	m_iWeaponYSize      = SwapEndianShort(m_iWeaponYSize);
	m_iFlags            = SwapEndianShort(m_iFlags);
	m_iAnimationDelay   = SwapEndianShort(m_iAnimationDelay);
	m_iWeaponDecay      = SwapEndianShort(m_iWeaponDecay);
	m_iRotationFrames   = SwapEndianShort(m_iRotationFrames);
	m_iBlinkMode        = SwapEndianShort(m_iBlinkMode);
	m_iBlinkValueA      = SwapEndianShort(m_iBlinkValueA);
	m_iBlinkValueB      = SwapEndianShort(m_iBlinkValueB);
	m_iBlinkValueC      = SwapEndianShort(m_iBlinkValueC);
	m_iBlinkValueD      = SwapEndianShort(m_iBlinkValueD);
	m_iShieldImage      = SwapEndianShort(m_iShieldImage);
	m_iShieldMask       = SwapEndianShort(m_iShieldMask);
	m_iShieldXSize      = SwapEndianShort(m_iShieldXSize);
	m_iShieldYSize      = SwapEndianShort(m_iShieldYSize);
	m_iGunPosX[0]       = SwapEndianShort(m_iGunPosX[0]);
	m_iGunPosX[1]       = SwapEndianShort(m_iGunPosX[1]);
	m_iGunPosX[2]       = SwapEndianShort(m_iGunPosX[2]);
	m_iGunPosX[3]       = SwapEndianShort(m_iGunPosX[3]);
	m_iGunPosY[0]       = SwapEndianShort(m_iGunPosY[0]);
	m_iGunPosY[1]       = SwapEndianShort(m_iGunPosY[1]);
	m_iGunPosY[2]       = SwapEndianShort(m_iGunPosY[2]);
	m_iGunPosY[3]       = SwapEndianShort(m_iGunPosY[3]);
	m_iTurretPosX[0]    = SwapEndianShort(m_iTurretPosX[0]);
	m_iTurretPosX[1]    = SwapEndianShort(m_iTurretPosX[1]);
	m_iTurretPosX[2]    = SwapEndianShort(m_iTurretPosX[2]);
	m_iTurretPosX[3]    = SwapEndianShort(m_iTurretPosX[3]);
	m_iTurretPosY[0]    = SwapEndianShort(m_iTurretPosY[0]);
	m_iTurretPosY[1]    = SwapEndianShort(m_iTurretPosY[1]);
	m_iTurretPosY[2]    = SwapEndianShort(m_iTurretPosY[2]);
	m_iTurretPosY[3]    = SwapEndianShort(m_iTurretPosY[3]);
	m_iGuidedPosX[0]    = SwapEndianShort(m_iGuidedPosX[0]);
	m_iGuidedPosX[1]    = SwapEndianShort(m_iGuidedPosX[1]);
	m_iGuidedPosX[2]    = SwapEndianShort(m_iGuidedPosX[2]);
	m_iGuidedPosX[3]    = SwapEndianShort(m_iGuidedPosX[3]);
	m_iGuidedPosY[0]    = SwapEndianShort(m_iGuidedPosY[0]);
	m_iGuidedPosY[1]    = SwapEndianShort(m_iGuidedPosY[1]);
	m_iGuidedPosY[2]    = SwapEndianShort(m_iGuidedPosY[2]);
	m_iGuidedPosY[3]    = SwapEndianShort(m_iGuidedPosY[3]);
	m_iBeamPosX[0]      = SwapEndianShort(m_iBeamPosX[0]);
	m_iBeamPosX[1]      = SwapEndianShort(m_iBeamPosX[1]);
	m_iBeamPosX[2]      = SwapEndianShort(m_iBeamPosX[2]);
	m_iBeamPosX[3]      = SwapEndianShort(m_iBeamPosX[3]);
	m_iBeamPosY[0]      = SwapEndianShort(m_iBeamPosY[0]);
	m_iBeamPosY[1]      = SwapEndianShort(m_iBeamPosY[1]);
	m_iBeamPosY[2]      = SwapEndianShort(m_iBeamPosY[2]);
	m_iBeamPosY[3]      = SwapEndianShort(m_iBeamPosY[3]);
	m_iUpCompressX      = SwapEndianShort(m_iUpCompressX);
	m_iUpCompressY      = SwapEndianShort(m_iUpCompressY);
	m_iDownCompressX    = SwapEndianShort(m_iDownCompressX);
	m_iDownCompressY    = SwapEndianShort(m_iDownCompressY);
	m_iGunPosZ[0]       = SwapEndianShort(m_iGunPosZ[0]);
	m_iGunPosZ[1]       = SwapEndianShort(m_iGunPosZ[1]);
	m_iGunPosZ[2]       = SwapEndianShort(m_iGunPosZ[2]);
	m_iGunPosZ[3]       = SwapEndianShort(m_iGunPosZ[3]);
	m_iTurretPosZ[0]    = SwapEndianShort(m_iTurretPosZ[0]);
	m_iTurretPosZ[1]    = SwapEndianShort(m_iTurretPosZ[1]);
	m_iTurretPosZ[2]    = SwapEndianShort(m_iTurretPosZ[2]);
	m_iTurretPosZ[3]    = SwapEndianShort(m_iTurretPosZ[3]);
	m_iGuidedPosZ[0]    = SwapEndianShort(m_iGuidedPosZ[0]);
	m_iGuidedPosZ[1]    = SwapEndianShort(m_iGuidedPosZ[1]);
	m_iGuidedPosZ[2]    = SwapEndianShort(m_iGuidedPosZ[2]);
	m_iGuidedPosZ[3]    = SwapEndianShort(m_iGuidedPosZ[3]);
	m_iBeamPosZ[0]      = SwapEndianShort(m_iBeamPosZ[0]);
	m_iBeamPosZ[1]      = SwapEndianShort(m_iBeamPosZ[1]);
	m_iBeamPosZ[2]      = SwapEndianShort(m_iBeamPosZ[2]);
	m_iBeamPosZ[3]      = SwapEndianShort(m_iBeamPosZ[3]);

	return 1;
}

int CShanResource::SaveToText(std::ostream & output)
{
	output << m_iRotationFrames   << '\t'
		   << m_iBaseImage        << '\t'
		   << m_iBaseMask         << '\t'
		   << m_iBaseSetCount     << '\t'
		   << m_iBaseXSize        << '\t'
		   << m_iBaseYSize        << '\t'
		   << m_iBaseTransparency << '\t'
		   << m_iAltImage         << '\t'
		   << m_iAltMask          << '\t'
		   << m_iAltSetCount      << '\t'
		   << m_iAltXSize         << '\t'
		   << m_iAltYSize         << '\t'
		   << m_iGlowImage        << '\t'
		   << m_iGlowMask         << '\t'
		   << m_iGlowXSize        << '\t'
		   << m_iGlowYSize        << '\t'
		   << m_iLightsImage      << '\t'
		   << m_iLightsMask       << '\t'
		   << m_iLightsXSize      << '\t'
		   << m_iLightsYSize      << '\t'
		   << m_iWeaponImage      << '\t'
		   << m_iWeaponMask       << '\t'
		   << m_iWeaponXSize      << '\t'
		   << m_iWeaponYSize      << '\t'
		   << m_iShieldImage      << '\t'
		   << m_iShieldMask       << '\t'
		   << m_iShieldXSize      << '\t'
		   << m_iShieldYSize      << '\t'
		   << m_iAnimationDelay   << '\t'
		   << m_iWeaponDecay      << '\t'
		   << m_iBlinkMode        << '\t'
		   << m_iBlinkValueA      << '\t'
		   << m_iBlinkValueB      << '\t'
		   << m_iBlinkValueC      << '\t'
		   << m_iBlinkValueD      << '\t'
		   << m_iGunPosX[0]       << '\t'
		   << m_iGunPosY[0]       << '\t'
		   << m_iGunPosZ[0]       << '\t'
		   << m_iGunPosX[1]       << '\t'
		   << m_iGunPosY[1]       << '\t'
		   << m_iGunPosZ[1]       << '\t'
		   << m_iGunPosX[2]       << '\t'
		   << m_iGunPosY[2]       << '\t'
		   << m_iGunPosZ[2]       << '\t'
		   << m_iGunPosX[3]       << '\t'
		   << m_iGunPosY[3]       << '\t'
		   << m_iGunPosZ[3]       << '\t'
		   << m_iTurretPosX[0]    << '\t'
		   << m_iTurretPosY[0]    << '\t'
		   << m_iTurretPosZ[0]    << '\t'
		   << m_iTurretPosX[1]    << '\t'
		   << m_iTurretPosY[1]    << '\t'
		   << m_iTurretPosZ[1]    << '\t'
		   << m_iTurretPosX[2]    << '\t'
		   << m_iTurretPosY[2]    << '\t'
		   << m_iTurretPosZ[2]    << '\t'
		   << m_iTurretPosX[3]    << '\t'
		   << m_iTurretPosY[3]    << '\t'
		   << m_iTurretPosZ[3]    << '\t'
		   << m_iGuidedPosX[0]    << '\t'
		   << m_iGuidedPosY[0]    << '\t'
		   << m_iGuidedPosZ[0]    << '\t'
		   << m_iGuidedPosX[1]    << '\t'
		   << m_iGuidedPosY[1]    << '\t'
		   << m_iGuidedPosZ[1]    << '\t'
		   << m_iGuidedPosX[2]    << '\t'
		   << m_iGuidedPosY[2]    << '\t'
		   << m_iGuidedPosZ[2]    << '\t'
		   << m_iGuidedPosX[3]    << '\t'
		   << m_iGuidedPosY[3]    << '\t'
		   << m_iGuidedPosZ[3]    << '\t'
		   << m_iBeamPosX[0]      << '\t'
		   << m_iBeamPosY[0]      << '\t'
		   << m_iBeamPosZ[0]      << '\t'
		   << m_iBeamPosX[1]      << '\t'
		   << m_iBeamPosY[1]      << '\t'
		   << m_iBeamPosZ[1]      << '\t'
		   << m_iBeamPosX[2]      << '\t'
		   << m_iBeamPosY[2]      << '\t'
		   << m_iBeamPosZ[2]      << '\t'
		   << m_iBeamPosX[3]      << '\t'
		   << m_iBeamPosY[3]      << '\t'
		   << m_iBeamPosZ[3]      << '\t'
		   << m_iUpCompressX      << '\t'
		   << m_iUpCompressY      << '\t'
		   << m_iDownCompressX    << '\t'
		   << m_iDownCompressY    << '\t';

	PrintHex16Field(output, (char *)&m_iFlags, '\t');

	return 1;
}

int CShanResource::LoadFromText(std::istream & input)
{
	input >> m_iRotationFrames
		  >> m_iBaseImage
		  >> m_iBaseMask
		  >> m_iBaseSetCount
		  >> m_iBaseXSize
		  >> m_iBaseYSize
		  >> m_iBaseTransparency
		  >> m_iAltImage
		  >> m_iAltMask
		  >> m_iAltSetCount
		  >> m_iAltXSize
		  >> m_iAltYSize
		  >> m_iGlowImage
		  >> m_iGlowMask
		  >> m_iGlowXSize
		  >> m_iGlowYSize
		  >> m_iLightsImage
		  >> m_iLightsMask
		  >> m_iLightsXSize
		  >> m_iLightsYSize
		  >> m_iWeaponImage
		  >> m_iWeaponMask
		  >> m_iWeaponXSize
		  >> m_iWeaponYSize
		  >> m_iShieldImage
		  >> m_iShieldMask
		  >> m_iShieldXSize
		  >> m_iShieldYSize
		  >> m_iAnimationDelay
		  >> m_iWeaponDecay
		  >> m_iBlinkMode
		  >> m_iBlinkValueA
		  >> m_iBlinkValueB
		  >> m_iBlinkValueC
		  >> m_iBlinkValueD
		  >> m_iGunPosX[0]
		  >> m_iGunPosY[0]
		  >> m_iGunPosZ[0]
		  >> m_iGunPosX[1]
		  >> m_iGunPosY[1]
		  >> m_iGunPosZ[1]
		  >> m_iGunPosX[2]
		  >> m_iGunPosY[2]
		  >> m_iGunPosZ[2]
		  >> m_iGunPosX[3]
		  >> m_iGunPosY[3]
		  >> m_iGunPosZ[3]
		  >> m_iTurretPosX[0]
		  >> m_iTurretPosY[0]
		  >> m_iTurretPosZ[0]
		  >> m_iTurretPosX[1]
		  >> m_iTurretPosY[1]
		  >> m_iTurretPosZ[1]
		  >> m_iTurretPosX[2]
		  >> m_iTurretPosY[2]
		  >> m_iTurretPosZ[2]
		  >> m_iTurretPosX[3]
		  >> m_iTurretPosY[3]
		  >> m_iTurretPosZ[3]
		  >> m_iGuidedPosX[0]
		  >> m_iGuidedPosY[0]
		  >> m_iGuidedPosZ[0]
		  >> m_iGuidedPosX[1]
		  >> m_iGuidedPosY[1]
		  >> m_iGuidedPosZ[1]
		  >> m_iGuidedPosX[2]
		  >> m_iGuidedPosY[2]
		  >> m_iGuidedPosZ[2]
		  >> m_iGuidedPosX[3]
		  >> m_iGuidedPosY[3]
		  >> m_iGuidedPosZ[3]
		  >> m_iBeamPosX[0]
		  >> m_iBeamPosY[0]
		  >> m_iBeamPosZ[0]
		  >> m_iBeamPosX[1]
		  >> m_iBeamPosY[1]
		  >> m_iBeamPosZ[1]
		  >> m_iBeamPosX[2]
		  >> m_iBeamPosY[2]
		  >> m_iBeamPosZ[2]
		  >> m_iBeamPosX[3]
		  >> m_iBeamPosY[3]
		  >> m_iBeamPosZ[3]
		  >> m_iUpCompressX
		  >> m_iUpCompressY
		  >> m_iDownCompressX
		  >> m_iDownCompressY;

	ReadHex16Field(input, (char *)&m_iFlags);

	return 1;
}

int CShanResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "shan ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_SHAN_EDIT1, CCONTROL_TYPE_INT, IDS_STRING16);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_SHAN_EDIT2, CCONTROL_TYPE_INT, IDS_STRING17);
	m_controls[1].SetInt(m_iBaseImage);
	m_controls[2].Create(hwnd, IDC_EDIT_SHAN_EDIT3, CCONTROL_TYPE_INT, IDS_STRING18);
	m_controls[2].SetInt(m_iBaseMask);
	m_controls[3].Create(hwnd, IDC_EDIT_SHAN_EDIT4, CCONTROL_TYPE_INT, IDS_STRING19);
	m_controls[3].SetInt(m_iBaseSetCount);
	m_controls[4].Create(hwnd, IDC_EDIT_SHAN_EDIT5, CCONTROL_TYPE_INT, IDS_STRING20);
	m_controls[4].SetInt(m_iBaseXSize);
	m_controls[5].Create(hwnd, IDC_EDIT_SHAN_EDIT6, CCONTROL_TYPE_INT, IDS_STRING21);
	m_controls[5].SetInt(m_iBaseYSize);
	m_controls[6].Create(hwnd, IDC_EDIT_SHAN_EDIT7, CCONTROL_TYPE_INT, IDS_STRING22);
	m_controls[6].SetInt(m_iBaseTransparency);
	m_controls[7].Create(hwnd, IDC_EDIT_SHAN_EDIT8, CCONTROL_TYPE_INT, IDS_STRING23);
	m_controls[7].SetInt(m_iAltImage);
	m_controls[8].Create(hwnd, IDC_EDIT_SHAN_EDIT9, CCONTROL_TYPE_INT, IDS_STRING24);
	m_controls[8].SetInt(m_iAltMask);
	m_controls[9].Create(hwnd, IDC_EDIT_SHAN_EDIT10, CCONTROL_TYPE_INT, IDS_STRING25);
	m_controls[9].SetInt(m_iAltSetCount);
	m_controls[10].Create(hwnd, IDC_EDIT_SHAN_EDIT11, CCONTROL_TYPE_INT, IDS_STRING26);
	m_controls[10].SetInt(m_iAltXSize);
	m_controls[11].Create(hwnd, IDC_EDIT_SHAN_EDIT12, CCONTROL_TYPE_INT, IDS_STRING27);
	m_controls[11].SetInt(m_iAltYSize);
	m_controls[12].Create(hwnd, IDC_EDIT_SHAN_EDIT13, CCONTROL_TYPE_INT, IDS_STRING28);
	m_controls[12].SetInt(m_iGlowImage);
	m_controls[13].Create(hwnd, IDC_EDIT_SHAN_EDIT14, CCONTROL_TYPE_INT, IDS_STRING29);
	m_controls[13].SetInt(m_iGlowMask);
	m_controls[14].Create(hwnd, IDC_EDIT_SHAN_EDIT15, CCONTROL_TYPE_INT, IDS_STRING30);
	m_controls[14].SetInt(m_iGlowXSize);
	m_controls[15].Create(hwnd, IDC_EDIT_SHAN_EDIT16, CCONTROL_TYPE_INT, IDS_STRING31);
	m_controls[15].SetInt(m_iGlowYSize);
	m_controls[16].Create(hwnd, IDC_EDIT_SHAN_EDIT17, CCONTROL_TYPE_INT, IDS_STRING32);
	m_controls[16].SetInt(m_iLightsImage);
	m_controls[17].Create(hwnd, IDC_EDIT_SHAN_EDIT18, CCONTROL_TYPE_INT, IDS_STRING33);
	m_controls[17].SetInt(m_iLightsMask);
	m_controls[18].Create(hwnd, IDC_EDIT_SHAN_EDIT19, CCONTROL_TYPE_INT, IDS_STRING34);
	m_controls[18].SetInt(m_iLightsXSize);
	m_controls[19].Create(hwnd, IDC_EDIT_SHAN_EDIT20, CCONTROL_TYPE_INT, IDS_STRING35);
	m_controls[19].SetInt(m_iLightsYSize);
	m_controls[20].Create(hwnd, IDC_EDIT_SHAN_EDIT21, CCONTROL_TYPE_INT, IDS_STRING36);
	m_controls[20].SetInt(m_iWeaponImage);
	m_controls[21].Create(hwnd, IDC_EDIT_SHAN_EDIT22, CCONTROL_TYPE_INT, IDS_STRING37);
	m_controls[21].SetInt(m_iWeaponMask);
	m_controls[22].Create(hwnd, IDC_EDIT_SHAN_EDIT23, CCONTROL_TYPE_INT, IDS_STRING38);
	m_controls[22].SetInt(m_iWeaponXSize);
	m_controls[23].Create(hwnd, IDC_EDIT_SHAN_EDIT24, CCONTROL_TYPE_INT, IDS_STRING39);
	m_controls[23].SetInt(m_iWeaponYSize);
	m_controls[24].Create(hwnd, IDC_EDIT_SHAN_EDIT25, CCONTROL_TYPE_INT, IDS_STRING40);
	m_controls[24].SetInt(m_iShieldImage);
	m_controls[25].Create(hwnd, IDC_EDIT_SHAN_EDIT26, CCONTROL_TYPE_INT, IDS_STRING41);
	m_controls[25].SetInt(m_iShieldMask);
	m_controls[26].Create(hwnd, IDC_EDIT_SHAN_EDIT27, CCONTROL_TYPE_INT, IDS_STRING42);
	m_controls[26].SetInt(m_iShieldXSize);
	m_controls[27].Create(hwnd, IDC_EDIT_SHAN_EDIT28, CCONTROL_TYPE_INT, IDS_STRING43);
	m_controls[27].SetInt(m_iShieldYSize);
	m_controls[28].Create(hwnd, IDC_EDIT_SHAN_EDIT29, CCONTROL_TYPE_INT, IDS_STRING53);
	m_controls[28].SetInt(m_iAnimationDelay);
	m_controls[29].Create(hwnd, IDC_EDIT_SHAN_EDIT30, CCONTROL_TYPE_INT, IDS_STRING54);
	m_controls[29].SetInt(m_iWeaponDecay);
	m_controls[30].Create(hwnd, IDC_EDIT_SHAN_EDIT31, CCONTROL_TYPE_INT, IDS_STRING55);
	m_controls[30].SetInt(m_iRotationFrames);
	m_controls[31].Create(hwnd, IDC_EDIT_SHAN_COMBO1, CCONTROL_TYPE_COMBOBOX, IDS_STRING56);
	m_controls[31].SetComboStrings(NUM_SHAN_BLINKMODE_CHOICES, g_szShanBlinkModeChoices);
	m_controls[32].Create(hwnd, IDC_EDIT_SHAN_EDIT33, CCONTROL_TYPE_INT, IDS_STRING57);
	m_controls[32].SetInt(m_iBlinkValueA);
	m_controls[33].Create(hwnd, IDC_EDIT_SHAN_EDIT34, CCONTROL_TYPE_INT, IDS_STRING58);
	m_controls[33].SetInt(m_iBlinkValueB);
	m_controls[34].Create(hwnd, IDC_EDIT_SHAN_EDIT35, CCONTROL_TYPE_INT, IDS_STRING59);
	m_controls[34].SetInt(m_iBlinkValueC);
	m_controls[35].Create(hwnd, IDC_EDIT_SHAN_EDIT36, CCONTROL_TYPE_INT, IDS_STRING60);
	m_controls[35].SetInt(m_iBlinkValueD);
	m_controls[36].Create(hwnd, IDC_EDIT_SHAN_EDIT37, CCONTROL_TYPE_INT, IDS_STRING61);
	m_controls[36].SetInt(m_iGunPosX[0]);
	m_controls[37].Create(hwnd, IDC_EDIT_SHAN_EDIT54, CCONTROL_TYPE_INT, IDS_STRING61);
	m_controls[37].SetInt(m_iGunPosX[1]);
	m_controls[38].Create(hwnd, IDC_EDIT_SHAN_EDIT62, CCONTROL_TYPE_INT, IDS_STRING61);
	m_controls[38].SetInt(m_iGunPosX[2]);
	m_controls[39].Create(hwnd, IDC_EDIT_SHAN_EDIT70, CCONTROL_TYPE_INT, IDS_STRING61);
	m_controls[39].SetInt(m_iGunPosX[3]);
	m_controls[40].Create(hwnd, IDC_EDIT_SHAN_EDIT38, CCONTROL_TYPE_INT, IDS_STRING62);
	m_controls[40].SetInt(m_iGunPosY[0]);
	m_controls[41].Create(hwnd, IDC_EDIT_SHAN_EDIT55, CCONTROL_TYPE_INT, IDS_STRING62);
	m_controls[41].SetInt(m_iGunPosY[1]);
	m_controls[42].Create(hwnd, IDC_EDIT_SHAN_EDIT63, CCONTROL_TYPE_INT, IDS_STRING62);
	m_controls[42].SetInt(m_iGunPosY[2]);
	m_controls[43].Create(hwnd, IDC_EDIT_SHAN_EDIT71, CCONTROL_TYPE_INT, IDS_STRING62);
	m_controls[43].SetInt(m_iGunPosY[3]);
	m_controls[44].Create(hwnd, IDC_EDIT_SHAN_EDIT39, CCONTROL_TYPE_INT, IDS_STRING63);
	m_controls[44].SetInt(m_iTurretPosX[0]);
	m_controls[45].Create(hwnd, IDC_EDIT_SHAN_EDIT56, CCONTROL_TYPE_INT, IDS_STRING63);
	m_controls[45].SetInt(m_iTurretPosX[1]);
	m_controls[46].Create(hwnd, IDC_EDIT_SHAN_EDIT64, CCONTROL_TYPE_INT, IDS_STRING63);
	m_controls[46].SetInt(m_iTurretPosX[2]);
	m_controls[47].Create(hwnd, IDC_EDIT_SHAN_EDIT72, CCONTROL_TYPE_INT, IDS_STRING63);
	m_controls[47].SetInt(m_iTurretPosX[3]);
	m_controls[48].Create(hwnd, IDC_EDIT_SHAN_EDIT40, CCONTROL_TYPE_INT, IDS_STRING64);
	m_controls[48].SetInt(m_iTurretPosY[0]);
	m_controls[49].Create(hwnd, IDC_EDIT_SHAN_EDIT57, CCONTROL_TYPE_INT, IDS_STRING64);
	m_controls[49].SetInt(m_iTurretPosY[1]);
	m_controls[50].Create(hwnd, IDC_EDIT_SHAN_EDIT65, CCONTROL_TYPE_INT, IDS_STRING64);
	m_controls[50].SetInt(m_iTurretPosY[2]);
	m_controls[51].Create(hwnd, IDC_EDIT_SHAN_EDIT73, CCONTROL_TYPE_INT, IDS_STRING64);
	m_controls[51].SetInt(m_iTurretPosY[3]);
	m_controls[52].Create(hwnd, IDC_EDIT_SHAN_EDIT41, CCONTROL_TYPE_INT, IDS_STRING65);
	m_controls[52].SetInt(m_iGuidedPosX[0]);
	m_controls[53].Create(hwnd, IDC_EDIT_SHAN_EDIT58, CCONTROL_TYPE_INT, IDS_STRING65);
	m_controls[53].SetInt(m_iGuidedPosX[1]);
	m_controls[54].Create(hwnd, IDC_EDIT_SHAN_EDIT66, CCONTROL_TYPE_INT, IDS_STRING65);
	m_controls[54].SetInt(m_iGuidedPosX[2]);
	m_controls[55].Create(hwnd, IDC_EDIT_SHAN_EDIT74, CCONTROL_TYPE_INT, IDS_STRING65);
	m_controls[55].SetInt(m_iGuidedPosX[3]);
	m_controls[56].Create(hwnd, IDC_EDIT_SHAN_EDIT42, CCONTROL_TYPE_INT, IDS_STRING66);
	m_controls[56].SetInt(m_iGuidedPosY[0]);
	m_controls[57].Create(hwnd, IDC_EDIT_SHAN_EDIT59, CCONTROL_TYPE_INT, IDS_STRING66);
	m_controls[57].SetInt(m_iGuidedPosY[1]);
	m_controls[58].Create(hwnd, IDC_EDIT_SHAN_EDIT67, CCONTROL_TYPE_INT, IDS_STRING66);
	m_controls[58].SetInt(m_iGuidedPosY[2]);
	m_controls[59].Create(hwnd, IDC_EDIT_SHAN_EDIT75, CCONTROL_TYPE_INT, IDS_STRING66);
	m_controls[59].SetInt(m_iGuidedPosY[3]);
	m_controls[60].Create(hwnd, IDC_EDIT_SHAN_EDIT43, CCONTROL_TYPE_INT, IDS_STRING67);
	m_controls[60].SetInt(m_iBeamPosX[0]);
	m_controls[61].Create(hwnd, IDC_EDIT_SHAN_EDIT60, CCONTROL_TYPE_INT, IDS_STRING67);
	m_controls[61].SetInt(m_iBeamPosX[1]);
	m_controls[62].Create(hwnd, IDC_EDIT_SHAN_EDIT68, CCONTROL_TYPE_INT, IDS_STRING67);
	m_controls[62].SetInt(m_iBeamPosX[2]);
	m_controls[63].Create(hwnd, IDC_EDIT_SHAN_EDIT76, CCONTROL_TYPE_INT, IDS_STRING67);
	m_controls[63].SetInt(m_iBeamPosX[3]);
	m_controls[64].Create(hwnd, IDC_EDIT_SHAN_EDIT44, CCONTROL_TYPE_INT, IDS_STRING68);
	m_controls[64].SetInt(m_iBeamPosY[0]);
	m_controls[65].Create(hwnd, IDC_EDIT_SHAN_EDIT61, CCONTROL_TYPE_INT, IDS_STRING68);
	m_controls[65].SetInt(m_iBeamPosY[1]);
	m_controls[66].Create(hwnd, IDC_EDIT_SHAN_EDIT69, CCONTROL_TYPE_INT, IDS_STRING68);
	m_controls[66].SetInt(m_iBeamPosY[2]);
	m_controls[67].Create(hwnd, IDC_EDIT_SHAN_EDIT77, CCONTROL_TYPE_INT, IDS_STRING68);
	m_controls[67].SetInt(m_iBeamPosY[3]);
	m_controls[68].Create(hwnd, IDC_EDIT_SHAN_EDIT45, CCONTROL_TYPE_INT, IDS_STRING69);
	m_controls[68].SetInt(m_iUpCompressX);
	m_controls[69].Create(hwnd, IDC_EDIT_SHAN_EDIT46, CCONTROL_TYPE_INT, IDS_STRING70);
	m_controls[69].SetInt(m_iUpCompressY);
	m_controls[70].Create(hwnd, IDC_EDIT_SHAN_EDIT47, CCONTROL_TYPE_INT, IDS_STRING71);
	m_controls[70].SetInt(m_iDownCompressX);
	m_controls[71].Create(hwnd, IDC_EDIT_SHAN_EDIT48, CCONTROL_TYPE_INT, IDS_STRING72);
	m_controls[71].SetInt(m_iDownCompressY);
	m_controls[72].Create(hwnd, IDC_EDIT_SHAN_EDIT49, CCONTROL_TYPE_INT, IDS_STRING73);
	m_controls[72].SetInt(m_iGunPosZ[0]);
	m_controls[73].Create(hwnd, IDC_EDIT_SHAN_EDIT78, CCONTROL_TYPE_INT, IDS_STRING73);
	m_controls[73].SetInt(m_iGunPosZ[1]);
	m_controls[74].Create(hwnd, IDC_EDIT_SHAN_EDIT82, CCONTROL_TYPE_INT, IDS_STRING73);
	m_controls[74].SetInt(m_iGunPosZ[2]);
	m_controls[75].Create(hwnd, IDC_EDIT_SHAN_EDIT86, CCONTROL_TYPE_INT, IDS_STRING73);
	m_controls[75].SetInt(m_iGunPosZ[3]);
	m_controls[76].Create(hwnd, IDC_EDIT_SHAN_EDIT50, CCONTROL_TYPE_INT, IDS_STRING74);
	m_controls[76].SetInt(m_iTurretPosZ[0]);
	m_controls[77].Create(hwnd, IDC_EDIT_SHAN_EDIT79, CCONTROL_TYPE_INT, IDS_STRING74);
	m_controls[77].SetInt(m_iTurretPosZ[1]);
	m_controls[78].Create(hwnd, IDC_EDIT_SHAN_EDIT83, CCONTROL_TYPE_INT, IDS_STRING74);
	m_controls[78].SetInt(m_iTurretPosZ[2]);
	m_controls[79].Create(hwnd, IDC_EDIT_SHAN_EDIT87, CCONTROL_TYPE_INT, IDS_STRING74);
	m_controls[79].SetInt(m_iTurretPosZ[3]);
	m_controls[80].Create(hwnd, IDC_EDIT_SHAN_EDIT51, CCONTROL_TYPE_INT, IDS_STRING75);
	m_controls[80].SetInt(m_iGuidedPosZ[0]);
	m_controls[81].Create(hwnd, IDC_EDIT_SHAN_EDIT80, CCONTROL_TYPE_INT, IDS_STRING75);
	m_controls[81].SetInt(m_iGuidedPosZ[1]);
	m_controls[82].Create(hwnd, IDC_EDIT_SHAN_EDIT84, CCONTROL_TYPE_INT, IDS_STRING75);
	m_controls[82].SetInt(m_iGuidedPosZ[2]);
	m_controls[83].Create(hwnd, IDC_EDIT_SHAN_EDIT88, CCONTROL_TYPE_INT, IDS_STRING75);
	m_controls[83].SetInt(m_iGuidedPosZ[3]);
	m_controls[84].Create(hwnd, IDC_EDIT_SHAN_EDIT52, CCONTROL_TYPE_INT, IDS_STRING76);
	m_controls[84].SetInt(m_iBeamPosZ[0]);
	m_controls[85].Create(hwnd, IDC_EDIT_SHAN_EDIT81, CCONTROL_TYPE_INT, IDS_STRING76);
	m_controls[85].SetInt(m_iBeamPosZ[1]);
	m_controls[86].Create(hwnd, IDC_EDIT_SHAN_EDIT85, CCONTROL_TYPE_INT, IDS_STRING76);
	m_controls[86].SetInt(m_iBeamPosZ[2]);
	m_controls[87].Create(hwnd, IDC_EDIT_SHAN_EDIT89, CCONTROL_TYPE_INT, IDS_STRING76);
	m_controls[87].SetInt(m_iBeamPosZ[3]);
	m_controls[88].Create(hwnd, IDC_EDIT_SHAN_COMBO2, CCONTROL_TYPE_COMBOBOX, IDS_STRING44);
	m_controls[88].SetComboStrings(NUM_SHAN_EXTRAFRAMES_CHOICES, g_szShanExtraFramesChoices);
	m_controls[89].Create(hwnd, IDC_EDIT_SHAN_CHECK5, CCONTROL_TYPE_CHECK, IDS_STRING48);
	m_controls[89].SetInt(m_iFlags & 0x0010);
	m_controls[90].Create(hwnd, IDC_EDIT_SHAN_CHECK6, CCONTROL_TYPE_CHECK, IDS_STRING49);
	m_controls[90].SetInt(m_iFlags & 0x0020);
	m_controls[91].Create(hwnd, IDC_EDIT_SHAN_CHECK7, CCONTROL_TYPE_CHECK, IDS_STRING50);
	m_controls[91].SetInt(m_iFlags & 0x0040);
	m_controls[92].Create(hwnd, IDC_EDIT_SHAN_CHECK8, CCONTROL_TYPE_CHECK, IDS_STRING51);
	m_controls[92].SetInt(m_iFlags & 0x0080);
	m_controls[93].Create(hwnd, IDC_EDIT_SHAN_CHECK9, CCONTROL_TYPE_CHECK, IDS_STRING52);
	m_controls[93].SetInt(m_iFlags & 0x0100);
	m_controls[94].Create(hwnd, IDC_EDIT_SHAN_EDIT53, CCONTROL_TYPE_STR256, IDS_STRING77);
	m_controls[94].SetString(m_szName);

	if((m_iFlags & 0x03) == 0x03)
		m_controls[88].SetInt(2);
	else if(m_iFlags & 0x01)
		m_controls[88].SetInt(1);
	else if(m_iFlags & 0x02)
		m_controls[88].SetInt(3);
	else if(m_iFlags & 0x04)
		m_controls[88].SetInt(4);
	else if(m_iFlags & 0x08)
		m_controls[88].SetInt(5);
	else
		m_controls[88].SetInt(0);

	if(m_iBlinkMode == -1)
		m_controls[31].SetInt(0);
	else
		m_controls[31].SetInt(m_iBlinkMode);

	if((m_iBlinkMode == -1) || (m_iBlinkMode == 0))
	{
		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT33), "(Ignored)");
		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT34), "(Ignored)");
		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT35), "(Ignored)");
		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT36), "(Ignored)");
	}
	else if(m_iBlinkMode == 1)
	{
		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT33), "Light on time");
		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT34), "Light off time");
		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT35), "Blinks per group");
		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT36), "Delay between groups");
	}
	else if(m_iBlinkMode == 2)
	{
		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT33), "Min intensity (1-32)");
		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT34), "Intensity increase (x100)");
		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT35), "Max intensity (1-32)");
		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT36), "Intensity decrease (x100)");
	}
	else
	{
		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT33), "Min intensity (1-32)");
		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT34), "Max intensity (1-32)");
		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT35), "Intensity change delay");
		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT36), "(Ignored)");
	}

	return 1;
}

int CShanResource::CloseAndSave(void)
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

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[94].GetString()) != 0))
		iIDOrNameChanged = 1;

	m_iID = m_controls[0].GetInt();

	m_iBaseImage        = m_controls[1].GetInt();
	m_iBaseMask         = m_controls[2].GetInt();
	m_iBaseSetCount     = m_controls[3].GetInt();
	m_iBaseXSize        = m_controls[4].GetInt();
	m_iBaseYSize        = m_controls[5].GetInt();
	m_iBaseTransparency = m_controls[6].GetInt();

	m_iAltImage    = m_controls[7].GetInt();
	m_iAltMask     = m_controls[8].GetInt();
	m_iAltSetCount = m_controls[9].GetInt();
	m_iAltXSize    = m_controls[10].GetInt();
	m_iAltYSize    = m_controls[11].GetInt();

	m_iGlowImage = m_controls[12].GetInt();
	m_iGlowMask  = m_controls[13].GetInt();
	m_iGlowXSize = m_controls[14].GetInt();
	m_iGlowYSize = m_controls[15].GetInt();

	m_iLightsImage = m_controls[16].GetInt();
	m_iLightsMask  = m_controls[17].GetInt();
	m_iLightsXSize = m_controls[18].GetInt();
	m_iLightsYSize = m_controls[19].GetInt();

	m_iWeaponImage = m_controls[20].GetInt();
	m_iWeaponMask  = m_controls[21].GetInt();
	m_iWeaponXSize = m_controls[22].GetInt();
	m_iWeaponYSize = m_controls[23].GetInt();

	m_iShieldImage = m_controls[24].GetInt();
	m_iShieldMask  = m_controls[25].GetInt();
	m_iShieldXSize = m_controls[26].GetInt();
	m_iShieldYSize = m_controls[27].GetInt();

	m_iAnimationDelay = m_controls[28].GetInt();
	m_iWeaponDecay    = m_controls[29].GetInt();

	m_iRotationFrames = m_controls[30].GetInt();

	m_iBlinkMode   = m_controls[31].GetInt();
	m_iBlinkValueA = m_controls[32].GetInt();
	m_iBlinkValueB = m_controls[33].GetInt();
	m_iBlinkValueC = m_controls[34].GetInt();
	m_iBlinkValueD = m_controls[35].GetInt();

	m_iGunPosX[0]    = m_controls[36].GetInt();
	m_iGunPosX[1]    = m_controls[37].GetInt();
	m_iGunPosX[2]    = m_controls[38].GetInt();
	m_iGunPosX[3]    = m_controls[39].GetInt();
	m_iGunPosY[0]    = m_controls[40].GetInt();
	m_iGunPosY[1]    = m_controls[41].GetInt();
	m_iGunPosY[2]    = m_controls[42].GetInt();
	m_iGunPosY[3]    = m_controls[43].GetInt();
	m_iTurretPosX[0] = m_controls[44].GetInt();
	m_iTurretPosX[1] = m_controls[45].GetInt();
	m_iTurretPosX[2] = m_controls[46].GetInt();
	m_iTurretPosX[3] = m_controls[47].GetInt();
	m_iTurretPosY[0] = m_controls[48].GetInt();
	m_iTurretPosY[1] = m_controls[49].GetInt();
	m_iTurretPosY[2] = m_controls[50].GetInt();
	m_iTurretPosY[3] = m_controls[51].GetInt();
	m_iGuidedPosX[0] = m_controls[52].GetInt();
	m_iGuidedPosX[1] = m_controls[53].GetInt();
	m_iGuidedPosX[2] = m_controls[54].GetInt();
	m_iGuidedPosX[3] = m_controls[55].GetInt();
	m_iGuidedPosY[0] = m_controls[56].GetInt();
	m_iGuidedPosY[1] = m_controls[57].GetInt();
	m_iGuidedPosY[2] = m_controls[58].GetInt();
	m_iGuidedPosY[3] = m_controls[59].GetInt();
	m_iBeamPosX[0]   = m_controls[60].GetInt();
	m_iBeamPosX[1]   = m_controls[61].GetInt();
	m_iBeamPosX[2]   = m_controls[62].GetInt();
	m_iBeamPosX[3]   = m_controls[63].GetInt();
	m_iBeamPosY[0]   = m_controls[64].GetInt();
	m_iBeamPosY[1]   = m_controls[65].GetInt();
	m_iBeamPosY[2]   = m_controls[66].GetInt();
	m_iBeamPosY[3]   = m_controls[67].GetInt();

	m_iUpCompressX   = m_controls[68].GetInt();
	m_iUpCompressY   = m_controls[69].GetInt();
	m_iDownCompressX = m_controls[70].GetInt();
	m_iDownCompressY = m_controls[71].GetInt();

	m_iGunPosZ[0]    = m_controls[72].GetInt();
	m_iGunPosZ[1]    = m_controls[73].GetInt();
	m_iGunPosZ[2]    = m_controls[74].GetInt();
	m_iGunPosZ[3]    = m_controls[75].GetInt();
	m_iTurretPosZ[0] = m_controls[76].GetInt();
	m_iTurretPosZ[1] = m_controls[77].GetInt();
	m_iTurretPosZ[2] = m_controls[78].GetInt();
	m_iTurretPosZ[3] = m_controls[79].GetInt();
	m_iGuidedPosZ[0] = m_controls[80].GetInt();
	m_iGuidedPosZ[1] = m_controls[81].GetInt();
	m_iGuidedPosZ[2] = m_controls[82].GetInt();
	m_iGuidedPosZ[3] = m_controls[83].GetInt();
	m_iBeamPosZ[0]   = m_controls[84].GetInt();
	m_iBeamPosZ[1]   = m_controls[85].GetInt();
	m_iBeamPosZ[2]   = m_controls[86].GetInt();
	m_iBeamPosZ[3]   = m_controls[87].GetInt();

	m_iFlags = 0x0000;

	int iChoice = m_controls[88].GetInt();

	if(iChoice == 1)
		m_iFlags |= 0x0001;
	else if(iChoice == 2)
		m_iFlags |= 0x0003;
	else if(iChoice == 3)
		m_iFlags |= 0x0002;
	else if(iChoice == 4)
		m_iFlags |= 0x0004;
	else if(iChoice == 5)
		m_iFlags |= 0x0008;

	m_iFlags |= m_controls[89].GetInt() << 4;
	m_iFlags |= m_controls[90].GetInt() << 5;
	m_iFlags |= m_controls[91].GetInt() << 6;
	m_iFlags |= m_controls[92].GetInt() << 7;
	m_iFlags |= m_controls[93].GetInt() << 8;

	strcpy_s(m_szName, m_controls[94].GetString());

	int i;

	for(i = 0; i < NUM_SHAN_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CShanResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_SHAN_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CShanResource::ShanDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CShanResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CShanResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_SHAN_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_SHAN_OK)
			{
				pResource->CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_SHAN_CONTROLS; i++)
				{
					if(iControlID == pResource->m_controls[i].GetControlID())
					{
						pResource->m_controls[i].ProcessMessage(iNotifyCode);

						break;
					}
				}
			}

			if((iNotifyCode == CBN_SELCHANGE) && (iControlID == IDC_EDIT_SHAN_COMBO1))
			{
				int iIndex = ComboBox_GetCurSel((HWND)lparam);

				if(iIndex == 0)
				{
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT33), "(Ignored)");
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT34), "(Ignored)");
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT35), "(Ignored)");
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT36), "(Ignored)");
				}
				else if(iIndex == 1)
				{
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT33), "Light on time");
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT34), "Light off time");
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT35), "Blinks per group");
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT36), "Delay between groups");
				}
				else if(iIndex == 2)
				{
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT33), "Min intensity (1-32)");
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT34), "Intensity increase (x100)");
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT35), "Max intensity (1-32)");
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT36), "Intensity decrease (x100)");
				}
				else
				{
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT33), "Min intensity (1-32)");
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT34), "Max intensity (1-32)");
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT35), "Intensity change delay");
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHAN_TEXT36), "(Ignored)");
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
