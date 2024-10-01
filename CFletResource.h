// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CFletResource.h

#ifndef CFLETRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CFLETRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CFletResource;

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

const int NUM_FLET_CONTROLS = 20;

const int NUM_FLET_FIELDS = 18;

const std::string g_szFletFields[NUM_FLET_FIELDS] =
	{"Lead Ship Type", "Escort Type 1", "Escort Type 2", "Escort Type 3",
	 "Escort Type 4", "Min Escort 1", "Min Escort 2", "Min Escort 3",
	 "Min Escort 4", "Max Escort 1", "Max Escort 2", "Max Escort 3",
	 "Max Escort 4", "Government", "System", "Appear On", "Hail Quote",
	 "Flags"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CFletResource : public CNovaResource
{
public:

	CFletResource(void);
	~CFletResource(void);

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

	static BOOL FletDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	short m_iLeadShipType;

	short m_iEscortTypes[4];
	short m_iMinEscorts[4];
	short m_iMaxEscorts[4];

	short m_iGovernment;

	short m_iSystem;

	char m_szAppearOn[256];

	short m_iQuote;

	USHORT m_iFlags;

	CControl m_controls[NUM_FLET_CONTROLS];
};

#endif		// #ifndef CFLETRESOURCE_H_INCLUDED
