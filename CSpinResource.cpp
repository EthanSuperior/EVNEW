// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CNovaResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CSpinResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CSpinResource::CSpinResource(void)
{
	m_iSpritesID = 0;
	m_iMaskID    = 0;
	m_iXSize     = 0;
	m_iYSize     = 0;
	m_iXTiles    = 0;
	m_iYTiles    = 0;
}

CSpinResource::~CSpinResource(void)
= default;

int CSpinResource::GetType(void)
{
	return CNR_TYPE_SPIN;
}

int CSpinResource::GetSize(void)
{
	return 12;
}

int CSpinResource::GetDialogID(void)
{
	return IDD_EDIT_SPIN;
}

DLGPROCNOCALLBACK CSpinResource::GetDialogProc(void)
{
	return SpinDlgProc;
}

int CSpinResource::GetNumFields(void)
{
	return NUM_SPIN_FIELDS;
}

const std::string * CSpinResource::GetFieldNames(void)
{
	return g_szSpinFields;
}

int CSpinResource::Save(char *pOutput)
{
	SwapEndians();

	*(short *)pOutput = m_iSpritesID; pOutput += sizeof(short);
	*(short *)pOutput = m_iMaskID;    pOutput += sizeof(short);
	*(short *)pOutput = m_iXSize;     pOutput += sizeof(short);
	*(short *)pOutput = m_iYSize;     pOutput += sizeof(short);
	*(short *)pOutput = m_iXTiles;    pOutput += sizeof(short);
	*(short *)pOutput = m_iYTiles;    pOutput += sizeof(short);

	SwapEndians();

	return 1;
}

int CSpinResource::Load(char *pInput, int iSize)
{
	m_iSpritesID = *(short *)pInput; pInput += sizeof(short);
	m_iMaskID    = *(short *)pInput; pInput += sizeof(short);
	m_iXSize     = *(short *)pInput; pInput += sizeof(short);
	m_iYSize     = *(short *)pInput; pInput += sizeof(short);
	m_iXTiles    = *(short *)pInput; pInput += sizeof(short);
	m_iYTiles    = *(short *)pInput; pInput += sizeof(short);

	SwapEndians();

	return 1;
}

int CSpinResource::SwapEndians(void)
{
	m_iSpritesID = SwapEndianShort(m_iSpritesID);
	m_iMaskID    = SwapEndianShort(m_iMaskID);
	m_iXSize     = SwapEndianShort(m_iXSize);
	m_iYSize     = SwapEndianShort(m_iYSize);
	m_iXTiles    = SwapEndianShort(m_iXTiles);
	m_iYTiles    = SwapEndianShort(m_iYTiles);

	return 1;
}

int CSpinResource::SaveToText(std::ostream & output)
{
	output << m_iSpritesID << '\t'
		   << m_iMaskID    << '\t'
		   << m_iXSize     << '\t'
		   << m_iYSize     << '\t'
		   << m_iXTiles    << '\t'
		   << m_iYTiles    << '\t';

	return 1;
}

int CSpinResource::LoadFromText(std::istream & input)
{
	input >> m_iSpritesID
		  >> m_iMaskID
		  >> m_iXSize
		  >> m_iYSize
		  >> m_iXTiles
		  >> m_iYTiles;

	input.ignore(1);

	return 1;
}

int CSpinResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "spin ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_SPIN_EDIT1, CCONTROL_TYPE_INT, IDS_STRING1);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_SPIN_EDIT2, CCONTROL_TYPE_INT, IDS_STRING2);
	m_controls[1].SetInt(m_iSpritesID);
	m_controls[2].Create(hwnd, IDC_EDIT_SPIN_EDIT3, CCONTROL_TYPE_INT, IDS_STRING3);
	m_controls[2].SetInt(m_iMaskID);
	m_controls[3].Create(hwnd, IDC_EDIT_SPIN_EDIT4, CCONTROL_TYPE_INT, IDS_STRING4);
	m_controls[3].SetInt(m_iXSize);
	m_controls[4].Create(hwnd, IDC_EDIT_SPIN_EDIT5, CCONTROL_TYPE_INT, IDS_STRING5);
	m_controls[4].SetInt(m_iYSize);
	m_controls[5].Create(hwnd, IDC_EDIT_SPIN_EDIT6, CCONTROL_TYPE_INT, IDS_STRING6);
	m_controls[5].SetInt(m_iXTiles);
	m_controls[6].Create(hwnd, IDC_EDIT_SPIN_EDIT7, CCONTROL_TYPE_INT, IDS_STRING7);
	m_controls[6].SetInt(m_iYTiles);
	m_controls[7].Create(hwnd, IDC_EDIT_SPIN_EDIT8, CCONTROL_TYPE_STR256, IDS_STRING8);
	m_controls[7].SetString(m_szName);

	return 1;
}

int CSpinResource::CloseAndSave(void)
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

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[7].GetString()) != 0))
		iIDOrNameChanged = 1;

	m_iID        = m_controls[0].GetInt();
	m_iSpritesID = m_controls[1].GetInt();
	m_iMaskID    = m_controls[2].GetInt();
	m_iXSize     = m_controls[3].GetInt();
	m_iYSize     = m_controls[4].GetInt();
	m_iXTiles    = m_controls[5].GetInt();
	m_iYTiles    = m_controls[6].GetInt();

	strcpy_s(m_szName, m_controls[7].GetString());

	int i;

	for(i = 0; i < NUM_SPIN_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CSpinResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_SPIN_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CSpinResource::SpinDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CSpinResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CSpinResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_SPIN_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_SPIN_OK)
			{
				pResource->CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_SPIN_CONTROLS; i++)
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
