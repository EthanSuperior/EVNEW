// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CDescResource.h

#ifndef CDESCRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CDESCRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CDescResource;

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

const int NUM_DESC_CONTROLS = 8;

const int NUM_DESC_FIELDS = 4;

const std::string g_szDescFields[NUM_DESC_FIELDS] =
	{"Text", "Graphics", "Movie File", "Flags"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CDescResource : public CNovaResource
{
public:

	CDescResource(void);
	~CDescResource(void);

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

	static BOOL DescDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	int FixNewlines(char cReplace, int iAdd);

	std::string m_szDescription;

	short m_iGraphics;

	char m_szMovieFile[32];

	USHORT m_iFlags;

	CControl m_controls[NUM_DESC_CONTROLS];
};

#endif		// #ifndef CDESCRESOURCE_H_INCLUDED
