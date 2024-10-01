// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CRoidResource.h

#ifndef CROIDRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CROIDRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CRoidResource;

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

const int NUM_ROID_CONTROLS = 13;

const int NUM_ROID_FIELDS = 11;

const std::string g_szRoidFields[NUM_ROID_FIELDS] =
	{"Strength", "Spin Rate", "Yield Type", "Yield Amount", "Particle Count",
	 "Particle Color", "Fragment Type 1", "Fragment Type 2", "Fragment Count",
	 "Explosion Type", "Mass"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CRoidResource : public CNovaResource
{
public:

	CRoidResource(void);
	~CRoidResource(void);

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

	static BOOL RoidDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	short m_iStrength;
	short m_iSpinRate;

	short m_iYieldType;
	short m_iYieldAmount;

	short m_iParticleCount;
	UINT  m_iParticleColor;

	short m_iFragmentType1;
	short m_iFragmentType2;
	short m_iFragmentCount;

	short m_iExplosionType;

	short m_iMass;

	CControl m_controls[NUM_ROID_CONTROLS];
};

#endif		// #ifndef CROIDRESOURCE_H_INCLUDED
