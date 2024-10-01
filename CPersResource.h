// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CPersResource.h

#ifndef CPERSRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CPERSRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CPersResource;

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>

#include <string>

#include "CControl.h"
#include "CNovaResource.h"

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

constexpr int NUM_PERS_CONTROLS = 49;

constexpr int NUM_PERS_AGGRESSION_CHOICES = 3;

const std::string g_szPersAggressionChoices[NUM_PERS_AGGRESSION_CHOICES] =
	{"Close", "Average", "Far"};

constexpr int NUM_PERS_FIELDS = 32;

const std::string g_szPersFields[NUM_PERS_FIELDS] =
	{"System", "Government", "AI Type", "Aggression", "Cowardice", "Ship Type",
	 "Credits", "Shield Mod", "Hail Picture", "Communication Quote",
	 "Hail Quote", "Linked Mission", "Active On", "Grant Class", "Grant Count",
	 "Grant Random", "Subtitle", "Color", "Weapon 1", "Weapon 2", "Weapon 3",
	 "Weapon 4", "Weapon 1 Count", "Weapon 2 Count", "Weapon 3 Count",
	 "Weapon 4 Count", "Weapon 1 Ammo", "Weapon 2 Ammo", "Weapon 3 Ammo",
	 "Weapon 4 Ammo", "Flags 1", "Flags 2"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CPersResource : public CNovaResource
{
public:

	CPersResource(void);
	~CPersResource(void) override;

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

	static BOOL PersDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	short m_iSystem;
	short m_iGovernment;

	short m_iAIType;

	short m_iAggressiveness;
	short m_iCowardice;

	short m_iShipType;

	short m_iWeaponTypes[4];
	short m_iWeaponCounts[4];
	short m_iWeaponAmmos[4];

	int   m_iCredits;

	short m_iShieldMod;

	short m_iHailPicture;
	short m_iCommQuote;
	short m_iHailQuote;

	short m_iLinkedMission;

	USHORT m_iFlags1;

	char  m_szActiveOn[256];

	short m_iGrantClass;
	short m_iGrantCount;
	short m_iGrantRandom;

	char  m_szSubtitle[64];

	UINT  m_iColor;

	USHORT m_iFlags2;

	CControl m_controls[NUM_PERS_CONTROLS];
};

#endif		// #ifndef CPERSRESOURCE_H_INCLUDED
