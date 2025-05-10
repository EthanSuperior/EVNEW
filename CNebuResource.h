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
#include "Utils.h"

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

const int NUM_NEBU_CONTROLS = 8;

const int NUM_NEBU_FIELDS = 6;

const std::string g_szNebuFields[NUM_NEBU_FIELDS] =
	{"X Position", "Y Position", "X Size", "Y Size", "Active On", "On Explore"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CNebuResource : public CNovaResource
{
public:

	CNebuResource(void);
	~CNebuResource(void);

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

	static BOOL NebuDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	void RegisterNCB() override;

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
