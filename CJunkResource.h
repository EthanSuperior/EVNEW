// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CJunkResource.h

#ifndef CJUNKRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CJUNKRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CJunkResource;

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

constexpr int NUM_JUNK_CONTROLS = 26;

constexpr int NUM_JUNK_FIELDS = 23;

const std::string g_szJunkFields[NUM_JUNK_FIELDS] =
	{"Sold At 1", "Sold At 2", "Sold At 3", "Sold At 4", "Sold At 5",
	 "Sold At 6", "Sold At 7", "Sold At 8", "Bought At 1", "Bought At 2",
	 "Bought At 3", "Bought At 4", "Bought At 5", "Bought At 6",
	 "Bought At 7", "Bought At 8", "Base Price", "Scan Mask",
	 "Lowercase Name", "Abbreviation", "Buy On", "Sell On", "Flags"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CJunkResource : public CNovaResource
{
public:

	CJunkResource(void);
	~CJunkResource(void) override;

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

	static BOOL JunkDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	short m_iSoldAt[8];
	short m_iBoughtAt[8];

	short m_iBasePrice;

	USHORT m_iFlags;

	char  m_cScanMask[2];

	char  m_szLowerCaseName[64];
	char  m_szAbbreviation[64];

	char  m_szBuyOn[255];
	char  m_szSellOn[255];

	CControl m_controls[NUM_JUNK_CONTROLS];

	CBitFieldControl m_bitFieldControl;
};

#endif		// #ifndef CJUNKRESOURCE_H_INCLUDED
