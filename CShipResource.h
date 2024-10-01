// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CShipResource.h

#ifndef CSHIPRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CSHIPRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CShipResource;

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>

#include <string>

#include "CControl.h"
#include "CBitFieldControl.h"
#include "CNovaResource.h"

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

constexpr int NUM_SHIP_CONTROLS = 127;

constexpr int NUM_SHIP_ESCORTTYPE_CHOICES = 5;

const std::string g_szShipEscortTypeChoices[NUM_SHIP_ESCORTTYPE_CHOICES] =
	{"Let Nova figure it out", "Fighter", "Medium ship", "Warship", "Freighter"};

constexpr int NUM_SHIP_FIELDS = 91;

const std::string g_szShipFields[NUM_SHIP_FIELDS] =
	{"Cargo", "Shields", "Shield Recharge", "Armor", "Armor Recharge", "Acceleration",
	 "Max Speed", "Turning", "Fuel", "Free Mass", "Max Guns", "Max Turrets", "Tech Level",
	 "Cost", "Death Delay", "Explosion 1", "Explosion 2", "Display Weight", "Mass",
	 "Length", "Crew", "Strength", "Government", "Escape Pod Count", "Fuel Regeneration",
	 "Skill Variation", "Availability", "Appear On", "On Purchase", "Deionize",
	 "Max Ionization", "Key Carried", "Contribute Bits", "Require Bits", "Buy Random",
	 "Hire Random", "On Capture", "On Retire", "Subtitle", "Short Name",
	 "Communication Name", "Long Name", "Movie File", "Escort AI", "Escort Upgrade To",
	 "Escort Upgrade Cost", "Escort Sell Value", "Escort Type", "Weapon 1", "Weapon 2",
	 "Weapon 3", "Weapon 4", "Weapon 5", "Weapon 6", "Weapon 7", "Weapon 8",
	 "Weapon 1 Count", "Weapon 2 Count", "Weapon 3 Count", "Weapon 4 Count",
	 "Weapon 5 Count", "Weapon 6 Count", "Weapon 7 Count", "Weapon 8 Count",
	 "Weapon 1 Ammo", "Weapon 2 Ammo", "Weapon 3 Ammo", "Weapon 4 Ammo", "Weapon 5 Ammo",
	 "Weapon 6 Ammo", "Weapon 7 Ammo", "Weapon 8 Ammo", "Outfit 1", "Outfit 2",
	 "Outfit 3", "Outfit 4", "Outfit 5", "Outfit 6", "Outfit 7", "Outfit 8",
	 "Outfit 1 Count", "Outfit 2 Count", "Outfit 3 Count", "Outfit 4 Count",
	 "Outfit 5 Count", "Outfit 6 Count", "Outfit 7 Count", "Outfit 8 Count", "Flags 1",
	 "Flags 2", "Flags 3"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CShipResource : public CNovaResource
{
public:

	CShipResource(void);
	~CShipResource(void) override;

	int GetType(void) override;
	int GetSize(void) override;

	int GetDialogID(void) override;
	DLGPROCNOCALLBACK GetDialogProc(void) override;

	int GetNumFields(void) override;
	const std::string * GetFieldNames(void) override;

	int Initialize(HWND hwnd) override;

	int CloseAndSave(void) override;
	int CloseAndDontSave(void) override;

	int Save(char *pOutput) override;
	int Load(char *pInput, int iSize) override;

	int SaveToText(std::ostream & output) override;
	int LoadFromText(std::istream & input) override;

	static BOOL ShipDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	short m_iCargo;

	short m_iShields;
	short m_iShieldRecharge;
	short m_iArmor;
	short m_iArmorRecharge;

	short m_iAcceleration;
	short m_iMaxSpeed;
	short m_iTurning;

	short m_iFuel;

	short m_iFreeMass;

	short m_iMaxGuns;
	short m_iMaxTurrets;

	short m_iTechLevel;

	int   m_iCost;

	short m_iDeathDelay;
	short m_iExplosion1;
	short m_iExplosion2;

	short m_iDisplayWeight;

	short m_iMass;
	short m_iLength;
	short m_iCrew;
	short m_iStrength;

	short m_iGovernment;

	short m_iEscapePodCount;

	short m_iFuelRegeneration;

	short m_iSkillVariation;

	char  m_szAvailability[255];
	char  m_szAppearOn[255];
	char  m_szOnPurchase[256];

	short m_iDeionize;
	short m_iMaxIonization;

	short m_iKeyCarried;

	char  m_cContribute[8];
	char  m_cRequire[8];

	short m_iBuyRandom;
	short m_iHireRandom;

	char  m_szOnCapture[255];
	char  m_szOnRetire[255];

	char  m_szSubtitle[64];
	char  m_szShortName[64];
	char  m_szCommName[32];
	char  m_szLongName[128];

	char  m_szMovieFile[32];

	short m_iEscortAI;
	short m_iEscortUpgradeTo;
	int   m_iEscortUpgradeCost;
	int   m_iEscortSellValue;
	short m_iEscortType;

	short m_iWeapons[8];
	short m_iWeaponCounts[8];
	short m_iWeaponAmmos[8];

	short m_iOutfits[8];
	short m_iOutfitCounts[8];

	USHORT m_iFlags1;
	USHORT m_iFlags2;
	USHORT m_iFlags3;

	CControl m_controls[NUM_SHIP_CONTROLS];

	CBitFieldControl m_bitFieldControl;
};

#endif		// #ifndef CSHIPRESOURCE_H_INCLUDED
