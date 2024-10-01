// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CControl.h

#ifndef CCONTROL_H_INCLUDED		// Prevent multiple inclusions
#define CCONTROL_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CControl;

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>

#include <string>

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

constexpr int CCONTROL_TYPE_NULL     = 0;
constexpr int CCONTROL_TYPE_INT      = 1;
constexpr int CCONTROL_TYPE_HEXINT16 = 2;
constexpr int CCONTROL_TYPE_HEXINT32 = 3;
constexpr int CCONTROL_TYPE_HEXINT64 = 4;
constexpr int CCONTROL_TYPE_STR8     = 5;
constexpr int CCONTROL_TYPE_STR16    = 6;
constexpr int CCONTROL_TYPE_STR32    = 7;
constexpr int CCONTROL_TYPE_STR33    = 8;
constexpr int CCONTROL_TYPE_STR64    = 9;
constexpr int CCONTROL_TYPE_STR65    = 10;
constexpr int CCONTROL_TYPE_STR128   = 11;
constexpr int CCONTROL_TYPE_STR255   = 12;
constexpr int CCONTROL_TYPE_STR256   = 13;
constexpr int CCONTROL_TYPE_STR1024  = 14;
constexpr int CCONTROL_TYPE_STRARB   = 15;
constexpr int CCONTROL_TYPE_CHECK    = 16;
constexpr int CCONTROL_TYPE_COLOR    = 17;
constexpr int CCONTROL_TYPE_COMBOBOX = 18;

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CControl
{
public:
	CControl(void);
	~CControl(void);

	int Create(HWND hwndDialog, int iControlID, int iType, int iHelpStringID);
	int Destroy(void);

	int ProcessMessage(int iNotifyCode);

	int GetControlID(void);
	int GetType(void);

	HWND GetHWND(void);

	int GetInt(void);
	const char * GetString(void);

	int IsValid(void);

	int SetMinValue(int iMinValue);
	int SetMaxValue(int iMaxValue);

	int GetMinValue(void);
	int GetMaxValue(void);

	int SetInt(int iValue);
	int SetString(const char *szValue);

	int SetComboStrings(int iNumStrings, const std::string *pStrings);

private:
	int CreateBitmap(int iColor);

	HWND m_hwndDialog;
	HWND m_hwndControl;

	int m_iControlID;

	int m_iType;

	int m_iHelpStringID;

	int m_iMinValue;
	int m_iMaxValue;

	int m_iIntValue;

	std::string m_szStringValue;

	HBITMAP m_hbmColor;
};

#endif		// #ifndef CCONTROL_H_INCLUDED
