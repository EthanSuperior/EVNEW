// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CUnkResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CUnkResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CUnkResource::CUnkResource(void)
{
	memset(m_szTypeCode, '\0', 5);
}

CUnkResource::~CUnkResource(void)
= default;

int CUnkResource::GetType(void)
{
	return CNR_TYPE_UNK;
}

int CUnkResource::GetSize(void)
{
	return m_vData.size();
}

int CUnkResource::GetDialogID(void)
{
	return -1;
}

DLGPROCNOCALLBACK CUnkResource::GetDialogProc(void)
{
	return NULL;
}

int CUnkResource::Save(char *pOutput)
{
	if(m_vData.size() > 0)
		memcpy(pOutput, &m_vData[0], m_vData.size() * sizeof(UCHAR));

	return 1;
}

int CUnkResource::Load(char *pInput, int iSize)
{
	m_vData.resize(iSize);

	memcpy(&m_vData[0], pInput, iSize);

	return 1;
}

int CUnkResource::SetTypeCode(const char *szTypeCode)
{
	memcpy(m_szTypeCode, szTypeCode, 4);

	return 1;
}

char * CUnkResource::GetTypeCode(void)
{
	return m_szTypeCode;
}

int CUnkResource::Initialize(HWND hwnd)
{
	return 1;
}

int CUnkResource::CloseAndSave(void)
{
	return 1;
}

int CUnkResource::CloseAndDontSave(void)
{
	return 1;
}
