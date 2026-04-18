// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CSpinResource.h

#ifndef CSPINRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CSPINRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CSpinResource;

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

const int NUM_SPIN_CONTROLS = 8;

const int NUM_SPIN_FIELDS = 6;

const std::string g_szSpinFields[NUM_SPIN_FIELDS] =
	{"Sprite", "Mask", "X Size", "Y Size", "X Tiles", "Y Tiles"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CSpinResource : public CNovaResource
{
public:

	CSpinResource(void);
	~CSpinResource(void);

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

	static BOOL SpinDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	short m_iSpritesID;
	short m_iMaskID;
	short m_iXSize;
	short m_iYSize;
	short m_iXTiles;
	short m_iYTiles;

	CControl m_controls[NUM_SPIN_CONTROLS];
};

#endif		// #ifndef CSPINRESOURCE_H_INCLUDED
