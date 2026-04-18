// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CRankResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CRankResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CRankResource::CRankResource(void)
{
	m_iWeight     = 0;
	m_iGovernment = -1;

	int i;

	for(i = 0; i < 8; i++)
		m_cContribute[i] = 0x00;

	m_iSalary    = 0;
	m_iSalaryCap = 0;

	m_iFlags = 0x0000;

	m_iPriceMod = 100;

	memset(m_szConvName,  0, 64 * sizeof(char));
	memset(m_szShortName, 0, 64 * sizeof(char));
}

CRankResource::~CRankResource(void)
{

}

int CRankResource::GetType(void)
{
	return CNR_TYPE_RANK;
}

int CRankResource::GetSize(void)
{
	return 152;
}

int CRankResource::GetDialogID(void)
{
	return IDD_EDIT_RANK;
}

DLGPROCNOCALLBACK CRankResource::GetDialogProc(void)
{
	return RankDlgProc;
}

int CRankResource::GetNumFields(void)
{
	return NUM_RANK_FIELDS;
}

const std::string * CRankResource::GetFieldNames(void)
{
	return g_szRankFields;
}

int CRankResource::Save(char *pOutput)
{
	SwapEndians();

	*(short *)pOutput = m_iWeight;     pOutput += sizeof(short);
	*(short *)pOutput = m_iGovernment; pOutput += sizeof(short);
	*(short *)pOutput = m_iPriceMod;   pOutput += sizeof(short);
	*(int   *)pOutput = m_iSalary;     pOutput += sizeof(int);
	*(int   *)pOutput = m_iSalaryCap;  pOutput += sizeof(int);

	memcpy(pOutput, m_cContribute, 8 * sizeof(char)); pOutput += 8 * sizeof(char);

	*(USHORT *)pOutput = m_iFlags;     pOutput += sizeof(USHORT);

	ToMacString(m_szConvName);
	ToMacString(m_szShortName);

	memcpy(pOutput, m_szConvName,  64 * sizeof(char)); pOutput += 64 * sizeof(char);
	memcpy(pOutput, m_szShortName, 64 * sizeof(char)); pOutput += 64 * sizeof(char);

	ToWinString(m_szConvName);
	ToWinString(m_szShortName);

	SwapEndians();

	return 1;
}

int CRankResource::Load(char *pInput, int iSize)
{
	m_iWeight     = *(short *)pInput; pInput += sizeof(short);
	m_iGovernment = *(short *)pInput; pInput += sizeof(short);
	m_iPriceMod   = *(short *)pInput; pInput += sizeof(short);
	m_iSalary     = *(int   *)pInput; pInput += sizeof(int);
	m_iSalaryCap  = *(int   *)pInput; pInput += sizeof(int);

	memcpy(m_cContribute, pInput, 8 * sizeof(char)); pInput += 8 * sizeof(char);

	m_iFlags      = *(USHORT *)pInput; pInput += sizeof(USHORT);

	memcpy(m_szConvName,  pInput, 64 * sizeof(char)); pInput += 64 * sizeof(char);
	memcpy(m_szShortName, pInput, 64 * sizeof(char)); pInput += 64 * sizeof(char);

	ToWinString(m_szConvName);
	ToWinString(m_szShortName);

	SwapEndians();

	return 1;
}

int CRankResource::SwapEndians(void)
{
	m_iWeight     = SwapEndianShort(m_iWeight);
	m_iGovernment = SwapEndianShort(m_iGovernment);
	m_iPriceMod   = SwapEndianShort(m_iPriceMod);
	m_iSalary     = SwapEndianInt(m_iSalary);
	m_iSalaryCap  = SwapEndianInt(m_iSalaryCap);
	m_iFlags      = SwapEndianShort(m_iFlags);

	return 1;
}

int CRankResource::SaveToText(std::ostream & output)
{
	output << m_iWeight     << '\t'
		   << m_iGovernment << '\t'
		   << m_iSalary     << '\t'
		   << m_iSalaryCap  << '\t'
		   << m_iPriceMod   << '\t';

	PrintTextField(output, m_szConvName,  '\t');
	PrintTextField(output, m_szShortName, '\t');

	PrintHex64Field(output, m_cContribute, '\t');

	PrintHex16Field(output, (char *)&m_iFlags, '\t');

	return 1;
}

int CRankResource::LoadFromText(std::istream & input)
{
	input >> m_iWeight
		  >> m_iGovernment
		  >> m_iSalary
		  >> m_iSalaryCap
		  >> m_iPriceMod;

	input.ignore(1);

	ReadTextField(input, m_szConvName,  64);
	ReadTextField(input, m_szShortName, 64);

	ReadHex64Field(input, m_cContribute);

	ReadHex16Field(input, (char *)&m_iFlags);

	return 1;
}

int CRankResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "rank ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_RANK_EDIT1, CCONTROL_TYPE_INT, IDS_STRING592);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_RANK_EDIT2, CCONTROL_TYPE_INT, IDS_STRING593);
	m_controls[1].SetInt(m_iWeight);
	m_controls[2].Create(hwnd, IDC_EDIT_RANK_EDIT3, CCONTROL_TYPE_INT, IDS_STRING594);
	m_controls[2].SetInt(m_iGovernment);
	m_controls[3].Create(hwnd, IDC_EDIT_RANK_EDIT4, CCONTROL_TYPE_HEXINT64, IDS_STRING595);
	m_controls[3].SetString(m_cContribute);
	m_controls[4].Create(hwnd, IDC_EDIT_RANK_EDIT5, CCONTROL_TYPE_INT, IDS_STRING596);
	m_controls[4].SetInt(m_iSalary);
	m_controls[5].Create(hwnd, IDC_EDIT_RANK_EDIT6, CCONTROL_TYPE_INT, IDS_STRING597);
	m_controls[5].SetInt(m_iSalaryCap);
	m_controls[6].Create(hwnd, IDC_EDIT_RANK_EDIT7, CCONTROL_TYPE_INT, IDS_STRING598);
	m_controls[6].SetInt(m_iPriceMod);
	m_controls[7].Create(hwnd, IDC_EDIT_RANK_EDIT9, CCONTROL_TYPE_STR64, IDS_STRING600);
	m_controls[7].SetString(m_szConvName);
	m_controls[8].Create(hwnd, IDC_EDIT_RANK_EDIT10, CCONTROL_TYPE_STR64, IDS_STRING601);
	m_controls[8].SetString(m_szShortName);
	m_controls[9].Create(hwnd, IDC_EDIT_RANK_CHECK1, CCONTROL_TYPE_CHECK, IDS_STRING602);
	m_controls[9].SetInt(m_iFlags & 0x0001);
	m_controls[10].Create(hwnd, IDC_EDIT_RANK_CHECK2, CCONTROL_TYPE_CHECK, IDS_STRING603);
	m_controls[10].SetInt(m_iFlags & 0x0002);
	m_controls[11].Create(hwnd, IDC_EDIT_RANK_CHECK3, CCONTROL_TYPE_CHECK, IDS_STRING604);
	m_controls[11].SetInt(m_iFlags & 0x0004);
	m_controls[12].Create(hwnd, IDC_EDIT_RANK_CHECK4, CCONTROL_TYPE_CHECK, IDS_STRING605);
	m_controls[12].SetInt(m_iFlags & 0x0008);
	m_controls[13].Create(hwnd, IDC_EDIT_RANK_CHECK5, CCONTROL_TYPE_CHECK, IDS_STRING606);
	m_controls[13].SetInt(m_iFlags & 0x0010);
	m_controls[14].Create(hwnd, IDC_EDIT_RANK_CHECK6, CCONTROL_TYPE_CHECK, IDS_STRING607);
	m_controls[14].SetInt(m_iFlags & 0x0020);
	m_controls[15].Create(hwnd, IDC_EDIT_RANK_CHECK7, CCONTROL_TYPE_CHECK, IDS_STRING608);
	m_controls[15].SetInt(m_iFlags & 0x0040);
	m_controls[16].Create(hwnd, IDC_EDIT_RANK_CHECK8, CCONTROL_TYPE_CHECK, IDS_STRING609);
	m_controls[16].SetInt(m_iFlags & 0x0100);
	m_controls[17].Create(hwnd, IDC_EDIT_RANK_CHECK9, CCONTROL_TYPE_CHECK, IDS_STRING610);
	m_controls[17].SetInt(m_iFlags & 0x0200);
	m_controls[18].Create(hwnd, IDC_EDIT_RANK_CHECK10, CCONTROL_TYPE_CHECK, IDS_STRING611);
	m_controls[18].SetInt(m_iFlags & 0x0400);
	m_controls[19].Create(hwnd, IDC_EDIT_RANK_CHECK11, CCONTROL_TYPE_CHECK, IDS_STRING612);
	m_controls[19].SetInt(m_iFlags & 0x0800);
	m_controls[20].Create(hwnd, IDC_EDIT_RANK_EDIT11, CCONTROL_TYPE_STR256, IDS_STRING613);
	m_controls[20].SetString(m_szName);

	return 1;
}

int CRankResource::CloseAndSave(void)
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

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[20].GetString()) != 0))
		iIDOrNameChanged = 1;

	m_iID         = m_controls[0].GetInt();

	m_iWeight     = m_controls[1].GetInt();
	m_iGovernment = m_controls[2].GetInt();

	memcpy(m_cContribute, m_controls[3].GetString(), 8 * sizeof(char));

	m_iSalary    = m_controls[4].GetInt();
	m_iSalaryCap = m_controls[5].GetInt();

	m_iPriceMod = m_controls[6].GetInt();

	strcpy(m_szConvName,  m_controls[7].GetString());
	strcpy(m_szShortName, m_controls[8].GetString());

	m_iFlags = 0x0000;

	m_iFlags |= m_controls[9].GetInt()  << 0;
	m_iFlags |= m_controls[10].GetInt() << 1;
	m_iFlags |= m_controls[11].GetInt() << 2;
	m_iFlags |= m_controls[12].GetInt() << 3;
	m_iFlags |= m_controls[13].GetInt() << 4;
	m_iFlags |= m_controls[14].GetInt() << 5;
	m_iFlags |= m_controls[15].GetInt() << 6;
	m_iFlags |= m_controls[16].GetInt() << 8;
	m_iFlags |= m_controls[17].GetInt() << 9;
	m_iFlags |= m_controls[18].GetInt() << 10;
	m_iFlags |= m_controls[19].GetInt() << 11;

	strcpy(m_szName, m_controls[20].GetString());

	int i;

	for(i = 0; i < NUM_RANK_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CRankResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_RANK_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CRankResource::RankDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CRankResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CRankResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_RANK_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_RANK_OK)
			{
				pResource->CloseAndSave();
			}
			else if(iControlID == IDC_EDIT_RANK_BUTTON1)
			{
				char cValue[8];

				memcpy(cValue, pResource->m_controls[3].GetString(), 8);

				pResource->m_bitFieldControl.DoDialog(pResource->m_pWindow, 64, cValue);

				pResource->m_controls[3].SetString(cValue);
			}
			else
			{
				for(i = 0; i < NUM_RANK_CONTROLS; i++)
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
