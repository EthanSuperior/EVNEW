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
#include "Utils.h"

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

const int NUM_JUNK_CONTROLS = 26;

const int NUM_JUNK_FIELDS = 23;

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
	~CJunkResource(void);

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
