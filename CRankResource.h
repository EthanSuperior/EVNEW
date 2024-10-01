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

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

constexpr int NUM_RANK_CONTROLS = 21;

constexpr int NUM_RANK_FIELDS = 9;

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
	~CRankResource(void) override;

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
