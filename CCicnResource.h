// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CCicnResource.h

#ifndef CCICNRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CCICNRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CCicnResource;

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>

#include <vector>
#include <string>

namespace qt
{
#include <QTML.h>
#include <Icons.h>
}

#include "CControl.h"
#include "CNovaResource.h"
#include "Utils.h"

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

constexpr int NUM_CICN_CONTROLS = 2;

constexpr int NUM_CICN_FIELDS = 5;

const std::string g_szCicnFields[NUM_CICN_FIELDS] =
	{"Width", "Height", "BPP", "Icon Filename", "Mask Filename"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CCicnResource : public CNovaResource
{
public:

	CCicnResource(void);
	~CCicnResource(void) override;

	int GetType(void) override;
	int GetSize(void) override;

	int GetDialogID(void) override;
	DLGPROCNOCALLBACK GetDialogProc(void) override;

	int GetNumFields(void) override;
	const std::string * GetFieldNames(void) override;

	int Initialize(HWND hwnd) override;

	int CloseAndSave(void) override;
	int CloseAndDontSave(void) override;

	int Save(char *pOutput) override;
	int Load(char *pInput, int iSize) override;

	int SaveToTextEx(std::ostream & output, std::string & szFilePath, std::string & szFilename1, std::string & szFilename2, int iParam) override;
	int LoadFromTextEx(std::istream & input, std::string & szFilePath) override;

	static BOOL CicnDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int MakeBitmap(HWND hwnd, int iIsIcon);

	UCHAR FindColor(UCHAR ucRed, UCHAR ucGreen, UCHAR ucBlue);

	int FileImport(int iIsIcon, const char *szFilename = NULL, int iShowErrorMessages = 1);
	int FileExport(int iIsIcon, const char *szFilename = NULL, int iShowErrorMessages = 1);

	int m_iWidth;
	int m_iHeight;
	int m_iBPP;

	std::vector<UCHAR> m_vIconData;
	std::vector<UCHAR> m_vMaskData;

	std::vector<UINT> m_vColorTable;

	int m_iNumColors;

	int m_iTempWidth;
	int m_iTempHeight;
	int m_iTempBPP;

	std::vector<UCHAR> m_vTempIconData;
	std::vector<UCHAR> m_vTempMaskData;
	std::vector<UINT>  m_vTempColorTable;

	int m_iTempNumColors;

	HBITMAP m_hbmIcon;
	HBITMAP m_hbmMask;

	CControl m_controls[NUM_CICN_CONTROLS];
};

#endif		// #ifndef CCICNRESOURCE_H_INCLUDED
