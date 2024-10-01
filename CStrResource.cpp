// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CStrResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CStrResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CStrResource::CStrResource(void)
{
	memset(m_szString, 0, 256 * sizeof(char));
}

CStrResource::~CStrResource(void)
{

}

int CStrResource::GetType(void)
{
	return CNR_TYPE_STR;
}

int CStrResource::GetSize(void)
{
	int iSize = strlen(m_szString) + 1;

	if(iSize & 1)
		iSize++;

	return iSize;
}

int CStrResource::GetDialogID(void)
{
	return IDD_EDIT_STR;
}

DLGPROCNOCALLBACK CStrResource::GetDialogProc(void)
{
	return StrDlgProc;
}

int CStrResource::GetNumFields(void)
{
	return NUM_STR_FIELDS;
}

const std::string * CStrResource::GetFieldNames(void)
{
	return g_szStrFields;
}

int CStrResource::Save(char *pOutput)
{
	ToMacString(m_szString);

	UCHAR ucStringLength = (UCHAR)strlen(m_szString);

	*pOutput = ucStringLength; pOutput++;

	memcpy(pOutput, m_szString, (int)ucStringLength * sizeof(char)); pOutput += (int)ucStringLength * sizeof(char);

	if((ucStringLength + 1) & 1)
	{
		*pOutput = 0x00; pOutput++;
	}

	ToWinString(m_szString);

	return 1;
}

int CStrResource::Load(char *pInput, int iSize)
{
	UCHAR ucStringLength;

	ucStringLength = *pInput; pInput++;

	memcpy(m_szString, pInput, (int)ucStringLength * sizeof(char)); pInput += (int)ucStringLength * sizeof(char);

	m_szString[ucStringLength] = '\0';

	ToWinString(m_szString);

	return 1;
}

int CStrResource::SaveToText(std::ostream & output)
{
	PrintTextField(output, m_szString, '\t');

	return 1;
}

int CStrResource::LoadFromText(std::istream & input)
{
	ReadTextField(input, m_szString, 256);

	return 1;
}

int CStrResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "str ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_STR_EDIT1, CCONTROL_TYPE_INT, IDS_STRING1056);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_STR_EDIT2, CCONTROL_TYPE_STR256, IDS_STRING1057);
	m_controls[1].SetString(m_szName);
	m_controls[2].Create(hwnd, IDC_EDIT_STR_EDIT3, CCONTROL_TYPE_STR255, IDS_STRING1058);
	m_controls[2].SetString(m_szString);

	return 1;
}

int CStrResource::CloseAndSave(void)
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

	strcpy(m_szName, m_controls[1].GetString());

	strcpy(m_szString, m_controls[2].GetString());

	int i;

	for(i = 0; i < NUM_STR_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CStrResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_STR_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CStrResource::StrDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow      *pWindow;
	CStrResource *pResource = NULL;
	CErrorLog    *pLog      = NULL;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CStrResource *)pWindow->GetExtraData(2);

	pLog = CErrorLog::GetCurrentErrorLog();

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

			if(iControlID == IDC_EDIT_STR_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_STR_OK)
			{
				pResource->CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_STR_CONTROLS; i++)
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
