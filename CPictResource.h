// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CPictResource.h

#ifndef CPICTRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CPICTRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CPictResource;

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>

#include <vector>
#include <string>

namespace qt
{
#include <QTML.h>
#include <QuickDraw.h>
#include <ImageCompression.h>
#include <QuickTimeComponents.h>
#include <TextUtils.h>
}

#include "CControl.h"
#include "CNovaResource.h"
#include "Utils.h"

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

constexpr int NUM_PICT_CONTROLS = 2;

constexpr int NUM_PICT_FIELDS = 3;

const std::string g_szPictFields[NUM_PICT_FIELDS] =
	{"Width", "Height", "Filename"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CPictResource : public CNovaResource
{
public:

	CPictResource(void);
	~CPictResource(void) override;

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

	int ShouldLoadDirect(void) override;
	int SaveDirect(std::ostream & output) override;
	int LoadDirect(std::istream & input, int iSize) override;

	static BOOL PictDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int FindBPP(void);

	int InitializePicture(HWND hwnd);

	int OnPaint(void);

	int FileImport(char *szFilename = NULL, int iShowErrorMessages = 1);
	int FileExport(const char *szFilename = NULL, int iImageType = -1, int iShowErrorMessages = 1);

	short m_iWidth;
	short m_iHeight;

	int m_iPortExists;

	qt::Handle m_hPicture;

	qt::Rect m_rectDest;

	short m_iTempWidth;
	short m_iTempHeight;

	qt::Handle m_hTempPicture;

	qt::Rect m_tempRectDest;

	int m_iIsDirty;

	CControl m_controls[NUM_PICT_CONTROLS];
};

#endif		// #ifndef CPICTRESOURCE_H_INCLUDED
