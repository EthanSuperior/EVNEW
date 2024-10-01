// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CMisnResource.h

#ifndef CMISNRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CMISNRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CMisnResource;

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

const int NUM_MISN_CONTROLS = 69;

const int NUM_MISN_AVAILLOCATION_CHOICES = 7;

const std::string g_szMisnAvailLocationChoices[NUM_MISN_AVAILLOCATION_CHOICES] =
	{"Mission computer", "Bar", "Offered from ship", "Main spaceport", "Commodity exchange", "Shipyard", "Outfitter"};

const int NUM_MISN_CARGOPICKUPMODE_CHOICES = 4;

const std::string g_szMisnCargoPickupModeChoices[NUM_MISN_CARGOPICKUPMODE_CHOICES] =
	{"No cargo", "Mission start", "At Travel Stellar", "When boarding special ship"};

const int NUM_MISN_CARGODROPOFFMODE_CHOICES = 3;

const std::string g_szMisnCargoDropoffModeChoices[NUM_MISN_CARGODROPOFFMODE_CHOICES] =
	{"No cargo", "At Travel Stellar", "Mission end"};

const int NUM_MISN_SHIPGOAL_CHOICES = 8;

const std::string g_szMisnShipGoalChoices[NUM_MISN_SHIPGOAL_CHOICES] =
	{"No goal", "Destroy all ships", "Disable but don't destroy them", "Board them",
	 "Escort them", "Observe them", "Rescue them", "Chase them off"};

const int NUM_MISN_SHIPBEHAVIOR_CHOICES = 4;

const std::string g_szMisnShipBehaviorChoices[NUM_MISN_SHIPBEHAVIOR_CHOICES] =
	{"Normal behavior", "Always attack player", "Protect player", "Destroy enemy stellars"};

const int NUM_MISN_SHIPSTART_CHOICES = 7;

const std::string g_szMisnShipStartChoices[NUM_MISN_SHIPSTART_CHOICES] =
	{"On top of Nav Default 4", "On top of Nav Default 3", "On top of Nav Default 2",
	 "On top of Nav Default 1", "Appear randomly in system", "Jump in after short delay",
	 "Appear randomly, cloaked"};

const int NUM_MISN_FIELDS = 51;

const std::string g_szMisnFields[NUM_MISN_FIELDS] =
	{"Available Stellar", "Available Location", "Available Record", "Available Rating",
	 "Available Random", "Travel Stellar", "Return Stellar", "Cargo Type", "Cargo Amount",
	 "Cargo Pickup Mode", "Cargo Dropoff Mode", "Scan Mask", "Pay Value", "Ship Count",
	 "Ship System", "Ship Dude", "Ship Goal", "Ship Behavior", "Ship Name", "Ship Start",
	 "Completion Government", "Completion Reward", "Ship Subtitle", "Briefing Desc",
	 "Quick Briefing Desc", "Load Cargo Desc", "Dropoff Cargo Desc", "Completion Desc",
	 "Failing Desc", "Ship Done Desc", "Refusing Desc", "Time Limit", "Aux. Ship Count",
	 "Aux. Ship Dude", "Aux. Ship Syst", "Available Ship Type", "Available Bits",
	 "On Accept", "On Refuse", "On Success", "On Failure", "On Abort", "On Ship Done",
	 "Require Bits", "Date Increment", "Accept Button", "Refuse Button", "Display Weight",
	 "Can Abort", "Flags 1", "Flags 2"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CMisnResource : public CNovaResource
{
public:

	CMisnResource(void);
	~CMisnResource(void);

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

	static BOOL MisnDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	short m_iAvailableStellar;
	short m_iAvailableLocation;
	short m_iAvailableRecord;
	short m_iAvailableRating;
	short m_iAvailableRandom;

	short m_iTravelStellar;
	short m_iReturnStellar;

	short m_iCargoType;
	short m_iCargoAmount;
	short m_iCargoPickup;
	short m_iCargoDropoff;

	char  m_cScanMask[2];

	int   m_iPayValue;

	short m_iShipCount;
	short m_iShipSystem;
	short m_iShipDude;
	short m_iShipGoal;
	short m_iShipBehavior;
	short m_iShipName;
	short m_iShipStart;

	short m_iCompletionGovernment;
	short m_iCompletionReward;

	short m_iShipSubtitle;

	short m_iBriefingDesc;
	short m_iQuickBriefDesc;
	short m_iLoadCargoDesc;
	short m_iDropoffCargoDesc;
	short m_iCompletionDesc;
	short m_iFailDesc;
	short m_iShipDoneDesc;

	short m_iCanAbort;

	short m_iTimeLimit;

	short m_iAuxShipCount;
	short m_iAuxShipDude;
	short m_iAuxShipSyst;

	USHORT m_iFlags1;
	USHORT m_iFlags2;

	short m_iAvailableShipType;

	short m_iRefuseDesc;

	char  m_szAvailableBits[255];
	char  m_szOnAccept[255];
	char  m_szOnRefuse[255];
	char  m_szOnSuccess[255];
	char  m_szOnFailure[255];
	char  m_szOnAbort[255];
	char  m_szOnShipDone[255];

	char  m_cRequire[8];

	short m_iDateIncrement;

	char  m_szAcceptButton[32];
	char  m_szRefuseButton[33];

	short m_iDisplayWeight;

	CControl m_controls[NUM_MISN_CONTROLS];

	CBitFieldControl m_bitFieldControl;
};

#endif		// #ifndef CMISNRESOURCE_H_INCLUDED
