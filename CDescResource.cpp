// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CDescResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CDescResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CDescResource::CDescResource(void)
{
	m_szDescription = "";

	m_iGraphics = 0;

	memset(m_szMovieFile, 0, 32 * sizeof(char));

	m_iFlags = 0x0000;
}

CDescResource::~CDescResource(void)
{

}

int CDescResource::GetType(void)
{
	return CNR_TYPE_DESC;
}

int CDescResource::GetSize(void)
{
	int iSize = 37;

	int i;

	for(i = 0; i < m_szDescription.size(); i++)
	{
		if(m_szDescription[i] != '\r')
			iSize++;
	}

	return iSize;
}

int CDescResource::GetDialogID(void)
{
	return IDD_EDIT_DESC;
}

DLGPROCNOCALLBACK CDescResource::GetDialogProc(void)
{
	return DescDlgProc;
}

int CDescResource::GetNumFields(void)
{
	return NUM_DESC_FIELDS;
}

const std::string * CDescResource::GetFieldNames(void)
{
	return g_szDescFields;
}

int CDescResource::Save(char *pOutput)
{
	SwapEndians();

	FixNewlines(0x0D, 0);

	ToMacString(m_szDescription);

	memcpy(pOutput, m_szDescription.c_str(), m_szDescription.size() * sizeof(char)); pOutput += m_szDescription.size();

	ToWinString(m_szDescription);

	*pOutput = '\0'; pOutput += sizeof(char);

	*(short *)pOutput = m_iGraphics; pOutput += sizeof(short);

	memcpy(pOutput, m_szMovieFile, 32 * sizeof(char)); pOutput += 32 * sizeof(char);

	*(USHORT *)pOutput = m_iFlags; pOutput += sizeof(USHORT);

	SwapEndians();

	FixNewlines(0x0D, 1);

	return 1;
}

int CDescResource::Load(char *pInput, int iSize)
{
	int iTextSize = iSize - 37;

	m_szDescription = pInput; pInput += (iTextSize + 1) * sizeof(char);

	ToWinString(m_szDescription);

	m_iGraphics = *(short *)pInput; pInput += sizeof(short);

	memcpy(m_szMovieFile, pInput, 32 * sizeof(char)); pInput += 32 * sizeof(char);

	m_iFlags = *(USHORT *)pInput; pInput += sizeof(USHORT);

	SwapEndians();

	FixNewlines(0x0D, 1);

	return 1;
}

int CDescResource::SwapEndians(void)
{
	m_iGraphics = SwapEndianShort(m_iGraphics);
	m_iFlags    = SwapEndianShort(m_iFlags);

	return 1;
}

int CDescResource::SaveToText(std::ostream & output)
{
	FixNewlines('\n', 0);

	PrintTextField(output, m_szDescription.c_str(), '\t');

	FixNewlines('\n', 1);

	output << m_iGraphics << '\t';

	PrintTextField(output, m_szMovieFile, '\t');

	PrintHex16Field(output, (char *)&m_iFlags, '\t');

	return 1;
}

int CDescResource::LoadFromText(std::istream & input)
{
	static char s_szBuffer[8192];

	ReadTextField(input, s_szBuffer, 8192);

	m_szDescription = s_szBuffer;

	FixNewlines('\n', 1);

	input >> m_iGraphics;

	input.ignore(1);

	ReadTextField(input, m_szMovieFile, 32);

	ReadHex16Field(input, (char *)&m_iFlags);

	return 1;
}

int CDescResource::FixNewlines(char cReplace, int iAdd)
{
	int i;

	if(m_szDescription.size() == 0)
		return 1;

	if(iAdd == 1)
	{
		for(i = 0; i < m_szDescription.size(); i++)
		{
			if(m_szDescription[i] == cReplace)
			{
				m_szDescription.insert(m_szDescription.begin() + i, '\r');
				m_szDescription[i + 1] = '\n';

				i++;
			}
		}
	}
	else
	{
		for(i = 0; i < m_szDescription.size() - 1; i++)
		{
			if((m_szDescription[i] == '\r') && (m_szDescription[i + 1] == '\n'))
			{
				m_szDescription.erase(m_szDescription.begin() + i);

				m_szDescription[i] = cReplace;
			}
		}
	}

	return 1;
}

int CDescResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "desc ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_DESC_EDIT1, CCONTROL_TYPE_INT, IDS_STRING208);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_DESC_EDIT2, CCONTROL_TYPE_STRARB, -1);
	m_controls[1].SetString(m_szDescription.c_str());
	m_controls[2].Create(hwnd, IDC_EDIT_DESC_EDIT3, CCONTROL_TYPE_INT, IDS_STRING210);
	m_controls[2].SetInt(m_iGraphics);
	m_controls[3].Create(hwnd, IDC_EDIT_DESC_EDIT4, CCONTROL_TYPE_STR255, IDS_STRING211);
	m_controls[3].SetString(m_szMovieFile);
	m_controls[4].Create(hwnd, IDC_EDIT_DESC_CHECK1, CCONTROL_TYPE_CHECK, IDS_STRING212);
	m_controls[4].SetInt(m_iFlags & 0x0001);
	m_controls[5].Create(hwnd, IDC_EDIT_DESC_CHECK2, CCONTROL_TYPE_CHECK, IDS_STRING213);
	m_controls[5].SetInt(m_iFlags & 0x0002);
	m_controls[6].Create(hwnd, IDC_EDIT_DESC_CHECK3, CCONTROL_TYPE_CHECK, IDS_STRING214);
	m_controls[6].SetInt(m_iFlags & 0x0004);
	m_controls[7].Create(hwnd, IDC_EDIT_DESC_EDIT5, CCONTROL_TYPE_STR256, IDS_STRING215);
	m_controls[7].SetString(m_szName);

	return 1;
}

int CDescResource::CloseAndSave(void)
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

	m_iID = m_controls[0].GetInt();

	m_szDescription = m_controls[1].GetString();

	m_iGraphics = m_controls[2].GetInt();

	strcpy(m_szMovieFile, m_controls[3].GetString());

	m_iFlags = 0x0000;

	m_iFlags |= m_controls[4].GetInt() << 0;
	m_iFlags |= m_controls[5].GetInt() << 1;
	m_iFlags |= m_controls[6].GetInt() << 2;

	strcpy(m_szName, m_controls[7].GetString());

	int i;

	for(i = 0; i < NUM_DESC_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CDescResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_DESC_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CDescResource::DescDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CDescResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CDescResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_DESC_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_DESC_OK)
			{
				pResource->CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_DESC_CONTROLS; i++)
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
