// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CColrResource.h

#ifndef CCOLRRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CCOLRRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CColrResource;

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

const int NUM_COLR_CONTROLS = 47;

const int NUM_COLR_FIELDS = 45;

const std::string g_szColrFields[NUM_COLR_FIELDS] =
	{"Button Up", "Button Down", "Button Grey", "Menu Font",
	 "Menu Font Size", "Menu Color 1", "Menu Color 2",
	 "Grid Bright", "Grid Dim", "Progress Bar X1",
	 "Progress Bar Y1", "Progress Bar X2", "Progress Bar Y2",
	 "Progress Bright", "Progress Dim", "Progress Outline",
	 "Button 1 X", "Button 1 Y", "Button 2 X", "Button 2 Y",
	 "Button 3 X", "Button 3 Y", "Button 4 X", "Button 4 Y",
	 "Button 5 X", "Button 5 Y", "Button 6 X", "Button 6 Y",
	 "Floating Map", "List Text", "List Background",
	 "List Highlight", "Escort Highlight", "Button Font",
	 "Button Font Size", "Logo X", "Logo Y", "Rollover X",
	 "Rollover Y", "Slide 1 X", "Slide 1 Y", "Slide 2 X",
	 "Slide 2 Y", "Slide 3 X", "Slide 3 Y"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CColrResource : public CNovaResource
{
public:

	CColrResource(void);
	~CColrResource(void);

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

	static BOOL ColrDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	UINT  m_iButtonUp;
	UINT  m_iButtonDown;
	UINT  m_iButtonGrey;

	char  m_szMenuFont[64];
	short m_iMenuFontSize;
	UINT  m_iMenuColor1;
	UINT  m_iMenuColor2;

	UINT  m_iGridDim;
	UINT  m_iGridBright;

	short m_iProgressBarX1;
	short m_iProgressBarY1;
	short m_iProgressBarX2;
	short m_iProgressBarY2;
	UINT  m_iProgressBright;
	UINT  m_iProgressDim;
	UINT  m_iProgressOutline;

	short m_iButton1X;
	short m_iButton1Y;
	short m_iButton2X;
	short m_iButton2Y;
	short m_iButton3X;
	short m_iButton3Y;
	short m_iButton4X;
	short m_iButton4Y;
	short m_iButton5X;
	short m_iButton5Y;
	short m_iButton6X;
	short m_iButton6Y;

	UINT  m_iFloatingMap;
	UINT  m_iListText;
	UINT  m_iListBackground;
	UINT  m_iListHighlight;
	UINT  m_iEscortHighlight;

	char  m_szButtonFont[64];
	short m_iButtonFontSize;

	short m_iLogoX;
	short m_iLogoY;
	short m_iRolloverX;
	short m_iRolloverY;
	short m_iSlide1X;
	short m_iSlide1Y;
	short m_iSlide2X;
	short m_iSlide2Y;
	short m_iSlide3X;
	short m_iSlide3Y;

	CControl m_controls[NUM_COLR_CONTROLS];
};

#endif		// #ifndef CCOLRRESOURCE_H_INCLUDED
