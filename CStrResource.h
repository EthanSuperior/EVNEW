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

constexpr int NUM_STR_CONTROLS = 3;

constexpr int NUM_STR_FIELDS = 1;

const std::string g_szStrFields[NUM_STR_FIELDS] =
	{"String"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CStrResource : public CNovaResource
{
public:

	CStrResource(void);
	~CStrResource(void) override;

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

	static BOOL StrDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	char m_szString[256];

	CControl m_controls[NUM_STR_CONTROLS];
};

#endif		// #ifndef CSTRRESOURCE_H_INCLUDED
