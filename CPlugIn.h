// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CPlugIn.h

#pragma once

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CPlugIn;

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#pragma warning(disable : 4786) // 'identifier' was truncated to '255' characters in the debug information

#include <vector>

#include "CWindow.h"
#include "CErrorLog.h"

#include "CNovaResource.h"

#include "CControl.h"

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CPlugIn
{
public:
	CPlugIn(void);
	~CPlugIn(void);

	int Clear(void);
	int ClearFilename(void);

	char *GetFilename(void);
	char *GetFilenameNoPath(void);

	int SetFilename(const char *szFilename);

	CNovaResource *FindById(int rezType, short iID);

	int SetOptions(int iShowErrorMessages, int iShowProgressBar);
	int SetCicnSaveOptions(int iSave, char *szSubdirectory, char *szFilenamePrefix, char *szMaskSubdirectory, char *szMaskFilenamePrefix);
	int SetPictSaveOptions(int iSave, char *szSubdirectory, char *szFilenamePrefix, int iImageFileType);
	int SetRle8SaveOptions(int iSave, char *szSubdirectory, char *szFilenamePrefix, char *szMaskSubdirectory, char *szMaskFilenamePrefix, int iImageFileType, int iMaskFileType, int iFramesPerRow);
	int SetRleDSaveOptions(int iSave, char *szSubdirectory, char *szFilenamePrefix, char *szMaskSubdirectory, char *szMaskFilenamePrefix, int iImageFileType, int iMaskFileType, int iFramesPerRow);
	int SetSndSaveOptions(int iSave, char *szSubdirectory, char *szFilenamePrefix);

	int GetCurFileOffset(void);

	int Load(char *szFilename, CWindow *pWndParent);
	int Save(CWindow *pWndParent);

	CNovaResource *AllocateResource(int iType);

	std::vector<std::vector<CNovaResource *>> m_vResources;

	int m_iIsDirty = 0;

private:
	std::string GenerateFilename(char *szSubdirectory, char *szFilenamePrefix, const char *szExtension, short iID);

	char m_szFilename[MAX_PATH];
	char m_szFilePath[MAX_PATH];
	char m_szFilenameNoPath[MAX_PATH];

	int m_iSaveAsText;

	int m_iFileOffset;

	CWindow m_wndLoading;

	int m_iShowErrorMessages;
	int m_iShowProgressBar;

	int m_iCicnSave;
	char m_szCicnSubdirectory[256];
	char m_szCicnFilenamePrefix[256];
	char m_szCicnMaskSubdirectory[256];
	char m_szCicnMaskFilenamePrefix[256];

	int m_iPictSave;
	char m_szPictSubdirectory[256];
	char m_szPictFilenamePrefix[256];
	int m_iPictImageFileType;

	int m_iRle8Save;
	char m_szRle8Subdirectory[256];
	char m_szRle8FilenamePrefix[256];
	char m_szRle8MaskSubdirectory[256];
	char m_szRle8MaskFilenamePrefix[256];
	int m_iRle8ImageFileType;
	int m_iRle8MaskFileType;
	int m_iRle8FramesPerRow;

	int m_iRleDSave;
	char m_szRleDSubdirectory[256];
	char m_szRleDFilenamePrefix[256];
	char m_szRleDMaskSubdirectory[256];
	char m_szRleDMaskFilenamePrefix[256];
	int m_iRleDImageFileType;
	int m_iRleDMaskFileType;
	int m_iRleDFramesPerRow;

	int m_iSndSave;
	char m_szSndSubdirectory[256];
	char m_szSndFilenamePrefix[256];
};
