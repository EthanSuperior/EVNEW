// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CBoomResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CBoomResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CBoomResource::CBoomResource(void)
{
	m_iFrameAdvance  = 1;
	m_iSoundIndex    = 0;
	m_iGraphicsIndex = 0;
}

CBoomResource::~CBoomResource(void)
{

}

int CBoomResource::GetType(void)
{
	return CNR_TYPE_BOOM;
}

int CBoomResource::GetSize(void)
{
	return 6;
}

int CBoomResource::GetDialogID(void)
{
	return IDD_EDIT_BOOM;
}

DLGPROCNOCALLBACK CBoomResource::GetDialogProc(void)
{
	return BoomDlgProc;
}

int CBoomResource::GetNumFields(void)
{
	return NUM_BOOM_FIELDS;
}

const std::string * CBoomResource::GetFieldNames(void)
{
	return g_szBoomFields;
}

int CBoomResource::Save(char *pOutput)
{
	SwapEndians();

	*(short *)pOutput = m_iFrameAdvance;  pOutput += sizeof(short);
	*(short *)pOutput = m_iSoundIndex;    pOutput += sizeof(short);
	*(short *)pOutput = m_iGraphicsIndex; pOutput += sizeof(short);

	SwapEndians();

	return 1;
}

int CBoomResource::Load(char *pInput, int iSize)
{
	m_iFrameAdvance  = *(short *)pInput; pInput += sizeof(short);
	m_iSoundIndex    = *(short *)pInput; pInput += sizeof(short);
	m_iGraphicsIndex = *(short *)pInput; pInput += sizeof(short);

	SwapEndians();

	return 1;
}

int CBoomResource::SwapEndians(void)
{
	m_iFrameAdvance  = SwapEndianShort(m_iFrameAdvance);
	m_iSoundIndex    = SwapEndianShort(m_iSoundIndex);
	m_iGraphicsIndex = SwapEndianShort(m_iGraphicsIndex);

	return 1;
}

int CBoomResource::SaveToText(std::ostream & output)
{
	output << m_iFrameAdvance  << '\t'
		   << m_iSoundIndex    << '\t'
		   << m_iGraphicsIndex << '\t';

	return 1;
}

int CBoomResource::LoadFromText(std::istream & input)
{
	input >> m_iFrameAdvance
		  >> m_iSoundIndex
		  >> m_iGraphicsIndex;

	input.ignore(1);

	return 1;
}

int CBoomResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "boom ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_BOOM_EDIT1, CCONTROL_TYPE_INT, IDS_STRING96);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_BOOM_EDIT2, CCONTROL_TYPE_INT, IDS_STRING97);
	m_controls[1].SetInt(m_iFrameAdvance);
	m_controls[2].Create(hwnd, IDC_EDIT_BOOM_EDIT3, CCONTROL_TYPE_INT, IDS_STRING98);
	m_controls[2].SetInt(m_iSoundIndex);
	m_controls[3].Create(hwnd, IDC_EDIT_BOOM_EDIT4, CCONTROL_TYPE_INT, IDS_STRING99);
	m_controls[3].SetInt(m_iGraphicsIndex);
	m_controls[4].Create(hwnd, IDC_EDIT_BOOM_EDIT5, CCONTROL_TYPE_STR256, IDS_STRING100);
	m_controls[4].SetString(m_szName);

	return 1;
}

int CBoomResource::CloseAndSave(void)
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

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[4].GetString()) != 0))
		iIDOrNameChanged = 1;

	m_iID            = m_controls[0].GetInt();
	m_iFrameAdvance  = m_controls[1].GetInt();
	m_iSoundIndex    = m_controls[2].GetInt();
	m_iGraphicsIndex = m_controls[3].GetInt();

	strcpy_s(m_szName, m_controls[4].GetString());

	int i;

	for(i = 0; i < NUM_BOOM_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CBoomResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_BOOM_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CBoomResource::BoomDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CBoomResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CBoomResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_BOOM_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_BOOM_OK)
			{
				pResource->CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_BOOM_CONTROLS; i++)
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
