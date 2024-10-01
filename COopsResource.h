// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File COopsResource.h

#ifndef COOPSRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define COOPSRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class COopsResource;

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

const int NUM_OOPS_CONTROLS = 8;

const int NUM_OOPS_FIELDS = 6;

const std::string g_szOopsFields[NUM_OOPS_FIELDS] =
	{"Stellar", "Commodity", "Price Change", "Duration", "Random", "Active On"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class COopsResource : public CNovaResource
{
public:

	COopsResource(void);
	~COopsResource(void);

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

	static BOOL OopsDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	short m_iStellar;
	short m_iCommodity;
	short m_iPriceDelta;
	short m_iDuration;
	short m_iRandom;

	char  m_szActiveOn[256];

	CControl m_controls[NUM_OOPS_CONTROLS];
};

#endif		// #ifndef COOPSRESOURCE_H_INCLUDED
