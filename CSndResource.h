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

constexpr int NUM_SND_CONTROLS = 2;

constexpr int NUM_SND_FIELDS = 1;

const std::string g_szSndFields[NUM_SND_FIELDS] =
	{"Filename"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CSndResource : public CNovaResource
{
public:

	CSndResource(void);
	~CSndResource(void) override;

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

	int SaveToTextEx(std::ostream & output, std::string & szFilePath, std::string & szFilename1, std::string & szFilename2, int iParam) override;
	int LoadFromTextEx(std::istream & input, std::string & szFilePath) override;

	int ShouldLoadDirect(void) override;
	int SaveDirect(std::ostream & output) override;
	int LoadDirect(std::istream & input, int iSize) override;

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
