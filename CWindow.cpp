// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CWindow.cpp

////////////////////////////////////////////////////////////////
//////////////////////////  INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include "CWindow.h"
#include "CErrorLog.h"
#include "CException.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

int CWindow::ms_iCount = 0;

CWindow::CWindow(void)
{
	m_hwnd      = NULL;
	m_hinstance = NULL;

	m_szTitle = "Game";

	m_szClassName = static_cast<std::string>("CWindow") + ToString(ms_iCount);

	m_iWidth         = 0;
	m_iHeight        = 0;
	m_xPos           = 0;
	m_yPos           = 0;
	m_dwStyle        = 0;
	m_iClientXOffset = 0;
	m_iClientYOffset = 0;

	m_iIsActive = 0;

	m_WndProc = NULL;
	m_DlgProc = NULL;

	int i;

	for(i = 0; i < CWINDOW_MAX_EXTRA_DATA; i++)
		m_iExtraData[i] = 0;

	m_szExceptionString = "";

	m_iState = CWINDOW_STATE_NULL;

	ms_iCount++;
}

CWindow::~CWindow(void)
{
	if(m_iState & CWINDOW_STATE_CREATED)
		Destroy();

	if(m_iState & CWINDOW_STATE_REGISTERED)
		Unregister();
}

int CWindow::Register(HINSTANCE hInstance, HICON hIcon, HCURSOR hCursor, HBRUSH hbrBackground, int iIsDialog, std::string szMenuName)
{
	if(m_iState & CWINDOW_STATE_REGISTERED)
		return 0;

	m_hinstance = hInstance;

	WNDCLASS wndclass;

	wndclass.style         = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc   = CWindow::CWindowWndProc;
	wndclass.cbClsExtra    = 0;
	wndclass.cbWndExtra    = 0;
	wndclass.hInstance     = m_hinstance;
	wndclass.hIcon         = hIcon;
	wndclass.hCursor       = hCursor;
	wndclass.hbrBackground = hbrBackground;
	wndclass.lpszMenuName  = szMenuName.c_str();
	wndclass.lpszClassName = m_szClassName.c_str();

	if(iIsDialog)
		wndclass.cbWndExtra = DLGWINDOWEXTRA;

	if(RegisterClass(&wndclass) == 0)
		throw CException("Unable to register window class!");

	m_iState |= CWINDOW_STATE_REGISTERED;

	return 1;
}

int CWindow::Unregister(void)
{
	if(!(m_iState & CWINDOW_STATE_REGISTERED))
		return 0;

	if(UnregisterClass(m_szClassName.c_str(), m_hinstance) == 0)
		throw CException("Unable to unregister window class!");

	m_iState &= ~CWINDOW_STATE_REGISTERED;

	return 1;
}

int CWindow::Create(std::string szTitle, int iWidth, int iHeight, int iX, int iY, DWORD dwStyle, CWindow *pWndParent, HMENU hMenu)
{
	if(m_iState & CWINDOW_STATE_CREATED)
		Destroy();

	if(!(m_iState & CWINDOW_STATE_REGISTERED))
		return 0;

	m_iState |= CWINDOW_STATE_CREATING;

	m_szTitle = szTitle;

	m_iWidth  = iWidth;
	m_iHeight = iHeight;
	m_xPos    = iX;
	m_yPos    = iY;
	m_dwStyle = dwStyle;

	m_pWndParent = pWndParent;

	HWND hwndParent;

	if(pWndParent == NULL)
		hwndParent = NULL;
	else
	{
		pWndParent->m_listChildren.push_back(this);

		hwndParent = pWndParent->GetHWND();
	}

	CreateWindow(m_szClassName.c_str(), m_szTitle.c_str(), m_dwStyle, m_xPos, m_yPos, m_iWidth, m_iHeight, hwndParent, hMenu, m_hinstance, this);

	if(m_hwnd == NULL)
		throw CException("Unable to create window!");

	m_iState &= ~CWINDOW_STATE_CREATING;
	m_iState |=  CWINDOW_STATE_CREATED;

	Resize(m_iWidth, m_iHeight);

	return 1;
}

int CWindow::CreateAsDialog(HINSTANCE hInstance, int iResourceID, int iModal, CWindow *pWndParent)
{
	if(m_iState & CWINDOW_STATE_CREATED)
		Destroy();

	m_iState |= CWINDOW_STATE_DIALOG;

	if(iModal)
		m_iState |= CWINDOW_STATE_MODAL;

	m_hinstance = hInstance;

	m_pWndParent = pWndParent;

	HWND hwndParent;

	if(pWndParent == NULL)
		hwndParent = NULL;
	else
	{
		pWndParent->m_listChildren.push_back(this);

		hwndParent = pWndParent->GetHWND();
	}

	if(iModal == 0)
	{
		m_iState |= CWINDOW_STATE_CREATING;

		CreateDialogParam(m_hinstance, MAKEINTRESOURCE(iResourceID), hwndParent, CWindowDlgProc, (LPARAM)this);

		if(m_hwnd == NULL)
			throw CException("Unable to create dialog box!");

		m_iState &= ~CWINDOW_STATE_CREATING;
		m_iState |=  CWINDOW_STATE_CREATED;

		Update();
		Show();

		m_dwStyle = 0;
	}
	else
	{
		m_hwnd = NULL;

		DialogBoxParam(m_hinstance, MAKEINTRESOURCE(iResourceID), hwndParent, CWindowDlgProc, (LPARAM)this);
	}

	return 1;
}

int CWindow::Destroy(void)
{
	if(!(m_iState & CWINDOW_STATE_CREATED))
		return 0;

	m_iState &= ~CWINDOW_STATE_CREATED;

	if(m_iState & CWINDOW_STATE_DIALOG)
		SetWindowLong(m_hwnd, DWL_USER, 0);
	else
		SetWindowLong(m_hwnd, GWL_USERDATA, 0);

	int i;

	for(i = 0; i < m_listChildren.size(); i++)
	{
		CWindow *pWndChild = m_listChildren.front();

		pWndChild->Destroy();
	}

	if(m_pWndParent != NULL)
	{
		ListCWindowPtrIterator iter = m_pWndParent->m_listChildren.begin();

		while(iter != m_pWndParent->m_listChildren.end())
		{
			if(*iter == this)
			{
				m_pWndParent->m_listChildren.erase(iter);

				break;
			}

			iter++;
		}
	}

	if((m_iState & CWINDOW_STATE_DIALOG) && (m_iState & CWINDOW_STATE_MODAL))
	{
		if(EndDialog(m_hwnd, 0) == 0)
			throw CException("Unable to destroy modal dialog box!");
	}
	else
	{
		if(DestroyWindow(m_hwnd) == 0)
			throw CException("Unable to destroy window!");
	}

	m_iState &= ~CWINDOW_STATE_DIALOG;
	m_iState &= ~CWINDOW_STATE_MODAL;

	m_hwnd = NULL;

	return 1;
}

int CWindow::Destroying(void)
{
	if(!(m_iState & CWINDOW_STATE_CREATED))
		return 0;

	if(m_iState & CWINDOW_STATE_DIALOG)
		SetWindowLong(m_hwnd, DWL_USER, 0);
	else
		SetWindowLong(m_hwnd, GWL_USERDATA, 0);

	m_iState &= ~CWINDOW_STATE_CREATED;
	m_iState &= ~CWINDOW_STATE_DIALOG;
	m_iState &= ~CWINDOW_STATE_MODAL;

	m_hwnd = NULL;

	return 1;
}

int CWindow::IsCreated(void)
{
	return ((m_iState & CWINDOW_STATE_CREATED) ? (1) : (0));
}

int CWindow::SetWndProc(LRESULT (*WndProc)(HWND, UINT, WPARAM, LPARAM))
{
	m_WndProc = WndProc;

	return 1;
}

int CWindow::SetDlgProc(BOOL (*DlgProc)(HWND, UINT, WPARAM, LPARAM))
{
	m_DlgProc = DlgProc;

	return 1;
}

int CWindow::Show(int iShow)
{
	if(iShow)
		ShowWindow(m_hwnd, SW_SHOW);
	else
		ShowWindow(m_hwnd, SW_HIDE);

	return 1;
}

int CWindow::SetFocus(void)
{
	::SetFocus(m_hwnd);

	return 1;
}

int CWindow::SetAsForeground(void)
{
	SetForegroundWindow(m_hwnd);

	return 1;
}

int CWindow::Move(int iX, int iY)
{
	if(m_iState & CWINDOW_STATE_CREATING)
		return 0;

	m_xPos = iX;
	m_yPos = iY;

	if(MoveWindow(m_hwnd, m_xPos, m_yPos, m_iWidth, m_iHeight, TRUE) == 0)
		return 0;

	return 1;
}

int CWindow::Resize(int iWidth, int iHeight)
{
	if(m_iState & CWINDOW_STATE_CREATING)
		return 0;

	RECT rectWindow;
	RECT rectClient;

	GetWindowRect(m_hwnd, &rectWindow);
	GetClientRect(m_hwnd, &rectClient);

	m_iWidth  = iWidth;
	m_iHeight = iHeight;

	iWidth  += ((rectWindow.right  - rectWindow.left) - (rectClient.right  - rectClient.left));
	iHeight += ((rectWindow.bottom - rectWindow.top)  - (rectClient.bottom - rectClient.top));

	if(MoveWindow(m_hwnd, m_xPos, m_yPos, iWidth, iHeight, TRUE) == 0)
		return 0;

	return 1;
}

int CWindow::MoveAndResize(int iX, int iY, int iWidth, int iHeight)
{
	if(m_iState & CWINDOW_STATE_CREATING)
		return 0;

	m_xPos    = iX;
	m_yPos    = iY;
	m_iWidth  = iWidth;
	m_iHeight = iHeight;

	RECT rectWindow;
	RECT rectClient;

	GetWindowRect(m_hwnd, &rectWindow);
	GetClientRect(m_hwnd, &rectClient);

	iWidth  += ((rectWindow.right  - rectWindow.left) - (rectClient.right  - rectClient.left));
	iHeight += ((rectWindow.bottom - rectWindow.top)  - (rectClient.bottom - rectClient.top));

	if(MoveWindow(m_hwnd, m_xPos, m_yPos, iWidth, iHeight, TRUE) == 0)
		return 0;

	return 1;
}

int CWindow::SetTitle(const char *szTitle)
{
	int iresult = SetWindowText(m_hwnd, szTitle);

	int err = GetLastError();

	return 1;
}

int CWindow::Update(void)
{
	if(m_iState & CWINDOW_STATE_CREATING)
		return 0;

	char szBuffer[1024];

	GetWindowText(m_hwnd, szBuffer, 1024);

	m_szTitle = szBuffer;

	RECT windowRect;
	RECT clientRect;

	GetWindowRect(m_hwnd, &windowRect);
	GetClientRect(m_hwnd, &clientRect);

	m_xPos    = windowRect.left;
	m_yPos    = windowRect.top;
	m_iWidth  = clientRect.right  - clientRect.left;
	m_iHeight = clientRect.bottom - clientRect.top;

	return 1;
}

int CWindow::SetHWND(HWND hwnd)
{
	m_hwnd = hwnd;

	return 1;
}

int CWindow::SetExtraData(int iIndex, int iData)
{
	if((iIndex < 0) || (iIndex >= CWINDOW_MAX_EXTRA_DATA))
		throw CException("CWindow::SetExtraData: index %d out of range [0, %d]!", iIndex, CWINDOW_MAX_EXTRA_DATA - 1);

	m_iExtraData[iIndex] = iData;

	return 1;
}

int CWindow::GetExtraData(int iIndex)
{
	if((iIndex < 0) || (iIndex >= CWINDOW_MAX_EXTRA_DATA))
		throw CException("CWindow::GetExtraData: index %d out of range [0, %d]!", iIndex, CWINDOW_MAX_EXTRA_DATA - 1);

	return m_iExtraData[iIndex];
}

std::string CWindow::GetExceptionString(void)
{
	return m_szExceptionString;
}

CWindow * CWindow::GetWindow(HWND hwnd, int iIsDialog)
{
	if(!iIsDialog)
		return ((CWindow *)GetWindowLong(hwnd, GWL_USERDATA));
	else
		return ((CWindow *)GetWindowLong(hwnd, DWL_USER));
}

LRESULT CALLBACK CWindow::CWindowWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;

	try
	{
		if((msg == WM_CREATE) || (msg == WM_NCCREATE))
			SetWindowLong(hwnd, GWL_USERDATA, (LONG)(((LPCREATESTRUCT)lparam)->lpCreateParams));

		pWindow = CWindow::GetWindow(hwnd);

		switch(msg)
		{
			case WM_ACTIVATE:
			{
				int isActive = (((LOWORD(wparam) == WA_ACTIVE) || (LOWORD(wparam) == WA_CLICKACTIVE)) ? 1 : 0);

				pWindow->m_iIsActive = isActive;

				if((pWindow != NULL) && (pWindow->m_WndProc != NULL))
					pWindow->m_WndProc(hwnd, msg, wparam, lparam);

				return 0;

				break;
			}

			case WM_CREATE:
			{
//				CREATESTRUCT * p = (CREATESTRUCT *)lparam;

				if(pWindow != NULL)
					pWindow->SetHWND(hwnd);

				if((pWindow != NULL) && (pWindow->m_WndProc != NULL))
					pWindow->m_WndProc(hwnd, msg, wparam, lparam);

				return 0;

				break;
			}

			case WM_NCCALCSIZE:
			{
				if(static_cast<BOOL>(wparam) == TRUE)
				{
					NCCALCSIZE_PARAMS *pParms = (NCCALCSIZE_PARAMS *)lparam;

					if(pWindow != NULL)
					{
						pWindow->m_iClientXOffset = pParms->rgrc[2].left + (pParms->rgrc[0].left - pParms->rgrc[1].left);
						pWindow->m_iClientYOffset = pParms->rgrc[2].top  + (pParms->rgrc[0].top  - pParms->rgrc[1].top);
					}
				}

				break;
			}

			case WM_NCACTIVATE:
			{
				if((pWindow != NULL) && (pWindow->m_WndProc != NULL))
					pWindow->m_WndProc(hwnd, msg, wparam, lparam);

				return 1;

				break;
			}

			case WM_WINDOWPOSCHANGING:
			{
//				LPWINDOWPOS pos;

//				pos = (LPWINDOWPOS) lparam;

				if((pWindow != NULL) && (pWindow->m_WndProc != NULL))
					pWindow->m_WndProc(hwnd, msg, wparam, lparam);

				return 0;

				break;
			}

			case WM_WINDOWPOSCHANGED:
			{
				if(pWindow != NULL)
					pWindow->Update();

				break;
			}

			case WM_PAINT:
			{
				HDC hdc;
				PAINTSTRUCT ps;

				hdc = BeginPaint(hwnd, &ps);

				EndPaint(hwnd, &ps);

				if((pWindow != NULL) && (pWindow->m_WndProc != NULL))
					pWindow->m_WndProc(hwnd, msg, wparam, lparam);

				return 0;

				break;
			}

			case WM_PARENTNOTIFY:
			{
				if(LOWORD(wparam) == WM_DESTROY)
				{
					if(pWindow != NULL)
					{
						CWindow *pWndChild = CWindow::GetWindow((HWND)lparam);

						ListCWindowPtrIterator iter;

						iter = pWindow->m_listChildren.begin();

						while(iter != pWindow->m_listChildren.end())
						{
							if(*iter == pWndChild)
							{
								pWindow->m_listChildren.erase(iter);

								break;
							}

							iter++;
						}

						if(pWindow->m_WndProc != NULL)
							pWindow->m_WndProc(hwnd, msg, wparam, lparam);
					}

					return 0;

					break;
				}

				break;
			}

			case WM_DESTROY:
			{
				if(pWindow != NULL)
				{
					pWindow->Destroying();

					int i;

					for(i = 0; i < pWindow->m_listChildren.size(); i++)
					{
						CWindow *pWndChild = pWindow->m_listChildren.front();

						pWndChild->Destroy();
					}

					if(pWindow->m_WndProc != NULL)
						pWindow->m_WndProc(hwnd, msg, wparam, lparam);
				}

				return 0;

				break;
			}

			default:
			{
				break;
			}
		}

		if((pWindow != NULL) && (pWindow->m_WndProc != NULL))
			return (pWindow->m_WndProc(hwnd, msg, wparam, lparam));
		else
			return (DefWindowProc(hwnd, msg, wparam, lparam));
	}
	catch(CException exception)
	{
		if(pWindow != NULL)
			pWindow->m_szExceptionString = exception.GetExceptionString();

		return (DefWindowProc(hwnd, msg, wparam, lparam));
	}
}

LRESULT CWindow::WndProc_PostQuitMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if(msg == WM_DESTROY)
	{
		PostQuitMessage(0);

		return 0;
	}
	else
	{
		return (DefWindowProc(hwnd, msg, wparam, lparam));
	}
}

BOOL CALLBACK CWindow::CWindowDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;

	int i;

	try
	{
		if(msg == WM_INITDIALOG)
			SetWindowLong(hwnd, DWL_USER, lparam);

		pWindow = CWindow::GetWindow(hwnd, 1);

		if(msg == WM_INITDIALOG)
		{
			if(pWindow->m_iState & CWINDOW_STATE_MODAL)
				pWindow->m_iState |= CWINDOW_STATE_CREATED;

			pWindow->SetHWND(hwnd);
		}

		switch(msg)
		{
			case WM_ACTIVATE:
			{
				int isActive = (((LOWORD(wparam) == WA_ACTIVE) || (LOWORD(wparam) == WA_CLICKACTIVE)) ? 1 : 0);

				if(pWindow != NULL)
				{
					pWindow->m_iIsActive = isActive;

					if(pWindow->m_DlgProc != NULL)
						pWindow->m_DlgProc(hwnd, msg, wparam, lparam);
				}

				return TRUE;

				break;
			}

			case WM_INITDIALOG:
			{
//				CREATESTRUCT * p = (CREATESTRUCT *)lparam;

				if((pWindow != NULL) && (pWindow->m_DlgProc != NULL))
					pWindow->m_DlgProc(hwnd, msg, wparam, lparam);

				return TRUE;

				break;
			}

			case WM_NCCALCSIZE:
			{
				if(static_cast<BOOL>(wparam) == TRUE)
				{
					NCCALCSIZE_PARAMS *pParms = (NCCALCSIZE_PARAMS *)lparam;

					if(pWindow != NULL)
					{
						pWindow->m_iClientXOffset = pParms->rgrc[2].left + (pParms->rgrc[0].left - pParms->rgrc[1].left);
						pWindow->m_iClientYOffset = pParms->rgrc[2].top  + (pParms->rgrc[0].top  - pParms->rgrc[1].top);
					}
				}

				break;
			}

			case WM_WINDOWPOSCHANGED:
			{
				if(pWindow != NULL)
					pWindow->Update();

				break;
			}

			case WM_PARENTNOTIFY:
			{
				if(LOWORD(wparam) == WM_DESTROY)
				{
					if(pWindow != NULL)
					{
						CWindow *pWndChild = CWindow::GetWindow((HWND)lparam);

						ListCWindowPtrIterator iter;

						iter = pWindow->m_listChildren.begin();

						while(iter != pWindow->m_listChildren.end())
						{
							if(*iter == pWndChild)
							{
								pWindow->m_listChildren.erase(iter);

								break;
							}

							iter++;
						}

						if(pWindow->m_DlgProc != NULL)
							pWindow->m_DlgProc(hwnd, msg, wparam, lparam);
					}

					return TRUE;

					break;
				}

				break;
			}

			case WM_DESTROY:
			{
				if(pWindow != NULL)
				{
					pWindow->Destroying();

					for(i = 0; i < pWindow->m_listChildren.size(); i++)
					{
						CWindow *pWndChild = pWindow->m_listChildren.front();

						pWndChild->Destroy();
					}

					if(pWindow->m_DlgProc != NULL)
						pWindow->m_DlgProc(hwnd, msg, wparam, lparam);
				}

				return TRUE;

				break;
			}

			default:
			{
				break;
			}
		}

		if((pWindow != NULL) && (pWindow->m_DlgProc != NULL))
			return (pWindow->m_DlgProc(hwnd, msg, wparam, lparam));
		else
			return FALSE;
	}
	catch(CException exception)
	{
		if(pWindow != NULL)
			pWindow->m_szExceptionString = exception.GetExceptionString();

		return FALSE;
	}
}

HWND CWindow::GetHWND(void)
{
	if(this == NULL)
		return NULL;

	return m_hwnd;
}

HINSTANCE CWindow::GetInstance(void)
{
	return m_hinstance;
}

std::string CWindow::GetTitle(void)
{
	return m_szTitle;
}

std::string CWindow::GetClassName(void)
{
	return m_szClassName;
}

int CWindow::GetWidth(void)
{
	return m_iWidth;
}

int CWindow::GetHeight(void)
{
	return m_iHeight;
}

int CWindow::GetXPos(void)
{
	return m_xPos;
}

int CWindow::GetYPos(void)
{
	return m_yPos;
}

int CWindow::GetClientXPos(void)
{
	return (m_xPos + m_iClientXOffset);
}

int CWindow::GetClientYPos(void)
{
	return (m_yPos + m_iClientYOffset);
}

int CWindow::IsActive(void)
{
	return m_iIsActive;
}

DWORD CWindow::GetStyle(void)
{
	return m_dwStyle;
}
