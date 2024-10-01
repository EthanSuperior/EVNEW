// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CStrlResource.h

#ifndef CSTRLRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CSTRLRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CStrlResource;

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>

#include <vector>
#include <string>

#include "CControl.h"
#include "CNovaResource.h"

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

constexpr int NUM_STRL_CONTROLS = 2;

constexpr int NUM_STRL_FIELDS = 2;

const std::string g_szStrlFields[NUM_STRL_FIELDS] =
	{"Number of strings", "Strings..."};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CStrlResource : public CNovaResource
{
public:

	CStrlResource(void);
	~CStrlResource(void) override;

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

	int EditCut(void);
	int EditCopy(void);
	int EditPaste(void);
	int EditDelete(void);

	static BOOL StrlDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static BOOL StrlStrDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int AddString(void);
	int EditString(void);
	int MoveUp(void);
	int MoveDown(void);

	std::vector<std::string> m_vStrings;

	int m_iCurString;

	int m_iWasSaved;

	CWindow m_wndEditString;

	CControl m_controls[NUM_STRL_CONTROLS];
};

#endif		// #ifndef CSTRLRESOURCE_H_INCLUDED
