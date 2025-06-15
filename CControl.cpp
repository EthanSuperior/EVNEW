// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CControl.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include "CWindow.h"
#include "CControl.h"
#include "Workspace.h"

#include <commctrl.h>
#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CControl::CControl(void)
{
	m_hwndDialog  = NULL;
	m_hwndControl = NULL;

	m_iControlID = 0;

	m_iType = CCONTROL_TYPE_NULL;

	m_iHelpStringID = 0;

	m_iMinValue = 0x80000000;
	m_iMaxValue = 0x7FFFFFFF;

	m_iIntValue = 0;

	m_szStringValue = "";

	m_hbmColor = NULL;
}

CControl::~CControl(void)
{
	Destroy();
}

int CControl::Create(HWND hwndDialog, int iControlID, int iType, int iHelpStringID)
{
	Destroy();

	m_hwndDialog  = hwndDialog;

	m_iControlID = iControlID;

	m_iType = iType;

	m_iHelpStringID = iHelpStringID;

	m_hwndControl = GetDlgItem(m_hwndDialog, m_iControlID);
	if (m_iType >= CCONTROL_TYPE_HEXINT16 && m_iType <= CCONTROL_TYPE_STRARB)
		g_OldEditProc = (WNDPROC)SetWindowLongPtr(m_hwndControl, GWLP_WNDPROC, (LONG_PTR)CControl::TextHelperProc);
	SetWindowLongPtr(m_hwndControl, GWLP_USERDATA, (LONG_PTR)this);
	if(m_iType == CCONTROL_TYPE_COLOR)
		CreateBitmap(SwapColorRedBlue(m_iIntValue));

	HINSTANCE hInstance;

	UINT iTooltipID = 0;

	char szBuffer[1024];

	if(iHelpStringID != -1)
	{
		hInstance = CWindow::GetWindow(hwndDialog, 1)->GetInstance();

		LoadString(hInstance, iHelpStringID, szBuffer, 1024);

		RECT rectControl;

		hwndTooltip = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL, WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hwndDialog, NULL, hInstance, NULL);

		SetWindowPos(hwndTooltip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

		GetClientRect(m_hwndControl, &rectControl);

		toolInfo.cbSize   = sizeof(TOOLINFO);
		toolInfo.uFlags = TTF_SUBCLASS | TTF_IDISHWND | TTF_TRANSPARENT;
		toolInfo.hwnd     = m_hwndControl;
		toolInfo.hinst    = hInstance;
		toolInfo.uId      = (UINT_PTR) m_hwndControl;
		toolInfo.lpszText = szBuffer;

		toolInfo.rect.left   = rectControl.left;    
		toolInfo.rect.top    = rectControl.top;
		toolInfo.rect.right  = rectControl.right;
		toolInfo.rect.bottom = rectControl.bottom;

		SendMessage(hwndTooltip, TTM_ADDTOOL, 0, (LPARAM)&toolInfo);
		SendMessage(hwndTooltip, TTM_SETMAXTIPWIDTH, 0, (LPARAM)200);
		SendMessage(hwndTooltip, TTM_SETDELAYTIME, TTDT_AUTOPOP, (LPARAM)10000);
	}

	return 1;
}

WNDPROC CControl::g_OldButtonProc = nullptr;
LRESULT CALLBACK CControl::EmbeddedButtonProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
	{
		LRESULT result = CallWindowProc(g_OldButtonProc, hwnd, msg, wParam, lParam);

		HDC hdc = GetDC(hwnd);
		RECT rc;
		GetClientRect(hwnd, &rc);

		RECT rcButton = rc;
		rcButton.left = rc.right - 8;
		rcButton.top += 2;
		rcButton.bottom -= 2;
		rcButton.right -= 2;

		DrawTextW(hdc, L"⋮", -1, &rcButton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		ReleaseDC(hwnd, hdc);
		return result;
	}
	case WM_LBUTTONDOWN:
	{
		RECT rc;
		GetClientRect(hwnd, &rc);
		int x = GET_X_LPARAM(lParam);

		if (x >= rc.right - 10) {
			CControl* pThis = (CControl*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			auto base = CWindow::GetWindow(pThis->m_hwndDialog, 1);
			HINSTANCE hInstance = base->GetInstance();
			RefDialogData data;
			data.helpStringID = pThis->m_iHelpStringID;
			data.constItems = pThis->m_vRefConstItems;
			data.refItems = pThis->m_vRefMapItems;
			CWindow m_wndRefSelect;
			m_wndRefSelect.SetExtraData(0, (int)&data);
			m_wndRefSelect.SetDlgProc(CControl::RezSelectDlgProc);
			m_wndRefSelect.CreateAsDialog(hInstance, IDD_REZ_SEL, 1, base);
			pThis->SetInt(data.selectedID);
			return 0;
		}
		break;
	}
	}
	return CallWindowProc(g_OldButtonProc, hwnd, msg, wParam, lParam);
}

BOOL CControl::RezSelectDlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CWindow* pWindow = CWindow::GetWindow(hwndDlg, 1);
	RefDialogData* pData;
	if (pWindow != NULL)
		pData = (RefDialogData*)pWindow->GetExtraData(0);
	switch (msg)
	{
	case WM_INITDIALOG:
	{

		// -- 1. Populate Help Text
		char helpBuffer[1024];
		LoadString(GetModuleHandle(NULL), pData->helpStringID, helpBuffer, sizeof(helpBuffer));
		SetDlgItemText(hwndDlg, IDC_REZ_DESCRIPTION, helpBuffer);

		// -- 2. Populate Filter Dropdown
		for (const RefItem& ref : pData->refItems) {
			std::string label = ref.description + g_szResourceTypes[ref.CNR_TYPE];
			SendDlgItemMessageA(hwndDlg, IDC_REZ_FILTER, CB_ADDSTRING, 0, (LPARAM)label.c_str());
		}
		SendDlgItemMessage(hwndDlg, IDC_REZ_FILTER, CB_SETCURSEL, 0, 0);

		// -- 3. Populate initial list (constItems + refItems[0])
		HWND hList = GetDlgItem(hwndDlg, IDC_REZ_LIST);

		// Const items
		for (const ConstItem& c : pData->constItems) {
			std::string line = std::to_string(c.value) + ": " + c.description;
			SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)line.c_str());
		}

		// Refs
		const RefItem& firstRef = pData->refItems[0];
		for (auto& n: Workspace::Names(firstRef.CNR_TYPE, firstRef.offset))
			SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)n.c_str());

		return TRUE;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_REZ_FILTER:
			if (HIWORD(wParam) == CBN_SELCHANGE) {
				int sel = (int)SendDlgItemMessage(hwndDlg, IDC_REZ_FILTER, CB_GETCURSEL, 0, 0);
				if (sel >= 0 && sel < pData->refItems.size()) {
					HWND hList = GetDlgItem(hwndDlg, IDC_REZ_LIST);
					SendMessage(hList, LB_RESETCONTENT, 0, 0);

					// Consts again
					for (const ConstItem& c : pData->constItems) {
						std::string line = std::to_string(c.value) + ": " + c.description;
						SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)line.c_str());
					}

					const RefItem& ref = pData->refItems[sel];
					for (auto& n : Workspace::Names(ref.CNR_TYPE, ref.offset))
						SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)n.c_str());
				}
			}
			break;
		case IDC_REZ_LIST:
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				int sel = (int)SendDlgItemMessage(hwndDlg, IDC_REZ_LIST, LB_GETCURSEL, 0, 0);
				if (sel >= 0) {
					char buf[256];
					SendDlgItemMessageA(hwndDlg, IDC_REZ_LIST, LB_GETTEXT, sel, (LPARAM)buf);
					SetDlgItemText(hwndDlg, IDC_REZ_SELECTED, buf);
				}
			}
			break;

		case IDOK:
		{
			int sel = (int)SendDlgItemMessage(hwndDlg, IDC_REZ_LIST, LB_GETCURSEL, 0, 0);
			if (sel >= 0) {
				char buf[256];
				SendDlgItemMessageA(hwndDlg, IDC_REZ_LIST, LB_GETTEXT, sel, (LPARAM)buf);

				// Get the number before the colon
				int id = -1;
				sscanf(buf, "%d", &id);
				pData->selectedID = id;
			}
			EndDialog(hwndDlg, IDOK);
			return TRUE;
		}

		case IDCANCEL:
			EndDialog(hwndDlg, IDCANCEL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

WNDPROC CControl::g_OldEditProc = nullptr;
LRESULT CALLBACK CControl::TextHelperProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN) {
		if ((GetKeyState(VK_CONTROL) & 0x8000) && wParam == 'A') {
			SendMessage(hwnd, EM_SETSEL, 0, -1); // Select all
			return 0; // Consume the message
		}
	}
	return CallWindowProc(g_OldEditProc, hwnd, msg, wParam, lParam);
}


int CControl::Destroy(void)
{
	m_hwndDialog  = NULL;
	m_hwndControl = NULL;

	m_iControlID = 0;

	m_iType = CCONTROL_TYPE_NULL;

	m_iHelpStringID = 0;

	m_iMinValue = 0x80000000;
	m_iMaxValue = 0x7FFFFFFF;

	m_iIntValue = 0;

	m_szStringValue = "";

	if(m_hbmColor != NULL)
	{
		DeleteObject(m_hbmColor);

		m_hbmColor = NULL;
	}

	return 1;
}

int CControl::ProcessMessage(int iNotifyCode)
{
	char szBuffer[1024];
	char *pBuffer;

	int iLength;

	int i;

	if(iNotifyCode == EN_CHANGE)
	{
		if(m_iType == CCONTROL_TYPE_INT)
		{
			FixIntegerField(m_hwndControl);

			Edit_GetText(m_hwndControl, szBuffer, 1024);

			m_iIntValue = FromString<int>((std::string)szBuffer);

			m_szStringValue = szBuffer;
		}
		else if(m_iType == CCONTROL_TYPE_HEXINT16)
		{
			FixHexIntegerField(m_hwndControl);

			Edit_GetText(m_hwndControl, szBuffer, 1024);

			iLength = strlen(szBuffer);

			if(iLength < 4)
			{
				for(i = iLength - 1; i >= 0; i--)
					szBuffer[4 - iLength + i] = szBuffer[i];

				for(i = 3 - iLength; i >= 0; i--)
					szBuffer[i] = '0';
			}
			else if(iLength > 4)
			{
				for(i = 0; i < 4; i++)
					szBuffer[i] = szBuffer[iLength + i - 4];
			}

			szBuffer[4] = '\0';

			for(i = 0; i < 4; i++)
			{
				if((szBuffer[i] >= 'A') && (szBuffer[i] <= 'F'))
					szBuffer[i] += '0' - 'A' + 10;
			}

			m_szStringValue.resize(3);

			for(i = 0; i < 2; i++)
				m_szStringValue[i] = (szBuffer[2 * i + 1] - '0') | ((szBuffer[2 * i] - '0') << 4);

			m_szStringValue[2] = '\0';
		}
		else if(m_iType == CCONTROL_TYPE_HEXINT32)
		{
			FixHexIntegerField(m_hwndControl);

			Edit_GetText(m_hwndControl, szBuffer, 1024);

			iLength = strlen(szBuffer);

			if(iLength < 8)
			{
				for(i = iLength - 1; i >= 0; i--)
					szBuffer[8 - iLength + i] = szBuffer[i];

				for(i = 7 - iLength; i >= 0; i--)
					szBuffer[i] = '0';
			}
			else if(iLength > 8)
			{
				for(i = 0; i < 8; i++)
					szBuffer[i] = szBuffer[iLength + i - 8];
			}

			szBuffer[8] = '\0';

			for(i = 0; i < 8; i++)
			{
				if((szBuffer[i] >= 'A') && (szBuffer[i] <= 'F'))
					szBuffer[i] += '0' - 'A' + 10;
			}

			m_szStringValue.resize(5);

			for(i = 0; i < 4; i++)
				m_szStringValue[i] = (szBuffer[2 * i + 1] - '0') | ((szBuffer[2 * i] - '0') << 4);

			m_szStringValue[4] = '\0';
		}
		else if(m_iType == CCONTROL_TYPE_HEXINT64)
		{
			FixHexIntegerField(m_hwndControl);

			Edit_GetText(m_hwndControl, szBuffer, 1024);

			iLength = strlen(szBuffer);

			if(iLength < 16)
			{
				for(i = iLength - 1; i >= 0; i--)
					szBuffer[16 - iLength + i] = szBuffer[i];

				for(i = 15 - iLength; i >= 0; i--)
					szBuffer[i] = '0';
			}
			else if(iLength > 16)
			{
				for(i = 0; i < 16; i++)
					szBuffer[i] = szBuffer[iLength + i - 16];
			}

			szBuffer[16] = '\0';

			for(i = 0; i < 16; i++)
			{
				if((szBuffer[i] >= 'A') && (szBuffer[i] <= 'F'))
					szBuffer[i] += '0' - 'A' + 10;
			}

			m_szStringValue.resize(9);

			for(i = 0; i < 8; i++)
				m_szStringValue[i] = (szBuffer[2 * i + 1] - '0') | ((szBuffer[2 * i] - '0') << 4);

			m_szStringValue[8] = '\0';
		}
		else if(m_iType == CCONTROL_TYPE_STR8)
		{
			Edit_GetText(m_hwndControl, szBuffer, 8);

			szBuffer[7] = '\0';

			m_szStringValue = szBuffer;
		}
		else if(m_iType == CCONTROL_TYPE_STR16)
		{
			Edit_GetText(m_hwndControl, szBuffer, 16);

			szBuffer[15] = '\0';

			m_szStringValue = szBuffer;
		}
		else if(m_iType == CCONTROL_TYPE_STR32)
		{
			Edit_GetText(m_hwndControl, szBuffer, 32);

			szBuffer[31] = '\0';

			m_szStringValue = szBuffer;
		}
		else if(m_iType == CCONTROL_TYPE_STR33)
		{
			Edit_GetText(m_hwndControl, szBuffer, 33);

			szBuffer[32] = '\0';

			m_szStringValue = szBuffer;
		}
		else if(m_iType == CCONTROL_TYPE_STR64)
		{
			Edit_GetText(m_hwndControl, szBuffer, 64);

			szBuffer[63] = '\0';

			m_szStringValue = szBuffer;
		}
		else if(m_iType == CCONTROL_TYPE_STR65)
		{
			Edit_GetText(m_hwndControl, szBuffer, 65);

			szBuffer[64] = '\0';

			m_szStringValue = szBuffer;
		}
		else if(m_iType == CCONTROL_TYPE_STR128)
		{
			Edit_GetText(m_hwndControl, szBuffer, 128);

			szBuffer[127] = '\0';

			m_szStringValue = szBuffer;
		}
		else if(m_iType == CCONTROL_TYPE_STR255)
		{
			Edit_GetText(m_hwndControl, szBuffer, 255);

			szBuffer[254] = '\0';

			m_szStringValue = szBuffer;
		}
		else if(m_iType == CCONTROL_TYPE_STR256)
		{
			Edit_GetText(m_hwndControl, szBuffer, 256);

			szBuffer[255] = '\0';

			m_szStringValue = szBuffer;
		}
		else if(m_iType == CCONTROL_TYPE_STR1024)
		{
			Edit_GetText(m_hwndControl, szBuffer, 1024);

			szBuffer[1023] = '\0';

			m_szStringValue = szBuffer;
		}
		else if(m_iType == CCONTROL_TYPE_STRARB)
		{
			int iLength = Edit_GetTextLength(m_hwndControl);

			pBuffer = NULL;

			pBuffer = new char[iLength + 1];

			if(pBuffer == NULL)
				throw CException("Error: could not allocate memory for string!");

			Edit_GetText(m_hwndControl, pBuffer, iLength + 1);

			pBuffer[iLength] = '\0';

			m_szStringValue = pBuffer;

			delete [] pBuffer;
		}
		Notified();
	}
	else if(iNotifyCode == BN_CLICKED)
	{
		if(m_iType == CCONTROL_TYPE_CHECK)
		{
			m_iIntValue = (Button_GetCheck(m_hwndControl) == BST_CHECKED) ? (1) : (0);
		}
		else if(m_iType == CCONTROL_TYPE_COLOR)
		{
			if(DoColorChooser(CWindow::GetWindow(m_hwndDialog, 1), (UINT *)&m_iIntValue))
			{
				CreateBitmap(m_iIntValue);

				SendMessage(m_hwndControl, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hbmColor);
			}
		}
	}
	else if(iNotifyCode == CBN_SELCHANGE)
	{
		if (m_iType == CCONTROL_TYPE_COMBOBOX)
		{
			m_iIntValue = ComboBox_GetCurSel(m_hwndControl);

			if (m_iIntValue == CB_ERR)
				m_iIntValue = 0;
		}
		else if (m_iType == CCONTROL_TYPE_REZBOX)
		{
			int index = ComboBox_GetCurSel(m_hwndControl);
			
			if (index == CB_ERR) m_iIntValue = 0;
			else {
				m_iIntValue = -1;

				char buffer[256] = {};
				ComboBox_GetLBText(m_hwndControl, index, buffer);
				for (size_t i = 0; i < m_vRezItems.size(); ++i) {
					if (m_vRezItems[i] == buffer) {
						m_szStringValue = buffer;
						m_iIntValue = i;
						break;
					}
				}
			}
		}
	}
	else if (iNotifyCode == CBN_EDITUPDATE)
	{
		if (m_iType == CCONTROL_TYPE_REZBOX)
		{
			char buffer[256] = {};
			GetWindowTextA(m_hwndControl, buffer, sizeof(buffer));

			DWORD selStart = 0, selEnd = 0;
			SendMessageA(m_hwndControl, CB_GETEDITSEL, (WPARAM)&selStart, (LPARAM)&selEnd);

			// Clear current items
			ComboBox_ResetContent(m_hwndControl);
			auto toLower = [](const std::string& s) {
				std::string r = s;
				std::transform(r.begin(), r.end(), r.begin(),
					[](unsigned char c) { return std::tolower(c); });
				return r;
				};
			std::string typedText = toLower(buffer);
			// Add matching items
			for (const std::string& item : m_vRezItems) {
				if (toLower(item).find(typedText) != std::string::npos) {
					ComboBox_AddString(m_hwndControl, item.c_str());
				}
			}

			// Restore typed text and caret
			SetWindowTextA(m_hwndControl, buffer);
			SendMessageA(m_hwndControl, CB_SETEDITSEL, 0, MAKELPARAM(selStart, selEnd));
		}
	}
	else if (iNotifyCode == WM_KEYDOWN)
	{
		if ((GetKeyState(VK_CONTROL)))
			if(GetAsyncKeyState('A')) {
				SendMessage(m_hwndControl, EM_SETSEL, 0, -1);  // Select all text
				return 0; // Consume message
			}
	}
	else {
		std::ofstream ofstream("log.txt", std::ios::app);
		ofstream << iNotifyCode << std::endl;
	}
	return 1;
}

int CControl::IsValid(void)
{
	if(m_iType == CCONTROL_TYPE_INT)
	{
		if((m_szStringValue.size() == 0) || (m_iIntValue < m_iMinValue) || (m_iIntValue > m_iMaxValue))
			return 0;
	}

	return 1;
}

int CControl::SetMinValue(int iMinValue)
{
	m_iMinValue = iMinValue;

	return 1;
}

int CControl::SetMaxValue(int iMaxValue)
{
	m_iMaxValue = iMaxValue;

	return 1;
}

int CControl::SetComboStrings(int iNumStrings, const std::string *pStrings)
{
	if(m_iType != CCONTROL_TYPE_COMBOBOX)
		return 0;

	int i;

	int cbErr = CB_ERR;

	int iResult = ComboBox_ResetContent(m_hwndControl);

	for(i = 0; i < iNumStrings; i++)
	{
		iResult = ComboBox_AddString(m_hwndControl, pStrings[i].c_str());
	}

	int iCount = ComboBox_GetCount(m_hwndControl);

	return 1;
}

void CControl::SetRefInfoMap(int refBox, std::vector<ConstItem>& constItms, std::vector<RefItem>& refItms)
{
	m_iRefBox = GetDlgItem(m_hwndDialog, refBox);

	TOOLINFO toolInfoLabel = toolInfo;
	toolInfoLabel.hwnd = m_iRefBox;
	toolInfoLabel.uId = (UINT_PTR)refBox;
	SendMessage(hwndTooltip, TTM_ADDTOOL, 0, (LPARAM)&toolInfoLabel);

	m_vRefConstItems = constItms;
	m_vRefMapItems = refItms;

	CControl::g_OldButtonProc = (WNDPROC)SetWindowLongPtr(m_hwndControl, GWLP_WNDPROC, (LONG_PTR)CControl::EmbeddedButtonProc);
	// Get position of the edit control
	//RECT rcEdit;
	//GetWindowRect(m_hwndControl, &rcEdit);
	//ScreenToClient(m_hwndDialog, (LPPOINT)&rcEdit.left);
	//ScreenToClient(m_hwndDialog, (LPPOINT)&rcEdit.right);

	//// Create the "..." button next to it
	//HWND hwndBrowse = CreateWindowEx(
	//	0,
	//	"BUTTON",
	//	"...",
	//	WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
	//	rcEdit.right + 4, rcEdit.top, 20, rcEdit.bottom - rcEdit.top,
	//	m_hwndDialog,
	//	(HMENU)(m_iControlID + 20000),
	//	GetModuleHandle(NULL),
	//	NULL
	//);
	Notified();
}

void CControl::Notified()
{
	if (m_iRefBox == NULL) return;
	int id = GetInt();

	for (auto& item : m_vRefConstItems) if (item.value == id) {
		Static_SetText(m_iRefBox, item.description.c_str());
		return;
	}
	id += 128;
	for (auto& item : m_vRefMapItems) 
		if ((id - item.offset) >= 128 && (id - item.offset) <= CNR_MAX_VALID_IDS[item.CNR_TYPE]) {
			Static_SetText(m_iRefBox,
				(item.description + Workspace::RezStr(item.CNR_TYPE, id - item.offset)).c_str());
			return;
		}
	Static_SetText(m_iRefBox, "Invalid Option");
}

int CControl::SetRezType(int rezNum)
{
	if (m_iType != CCONTROL_TYPE_REZBOX)
		return 0;
	ComboBox_ResetContent(m_hwndControl);
	m_vRezItems = Workspace::Names(rezNum);
	for (const auto& name : m_vRezItems) ComboBox_AddString(m_hwndControl, name.c_str());
	ComboBox_GetCount(m_hwndControl);
	SetInt(0);
	return 1;
}

int CControl::GetMinValue(void)
{
	return m_iMinValue;
}

int CControl::GetMaxValue(void)
{
	return m_iMaxValue;
}

int CControl::GetControlID(void)
{
	return m_iControlID;
}

int CControl::GetType(void)
{
	return m_iType;
}

HWND CControl::GetHWND(void)
{
	return m_hwndControl;
}

int CControl::GetInt(void)
{
	return m_iIntValue;
}

const char * CControl::GetString(void)
{
	return m_szStringValue.c_str();
}

int CControl::SetInt(int iValue)
{
	if(m_iType == CCONTROL_TYPE_CHECK)
	{
		if(iValue != 0)
		{
			m_iIntValue = 1;

			Button_SetCheck(m_hwndControl, BST_CHECKED);
		}
		else
		{
			m_iIntValue = 0;

			Button_SetCheck(m_hwndControl, BST_UNCHECKED);
		}
	}
	else if(m_iType == CCONTROL_TYPE_COLOR)
	{
		CreateBitmap(iValue);

		SendMessage(m_hwndControl, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hbmColor);

		m_iIntValue = iValue;
	}
	else if(m_iType == CCONTROL_TYPE_COMBOBOX || m_iType == CCONTROL_TYPE_REZBOX)
	{
		ComboBox_SetCurSel(m_hwndControl, iValue);

		m_iIntValue = iValue;
	}
	else
	{
		if(iValue < m_iMinValue)
			iValue = m_iMinValue;
		else if(iValue > m_iMaxValue)
			iValue = m_iMaxValue;

		Edit_SetText(m_hwndControl, ToString(iValue).c_str());
	}

	return 1;
}

int CControl::SetString(const char *szValue)
{
	if((m_iType != CCONTROL_TYPE_CHECK) && (m_iType != CCONTROL_TYPE_COLOR))
	{
		char szBuffer[1024];

		int i;

		if(m_iType == CCONTROL_TYPE_HEXINT16)
		{
			for(i = 0; i < 2; i++)
			{
				if(((UCHAR)szValue[i] & 0xF0) <= 0x90)
					szBuffer[2 * i] = ((szValue[i] & 0xF0) >> 4) + '0';
				else
					szBuffer[2 * i] = ((szValue[i] & 0xF0) >> 4) + 'A' - 10;

				if((szValue[i] & 0x0F) <= 0x09)
					szBuffer[2 * i + 1] = (szValue[i] & 0x0F) + '0';
				else
					szBuffer[2 * i + 1] = (szValue[i] & 0x0F) + 'A' - 10;
			}

			szBuffer[4] = '\0';
		}
		else if(m_iType == CCONTROL_TYPE_HEXINT32)
		{
			for(i = 0; i < 4; i++)
			{
				if(((UCHAR)szValue[i] & 0xF0) <= 0x90)
					szBuffer[2 * i] = ((szValue[i] & 0xF0) >> 4) + '0';
				else
					szBuffer[2 * i] = ((szValue[i] & 0xF0) >> 4) + 'A' - 10;

				if((szValue[i] & 0x0F) <= 0x09)
					szBuffer[2 * i + 1] = (szValue[i] & 0x0F) + '0';
				else
					szBuffer[2 * i + 1] = (szValue[i] & 0x0F) + 'A' - 10;
			}

			szBuffer[8] = '\0';
		}
		else if(m_iType == CCONTROL_TYPE_HEXINT64)
		{
			for(i = 0; i < 8; i++)
			{
				if(((UCHAR)szValue[i] & 0xF0) <= 0x90)
					szBuffer[2 * i] = ((szValue[i] & 0xF0) >> 4) + '0';
				else
					szBuffer[2 * i] = ((szValue[i] & 0xF0) >> 4) + 'A' - 10;

				if((szValue[i] & 0x0F) <= 0x09)
					szBuffer[2 * i + 1] = (szValue[i] & 0x0F) + '0';
				else
					szBuffer[2 * i + 1] = (szValue[i] & 0x0F) + 'A' - 10;
			}

			szBuffer[16] = '\0';
		}
		else
		{
			Edit_SetText(m_hwndControl, szValue);

			ProcessMessage(EN_CHANGE);

			return 1;
		}

		Edit_SetText(m_hwndControl, szBuffer);

		ProcessMessage(EN_CHANGE);
	}

	return 1;
}

int CControl::CreateBitmap(int iColor)
{
	HDC hdcDialog;
	HDC hdcMemory;

	HBRUSH hbrColor;

	RECT rectButton;

	if(m_hbmColor != NULL)
	{
		DeleteObject(m_hbmColor);

		m_hbmColor = NULL;
	}

	hdcDialog = GetDC(m_hwndDialog);

	GetClientRect(m_hwndControl, &rectButton);

	hdcMemory = CreateCompatibleDC(hdcDialog);

	m_hbmColor = CreateCompatibleBitmap(hdcDialog, rectButton.right, rectButton.bottom);

	SelectObject(hdcMemory, m_hbmColor);

	hbrColor = CreateSolidBrush(SwapColorRedBlue((UINT)iColor));

	FillRect(hdcMemory, &rectButton, hbrColor);

	DeleteObject(hbrColor);
	DeleteDC(hdcMemory);
	ReleaseDC(m_hwndDialog, hdcDialog);

	return 1;
}
