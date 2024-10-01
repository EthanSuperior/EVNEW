// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CCharResource.h

#ifndef CCHARRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CCHARRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CCharResource;

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

const int NUM_CHAR_CONTROLS = 33;

const int NUM_CHAR_FIELDS = 31;

const std::string g_szCharFields[NUM_CHAR_FIELDS] =
	{"Cash", "Ship Type", "System 1", "System 2", "System 3", "System 4",
	 "Government 1", "Status 1", "Government 2", "Status 2",
	 "Government 3", "Status 3", "Government 4", "Status 4",
	 "Combat Rating", "Intro Pict 1", "Intro Pict 2", "Intro Pict 3",
	 "Intro Pict 4", "Pict Delay 1", "Pict Delay 2", "Pict Delay 3",
	 "Pict Delay 4", "Intro Text", "On Start", "Start Day",
	 "Start Month", "Start Year", "Date Prefix", "Date Suffix", "Flags"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CCharResource : public CNovaResource
{
public:

	CCharResource(void);
	~CCharResource(void);

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

	static BOOL CharDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	int   m_iCash;
	short m_iShipType;

	short m_iSystem1;
	short m_iSystem2;
	short m_iSystem3;
	short m_iSystem4;

	short m_iGovernment1;
	short m_iStatus1;
	short m_iGovernment2;
	short m_iStatus2;
	short m_iGovernment3;
	short m_iStatus3;
	short m_iGovernment4;
	short m_iStatus4;

	short m_iCombatRating;

	short m_iIntroPict1;
	short m_iIntroPict2;
	short m_iIntroPict3;
	short m_iIntroPict4;
	short m_iPictDelay1;
	short m_iPictDelay2;
	short m_iPictDelay3;
	short m_iPictDelay4;

	short m_iIntroText;

	char m_szOnStart[256];

	USHORT m_iFlags;

	short m_iStartDay;
	short m_iStartMonth;
	short m_iStartYear;

	char m_szDatePrefix[16];
	char m_szDateSuffix[16];

	CControl m_controls[NUM_CHAR_CONTROLS];
};

#endif		// #ifndef CCHARRESOURCE_H_INCLUDED
