// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CGovtResource.h

#ifndef CGOVTRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CGOVTRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CGovtResource;

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

const int NUM_GOVT_CONTROLS = 62;

const int NUM_GOVT_FIELDS = 38;

const std::string g_szGovtFields[NUM_GOVT_FIELDS] =
	{"Voice Type", "Scan Fine", "Crime Tolerance", "Smuggling Penalty",
	 "Diabling Penalty", "Boarding Penalty", "Killing Penalty",
	 "Shooting Penalty", "Initial Record", "Max Odds", "Class 1",
	 "Class 2", "Class 3", "Class 4", "Ally 1", "Ally 2", "Ally 3",
	 "Ally 4", "Enemy 1", "Enemy 2", "Enemy 3", "Enemy 4", "Interface",
	 "News Picture", "Skill Multiplier", "Scan Mask", "Require Bits",
	 "Inherent Jamming Type 1", "Inherent Jamming Type 2",
	 "Inherent Jamming Type 3", "Inherent Jamming Type 4", "Medium Name",
	 "Color", "Ship Color", "Communication Name", "Target Name", "Flags 1",
	 "Flags 2"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CGovtResource : public CNovaResource
{
public:

	CGovtResource(void);
	~CGovtResource(void);

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

	static BOOL GovtDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	short m_iVoiceType;

	short m_iCrimeTolerance;

	USHORT m_iFlags1;
	USHORT m_iFlags2;

	short m_iScanFine;
	short m_iSmugglingPenalty;
	short m_iDisablingPenalty;
	short m_iBoardingPenalty;
	short m_iKillingPenalty;
	short m_iShootingPenalty;
	short m_iInitialRecord;

	short m_iMaxOdds;

	short m_iClasses[4];
	short m_iAllies[4];
	short m_iEnemies[4];

	short m_iInterface;
	short m_iNewsPicture;

	short m_iSkillMultiplier;

	char  m_cScanMask[2];

	char  m_cRequire[8];

	short m_iInherentJamming[4];

	char  m_szMediumName[64];

	UINT  m_iColor;
	UINT  m_iShipColor;

	char  m_szCommName[16];
	char  m_szTargetName[16];

	CControl m_controls[NUM_GOVT_CONTROLS];

	CBitFieldControl m_bitFieldControl;
};

#endif		// #ifndef CGOVTRESOURCE_H_INCLUDED
