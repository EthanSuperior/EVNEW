// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File EVNEW.cpp

// This project is OPEN SOURCE.  You may freely use, modify, and distribute
// this source code, under the conditions that:
// (1) The comments at the top of every file are left unaltered
// (2) The accompanying file "Readme.txt" is distributed unaltered
// (3) I, Adam Rosenfield, am cited as the original author
// (4) You do not sell any part, including the source and executable, for profit


// How to compile EVNEW:

// EVNEW uses the QuickTime Software Development Kit (SDK) for several things.
// You can download the SDK from 
// <http://developer.apple.com/quicktime>
// Once the SDK is installed, add to your compiler's search paths for headers
// and libraries the locations of the QT SDK headers and libraries, or just
// copy them into your compiler's header and library directories.  Using
// Microsoft Visual C++, you do this by going to Tools -> Options, clicking
// the Directories tab, and adding the QT directories to the lists under
// Include files and Library files.  Finally, you have to link the project
// to qtmlClient.lib and comctl32.lib .  In MSVC, you do this by going to
// Project -> Settings, clicking the Link tab, and adding qtmlClient.lib to the
// Object/library modules box.  When the project is being linked, you may get a
// warning:
// "LINK : warning LNK4098: defaultlib "LIBCMT" conflicts with use of other
//         libs; use /NODEFAULTLIB:library"
// You can ignore this.

// How To Compile 2025:
// Download QT SDK from https://github.com/Olde-Skuul/quicktime7windows
// Download CE of Nova
// Get Visual Stuido (I used 2022)
// In Project Properies
// Under Configuration Properties > General
// Set Configuration Type to Application (.exe)
// Set C++ Language Standard to ISO C++17 Standard
// Configuration Properties > VC++ Directories
// Add the C:\QT_SDK_PATH\CIncludes to Include Directories
// Add the C:\QT_SDK_PATH\Libraries to Library Directories
// Under Configuration Properties > Linker > Input
// Add comctl32.lib and QTMLClient.lib to Additional Dependencies
// In Ignore Specific Default Libraries add LIBCMT


////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

#include <algorithm>
#include <set>

namespace qt
{
	#include <QTML.h>
}

#include "EVNEW.h"
#include "CPlugIn.h"

#include "CNovaResource.h"
#include "CBoomResource.h"
#include "CCharResource.h"
#include "CCicnResource.h"
#include "CColrResource.h"
#include "CCronResource.h"
#include "CDescResource.h"
#include "CDudeResource.h"
#include "CFletResource.h"
#include "CGovtResource.h"
#include "CIntfResource.h"
#include "CJunkResource.h"
#include "CMisnResource.h"
#include "CNebuResource.h"
#include "COopsResource.h"
#include "COutfResource.h"
#include "CPersResource.h"
#include "CPictResource.h"
#include "CRankResource.h"
#include "CRLEResource.h"
#include "CRoidResource.h"
#include "CShanResource.h"
#include "CShipResource.h"
#include "CSndResource.h"
#include "CSpinResource.h"
#include "CSpobResource.h"
#include "CStrResource.h"
#include "CStrlResource.h"
#include "CSystResource.h"
#include "CWeapResource.h"
#include "CUnkResource.h"

#include "resource.h"

CEditor * CEditor::ms_pCurrentEditor = NULL;

////////////////////////////////////////////////////////////////
//////////////////////////	FUNCTIONS  /////////////////////////
////////////////////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow)
{
	CEditor editor;

	return (editor.Run(hInstance));
}

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CEditor::CEditor(void)
{

}

CEditor::~CEditor(void)
{

}

int CEditor::Init(HINSTANCE hInstance)
{
	LPSTR szCommandLine = GetCommandLine();

	int iCount = ParseCommandLine(szCommandLine, m_szDirectory);

	char *pLastBackslash = strrchr(m_szDirectory, '\\');

	if(pLastBackslash == NULL)
		pLastBackslash = m_szDirectory;

	pLastBackslash[0] = '\0';

	strcpy(m_szTempFileDirectory, m_szDirectory);
	strcat(m_szTempFileDirectory, "\\Temp");

	CreateDirectory(m_szTempFileDirectory, NULL);

	szCommandLine += iCount;

	char szBuffer[MAX_PATH];

	if(m_iPrefGenerateLogFile)
	{
		strcpy(szBuffer, m_szDirectory);
		strcat(szBuffer, "\\log.txt");

		m_errorLog.OpenLogFile(szBuffer, 0);
		m_errorLog.EnableLogFileAutoFlush();
	}

	m_errorLog.SetAsCurrentErrorLog();

	CEditor::ms_pCurrentEditor = this;

	LoadPreferences();

	qt::OSErr qtErr = qt::InitializeQTML(0);

	if(qtErr != qt::noErr)
	{
		m_errorLog << "Error: Unable to initialize QTML!" << CErrorLog::endl;

		MessageBox(NULL, "QuickTime is not installed on this computer.\nEVNEW requires QuickTime to run.", "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	char szArg1[MAX_PATH], szArg2[MAX_PATH], szArg3[MAX_PATH];

	iCount = ParseCommandLine(szCommandLine, szArg1); szCommandLine += iCount;

	int iShouldLoadAtEnd = 0;

	m_iIsDirty = 0;

	if(iCount > 0)
	{
		if(strcmp(szArg1, "-torez") == 0)
		{
			iCount = ParseCommandLine(szCommandLine, szArg2); szCommandLine += iCount;

			if(iCount == 0)
			{
				MessageBox(NULL, "Usage: EVNEW.exe -torez \"source.txt\" \"destination.rez\"", "Error", MB_OK | MB_ICONEXCLAMATION);

				return 0;
			}

			iCount = ParseCommandLine(szCommandLine, szArg3); szCommandLine += iCount;

			if(iCount == 0)
			{
				MessageBox(NULL, "Usage: EVNEW.exe -torez \"source.txt\" \"destination.rez\"", "Error", MB_OK | MB_ICONEXCLAMATION);

				return 0;
			}

			if(GetCurrentPlugin()->Load(szArg2, NULL) == 0)
				return 0;

			char *pExtension = strrchr(szArg3, '.');

			if(pExtension == NULL)
				pExtension = szArg3;
			else
				pExtension++;

			if(strcmp(pExtension, "rez") != 0)
				strcat(szArg3, ".rez");

			GetCurrentPlugin()->SetFilename(szArg3);
			GetCurrentPlugin()->Save(NULL);

			return 0;
		}
		else if(strcmp(szArg1, "-totxt") == 0)
		{
			iCount = ParseCommandLine(szCommandLine, szArg2); szCommandLine += iCount;

			if(iCount == 0)
			{
				MessageBox(NULL, "Usage: EVNEW.exe -totxt \"source.rez\" \"destination.txt\"", "Error", MB_OK | MB_ICONEXCLAMATION);

				return 0;
			}

			iCount = ParseCommandLine(szCommandLine, szArg3); szCommandLine += iCount;

			if(iCount == 0)
			{
				MessageBox(NULL, "Usage: EVNEW.exe -totxt \"source.rez\" \"destination.txt\"", "Error", MB_OK | MB_ICONEXCLAMATION);

				return 0;
			}

			if(GetCurrentPlugin()->Load(szArg2, NULL) == 0)
				return 0;

			char *pExtension = strrchr(szArg3, '.');

			if(pExtension == NULL)
				pExtension = szArg3;
			else
				pExtension++;

			if(strcmp(pExtension, "txt") != 0)
				strcat(szArg3, ".txt");

			GetCurrentPlugin()->SetFilename(szArg3);
			GetCurrentPlugin()->Save(NULL);

			return 0;
		}
		else
		{
			iShouldLoadAtEnd = 1;
		}
	}

	INITCOMMONCONTROLSEX iccex;

	iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	iccex.dwICC  = ICC_WIN95_CLASSES;

	InitCommonControlsEx(&iccex);

	m_dialogMain.SetExtraData(0, (int)this);
	m_dialogMain.SetExtraData(1, (int)&m_errorLog);
	m_dialogMain.SetDlgProc(CEditor::MainDialogProc);
	m_dialogMain.CreateAsDialog(hInstance, IDD_MAINDIALOG, 0, NULL);
	m_dialogMain.SetTitle("Untitled.rez - EVNEW");

	HWND hwndListResourceTypes;
	HWND hwndListResources;

	hwndListResourceTypes = GetDlgItem(m_dialogMain.GetHWND(), IDC_LIST_RESOURCETYPES);
	hwndListResources     = GetDlgItem(m_dialogMain.GetHWND(), IDC_LIST_RESOURCES);

	int i;

	std::string szBuffer2;

	for(i = 0; i < NUM_RESOURCE_TYPES; i++)
	{
		szBuffer2 = g_szResourceTypes[i];
		szBuffer2 += " (0)";

		ListBox_AddString(hwndListResourceTypes, szBuffer2.c_str());
	}

	ListBox_SetCurSel(hwndListResourceTypes, 0);

	m_iCurrentResourceType = 0;

	m_hMainMenu = GetMenu(m_dialogMain.GetHWND());

	m_hWindowMenu = GetSubMenu(m_hMainMenu, 3);

	m_hResourceTypePopupMenu = LoadMenu(m_dialogMain.GetInstance(), MAKEINTRESOURCE(IDR_RESOURCETYPEPOPUPMENU));
	m_hResourcePopupMenu     = LoadMenu(m_dialogMain.GetInstance(), MAKEINTRESOURCE(IDR_RESOURCEPOPUPMENU));

	MENUITEMINFO menuItemInfo;

	memset(&menuItemInfo, 0, sizeof(MENUITEMINFO));

	menuItemInfo.cbSize     = sizeof(MENUITEMINFO);
	menuItemInfo.fMask      = MIIM_DATA;
	menuItemInfo.dwItemData = (DWORD)&m_dialogMain;

	SetMenuItemInfo(m_hWindowMenu, 0, TRUE, &menuItemInfo);

	m_hAccelerators = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	m_iAcceleratorHandled = 0;

	memset(&m_ofnLoadSave, 0, sizeof(OPENFILENAME));

	m_ofnLoadSave.lStructSize   = sizeof(OPENFILENAME);
	m_ofnLoadSave.nMaxFile      = MAX_PATH;
	m_ofnLoadSave.nMaxFileTitle = MAX_PATH;

//	memset(&m_ofnBrowse, 0, sizeof(OPENFILENAME));
//
//	m_ofnBrowse.lStructSize   = sizeof(OPENFILENAME);
//	m_ofnBrowse.nMaxFile      = MAX_PATH;
//	m_ofnBrowse.nMaxFileTitle = MAX_PATH;
//	m_ofnBrowse.lpstrTitle    = "Select EVN Location";
//	m_ofnBrowse.lpstrFilter   = "Executables (*.exe)\0*.exe\0";
//	m_ofnBrowse.nFilterIndex  = 1;
//	m_ofnBrowse.lpstrDefExt   = "exe";
//	m_ofnBrowse.Flags         = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

//	memset(&m_EVNProcessInfo, 0, sizeof(PROCESS_INFORMATION));

//	m_iIsEVNRunning = 0;

	m_iResourceClipboardFormat = RegisterClipboardFormat("CNovaResource");
	
	if (iShouldLoadAtEnd) {
		FileOpen(0, szArg1);
	}
	else if (szLastOpen != "") {
		FileOpen(0, szLastOpen.data());
	}
	//Load Default Values

	return 1;
}

int CEditor::Shutdown(void)
{
//	if(m_iIsEVNRunning)
//	{
//		DWORD dwExitCode;
//
//		GetExitCodeProcess(m_EVNProcessInfo.hProcess, &dwExitCode);
//
//		if(dwExitCode != STILL_ACTIVE)
//		{
//			m_iIsEVNRunning = 0;
//
//			DeleteFile(m_szTempPluginFilename.c_str());
//
//			m_szTempPluginFilename = "";
//
//			memset(&m_EVNProcessInfo, 0, sizeof(PROCESS_INFORMATION));
//		}
//	}
	int i;

	if (m_iIsDirty)
	{
		if (AskForSave() == 0) {
			m_dialogMain.Destroy();

			qt::TerminateQTML();

			m_errorLog.CloseLogFile();
			Workspace::Clear();
			return 1;
		}

		m_iIsDirty = 0;
	}

	for (i = m_vEditDialogs.size() - 1; i >= 0; i--)
		((CNovaResource*)m_vEditDialogs[i]->GetExtraData(2))->CloseAndDontSave();


	GetCurrentPlugin()->ClearFilename();

	m_dialogMain.Destroy();

	qt::TerminateQTML();

	m_errorLog.CloseLogFile();

	return 1;
}

int CEditor::Run(HINSTANCE hInstance)
{
	MSG msg;

	msg.wParam = 0;

	int iResult;

	try
	{
		iResult = Init(hInstance);
	}
	catch(CException exception)
	{
		m_errorLog.FatalError(exception.GetExceptionString());

		iResult = 0;
	}

	int i;

	int iIsDialogMessage;

	if(iResult)
	{
		while(GetMessage(&msg, NULL, 0, 0) != 0)
		{
			m_iAcceleratorHandled = 0;

			if((TranslateAccelerator(m_dialogMain.GetHWND(), m_hAccelerators, &msg) == 0) || (m_iAcceleratorHandled == 0))
			{
				if(IsDialogMessage(m_dialogMain.GetHWND(), &msg) == 0)
				{
					iIsDialogMessage = 0;

					for(i = 0; i < m_vEditDialogs.size(); i++)
					{
						if(IsDialogMessage(m_vEditDialogs[i]->GetHWND(), &msg) != 0)
						{
							iIsDialogMessage = 1;

							break;
						}
					}

					if(!iIsDialogMessage)
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}
			}

			if(m_dialogMain.GetExceptionString()[0] != '\0')
			{
				m_errorLog.FatalError(m_dialogMain.GetExceptionString());

				break;
			}
		}
	}

	try
	{
		Shutdown();
	}
	catch(CException exception)
	{
		m_errorLog.FatalError(exception.GetExceptionString());
	}

	return (msg.wParam);
}

int CEditor::ParseCommandLine(LPSTR szCommandLine, char *szBuffer)
{
	int iRetValue = 0;

	if(strcmp(szCommandLine, "") != 0)
	{
		if(szCommandLine[0] == '\"')
		{
			char *pCloseQuote = strchr(szCommandLine + 1, '\"');

			if(pCloseQuote == NULL)
			{
				strcpy(szBuffer, szCommandLine + 1);

				iRetValue = strlen(szBuffer) + 1;
			}
			else
			{
				strncpy(szBuffer, szCommandLine + 1, pCloseQuote - szCommandLine - 1);

				szBuffer[pCloseQuote - szCommandLine - 1] = '\0';

				iRetValue = pCloseQuote - szCommandLine + 1;
			}
		}
		else
		{
			char *pSpace = strpbrk(szCommandLine, " \n\t\r");

			if(pSpace == NULL)
			{
				strcpy(szBuffer, szCommandLine);

				iRetValue = strlen(szBuffer);
			}
			else
			{
				strncpy(szBuffer, szCommandLine, pSpace - szCommandLine);

				szBuffer[pSpace - szCommandLine] = '\0';

				iRetValue = pSpace - szCommandLine + 1;
			}
		}

		while((szCommandLine[iRetValue] == ' ') || (szCommandLine[iRetValue] == '\n') || (szCommandLine[iRetValue] == '\t') || (szCommandLine[iRetValue] == '\r'))
			iRetValue++;
	}
	else
	{
		strcpy(szBuffer, "");

		iRetValue = 0;
	}

	return iRetValue;
}

CEditor* CEditor::GetCurrentEditor(void)
{
	return CEditor::ms_pCurrentEditor;
}

CPlugIn* CEditor::GetCurrentPlugin(void)
{
	return Workspace::ActiveFile();
}

int CEditor::LoadPreferences(void)
{
	std::ifstream inPrefs;

	char szBuffer[MAX_PATH];

	strcpy(szBuffer, m_szDirectory);
	strcat(szBuffer, "\\Preferences.txt");

	inPrefs.open(szBuffer, std::ios::in);

	if(inPrefs.is_open() == 0)
	{
//		strcpy(m_szEVNLocation, "C:\\Program Files\\Ambrosia\\EV Nova\\EV Nova.exe");

		m_iPrefGenerateLogFile    = 1;
		m_iPrefCacheRLEs          = 1;
		m_iPrefRLEBackgroundColor = 0x00808080;
		m_szRecentPaths.clear();
		SavePreferences();

		return 1;
	}

	char szLine[1024];

	std::string szStrLine;
	std::string szToken;

	inPrefs.getline(szLine, 1024);

	while(!inPrefs.eof())
	{
		inPrefs.getline(szLine, 1024);

		if(inPrefs.eof())
			break;

		szStrLine = szLine;

		if(szStrLine.size() == 0)
			continue;

		szToken = szStrLine.substr(0, szStrLine.find(' '));

		szStrLine = szStrLine.substr(szStrLine.find(' ') + 1);

		while((szStrLine[0] == ' ') || (szStrLine[0] == '\t'))
			szStrLine = szStrLine.substr(1);

//		if(szToken == "EVNLOCATION")
//			strcpy(m_szEVNLocation, szStrLine.c_str());
		if(szToken == "GENERATELOGFILE")
			m_iPrefGenerateLogFile = FromString<int>(szStrLine);
		else if(szToken == "CACHERLES")
			m_iPrefCacheRLEs = FromString<int>(szStrLine);
		else if(szToken == "RLEBACKGROUNDCOLOR")
		{
			int iRed, iGreen, iBlue;

			iRed = FromString<int>(szStrLine.substr(0, szStrLine.find(' ')));

			szStrLine = szStrLine.substr(szStrLine.find(' ') + 1);

			iGreen = FromString<int>(szStrLine.substr(0, szStrLine.find(' ')));

			iBlue = FromString<int>(szStrLine.substr(szStrLine.find(' ') + 1));

			m_iPrefRLEBackgroundColor = ((iRed & 0xFF) << 16) | ((iGreen & 0xFF) << 8) | (iBlue & 0xFF);
		}
		else if (szToken == "RECENTFILE")
		{
			if (szLastOpen == "") szLastOpen = szStrLine;
			m_szRecentPaths.push_back(szStrLine);
		}
	}

	inPrefs.close();

	SavePreferences();

	return 1;
}

int CEditor::SavePreferences(void)
{
	std::ofstream outPrefs;

	char szBuffer[MAX_PATH];

	strcpy(szBuffer, m_szDirectory);
	strcat(szBuffer, "\\Preferences.txt");

	outPrefs.open(szBuffer, std::ios::out | std::ios::trunc);

	if(outPrefs.is_open() == 0)
	{
		MessageBox(m_dialogMain.GetHWND(), "Unable to open Preferences.txt!", "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	outPrefs << "EVNEW Preferences"                             << std::endl
			                                                    << std::endl
			 << "GENERATELOGFILE "    << m_iPrefGenerateLogFile << std::endl
			 << "CACHERLES "          << m_iPrefCacheRLEs       << std::endl
			 << "RLEBACKGROUNDCOLOR " << ((m_iPrefRLEBackgroundColor >> 16) & 0xFF) << ' '
									  << ((m_iPrefRLEBackgroundColor >> 8)  & 0xFF) << ' '
									  << ( m_iPrefRLEBackgroundColor        & 0xFF) << std::endl;

	std::set<std::string> s;
	for (auto& p : m_szRecentPaths) {
		if (!s.insert(p).second) continue;
		outPrefs << "RECENTFILE " << p << std::endl;
		if (s.size() == 5) break;
	}
	outPrefs.close();

	return 1;
}

char * CEditor::GetTempFileDirectory(void)
{
	return m_szTempFileDirectory;
}

int CEditor::GenerateTempFilename(char *szBuffer)
{
	std::string szFilename, szFilenameFinal;

	szFilename = m_szTempFileDirectory;
	szFilename += '\\';
	szFilename += szBuffer;

	std::ifstream filein;

	filein.open(szFilename.c_str(), std::ios::in);

	if(!filein.is_open())
	{
		strcpy(szBuffer, szFilename.c_str());

		return 1;
	}

	int i;

	for(i = 2; i <= 32767; i++)
	{
		filein.close();

		szFilenameFinal = szFilename;
		szFilenameFinal += '_';
		szFilenameFinal += ToString(i);

		filein.open(szFilenameFinal.c_str(), std::ios::in);

		if(!filein.is_open())
		{
			strcpy(szBuffer, szFilenameFinal.c_str());

			return 1;
		}
	}

	return 0;
}

//char *CEditor::GetEVNLocation(void)
//{
//	return m_szEVNLocation;
//}

int CEditor::PrefGenerateLogFile(void)
{
	return m_iPrefGenerateLogFile;
}

int CEditor::PrefCacheRLEs(void)
{
	return m_iPrefCacheRLEs;
}

int CEditor::PrefRLEBackgroundColor(void)
{
	return m_iPrefRLEBackgroundColor;
}

int CEditor::FileNew(void)
{
	int i;

	if(m_iIsDirty)
	{
		if(AskForSave() == 0)
			return 0;

		m_iIsDirty = 0;
	}

	for(i = m_vEditDialogs.size() - 1; i >= 0; i--)
		((CNovaResource *)m_vEditDialogs[i]->GetExtraData(2))->CloseAndDontSave();

	GetCurrentPlugin()->Clear();
	GetCurrentPlugin()->ClearFilename();
	UpdateResourceList();
	Workspace::Clear();

	m_dialogMain.SetTitle("Untitled.rez - EVNEW");

	return 1;
}

int CEditor::FileOpen(int iDialog, char *szFilename)
{
	if(m_iIsDirty)
	{
		if(AskForSave() == 0)
			return 0;

		m_iIsDirty = 0;
	}

	char szFilename2[MAX_PATH];

	if(iDialog)
	{
		strcpy(szFilename2, "");

		m_ofnLoadSave.hwndOwner    = m_dialogMain.GetHWND();
		m_ofnLoadSave.lpstrFile    = szFilename2;
		m_ofnLoadSave.lpstrTitle   = "Open Plug-In";
		m_ofnLoadSave.lpstrFilter  = "Windows Plug-In (*.rez)\0*.rez\0Text file (*.txt)\0*.txt\0";
		m_ofnLoadSave.nFilterIndex = 1;
		m_ofnLoadSave.lpstrDefExt  = "rez";
		m_ofnLoadSave.Flags        = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

		if(GetOpenFileName(&m_ofnLoadSave) == 0)
			return 0;
	}
	else
	{
		strcpy(szFilename2, szFilename);
	}
	
	int iResult = Workspace::Open(szFilename2, &m_dialogMain);
	szLastOpen = szFilename2;
	m_szRecentPaths.insert(m_szRecentPaths.begin(), szFilename2);
	UpdateResourceList();

	if(iResult == 0)
	{
		std::string szBuffer = "One or more errors occured while loading file\"";

		szBuffer += GetCurrentPlugin()->GetFilename();
		szBuffer += "\".";

		if(m_iPrefGenerateLogFile)
			szBuffer += "  Consult log.txt for details.";

		MessageBox(m_dialogMain.GetHWND(), szBuffer.c_str(), "Error", MB_ICONEXCLAMATION | MB_OK);

		return 0;
	}

	std::string szTitle;

	szTitle = GetCurrentPlugin()->GetFilenameNoPath();
	szTitle += " - EVNEW";

	m_dialogMain.SetTitle(szTitle.c_str());

	if(m_ofnLoadSave.nFilterIndex == 2)
		GetCurrentPlugin()->SetFilename("");

	return 1;
}

int CEditor::FileSave(void)
{
	if(strcmp(GetCurrentPlugin()->GetFilename(), "") == 0)
	{
		if(FileSaveAs() == 0)
			return 0;
	}

	GetCurrentPlugin()->Save(&m_dialogMain);

	m_iIsDirty = 0;

	return 1;
}

int CEditor::FileSaveAs(void)
{
	char szFilename[MAX_PATH];

	strcpy(szFilename, "");

	m_ofnLoadSave.hwndOwner    = m_dialogMain.GetHWND();
	m_ofnLoadSave.lpstrFile    = szFilename;
	m_ofnLoadSave.lpstrTitle   = "Save Plug-In";
	m_ofnLoadSave.lpstrFilter  = "Windows Plug-In (*.rez)\0*.rez\0Text file (*.txt)\0*.txt\0";
	m_ofnLoadSave.nFilterIndex = 1;
	m_ofnLoadSave.lpstrDefExt  = "rez";
	m_ofnLoadSave.Flags        = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

	if(GetSaveFileName(&m_ofnLoadSave) == 0)
		return 0;

	if(strcmp(szFilename, "") == 0)
		return 0;

	if(m_ofnLoadSave.nFilterIndex == 2)
	{
		if(GetCurrentPlugin()->m_vResources[CNR_TYPE_CICN].size() > 0)
		{
			AskForCicnExportFormat();

			if(m_iCicnExportReturnValue == -1)
				return 0;
			else if(m_iCicnExportReturnValue == 0)
				GetCurrentPlugin()->SetCicnSaveOptions(0, m_szCicnExportSubdirectory, m_szCicnExportFilenamePrefix, m_szCicnExportMaskSubdirectory, m_szCicnExportMaskFilenamePrefix);
			else
				GetCurrentPlugin()->SetCicnSaveOptions(1, m_szCicnExportSubdirectory, m_szCicnExportFilenamePrefix, m_szCicnExportMaskSubdirectory, m_szCicnExportMaskFilenamePrefix);
		}

		if(GetCurrentPlugin()->m_vResources[CNR_TYPE_PICT].size() > 0)
		{
			AskForPictExportFormat();

			if(m_iPictExportReturnValue == -1)
				return 0;
			else if(m_iPictExportReturnValue == 0)
				GetCurrentPlugin()->SetPictSaveOptions(0, m_szPictExportSubdirectory, m_szPictExportFilenamePrefix, m_iPictExportType);
			else
				GetCurrentPlugin()->SetPictSaveOptions(1, m_szPictExportSubdirectory, m_szPictExportFilenamePrefix, m_iPictExportType);
		}

		if(GetCurrentPlugin()->m_vResources[CNR_TYPE_RLE8].size() > 0)
		{
			AskForRle8ExportFormat();

			if(m_iRleExportReturnValue == -1)
				return 0;
			else if(m_iRleExportReturnValue == 0)
				GetCurrentPlugin()->SetRle8SaveOptions(0, m_szRleExportSubdirectory, m_szRleExportFilenamePrefix, m_szRleExportMaskSubdirectory, m_szRleExportMaskFilenamePrefix, m_iRleExportImageFileType, m_iRleExportMaskFileType, m_iRleExportFramesPerRow);
			else
				GetCurrentPlugin()->SetRle8SaveOptions(1, m_szRleExportSubdirectory, m_szRleExportFilenamePrefix, m_szRleExportMaskSubdirectory, m_szRleExportMaskFilenamePrefix, m_iRleExportImageFileType, m_iRleExportMaskFileType, m_iRleExportFramesPerRow);
		}

		if(GetCurrentPlugin()->m_vResources[CNR_TYPE_RLED].size() > 0)
		{
			AskForRleDExportFormat();

			if(m_iRleExportReturnValue == -1)
				return 0;
			else if(m_iRleExportReturnValue == 0)
				GetCurrentPlugin()->SetRleDSaveOptions(0, m_szRleExportSubdirectory, m_szRleExportFilenamePrefix, m_szRleExportMaskSubdirectory, m_szRleExportMaskFilenamePrefix, m_iRleExportImageFileType, m_iRleExportMaskFileType, m_iRleExportFramesPerRow);
			else
				GetCurrentPlugin()->SetRleDSaveOptions(1, m_szRleExportSubdirectory, m_szRleExportFilenamePrefix, m_szRleExportMaskSubdirectory, m_szRleExportMaskFilenamePrefix, m_iRleExportImageFileType, m_iRleExportMaskFileType, m_iRleExportFramesPerRow);
		}

		if(GetCurrentPlugin()->m_vResources[CNR_TYPE_SND].size() > 0)
		{
			AskForSndExportFormat();

			if(m_iSndExportReturnValue == -1)
				return 0;
			else if(m_iSndExportReturnValue == 0)
				GetCurrentPlugin()->SetSndSaveOptions(0, m_szSndExportSubdirectory, m_szSndExportFilenamePrefix);
			else
				GetCurrentPlugin()->SetSndSaveOptions(1, m_szSndExportSubdirectory, m_szSndExportFilenamePrefix);
		}
	}

	GetCurrentPlugin()->SetFilename(szFilename);

	FileSave();

	EditLoadLibrary("../Nova Files", false);

	std::string szTitle;

	szTitle = GetCurrentPlugin()->GetFilenameNoPath();
	szTitle += " - EVNEW";

	m_dialogMain.SetTitle(szTitle.c_str());

	if(m_ofnLoadSave.nFilterIndex == 2)
		GetCurrentPlugin()->SetFilename("");

	return 1;
}

/*int CEditor::FileTestPlugIn(void)
{
	if(m_iIsEVNRunning)
	{
		MessageBox(m_dialogMain.GetHWND(), "EVN is currently still running.  Please exit it and try again.", "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	std::string szPlugInFolder;

	szPlugInFolder = m_szEVNLocation;
	szPlugInFolder = szPlugInFolder.substr(0, szPlugInFolder.rfind('\\'));
	szPlugInFolder += "\\Nova Plug-ins\\";

	int i;

	std::ifstream filein;

	for(i = 0; i < 32768; i++)
	{
		m_szTempPluginFilename = szPlugInFolder;
		m_szTempPluginFilename += "Temp plug-in";
		m_szTempPluginFilename += ToString(i);
		m_szTempPluginFilename += ".rez";

		filein.open(m_szTempPluginFilename.c_str(), std::ios::in);

		if(filein.is_open() == 0)
			break;

		filein.close();
	}

	if(i == 32768)
	{
		MessageBox(m_dialogMain.GetHWND(), "Unable to find suitable filename for temporary plug-in!", "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	char szFilenameCopy[MAX_PATH];

	strcpy(szFilenameCopy, GetCurrentPlugin()->GetFilename());

	GetCurrentPlugin()->SetFilename(m_szTempPluginFilename.c_str());

	FileSave();

	GetCurrentPlugin()->SetFilename(szFilenameCopy);

	STARTUPINFO sui;

	memset(&sui, 0, sizeof(STARTUPINFO));

	sui.cb = sizeof(STARTUPINFO);

	sui.wShowWindow = SW_SHOW;

	if(CreateProcess(m_szEVNLocation, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sui, &m_EVNProcessInfo) == 0)
	{
		MessageBox(m_dialogMain.GetHWND(), "Unable to launch EV: Nova!", "Error", MB_OK | MB_ICONEXCLAMATION);

		DeleteFile(m_szTempPluginFilename.c_str());

		memset(&m_EVNProcessInfo, 0, sizeof(PROCESS_INFORMATION));

		m_iIsEVNRunning = 0;

		return 0;
	}

	m_iIsEVNRunning = 1;

	return 1;
}*/

int CEditor::FileExit(void)
{
//	if(m_iIsEVNRunning)
//	{
//		MessageBox(m_dialogMain.GetHWND(), "EVN is still running with a temporary copy of this plug-in.  Please close EVN so that EVNEW can delete this file before exiting.", "Error", MB_OK | MB_ICONEXCLAMATION);
//
//		return 0;
//	}

	if(m_iIsDirty)
	{
		if(AskForSave() == 0)
			return 0;

		m_iIsDirty = 0;
	}

	PostQuitMessage(0);

	SavePreferences();

	return 1;
}

char * CEditor::GetCurFilename(void)
{
	return GetCurrentPlugin()->GetFilename();
}

char * CEditor::GetCurFilenameNoPath(void)
{
	return GetCurrentPlugin()->GetFilenameNoPath();
}

int CEditor::GetCurFileOffset(void)
{
	return GetCurrentPlugin()->GetCurFileOffset();
}

int CEditor::EditCut(void)
{
	EditCopy();
	EditDelete();

	return 1;
}

int CEditor::EditCopy(void)
{
	HWND hwndListResources = GetDlgItem(m_dialogMain.GetHWND(), IDC_LIST_RESOURCES);

	int iSelected = ListBox_GetCurSel(hwndListResources);

	if(iSelected == -1)
		return 0;

	CNovaResource *pResource = GetCurrentPlugin()->m_vResources[m_iCurrentResourceType][iSelected];

	if(OpenClipboard(m_dialogMain.GetHWND()) == 0)
		return 0;

	EmptyClipboard();

	int iSize = pResource->GetSize();

	HGLOBAL hGlobalMem = GlobalAlloc(GMEM_MOVEABLE, (iSize + 266) * sizeof(char));

	if(hGlobalMem == NULL)
	{
		CloseClipboard();

		return 0;
	}

	char *pGlobalMem = (char *)GlobalLock(hGlobalMem);

	if(pGlobalMem == NULL)
	{
		CloseClipboard();

		return 0;
	}

	short iID = pResource->GetID();
	int iType = pResource->GetType();

	char szName[256];

	strcpy(szName, pResource->GetName());

	*(int   *) pGlobalMem      = iType;
	*(int   *)(pGlobalMem + 4) = iSize;
	*(short *)(pGlobalMem + 8) = iID;

	memcpy(pGlobalMem + 10, szName, 256 * sizeof(char));

	pResource->Save(pGlobalMem + 266);

	GlobalUnlock(hGlobalMem);

	SetClipboardData(m_iResourceClipboardFormat, hGlobalMem);

	CloseClipboard();

	return 1;
}

int CEditor::EditPaste(int iOverwrite)
{
	HWND hwndListResourceTypes = GetDlgItem(m_dialogMain.GetHWND(), IDC_LIST_RESOURCETYPES);
	HWND hwndListResources     = GetDlgItem(m_dialogMain.GetHWND(), IDC_LIST_RESOURCES);

	CNovaResource *pResource;

	if(IsClipboardFormatAvailable(m_iResourceClipboardFormat) == 0)
		return 0;

	if(OpenClipboard(m_dialogMain.GetHWND()) == 0)
		return 0;

	HGLOBAL hGlobalMem = GetClipboardData(m_iResourceClipboardFormat);

	if(hGlobalMem == NULL)
	{
		CloseClipboard();

		return 0;
	}

	char *pGlobalMem = (char *)GlobalLock(hGlobalMem);

	if(pGlobalMem == NULL)
	{
		CloseClipboard();

		return 0;
	}

	short iID;
	int iType;
	int iSize;

	char szName[256];

	iType = *(int   *) pGlobalMem;
	iSize = *(int   *)(pGlobalMem + 4);
	iID   = *(short *)(pGlobalMem + 8);

	memcpy(szName, pGlobalMem + 10, 256 * sizeof(char));

	int iSelection;

	if(iOverwrite)
	{
		if(ListBox_GetCurSel(hwndListResourceTypes) == iType)
		{
			iSelection = ListBox_GetCurSel(hwndListResources);

			if(iSelection == -1)
			{
				pResource = GetCurrentPlugin()->AllocateResource(iType);

				iOverwrite = 0;
			}
			else
			{
				pResource = GetCurrentPlugin()->m_vResources[iType][iSelection];
			}
		}
		else
		{
			pResource = GetCurrentPlugin()->AllocateResource(iType);

			iOverwrite = 0;
		}
	}
	else
	{
		pResource = GetCurrentPlugin()->AllocateResource(iType);
	}

	pResource->Load(pGlobalMem + 266, iSize);

	GlobalUnlock(hGlobalMem);

	CloseClipboard();

	ListBox_SetCurSel(hwndListResourceTypes, iType);

	if(!iOverwrite)
		pResource->SetID(FindUniqueResourceID(iType, iID));

	pResource->SetName(szName);

	pResource->SetIsNew(0);

	if(!iOverwrite)
		GetCurrentPlugin()->m_vResources[iType].push_back(pResource);

	UpdateResourceList();

	int i;

	for(i = 0; i < GetCurrentPlugin()->m_vResources[iType].size(); i++)
	{
		if(GetCurrentPlugin()->m_vResources[iType][i] == pResource)
		{
			ListBox_SetCurSel(hwndListResources, i);

			break;
		}
	}

	if(i == GetCurrentPlugin()->m_vResources[iType].size())
		ListBox_SetCurSel(hwndListResources, -1);

	SetDirty();

	return 1;
}

int CEditor::EditDelete(void)
{
	ResourceDelete();

	return 1;
}

int CEditor::EditTemplate(void)
{
	m_wndTemplate.SetExtraData(0, (int)this);
	m_wndTemplate.SetExtraData(1, (int)&m_errorLog);
	m_wndTemplate.SetDlgProc(CEditor::TemplateDialogProc);
	m_wndTemplate.CreateAsDialog(m_dialogMain.GetInstance(), IDD_EDIT_TEMP, 1, &m_dialogMain);
	return 1;
}

int CEditor::EditPreferences(void)
{
	m_wndPreferences.SetExtraData(0, (int)this);
	m_wndPreferences.SetExtraData(1, (int)&m_errorLog);
	m_wndPreferences.SetDlgProc(CEditor::PreferencesDialogProc);
	m_wndPreferences.CreateAsDialog(m_dialogMain.GetInstance(), IDD_PREFERENCES, 1, &m_dialogMain);

	return 1;
}

void CEditor::EditLoadLibrary(std::string path, bool clearFirst)
{
	if (clearFirst) Workspace::Clear();

	std::filesystem::path absPath = std::filesystem::absolute(path);

	if (!std::filesystem::exists(absPath)) {
		MessageBox(NULL, ("Could Not Load Library at:\n" + absPath.string()).c_str(), "Error", MB_ICONERROR | MB_OK);
		return;
	}
	Workspace::Open(absPath.string(), &m_dialogMain);
}

int CEditor::ResourceNew(void)
{
	CNovaResource *pNovaResource = NULL;

	pNovaResource = GetCurrentPlugin()->AllocateResource(m_iCurrentResourceType);

	if(pNovaResource == NULL)
		return 0;

	if(GetCurrentPlugin()->m_vResources[m_iCurrentResourceType].size() == 0)
		pNovaResource->SetID(128);
	else
		pNovaResource->SetID(GetCurrentPlugin()->m_vResources[m_iCurrentResourceType][GetCurrentPlugin()->m_vResources[m_iCurrentResourceType].size() - 1]->GetID() + 1);
	GetCurrentPlugin()->m_vResources[m_iCurrentResourceType].push_back(pNovaResource);

	UpdateResourceList();

	HWND hwndListResources = GetDlgItem(m_dialogMain.GetHWND(), IDC_LIST_RESOURCES);

	ListBox_SetCurSel(hwndListResources, GetCurrentPlugin()->m_vResources[m_iCurrentResourceType].size() - 1);

	ResourceEdit();

	return 1;
}

int CEditor::ResourceEdit(void)
{
	HWND hwndListResources = GetDlgItem(m_dialogMain.GetHWND(), IDC_LIST_RESOURCES);

	int iSelected = ListBox_GetCurSel(hwndListResources);

	if(iSelected == -1)
		return 0;

	CNovaResource *pNovaResource = GetCurrentPlugin()->m_vResources[m_iCurrentResourceType][iSelected];

	if(pNovaResource == NULL)
		return 0;

	int i;

	for(i = 0; i < m_vEditDialogs.size(); i++)
	{
		if(m_vEditDialogs[i]->GetExtraData(2) == (int)pNovaResource)
		{
			SetFocus(m_vEditDialogs[i]->GetHWND());

			return 1;
		}
	}

	if(pNovaResource->GetDialogID() != -1)
	{
		m_vEditDialogs.push_back(new CWindow());

		pNovaResource->SetWindow(m_vEditDialogs[m_vEditDialogs.size() - 1]);

		m_vEditDialogs[m_vEditDialogs.size() - 1]->SetDlgProc(pNovaResource->GetDialogProc());
		m_vEditDialogs[m_vEditDialogs.size() - 1]->SetExtraData(0, (int)this);
		m_vEditDialogs[m_vEditDialogs.size() - 1]->SetExtraData(1, (int)&m_errorLog);
		m_vEditDialogs[m_vEditDialogs.size() - 1]->SetExtraData(2, (int)pNovaResource);

		int iCount = GetMenuItemCount(m_hWindowMenu);

		std::string szMenuString = "";

		if(iCount < 9)
			szMenuString += '&';

		szMenuString += ToString(iCount + 1);
		szMenuString += " - ";
		szMenuString += g_szResourceTypes[pNovaResource->GetType()];
		szMenuString += ' ';
		szMenuString += ToString(pNovaResource->GetID());
		szMenuString += " (";
		szMenuString += pNovaResource->GetName();
		szMenuString += ')';

		char *pString = NULL;

		pString = new char[szMenuString.size() + 1];

		if(pString == NULL)
			throw CException("Error: unable to allocate memory for menu item string!");

		strcpy(pString, szMenuString.c_str());

		m_vEditDialogs[m_vEditDialogs.size() - 1]->SetExtraData(4, (int)pString);

		MENUITEMINFO menuItemInfo;

		memset(&menuItemInfo, 0, sizeof(MENUITEMINFO));

		menuItemInfo.cbSize     = sizeof(MENUITEMINFO);
		menuItemInfo.fMask      = MIIM_DATA | MIIM_ID | MIIM_STATE | MIIM_TYPE;
		menuItemInfo.fType      = MFT_STRING;
		menuItemInfo.fState     = MFS_ENABLED;
		menuItemInfo.wID        = IDM_WINDOW_1 + iCount;
		menuItemInfo.dwItemData = (DWORD)m_vEditDialogs[m_vEditDialogs.size() - 1];
		menuItemInfo.dwTypeData = pString;
		menuItemInfo.cch        = szMenuString.size();

		InsertMenuItem(m_hWindowMenu, iCount, TRUE, &menuItemInfo);

		m_vEditDialogs[m_vEditDialogs.size() - 1]->CreateAsDialog(m_dialogMain.GetInstance(), pNovaResource->GetDialogID(), 0, &m_dialogMain);
//		m_vEditDialogs[m_vEditDialogs.size() - 1]->CreateAsDialog(m_dialogMain.GetInstance(), pNovaResource->GetDialogID(), 1, NULL);
	}

	return 1;
}

void CEditor::ResourceExtra(short id, std::string dfltName, int type) {
	CNovaResource* pNovaResource = FindById(type, id);
	// If the resource is not found in the plugin - copy it from the library
	if (pNovaResource == NULL) {
		pNovaResource = ResourceTemplate(id, Workspace::FindById(type, id), dfltName);
		if (pNovaResource != NULL) {
			SetDirty();
			UpdateResourceList();
		}
	}
	// If the resource is not found in the library - create a new one
	if (pNovaResource == NULL) {
		pNovaResource = GetCurrentPlugin()->AllocateResource(type);
		pNovaResource->SetID(id);
		pNovaResource->SetName(dfltName.c_str());
		GetCurrentPlugin()->m_vResources[type].push_back(pNovaResource);
		SetDirty();
		UpdateResourceList();
	}

	for (int i = 0; i < m_vEditDialogs.size(); i++)
	{
		if (m_vEditDialogs[i]->GetExtraData(2) != (int)pNovaResource) continue;
		SetFocus(m_vEditDialogs[i]->GetHWND());
		return;
	}

	if (pNovaResource->GetDialogID() == -1) return;
	CWindow* pWindow = new CWindow();
	pNovaResource->SetWindow(pWindow);
	pWindow->SetDlgProc(pNovaResource->GetDialogProc());
	pWindow->SetExtraData(0, (int)this);
	pWindow->SetExtraData(1, (int)&m_errorLog);
	pWindow->SetExtraData(2, (int)pNovaResource);
	m_vEditDialogs.push_back(pWindow);

	int iCount = GetMenuItemCount(m_hWindowMenu);

	std::string szMenuString = "";

	if (iCount < 9)	szMenuString += '&';

	szMenuString += ToString(iCount + 1);
	szMenuString += " - ";
	szMenuString += g_szResourceTypes[pNovaResource->GetType()];
	szMenuString += ' ';
	szMenuString += ToString(pNovaResource->GetID());
	szMenuString += " (";
	szMenuString += pNovaResource->GetName();
	szMenuString += ')';

	char* pString = NULL;

	pString = new char[szMenuString.size() + 1];

	if (pString == NULL) throw CException("Error: unable to allocate memory for menu item string!");

	strcpy(pString, szMenuString.c_str());

	pWindow->SetExtraData(4, (int)pString);

	MENUITEMINFO menuItemInfo;

	memset(&menuItemInfo, 0, sizeof(MENUITEMINFO));

	menuItemInfo.cbSize = sizeof(MENUITEMINFO);
	menuItemInfo.fMask = MIIM_DATA | MIIM_ID | MIIM_STATE | MIIM_TYPE;
	menuItemInfo.fType = MFT_STRING;
	menuItemInfo.fState = MFS_ENABLED;
	menuItemInfo.wID = IDM_WINDOW_1 + iCount;
	menuItemInfo.dwItemData = (DWORD)pWindow;
	menuItemInfo.dwTypeData = pString;
	menuItemInfo.cch = szMenuString.size();

	InsertMenuItem(m_hWindowMenu, iCount, TRUE, &menuItemInfo);

	pWindow->CreateAsDialog(m_dialogMain.GetInstance(), pNovaResource->GetDialogID(), 0, &m_dialogMain);
}

CNovaResource* CEditor::ResourceTemplate(short iID, CNovaResource* pTemplateResource, std::string rezName)
{
	if (pTemplateResource == NULL) return NULL;
	int iType = pTemplateResource->GetType();
	short tempID = pTemplateResource->GetID();
	int iSize = pTemplateResource->GetSize();

	if (iType == CNR_TYPE_MISN) {
		ResourceTemplate(iID + 4000 - 128, Workspace::FindById(CNR_TYPE_DESC, tempID + 4000 - 128), rezName);
		ResourceTemplate(iID + 5000 - 128, Workspace::FindById(CNR_TYPE_DESC, tempID + 5000 - 128), rezName);
		ResourceTemplate(iID + 6000 - 128, Workspace::FindById(CNR_TYPE_DESC, tempID + 6000 - 128), rezName);
		ResourceTemplate(iID + 7000 - 128, Workspace::FindById(CNR_TYPE_DESC, tempID + 7000 - 128), rezName);
		ResourceTemplate(iID + 8000 - 128, Workspace::FindById(CNR_TYPE_DESC, tempID + 8000 - 128), rezName);
		ResourceTemplate(iID + 9000 - 128, Workspace::FindById(CNR_TYPE_DESC, tempID + 9000 - 128), rezName);
		ResourceTemplate(iID + 15000 - 128, Workspace::FindById(CNR_TYPE_DESC, tempID + 15000 - 128), rezName);
		ResourceTemplate(iID + 16000 - 128, Workspace::FindById(CNR_TYPE_DESC, tempID + 16000 - 128), rezName);
		ResourceTemplate(iID + 17000 - 128, Workspace::FindById(CNR_TYPE_DESC, tempID + 17000 - 128), rezName);
	}
	else if (iType == CNR_TYPE_NEBU) {
		short nebuTempID = ((tempID - 128) * 7) + 9500;
		short nebuID = ((iID - 128) * 7) + 9500;
		ResourceTemplate(nebuID, Workspace::FindById(CNR_TYPE_PICT, nebuTempID), rezName + "; 42.1%");
		ResourceTemplate(nebuID + 1, Workspace::FindById(CNR_TYPE_PICT, nebuTempID + 1), rezName + "; 56.2%");
		ResourceTemplate(nebuID + 2, Workspace::FindById(CNR_TYPE_PICT, nebuTempID + 2), rezName + "; 75.0%");
		ResourceTemplate(nebuID + 3, Workspace::FindById(CNR_TYPE_PICT, nebuTempID + 3), rezName + "; 100.0%");
		ResourceTemplate(nebuID + 4, Workspace::FindById(CNR_TYPE_PICT, nebuTempID + 4), rezName + "; 133.3%");
		ResourceTemplate(nebuID + 5, Workspace::FindById(CNR_TYPE_PICT, nebuTempID + 5), rezName + "; 177.7%");
		ResourceTemplate(nebuID + 6, Workspace::FindById(CNR_TYPE_PICT, nebuTempID + 6), rezName + "; 237.0%");
	}
	else if (iType == CNR_TYPE_OUTF) {
		ResourceTemplate(iID + 3000 - 128, Workspace::FindById(CNR_TYPE_DESC, tempID + 3000 - 128), rezName);
		ResourceTemplate(iID + 6000 - 128, Workspace::FindById(CNR_TYPE_PICT, tempID + 6000 - 128), rezName);
	}
	else if (iType == CNR_TYPE_SHIP) {
		ResourceTemplate(iID, Workspace::FindById(CNR_TYPE_SHAN, tempID), rezName);
		ResourceTemplate(iID + 3000 - 128, Workspace::FindById(CNR_TYPE_PICT, tempID + 3000 - 128), rezName + "; Targeting");
		ResourceTemplate(iID + 5000 - 128, Workspace::FindById(CNR_TYPE_PICT, tempID + 5000 - 128), rezName);
		ResourceTemplate(iID + 13000 - 128, Workspace::FindById(CNR_TYPE_DESC, tempID + 13000 - 128), rezName);
		ResourceTemplate(iID + 14000 - 128, Workspace::FindById(CNR_TYPE_DESC, tempID + 14000 - 128), rezName + "; Escort");
		rezName += +";:" + ToString(tempID);
	}
	else if (iType == CNR_TYPE_SPOB) ResourceTemplate(iID, Workspace::FindById(CNR_TYPE_DESC, tempID), rezName);

	char* pBuffer = new char[iSize];
	pTemplateResource->Save(pBuffer);

	CNovaResource* pNewResource = FindById(iType, iID);
	if (pNewResource == NULL) {
		pNewResource = GetCurrentPlugin()->AllocateResource(iType);
		GetCurrentPlugin()->m_vResources[iType].push_back(pNewResource);
		UpdateResourceList();
	}
	pNewResource->Load(pBuffer, iSize);
	pNewResource->SetID(iID);
	pNewResource->SetName(rezName.c_str());
	pNewResource->SetIsNew(0);
	SetDirty();
	delete[] pBuffer;
	return pNewResource;
}

int CEditor::ResourceDelete(void)
{
	HWND hwndListResources = GetDlgItem(m_dialogMain.GetHWND(), IDC_LIST_RESOURCES);

	int iSelected = ListBox_GetCurSel(hwndListResources);

	if(iSelected == -1)
		return 0;

	int i;

	for(i = 0; i < m_vEditDialogs.size(); i++)
	{
		if(m_vEditDialogs[i]->GetExtraData(2) == (int)GetCurrentPlugin()->m_vResources[m_iCurrentResourceType][iSelected])
		{
			GetCurrentPlugin()->m_vResources[m_iCurrentResourceType][iSelected]->SetIsNew(0);

			GetCurrentPlugin()->m_vResources[m_iCurrentResourceType][iSelected]->CloseAndDontSave();

			break;
		}
	}

	delete GetCurrentPlugin()->m_vResources[m_iCurrentResourceType][iSelected];

	GetCurrentPlugin()->m_vResources[m_iCurrentResourceType].erase(GetCurrentPlugin()->m_vResources[m_iCurrentResourceType].begin() + iSelected);

	UpdateResourceList();

	if(iSelected < GetCurrentPlugin()->m_vResources[m_iCurrentResourceType].size())
		ListBox_SetCurSel(hwndListResources, iSelected);
	else if(iSelected > 0)
		ListBox_SetCurSel(hwndListResources, iSelected - 1);

	SetDirty();

	return 1;
}

int CEditor::HelpAbout(void)
{
	m_wndAbout.SetExtraData(0, (int)this);
	m_wndAbout.SetExtraData(1, (int)&m_errorLog);
	m_wndAbout.SetDlgProc(CEditor::AboutDialogProc);
	m_wndAbout.CreateAsDialog(m_dialogMain.GetInstance(), IDD_ABOUT, 0, NULL);

	return 1;
}

int CEditor::RunNova(void)
{
	std::vector<std::string> extensions = { ".nplay", ".exe", ".lnk" };
	std::filesystem::path root = Workspace::Get().rootPath;

	if (!std::filesystem::exists(root) || !std::filesystem::is_directory(root)) {
		MessageBoxA(NULL, ("Invalid root folder:\n" + root.string()).c_str(), "Error", MB_ICONERROR | MB_OK);
		return FALSE;
	}

	try {
		for (const auto& ext : extensions) {
			for (const auto& entry : std::filesystem::directory_iterator(root)) {
				if (entry.is_regular_file() && entry.path().extension() == ext) {
					std::string pathStr = entry.path().generic_string();

					HINSTANCE result = ShellExecuteA(NULL, "open", pathStr.c_str(), NULL, root.string().c_str(), SW_SHOWNORMAL);
					if ((INT_PTR)result <= 32) {
						std::string error = "Failed to launch:\n" + pathStr;
						MessageBoxA(NULL, error.c_str(), "Error", MB_ICONERROR | MB_OK);
						return FALSE;
					}

					return TRUE;
				}
			}
		}
	} catch (const std::filesystem::filesystem_error& e) {
		MessageBoxA(NULL, e.what(), "Filesystem Error", MB_ICONERROR | MB_OK);
	}
	return FALSE;
}

int CEditor::SetDirty(void)
{
	m_iIsDirty = 1;

	return 1;
}

int CEditor::AskForSave(void)
{
	int iResult = MessageBox(m_dialogMain.GetHWND(), "The current plug-in is unsaved.  Would you like to save it?", "Unsaved Plug-in", MB_YESNOCANCEL | MB_ICONEXCLAMATION);

	if(iResult == IDCANCEL)
		return 0;
	else if(iResult == IDYES)
	{
		if(FileSave() == 0)
			return 0;
	}

	return 1;
}

int CEditor::PrefsInitDialog(HWND hwnd)
{
//	m_prefControls[0].Create(hwnd, IDC_PREFERENCES_EDIT1, CCONTROL_TYPE_STR256, IDS_STRING1600);
//	m_prefControls[0].SetString(m_szEVNLocation);
	m_prefControls[0].Create(hwnd, IDC_PREFERENCES_CHECK1, CCONTROL_TYPE_CHECK, IDS_STRING1601);
	m_prefControls[0].SetInt(m_iPrefGenerateLogFile);
	m_prefControls[1].Create(hwnd, IDC_PREFERENCES_CHECK2, CCONTROL_TYPE_CHECK, IDS_STRING1602);
	m_prefControls[1].SetInt(m_iPrefCacheRLEs);
	m_prefControls[2].Create(hwnd, IDC_PREFERENCES_BUTTON1, CCONTROL_TYPE_COLOR, IDS_STRING1603);
	m_prefControls[2].SetInt(m_iPrefRLEBackgroundColor);

	return 1;
}

//int CEditor::PrefsBrowse(void)
//{
//	char szBuffer[MAX_PATH];
//
//	strcpy(szBuffer, m_prefControls[0].GetString());
//
//	m_ofnBrowse.hwndOwner = m_wndPreferences.GetHWND();
//	m_ofnBrowse.lpstrFile = szBuffer;
//
//	if(GetOpenFileName(&m_ofnBrowse) == 0)
//		return 0;
//
//	m_prefControls[0].SetString(szBuffer);
//
//	return 1;
//}

int CEditor::PrefsCloseAndSave(void)
{
//	strcpy(m_szEVNLocation, m_prefControls[0].GetString());

	m_iPrefGenerateLogFile    = m_prefControls[0].GetInt();
	m_iPrefCacheRLEs          = m_prefControls[1].GetInt();
	m_iPrefRLEBackgroundColor = m_prefControls[2].GetInt();

	int i;

	for(i = 0; i < NUM_PREFERENCE_CONTROLS; i++)
		m_prefControls[i].Destroy();

	m_wndPreferences.Destroy();

	SavePreferences();

	return 1;
}

int CEditor::PrefsCloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_PREFERENCE_CONTROLS; i++)
		m_prefControls[i].Destroy();

	m_wndPreferences.Destroy();

	return 1;
}

int CEditor::TempInitDialog(HWND hwnd)
{
	m_tempControls[0].Create(hwnd, IDC_EDIT_TEMP_EDIT1, CCONTROL_TYPE_INT, IDS_STRING400);
	m_tempControls[0].SetInt(FindUniqueResourceID(m_iCurrentResourceType, 128));
	m_tempControls[1].Create(hwnd, IDC_EDIT_TEMP_EDIT2, CCONTROL_TYPE_STR256, IDS_STRING468);
	m_tempControls[2].Create(hwnd, IDC_EDIT_TEMP_DROP1, CCONTROL_TYPE_REZBOX, IDS_STRING996);
	m_tempControls[2].SetRezType(m_iCurrentResourceType);
	return 1;
}

int CEditor::TempCloseAndSave(void)
{
	short m_iTempID = m_tempControls[0].GetInt();
	std::string m_szTempName = m_tempControls[1].GetString();
	short m_iTempCombo = m_tempControls[2].GetInt();

	for (int i = 0; i < NUM_TEMPLATE_CONTROLS; i++) m_tempControls[i].Destroy();
	m_wndTemplate.Destroy();

	if (m_iTempCombo == -1) return 0;
	ResourceTemplate(m_iTempID, Workspace::FindByIdx(m_iCurrentResourceType, m_iTempCombo), m_szTempName);
	UpdateResourceList();
	HWND hwndListResources = GetDlgItem(m_dialogMain.GetHWND(), IDC_LIST_RESOURCES);
	int i;
	for (i = 0; i < GetCurrentPlugin()->m_vResources[m_iCurrentResourceType].size(); i++) {
		if (GetCurrentPlugin()->m_vResources[m_iCurrentResourceType][i]->GetID() == m_iTempID) {
			ListBox_SetCurSel(hwndListResources, i);
			break;
		}
	}
	if (i == GetCurrentPlugin()->m_vResources[m_iCurrentResourceType].size()) ListBox_SetCurSel(hwndListResources, -1);

	SetDirty();
	ResourceEdit();
	return 1;
}

int CEditor::TempCloseAndDontSave(void)
{
	for (int i = 0; i < NUM_TEMPLATE_CONTROLS; i++)
		m_tempControls[i].Destroy();
	m_wndTemplate.Destroy();
	return 1;
}

int CEditor::RemoveEditDialog(CWindow *pWindow, int iIDOrNameChanged)
{
	if(pWindow == NULL)
		return 0;

	CNovaResource *pResource = (CNovaResource *)pWindow->GetExtraData(2);

	if(pResource == NULL)
		return 0;

	pResource->SetWindow(NULL);

	pWindow->Destroy();

	int i;

	for(i = 0; i < m_vEditDialogs.size(); i++)
	{
		if(m_vEditDialogs[i] == pWindow)
		{
			m_vEditDialogs.erase(m_vEditDialogs.begin() + i);

			break;
		}
	}

	MENUITEMINFO menuItemInfo;

	memset(&menuItemInfo, 0, sizeof(MENUITEMINFO));

	menuItemInfo.cbSize = sizeof(MENUITEMINFO);
	menuItemInfo.fMask  = MIIM_DATA;

	for(i = IDM_WINDOW_1; i <= IDM_WINDOW_MAX; i++)
	{	
		GetMenuItemInfo(m_hWindowMenu, i, FALSE, &menuItemInfo);

		if((CWindow *)menuItemInfo.dwItemData == pWindow)
		{
			DeleteMenu(m_hWindowMenu, i, MF_BYCOMMAND);

			DrawMenuBar(m_dialogMain.GetHWND());

			break;
		}
	}

	char *pString = (char *)pWindow->GetExtraData(4);

	if(pString != NULL)
		delete [] pString;

	delete pWindow;

	if(pResource->IsNew())
	{
		int iType = pResource->GetType();

		for(i = 0; i < GetCurrentPlugin()->m_vResources[iType].size(); i++)
		{
			if(GetCurrentPlugin()->m_vResources[iType][i] == pResource)
			{
				GetCurrentPlugin()->m_vResources[iType].erase(GetCurrentPlugin()->m_vResources[iType].begin() + i);

				delete pResource;

				break;
			}
		}

		UpdateResourceList();
	}
	else
	{
		if(iIDOrNameChanged)
			UpdateResourceList();
	}

	m_dialogMain.SetAsForeground();

	SetFocus(GetDlgItem(m_dialogMain.GetHWND(), IDC_LIST_RESOURCES));

	return 1;
}

int CEditor::AskForCicnExportFormat(void)
{
	m_wndCicnExportFormat.SetExtraData(0, (int)this);
	m_wndCicnExportFormat.SetExtraData(1, (int)&m_errorLog);
	m_wndCicnExportFormat.SetDlgProc(CicnExportFormatProc);
	m_wndCicnExportFormat.CreateAsDialog(m_dialogMain.GetInstance(), IDD_CICN_EXPORT, 1, &m_dialogMain);

	return m_iCicnExportReturnValue;
}

int CEditor::AskForPictExportFormat(void)
{
	m_wndPictExportFormat.SetExtraData(0, (int)this);
	m_wndPictExportFormat.SetExtraData(1, (int)&m_errorLog);
	m_wndPictExportFormat.SetDlgProc(PictExportFormatProc);
	m_wndPictExportFormat.CreateAsDialog(m_dialogMain.GetInstance(), IDD_PICT_EXPORT, 1, &m_dialogMain);

	return m_iPictExportReturnValue;
}

int CEditor::AskForRle8ExportFormat(void)
{
	m_wndRleExportFormat.SetExtraData(0, (int)this);
	m_wndRleExportFormat.SetExtraData(1, (int)&m_errorLog);
	m_wndRleExportFormat.SetExtraData(2, 8);
	m_wndRleExportFormat.SetDlgProc(RleExportFormatProc);
	m_wndRleExportFormat.CreateAsDialog(m_dialogMain.GetInstance(), IDD_RLE_EXPORT2, 1, &m_dialogMain);

	return m_iRleExportReturnValue;
}

int CEditor::AskForRleDExportFormat(void)
{
	m_wndRleExportFormat.SetExtraData(0, (int)this);
	m_wndRleExportFormat.SetExtraData(1, (int)&m_errorLog);
	m_wndRleExportFormat.SetExtraData(2, 16);
	m_wndRleExportFormat.SetDlgProc(RleExportFormatProc);
	m_wndRleExportFormat.CreateAsDialog(m_dialogMain.GetInstance(), IDD_RLE_EXPORT2, 1, &m_dialogMain);

	return m_iRleExportReturnValue;
}

int CEditor::AskForSndExportFormat(void)
{
	m_wndSndExportFormat.SetExtraData(0, (int)this);
	m_wndSndExportFormat.SetExtraData(1, (int)&m_errorLog);
	m_wndSndExportFormat.SetDlgProc(SndExportFormatProc);
	m_wndSndExportFormat.CreateAsDialog(m_dialogMain.GetInstance(), IDD_SND_EXPORT, 1, &m_dialogMain);

	return m_iSndExportReturnValue;
}

short CEditor::FindUniqueResourceID(int iType, short iStart)
{
	short i;

	int j;

	int iUnique;

	for(i = iStart; i <= 32767; i++)
	{
		iUnique = 1;

		for(j = 0; j < GetCurrentPlugin()->m_vResources[iType].size(); j++)
		{
			if(GetCurrentPlugin()->m_vResources[iType][j]->GetID() == i)
			{
				iUnique = 0;

				break;
			}
		}

		if(iUnique)
			return i;
	}

	for(i = 128; i < iStart; i++)
	{
		iUnique = 1;

		for(j = 0; j < GetCurrentPlugin()->m_vResources[iType].size(); j++)
		{
			if(GetCurrentPlugin()->m_vResources[iType][j]->GetID() == i)
			{
				iUnique = 0;

				break;
			}
		}

		if(iUnique)
			return i;
	}

	return -1;
}

CNovaResource* CEditor::FindById(int rezType, short iID) {
	CNovaResource* pResource = NULL;
	for (auto* ptr : GetCurrentPlugin()->m_vResources[rezType]) {
		if (ptr->GetID() != iID) continue;
		pResource = ptr;
		break;
	}
	return pResource;
}

int CEditor::IsUniqueResourceID(CNovaResource *pResource, short iID)
{
	int i;

	int iType = pResource->GetType();

	for(i = 0; i < GetCurrentPlugin()->m_vResources[iType].size(); i++)
	{
		if((GetCurrentPlugin()->m_vResources[iType][i]->GetID() == iID) && (GetCurrentPlugin()->m_vResources[iType][i] != pResource))
			return 0;
	}

	return 1;
}

int CEditor::UpdateResourceList(void)
{
	HWND hwndListResourceTypes = GetDlgItem(m_dialogMain.GetHWND(), IDC_LIST_RESOURCETYPES);
	HWND hwndListResources     = GetDlgItem(m_dialogMain.GetHWND(), IDC_LIST_RESOURCES);

	int i;

	std::string szBuffer;

	int iResourceType = ListBox_GetCurSel(hwndListResourceTypes);
	int iSelection    = ListBox_GetCurSel(hwndListResources);

	int iTopIndex = ListBox_GetTopIndex(hwndListResources);

	int iFlag = 0;

	if(m_iCurrentResourceType == iResourceType)
		iFlag = 1;

	m_iCurrentResourceType = iResourceType;

	ListBox_ResetContent(hwndListResourceTypes);

	for(i = 0; i < NUM_RESOURCE_TYPES; i++)
	{
		szBuffer = g_szResourceTypes[i];
		szBuffer += " (";
		szBuffer += ToString(GetCurrentPlugin()->m_vResources[i].size());
		szBuffer += ")";

		ListBox_AddString(hwndListResourceTypes, szBuffer.c_str());
	}

	ListBox_SetCurSel(hwndListResourceTypes, m_iCurrentResourceType);

	ListBox_ResetContent(hwndListResources);

	if(GetCurrentPlugin()->m_vResources[m_iCurrentResourceType].size() > 0)
	{
		std::sort(GetCurrentPlugin()->m_vResources[m_iCurrentResourceType].begin(), GetCurrentPlugin()->m_vResources[m_iCurrentResourceType].end(), SNovaResourceCompare());

		for(i = 0; i < GetCurrentPlugin()->m_vResources[m_iCurrentResourceType].size(); i++)
		{
			szBuffer = g_szResourceTypes[GetCurrentPlugin()->m_vResources[m_iCurrentResourceType][i]->GetType()];
			szBuffer += ' ';
			szBuffer += ToString(GetCurrentPlugin()->m_vResources[m_iCurrentResourceType][i]->GetID());
			szBuffer += " (";
			szBuffer += GetCurrentPlugin()->m_vResources[m_iCurrentResourceType][i]->GetName();
			szBuffer += ')';

			ListBox_AddString(hwndListResources, szBuffer.c_str());
		}

		if(iFlag)
		{
			ListBox_SetCurSel(hwndListResources, iSelection);

			ListBox_SetTopIndex(hwndListResources, iTopIndex);
		}
	}

	return 1;
}

BOOL CEditor::MainDialogProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CEditor *pEditor;

	pWindow = CWindow::GetWindow(hwnd, 1);

	pEditor = CEditor::GetCurrentEditor();

	int i;

//	if(pEditor->m_iIsEVNRunning)
//	{
//		DWORD dwExitCode;
//
//		GetExitCodeProcess(pEditor->m_EVNProcessInfo.hProcess, &dwExitCode);
//
//		if(dwExitCode != STILL_ACTIVE)
//		{
//			pEditor->m_iIsEVNRunning = 0;
//
//			DeleteFile(pEditor->m_szTempPluginFilename.c_str());
//
//			pEditor->m_szTempPluginFilename = "";
//
//			memset(&pEditor->m_EVNProcessInfo, 0, sizeof(PROCESS_INFORMATION));
//		}
//	}

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			//HWND hMainWnd = GetParent(hwnd); // or your main window HWND directly
			HMENU hMainMenu = GetMenu(hwnd);
			if (!hMainMenu) return TRUE; // Or handle error

			HMENU hRecentMenu = CreatePopupMenu();
			for (size_t i = 0; i < pEditor->m_szRecentPaths.size(); ++i) {
				std::string displayName = pEditor->m_szRecentPaths[i];
				AppendMenuA(hRecentMenu, MF_STRING, IDM_RECENT_FILE_0 + static_cast<UINT>(i), displayName.c_str());
			}

			HMENU hFileMenu = GetSubMenu(hMainMenu, 0); // assuming File is first
			InsertMenuA(hFileMenu, 2, MF_BYPOSITION | MF_POPUP, (UINT_PTR)hRecentMenu, "Open Recent");

			DrawMenuBar(hwnd);

			return TRUE;

			break;
		}

		case WM_SYSCOMMAND:
		{
			if(wparam == SC_CLOSE)
				pEditor->FileExit();

			break;
		}

		case WM_COMMAND:
		{
			int iNotifyCode = HIWORD(wparam);
			int iControlID  = LOWORD(wparam);

			if(iControlID == IDC_LIST_RESOURCETYPES)
			{
				HWND hwndListResourceTypes = GetDlgItem(hwnd, IDC_LIST_RESOURCETYPES);
				HWND hwndListResources     = GetDlgItem(hwnd, IDC_LIST_RESOURCES);

				if(iNotifyCode == LBN_SELCHANGE)
				{
					pEditor->UpdateResourceList();
				}
				else if(iNotifyCode == LBN_DBLCLK)
				{
					pEditor->ResourceNew();
				}
			}
			else if(iControlID == IDC_LIST_RESOURCES)
			{
				if(iNotifyCode == LBN_DBLCLK)
				{
					pEditor->ResourceEdit();
				}
			}
			else if(iControlID == IDC_BUTTON_NEW)
			{
				if(iNotifyCode == BN_CLICKED)
				{
					pEditor->ResourceNew();
				}
			}
			else if(iControlID >= IDM_RECENT_FILE_0 && iControlID <= IDM_RECENT_FILE_0 + 4) {
				char buffer[256] = {};
				MENUITEMINFOA mii = { sizeof(MENUITEMINFOA) };
				mii.fMask = MIIM_STRING;
				mii.dwTypeData = buffer;
				mii.cch = sizeof(buffer);

				HMENU hFileMenu = GetSubMenu(GetMenu(hwnd), 0); // Assuming "File" is first submenu

				if (GetMenuItemInfoA(hFileMenu, iControlID, FALSE, &mii)) {
					pEditor->FileOpen(0, buffer);
				}
			}
			else if(iControlID == IDC_BUTTON_EDIT)
			{
				if(iNotifyCode == BN_CLICKED)
				{
					pEditor->ResourceEdit();
				}
			}
			else if (iControlID == IDC_BUTTON_TEMPLATE1)
			{
				if (iNotifyCode == BN_CLICKED)
				{
					pEditor->EditTemplate();
				}
			}
			else if(iControlID == IDC_BUTTON_DELETE)
			{
				if(iNotifyCode == BN_CLICKED)
				{
					pEditor->ResourceDelete();
				}
			}
			else if(iControlID == IDM_FILE_NEW)
			{
				pEditor->FileNew();
			}
			else if(iControlID == IDM_FILE_OPEN)
			{
				pEditor->FileOpen(1, NULL);
			}
			else if(iControlID == IDM_FILE_SAVE)
			{
				pEditor->FileSave();
			}
			else if(iControlID == IDM_FILE_SAVEAS)
			{
				pEditor->FileSaveAs();
			}
//			else if(iControlID == IDM_FILE_TESTPLUGIN)
//			{
//				pEditor->FileTestPlugIn();
//			}
			else if(iControlID == IDM_FILE_EXIT)
			{
				pEditor->FileExit();
			}
			else if(iControlID == IDM_EDIT_CUT)
			{
				pEditor->EditCut();
			}
			else if(iControlID == IDM_EDIT_COPY)
			{
				pEditor->EditCopy();
			}
			else if(iControlID == IDM_EDIT_PASTE)
			{
				pEditor->EditPaste(0);
			}
			else if(iControlID == IDM_EDIT_DELETE)
			{
				pEditor->EditDelete();
			}
			else if(iControlID == IDM_EDIT_PREFERENCES)
			{
				pEditor->EditPreferences();
			}
			else if (iControlID == ID_EDIT_LOADLIBRARY) 
			{
				//pEditor->EditLoadLibrary("../Nova Files", false);
			}
			else if(iControlID == IDM_RESOURCE_NEW)
			{
				pEditor->ResourceNew();
			}
			else if(iControlID == IDM_RESOURCE_EDIT)
			{
				pEditor->ResourceEdit();
			}
			else if(iControlID == IDM_RESOURCE_DELETE)
			{
				pEditor->ResourceDelete();
			}
			else if((iControlID >= IDM_WINDOW_1) && (iControlID <= IDM_WINDOW_MAX))
			{
				MENUITEMINFO menuItemInfo;

				memset(&menuItemInfo, 0, sizeof(MENUITEMINFO));

				menuItemInfo.cbSize = sizeof(MENUITEMINFO);
				menuItemInfo.fMask  = MIIM_DATA;

				GetMenuItemInfo(pEditor->m_hWindowMenu, iControlID, FALSE, &menuItemInfo);

				CWindow *pActiveWindow = (CWindow *)menuItemInfo.dwItemData;

				pActiveWindow->SetFocus();
			}
			else if(iControlID == IDM_HELP_ABOUT)
			{
				pEditor->HelpAbout();
			}
			else if (iControlID == IDM_HELP_NCB)
			{
				MessageBox(NULL, Workspace::GetAvailableNCB().c_str(), "Available NCBs", MB_OK);
			}
			else if (iControlID == IDM_RUNDEV)
			{
				pEditor->RunNova();
			}
			else if(iControlID == IDA_FILENEW)		// Ctrl+N
			{
				pEditor->FileNew();

				pEditor->m_iAcceleratorHandled = 1;
			}
			else if(iControlID == IDA_FILEOPEN)		// Ctrl+O
			{
				pEditor->FileOpen(1, NULL);

				pEditor->m_iAcceleratorHandled = 1;
			}
			else if(iControlID == IDA_FILESAVE)		// Ctrl+S
			{
				pEditor->FileSave();

				pEditor->m_iAcceleratorHandled = 1;
			}
			else if(iControlID == IDA_FILEEXIT)		// Alt+F4
			{
				pEditor->FileExit();

				pEditor->m_iAcceleratorHandled = 1;
			}
			else if(iControlID == IDA_EDITRESOURCE)		// Enter
			{
				pEditor->ResourceEdit();
			}
			else if(iControlID == IDA_FILECLOSEANDDONTSAVE)		// Escape
			{
				for(i = 0; i < pEditor->m_vEditDialogs.size(); i++)
				{
					if(pEditor->m_vEditDialogs[i]->IsActive())
					{
						((CNovaResource *)pEditor->m_vEditDialogs[i]->GetExtraData(2))->CloseAndDontSave();

						pEditor->m_iAcceleratorHandled = 1;

						break;
					}
				}
			}
			else if(iControlID == IDA_EDITCUT)		// Ctrl+X
			{
				if(pEditor->m_dialogMain.IsActive())
				{
					pEditor->EditCut();

					pEditor->m_iAcceleratorHandled = 1;
				}
				else
				{
					for(i = 0; i < pEditor->m_vEditDialogs.size(); i++)
					{
						if((pEditor->m_vEditDialogs[i]->IsActive()) && (((CNovaResource *)(pEditor->m_vEditDialogs[i]->GetExtraData(2)))->GetType() == CNR_TYPE_STRL))
						{
							if(((CStrlResource *)pEditor->m_vEditDialogs[i]->GetExtraData(2))->EditCut() == 1)
								pEditor->m_iAcceleratorHandled = 1;

							break;
						}
					}
				}
			}
			else if(iControlID == IDA_EDITCOPY)		// Ctrl+C
			{
				if(pEditor->m_dialogMain.IsActive())
				{
					pEditor->EditCopy();

					pEditor->m_iAcceleratorHandled = 1;
				}
				else
				{
					for(i = 0; i < pEditor->m_vEditDialogs.size(); i++)
					{
						if((pEditor->m_vEditDialogs[i]->IsActive()) && (((CNovaResource *)(pEditor->m_vEditDialogs[i]->GetExtraData(2)))->GetType() == CNR_TYPE_STRL))
						{
							if(((CStrlResource *)pEditor->m_vEditDialogs[i]->GetExtraData(2))->EditCopy() == 1)
								pEditor->m_iAcceleratorHandled = 1;

							break;
						}
					}
				}
			}
			else if(iControlID == IDA_EDITPASTE)		// Ctrl+V
			{
				if(pEditor->m_dialogMain.IsActive())
				{
					pEditor->EditPaste(0);

					pEditor->m_iAcceleratorHandled = 1;
				}
				else
				{
					for(i = 0; i < pEditor->m_vEditDialogs.size(); i++)
					{
						if((pEditor->m_vEditDialogs[i]->IsActive()) && (((CNovaResource *)(pEditor->m_vEditDialogs[i]->GetExtraData(2)))->GetType() == CNR_TYPE_STRL))
						{
							if(((CStrlResource *)pEditor->m_vEditDialogs[i]->GetExtraData(2))->EditPaste() == 1)
								pEditor->m_iAcceleratorHandled = 1;

							break;
						}
					}
				}
			}
			else if(iControlID == IDA_EDITDELETE)		// Delete
			{
				if(pEditor->m_dialogMain.IsActive())
				{
					pEditor->EditDelete();

					pEditor->m_iAcceleratorHandled = 1;
				}
				else
				{
					for(i = 0; i < pEditor->m_vEditDialogs.size(); i++)
					{
						if((pEditor->m_vEditDialogs[i]->IsActive()) && (((CNovaResource *)(pEditor->m_vEditDialogs[i]->GetExtraData(2)))->GetType() == CNR_TYPE_STRL))
						{
							if(((CStrlResource *)pEditor->m_vEditDialogs[i]->GetExtraData(2))->EditDelete() == 1)
								pEditor->m_iAcceleratorHandled = 1;

							break;
						}
					}
				}
			}
			else if(iControlID == IDM_RESOURCETYPEPOPUP_NEW)
			{
				pEditor->ResourceNew();
			}
			else if(iControlID == IDM_RESOURCEPOPUP_EDIT)
			{
				pEditor->ResourceEdit();
			}
			else if(iControlID == IDM_RESOURCEPOPUP_CUT)
			{
				pEditor->EditCut();
			}
			else if(iControlID == IDM_RESOURCEPOPUP_COPY)
			{
				pEditor->EditCopy();
			}
			else if(iControlID == IDM_RESOURCEPOPUP_PASTE)
			{
				pEditor->EditPaste(0);
			}
			else if(iControlID == IDM_RESOURCEPOPUP_PASTEOVER)
			{
				pEditor->EditPaste(1);
			}
			else if(iControlID == IDM_RESOURCEPOPUP_DELETE)
			{
				pEditor->EditDelete();
			}
			else
			{

			}

			return TRUE;

			break;
		}

		case WM_CONTEXTMENU:		// Right-click on a list box to open a popup menu
		{
			HWND hwndControl = (HWND)wparam;

			int iControlID = GetDlgCtrlID(hwndControl);

			if(iControlID == IDC_LIST_RESOURCETYPES)
			{
				int iXMousePos, iYMousePos;

				iXMousePos = LOWORD(lparam);
				iYMousePos = HIWORD(lparam);

				RECT rectListTypes;

				GetWindowRect(hwndControl, &rectListTypes);

				int iTopIndex       = ListBox_GetTopIndex(hwndControl);
				int iListItemHeight = ListBox_GetItemHeight(hwndControl, 0);

				int iTypeIndex = (iYMousePos - rectListTypes.top) / iListItemHeight + iTopIndex;

				if((iTypeIndex >= 0) && (iTypeIndex < NUM_RESOURCE_TYPES))
				{
					ListBox_SetCurSel(hwndControl, iTypeIndex);

					pEditor->UpdateResourceList();

					TrackPopupMenuEx(GetSubMenu(pEditor->m_hResourceTypePopupMenu, 0), TPM_LEFTALIGN | TPM_TOPALIGN | TPM_LEFTBUTTON, iXMousePos, iYMousePos, hwnd, NULL);
				}

				return TRUE;
			}
			else if(iControlID == IDC_LIST_RESOURCES)
			{
				int iXMousePos, iYMousePos;

				iXMousePos = LOWORD(lparam);
				iYMousePos = HIWORD(lparam);

				RECT rectListResources;

				GetWindowRect(hwndControl, &rectListResources);

				int iTopIndex       = ListBox_GetTopIndex(hwndControl);
				int iListItemHeight = ListBox_GetItemHeight(hwndControl, 0);

				int iResourceIndex = (iYMousePos - rectListResources.top) / iListItemHeight + iTopIndex;

				if((iResourceIndex >= 0) && (iResourceIndex < pEditor->GetCurrentPlugin()->m_vResources[pEditor->m_iCurrentResourceType].size()))
				{
					ListBox_SetCurSel(hwndControl, iResourceIndex);

					TrackPopupMenuEx(GetSubMenu(pEditor->m_hResourcePopupMenu, 0), TPM_LEFTALIGN | TPM_TOPALIGN | TPM_LEFTBUTTON, iXMousePos, iYMousePos, hwnd, NULL);
				}

				return TRUE;
			}

			break;
		}

		default:
		{
			break;
		}
	}

	return FALSE;
}

BOOL CEditor::PreferencesDialogProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CEditor *pEditor;

	pWindow = CWindow::GetWindow(hwnd, 1);

	pEditor = (CEditor *)pWindow->GetExtraData(0);

	int i;

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			pEditor->PrefsInitDialog(hwnd);

			return TRUE;
		}

		case WM_SYSCOMMAND:
		{
			if(wparam == SC_CLOSE)
			{
				pEditor->PrefsCloseAndDontSave();

				return TRUE;
			}

			break;
		}

		case WM_COMMAND:
		{
			int iNotifyCode = HIWORD(wparam);
			int iControlID  = LOWORD(wparam);

			if(iControlID == IDC_PREFERENCES_CANCEL)
			{
				pEditor->PrefsCloseAndDontSave();
			}
			else if(iControlID == IDC_PREFERENCES_OK)
			{
				pEditor->PrefsCloseAndSave();
			}
//			else if(iControlID == IDC_PREFERENCES_BUTTON1)
//			{
//				pEditor->PrefsBrowse();
//			}
			else
			{
				for(i = 0; i < NUM_PREFERENCE_CONTROLS; i++)
				{
					if(iControlID == pEditor->m_prefControls[i].GetControlID())
					{
						pEditor->m_prefControls[i].ProcessMessage(iNotifyCode);

						break;
					}
				}
			}

			return TRUE;

			break;
		}

		default:
		{
			break;
		}
	}

	return FALSE;
}

BOOL CEditor::TemplateDialogProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow* pWindow;
	CEditor* pEditor;

	pWindow = CWindow::GetWindow(hwnd, 1);

	pEditor = (CEditor*)pWindow->GetExtraData(0);

	int i;

	switch (msg)
	{
	case WM_INITDIALOG:
	{
		pEditor->TempInitDialog(hwnd);

		return TRUE;
	}

	case WM_SYSCOMMAND:
	{
		if (wparam == SC_CLOSE)
		{
			pEditor->TempCloseAndDontSave();

			return TRUE;
		}

		break;
	}

	case WM_COMMAND:
	{
		int iNotifyCode = HIWORD(wparam);
		int iControlID = LOWORD(wparam);

		if (iControlID == IDC_EDIT_TEMP_CANCEL)
		{
			pEditor->TempCloseAndDontSave();
		}
		else if (iControlID == IDC_EDIT_TEMP_OK)
		{
			pEditor->TempCloseAndSave();
		}
		else
		{
			for (i = 0; i < NUM_TEMPLATE_CONTROLS; i++)
			{
				if (iControlID == pEditor->m_tempControls[i].GetControlID())
				{
					pEditor->m_tempControls[i].ProcessMessage(iNotifyCode);
					break;
				}
			}
		}

		return TRUE;

		break;
	}

	default:
	{
		break;
	}
	}

	return FALSE;
}

BOOL CEditor::AboutDialogProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CEditor *pEditor;

	pWindow = CWindow::GetWindow(hwnd, 1);

	pEditor = (CEditor *)pWindow->GetExtraData(0);

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			return TRUE;
		}

		case WM_SYSCOMMAND:
		{
			if(wparam == SC_CLOSE)
			{
				pWindow->Destroy();

				return TRUE;
			}

			break;
		}

		case WM_COMMAND:
		{
			int iNotifyCode = HIWORD(wparam);
			int iControlID  = LOWORD(wparam);

			if(iControlID == IDC_ABOUT_OK)
			{
				pWindow->Destroy();
			}

			return TRUE;

			break;
		}

		default:
		{
			break;
		}
	}

	return FALSE;
}

BOOL CEditor::CicnExportFormatProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CEditor *pEditor;

	pWindow = CWindow::GetWindow(hwnd, 1);

	pEditor = (CEditor *)pWindow->GetExtraData(0);

	int i;

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			pEditor->m_cicnExportFormatControls[0].Create(hwnd, IDC_CICN_EXPORT_EDIT1, CCONTROL_TYPE_STR256, -1);
			pEditor->m_cicnExportFormatControls[0].SetString("Cicns");
			pEditor->m_cicnExportFormatControls[1].Create(hwnd, IDC_CICN_EXPORT_EDIT2, CCONTROL_TYPE_STR256, -1);
			pEditor->m_cicnExportFormatControls[1].SetString("cicn");
			pEditor->m_cicnExportFormatControls[2].Create(hwnd, IDC_CICN_EXPORT_EDIT3, CCONTROL_TYPE_STR256, -1);
			pEditor->m_cicnExportFormatControls[2].SetString("Cicns");
			pEditor->m_cicnExportFormatControls[3].Create(hwnd, IDC_CICN_EXPORT_EDIT4, CCONTROL_TYPE_STR256, -1);
			pEditor->m_cicnExportFormatControls[3].SetString("cicnmask");

			return TRUE;
		}

		case WM_SYSCOMMAND:
		{
			if(wparam == SC_CLOSE)
			{
				pEditor->m_iCicnExportReturnValue = -1;

				for(i = 0; i < NUM_CICN_EXPORT_FORMAT_CONTROLS; i++)
					pEditor->m_cicnExportFormatControls[i].Destroy();

				pEditor->m_wndCicnExportFormat.Destroy();

				return TRUE;
			}

			break;
		}

		case WM_COMMAND:
		{
			int iNotifyCode = HIWORD(wparam);
			int iControlID  = LOWORD(wparam);

			if(iControlID == IDC_CICN_EXPORT_OK)
			{
				strcpy(pEditor->m_szCicnExportSubdirectory,       pEditor->m_cicnExportFormatControls[0].GetString());
				strcpy(pEditor->m_szCicnExportFilenamePrefix,     pEditor->m_cicnExportFormatControls[1].GetString());
				strcpy(pEditor->m_szCicnExportMaskSubdirectory,   pEditor->m_cicnExportFormatControls[2].GetString());
				strcpy(pEditor->m_szCicnExportMaskFilenamePrefix, pEditor->m_cicnExportFormatControls[3].GetString());

				pEditor->m_iCicnExportReturnValue = 1;

				for(i = 0; i < NUM_CICN_EXPORT_FORMAT_CONTROLS; i++)
					pEditor->m_cicnExportFormatControls[i].Destroy();

				pEditor->m_wndCicnExportFormat.Destroy();
			}
			else if(iControlID == IDC_CICN_EXPORT_CANCEL)
			{
				pEditor->m_iCicnExportReturnValue = -1;

				for(i = 0; i < NUM_CICN_EXPORT_FORMAT_CONTROLS; i++)
					pEditor->m_cicnExportFormatControls[i].Destroy();

				pEditor->m_wndCicnExportFormat.Destroy();
			}
			else if(iControlID == IDC_CICN_EXPORT_BUTTON3)
			{
				pEditor->m_iCicnExportReturnValue = 0;

				for(i = 0; i < NUM_CICN_EXPORT_FORMAT_CONTROLS; i++)
					pEditor->m_cicnExportFormatControls[i].Destroy();

				pEditor->m_wndCicnExportFormat.Destroy();
			}
			else
			{
				for(i = 0; i < NUM_CICN_EXPORT_FORMAT_CONTROLS; i++)
				{
					if(iControlID == pEditor->m_cicnExportFormatControls[i].GetControlID())
					{
						pEditor->m_cicnExportFormatControls[i].ProcessMessage(iNotifyCode);

						break;
					}
				}
			}

			return TRUE;

			break;
		}

		default:
		{
			break;
		}
	}

	return FALSE;
}

BOOL CEditor::PictExportFormatProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CEditor *pEditor;

	pWindow = CWindow::GetWindow(hwnd, 1);

	pEditor = (CEditor *)pWindow->GetExtraData(0);

	int i;

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			pEditor->m_pictExportFormatControls[0].Create(hwnd, IDC_PICT_EXPORT_EDIT1, CCONTROL_TYPE_STR256, -1);
			pEditor->m_pictExportFormatControls[0].SetString("Picts");
			pEditor->m_pictExportFormatControls[1].Create(hwnd, IDC_PICT_EXPORT_EDIT2, CCONTROL_TYPE_STR256, -1);
			pEditor->m_pictExportFormatControls[1].SetString("pict");
			pEditor->m_pictExportFormatControls[2].Create(hwnd, IDC_PICT_EXPORT_COMBO1, CCONTROL_TYPE_COMBOBOX, -1);
			pEditor->m_pictExportFormatControls[2].SetComboStrings(NUM_IMAGE_TYPE_CHOICES, g_szImageTypeChoices);
			pEditor->m_pictExportFormatControls[2].SetInt(0);

			return TRUE;
		}

		case WM_SYSCOMMAND:
		{
			if(wparam == SC_CLOSE)
			{
				pEditor->m_iPictExportReturnValue = -1;

				for(i = 0; i < NUM_PICT_EXPORT_FORMAT_CONTROLS; i++)
					pEditor->m_pictExportFormatControls[i].Destroy();

				pEditor->m_wndPictExportFormat.Destroy();

				return TRUE;
			}

			break;
		}

		case WM_COMMAND:
		{
			int iNotifyCode = HIWORD(wparam);
			int iControlID  = LOWORD(wparam);

			if(iControlID == IDC_PICT_EXPORT_OK)
			{
				strcpy(pEditor->m_szPictExportSubdirectory,   pEditor->m_pictExportFormatControls[0].GetString());
				strcpy(pEditor->m_szPictExportFilenamePrefix, pEditor->m_pictExportFormatControls[1].GetString());

				pEditor->m_iPictExportType = pEditor->m_pictExportFormatControls[2].GetInt();

				pEditor->m_iPictExportReturnValue = 1;

				for(i = 0; i < NUM_PICT_EXPORT_FORMAT_CONTROLS; i++)
					pEditor->m_pictExportFormatControls[i].Destroy();

				pEditor->m_wndPictExportFormat.Destroy();
			}
			else if(iControlID == IDC_PICT_EXPORT_CANCEL)
			{
				pEditor->m_iPictExportReturnValue = -1;

				for(i = 0; i < NUM_PICT_EXPORT_FORMAT_CONTROLS; i++)
					pEditor->m_pictExportFormatControls[i].Destroy();

				pEditor->m_wndPictExportFormat.Destroy();
			}
			else if(iControlID == IDC_PICT_EXPORT_BUTTON3)
			{
				pEditor->m_iPictExportReturnValue = 0;

				for(i = 0; i < NUM_PICT_EXPORT_FORMAT_CONTROLS; i++)
					pEditor->m_pictExportFormatControls[i].Destroy();

				pEditor->m_wndPictExportFormat.Destroy();
			}
			else
			{
				for(i = 0; i < NUM_PICT_EXPORT_FORMAT_CONTROLS; i++)
				{
					if(iControlID == pEditor->m_pictExportFormatControls[i].GetControlID())
					{
						pEditor->m_pictExportFormatControls[i].ProcessMessage(iNotifyCode);

						break;
					}
				}
			}

			return TRUE;

			break;
		}

		default:
		{
			break;
		}
	}

	return FALSE;
}

BOOL CEditor::RleExportFormatProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CEditor *pEditor;

	pWindow = CWindow::GetWindow(hwnd, 1);

	pEditor = (CEditor *)pWindow->GetExtraData(0);

	int i;

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			pEditor->m_rleExportFormatControls[0].Create(hwnd, IDC_RLE_EXPORT2_EDIT1, CCONTROL_TYPE_STR256, -1);
			pEditor->m_rleExportFormatControls[1].Create(hwnd, IDC_RLE_EXPORT2_EDIT2, CCONTROL_TYPE_STR256, -1);
			pEditor->m_rleExportFormatControls[2].Create(hwnd, IDC_RLE_EXPORT2_COMBO1, CCONTROL_TYPE_COMBOBOX, -1);
			pEditor->m_rleExportFormatControls[2].SetComboStrings(NUM_RLE_IMAGE_TYPE_CHOICES, g_szRleImageTypeChoices);
			pEditor->m_rleExportFormatControls[2].SetInt(0);
			pEditor->m_rleExportFormatControls[3].Create(hwnd, IDC_RLE_EXPORT2_EDIT3, CCONTROL_TYPE_STR256, -1);
			pEditor->m_rleExportFormatControls[4].Create(hwnd, IDC_RLE_EXPORT2_EDIT4, CCONTROL_TYPE_STR256, -1);
			pEditor->m_rleExportFormatControls[5].Create(hwnd, IDC_RLE_EXPORT2_COMBO2, CCONTROL_TYPE_COMBOBOX, -1);
			pEditor->m_rleExportFormatControls[5].SetComboStrings(NUM_RLE_IMAGE_TYPE_CHOICES, g_szRleImageTypeChoices);
			pEditor->m_rleExportFormatControls[5].SetInt(0);
			pEditor->m_rleExportFormatControls[6].Create(hwnd, IDC_RLE_EXPORT2_EDIT5, CCONTROL_TYPE_INT, -1);
			pEditor->m_rleExportFormatControls[6].SetInt(6);
			pEditor->m_rleExportFormatControls[6].SetMinValue(1);

			if(pWindow->GetExtraData(2) == 8)
			{
				pEditor->m_rleExportFormatControls[0].SetString("Rle8s");
				pEditor->m_rleExportFormatControls[1].SetString("rle8_");
				pEditor->m_rleExportFormatControls[3].SetString("Rle8s");
				pEditor->m_rleExportFormatControls[4].SetString("rle8mask_");

				pWindow->SetTitle("rle8 Export Format");

				SetWindowText(GetDlgItem(hwnd, IDC_RLE_EXPORT2_BUTTON3), "Don't Export rle8s");
			}
			else
			{
				pEditor->m_rleExportFormatControls[0].SetString("RleDs");
				pEditor->m_rleExportFormatControls[1].SetString("rleD_");
				pEditor->m_rleExportFormatControls[3].SetString("RleDs");
				pEditor->m_rleExportFormatControls[4].SetString("rleDmask_");

				pWindow->SetTitle("rleD Export Format");

				SetWindowText(GetDlgItem(hwnd, IDC_RLE_EXPORT2_BUTTON3), "Don't Export rleDs");
			}

			return TRUE;
		}

		case WM_SYSCOMMAND:
		{
			if(wparam == SC_CLOSE)
			{
				pEditor->m_iRleExportReturnValue = -1;

				for(i = 0; i < NUM_RLE_EXPORT2_FORMAT_CONTROLS; i++)
					pEditor->m_rleExportFormatControls[i].Destroy();

				pEditor->m_wndRleExportFormat.Destroy();

				return TRUE;
			}

			break;
		}

		case WM_COMMAND:
		{
			int iNotifyCode = HIWORD(wparam);
			int iControlID  = LOWORD(wparam);

			if(iControlID == IDC_RLE_EXPORT2_OK)
			{
				strcpy(pEditor->m_szRleExportSubdirectory,       pEditor->m_rleExportFormatControls[0].GetString());
				strcpy(pEditor->m_szRleExportFilenamePrefix,     pEditor->m_rleExportFormatControls[1].GetString());

				pEditor->m_iRleExportImageFileType = pEditor->m_rleExportFormatControls[2].GetInt();

				strcpy(pEditor->m_szRleExportMaskSubdirectory,   pEditor->m_rleExportFormatControls[3].GetString());
				strcpy(pEditor->m_szRleExportMaskFilenamePrefix, pEditor->m_rleExportFormatControls[4].GetString());

				pEditor->m_iRleExportMaskFileType = pEditor->m_rleExportFormatControls[5].GetInt();
				pEditor->m_iRleExportFramesPerRow = pEditor->m_rleExportFormatControls[6].GetInt();

				pEditor->m_iRleExportReturnValue = 1;

				for(i = 0; i < NUM_RLE_EXPORT2_FORMAT_CONTROLS; i++)
					pEditor->m_rleExportFormatControls[i].Destroy();

				pEditor->m_wndRleExportFormat.Destroy();
			}
			else if(iControlID == IDC_RLE_EXPORT2_CANCEL)
			{
				pEditor->m_iRleExportReturnValue = -1;

				for(i = 0; i < NUM_RLE_EXPORT2_FORMAT_CONTROLS; i++)
					pEditor->m_rleExportFormatControls[i].Destroy();

				pEditor->m_wndRleExportFormat.Destroy();
			}
			else if(iControlID == IDC_RLE_EXPORT2_BUTTON3)
			{
				pEditor->m_iRleExportReturnValue = 0;

				for(i = 0; i < NUM_RLE_EXPORT2_FORMAT_CONTROLS; i++)
					pEditor->m_rleExportFormatControls[i].Destroy();

				pEditor->m_wndRleExportFormat.Destroy();
			}
			else
			{
				for(i = 0; i < NUM_RLE_EXPORT2_FORMAT_CONTROLS; i++)
				{
					if(iControlID == pEditor->m_rleExportFormatControls[i].GetControlID())
					{
						pEditor->m_rleExportFormatControls[i].ProcessMessage(iNotifyCode);

						break;
					}
				}
			}

			return TRUE;

			break;
		}

		default:
		{
			break;
		}
	}

	return FALSE;
}

BOOL CEditor::SndExportFormatProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CEditor *pEditor;

	pWindow = CWindow::GetWindow(hwnd, 1);

	pEditor = (CEditor *)pWindow->GetExtraData(0);

	int i;

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			pEditor->m_sndExportFormatControls[0].Create(hwnd, IDC_SND_EXPORT_EDIT1, CCONTROL_TYPE_STR256, -1);
			pEditor->m_sndExportFormatControls[0].SetString("Sounds");
			pEditor->m_sndExportFormatControls[1].Create(hwnd, IDC_SND_EXPORT_EDIT2, CCONTROL_TYPE_STR256, -1);
			pEditor->m_sndExportFormatControls[1].SetString("snd");

			return TRUE;
		}

		case WM_SYSCOMMAND:
		{
			if(wparam == SC_CLOSE)
			{
				pEditor->m_iSndExportReturnValue = -1;

				for(i = 0; i < NUM_SND_EXPORT_FORMAT_CONTROLS; i++)
					pEditor->m_sndExportFormatControls[i].Destroy();

				pEditor->m_wndSndExportFormat.Destroy();

				return TRUE;
			}

			break;
		}

		case WM_COMMAND:
		{
			int iNotifyCode = HIWORD(wparam);
			int iControlID  = LOWORD(wparam);

			if(iControlID == IDC_SND_EXPORT_OK)
			{
				strcpy(pEditor->m_szSndExportSubdirectory,   pEditor->m_sndExportFormatControls[0].GetString());
				strcpy(pEditor->m_szSndExportFilenamePrefix, pEditor->m_sndExportFormatControls[1].GetString());

				pEditor->m_iSndExportReturnValue = 1;

				for(i = 0; i < NUM_SND_EXPORT_FORMAT_CONTROLS; i++)
					pEditor->m_sndExportFormatControls[i].Destroy();

				pEditor->m_wndSndExportFormat.Destroy();
			}
			else if(iControlID == IDC_SND_EXPORT_CANCEL)
			{
				pEditor->m_iSndExportReturnValue = -1;

				for(i = 0; i < NUM_SND_EXPORT_FORMAT_CONTROLS; i++)
					pEditor->m_sndExportFormatControls[i].Destroy();

				pEditor->m_wndSndExportFormat.Destroy();
			}
			else if(iControlID == IDC_SND_EXPORT_BUTTON3)
			{
				pEditor->m_iSndExportReturnValue = 0;

				for(i = 0; i < NUM_SND_EXPORT_FORMAT_CONTROLS; i++)
					pEditor->m_sndExportFormatControls[i].Destroy();

				pEditor->m_wndSndExportFormat.Destroy();
			}
			else
			{
				for(i = 0; i < NUM_SND_EXPORT_FORMAT_CONTROLS; i++)
				{
					if(iControlID == pEditor->m_sndExportFormatControls[i].GetControlID())
					{
						pEditor->m_sndExportFormatControls[i].ProcessMessage(iNotifyCode);

						break;
					}
				}
			}

			return TRUE;

			break;
		}

		default:
		{
			break;
		}
	}

	return FALSE;
}
