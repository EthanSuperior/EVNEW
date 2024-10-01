// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CFletResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CFletResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CFletResource::CFletResource(void)
{
	m_iLeadShipType = 0;

	int i;

	for(i = 0; i < 4; i++)
	{
		m_iEscortTypes[i] = 0;
		m_iMinEscorts[i]  = 0;
		m_iMaxEscorts[i]  = 0;
	}

	m_iGovernment = -1;

	m_iSystem = -1;

	memset(m_szAppearOn, 0, 256 * sizeof(char));

	m_iQuote = -1;

	m_iFlags = 0x0000;
}

CFletResource::~CFletResource(void)
{

}

int CFletResource::GetType(void)
{
	return CNR_TYPE_FLET;
}

int CFletResource::GetSize(void)
{
	return 306;
}

int CFletResource::GetDialogID(void)
{
	return IDD_EDIT_FLET;
}

DLGPROCNOCALLBACK CFletResource::GetDialogProc(void)
{
	return FletDlgProc;
}

int CFletResource::GetNumFields(void)
{
	return NUM_FLET_FIELDS;
}

const std::string * CFletResource::GetFieldNames(void)
{
	return g_szFletFields;
}

int CFletResource::Save(char *pOutput)
{
	SwapEndians();

	*(short *)pOutput = m_iLeadShipType;   pOutput += sizeof(short);
	*(short *)pOutput = m_iEscortTypes[0]; pOutput += sizeof(short);
	*(short *)pOutput = m_iEscortTypes[1]; pOutput += sizeof(short);
	*(short *)pOutput = m_iEscortTypes[2]; pOutput += sizeof(short);
	*(short *)pOutput = m_iEscortTypes[3]; pOutput += sizeof(short);
	*(short *)pOutput = m_iMinEscorts[0];  pOutput += sizeof(short);
	*(short *)pOutput = m_iMinEscorts[1];  pOutput += sizeof(short);
	*(short *)pOutput = m_iMinEscorts[2];  pOutput += sizeof(short);
	*(short *)pOutput = m_iMinEscorts[3];  pOutput += sizeof(short);
	*(short *)pOutput = m_iMaxEscorts[0];  pOutput += sizeof(short);
	*(short *)pOutput = m_iMaxEscorts[1];  pOutput += sizeof(short);
	*(short *)pOutput = m_iMaxEscorts[2];  pOutput += sizeof(short);
	*(short *)pOutput = m_iMaxEscorts[3];  pOutput += sizeof(short);
	*(short *)pOutput = m_iGovernment;     pOutput += sizeof(short);
	*(short *)pOutput = m_iSystem;         pOutput += sizeof(short);

	memcpy(pOutput, m_szAppearOn, 256 * sizeof(char)); pOutput += 256 * sizeof(char);

	*(short *)pOutput = m_iQuote;          pOutput += sizeof(short);
	*(USHORT *)pOutput = m_iFlags;         pOutput += sizeof(USHORT);

	SwapEndians();

	return 1;
}

int CFletResource::Load(char *pInput, int iSize)
{
	m_iLeadShipType   = *(short *)pInput; pInput += sizeof(short);
	m_iEscortTypes[0] = *(short *)pInput; pInput += sizeof(short);
	m_iEscortTypes[1] = *(short *)pInput; pInput += sizeof(short);
	m_iEscortTypes[2] = *(short *)pInput; pInput += sizeof(short);
	m_iEscortTypes[3] = *(short *)pInput; pInput += sizeof(short);
	m_iMinEscorts[0]  = *(short *)pInput; pInput += sizeof(short);
	m_iMinEscorts[1]  = *(short *)pInput; pInput += sizeof(short);
	m_iMinEscorts[2]  = *(short *)pInput; pInput += sizeof(short);
	m_iMinEscorts[3]  = *(short *)pInput; pInput += sizeof(short);
	m_iMaxEscorts[0]  = *(short *)pInput; pInput += sizeof(short);
	m_iMaxEscorts[1]  = *(short *)pInput; pInput += sizeof(short);
	m_iMaxEscorts[2]  = *(short *)pInput; pInput += sizeof(short);
	m_iMaxEscorts[3]  = *(short *)pInput; pInput += sizeof(short);
	m_iGovernment     = *(short *)pInput; pInput += sizeof(short);
	m_iSystem         = *(short *)pInput; pInput += sizeof(short);

	memcpy(m_szAppearOn, pInput, 256 * sizeof(char)); pInput += 256 * sizeof(char);

	m_iQuote          = *(short *)pInput; pInput += sizeof(short);
	m_iFlags          = *(USHORT *)pInput; pInput += sizeof(USHORT);

	SwapEndians();

	return 1;
}

int CFletResource::SwapEndians(void)
{
	m_iLeadShipType   = SwapEndianShort(m_iLeadShipType);
	m_iEscortTypes[0] = SwapEndianShort(m_iEscortTypes[0]);
	m_iEscortTypes[1] = SwapEndianShort(m_iEscortTypes[1]);
	m_iEscortTypes[2] = SwapEndianShort(m_iEscortTypes[2]);
	m_iEscortTypes[3] = SwapEndianShort(m_iEscortTypes[3]);
	m_iMinEscorts[0]  = SwapEndianShort(m_iMinEscorts[0]);
	m_iMinEscorts[1]  = SwapEndianShort(m_iMinEscorts[1]);
	m_iMinEscorts[2]  = SwapEndianShort(m_iMinEscorts[2]);
	m_iMinEscorts[3]  = SwapEndianShort(m_iMinEscorts[3]);
	m_iMaxEscorts[0]  = SwapEndianShort(m_iMaxEscorts[0]);
	m_iMaxEscorts[1]  = SwapEndianShort(m_iMaxEscorts[1]);
	m_iMaxEscorts[2]  = SwapEndianShort(m_iMaxEscorts[2]);
	m_iMaxEscorts[3]  = SwapEndianShort(m_iMaxEscorts[3]);
	m_iGovernment     = SwapEndianShort(m_iGovernment);
	m_iSystem         = SwapEndianShort(m_iSystem);
	m_iQuote          = SwapEndianShort(m_iQuote);
	m_iFlags          = SwapEndianShort(m_iFlags);

	return 1;
}

int CFletResource::SaveToText(std::ostream & output)
{
	output << m_iLeadShipType   << '\t'
		   << m_iEscortTypes[0] << '\t'
		   << m_iEscortTypes[1] << '\t'
		   << m_iEscortTypes[2] << '\t'
		   << m_iEscortTypes[3] << '\t'
		   << m_iMinEscorts[0]  << '\t'
		   << m_iMinEscorts[1]  << '\t'
		   << m_iMinEscorts[2]  << '\t'
		   << m_iMinEscorts[3]  << '\t'
		   << m_iMaxEscorts[0]  << '\t'
		   << m_iMaxEscorts[1]  << '\t'
		   << m_iMaxEscorts[2]  << '\t'
		   << m_iMaxEscorts[3]  << '\t'
		   << m_iGovernment     << '\t'
		   << m_iSystem         << '\t';

	PrintTextField(output, m_szAppearOn, '\t');

	output << m_iQuote << '\t';

	PrintHex16Field(output, (char *)&m_iFlags, '\t');

	return 1;
}

int CFletResource::LoadFromText(std::istream & input)
{
	input >> m_iLeadShipType
		  >> m_iEscortTypes[0]
		  >> m_iEscortTypes[1]
		  >> m_iEscortTypes[2]
		  >> m_iEscortTypes[3]
		  >> m_iMinEscorts[0]
		  >> m_iMinEscorts[1]
		  >> m_iMinEscorts[2]
		  >> m_iMinEscorts[3]
		  >> m_iMaxEscorts[0]
		  >> m_iMaxEscorts[1]
		  >> m_iMaxEscorts[2]
		  >> m_iMaxEscorts[3]
		  >> m_iGovernment
		  >> m_iSystem;

	input.ignore(1);

	ReadTextField(input, m_szAppearOn, 256);

	input >> m_iQuote;

	ReadHex16Field(input, (char *)&m_iFlags);

	return 1;
}

int CFletResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "flet ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_FLET_EDIT1, CCONTROL_TYPE_INT, IDS_STRING256);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_FLET_EDIT2, CCONTROL_TYPE_INT, IDS_STRING257);
	m_controls[1].SetInt(m_iLeadShipType);
	m_controls[2].Create(hwnd, IDC_EDIT_FLET_EDIT3, CCONTROL_TYPE_INT, IDS_STRING258);
	m_controls[2].SetInt(m_iEscortTypes[0]);
	m_controls[3].Create(hwnd, IDC_EDIT_FLET_EDIT4, CCONTROL_TYPE_INT, IDS_STRING258);
	m_controls[3].SetInt(m_iEscortTypes[1]);
	m_controls[4].Create(hwnd, IDC_EDIT_FLET_EDIT5, CCONTROL_TYPE_INT, IDS_STRING258);
	m_controls[4].SetInt(m_iEscortTypes[2]);
	m_controls[5].Create(hwnd, IDC_EDIT_FLET_EDIT6, CCONTROL_TYPE_INT, IDS_STRING258);
	m_controls[5].SetInt(m_iEscortTypes[3]);
	m_controls[6].Create(hwnd, IDC_EDIT_FLET_EDIT7, CCONTROL_TYPE_INT, IDS_STRING259);
	m_controls[6].SetInt(m_iMinEscorts[0]);
	m_controls[7].Create(hwnd, IDC_EDIT_FLET_EDIT8, CCONTROL_TYPE_INT, IDS_STRING259);
	m_controls[7].SetInt(m_iMinEscorts[1]);
	m_controls[8].Create(hwnd, IDC_EDIT_FLET_EDIT9, CCONTROL_TYPE_INT, IDS_STRING259);
	m_controls[8].SetInt(m_iMinEscorts[2]);
	m_controls[9].Create(hwnd, IDC_EDIT_FLET_EDIT10, CCONTROL_TYPE_INT, IDS_STRING259);
	m_controls[9].SetInt(m_iMinEscorts[3]);
	m_controls[10].Create(hwnd, IDC_EDIT_FLET_EDIT11, CCONTROL_TYPE_INT, IDS_STRING260);
	m_controls[10].SetInt(m_iMaxEscorts[0]);
	m_controls[11].Create(hwnd, IDC_EDIT_FLET_EDIT12, CCONTROL_TYPE_INT, IDS_STRING260);
	m_controls[11].SetInt(m_iMaxEscorts[1]);
	m_controls[12].Create(hwnd, IDC_EDIT_FLET_EDIT13, CCONTROL_TYPE_INT, IDS_STRING260);
	m_controls[12].SetInt(m_iMaxEscorts[2]);
	m_controls[13].Create(hwnd, IDC_EDIT_FLET_EDIT14, CCONTROL_TYPE_INT, IDS_STRING260);
	m_controls[13].SetInt(m_iMaxEscorts[3]);
	m_controls[14].Create(hwnd, IDC_EDIT_FLET_EDIT15, CCONTROL_TYPE_INT, IDS_STRING261);
	m_controls[14].SetInt(m_iGovernment);
	m_controls[15].Create(hwnd, IDC_EDIT_FLET_EDIT16, CCONTROL_TYPE_INT, IDS_STRING262);
	m_controls[15].SetInt(m_iSystem);
	m_controls[16].Create(hwnd, IDC_EDIT_FLET_EDIT17, CCONTROL_TYPE_STR256, IDS_STRING263);
	m_controls[16].SetString(m_szAppearOn);
	m_controls[17].Create(hwnd, IDC_EDIT_FLET_EDIT18, CCONTROL_TYPE_INT, IDS_STRING264);
	m_controls[17].SetInt(m_iQuote);
	m_controls[18].Create(hwnd, IDC_EDIT_FLET_CHECK1, CCONTROL_TYPE_CHECK, IDS_STRING265);
	m_controls[18].SetInt(m_iFlags & 0x0001);
	m_controls[19].Create(hwnd, IDC_EDIT_FLET_EDIT19, CCONTROL_TYPE_STR256, IDS_STRING266);
	m_controls[19].SetString(m_szName);

	return 1;
}

int CFletResource::CloseAndSave(void)
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

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[19].GetString()) != 0))
		iIDOrNameChanged = 1;

	m_iID = m_controls[0].GetInt();

	m_iLeadShipType = m_controls[1].GetInt();

	m_iEscortTypes[0] = m_controls[2].GetInt();
	m_iEscortTypes[1] = m_controls[3].GetInt();
	m_iEscortTypes[2] = m_controls[4].GetInt();
	m_iEscortTypes[3] = m_controls[5].GetInt();
	m_iMinEscorts[0]  = m_controls[6].GetInt();
	m_iMinEscorts[1]  = m_controls[7].GetInt();
	m_iMinEscorts[2]  = m_controls[8].GetInt();
	m_iMinEscorts[3]  = m_controls[9].GetInt();
	m_iMaxEscorts[0]  = m_controls[10].GetInt();
	m_iMaxEscorts[1]  = m_controls[11].GetInt();
	m_iMaxEscorts[2]  = m_controls[12].GetInt();
	m_iMaxEscorts[3]  = m_controls[13].GetInt();

	m_iGovernment = m_controls[14].GetInt();

	m_iSystem = m_controls[15].GetInt();

	strcpy(m_szAppearOn, m_controls[16].GetString());

	m_iQuote = m_controls[17].GetInt();

	m_iFlags = 0x0000;

	m_iFlags |= m_controls[18].GetInt() << 0;

	strcpy(m_szName, m_controls[19].GetString());

	int i;

	for(i = 0; i < NUM_FLET_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CFletResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_FLET_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CFletResource::FletDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CFletResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CFletResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_FLET_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_FLET_OK)
			{
				pResource->CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_FLET_CONTROLS; i++)
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
