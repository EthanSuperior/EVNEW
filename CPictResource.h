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

const int NUM_PICT_CONTROLS = 2;

const int NUM_PICT_FIELDS = 3;

const std::string g_szPictFields[NUM_PICT_FIELDS] =
	{"Width", "Height", "Filename"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CPictResource : public CNovaResource
{
public:

	CPictResource(void);
	~CPictResource(void);

	int GetType(void);
	int GetSize(void);

	int GetDialogID(void);
	DLGPROCNOCALLBACK GetDialogProc(void);

	int GetNumFields(void);
	const std::string * GetFieldNames(void);

	int Initialize(HWND hwnd);

	int CloseAndSave(void);
	int CloseAndDontSave(void);

	int Save(char *pOutput);
	int Load(char *pInput, int iSize);

	int SaveToTextEx(std::ostream & output, std::string & szFilePath, std::string & szFilename1, std::string & szFilename2, int iParam);
	int LoadFromTextEx(std::istream & input, std::string & szFilePath);

	int ShouldLoadDirect(void);
	int SaveDirect(std::ostream & output);
	int LoadDirect(std::istream & input, int iSize);

	static BOOL PictDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int FindBPP(void);

	int InitializePicture(HWND hwnd);

	/** Rasterize the active PictHandle to a BMP (QuickTime) and cache for GDI painting. */
	int EnsurePictPreview(void);
	void InvalidatePictPreview(void);

	int OnPaint(void);

	int FileImport(char *szFilename = NULL, int iShowErrorMessages = 1);
	int FileExport(const char *szFilename = NULL, int iImageType = -1, int iShowErrorMessages = 1);

	short m_iWidth;
	short m_iHeight;

	/** Full-size preview DIB; scaled in OnPaint with GDI. QuickTime is not used for scaling. */
	HBITMAP m_hPreviewBitmap;

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
