// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CBoomResource.h

#ifndef CBOOMRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CBOOMRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CBoomResource;

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

constexpr int NUM_BOOM_CONTROLS = 5;

constexpr int NUM_BOOM_FIELDS = 3;

const std::string g_szBoomFields[NUM_BOOM_FIELDS] =
	{"Frame Advance", "Sound Index", "Graphics Index"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CBoomResource : public CNovaResource
{
public:

	CBoomResource(void);
	~CBoomResource(void) override;

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

	static BOOL BoomDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	short m_iFrameAdvance;
	short m_iSoundIndex;
	short m_iGraphicsIndex;

	CControl m_controls[NUM_BOOM_CONTROLS];
};

#endif		// #ifndef CBOOMRESOURCE_H_INCLUDED
