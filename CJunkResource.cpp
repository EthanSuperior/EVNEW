// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CJunkResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CJunkResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CJunkResource::CJunkResource(void)
{
	int i;

	for(i = 0; i < 8; i++)
	{
		m_iSoldAt[i]   = 0;
		m_iBoughtAt[i] = 0;
	}

	m_iBasePrice = 0;

	m_iFlags = 0x0000;

	for(i = 0; i < 2; i++)
		m_cScanMask[i] = 0x00;

	memset(m_szLowerCaseName, 0, 64 * sizeof(char));
	memset(m_szAbbreviation,  0, 64 * sizeof(char));

	memset(m_szBuyOn,  0, 255 * sizeof(char));
	memset(m_szSellOn, 0, 255 * sizeof(char));
}

CJunkResource::~CJunkResource(void)
{

}

int CJunkResource::GetType(void)
{
	return CNR_TYPE_JUNK;
}

int CJunkResource::GetSize(void)
{
	return 676;
}

int CJunkResource::GetDialogID(void)
{
	return IDD_EDIT_JUNK;
}

DLGPROCNOCALLBACK CJunkResource::GetDialogProc(void)
{
	return JunkDlgProc;
}

int CJunkResource::GetNumFields(void)
{
	return NUM_JUNK_FIELDS;
}

const std::string * CJunkResource::GetFieldNames(void)
{
	return g_szJunkFields;
}

int CJunkResource::Save(char *pOutput)
{
	SwapEndians();

	*(short *)pOutput = m_iSoldAt[0];   pOutput += sizeof(short);
	*(short *)pOutput = m_iSoldAt[1];   pOutput += sizeof(short);
	*(short *)pOutput = m_iSoldAt[2];   pOutput += sizeof(short);
	*(short *)pOutput = m_iSoldAt[3];   pOutput += sizeof(short);
	*(short *)pOutput = m_iSoldAt[4];   pOutput += sizeof(short);
	*(short *)pOutput = m_iSoldAt[5];   pOutput += sizeof(short);
	*(short *)pOutput = m_iSoldAt[6];   pOutput += sizeof(short);
	*(short *)pOutput = m_iSoldAt[7];   pOutput += sizeof(short);
	*(short *)pOutput = m_iBoughtAt[0]; pOutput += sizeof(short);
	*(short *)pOutput = m_iBoughtAt[1]; pOutput += sizeof(short);
	*(short *)pOutput = m_iBoughtAt[2]; pOutput += sizeof(short);
	*(short *)pOutput = m_iBoughtAt[3]; pOutput += sizeof(short);
	*(short *)pOutput = m_iBoughtAt[4]; pOutput += sizeof(short);
	*(short *)pOutput = m_iBoughtAt[5]; pOutput += sizeof(short);
	*(short *)pOutput = m_iBoughtAt[6]; pOutput += sizeof(short);
	*(short *)pOutput = m_iBoughtAt[7]; pOutput += sizeof(short);
	*(short *)pOutput = m_iBasePrice;   pOutput += sizeof(short);
	*(USHORT *)pOutput = m_iFlags;      pOutput += sizeof(USHORT);

	ToMacString(m_szLowerCaseName);
	ToMacString(m_szAbbreviation);

	memcpy(pOutput, m_cScanMask,        2 * sizeof(char)); pOutput +=   2 * sizeof(char);
	memcpy(pOutput, m_szLowerCaseName, 64 * sizeof(char)); pOutput +=  64 * sizeof(char);
	memcpy(pOutput, m_szAbbreviation,  64 * sizeof(char)); pOutput +=  64 * sizeof(char);
	memcpy(pOutput, m_szBuyOn,        255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_szSellOn,       255 * sizeof(char)); pOutput += 255 * sizeof(char);

	ToWinString(m_szLowerCaseName);
	ToWinString(m_szAbbreviation);

	SwapEndians();

	return 1;
}

int CJunkResource::Load(char *pInput, int iSize)
{
	m_iSoldAt[0]   = *(short *)pInput; pInput += sizeof(short);
	m_iSoldAt[1]   = *(short *)pInput; pInput += sizeof(short);
	m_iSoldAt[2]   = *(short *)pInput; pInput += sizeof(short);
	m_iSoldAt[3]   = *(short *)pInput; pInput += sizeof(short);
	m_iSoldAt[4]   = *(short *)pInput; pInput += sizeof(short);
	m_iSoldAt[5]   = *(short *)pInput; pInput += sizeof(short);
	m_iSoldAt[6]   = *(short *)pInput; pInput += sizeof(short);
	m_iSoldAt[7]   = *(short *)pInput; pInput += sizeof(short);
	m_iBoughtAt[0] = *(short *)pInput; pInput += sizeof(short);
	m_iBoughtAt[1] = *(short *)pInput; pInput += sizeof(short);
	m_iBoughtAt[2] = *(short *)pInput; pInput += sizeof(short);
	m_iBoughtAt[3] = *(short *)pInput; pInput += sizeof(short);
	m_iBoughtAt[4] = *(short *)pInput; pInput += sizeof(short);
	m_iBoughtAt[5] = *(short *)pInput; pInput += sizeof(short);
	m_iBoughtAt[6] = *(short *)pInput; pInput += sizeof(short);
	m_iBoughtAt[7] = *(short *)pInput; pInput += sizeof(short);
	m_iBasePrice   = *(short *)pInput; pInput += sizeof(short);
	m_iFlags       = *(USHORT *)pInput; pInput += sizeof(USHORT);

	memcpy(m_cScanMask,       pInput,   2 * sizeof(char)); pInput +=   2 * sizeof(char);
	memcpy(m_szLowerCaseName, pInput,  64 * sizeof(char)); pInput +=  64 * sizeof(char);
	memcpy(m_szAbbreviation,  pInput,  64 * sizeof(char)); pInput +=  64 * sizeof(char);
	memcpy(m_szBuyOn,         pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	memcpy(m_szSellOn,        pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);

	ToWinString(m_szLowerCaseName);
	ToWinString(m_szAbbreviation);

	SwapEndians();

	return 1;
}

int CJunkResource::SwapEndians(void)
{
	m_iSoldAt[0]   = SwapEndianShort(m_iSoldAt[0]);
	m_iSoldAt[1]   = SwapEndianShort(m_iSoldAt[1]);
	m_iSoldAt[2]   = SwapEndianShort(m_iSoldAt[2]);
	m_iSoldAt[3]   = SwapEndianShort(m_iSoldAt[3]);
	m_iSoldAt[4]   = SwapEndianShort(m_iSoldAt[4]);
	m_iSoldAt[5]   = SwapEndianShort(m_iSoldAt[5]);
	m_iSoldAt[6]   = SwapEndianShort(m_iSoldAt[6]);
	m_iSoldAt[7]   = SwapEndianShort(m_iSoldAt[7]);
	m_iBoughtAt[0] = SwapEndianShort(m_iBoughtAt[0]);
	m_iBoughtAt[1] = SwapEndianShort(m_iBoughtAt[1]);
	m_iBoughtAt[2] = SwapEndianShort(m_iBoughtAt[2]);
	m_iBoughtAt[3] = SwapEndianShort(m_iBoughtAt[3]);
	m_iBoughtAt[4] = SwapEndianShort(m_iBoughtAt[4]);
	m_iBoughtAt[5] = SwapEndianShort(m_iBoughtAt[5]);
	m_iBoughtAt[6] = SwapEndianShort(m_iBoughtAt[6]);
	m_iBoughtAt[7] = SwapEndianShort(m_iBoughtAt[7]);
	m_iBasePrice   = SwapEndianShort(m_iBasePrice);
	m_iFlags       = SwapEndianShort(m_iFlags);

	return 1;
}

int CJunkResource::SaveToText(std::ostream & output)
{
	output << m_iSoldAt[0]   << '\t'
		   << m_iSoldAt[1]   << '\t'
		   << m_iSoldAt[2]   << '\t'
		   << m_iSoldAt[3]   << '\t'
		   << m_iSoldAt[4]   << '\t'
		   << m_iSoldAt[5]   << '\t'
		   << m_iSoldAt[6]   << '\t'
		   << m_iSoldAt[7]   << '\t'
		   << m_iBoughtAt[0] << '\t'
		   << m_iBoughtAt[1] << '\t'
		   << m_iBoughtAt[2] << '\t'
		   << m_iBoughtAt[3] << '\t'
		   << m_iBoughtAt[4] << '\t'
		   << m_iBoughtAt[5] << '\t'
		   << m_iBoughtAt[6] << '\t'
		   << m_iBoughtAt[7] << '\t'
		   << m_iBasePrice   << '\t';

	char c = m_cScanMask[0]; m_cScanMask[0] = m_cScanMask[1]; m_cScanMask[1] = c;

	PrintHex16Field(output, m_cScanMask, '\t');

	c = m_cScanMask[0]; m_cScanMask[0] = m_cScanMask[1]; m_cScanMask[1] = c;

	PrintTextField(output, m_szLowerCaseName, '\t');
	PrintTextField(output, m_szAbbreviation,  '\t');
	PrintTextField(output, m_szBuyOn,         '\t');
	PrintTextField(output, m_szSellOn,        '\t');

	PrintHex16Field(output, (char *)&m_iFlags, '\t');

	return 1;
}

int CJunkResource::LoadFromText(std::istream & input)
{
	input >> m_iSoldAt[0]
		  >> m_iSoldAt[1]
		  >> m_iSoldAt[2]
		  >> m_iSoldAt[3]
		  >> m_iSoldAt[4]
		  >> m_iSoldAt[5]
		  >> m_iSoldAt[6]
		  >> m_iSoldAt[7]
		  >> m_iBoughtAt[0]
		  >> m_iBoughtAt[1]
		  >> m_iBoughtAt[2]
		  >> m_iBoughtAt[3]
		  >> m_iBoughtAt[4]
		  >> m_iBoughtAt[5]
		  >> m_iBoughtAt[6]
		  >> m_iBoughtAt[7]
		  >> m_iBasePrice;

	ReadHex16Field(input, m_cScanMask);

	char c = m_cScanMask[0]; m_cScanMask[0] = m_cScanMask[1]; m_cScanMask[1] = c;

	ReadTextField(input, m_szLowerCaseName, 64);
	ReadTextField(input, m_szAbbreviation,  64);
	ReadTextField(input, m_szBuyOn,        255);
	ReadTextField(input, m_szSellOn,       255);

	ReadHex16Field(input, (char *)&m_iFlags);

	return 1;
}

int CJunkResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "junk ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_JUNK_EDIT1, CCONTROL_TYPE_INT, IDS_STRING384);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_JUNK_EDIT2, CCONTROL_TYPE_INT, IDS_STRING385);
	m_controls[1].SetInt(m_iSoldAt[0]);
	m_controls[2].Create(hwnd, IDC_EDIT_JUNK_EDIT3, CCONTROL_TYPE_INT, IDS_STRING385);
	m_controls[2].SetInt(m_iSoldAt[1]);
	m_controls[3].Create(hwnd, IDC_EDIT_JUNK_EDIT4, CCONTROL_TYPE_INT, IDS_STRING385);
	m_controls[3].SetInt(m_iSoldAt[2]);
	m_controls[4].Create(hwnd, IDC_EDIT_JUNK_EDIT5, CCONTROL_TYPE_INT, IDS_STRING385);
	m_controls[4].SetInt(m_iSoldAt[3]);
	m_controls[5].Create(hwnd, IDC_EDIT_JUNK_EDIT6, CCONTROL_TYPE_INT, IDS_STRING385);
	m_controls[5].SetInt(m_iSoldAt[4]);
	m_controls[6].Create(hwnd, IDC_EDIT_JUNK_EDIT7, CCONTROL_TYPE_INT, IDS_STRING385);
	m_controls[6].SetInt(m_iSoldAt[5]);
	m_controls[7].Create(hwnd, IDC_EDIT_JUNK_EDIT8, CCONTROL_TYPE_INT, IDS_STRING385);
	m_controls[7].SetInt(m_iSoldAt[6]);
	m_controls[8].Create(hwnd, IDC_EDIT_JUNK_EDIT9, CCONTROL_TYPE_INT, IDS_STRING385);
	m_controls[8].SetInt(m_iSoldAt[7]);
	m_controls[9].Create(hwnd, IDC_EDIT_JUNK_EDIT10, CCONTROL_TYPE_INT, IDS_STRING386);
	m_controls[9].SetInt(m_iBoughtAt[0]);
	m_controls[10].Create(hwnd, IDC_EDIT_JUNK_EDIT11, CCONTROL_TYPE_INT, IDS_STRING386);
	m_controls[10].SetInt(m_iBoughtAt[1]);
	m_controls[11].Create(hwnd, IDC_EDIT_JUNK_EDIT12, CCONTROL_TYPE_INT, IDS_STRING386);
	m_controls[11].SetInt(m_iBoughtAt[2]);
	m_controls[12].Create(hwnd, IDC_EDIT_JUNK_EDIT13, CCONTROL_TYPE_INT, IDS_STRING386);
	m_controls[12].SetInt(m_iBoughtAt[3]);
	m_controls[13].Create(hwnd, IDC_EDIT_JUNK_EDIT14, CCONTROL_TYPE_INT, IDS_STRING386);
	m_controls[13].SetInt(m_iBoughtAt[4]);
	m_controls[14].Create(hwnd, IDC_EDIT_JUNK_EDIT15, CCONTROL_TYPE_INT, IDS_STRING386);
	m_controls[14].SetInt(m_iBoughtAt[5]);
	m_controls[15].Create(hwnd, IDC_EDIT_JUNK_EDIT16, CCONTROL_TYPE_INT, IDS_STRING386);
	m_controls[15].SetInt(m_iBoughtAt[6]);
	m_controls[16].Create(hwnd, IDC_EDIT_JUNK_EDIT17, CCONTROL_TYPE_INT, IDS_STRING386);
	m_controls[16].SetInt(m_iBoughtAt[7]);
	m_controls[17].Create(hwnd, IDC_EDIT_JUNK_EDIT18, CCONTROL_TYPE_INT, IDS_STRING387);
	m_controls[17].SetInt(m_iBasePrice);
	m_controls[18].Create(hwnd, IDC_EDIT_JUNK_EDIT19, CCONTROL_TYPE_HEXINT16, IDS_STRING388);
	m_controls[18].SetString(m_cScanMask);
	m_controls[19].Create(hwnd, IDC_EDIT_JUNK_EDIT20, CCONTROL_TYPE_STR64, IDS_STRING389);
	m_controls[19].SetString(m_szLowerCaseName);
	m_controls[20].Create(hwnd, IDC_EDIT_JUNK_EDIT21, CCONTROL_TYPE_STR64, IDS_STRING390);
	m_controls[20].SetString(m_szAbbreviation);
	m_controls[21].Create(hwnd, IDC_EDIT_JUNK_EDIT22, CCONTROL_TYPE_STR255, IDS_STRING391);
	m_controls[21].SetString(m_szBuyOn);
	m_controls[22].Create(hwnd, IDC_EDIT_JUNK_EDIT23, CCONTROL_TYPE_STR255, IDS_STRING392);
	m_controls[22].SetString(m_szSellOn);
	m_controls[23].Create(hwnd, IDC_EDIT_JUNK_CHECK1, CCONTROL_TYPE_CHECK, IDS_STRING393);
	m_controls[23].SetInt(m_iFlags & 0x0001);
	m_controls[24].Create(hwnd, IDC_EDIT_JUNK_CHECK2, CCONTROL_TYPE_CHECK, IDS_STRING393);
	m_controls[24].SetInt(m_iFlags & 0x0002);
	m_controls[25].Create(hwnd, IDC_EDIT_JUNK_EDIT24, CCONTROL_TYPE_STR256, IDS_STRING394);
	m_controls[25].SetString(m_szName);

	return 1;
}

int CJunkResource::CloseAndSave(void)
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

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[25].GetString()) != 0))
		iIDOrNameChanged = 1;

	m_iID          = m_controls[0].GetInt();
	m_iSoldAt[0]   = m_controls[1].GetInt();
	m_iSoldAt[1]   = m_controls[2].GetInt();
	m_iSoldAt[2]   = m_controls[3].GetInt();
	m_iSoldAt[3]   = m_controls[4].GetInt();
	m_iSoldAt[4]   = m_controls[5].GetInt();
	m_iSoldAt[5]   = m_controls[6].GetInt();
	m_iSoldAt[6]   = m_controls[7].GetInt();
	m_iSoldAt[7]   = m_controls[8].GetInt();
	m_iBoughtAt[0] = m_controls[9].GetInt();
	m_iBoughtAt[1] = m_controls[10].GetInt();
	m_iBoughtAt[2] = m_controls[11].GetInt();
	m_iBoughtAt[3] = m_controls[12].GetInt();
	m_iBoughtAt[4] = m_controls[13].GetInt();
	m_iBoughtAt[5] = m_controls[14].GetInt();
	m_iBoughtAt[6] = m_controls[15].GetInt();
	m_iBoughtAt[7] = m_controls[16].GetInt();
	m_iBasePrice   = m_controls[17].GetInt();

	memcpy(m_cScanMask, m_controls[18].GetString(), 2 * sizeof(char));

	strcpy_s(m_szLowerCaseName, m_controls[19].GetString());
	strcpy_s(m_szAbbreviation, m_controls[20].GetString());
	strcpy_s(m_szBuyOn, m_controls[21].GetString());
	strcpy_s(m_szSellOn, m_controls[22].GetString());

	m_iFlags = 0x0000;

	m_iFlags |= m_controls[23].GetInt() << 0;
	m_iFlags |= m_controls[24].GetInt() << 1;

	strcpy_s(m_szName, m_controls[25].GetString());

	int i;

	for(i = 0; i < NUM_JUNK_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CJunkResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_JUNK_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CJunkResource::JunkDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CJunkResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CJunkResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_JUNK_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_JUNK_OK)
			{
				pResource->CloseAndSave();
			}
			else if(iControlID == IDC_EDIT_JUNK_BUTTON1)
			{
				char cValue[2];

				memcpy(cValue, pResource->m_controls[18].GetString(), 2);

				pResource->m_bitFieldControl.DoDialog(pResource->m_pWindow, 16, cValue);

				pResource->m_controls[18].SetString(cValue);
			}
			else
			{
				for(i = 0; i < NUM_JUNK_CONTROLS; i++)
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
