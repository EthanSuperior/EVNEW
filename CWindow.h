// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CWindow.h

#ifndef CWINDOW_H_INCLUDED		// Prevent multiple inclusions
#define CWINDOW_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CWindow;

////////////////////////////////////////////////////////////////
//////////////////////////  INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <windowsx.h>
#include <cstdio>

#include <string>
#include <list>

#include "CException.h"
#include "Utils.h"

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

const int CWINDOW_STATE_NULL       = 0x00;
const int CWINDOW_STATE_REGISTERED = 0x01;
const int CWINDOW_STATE_CREATING   = 0x02;
const int CWINDOW_STATE_CREATED    = 0x04;
const int CWINDOW_STATE_DIALOG     = 0x08;
const int CWINDOW_STATE_MODAL      = 0x10;

const int CWINDOW_MAX_EXTRA_DATA = 8;

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

typedef std::list<CWindow *> ListCWindowPtr;
typedef ListCWindowPtr::iterator ListCWindowPtrIterator;

// This class makes setting up a window really easy

class CWindow
{
public:
	CWindow(void);		// Constructor
	~CWindow(void);		// Destructor

	int Register(HINSTANCE hInstance, HICON hIcon, HCURSOR hCursor, HBRUSH hbrBackground, int iIsDialog = 0, std::string szMenuName = "");
	int Unregister(void);

	int Create(std::string szTitle, int iWidth, int iHeight, int iX, int iY, DWORD dwStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE, CWindow *pWndParent = NULL, HMENU hMenu = NULL);	// Create the window
	int CreateAsDialog(HINSTANCE hInstance, int iResourceID, int iModal, CWindow *pWndParent);		// Create the window as a dialog box
	int Destroy(void);			// Destroy the window
	int Destroying(void);		// Notify the window that Windows is destroying it

	int IsCreated(void);		// Has the window been created?

	int SetWndProc(LRESULT (*WndProc)(HWND, UINT, WPARAM, LPARAM));		// Set this window's default message handler
	int SetDlgProc(BOOL    (*DlgProc)(HWND, UINT, WPARAM, LPARAM));

	int Show(int iShow = 1);						// Show/hide the window

	int SetFocus(void);			// Set this window as the focus
	int SetAsForeground(void);	// Make this window the foreground window

	int SetTitle(const char *szTitle);		// Set the window's title

	int Move(int iX, int iY);					// Move the window to a specific point
	int Resize(int iWidth, int iHeight);		// Resize the window's dimensions
	int MoveAndResize(int iX, int iY, int iWidth, int iHeight);		// Move and resize the window

	int Update(void);							// Update the member variables for a user change to the window

	int SetExtraData(int iIndex, int iData);	// Set the user data
	int GetExtraData(int iIndex);

	static CWindow * GetWindow(HWND hwnd, int iIsDialog = 0);		// Get a CWindow from a HWND

	HWND      GetHWND(void);		// Get the window's Win32 handle
	HINSTANCE GetInstance(void);	// Get the window's instance handle

	std::string GetTitle(void);			// Get the window's title
	std::string GetClassName(void);		// Get the window class's name

	int GetWidth(void);				// Get the window's width
	int GetHeight(void);			// Get the window's height
	int GetXPos(void);				// Get the window's x-coordinate
	int GetYPos(void);				// Get the window's y-coordinate
	int GetClientXPos(void);		// Get the window's client area's x-coordinate
	int GetClientYPos(void);		// Get the window's client area's y-coordinate

	int IsActive(void);				// Is the window currently active?

	DWORD GetStyle(void);			// Get the window's style flags

	std::string GetExceptionString(void);	// Get the exception string generated during the message handler

	static LRESULT WndProc_PostQuitMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);		// A message handler that calls PostQuitMessage(0) on the WM_DESTROY message

private:
	static LRESULT CALLBACK CWindowWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);		// A generic message handler
	static BOOL    CALLBACK CWindowDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);		// A generic message handler for dialog boxes

	int SetHWND(HWND hwnd);

	HWND      m_hwnd;		// The actual system window handle
	HINSTANCE m_hinstance;	// The window's instance handle

	std::string m_szTitle;		// The window's title
	std::string m_szClassName;	// The window's class name

	int m_iWidth;			// The window's width
	int m_iHeight;			// The window's height

	int m_xPos;				// The window's position's x-coordinate
	int m_yPos;				// The window's position's y-coordinate

	int m_iClientXOffset;		// The window's client area's x-coordinate offset
	int m_iClientYOffset;		// The window's client area's y-coordinate

	int m_iIsActive;			// Is the window currently active?

	LRESULT (*m_WndProc)(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);	// This window's default message handler
	BOOL    (*m_DlgProc)(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);	// This dialog's default message handler

	DWORD m_dwStyle;			// The window's style flags

	int m_iExtraData[CWINDOW_MAX_EXTRA_DATA];		// Extra user window data

	std::string m_szExceptionString;	// The exception string generated during the message handler

	CWindow *m_pWndParent;	// The window's parent
	std::list<CWindow *> m_listChildren;		// A list of the window's children

	int m_iState;			// The state of the window

	static int ms_iCount;	// The number of windows that have been created
};

#endif		// #ifndef CWINDOW_H_INCLUDED
