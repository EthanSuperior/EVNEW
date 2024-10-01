// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CBitFieldControl.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include "CWindow.h"

#include "CErrorLog.h"

#include "CBitFieldControl.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CBitFieldControl::CBitFieldControl(void)
{
	int i;

	for(i = 0; i < 8; i++)
		m_cValue[i] = 0x00;

	m_iNumBits = 0;
}

CBitFieldControl::~CBitFieldControl(void)
{

}

int CBitFieldControl::DoDialog(CWindow *pWndParent, int iNumBits, char *pValue)
{
	if(iNumBits == 16)
	{
		m_iNumBits = 16;

		memcpy(m_cValue, pValue, 2);

		m_wndBits.SetExtraData(0, pWndParent->GetExtraData(0));
		m_wndBits.SetExtraData(1, pWndParent->GetExtraData(1));
		m_wndBits.SetExtraData(2, pWndParent->GetExtraData(2));
		m_wndBits.SetExtraData(5, (int)this);
		m_wndBits.SetDlgProc(CBitFieldControl::BitFieldControlDlgProc);
		m_wndBits.CreateAsDialog(pWndParent->GetInstance(), IDD_EDIT_BITS16, 1, pWndParent);

		memcpy(pValue, m_cValue, 2);
	}
	else if(iNumBits == 64)
	{
		m_iNumBits = 64;

		memcpy(m_cValue, pValue, 8);

		m_wndBits.SetExtraData(0, pWndParent->GetExtraData(0));
		m_wndBits.SetExtraData(1, pWndParent->GetExtraData(1));
		m_wndBits.SetExtraData(2, pWndParent->GetExtraData(2));
		m_wndBits.SetExtraData(5, (int)this);
		m_wndBits.SetDlgProc(CBitFieldControl::BitFieldControlDlgProc);
		m_wndBits.CreateAsDialog(pWndParent->GetInstance(), IDD_EDIT_BITS64, 1, pWndParent);

		memcpy(pValue, m_cValue, 8);
	}
	else
		return 0;

	return 1;
}

int CBitFieldControl::InitializeControls(HWND hwnd)
{
	if(m_iNumBits == 16)
	{
		m_controls[0].Create(hwnd, IDC_EDIT_BITS16_CHECK1, CCONTROL_TYPE_CHECK, -1);
		m_controls[0].SetInt(m_cValue[1] & 0x01);
		m_controls[1].Create(hwnd, IDC_EDIT_BITS16_CHECK2, CCONTROL_TYPE_CHECK, -1);
		m_controls[1].SetInt(m_cValue[1] & 0x02);
		m_controls[2].Create(hwnd, IDC_EDIT_BITS16_CHECK3, CCONTROL_TYPE_CHECK, -1);
		m_controls[2].SetInt(m_cValue[1] & 0x04);
		m_controls[3].Create(hwnd, IDC_EDIT_BITS16_CHECK4, CCONTROL_TYPE_CHECK, -1);
		m_controls[3].SetInt(m_cValue[1] & 0x08);
		m_controls[4].Create(hwnd, IDC_EDIT_BITS16_CHECK5, CCONTROL_TYPE_CHECK, -1);
		m_controls[4].SetInt(m_cValue[1] & 0x10);
		m_controls[5].Create(hwnd, IDC_EDIT_BITS16_CHECK6, CCONTROL_TYPE_CHECK, -1);
		m_controls[5].SetInt(m_cValue[1] & 0x20);
		m_controls[6].Create(hwnd, IDC_EDIT_BITS16_CHECK7, CCONTROL_TYPE_CHECK, -1);
		m_controls[6].SetInt(m_cValue[1] & 0x40);
		m_controls[7].Create(hwnd, IDC_EDIT_BITS16_CHECK8, CCONTROL_TYPE_CHECK, -1);
		m_controls[7].SetInt(m_cValue[1] & 0x80);
		m_controls[8].Create(hwnd, IDC_EDIT_BITS16_CHECK9, CCONTROL_TYPE_CHECK, -1);
		m_controls[8].SetInt(m_cValue[0] & 0x01);
		m_controls[9].Create(hwnd, IDC_EDIT_BITS16_CHECK10, CCONTROL_TYPE_CHECK, -1);
		m_controls[9].SetInt(m_cValue[0] & 0x02);
		m_controls[10].Create(hwnd, IDC_EDIT_BITS16_CHECK11, CCONTROL_TYPE_CHECK, -1);
		m_controls[10].SetInt(m_cValue[0] & 0x04);
		m_controls[11].Create(hwnd, IDC_EDIT_BITS16_CHECK12, CCONTROL_TYPE_CHECK, -1);
		m_controls[11].SetInt(m_cValue[0] & 0x08);
		m_controls[12].Create(hwnd, IDC_EDIT_BITS16_CHECK13, CCONTROL_TYPE_CHECK, -1);
		m_controls[12].SetInt(m_cValue[0] & 0x10);
		m_controls[13].Create(hwnd, IDC_EDIT_BITS16_CHECK14, CCONTROL_TYPE_CHECK, -1);
		m_controls[13].SetInt(m_cValue[0] & 0x20);
		m_controls[14].Create(hwnd, IDC_EDIT_BITS16_CHECK15, CCONTROL_TYPE_CHECK, -1);
		m_controls[14].SetInt(m_cValue[0] & 0x40);
		m_controls[15].Create(hwnd, IDC_EDIT_BITS16_CHECK16, CCONTROL_TYPE_CHECK, -1);
		m_controls[15].SetInt(m_cValue[0] & 0x80);
	}
	else if(m_iNumBits == 64)
	{
		m_controls[0].Create(hwnd, IDC_EDIT_BITS64_CHECK1, CCONTROL_TYPE_CHECK, -1);
		m_controls[0].SetInt(m_cValue[7] & 0x01);
		m_controls[1].Create(hwnd, IDC_EDIT_BITS64_CHECK2, CCONTROL_TYPE_CHECK, -1);
		m_controls[1].SetInt(m_cValue[7] & 0x02);
		m_controls[2].Create(hwnd, IDC_EDIT_BITS64_CHECK3, CCONTROL_TYPE_CHECK, -1);
		m_controls[2].SetInt(m_cValue[7] & 0x04);
		m_controls[3].Create(hwnd, IDC_EDIT_BITS64_CHECK4, CCONTROL_TYPE_CHECK, -1);
		m_controls[3].SetInt(m_cValue[7] & 0x08);
		m_controls[4].Create(hwnd, IDC_EDIT_BITS64_CHECK5, CCONTROL_TYPE_CHECK, -1);
		m_controls[4].SetInt(m_cValue[7] & 0x10);
		m_controls[5].Create(hwnd, IDC_EDIT_BITS64_CHECK6, CCONTROL_TYPE_CHECK, -1);
		m_controls[5].SetInt(m_cValue[7] & 0x20);
		m_controls[6].Create(hwnd, IDC_EDIT_BITS64_CHECK7, CCONTROL_TYPE_CHECK, -1);
		m_controls[6].SetInt(m_cValue[7] & 0x40);
		m_controls[7].Create(hwnd, IDC_EDIT_BITS64_CHECK8, CCONTROL_TYPE_CHECK, -1);
		m_controls[7].SetInt(m_cValue[7] & 0x80);
		m_controls[8].Create(hwnd, IDC_EDIT_BITS64_CHECK9, CCONTROL_TYPE_CHECK, -1);
		m_controls[8].SetInt(m_cValue[6] & 0x01);
		m_controls[9].Create(hwnd, IDC_EDIT_BITS64_CHECK10, CCONTROL_TYPE_CHECK, -1);
		m_controls[9].SetInt(m_cValue[6] & 0x02);
		m_controls[10].Create(hwnd, IDC_EDIT_BITS64_CHECK11, CCONTROL_TYPE_CHECK, -1);
		m_controls[10].SetInt(m_cValue[6] & 0x04);
		m_controls[11].Create(hwnd, IDC_EDIT_BITS64_CHECK12, CCONTROL_TYPE_CHECK, -1);
		m_controls[11].SetInt(m_cValue[6] & 0x08);
		m_controls[12].Create(hwnd, IDC_EDIT_BITS64_CHECK13, CCONTROL_TYPE_CHECK, -1);
		m_controls[12].SetInt(m_cValue[6] & 0x10);
		m_controls[13].Create(hwnd, IDC_EDIT_BITS64_CHECK14, CCONTROL_TYPE_CHECK, -1);
		m_controls[13].SetInt(m_cValue[6] & 0x20);
		m_controls[14].Create(hwnd, IDC_EDIT_BITS64_CHECK15, CCONTROL_TYPE_CHECK, -1);
		m_controls[14].SetInt(m_cValue[6] & 0x40);
		m_controls[15].Create(hwnd, IDC_EDIT_BITS64_CHECK16, CCONTROL_TYPE_CHECK, -1);
		m_controls[15].SetInt(m_cValue[6] & 0x80);
		m_controls[16].Create(hwnd, IDC_EDIT_BITS64_CHECK17, CCONTROL_TYPE_CHECK, -1);
		m_controls[16].SetInt(m_cValue[5] & 0x01);
		m_controls[17].Create(hwnd, IDC_EDIT_BITS64_CHECK18, CCONTROL_TYPE_CHECK, -1);
		m_controls[17].SetInt(m_cValue[5] & 0x02);
		m_controls[18].Create(hwnd, IDC_EDIT_BITS64_CHECK19, CCONTROL_TYPE_CHECK, -1);
		m_controls[18].SetInt(m_cValue[5] & 0x04);
		m_controls[19].Create(hwnd, IDC_EDIT_BITS64_CHECK20, CCONTROL_TYPE_CHECK, -1);
		m_controls[19].SetInt(m_cValue[5] & 0x08);
		m_controls[20].Create(hwnd, IDC_EDIT_BITS64_CHECK21, CCONTROL_TYPE_CHECK, -1);
		m_controls[20].SetInt(m_cValue[5] & 0x10);
		m_controls[21].Create(hwnd, IDC_EDIT_BITS64_CHECK22, CCONTROL_TYPE_CHECK, -1);
		m_controls[21].SetInt(m_cValue[5] & 0x20);
		m_controls[22].Create(hwnd, IDC_EDIT_BITS64_CHECK23, CCONTROL_TYPE_CHECK, -1);
		m_controls[22].SetInt(m_cValue[5] & 0x40);
		m_controls[23].Create(hwnd, IDC_EDIT_BITS64_CHECK24, CCONTROL_TYPE_CHECK, -1);
		m_controls[23].SetInt(m_cValue[5] & 0x80);
		m_controls[24].Create(hwnd, IDC_EDIT_BITS64_CHECK25, CCONTROL_TYPE_CHECK, -1);
		m_controls[24].SetInt(m_cValue[4] & 0x01);
		m_controls[25].Create(hwnd, IDC_EDIT_BITS64_CHECK26, CCONTROL_TYPE_CHECK, -1);
		m_controls[25].SetInt(m_cValue[4] & 0x02);
		m_controls[26].Create(hwnd, IDC_EDIT_BITS64_CHECK27, CCONTROL_TYPE_CHECK, -1);
		m_controls[26].SetInt(m_cValue[4] & 0x04);
		m_controls[27].Create(hwnd, IDC_EDIT_BITS64_CHECK28, CCONTROL_TYPE_CHECK, -1);
		m_controls[27].SetInt(m_cValue[4] & 0x08);
		m_controls[28].Create(hwnd, IDC_EDIT_BITS64_CHECK29, CCONTROL_TYPE_CHECK, -1);
		m_controls[28].SetInt(m_cValue[4] & 0x10);
		m_controls[29].Create(hwnd, IDC_EDIT_BITS64_CHECK30, CCONTROL_TYPE_CHECK, -1);
		m_controls[29].SetInt(m_cValue[4] & 0x20);
		m_controls[30].Create(hwnd, IDC_EDIT_BITS64_CHECK31, CCONTROL_TYPE_CHECK, -1);
		m_controls[30].SetInt(m_cValue[4] & 0x40);
		m_controls[31].Create(hwnd, IDC_EDIT_BITS64_CHECK32, CCONTROL_TYPE_CHECK, -1);
		m_controls[31].SetInt(m_cValue[4] & 0x80);
		m_controls[32].Create(hwnd, IDC_EDIT_BITS64_CHECK33, CCONTROL_TYPE_CHECK, -1);
		m_controls[32].SetInt(m_cValue[3] & 0x01);
		m_controls[33].Create(hwnd, IDC_EDIT_BITS64_CHECK34, CCONTROL_TYPE_CHECK, -1);
		m_controls[33].SetInt(m_cValue[3] & 0x02);
		m_controls[34].Create(hwnd, IDC_EDIT_BITS64_CHECK35, CCONTROL_TYPE_CHECK, -1);
		m_controls[34].SetInt(m_cValue[3] & 0x04);
		m_controls[35].Create(hwnd, IDC_EDIT_BITS64_CHECK36, CCONTROL_TYPE_CHECK, -1);
		m_controls[35].SetInt(m_cValue[3] & 0x08);
		m_controls[36].Create(hwnd, IDC_EDIT_BITS64_CHECK37, CCONTROL_TYPE_CHECK, -1);
		m_controls[36].SetInt(m_cValue[3] & 0x10);
		m_controls[37].Create(hwnd, IDC_EDIT_BITS64_CHECK38, CCONTROL_TYPE_CHECK, -1);
		m_controls[37].SetInt(m_cValue[3] & 0x20);
		m_controls[38].Create(hwnd, IDC_EDIT_BITS64_CHECK39, CCONTROL_TYPE_CHECK, -1);
		m_controls[38].SetInt(m_cValue[3] & 0x40);
		m_controls[39].Create(hwnd, IDC_EDIT_BITS64_CHECK40, CCONTROL_TYPE_CHECK, -1);
		m_controls[39].SetInt(m_cValue[3] & 0x80);
		m_controls[40].Create(hwnd, IDC_EDIT_BITS64_CHECK41, CCONTROL_TYPE_CHECK, -1);
		m_controls[40].SetInt(m_cValue[2] & 0x01);
		m_controls[41].Create(hwnd, IDC_EDIT_BITS64_CHECK42, CCONTROL_TYPE_CHECK, -1);
		m_controls[41].SetInt(m_cValue[2] & 0x02);
		m_controls[42].Create(hwnd, IDC_EDIT_BITS64_CHECK43, CCONTROL_TYPE_CHECK, -1);
		m_controls[42].SetInt(m_cValue[2] & 0x04);
		m_controls[43].Create(hwnd, IDC_EDIT_BITS64_CHECK44, CCONTROL_TYPE_CHECK, -1);
		m_controls[43].SetInt(m_cValue[2] & 0x08);
		m_controls[44].Create(hwnd, IDC_EDIT_BITS64_CHECK45, CCONTROL_TYPE_CHECK, -1);
		m_controls[44].SetInt(m_cValue[2] & 0x10);
		m_controls[45].Create(hwnd, IDC_EDIT_BITS64_CHECK46, CCONTROL_TYPE_CHECK, -1);
		m_controls[45].SetInt(m_cValue[2] & 0x20);
		m_controls[46].Create(hwnd, IDC_EDIT_BITS64_CHECK47, CCONTROL_TYPE_CHECK, -1);
		m_controls[46].SetInt(m_cValue[2] & 0x40);
		m_controls[47].Create(hwnd, IDC_EDIT_BITS64_CHECK48, CCONTROL_TYPE_CHECK, -1);
		m_controls[47].SetInt(m_cValue[2] & 0x80);
		m_controls[48].Create(hwnd, IDC_EDIT_BITS64_CHECK49, CCONTROL_TYPE_CHECK, -1);
		m_controls[48].SetInt(m_cValue[1] & 0x01);
		m_controls[49].Create(hwnd, IDC_EDIT_BITS64_CHECK50, CCONTROL_TYPE_CHECK, -1);
		m_controls[49].SetInt(m_cValue[1] & 0x02);
		m_controls[50].Create(hwnd, IDC_EDIT_BITS64_CHECK51, CCONTROL_TYPE_CHECK, -1);
		m_controls[50].SetInt(m_cValue[1] & 0x04);
		m_controls[51].Create(hwnd, IDC_EDIT_BITS64_CHECK52, CCONTROL_TYPE_CHECK, -1);
		m_controls[51].SetInt(m_cValue[1] & 0x08);
		m_controls[52].Create(hwnd, IDC_EDIT_BITS64_CHECK53, CCONTROL_TYPE_CHECK, -1);
		m_controls[52].SetInt(m_cValue[1] & 0x10);
		m_controls[53].Create(hwnd, IDC_EDIT_BITS64_CHECK54, CCONTROL_TYPE_CHECK, -1);
		m_controls[53].SetInt(m_cValue[1] & 0x20);
		m_controls[54].Create(hwnd, IDC_EDIT_BITS64_CHECK55, CCONTROL_TYPE_CHECK, -1);
		m_controls[54].SetInt(m_cValue[1] & 0x40);
		m_controls[55].Create(hwnd, IDC_EDIT_BITS64_CHECK56, CCONTROL_TYPE_CHECK, -1);
		m_controls[55].SetInt(m_cValue[1] & 0x80);
		m_controls[56].Create(hwnd, IDC_EDIT_BITS64_CHECK57, CCONTROL_TYPE_CHECK, -1);
		m_controls[56].SetInt(m_cValue[0] & 0x01);
		m_controls[57].Create(hwnd, IDC_EDIT_BITS64_CHECK58, CCONTROL_TYPE_CHECK, -1);
		m_controls[57].SetInt(m_cValue[0] & 0x02);
		m_controls[58].Create(hwnd, IDC_EDIT_BITS64_CHECK59, CCONTROL_TYPE_CHECK, -1);
		m_controls[58].SetInt(m_cValue[0] & 0x04);
		m_controls[59].Create(hwnd, IDC_EDIT_BITS64_CHECK60, CCONTROL_TYPE_CHECK, -1);
		m_controls[59].SetInt(m_cValue[0] & 0x08);
		m_controls[60].Create(hwnd, IDC_EDIT_BITS64_CHECK61, CCONTROL_TYPE_CHECK, -1);
		m_controls[60].SetInt(m_cValue[0] & 0x10);
		m_controls[61].Create(hwnd, IDC_EDIT_BITS64_CHECK62, CCONTROL_TYPE_CHECK, -1);
		m_controls[61].SetInt(m_cValue[0] & 0x20);
		m_controls[62].Create(hwnd, IDC_EDIT_BITS64_CHECK63, CCONTROL_TYPE_CHECK, -1);
		m_controls[62].SetInt(m_cValue[0] & 0x40);
		m_controls[63].Create(hwnd, IDC_EDIT_BITS64_CHECK64, CCONTROL_TYPE_CHECK, -1);
		m_controls[63].SetInt(m_cValue[0] & 0x80);
	}

	return 1;
}

int CBitFieldControl::CloseAndSave(void)
{
	int i;

	for(i = 0; i < m_iNumBits / 8; i++)
		m_cValue[i] = 0x00;

	if(m_iNumBits == 16)
	{
		m_cValue[1] |= m_controls[0].GetInt();
		m_cValue[1] |= m_controls[1].GetInt()  << 1;
		m_cValue[1] |= m_controls[2].GetInt()  << 2;
		m_cValue[1] |= m_controls[3].GetInt()  << 3;
		m_cValue[1] |= m_controls[4].GetInt()  << 4;
		m_cValue[1] |= m_controls[5].GetInt()  << 5;
		m_cValue[1] |= m_controls[6].GetInt()  << 6;
		m_cValue[1] |= m_controls[7].GetInt()  << 7;
		m_cValue[0] |= m_controls[8].GetInt();
		m_cValue[0] |= m_controls[9].GetInt()  << 1;
		m_cValue[0] |= m_controls[10].GetInt() << 2;
		m_cValue[0] |= m_controls[11].GetInt() << 3;
		m_cValue[0] |= m_controls[12].GetInt() << 4;
		m_cValue[0] |= m_controls[13].GetInt() << 5;
		m_cValue[0] |= m_controls[14].GetInt() << 6;
		m_cValue[0] |= m_controls[15].GetInt() << 7;
	}
	else if(m_iNumBits == 64)
	{
		m_cValue[7] |= m_controls[0].GetInt();
		m_cValue[7] |= m_controls[1].GetInt()  << 1;
		m_cValue[7] |= m_controls[2].GetInt()  << 2;
		m_cValue[7] |= m_controls[3].GetInt()  << 3;
		m_cValue[7] |= m_controls[4].GetInt()  << 4;
		m_cValue[7] |= m_controls[5].GetInt()  << 5;
		m_cValue[7] |= m_controls[6].GetInt()  << 6;
		m_cValue[7] |= m_controls[7].GetInt()  << 7;
		m_cValue[6] |= m_controls[8].GetInt();
		m_cValue[6] |= m_controls[9].GetInt()  << 1;
		m_cValue[6] |= m_controls[10].GetInt() << 2;
		m_cValue[6] |= m_controls[11].GetInt() << 3;
		m_cValue[6] |= m_controls[12].GetInt() << 4;
		m_cValue[6] |= m_controls[13].GetInt() << 5;
		m_cValue[6] |= m_controls[14].GetInt() << 6;
		m_cValue[6] |= m_controls[15].GetInt() << 7;
		m_cValue[5] |= m_controls[16].GetInt();
		m_cValue[5] |= m_controls[17].GetInt() << 1;
		m_cValue[5] |= m_controls[18].GetInt() << 2;
		m_cValue[5] |= m_controls[19].GetInt() << 3;
		m_cValue[5] |= m_controls[20].GetInt() << 4;
		m_cValue[5] |= m_controls[21].GetInt() << 5;
		m_cValue[5] |= m_controls[22].GetInt() << 6;
		m_cValue[5] |= m_controls[23].GetInt() << 7;
		m_cValue[4] |= m_controls[24].GetInt();
		m_cValue[4] |= m_controls[25].GetInt() << 1;
		m_cValue[4] |= m_controls[26].GetInt() << 2;
		m_cValue[4] |= m_controls[27].GetInt() << 3;
		m_cValue[4] |= m_controls[28].GetInt() << 4;
		m_cValue[4] |= m_controls[29].GetInt() << 5;
		m_cValue[4] |= m_controls[30].GetInt() << 6;
		m_cValue[4] |= m_controls[31].GetInt() << 7;
		m_cValue[3] |= m_controls[32].GetInt();
		m_cValue[3] |= m_controls[33].GetInt() << 1;
		m_cValue[3] |= m_controls[34].GetInt() << 2;
		m_cValue[3] |= m_controls[35].GetInt() << 3;
		m_cValue[3] |= m_controls[36].GetInt() << 4;
		m_cValue[3] |= m_controls[37].GetInt() << 5;
		m_cValue[3] |= m_controls[38].GetInt() << 6;
		m_cValue[3] |= m_controls[39].GetInt() << 7;
		m_cValue[2] |= m_controls[40].GetInt();
		m_cValue[2] |= m_controls[41].GetInt() << 1;
		m_cValue[2] |= m_controls[42].GetInt() << 2;
		m_cValue[2] |= m_controls[43].GetInt() << 3;
		m_cValue[2] |= m_controls[44].GetInt() << 4;
		m_cValue[2] |= m_controls[45].GetInt() << 5;
		m_cValue[2] |= m_controls[46].GetInt() << 6;
		m_cValue[2] |= m_controls[47].GetInt() << 7;
		m_cValue[1] |= m_controls[48].GetInt();
		m_cValue[1] |= m_controls[49].GetInt() << 1;
		m_cValue[1] |= m_controls[50].GetInt() << 2;
		m_cValue[1] |= m_controls[51].GetInt() << 3;
		m_cValue[1] |= m_controls[52].GetInt() << 4;
		m_cValue[1] |= m_controls[53].GetInt() << 5;
		m_cValue[1] |= m_controls[54].GetInt() << 6;
		m_cValue[1] |= m_controls[55].GetInt() << 7;
		m_cValue[0] |= m_controls[56].GetInt();
		m_cValue[0] |= m_controls[57].GetInt() << 1;
		m_cValue[0] |= m_controls[58].GetInt() << 2;
		m_cValue[0] |= m_controls[59].GetInt() << 3;
		m_cValue[0] |= m_controls[60].GetInt() << 4;
		m_cValue[0] |= m_controls[61].GetInt() << 5;
		m_cValue[0] |= m_controls[62].GetInt() << 6;
		m_cValue[0] |= m_controls[63].GetInt() << 7;
	}

	for(i = 0; i < m_iNumBits; i++)
		m_controls[i].Destroy();

	m_wndBits.Destroy();

	return 1;
}

int CBitFieldControl::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < m_iNumBits; i++)
		m_controls[i].Destroy();

	m_wndBits.Destroy();

	return 1;
}

BOOL CBitFieldControl::BitFieldControlDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow          *pWindow;
	CBitFieldControl *pBitFieldControl = NULL;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pBitFieldControl = (CBitFieldControl *)pWindow->GetExtraData(5);

	int i;

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			pBitFieldControl->InitializeControls(hwnd);

			return TRUE;

			break;
		}

		case WM_SYSCOMMAND:
		{
			if(wparam == SC_CLOSE)
			{
				pBitFieldControl->CloseAndDontSave();

				return TRUE;
			}

			break;
		}

		case WM_COMMAND:
		{
			int iNotifyCode = HIWORD(wparam);
			int iControlID  = LOWORD(wparam);

			if((iControlID == IDC_EDIT_BITS16_CANCEL) || (iControlID == IDC_EDIT_BITS64_CANCEL))
			{
				pBitFieldControl->CloseAndDontSave();
			}
			else if((iControlID == IDC_EDIT_BITS16_OK) || (iControlID == IDC_EDIT_BITS64_OK))
			{
				pBitFieldControl->CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_CBITFIELDCONTROL_CONTROLS; i++)
				{
					if(iControlID == pBitFieldControl->m_controls[i].GetControlID())
					{
						pBitFieldControl->m_controls[i].ProcessMessage(iNotifyCode);

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
