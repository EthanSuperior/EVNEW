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

constexpr int NUM_RLE_CONTROLS = 4;

constexpr int NUM_RLE_IMPORT_CONTROLS = 9;
constexpr int NUM_RLE_EXPORT_CONTROLS = 7;

constexpr char RLE_OPCODE_ENDOFFRAME     = 0x00;
constexpr char RLE_OPCODE_LINESTART      = 0x01;
constexpr char RLE_OPCODE_PIXELDATA      = 0x02;
constexpr char RLE_OPCODE_TRANSPARENTRUN = 0x03;
constexpr char RLE_OPCODE_PIXELRUN       = 0x04;

constexpr int NUM_RLE_FIELDS = 6;

const std::string g_szRleFields[NUM_RLE_FIELDS] =
	{"Width", "Height", "Frames", "X Frames", "Image Filename", "Mask Filename"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CRLEResource : public CNovaResource
{
public:

	CRLEResource(void);
	~CRLEResource(void) override;

	int GetType(void) override;
	int GetSize(void) override;

	int GetDialogID(void) override;
	DLGPROCNOCALLBACK GetDialogProc(void) override;

	int GetNumFields(void) override;
	const std::string * GetFieldNames(void) override;

	int Initialize(HWND hwnd) override;

	int CloseAndSave(void) override;
	int CloseAndDontSave(void) override;

	int SetBPP(short iBPP);
	short GetBPP(void);

	int Save(char *pOutput) override;
	int Load(char *pInput, int iSize) override;

	int ShouldLoadDirect(void) override;
	int SaveDirect(std::ostream & output) override;
	int LoadDirect(std::istream & input, int iSize) override;

	int SaveToTextEx(std::ostream & output, std::string & szFilePath, std::string & szFilename1, std::string & szFilename2, int iParam) override;
	int LoadFromTextEx(std::istream & input, std::string & szFilePath) override;

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
