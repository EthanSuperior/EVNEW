// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File COutfResource.h

#ifndef COUTFRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define COUTFRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class COutfResource;

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

const int NUM_OUTF_CONTROLS = 44;

const int NUM_OUTF_MODTYPE_CHOICES = 49;

const std::string g_szOutfModTypeChoices[NUM_OUTF_MODTYPE_CHOICES] =
	{"Unused", "Weapon", "More cargo space", "Ammunition", "More shield capacity",
	 "Faster shield recharge", "More armor capacity", "Acceleration booster",
	 "Speed increase", "Turning increase", "Escape pod", "More fuel capacity",
	 "Density scanner", "IFF scanner", "Afterburner", "Map", "Cloaking device",
	 "Fuel scoop", "Auto-refueler", "Auto-eject", "Clean legal record",
	 "Jump days mod", "Jump distance mod", "Interference mod", "Marines",
	 "Max outfits", "Murkiness", "Faster armor recharge", "Cloak scanner",
	 "Mining scoop", "Multi-jump", "Jamming type 1", "Jamming type 2",
	 "Jamming type 3", "Jamming type 4", "Fast jumping", "Inertial dampener",
	 "Deionizer", "Ion capacity mod", "Gravity resistance",
	 "Deadly stellar resistance", "Paint", "Reinforcement inhibiter",
	 "Max guns mod", "Max turrets mod", "Bomb", "IFF scrambler", "Repair system",
	 "Nonlethal bomb"};

const std::string g_szOutfModValueTexts[NUM_OUTF_MODTYPE_CHOICES] =
	{"(Ignored)", "Weapon ID", "Amount of cargo to add", "Associated weapon ID",
	 "Shield points to add", "Shield recharge to add",
	 "Armor points to add", "Acceleration to add", "Max speed to add",
	 "Amount of turning to add", "(Ignored)", "Extra fuel to add", "(Ignored)",
	 "(Ignored)", "Fuel used (units/sec)", "(See Bible for details)", "(Click for details)",
	 "Frames to generate 1 unit of fuel", "(Ignored)", "(Ignored)",
	 "Government ID or -1 for all", "Days to change hyperspace jump time",
	 "Pixels to change no-jump zone radius", "Amount of interference to subtract",
	 "Crew to add", "Outfit ID to increase maximum of",
	 "Amount to change murkiness", "Amount of armor recharge to add",
	 "(Click for details)", "(Ignored)", "Number of extra jumps",
	 "Amount of jamming to add or subtract", "Amount of jamming to add or subtract",
	 "Amount of jamming to add or subtract", "Amount of jamming to add or subtract",
	 "(Ignored)", "(Ignored)", "Amount of deionization rate to add",
	 "Amount of extra ionization capacity", "(Ignored)", "(Ignored)",
	 "15-bit color to paint ship", "Government class",
	 "Number of max guns to add or subtract", "Number of max turrets to add or subtract",
	 "Desc ID to show when destroyed", "Government class", "(Ignored)",
	 "Boom ID to display"};

const int NUM_OUTF_FIELDS = 26;

const std::string g_szOutfFields[NUM_OUTF_FIELDS] =
	{"Display Weight", "Mass", "Tech Level", "Mod Type 1", "Mod Value 1",
	 "Mod Type 2", "Mod Value 2", "Mod Type 3", "Mod Value 3", "Mod Type 4",
	 "Mod Value 4", "Max Count", "Cost", "Item Class", "Scan Mask", "Buy Random",
	 "Availability", "On Purchase", "On Sell", "Contribute Bits", "Require Bits",
	 "Short Name", "Lower Case Name", "Lower Case Plural Name",
	 "Requirments Government", "Flags"};

const int NUM_OUTF_MODTYPE17_CONTROLS = 7;
const int NUM_OUTF_MODTYPE30_CONTROLS = 4;

const int NUM_OUTF_MODTYPE17_FUELSHIELDDRAIN_CHOICES = 16;

const std::string g_szOutfModType17FuelShieldDrainChoices[NUM_OUTF_MODTYPE17_FUELSHIELDDRAIN_CHOICES] =
	{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class COutfResource : public CNovaResource
{
public:

	COutfResource(void);
	~COutfResource(void);

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

	static BOOL OutfDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	static BOOL OutfEditModType17DlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static BOOL OutfEditModType30DlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	int DoEditModType17(void);
	int DoEditModType30(void);

	int InitModType17Controls(HWND hwnd);
	int InitModType30Controls(HWND hwnd);

	int ModType17CloseAndSave(void);
	int ModType17CloseAndDontSave(void);
	int ModType30CloseAndSave(void);
	int ModType30CloseAndDontSave(void);

	int SwapEndians(void);

	short ModTypeToIndex(short iModType);
	short IndexToModType(short iIndex);

	short m_iDisplayWeight;
	short m_iMass;
	short m_iTechLevel;

	short m_iModTypes[4];
	short m_iModValues[4];

	short m_iMaxCount;

	USHORT m_iFlags;

	int   m_iCost;

	char  m_szAvailability[255];
	char  m_szOnPurchase[255];

	char  m_cContribute[8];
	char  m_cRequire[8];

	char  m_szOnSell[255];

	short m_iItemClass;

	char  m_cScanMask[2];

	short m_iBuyRandom;

	char  m_szShortName[64];
	char  m_szLowerCaseName[64];
	char  m_szLowerCasePluralName[65];

	short m_iRequiredGovernment;

	CControl m_controls[NUM_OUTF_CONTROLS];

	CBitFieldControl m_bitFieldControl;

	int m_iEditModTypeIndex;

	CControl m_controlsModType17[NUM_OUTF_MODTYPE17_CONTROLS];
	CControl m_controlsModType30[NUM_OUTF_MODTYPE30_CONTROLS];

	CWindow m_wndEditModType17or30;
};

#endif		// #ifndef COUTFRESOURCE_H_INCLUDED
