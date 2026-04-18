// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CStrResource.h

#ifndef CSTRRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CSTRRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CStrResource;

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>

#include <string>

#include <string.h>

#include "CControl.h"
#include "CNovaResource.h"
#include "Utils.h"

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

const int NUM_STR_CONTROLS = 3;

const int NUM_STR_FIELDS = 1;

const std::string g_szStrFields[NUM_STR_FIELDS] =
	{"String"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CStrResource : public CNovaResource
{
public:

	CStrResource(void);
	~CStrResource(void);

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

	static BOOL StrDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	char m_szString[256];

	CControl m_controls[NUM_STR_CONTROLS];
};

#endif		// #ifndef CSTRRESOURCE_H_INCLUDED
