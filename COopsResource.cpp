// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File COopsResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "COopsResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

COopsResource::COopsResource(void)
{
	m_iStellar    = -2;
	m_iCommodity  =  0;
	m_iPriceDelta =  0;
	m_iDuration   =  0;
	m_iRandom     =  0;

	memset(m_szActiveOn, 0, 256 * sizeof(char));
}

COopsResource::~COopsResource(void)
{

}

int COopsResource::GetType(void)
{
	return CNR_TYPE_OOPS;
}

int COopsResource::GetSize(void)
{
	return 282;
}

int COopsResource::GetDialogID(void)
{
	return IDD_EDIT_OOPS;
}

DLGPROCNOCALLBACK COopsResource::GetDialogProc(void)
{
	return OopsDlgProc;
}

int COopsResource::GetNumFields(void)
{
	return NUM_OOPS_FIELDS;
}

const std::string * COopsResource::GetFieldNames(void)
{
	return g_szOopsFields;
}

int COopsResource::Save(char *pOutput)
{
	SwapEndians();

	*(short *)pOutput = m_iStellar;    pOutput += sizeof(short);
	*(short *)pOutput = m_iCommodity;  pOutput += sizeof(short);
	*(short *)pOutput = m_iPriceDelta; pOutput += sizeof(short);
	*(short *)pOutput = m_iDuration;   pOutput += sizeof(short);
	*(short *)pOutput = m_iRandom;     pOutput += sizeof(short);

	memcpy(pOutput, m_szActiveOn, 256 * sizeof(char)); pOutput += 256 * sizeof(char);

	SwapEndians();

	return 1;
}

int COopsResource::Load(char *pInput, int iSize)
{
	m_iStellar    = *(short *)pInput; pInput += sizeof(short);
	m_iCommodity  = *(short *)pInput; pInput += sizeof(short);
	m_iPriceDelta = *(short *)pInput; pInput += sizeof(short);
	m_iDuration   = *(short *)pInput; pInput += sizeof(short);
	m_iRandom     = *(short *)pInput; pInput += sizeof(short);

	memcpy(m_szActiveOn, pInput, 256 * sizeof(char)); pInput += 256 * sizeof(char);

	SwapEndians();

	return 1;
}

int COopsResource::SwapEndians(void)
{
	m_iStellar    = SwapEndianShort(m_iStellar);
	m_iCommodity  = SwapEndianShort(m_iCommodity);
	m_iPriceDelta = SwapEndianShort(m_iPriceDelta);
	m_iDuration   = SwapEndianShort(m_iDuration);
	m_iRandom     = SwapEndianShort(m_iRandom);

	return 1;
}

int COopsResource::SaveToText(std::ostream & output)
{
	output << m_iStellar    << '\t'
		   << m_iCommodity  << '\t'
		   << m_iPriceDelta << '\t'
		   << m_iDuration   << '\t'
		   << m_iRandom     << '\t';

	PrintTextField(output, m_szActiveOn, '\t');

	return 1;
}

int COopsResource::LoadFromText(std::istream & input)
{
	input >> m_iStellar
		  >> m_iCommodity
		  >> m_iPriceDelta
		  >> m_iDuration
		  >> m_iRandom;

	input.ignore(1);

	ReadTextField(input, m_szActiveOn, 256);

	return 1;
}

int COopsResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "oops ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_OOPS_EDIT1, CCONTROL_TYPE_INT, IDS_STRING496);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_OOPS_EDIT2, CCONTROL_TYPE_INT, IDS_STRING497);
	m_controls[1].SetInt(m_iStellar);
	m_controls[2].Create(hwnd, IDC_EDIT_OOPS_EDIT3, CCONTROL_TYPE_INT, IDS_STRING498);
	m_controls[2].SetInt(m_iCommodity);
	m_controls[3].Create(hwnd, IDC_EDIT_OOPS_EDIT4, CCONTROL_TYPE_INT, IDS_STRING499);
	m_controls[3].SetInt(m_iPriceDelta);
	m_controls[4].Create(hwnd, IDC_EDIT_OOPS_EDIT5, CCONTROL_TYPE_INT, IDS_STRING500);
	m_controls[4].SetInt(m_iDuration);
	m_controls[5].Create(hwnd, IDC_EDIT_OOPS_EDIT6, CCONTROL_TYPE_INT, IDS_STRING501);
	m_controls[5].SetInt(m_iRandom);
	m_controls[6].Create(hwnd, IDC_EDIT_OOPS_EDIT7, CCONTROL_TYPE_STR256, IDS_STRING502);
	m_controls[6].SetString(m_szActiveOn);
	m_controls[7].Create(hwnd, IDC_EDIT_OOPS_EDIT8, CCONTROL_TYPE_STR256, IDS_STRING503);
	m_controls[7].SetString(m_szName);

	return 1;
}

int COopsResource::CloseAndSave(void)
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

	m_iID         = m_controls[0].GetInt();
	m_iStellar    = m_controls[1].GetInt();
	m_iCommodity  = m_controls[2].GetInt();
	m_iPriceDelta = m_controls[3].GetInt();
	m_iDuration   = m_controls[4].GetInt();
	m_iRandom     = m_controls[5].GetInt();

	strcpy_s(m_szActiveOn, m_controls[6].GetString());

	strcpy_s(m_szName, m_controls[7].GetString());

	int i;

	for(i = 0; i < NUM_OOPS_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int COopsResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_OOPS_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL COopsResource::OopsDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	COopsResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (COopsResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_OOPS_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_OOPS_OK)
			{
				pResource->CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_OOPS_CONTROLS; i++)
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
