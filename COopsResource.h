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

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

constexpr int NUM_OOPS_CONTROLS = 8;

constexpr int NUM_OOPS_FIELDS = 6;

const std::string g_szOopsFields[NUM_OOPS_FIELDS] =
	{"Stellar", "Commodity", "Price Change", "Duration", "Random", "Active On"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class COopsResource : public CNovaResource
{
public:

	COopsResource(void);
	~COopsResource(void) override;

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
