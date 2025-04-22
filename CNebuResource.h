// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CNebuResource.h

#ifndef CNEBURESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CNEBURESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CNebuResource;

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

constexpr int NUM_NEBU_CONTROLS = 8;

constexpr int NUM_NEBU_FIELDS = 6;

const std::string g_szNebuFields[NUM_NEBU_FIELDS] =
	{"X Position", "Y Position", "X Size", "Y Size", "Active On", "On Explore"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CNebuResource : public CNovaResource
{
public:

	CNebuResource(void);
	~CNebuResource(void) override;

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

	static BOOL NebuDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	short m_iXPosition;
	short m_iYPosition;

	short m_iXSize;
	short m_iYSize;

	char  m_szActiveOn[255];
	char  m_szOnExplore[255];

	CControl m_controls[NUM_NEBU_CONTROLS];
};

#endif		// #ifndef CNEBURESOURCE_H_INCLUDED
