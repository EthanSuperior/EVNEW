// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CDudeResource.h

#ifndef CDUDERESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CDUDERESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CDudeResource;

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

const int NUM_DUDE_CONTROLS = 49;

const int NUM_DUDE_FIELDS = 36;

const std::string g_szDudeFields[NUM_DUDE_FIELDS] =
	{"AI Type", "Government", "Ship 1", "Ship 2", "Ship 3", "Ship 4",
	 "Ship 5", "Ship 6", "Ship 7", "Ship 8", "Ship 9", "Ship 10",
	 "Ship 11", "Ship 12", "Ship 13", "Ship 14", "Ship 15", "Ship 16",
	 "Probability 1", "Probability 2", "Probability 3",
	 "Probability 4", "Probability 5", "Probability 6",
	 "Probability 7", "Probability 8", "Probability 9",
	 "Probability 10", "Probability 11", "Probability 12",
	 "Probability 13", "Probability 14", "Probability 15",
	 "Probability 16", "Flags", "Info Types"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CDudeResource : public CNovaResource
{
public:

	CDudeResource(void);
	~CDudeResource(void);

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

	static BOOL DudeDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	short m_iAIType;
	short m_iGovernment;

	USHORT m_iInfoTypes;
	USHORT m_iFlags;

	short m_iShipTypes[16];
	short m_iShipProbabilities[16];

	CControl m_controls[NUM_DUDE_CONTROLS];
};

#endif		// #ifndef CDUDERESOURCE_H_INCLUDED
