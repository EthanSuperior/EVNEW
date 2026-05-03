// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CIntfResource.h

#ifndef CINTFRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CINTFRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CIntfResource;

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

const int NUM_INTF_CONTROLS = 46;

const int NUM_INTF_FIELDS = 44;

const std::string g_szIntfFields[NUM_INTF_FIELDS] =
	{"Bright Text", "Dim Text", "Radar X1", "Radar Y1", "Radar X2",
	 "Radar Y2", "Bright Radar", "Dim Radar", "Shield X1", "Shield Y1",
	 "Shield X2", "Shield Y2", "Shield Color", "Armor X1", "Armor Y1",
	 "Armor X2", "Armor Y2", "Armor Color", "Fuel X1", "Fuel Y1",
	 "Fuel X2", "Fuel Y2", "Fuel Full", "Fuel Partial", "Navigation X1",
	 "Navigation Y1", "Navigation X2", "Navigation Y2", "Weapon X1",
	 "Weapon Y1", "Weapon X2", "Weapon Y2", "Target X1", "Target Y1",
	 "Target X2", "Target Y2", "Cargo X1", "Cargo Y1", "Cargo X2",
	 "Cargo Y2", "Status Font", "Status Font Size", "Subtitle font size",
	 "Background"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CIntfResource : public CNovaResource
{
public:

	CIntfResource(void);
	~CIntfResource(void);

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

	static BOOL IntfDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	UINT  m_iBrightText;
	UINT  m_iDimText;

	short m_iRadarX1;
	short m_iRadarY1;
	short m_iRadarX2;
	short m_iRadarY2;

	UINT  m_iBrightRadar;
	UINT  m_iDimRadar;

	short m_iShieldX1;
	short m_iShieldY1;
	short m_iShieldX2;
	short m_iShieldY2;

	UINT  m_iShieldColor;

	short m_iArmorX1;
	short m_iArmorY1;
	short m_iArmorX2;
	short m_iArmorY2;

	UINT  m_iArmorColor;

	short m_iFuelX1;
	short m_iFuelY1;
	short m_iFuelX2;
	short m_iFuelY2;

	UINT  m_iFuelFull;
	UINT  m_iFuelPartial;

	short m_iNavigationX1;
	short m_iNavigationY1;
	short m_iNavigationX2;
	short m_iNavigationY2;

	short m_iWeaponX1;
	short m_iWeaponY1;
	short m_iWeaponX2;
	short m_iWeaponY2;

	short m_iTargetX1;
	short m_iTargetY1;
	short m_iTargetX2;
	short m_iTargetY2;

	short m_iCargoX1;
	short m_iCargoY1;
	short m_iCargoX2;
	short m_iCargoY2;

	char  m_szStatusFont[64];
	short m_iStatusFontSize;
	short m_iSubtitleFontSize;

	short m_iBackground;

	CControl m_controls[NUM_INTF_CONTROLS];
};

#endif		// #ifndef CINTFRESOURCE_H_INCLUDED
