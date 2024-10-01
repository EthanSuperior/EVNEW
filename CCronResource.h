// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CCronResource.h

#ifndef CCRONRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CCRONRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CCronResource;

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

constexpr int NUM_CRON_CONTROLS = 28;

constexpr int NUM_CRON_FIELDS = 25;

const std::string g_szCronFields[NUM_CRON_FIELDS] =
	{"First Day", "First Month", "First Year", "Last Day", "Last Month",
	 "Last Year", "Random", "Duration", "Pre Holdoff", "Post Holdoff",
	 "Enable On", "On Start", "On End", "Contribute", "Require",
	 "Government 1", "Government News 1", "Government 2",
	 "Government News 2", "Government 3", "Government News 3",
	 "Government 4", "Government News 4", "Independent News",
	 "Flags"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CCronResource : public CNovaResource
{
public:

	CCronResource(void);
	~CCronResource(void) override;

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

	static BOOL CronDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	short m_iFirstDay;
	short m_iFirstMonth;
	short m_iFirstYear;

	short m_iLastDay;
	short m_iLastMonth;
	short m_iLastYear;

	short m_iRandom;
	short m_iDuration;

	short m_iPreHoldoff;
	short m_iPostHoldoff;

	USHORT m_iFlags;

	char  m_szEnableOn[255];
	char  m_szOnStart[255];
	char  m_szOnEnd[256];

	char m_cContribute[8];
	char m_cRequire[8];

	short m_iGovernment1;
	short m_iGovernmentNews1;
	short m_iGovernment2;
	short m_iGovernmentNews2;
	short m_iGovernment3;
	short m_iGovernmentNews3;
	short m_iGovernment4;
	short m_iGovernmentNews4;

	short m_iIndependentNews;

	CControl m_controls[NUM_CRON_CONTROLS];

	CBitFieldControl m_bitFieldControl;
};

#endif		// #ifndef CCRONRESOURCE_H_INCLUDED
