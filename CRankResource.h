// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CRankResource.h

#ifndef CRANKRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CRANKRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CRankResource;

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>

#include <string>

#include "CControl.h"
#include "CBitFieldControl.h"
#include "CNovaResource.h"
#include "Utils.h"

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

const int NUM_RANK_CONTROLS = 21;

const int NUM_RANK_FIELDS = 9;

const std::string g_szRankFields[NUM_RANK_FIELDS] =
	{"Weight", "Government", "Salary", "Salary Cap", "Price Mod",
	 "Conversation Name", "Short Name", "Contribute Bits", "Flags"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CRankResource : public CNovaResource
{
public:

	CRankResource(void);
	~CRankResource(void);

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

	static BOOL RankDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	short m_iWeight;
	short m_iGovernment;

	char  m_cContribute[8];

	int   m_iSalary;
	int   m_iSalaryCap;

	USHORT m_iFlags;

	short m_iPriceMod;

	char  m_szConvName[64];
	char  m_szShortName[64];

	CControl m_controls[NUM_RANK_CONTROLS];

	CBitFieldControl m_bitFieldControl;
};

#endif		// #ifndef CRANKRESOURCE_H_INCLUDED
