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

constexpr int NUM_DESC_CONTROLS = 8;

constexpr int NUM_DESC_FIELDS = 4;

const std::string g_szDescFields[NUM_DESC_FIELDS] =
	{"Text", "Graphics", "Movie File", "Flags"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CDescResource : public CNovaResource
{
public:

	CDescResource(void);
	~CDescResource(void) override;

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
