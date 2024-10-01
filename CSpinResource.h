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

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

constexpr int NUM_SPIN_CONTROLS = 8;

constexpr int NUM_SPIN_FIELDS = 6;

const std::string g_szSpinFields[NUM_SPIN_FIELDS] =
	{"Sprite", "Mask", "X Size", "Y Size", "X Tiles", "Y Tiles"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CSpinResource : public CNovaResource
{
public:

	CSpinResource(void);
	~CSpinResource(void) override;

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
