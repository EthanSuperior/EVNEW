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

const int NUM_BOOM_CONTROLS = 5;

const int NUM_BOOM_FIELDS = 3;

const std::string g_szBoomFields[NUM_BOOM_FIELDS] =
	{"Frame Advance", "Sound Index", "Graphics Index"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CBoomResource : public CNovaResource
{
public:

	CBoomResource(void);
	~CBoomResource(void);

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

	static BOOL BoomDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	short m_iFrameAdvance;
	short m_iSoundIndex;
	short m_iGraphicsIndex;

	CControl m_controls[NUM_BOOM_CONTROLS];
};

#endif		// #ifndef CBOOMRESOURCE_H_INCLUDED
