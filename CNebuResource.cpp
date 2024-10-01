// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CNebuResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CNebuResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CNebuResource::CNebuResource(void)
{
	m_iXPosition = 0;
	m_iYPosition = 0;

	m_iXSize = 0;
	m_iYSize = 0;

	memset(m_szActiveOn,  0, 255 * sizeof(char));
	memset(m_szOnExplore, 0, 255 * sizeof(char));
}

CNebuResource::~CNebuResource(void)
= default;

int CNebuResource::GetType(void)
{
	return CNR_TYPE_NEBU;
}

int CNebuResource::GetSize(void)
{
	return 534;
}

int CNebuResource::GetDialogID(void)
{
	return IDD_EDIT_NEBU;
}

DLGPROCNOCALLBACK CNebuResource::GetDialogProc(void)
{
	return NebuDlgProc;
}

int CNebuResource::GetNumFields(void)
{
	return NUM_NEBU_FIELDS;
}

const std::string * CNebuResource::GetFieldNames(void)
{
	return g_szNebuFields;
}

int CNebuResource::Save(char *pOutput)
{
	SwapEndians();

	*(short *)pOutput = m_iXPosition; pOutput += sizeof(short);
	*(short *)pOutput = m_iYPosition; pOutput += sizeof(short);
	*(short *)pOutput = m_iXSize;     pOutput += sizeof(short);
	*(short *)pOutput = m_iYSize;     pOutput += sizeof(short);

	memcpy(pOutput, m_szActiveOn,  255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_szOnExplore, 255 * sizeof(char)); pOutput += 255 * sizeof(char);

	SwapEndians();

	return 1;
}

int CNebuResource::Load(char *pInput, int iSize)
{
	m_iXPosition = *(short *)pInput; pInput += sizeof(short);
	m_iYPosition = *(short *)pInput; pInput += sizeof(short);
	m_iXSize     = *(short *)pInput; pInput += sizeof(short);
	m_iYSize     = *(short *)pInput; pInput += sizeof(short);

	memcpy(m_szActiveOn,  pInput, 255 * sizeof(char)); pInput += sizeof(char);
	memcpy(m_szOnExplore, pInput, 255 * sizeof(char)); pInput += sizeof(char);

	SwapEndians();

	return 1;
}

int CNebuResource::SwapEndians(void)
{
	m_iXPosition = SwapEndianShort(m_iXPosition);
	m_iYPosition = SwapEndianShort(m_iYPosition);
	m_iXSize     = SwapEndianShort(m_iXSize);
	m_iYSize     = SwapEndianShort(m_iYSize);

	return 1;
}

int CNebuResource::SaveToText(std::ostream & output)
{
	output << m_iXPosition << '\t'
		   << m_iYPosition << '\t'
		   << m_iXSize     << '\t'
		   << m_iYSize     << '\t';

	PrintTextField(output, m_szActiveOn,  '\t');
	PrintTextField(output, m_szOnExplore, '\t');

	return 1;
}

int CNebuResource::LoadFromText(std::istream & input)
{
	input >> m_iXPosition
		  >> m_iYPosition
		  >> m_iXSize
		  >> m_iYSize;

	input.ignore(1);

	ReadTextField(input, m_szActiveOn,  255);
	ReadTextField(input, m_szOnExplore, 255);

	return 1;
}

int CNebuResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "nebu ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_NEBU_EDIT1, CCONTROL_TYPE_INT, IDS_STRING480);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_NEBU_EDIT2, CCONTROL_TYPE_INT, IDS_STRING481);
	m_controls[1].SetInt(m_iXPosition);
	m_controls[2].Create(hwnd, IDC_EDIT_NEBU_EDIT3, CCONTROL_TYPE_INT, IDS_STRING481);
	m_controls[2].SetInt(m_iYPosition);
	m_controls[3].Create(hwnd, IDC_EDIT_NEBU_EDIT4, CCONTROL_TYPE_INT, IDS_STRING482);
	m_controls[3].SetInt(m_iXSize);
	m_controls[4].Create(hwnd, IDC_EDIT_NEBU_EDIT5, CCONTROL_TYPE_INT, IDS_STRING482);
	m_controls[4].SetInt(m_iYSize);
	m_controls[5].Create(hwnd, IDC_EDIT_NEBU_EDIT6, CCONTROL_TYPE_STR255, IDS_STRING483);
	m_controls[5].SetString(m_szActiveOn);
	m_controls[6].Create(hwnd, IDC_EDIT_NEBU_EDIT7, CCONTROL_TYPE_STR255, IDS_STRING484);
	m_controls[6].SetString(m_szOnExplore);
	m_controls[7].Create(hwnd, IDC_EDIT_NEBU_EDIT8, CCONTROL_TYPE_STR256, IDS_STRING485);
	m_controls[7].SetString(m_szName);

	std::string szText = "PICT IDs: ";
	szText += ToString(9500 + (m_iID - 128) * 7);
	szText += " to ";
	szText += ToString(9500 + (m_iID - 128) * 7 + 6);

	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_NEBU_TEXT9), szText.c_str());

	return 1;
}

int CNebuResource::CloseAndSave(void)
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
	m_iXPosition = m_controls[1].GetInt();
	m_iYPosition = m_controls[2].GetInt();
	m_iXSize     = m_controls[3].GetInt();
	m_iYSize     = m_controls[4].GetInt();

	strcpy_s(m_szActiveOn,  m_controls[5].GetString());
	strcpy_s(m_szOnExplore, m_controls[6].GetString());

	strcpy_s(m_szName, m_controls[7].GetString());

	int i;

	for(i = 0; i < NUM_NEBU_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CNebuResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_NEBU_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CNebuResource::NebuDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CNebuResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CNebuResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_NEBU_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_NEBU_OK)
			{
				pResource->CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_NEBU_CONTROLS; i++)
				{
					if(iControlID == pResource->m_controls[i].GetControlID())
					{
						pResource->m_controls[i].ProcessMessage(iNotifyCode);

						break;
					}
				}
			}

			if((iControlID == IDC_EDIT_NEBU_EDIT1) && (iNotifyCode == EN_CHANGE))
			{
				if((pResource->m_controls[0].GetInt() >= 128) && (pResource->m_controls[0].GetInt() < 160))
				{
					std::string szText = "PICT IDs: ";
					szText += ToString(9500 + (pResource->m_controls[0].GetInt() - 128) * 7);
					szText += " to ";
					szText += ToString(9500 + (pResource->m_controls[0].GetInt() - 128) * 7 + 6);

					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_NEBU_TEXT9), szText.c_str());
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
