// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CWeapResource.h

#ifndef CWEAPRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CWEAPRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CWeapResource;

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

const int NUM_WEAP_CONTROLS = 96;

const int NUM_WEAP_GUIDANCE_CHOICES = 12;

const std::string g_szWeapGuidanceChoices[NUM_WEAP_GUIDANCE_CHOICES] =
	{"Unguided projectile", "Beam weapon", "Homing weapon", "Turreted beam",
	 "Turreted unguided projectile", "Freefall bomb", "Freeflight rocket",
	 "Front quadrant turret", "Rear quadrant turret", "Point defense turret",
	 "Point defense beam", "Carried ship"};

const int NUM_WEAP_EXITTYPE_CHOICES = 5;

const std::string g_szWeapExitTypeChoices[NUM_WEAP_EXITTYPE_CHOICES] =
	{"Center of ship", "Gun exit points", "Turret exit points",
	 "Guided weapon exit points", "Beam exit points"};

const int NUM_WEAP_FIELDS = 54;

const std::string g_szWeapFields[NUM_WEAP_FIELDS] =
	{"Reload", "Lifetime", "Mass Damage", "Energy Damage", "Guidance", "Speed",
	 "Ammo Type", "Graphics", "Inaccuracy", "Sound", "Impact", "Explosion Type",
	 "Proximity Radius", "Blast Radius", "Smoke Set", "Decay", "Particle Count",
	 "Particle Velocity", "Min Particle Life", "Max Particle Life",
	 "Particle Color", "Beam Length", "Beam Width", "Beam Falloff", "Beam Color",
	 "Corona Color", "Submunitions Count", "Submunitions Type",
	 "Submunitions Angle", "Submunitions Limit", "Proximity Delay", "Ionization",
	 "Hit Particle Count", "Hit Particle Life", "Hit Particle Velocity",
	 "Hit Particle Color", "Exit Type", "Burst Count", "Burst Reload",
	 "Jamming Type 1 Vulnerability", "Jamming Type 2 Vulnerability",
	 "Jamming Type 3 Vulnerability", "Jamming Type 4 Vulnerability", "Durability",
	 "Guided Turn Rate", "Max Ammo", "Recoil", "Lightning Density",
	 "Lightning Amplitude", "Ionization Color", "Flags 1", "Flags 2", "Flags 3",
	 "Seeker Flags"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CWeapResource : public CNovaResource
{
public:

	CWeapResource(void);
	~CWeapResource(void);

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

	static BOOL WeapDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	short m_iReload;
	short m_iLifetime;

	short m_iMassDamage;
	short m_iEnergyDamage;

	short m_iGuidance;
	short m_iSpeed;
	short m_iAmmoType;

	short m_iGraphics;

	short m_iInaccuracy;

	short m_iSound;

	short m_iImpact;
	short m_iExplosionType;
	short m_iProximityRadius;
	short m_iBlastRadius;

	short m_iSmokeSet;

	short m_iDecay;

	short m_iParticleCount;
	short m_iParticleVelocity;
	short m_iParticleMinLife;
	short m_iParticleMaxLife;
	UINT  m_iParticleColor;

	short m_iBeamLength;
	short m_iBeamWidth;
	short m_iBeamFalloff;
	UINT  m_iBeamColor;
	UINT  m_iCoronaColor;

	short m_iSubmunitionsCount;
	short m_iSubmunitionsType;
	short m_iSubmunitionsAngle;
	short m_iSubmunitionsLimit;

	short m_iProximityDelay;

	short m_iIonization;

	short m_iHitParticleCount;
	short m_iHitParticleLife;
	short m_iHitParticleVelocity;
	UINT  m_iHitParticleColor;

	short m_iExitType;

	short m_iBurstCount;
	short m_iBurstReload;

	short m_iJammingVulnerability[4];

	short m_iDurability;

	short m_iGuidedTurnRate;

	short m_iMaxAmmo;

	short m_iRecoil;

	short m_iLightningDensity;
	short m_iLightningAmplitude;

	UINT  m_iIonizationColor;

	USHORT m_iFlags1;
	USHORT m_iFlags2;
	USHORT m_iFlags3;
	USHORT m_iSeekerFlags;

	CControl m_controls[NUM_WEAP_CONTROLS];
};

#endif		// #ifndef CWEAPRESOURCE_H_INCLUDED
