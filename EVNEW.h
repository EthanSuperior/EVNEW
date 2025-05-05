// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File EVNEW.h
#pragma once

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CEditor;

////////////////////////////////////////////////////////////////
//////////////////////////  INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#pragma warning (disable: 4786)		// 'identifier' was truncated to '255' characters in the debug information

#include <vector>
#include <string>
#include <commdlg.h>

#include "CWindow.h"
#include "CErrorLog.h"

#include "CNovaResource.h"

#include "CPlugIn.h"

#include "CControl.h"

#include "NovaLib.h"

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

const int NUM_PREFERENCE_CONTROLS = 3;
const int NUM_TEMPLATE_CONTROLS = 3;

const int NUM_CICN_EXPORT_FORMAT_CONTROLS = 4;
const int NUM_PICT_EXPORT_FORMAT_CONTROLS = 3;
const int NUM_RLE_EXPORT2_FORMAT_CONTROLS = 7;
const int NUM_SND_EXPORT_FORMAT_CONTROLS  = 2;

const int NUM_IMAGE_TYPE_CHOICES = 6;

const std::string g_szImageTypeChoices[NUM_IMAGE_TYPE_CHOICES] =
	{"Bitmap (*.bmp)", "Portable Network Graphics (*.png)", "JPEG (*.jpg)", "Mac PICT (*.pic)",
	 "TIFF (*.tiff)", "Targa (*.tga)"};

const std::string g_szImageTypeExtensions[NUM_IMAGE_TYPE_CHOICES] =
	{".bmp", ".png", ".jpg", ".pic", ".tiff", ".tga"};

const int NUM_RLE_IMAGE_TYPE_CHOICES = 4;

const std::string g_szRleImageTypeChoices[NUM_RLE_IMAGE_TYPE_CHOICES] =
	{"Bitmap (*.bmp)", "Portable Network Graphics (*.png)", "JPEG (*.jpg)", "TIFF (*.tiff)"};

const std::string g_szRleImageTypeExtensions[NUM_RLE_IMAGE_TYPE_CHOICES] =
	{".bmp", ".png", ".jpg", ".tiff"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CEditor
{
public:

	CEditor(void);
	~CEditor(void);

	int Run(HINSTANCE hInstance);

	static CEditor* GetCurrentEditor(void);
	static CPlugIn* GetCurrentPlugin(void);

	char *GetCurFilename(void);
	char *GetCurFilenameNoPath(void);

	int GetCurFileOffset(void);

	char *GetTempFileDirectory(void);

	int GenerateTempFilename(char *szBuffer);

//	char *GetEVNLocation(void);

	int PrefGenerateLogFile(void);
	int PrefCacheRLEs(void);
	int PrefRLEBackgroundColor(void);

	int RemoveEditDialog(CWindow *pWindow, int iIDOrNameChanged);

	int IsUniqueResourceID(CNovaResource* pResource, short iID);

	CNovaResource* Find(int rezType, short iID);
	
	void ResourceExtra(short id, std::string dfltName, int type = CNR_TYPE_DESC);

	int SetDirty(void);


private:

	std::string GetRootFolder(std::string filename = "");

	int Init(HINSTANCE hInstance);
	int Shutdown(void);

	int ParseCommandLine(LPSTR szCommandLine, char *szBuffer);

	int LoadPreferences(void);
	int SavePreferences(void);

	int PrefsInitDialog(HWND hwnd);
//	int PrefsBrowse(void);
	int PrefsCloseAndSave(void);
	int PrefsCloseAndDontSave(void);

	int TempInitDialog(HWND hwnd);
	int TempCloseAndSave(void);
	int TempCloseAndDontSave(void);

	int FileNew(void);
	int FileOpen(int iOpenDialog, char *szFilename);
	int FileSave(void);
	int FileSaveAs(void);
//	int FileTestPlugIn(void);
	int FileExit(void);

	int EditCut(void);
	int EditCopy(void);
	int EditPaste(int iOverwrite);
	int EditDelete(void);
	int EditTemplate(void);
	int EditPreferences(void);
	void EditLoadLibrary(std::string path, bool clearFirst = true);

	int ResourceNew(void);
	int ResourceEdit(void);
	int ResourceDelete(void);
	CNovaResource* ResourceTemplate(short id, CNovaResource* pTemplateResource, std::string resName);

	int HelpAbout(void);

	int AskForSave(void);

	int AskForCicnExportFormat(void);
	int AskForPictExportFormat(void);
	int AskForRle8ExportFormat(void);
	int AskForRleDExportFormat(void);
	int AskForSndExportFormat(void);

	short FindUniqueResourceID(int iType, short iStart);

	int UpdateResourceList(void);

	static BOOL MainDialogProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static BOOL PreferencesDialogProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static BOOL AboutDialogProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static BOOL TemplateDialogProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	static BOOL CicnExportFormatProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static BOOL PictExportFormatProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static BOOL RleExportFormatProc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static BOOL SndExportFormatProc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	CPlugIn m_plugIn;

	CWindow m_dialogMain;

	std::vector<CWindow *> m_vEditDialogs;
	std::vector<std::string> m_szRecentPaths;

	HMENU m_hMainMenu;
	HMENU m_hWindowMenu;

	HMENU m_hResourceTypePopupMenu;
	HMENU m_hResourcePopupMenu;

	HACCEL m_hAccelerators;

	int m_iAcceleratorHandled;

	OPENFILENAME m_ofnLoadSave;

	int m_iIsDirty;

	CWindow m_wndPreferences;
	CWindow m_wndAbout;
	CWindow m_wndTemplate;

	CWindow m_wndCicnExportFormat;
	CWindow m_wndPictExportFormat;
	CWindow m_wndRleExportFormat;
	CWindow m_wndSndExportFormat;

//	OPENFILENAME m_ofnBrowse;

	char m_szDirectory[MAX_PATH];

	char m_szTempFileDirectory[MAX_PATH];

//	char m_szEVNLocation[MAX_PATH];

	int m_iPrefGenerateLogFile;
	int m_iPrefCacheRLEs;
	int m_iPrefRLEBackgroundColor;

	CControl m_prefControls[NUM_PREFERENCE_CONTROLS];
	CControl m_tempControls[NUM_TEMPLATE_CONTROLS];

	CControl m_cicnExportFormatControls[NUM_CICN_EXPORT_FORMAT_CONTROLS];
	CControl m_pictExportFormatControls[NUM_PICT_EXPORT_FORMAT_CONTROLS];
	CControl m_rleExportFormatControls[ NUM_RLE_EXPORT2_FORMAT_CONTROLS];
	CControl m_sndExportFormatControls[ NUM_SND_EXPORT_FORMAT_CONTROLS];

	char m_szCicnExportSubdirectory[MAX_PATH];
	char m_szCicnExportFilenamePrefix[MAX_PATH];
	char m_szCicnExportMaskSubdirectory[MAX_PATH];
	char m_szCicnExportMaskFilenamePrefix[MAX_PATH];
	int  m_iCicnExportReturnValue;

	char m_szPictExportSubdirectory[MAX_PATH];
	char m_szPictExportFilenamePrefix[MAX_PATH];
	int  m_iPictExportType;
	int  m_iPictExportReturnValue;

	char m_szRleExportSubdirectory[MAX_PATH];
	char m_szRleExportFilenamePrefix[MAX_PATH];
	char m_szRleExportMaskSubdirectory[MAX_PATH];
	char m_szRleExportMaskFilenamePrefix[MAX_PATH];
	int  m_iRleExportImageFileType;
	int  m_iRleExportMaskFileType;
	int  m_iRleExportFramesPerRow;
	int  m_iRleExportReturnValue;

	char m_szSndExportSubdirectory[MAX_PATH];
	char m_szSndExportFilenamePrefix[MAX_PATH];
	int  m_iSndExportReturnValue;

	int m_iCurrentResourceType;

	UINT m_iResourceClipboardFormat;


//	PROCESS_INFORMATION m_EVNProcessInfo;

//	int m_iIsEVNRunning;

//	std::string m_szTempPluginFilename;

	CErrorLog m_errorLog;
	std::string szLastOpen;
	static CEditor * ms_pCurrentEditor;
};
