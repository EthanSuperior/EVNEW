// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CSndResource.h

#ifndef CSNDRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CSNDRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CSndResource;

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>

#include <vector>
#include <string>

namespace qt
{
#include <Sound.h>
}

#include "CControl.h"
#include "CNovaResource.h"

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

const int NUM_SND_CONTROLS = 2;

const int NUM_SND_FIELDS = 1;

const std::string g_szSndFields[NUM_SND_FIELDS] =
	{"Filename"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CSndResource : public CNovaResource
{
public:

	CSndResource(void);
	~CSndResource(void);

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

	int SaveToTextEx(std::ostream & output, std::string & szFilePath, std::string & szFilename1, std::string & szFilename2, int iParam);
	int LoadFromTextEx(std::istream & input, std::string & szFilePath);

	int ShouldLoadDirect(void);
	int SaveDirect(std::ostream & output);
	int LoadDirect(std::istream & input, int iSize);

	static BOOL SndDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int FileImport(const char *szFilename, int iShowErrorMessages);
	int FileExport(const char *szFilename, int iShowErrorMessages);

	int SwapEndians(void);

	int PlaySound(void);

	std::vector<UCHAR> m_vData;
	std::vector<UCHAR> m_vData2;

	int m_iFormat;
	int m_iFormatCopy;

	int m_iIsDirty;

	qt::SndListResource  *m_pSndHeader;
	qt::Snd2ListResource *m_pSnd2Header;
	qt::CmpSoundHeader   *m_pSndInfo;

	UCHAR *m_pSndData;

	CControl m_controls[NUM_SND_CONTROLS];
};

#endif		// #ifndef CSNDRESOURCE_H_INCLUDED
