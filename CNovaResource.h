// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CNovaResource.h

#pragma once

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CNovaResource;

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <windows.h>

#include "CWindow.h"
#include "CControl.h"

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

const int CNR_TYPE_NONE = -1;

const int CNR_TYPE_BOOM =  0;
const int CNR_TYPE_CHAR =  1;
const int CNR_TYPE_CICN =  2;
const int CNR_TYPE_COLR =  3;
const int CNR_TYPE_CRON =  4;
const int CNR_TYPE_DESC =  5;
const int CNR_TYPE_DUDE =  6;
const int CNR_TYPE_FLET =  7;
const int CNR_TYPE_GOVT =  8;
const int CNR_TYPE_INTF =  9;
const int CNR_TYPE_JUNK = 10;
const int CNR_TYPE_MISN = 11;
const int CNR_TYPE_NEBU = 12;
const int CNR_TYPE_OOPS = 13;
const int CNR_TYPE_OUTF = 14;
const int CNR_TYPE_PERS = 15;
const int CNR_TYPE_PICT = 16;
const int CNR_TYPE_RANK = 17;
const int CNR_TYPE_RLE8 = 18;
const int CNR_TYPE_RLED = 19;
const int CNR_TYPE_ROID = 20;
const int CNR_TYPE_SHAN = 21;
const int CNR_TYPE_SHIP = 22;
const int CNR_TYPE_SND  = 23;
const int CNR_TYPE_SPIN = 24;
const int CNR_TYPE_SPOB = 25;
const int CNR_TYPE_STR  = 26;
const int CNR_TYPE_STRL = 27;
const int CNR_TYPE_SYST = 28;
const int CNR_TYPE_WEAP = 29;
const int CNR_TYPE_UNK  = 30;
const int CNR_MAX_VALID_IDS[] = { 191, 32767, 32767, 32767,   639, 32767,   639,   383,   383, 32767,
								  255,  1127,   159,   383,   639,  1151, 32767,   255, 32767, 32767,
								  143,   895,   895, 32767, 32767,  2175, 32767, 32767,  2175,   383 };
const int NUM_RESOURCE_TYPES = 30;

const std::string g_szResourceTypes[] = {"boom", "char", "cicn", "colr", "cron", "desc", "dude", "flet", "govt", "intf",
										 "junk", "misn", "nebu", "oops", "outf", "pers", "pict", "rank", "rle8", "rleD",
										 "roid", "shan", "ship", "snd",  "spin", "spob", "str",  "str#", "syst", "weap"};

const std::string g_szMacResourceTypes[] = {"bššm", "chŠr", "cicn", "cšlr", "cršn", "d‘sc", "dŸde", "fl‘t", "gšvt", "•ntf",
											"jŸnk", "m•sn", "n‘bu", "šops", "oŸtf", "p‘rs", "PICT", "rŠnk", "rl‘8", "rl‘D",
											"ršid", "shŠn", "sh•p", "snd ", "sp•n", "spšb", "STR ", "STR#", "sØst", "w‘ap"};

const int g_iResourceCanLoadSaveText[] = {1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
										  1, 1, 1, 1, 1, 1, 0, 1, 0, 0,
										  1, 1, 1, 0, 1, 1, 1, 1, 1, 1};

typedef BOOL (*DLGPROCNOCALLBACK)(HWND, UINT, WPARAM, LPARAM);

const int NUM_AITYPE_CHOICES = 4;

const std::string g_szAITypeChoices[NUM_AITYPE_CHOICES] = {"Wimpy trader", "Brave trader", "Warship", "Interceptor"}; 

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CNovaResource
{
public:

	CNovaResource(void);
	virtual ~CNovaResource(void);

	virtual int GetType(void) = 0;
	virtual int GetSize(void) = 0;

	virtual int GetDialogID(void) = 0;
	virtual DLGPROCNOCALLBACK GetDialogProc(void) = 0;

	virtual int GetNumFields(void);
	virtual const std::string * GetFieldNames(void);

	int SetID(short iID);
	short GetID(void);

	int SetName(const char *szName);
	char *GetName(void);

	int SetIsNew(int iIsNew);
	int IsNew(void);

	int SetWindow(CWindow *pWindow);
	CWindow *GetWindow(void);

	virtual int ShouldLoadDirect(void);
	virtual int SaveDirect(std::ostream & output);
	virtual int LoadDirect(std::istream & input, int iSize);

	virtual int SaveToText(std::ostream & output);
	virtual int SaveToTextEx(std::ostream & output, std::string & szFilePath, std::string & szFilename1, std::string & szFilename2, int iParam);
	virtual int LoadFromText(std::istream & input);
	virtual int LoadFromTextEx(std::istream & input, std::string & szFilePath);

	virtual int Initialize(HWND hwnd) = 0;

	virtual int CloseAndSave(void) = 0;
	virtual int CloseAndDontSave(void) = 0;

	virtual int Save(char *pOutput) = 0;
	virtual int Load(char* pInput, int iSize) = 0;
	virtual void RegisterNCB() {};

	static void SetIfDefaultInt(CControl* m_controls, short controlID, short oldV, short newV, short offset = 0);
	static void SetIfDefaultStr(CControl* m_controls, short controlID, short oldBit, short newBit);

	friend struct SNovaResourceCompare;

protected:

	short m_iID;

	char m_szName[256];

	int m_iIsNew;

	CWindow *m_pWindow;
};

struct SNovaResourceCompare
{
public:
	SNovaResourceCompare(void) = default;
	bool operator () (const CNovaResource *pResource1, const CNovaResource *pResource2)
	{
		return (pResource1->m_iID < pResource2->m_iID);
	}
};