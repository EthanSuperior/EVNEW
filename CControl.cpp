// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CControl.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include "CWindow.h"
#include "CControl.h"

#include <commctrl.h>

#include "CException.h"

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

	if(m_iType == CCONTROL_TYPE_COLOR)
		CreateBitmap(SwapColorRedBlue(m_iIntValue));

	HINSTANCE hInstance;

	HWND hwndTooltip;

	TOOLINFO toolInfo;

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

			m_iIntValue = FromString<int>(static_cast<std::string>(szBuffer));

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
		if(m_iType == CCONTROL_TYPE_COMBOBOX)
		{
			m_iIntValue = ComboBox_GetCurSel(m_hwndControl);

			if(m_iIntValue == CB_ERR)
				m_iIntValue = 0;
		}
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
	else if(m_iType == CCONTROL_TYPE_COMBOBOX)
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
				if((static_cast<UCHAR>(szValue[i]) & 0xF0) <= 0x90)
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
				if((static_cast<UCHAR>(szValue[i]) & 0xF0) <= 0x90)
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
				if((static_cast<UCHAR>(szValue[i]) & 0xF0) <= 0x90)
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

	hbrColor = CreateSolidBrush(SwapColorRedBlue(static_cast<UINT>(iColor)));

	FillRect(hdcMemory, &rectButton, hbrColor);

	DeleteObject(hbrColor);
	DeleteDC(hdcMemory);
	ReleaseDC(m_hwndDialog, hdcDialog);

	return 1;
}
