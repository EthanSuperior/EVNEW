// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CNovaResource.h

#ifndef CNOVARESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CNOVARESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CNovaResource;

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <string>
#include <windows.h>

#include "CWindow.h"

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

constexpr int CNR_TYPE_NONE = -1;

constexpr int CNR_TYPE_BOOM =  0;
constexpr int CNR_TYPE_CHAR =  1;
constexpr int CNR_TYPE_CICN =  2;
constexpr int CNR_TYPE_COLR =  3;
constexpr int CNR_TYPE_CRON =  4;
constexpr int CNR_TYPE_DESC =  5;
constexpr int CNR_TYPE_DUDE =  6;
constexpr int CNR_TYPE_FLET =  7;
constexpr int CNR_TYPE_GOVT =  8;
constexpr int CNR_TYPE_INTF =  9;
constexpr int CNR_TYPE_JUNK = 10;
constexpr int CNR_TYPE_MISN = 11;
constexpr int CNR_TYPE_NEBU = 12;
constexpr int CNR_TYPE_OOPS = 13;
constexpr int CNR_TYPE_OUTF = 14;
constexpr int CNR_TYPE_PERS = 15;
constexpr int CNR_TYPE_PICT = 16;
constexpr int CNR_TYPE_RANK = 17;
constexpr int CNR_TYPE_RLE8 = 18;
constexpr int CNR_TYPE_RLED = 19;
constexpr int CNR_TYPE_ROID = 20;
constexpr int CNR_TYPE_SHAN = 21;
constexpr int CNR_TYPE_SHIP = 22;
constexpr int CNR_TYPE_SND  = 23;
constexpr int CNR_TYPE_SPIN = 24;
constexpr int CNR_TYPE_SPOB = 25;
constexpr int CNR_TYPE_STR  = 26;
constexpr int CNR_TYPE_STRL = 27;
constexpr int CNR_TYPE_SYST = 28;
constexpr int CNR_TYPE_WEAP = 29;
constexpr int CNR_TYPE_UNK  = 30;

constexpr int NUM_RESOURCE_TYPES = 30;

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

constexpr int NUM_AITYPE_CHOICES = 4;

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
	virtual int Load(char *pInput, int iSize) = 0;

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
	SNovaResourceCompare(void);

	bool operator () (const CNovaResource *pResource1, const CNovaResource *pResource2);
};

#endif		// #ifndef CNOVARESOURCE_H_INCLUDED
