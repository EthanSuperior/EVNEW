// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CShanResource.h

#ifndef CSHANRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CSHANRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CShanResource;

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>

#include <string>

#include "CControl.h"
#include "CNovaResource.h"
#include "Utils.h"

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

const int NUM_SHAN_CONTROLS = 95;

const int NUM_SHAN_EXTRAFRAMES_CHOICES = 6;

const std::string g_szShanExtraFramesChoices[NUM_SHAN_EXTRAFRAMES_CHOICES] =
	{"No extra frames", "Banking", "Banking with engine glow", "Animated ship parts",
	 "When carrying Key Carried ships", "Shown in sequence"};

const int NUM_SHAN_BLINKMODE_CHOICES = 4;

const std::string g_szShanBlinkModeChoices[NUM_SHAN_BLINKMODE_CHOICES] =
	{"None", "Square", "Triangle", "Random"};

const int NUM_SHAN_FIELDS = 88;

const std::string g_szShanFields[NUM_SHAN_FIELDS] =
	{"Frames", "Base Image", "Base Mask", "Base Set Count", "Base X Size", "Base Y Size",
	 "Base Transparency", "Alternate Image", "Alternate Image Mask",
	 "Alternate Image Set Count", "Alternate Image X Size", "Alternate Image Y Size",
	 "Engine Glow Image", "Engine Glow Mask", "Engine Glow X Size", "Engine Glow Y Size",
	 "Running Lights Image", "Running Lights Mask", "Running Lights X Size",
	 "Running Lights Y Size", "Weapon Image", "Weapon Mask", "Weapon X Size",
	 "Weapon Y Size", "Shield Image", "Shield Mask", "Shield X Size", "Shield Y Size",
	 "Animation Delay", "Weapon Decay", "Blink Mode", "Blink Value A", "Blink Value B",
	 "Blink Value C", "Blink Value D", "Gun Exit 1 X", "Gun Exit 1 Y", "Gun Exit 1 Z",
	 "Gun Exit 2 X", "Gun Exit 2 Y", "Gun Exit 2 Z", "Gun Exit 3 X", "Gun Exit 3 Y",
	 "Gun Exit 3 Z", "Gun Exit 4 X", "Gun Exit 4 Y", "Gun Exit 4 Z", "Turret Exit 1 X",
	 "Turret Exit 1 Y", "Turret Exit 1 Z", "Turret Exit 2 X", "Turret Exit 2 Y",
	 "Turret Exit 2 Z", "Turret Exit 3 X", "Turret Exit 3 Y", "Turret Exit 3 Z",
	 "Turret Exit 4 X", "Turret Exit 4 Y", "Turret Exit 4 Z", "Guided Exit 1 X",
	 "Guided Exit 1 Y", "Guided Exit 1 Z", "Guided Exit 2 X", "Guided Exit 2 Y",
	 "Guided Exit 2 Z", "Guided Exit 3 X", "Guided Exit 3 Y", "Guided Exit 3 Z",
	 "Guided Exit 4 X", "Guided Exit 4 Y", "Guided Exit 4 Z", "Beam Exit 1 X",
	 "Beam Exit 1 Y", "Beam Exit 1 Z", "Beam Exit 2 X", "Beam Exit 2 Y", "Beam Exit 2 Z",
	 "Beam Exit 3 X", "Beam Exit 3 Y", "Beam Exit 3 Z", "Beam Exit 4 X", "Beam Exit 4 Y",
	 "Beam Exit 4 Z", "Up Compress X", "Up Compress Y", "Down Compress X", "Down Compress Y",
	 "Flags"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CShanResource : public CNovaResource
{
public:

	CShanResource(void);
	~CShanResource(void);

	int GetType(void);
	int GetSize(void);

	int GetDialogID(void);
	DLGPROCNOCALLBACK GetDialogProc(void);

	int GetNumFields(void);
	const std::string * GetFieldNames(void);

	int Initialize(HWND hwnd);

	int CloseAndSave(void);
	int CloseAndDontSave(void);

	int Save(char *pOutput);
	int Load(char *pInput, int iSize);

	int SaveToText(std::ostream & output);
	int LoadFromText(std::istream & input);

	static BOOL ShanDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	short m_iBaseImage;
	short m_iBaseMask;
	short m_iBaseSetCount;
	short m_iBaseXSize;
	short m_iBaseYSize;
	short m_iBaseTransparency;

	short m_iAltImage;
	short m_iAltMask;
	short m_iAltSetCount;
	short m_iAltXSize;
	short m_iAltYSize;

	short m_iGlowImage;
	short m_iGlowMask;
	short m_iGlowXSize;
	short m_iGlowYSize;

	short m_iLightsImage;
	short m_iLightsMask;
	short m_iLightsXSize;
	short m_iLightsYSize;

	short m_iWeaponImage;
	short m_iWeaponMask;
	short m_iWeaponXSize;
	short m_iWeaponYSize;

	short m_iShieldImage;
	short m_iShieldMask;
	short m_iShieldXSize;
	short m_iShieldYSize;

	USHORT m_iFlags;

	short m_iAnimationDelay;
	short m_iWeaponDecay;

	short m_iRotationFrames;

	short m_iBlinkMode;
	short m_iBlinkValueA;
	short m_iBlinkValueB;
	short m_iBlinkValueC;
	short m_iBlinkValueD;

	short m_iGunPosX[4];
	short m_iGunPosY[4];
	short m_iTurretPosX[4];
	short m_iTurretPosY[4];
	short m_iGuidedPosX[4];
	short m_iGuidedPosY[4];
	short m_iBeamPosX[4];
	short m_iBeamPosY[4];

	short m_iUpCompressX;
	short m_iUpCompressY;
	short m_iDownCompressX;
	short m_iDownCompressY;

	short m_iGunPosZ[4];
	short m_iTurretPosZ[4];
	short m_iGuidedPosZ[4];
	short m_iBeamPosZ[4];

	CControl m_controls[NUM_SHAN_CONTROLS];
};

#endif		// #ifndef CSHANRESOURCE_H_INCLUDED
