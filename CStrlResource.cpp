// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CStrlResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CStrlResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CStrlResource::CStrlResource(void)
{
	m_iCurString = -1;

	m_iWasSaved = 0;
}

CStrlResource::~CStrlResource(void)
{

}

int CStrlResource::GetType(void)
{
	return CNR_TYPE_STRL;
}

int CStrlResource::GetSize(void)
{
	int iSize = m_vStrings.size() + 2;

	int i;

	for(i = 0; i < m_vStrings.size(); i++)
		iSize += (int)(UCHAR)m_vStrings[i].size();

	return iSize;
}

int CStrlResource::GetDialogID(void)
{
	return IDD_EDIT_STRL;
}

DLGPROCNOCALLBACK CStrlResource::GetDialogProc(void)
{
	return StrlDlgProc;
}

int CStrlResource::GetNumFields(void)
{
	return NUM_STRL_FIELDS;
}

const std::string * CStrlResource::GetFieldNames(void)
{
	return g_szStrlFields;
}

int CStrlResource::Save(char *pOutput)
{
	short iNumStrings = SwapEndianShort((short)m_vStrings.size());

	*(short *)pOutput = iNumStrings; pOutput += sizeof(short);

	UCHAR ucStringLength;

	char szBuffer[256];

	int i;

	for(i = 0; i < m_vStrings.size(); i++)
	{
		strcpy_s(szBuffer, m_vStrings[i].c_str());

		szBuffer[255] = '\0';

		ToMacString(szBuffer);

		ucStringLength = (UCHAR)strlen(szBuffer);

		*pOutput = ucStringLength; pOutput++;

		memcpy(pOutput, szBuffer, (int)ucStringLength * sizeof(char)); pOutput += (int)ucStringLength * sizeof(char);
	}

	return 1;
}

int CStrlResource::Load(char *pInput, int iSize)
{
	short iNumStrings;
	unsigned char ucStringLength;

	iNumStrings = SwapEndianShort(*(short *)pInput); pInput += sizeof(short);

	m_vStrings.resize(iNumStrings);

	short i;

	char szBuffer[256];

	for(i = 0; i < iNumStrings; i++)
	{
		ucStringLength = *pInput; pInput++;

		memcpy(szBuffer, pInput, (int)ucStringLength * sizeof(char)); pInput += (int)ucStringLength * sizeof(char);

		szBuffer[ucStringLength] = '\0';

		ToWinString(szBuffer);

		m_vStrings[i] = szBuffer;
	}

	return 1;
}

int CStrlResource::SaveToText(std::ostream & output)
{
	output << m_vStrings.size() << '\t';

	int i;

	for(i = 0; i < m_vStrings.size(); i++)
	{
		if(i % 252 < 251)
		{
			PrintTextField(output, m_vStrings[i].c_str(), '\t');
		}
		else
		{
			PrintTextField(output, m_vStrings[i].c_str(), '\n');

			output << "\t\t\t\t";
		}
	}

	if(i% 252 == 251)
		output << "\n\t\t\t\t";
	else
		output << '\t';

	return 1;
}

int CStrlResource::LoadFromText(std::istream & input)
{
	int iCount;

	input >> iCount;

	input.ignore(1);

	m_vStrings.resize(iCount);

	int i;

	char szBuffer[256];

	for(i = 0; i < iCount; i++)
	{
		ReadTextField(input, szBuffer, 256);

		m_vStrings[i] = szBuffer;
	}

	while((input.peek() == '\t') || (input.peek() == '\n'))
		input.ignore(1);

	return 1;
}

int CStrlResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "str# ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_STRL_EDIT1, CCONTROL_TYPE_INT, IDS_STRING1024);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_STRL_EDIT2, CCONTROL_TYPE_STR256, IDS_STRING1025);
	m_controls[1].SetString(m_szName);

	HWND hwndStringList = GetDlgItem(hwnd, IDC_EDIT_STRL_LIST1);

	ListBox_ResetContent(hwndStringList);

	int i;

	for(i = 0; i < m_vStrings.size(); i++)
		ListBox_AddString(hwndStringList, m_vStrings[i].c_str());

	char szString[16];

	strcpy_s(szString, "");

	ListBox_AddString(hwndStringList, szString);

	return 1;
}

int CStrlResource::CloseAndSave(void)
{
	std::string szError;

	if(CEditor::GetCurrentEditor()->IsUniqueResourceID(this, m_controls[0].GetInt()) == 0)
	{
		szError = ToString(m_controls[0].GetInt());
		szError += " is not a unique ";
		szError += g_szResourceTypes[GetType()];
		szError += " ID.  Please enter a unique ID.";

		MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}
	else if((m_controls[0].GetInt() < 128) || (m_controls[0].GetInt() > 32767))
	{
		szError = ToString(m_controls[0].GetInt());
		szError += " is not a valid ID.  Please enter an ID between 128 and 32767 inclusive.";

		MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	int iIDOrNameChanged = 0;

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[1].GetString()) != 0))
		iIDOrNameChanged = 1;

	CErrorLog *pLog = (CErrorLog *)m_pWindow->GetExtraData(1);

	m_iID = m_controls[0].GetInt();

	strcpy_s(m_szName, m_controls[1].GetString());

	HWND hwndStringList = GetDlgItem(m_pWindow->GetHWND(), IDC_EDIT_STRL_LIST1);

	int iCount = ListBox_GetCount(hwndStringList);

	m_vStrings.resize(iCount - 1);

	int iLength;

	char *pString;

	int i;

	for(i = 0; i < iCount - 1; i++)
	{
		iLength = ListBox_GetTextLen(hwndStringList, i);

		pString = NULL;
		pString = new char[iLength + 1];

		if(pString == NULL)
		{
			*pLog << "Error: Unable to allocate " << (iLength + 1) << " bytes for string " << (i + 1) << " in STR# " << m_iID << " (" << m_szName << ")!" << CErrorLog::endl;

			continue;
		}

		ListBox_GetText(hwndStringList, i, pString);

		pString[iLength] = '\0';

		m_vStrings[i] = pString;

		delete [] pString;

		if(m_vStrings[i].size() > 255)
			m_vStrings[i].resize(255);
	}

	for(i = 0; i < NUM_STRL_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CStrlResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_STRL_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

int CStrlResource::AddString(void)
{
	HWND hwndStringList = GetDlgItem(m_pWindow->GetHWND(), IDC_EDIT_STRL_LIST1);

	int iSelection = ListBox_GetCurSel(hwndStringList);

	char szString[16];

	strcpy_s(szString, "");

	ListBox_InsertString(hwndStringList, iSelection, szString);

	if(iSelection == -1)
		iSelection = ListBox_GetCount(hwndStringList) - 2;

	ListBox_SetCurSel(hwndStringList, iSelection);

	EditString();

	return 1;
}

int CStrlResource::EditString(void)
{
	HWND hwndStringList = GetDlgItem(m_pWindow->GetHWND(), IDC_EDIT_STRL_LIST1);

	int iSelection = ListBox_GetCurSel(hwndStringList);

	int iCount = ListBox_GetCount(hwndStringList);

	int iFlag = 0;

	if((iSelection == -1) || (iSelection == iCount - 1))
	{
		char szString[16];

		strcpy_s(szString, "");

		ListBox_InsertString(hwndStringList, iSelection, szString);

		iSelection = ListBox_GetCount(hwndStringList) - 2;

		iFlag = 1;
	}

	m_iCurString = iSelection;

	m_iWasSaved = 0;

	m_wndEditString.SetExtraData(0, m_pWindow->GetExtraData(0));
	m_wndEditString.SetExtraData(1, m_pWindow->GetExtraData(1));
	m_wndEditString.SetExtraData(2, (int)this);
	m_wndEditString.SetDlgProc(CStrlResource::StrlStrDlgProc);
	m_wndEditString.CreateAsDialog(m_pWindow->GetInstance(), IDD_EDIT_STRL_STR, 1, m_pWindow);

	if((iFlag) && (!m_iWasSaved))
		ListBox_DeleteString(hwndStringList, iSelection);

	m_iCurString = -1;

	return 1;
}

int CStrlResource::MoveUp(void)
{
	CErrorLog *pLog = (CErrorLog *)m_pWindow->GetExtraData(1);

	HWND hwndStringList = GetDlgItem(m_pWindow->GetHWND(), IDC_EDIT_STRL_LIST1);

	int iSelection = ListBox_GetCurSel(hwndStringList);

	int iCount = ListBox_GetCount(hwndStringList);

	char *pString = NULL;

	int iLength;

	if((iSelection >= 1) && (iSelection < iCount - 1))
	{
		iLength = ListBox_GetTextLen(hwndStringList, iSelection);

		pString = new char[iLength + 1];

		if(pString == NULL)
		{
			*pLog << "Error: Unable to allocate " << iLength << " bytes for temporary string." << CErrorLog::endl;
		}
		else
		{
			ListBox_GetText(hwndStringList, iSelection, pString);

			pString[iLength] = '\0';

			ListBox_DeleteString(hwndStringList, iSelection);
			ListBox_InsertString(hwndStringList, iSelection - 1, pString);
			ListBox_SetCurSel(hwndStringList, iSelection - 1);

			delete [] pString;
		}
	}

	return 1;
}

int CStrlResource::MoveDown(void)
{
	CErrorLog *pLog = (CErrorLog *)m_pWindow->GetExtraData(1);

	HWND hwndStringList = GetDlgItem(m_pWindow->GetHWND(), IDC_EDIT_STRL_LIST1);

	int iSelection = ListBox_GetCurSel(hwndStringList);

	char *pString = NULL;

	int iLength;

	if((iSelection >= 0) && (iSelection < ListBox_GetCount(hwndStringList) - 2))
	{
		iLength = ListBox_GetTextLen(hwndStringList, iSelection);

		pString = new char[iLength + 1];

		if(pString == NULL)
		{
			*pLog << "Error: Unable to allocate " << iLength << " bytes for temporary string." << CErrorLog::endl;
		}
		else
		{
			ListBox_GetText(hwndStringList, iSelection, pString);

			pString[iLength] = '\0';

			ListBox_DeleteString(hwndStringList, iSelection);
			ListBox_InsertString(hwndStringList, iSelection + 1, pString);
			ListBox_SetCurSel(hwndStringList, iSelection + 1);

			delete [] pString;
		}
	}

	return 1;
}

int CStrlResource::EditCut(void)
{
	EditCopy();
	EditDelete();

	return 1;
}

int CStrlResource::EditCopy(void)
{
	HWND hwndStringList = GetDlgItem(m_pWindow->GetHWND(), IDC_EDIT_STRL_LIST1);

	int iSelection = ListBox_GetCurSel(hwndStringList);

	int iCount = ListBox_GetCount(hwndStringList);

	if((iSelection == -1) || (iSelection == iCount - 1))
		return 0;

	int iSize = ListBox_GetTextLen(hwndStringList, iSelection);

	if(OpenClipboard(m_pWindow->GetHWND()) == 0)
		return 0;

	EmptyClipboard();

	HGLOBAL hGlobalMem = GlobalAlloc(GMEM_MOVEABLE, (iSize + 1) * sizeof(char));

	if(hGlobalMem == NULL)
	{
		CloseClipboard();

		return 0;
	}

	char *pMemPtr = (char *)GlobalLock(hGlobalMem);

	ListBox_GetText(hwndStringList, iSelection, pMemPtr);

	pMemPtr[iSize] = '\0';

	GlobalUnlock(hGlobalMem);

	SetClipboardData(CF_TEXT, hGlobalMem);

	CloseClipboard();

	return 1;
}

int CStrlResource::EditPaste(void)
{
	HWND hwndStringList = GetDlgItem(m_pWindow->GetHWND(), IDC_EDIT_STRL_LIST1);

	int iSelection = ListBox_GetCurSel(hwndStringList);

	if(IsClipboardFormatAvailable(CF_TEXT) == 0)
		return 0;

	if(OpenClipboard(m_pWindow->GetHWND()) == 0)
		return 0;

	HGLOBAL hGlobalMem = GetClipboardData(CF_TEXT);

	if(hGlobalMem == NULL)
	{
		CloseClipboard();

		return 0;
	}

	char *pMemPtr = (char *)GlobalLock(hGlobalMem);

	if(pMemPtr == NULL)
	{
		CloseClipboard();

		return 0;
	}

	if(iSelection == -1)
		iSelection = ListBox_GetCount(hwndStringList) - 1;

	ListBox_InsertString(hwndStringList, iSelection, pMemPtr);

	GlobalUnlock(hGlobalMem);

	CloseClipboard();

	ListBox_SetCurSel(hwndStringList, iSelection);

	return 1;
}

int CStrlResource::EditDelete(void)
{
	HWND hwndStringList = GetDlgItem(m_pWindow->GetHWND(), IDC_EDIT_STRL_LIST1);

	int iSelection = ListBox_GetCurSel(hwndStringList);

	int iCount = ListBox_GetCount(hwndStringList);

	if((iSelection >= 0) && (iSelection < iCount - 1))
	{
		ListBox_DeleteString(hwndStringList, iSelection);
		ListBox_SetCurSel(hwndStringList, iSelection);
	}

	return 1;
}

BOOL CStrlResource::StrlDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow       *pWindow;
	CStrlResource *pResource = NULL;
	CErrorLog     *pLog      = NULL;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CStrlResource *)pWindow->GetExtraData(2);

	pLog = CErrorLog::GetCurrentErrorLog();

	HWND hwndStringList = GetDlgItem(hwnd, IDC_EDIT_STRL_LIST1);

	int i;

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			pResource->Initialize(hwnd);

			return TRUE;

			break;
		}

		case WM_SYSCOMMAND:
		{
			if(wparam == SC_CLOSE)
			{
				pResource->CloseAndDontSave();

				return TRUE;
			}

			break;
		}

		case WM_COMMAND:
		{
			int iNotifyCode = HIWORD(wparam);
			int iControlID  = LOWORD(wparam);

			if(iControlID == IDC_EDIT_STRL_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_STRL_OK)
			{
				pResource->CloseAndSave();
			}
			else if(iControlID == IDC_EDIT_STRL_LIST1)
			{
				if(iNotifyCode == LBN_DBLCLK)
				{
					pResource->EditString();
				}
			}
			else if(iControlID == IDC_EDIT_STRL_BUTTON1)
			{
				pResource->AddString();
			}
			else if(iControlID == IDC_EDIT_STRL_BUTTON2)
			{
				pResource->EditDelete();
			}
			else if(iControlID == IDC_EDIT_STRL_BUTTON3)
			{
				pResource->MoveUp();
			}
			else if(iControlID == IDC_EDIT_STRL_BUTTON4)
			{
				pResource->MoveDown();
			}
			else if(iControlID == IDM_STRL_FILE_CLOSEANDSAVE)
			{
				pResource->CloseAndSave();
			}
			else if(iControlID == IDM_STRL_FILE_CLOSEANDDONTSAVE)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDM_STRL_EDIT_ADDSTRING)
			{
				pResource->AddString();
			}
			else if(iControlID == IDM_STRL_EDIT_EDITSTRING)
			{
				pResource->EditString();
			}
			else if(iControlID == IDM_STRL_EDIT_MOVEUP)
			{
				pResource->MoveUp();
			}
			else if(iControlID == IDM_STRL_EDIT_MOVEDOWN)
			{
				pResource->MoveDown();
			}
			else if(iControlID == IDM_STRL_EDIT_CUT)
			{
				pResource->EditCut();
			}
			else if(iControlID == IDM_STRL_EDIT_COPY)
			{
				pResource->EditCopy();
			}
			else if(iControlID == IDM_STRL_EDIT_PASTE)
			{
				pResource->EditPaste();
			}
			else if(iControlID == IDM_STRL_EDIT_DELETE)
			{
				pResource->EditDelete();
			}
			else
			{
				for(i = 0; i < NUM_STRL_CONTROLS; i++)
				{
					if(iControlID == pResource->m_controls[i].GetControlID())
					{
						pResource->m_controls[i].ProcessMessage(iNotifyCode);

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

BOOL CStrlResource::StrlStrDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow       *pWindow;
	CStrlResource *pResource;
	CErrorLog     *pLog;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CStrlResource *)pWindow->GetExtraData(2);

	pLog = CErrorLog::GetCurrentErrorLog();

	HWND hwndEditString = GetDlgItem(hwnd, IDC_EDIT_STRL_STR_EDIT1);

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			HWND hwndStringList = GetDlgItem(pResource->m_pWindow->GetHWND(), IDC_EDIT_STRL_LIST1);

			char *pString = NULL;

			int iLength;

			iLength = ListBox_GetTextLen(hwndStringList, pResource->m_iCurString);

			pString = new char[iLength + 1];

			if(pString == NULL)
			{
				*pLog << "Error: Unable to allocate " << iLength << " bytes for string." << CErrorLog::endl;
			}
			else
			{
				ListBox_GetText(hwndStringList, pResource->m_iCurString, pString);

				pString[iLength] = '\0';

				Edit_SetText(hwndEditString, pString);

				delete [] pString;
			}

			return TRUE;

			break;
		}

		case WM_SYSCOMMAND:
		{
			if(wparam == SC_CLOSE)
			{
				EndDialog(hwnd, 0);

				return TRUE;
			}

			break;
		}

		case WM_COMMAND:
		{
			int iNotifyCode = HIWORD(wparam);
			int iControlID  = LOWORD(wparam);

			if(iControlID == IDC_EDIT_STRL_STR_CANCEL)
			{
				EndDialog(hwnd, 0);
			}
			else if(iControlID == IDC_EDIT_STRL_STR_OK)
			{
				char *pString;

				int iLength;

				iLength = Edit_GetTextLength(hwndEditString);

				pString = new char[iLength + 1];

				if(pString == NULL)
				{
					*pLog << "Error: Unable to allocate " << iLength << " bytes for string." << CErrorLog::endl;
				}
				else
				{
					Edit_GetText(hwndEditString, pString, iLength + 1);

					pString[iLength] = '\0';

					HWND hwndStringList = GetDlgItem(pResource->m_pWindow->GetHWND(), IDC_EDIT_STRL_LIST1);

					ListBox_DeleteString(hwndStringList, pResource->m_iCurString);
					ListBox_InsertString(hwndStringList, pResource->m_iCurString, pString);

					delete [] pString;

					pResource->m_iWasSaved = 1;
				}

				EndDialog(hwnd, 1);
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
