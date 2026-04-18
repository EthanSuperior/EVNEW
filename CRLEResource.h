// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CRLEResource.h

#ifndef CRLERESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CRLERESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CRLEResource;

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>

#include <vector>
#include <string>

namespace qt
{
#include <QTML.h>
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

const int NUM_RLE_CONTROLS = 4;

const int NUM_RLE_IMPORT_CONTROLS = 9;
const int NUM_RLE_EXPORT_CONTROLS = 7;

const char RLE_OPCODE_ENDOFFRAME     = 0x00;
const char RLE_OPCODE_LINESTART      = 0x01;
const char RLE_OPCODE_PIXELDATA      = 0x02;
const char RLE_OPCODE_TRANSPARENTRUN = 0x03;
const char RLE_OPCODE_PIXELRUN       = 0x04;

const int NUM_RLE_FIELDS = 6;

const std::string g_szRleFields[NUM_RLE_FIELDS] =
	{"Width", "Height", "Frames", "X Frames", "Image Filename", "Mask Filename"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CRLEResource : public CNovaResource
{
public:

	CRLEResource(void);
	~CRLEResource(void);

	int GetType(void);
	int GetSize(void);

	int GetDialogID(void);
	DLGPROCNOCALLBACK GetDialogProc(void);

	int GetNumFields(void);
	const std::string * GetFieldNames(void);

	int Initialize(HWND hwnd);

	int CloseAndSave(void);
	int CloseAndDontSave(void);

	int SetBPP(short iBPP);
	short GetBPP(void);

	int Save(char *pOutput);
	int Load(char *pInput, int iSize);

	int ShouldLoadDirect(void);
	int SaveDirect(std::ostream & output);
	int LoadDirect(std::istream & input, int iSize);

	int SaveToTextEx(std::ostream & output, std::string & szFilePath, std::string & szFilename1, std::string & szFilename2, int iParam);
	int LoadFromTextEx(std::istream & input, std::string & szFilePath);

	static BOOL RLEDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	static BOOL RLEImportDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static BOOL RLEExportDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	int FileImport(void);
	int FileExport(void);

	int InitImportControls(HWND hwnd);
	int InitExportControls(HWND hwnd);

	int DoImportBrowse(void);
	int DoExportBrowse(void);

	int DoImport(const char *szFilename, int iIsImage, int iNumFramesToImport, int iWidth, int iHeight, int iFramesPerRow, int iFramesPerColumn, int iFirstFrame, int iShowErrorMessages);
	int DoExport(const char *szFilename, int iIsImage, int iNumFramesToExport, int iFramesPerRow, int iFramesPerColumn, int iFirstFrame, int iShowErrorMessages);

	int ImportCloseAndDontSave(void);
	int ExportCloseAndDontSave(void);

	int CompileImage(void);
	int DecompileImage(void);

	int MakeBitmap(HWND hwnd);

	int SwapEndians(void);

	short m_iWidth;
	short m_iHeight;
	short m_iBPP;
	short m_iNumFrames;

	HBITMAP m_hbmImage;

	int m_iFramesPerRow;
	int m_iFramesPerColumn;

	int m_iCurPage;

	int m_iIsDirty;

	std::vector<UCHAR> m_vData1;
	std::vector< std::vector<UCHAR> > m_vData2;
	std::vector< std::vector<UCHAR> > m_vData3;

	CControl m_controls[NUM_RLE_CONTROLS];

	CWindow m_wndImport;
	CWindow m_wndExport;

	int m_iImportFilter;
	int m_iExportFilter;

	CControl m_importControls[NUM_RLE_IMPORT_CONTROLS];
	CControl m_exportControls[NUM_RLE_EXPORT_CONTROLS];
};

#endif		// #ifndef CRLERESOURCE_H_INCLUDED
