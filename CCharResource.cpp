// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CCharResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CCharResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CCharResource::CCharResource(void)
{
	m_iCash     = 0;
	m_iShipType = 0;

	m_iSystem1 = 128;
	m_iSystem2 = -1;
	m_iSystem3 = -1;
	m_iSystem4 = -1;

	m_iGovernment1 = -1;
	m_iStatus1     =  0;
	m_iGovernment2 = -1;
	m_iStatus2     =  0;
	m_iGovernment3 = -1;
	m_iStatus3     =  0;
	m_iGovernment4 = -1;
	m_iStatus4     =  0;

	m_iCombatRating = 0;

	m_iIntroPict1 = -1;
	m_iIntroPict2 = -1;
	m_iIntroPict3 = -1;
	m_iIntroPict4 = -1;
	m_iPictDelay1 =  1;
	m_iPictDelay2 =  1;
	m_iPictDelay3 =  1;
	m_iPictDelay4 =  1;

	m_iIntroText = -1;

	memset(m_szOnStart, 0, 256 * sizeof(char));

	m_iFlags = 0x0000;

	m_iStartDay   = 0;
	m_iStartMonth = 0;
	m_iStartYear  = 0;

	memset(m_szDatePrefix, 0, 16 * sizeof(char));
	memset(m_szDateSuffix, 0, 16 * sizeof(char));
}

CCharResource::~CCharResource(void)
= default;

int CCharResource::GetType(void)
{
	return CNR_TYPE_CHAR;
}

int CCharResource::GetSize(void)
{
	return 362;
}

int CCharResource::GetDialogID(void)
{
	return IDD_EDIT_CHAR;
}

DLGPROCNOCALLBACK CCharResource::GetDialogProc(void)
{
	return CharDlgProc;
}

int CCharResource::GetNumFields(void)
{
	return NUM_CHAR_FIELDS;
}

const std::string * CCharResource::GetFieldNames(void)
{
	return g_szCharFields;
}

int CCharResource::Save(char *pOutput)
{
	SwapEndians();

	*(int   *)pOutput = m_iCash;         pOutput += sizeof(int);
	*(short *)pOutput = m_iShipType;     pOutput += sizeof(short);
	*(short *)pOutput = m_iSystem1;      pOutput += sizeof(short);
	*(short *)pOutput = m_iSystem2;      pOutput += sizeof(short);
	*(short *)pOutput = m_iSystem3;      pOutput += sizeof(short);
	*(short *)pOutput = m_iSystem4;      pOutput += sizeof(short);
	*(short *)pOutput = m_iGovernment1;  pOutput += sizeof(short);
	*(short *)pOutput = m_iGovernment2;  pOutput += sizeof(short);
	*(short *)pOutput = m_iGovernment3;  pOutput += sizeof(short);
	*(short *)pOutput = m_iGovernment4;  pOutput += sizeof(short);
	*(short *)pOutput = m_iStatus1;      pOutput += sizeof(short);
	*(short *)pOutput = m_iStatus2;      pOutput += sizeof(short);
	*(short *)pOutput = m_iStatus3;      pOutput += sizeof(short);
	*(short *)pOutput = m_iStatus4;      pOutput += sizeof(short);
	*(short *)pOutput = m_iCombatRating; pOutput += sizeof(short);
	*(short *)pOutput = m_iIntroPict1;   pOutput += sizeof(short);
	*(short *)pOutput = m_iIntroPict2;   pOutput += sizeof(short);
	*(short *)pOutput = m_iIntroPict3;   pOutput += sizeof(short);
	*(short *)pOutput = m_iIntroPict4;   pOutput += sizeof(short);
	*(short *)pOutput = m_iPictDelay1;   pOutput += sizeof(short);
	*(short *)pOutput = m_iPictDelay2;   pOutput += sizeof(short);
	*(short *)pOutput = m_iPictDelay3;   pOutput += sizeof(short);
	*(short *)pOutput = m_iPictDelay4;   pOutput += sizeof(short);
	*(short *)pOutput = m_iIntroText;    pOutput += sizeof(short);

	memcpy(pOutput, m_szOnStart, 256 * sizeof(char)); pOutput += 256 * sizeof(char);

	*(USHORT *)pOutput = m_iFlags;        pOutput += sizeof(USHORT);
	*(short *)pOutput = m_iStartDay;     pOutput += sizeof(short);
	*(short *)pOutput = m_iStartMonth;   pOutput += sizeof(short);
	*(short *)pOutput = m_iStartYear;    pOutput += sizeof(short);

	ToMacString(m_szDatePrefix);
	ToMacString(m_szDateSuffix);

	memcpy(pOutput, m_szDatePrefix, 16 * sizeof(char)); pOutput += 16 * sizeof(char);
	memcpy(pOutput, m_szDateSuffix, 16 * sizeof(char)); pOutput += 16 * sizeof(char);

	ToWinString(m_szDatePrefix);
	ToWinString(m_szDateSuffix);

	SwapEndians();

	return 1;
}

int CCharResource::Load(char *pInput, int iSize)
{
	m_iCash         = *(int   *)pInput; pInput += sizeof(int);
	m_iShipType     = *(short *)pInput; pInput += sizeof(short);
	m_iSystem1      = *(short *)pInput; pInput += sizeof(short);
	m_iSystem2      = *(short *)pInput; pInput += sizeof(short);
	m_iSystem3      = *(short *)pInput; pInput += sizeof(short);
	m_iSystem4      = *(short *)pInput; pInput += sizeof(short);
	m_iGovernment1  = *(short *)pInput; pInput += sizeof(short);
	m_iGovernment2  = *(short *)pInput; pInput += sizeof(short);
	m_iGovernment3  = *(short *)pInput; pInput += sizeof(short);
	m_iGovernment4  = *(short *)pInput; pInput += sizeof(short);
	m_iStatus1      = *(short *)pInput; pInput += sizeof(short);
	m_iStatus2      = *(short *)pInput; pInput += sizeof(short);
	m_iStatus3      = *(short *)pInput; pInput += sizeof(short);
	m_iStatus4      = *(short *)pInput; pInput += sizeof(short);
	m_iCombatRating = *(short *)pInput; pInput += sizeof(short);
	m_iIntroPict1   = *(short *)pInput; pInput += sizeof(short);
	m_iIntroPict2   = *(short *)pInput; pInput += sizeof(short);
	m_iIntroPict3   = *(short *)pInput; pInput += sizeof(short);
	m_iIntroPict4   = *(short *)pInput; pInput += sizeof(short);
	m_iPictDelay1   = *(short *)pInput; pInput += sizeof(short);
	m_iPictDelay2   = *(short *)pInput; pInput += sizeof(short);
	m_iPictDelay3   = *(short *)pInput; pInput += sizeof(short);
	m_iPictDelay4   = *(short *)pInput; pInput += sizeof(short);
	m_iIntroText    = *(short *)pInput; pInput += sizeof(short);

	memcpy(m_szOnStart, pInput, 256 * sizeof(char)); pInput += 256 * sizeof(char);

	m_iFlags        = *(USHORT *)pInput; pInput += sizeof(USHORT);
	m_iStartDay     = *(short *)pInput; pInput += sizeof(short);
	m_iStartMonth   = *(short *)pInput; pInput += sizeof(short);
	m_iStartYear    = *(short *)pInput; pInput += sizeof(short);

	memcpy(m_szDatePrefix, pInput, 16 * sizeof(char)); pInput += 16 * sizeof(char);
	memcpy(m_szDateSuffix, pInput, 16 * sizeof(char)); pInput += 16 * sizeof(char);

	ToWinString(m_szDatePrefix);
	ToWinString(m_szDateSuffix);

	SwapEndians();

	return 1;
}

int CCharResource::SwapEndians(void)
{
	m_iCash         = SwapEndianInt(m_iCash);
	m_iShipType     = SwapEndianShort(m_iShipType);
	m_iSystem1      = SwapEndianShort(m_iSystem1);
	m_iSystem2      = SwapEndianShort(m_iSystem2);
	m_iSystem3      = SwapEndianShort(m_iSystem3);
	m_iSystem4      = SwapEndianShort(m_iSystem4);
	m_iGovernment1  = SwapEndianShort(m_iGovernment1);
	m_iGovernment2  = SwapEndianShort(m_iGovernment2);
	m_iGovernment3  = SwapEndianShort(m_iGovernment3);
	m_iGovernment4  = SwapEndianShort(m_iGovernment4);
	m_iStatus1      = SwapEndianShort(m_iStatus1);
	m_iStatus2      = SwapEndianShort(m_iStatus2);
	m_iStatus3      = SwapEndianShort(m_iStatus3);
	m_iStatus4      = SwapEndianShort(m_iStatus4);
	m_iCombatRating = SwapEndianShort(m_iCombatRating);
	m_iIntroPict1   = SwapEndianShort(m_iIntroPict1);
	m_iIntroPict2   = SwapEndianShort(m_iIntroPict2);
	m_iIntroPict3   = SwapEndianShort(m_iIntroPict3);
	m_iIntroPict4   = SwapEndianShort(m_iIntroPict4);
	m_iPictDelay1   = SwapEndianShort(m_iPictDelay1);
	m_iPictDelay2   = SwapEndianShort(m_iPictDelay2);
	m_iPictDelay3   = SwapEndianShort(m_iPictDelay3);
	m_iPictDelay4   = SwapEndianShort(m_iPictDelay4);
	m_iIntroText    = SwapEndianShort(m_iIntroText);
	m_iFlags        = SwapEndianShort(m_iFlags);
	m_iStartDay     = SwapEndianShort(m_iStartDay);
	m_iStartMonth   = SwapEndianShort(m_iStartMonth);
	m_iStartYear    = SwapEndianShort(m_iStartYear);

	return 1;
}

int CCharResource::SaveToText(std::ostream & output)
{
	output << m_iCash         << '\t'
		   << m_iShipType     << '\t'
		   << m_iSystem1      << '\t'
		   << m_iSystem2      << '\t'
		   << m_iSystem3      << '\t'
		   << m_iSystem4      << '\t'
		   << m_iGovernment1  << '\t'
		   << m_iStatus1      << '\t'
		   << m_iGovernment2  << '\t'
		   << m_iStatus2      << '\t'
		   << m_iGovernment3  << '\t'
		   << m_iStatus3      << '\t'
		   << m_iGovernment4  << '\t'
		   << m_iStatus4      << '\t'
		   << m_iCombatRating << '\t'
		   << m_iIntroPict1   << '\t'
		   << m_iIntroPict2   << '\t'
		   << m_iIntroPict3   << '\t'
		   << m_iIntroPict4   << '\t'
		   << m_iPictDelay1   << '\t'
		   << m_iPictDelay2   << '\t'
		   << m_iPictDelay3   << '\t'
		   << m_iPictDelay4   << '\t'
		   << m_iIntroText    << '\t';

	PrintTextField(output, m_szOnStart, '\t');

	output << m_iStartDay     << '\t'
		   << m_iStartMonth   << '\t'
		   << m_iStartYear    << '\t';

	PrintTextField(output, m_szDatePrefix, '\t');
	PrintTextField(output, m_szDateSuffix, '\t');

	PrintHex16Field(output, (char *)&m_iFlags, '\t');

	return 1;
}

int CCharResource::LoadFromText(std::istream & input)
{
	input >> m_iCash
		  >> m_iShipType
		  >> m_iSystem1
		  >> m_iSystem2
		  >> m_iSystem3
		  >> m_iSystem4
		  >> m_iGovernment1
		  >> m_iStatus1
		  >> m_iGovernment2
		  >> m_iStatus2
		  >> m_iGovernment3
		  >> m_iStatus3
		  >> m_iGovernment4
		  >> m_iStatus4
		  >> m_iCombatRating
		  >> m_iIntroPict1
		  >> m_iIntroPict2
		  >> m_iIntroPict3
		  >> m_iIntroPict4
		  >> m_iPictDelay1
		  >> m_iPictDelay2
		  >> m_iPictDelay3
		  >> m_iPictDelay4
		  >> m_iIntroText;

	input.ignore(1);

	ReadTextField(input, m_szOnStart, 256);

	input >> m_iStartDay
		  >> m_iStartMonth
		  >> m_iStartYear;

	input.ignore(1);

	ReadTextField(input, m_szDatePrefix, 16);
	ReadTextField(input, m_szDateSuffix, 16);

	ReadHex16Field(input, (char *)&m_iFlags);

	return 1;
}

int CCharResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "char ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();;

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_CHAR_EDIT1, CCONTROL_TYPE_INT, IDS_STRING112);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_CHAR_EDIT2, CCONTROL_TYPE_INT, IDS_STRING113);
	m_controls[1].SetInt(m_iCash);
	m_controls[2].Create(hwnd, IDC_EDIT_CHAR_EDIT3, CCONTROL_TYPE_INT, IDS_STRING114);
	m_controls[2].SetInt(m_iShipType);
	m_controls[3].Create(hwnd, IDC_EDIT_CHAR_EDIT4, CCONTROL_TYPE_INT, IDS_STRING115);
	m_controls[3].SetInt(m_iSystem1);
	m_controls[4].Create(hwnd, IDC_EDIT_CHAR_EDIT5, CCONTROL_TYPE_INT, IDS_STRING115);
	m_controls[4].SetInt(m_iSystem2);
	m_controls[5].Create(hwnd, IDC_EDIT_CHAR_EDIT6, CCONTROL_TYPE_INT, IDS_STRING115);
	m_controls[5].SetInt(m_iSystem3);
	m_controls[6].Create(hwnd, IDC_EDIT_CHAR_EDIT7, CCONTROL_TYPE_INT, IDS_STRING115);
	m_controls[6].SetInt(m_iSystem4);
	m_controls[7].Create(hwnd, IDC_EDIT_CHAR_EDIT8, CCONTROL_TYPE_INT, IDS_STRING116);
	m_controls[7].SetInt(m_iGovernment1);
	m_controls[8].Create(hwnd, IDC_EDIT_CHAR_EDIT9, CCONTROL_TYPE_INT, IDS_STRING116);
	m_controls[8].SetInt(m_iStatus1);
	m_controls[9].Create(hwnd, IDC_EDIT_CHAR_EDIT10, CCONTROL_TYPE_INT, IDS_STRING116);
	m_controls[9].SetInt(m_iGovernment2);
	m_controls[10].Create(hwnd, IDC_EDIT_CHAR_EDIT11, CCONTROL_TYPE_INT, IDS_STRING116);
	m_controls[10].SetInt(m_iStatus2);
	m_controls[11].Create(hwnd, IDC_EDIT_CHAR_EDIT12, CCONTROL_TYPE_INT, IDS_STRING116);
	m_controls[11].SetInt(m_iGovernment3);
	m_controls[12].Create(hwnd, IDC_EDIT_CHAR_EDIT13, CCONTROL_TYPE_INT, IDS_STRING116);
	m_controls[12].SetInt(m_iStatus3);
	m_controls[13].Create(hwnd, IDC_EDIT_CHAR_EDIT14, CCONTROL_TYPE_INT, IDS_STRING116);
	m_controls[13].SetInt(m_iGovernment4);
	m_controls[14].Create(hwnd, IDC_EDIT_CHAR_EDIT15, CCONTROL_TYPE_INT, IDS_STRING116);
	m_controls[14].SetInt(m_iStatus4);
	m_controls[15].Create(hwnd, IDC_EDIT_CHAR_EDIT16, CCONTROL_TYPE_INT, IDS_STRING117);
	m_controls[15].SetInt(m_iCombatRating);
	m_controls[16].Create(hwnd, IDC_EDIT_CHAR_EDIT17, CCONTROL_TYPE_INT, IDS_STRING118);
	m_controls[16].SetInt(m_iIntroPict1);
	m_controls[17].Create(hwnd, IDC_EDIT_CHAR_EDIT18, CCONTROL_TYPE_INT, IDS_STRING118);
	m_controls[17].SetInt(m_iIntroPict2);
	m_controls[18].Create(hwnd, IDC_EDIT_CHAR_EDIT19, CCONTROL_TYPE_INT, IDS_STRING118);
	m_controls[18].SetInt(m_iIntroPict3);
	m_controls[19].Create(hwnd, IDC_EDIT_CHAR_EDIT20, CCONTROL_TYPE_INT, IDS_STRING118);
	m_controls[19].SetInt(m_iIntroPict4);
	m_controls[20].Create(hwnd, IDC_EDIT_CHAR_EDIT21, CCONTROL_TYPE_INT, IDS_STRING119);
	m_controls[20].SetInt(m_iPictDelay1);
	m_controls[21].Create(hwnd, IDC_EDIT_CHAR_EDIT22, CCONTROL_TYPE_INT, IDS_STRING119);
	m_controls[21].SetInt(m_iPictDelay2);
	m_controls[22].Create(hwnd, IDC_EDIT_CHAR_EDIT23, CCONTROL_TYPE_INT, IDS_STRING119);
	m_controls[22].SetInt(m_iPictDelay3);
	m_controls[23].Create(hwnd, IDC_EDIT_CHAR_EDIT24, CCONTROL_TYPE_INT, IDS_STRING119);
	m_controls[23].SetInt(m_iPictDelay4);
	m_controls[24].Create(hwnd, IDC_EDIT_CHAR_EDIT25, CCONTROL_TYPE_INT, IDS_STRING120);
	m_controls[24].SetInt(m_iIntroText);
	m_controls[25].Create(hwnd, IDC_EDIT_CHAR_EDIT26, CCONTROL_TYPE_STR256, IDS_STRING121);
	m_controls[25].SetString(m_szOnStart);
	m_controls[26].Create(hwnd, IDC_EDIT_CHAR_EDIT27, CCONTROL_TYPE_INT, IDS_STRING122);
	m_controls[26].SetInt(m_iStartYear);
	m_controls[27].Create(hwnd, IDC_EDIT_CHAR_EDIT28, CCONTROL_TYPE_STR16, IDS_STRING123);
	m_controls[27].SetString(m_szDatePrefix);
	m_controls[28].Create(hwnd, IDC_EDIT_CHAR_EDIT29, CCONTROL_TYPE_STR16, IDS_STRING124);
	m_controls[28].SetString(m_szDateSuffix);
	m_controls[29].Create(hwnd, IDC_EDIT_CHAR_CHECK30, CCONTROL_TYPE_CHECK, IDS_STRING125);
	m_controls[29].SetInt(m_iFlags & 0x0001);
	m_controls[30].Create(hwnd, IDC_EDIT_CHAR_EDIT30, CCONTROL_TYPE_STR256, IDS_STRING126);
	m_controls[30].SetString(m_szName);
	m_controls[31].Create(hwnd, IDC_EDIT_CHAR_EDIT31, CCONTROL_TYPE_INT, IDS_STRING127);
	m_controls[31].SetInt(m_iStartDay);
	m_controls[32].Create(hwnd, IDC_EDIT_CHAR_EDIT32, CCONTROL_TYPE_INT, IDS_STRING2128);
	m_controls[32].SetInt(m_iStartMonth);

	return 1;
}

int CCharResource::CloseAndSave(void)
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

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[30].GetString()) != 0))
		iIDOrNameChanged = 1;

	m_iID           = m_controls[0].GetInt();
	m_iCash         = m_controls[1].GetInt();
	m_iShipType     = m_controls[2].GetInt();
	m_iSystem1      = m_controls[3].GetInt();
	m_iSystem2      = m_controls[4].GetInt();
	m_iSystem3      = m_controls[5].GetInt();
	m_iSystem4      = m_controls[6].GetInt();
	m_iGovernment1  = m_controls[7].GetInt();
	m_iStatus1      = m_controls[8].GetInt();
	m_iGovernment2  = m_controls[9].GetInt();
	m_iStatus2      = m_controls[10].GetInt();
	m_iGovernment3  = m_controls[11].GetInt();
	m_iStatus3      = m_controls[12].GetInt();
	m_iGovernment4  = m_controls[13].GetInt();
	m_iStatus4      = m_controls[14].GetInt();
	m_iCombatRating = m_controls[15].GetInt();
	m_iIntroPict1   = m_controls[16].GetInt();
	m_iIntroPict2   = m_controls[17].GetInt();
	m_iIntroPict3   = m_controls[18].GetInt();
	m_iIntroPict4   = m_controls[19].GetInt();
	m_iPictDelay1   = m_controls[20].GetInt();
	m_iPictDelay2   = m_controls[21].GetInt();
	m_iPictDelay3   = m_controls[22].GetInt();
	m_iPictDelay4   = m_controls[23].GetInt();
	m_iIntroText    = m_controls[24].GetInt();

	strcpy_s(m_szOnStart, m_controls[25].GetString());

	m_iStartDay   = m_controls[31].GetInt();
	m_iStartMonth = m_controls[32].GetInt();
	m_iStartYear  = m_controls[26].GetInt();

	strcpy_s(m_szDatePrefix, m_controls[27].GetString());
	strcpy_s(m_szDateSuffix, m_controls[28].GetString());

	m_iFlags = 0x0000;

	m_iFlags |= m_controls[29].GetInt() << 0;

	strcpy_s(m_szName, m_controls[30].GetString());

	int i;

	for(i = 0; i < 33; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CCharResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_CHAR_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CCharResource::CharDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CCharResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if (pWindow != NULL) pResource = (CCharResource*)pWindow->GetExtraData(2);
	else if (!pResource) return FALSE;
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

			if(iControlID == IDC_EDIT_CHAR_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_CHAR_OK)
			{
				pResource->CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_CHAR_CONTROLS; i++)
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
