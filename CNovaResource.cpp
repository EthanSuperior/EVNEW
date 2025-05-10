// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CNovaResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <string.h>

#include "CNovaResource.h"
#include "CControl.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CNovaResource::CNovaResource(void)
{
	m_iID = 128;

	memset(m_szName, 0, 256 * sizeof(char));

	m_iIsNew = 1;

	m_pWindow = NULL;
}

CNovaResource::~CNovaResource(void)
{

}

int CNovaResource::SetID(short iID)
{
	m_iID = iID;
	
	return 1;
}

short CNovaResource::GetID(void)
{
	return m_iID;
}

int CNovaResource::SetName(const char *szName)
{
	strcpy(m_szName, szName);

	return 1;
}

char * CNovaResource::GetName(void)
{
	return m_szName;
}

int CNovaResource::SetIsNew(int iIsNew)
{
	m_iIsNew = iIsNew;

	return 1;
}

int CNovaResource::IsNew(void)
{
	return m_iIsNew;
}

int CNovaResource::SetWindow(CWindow *pWindow)
{
	m_pWindow = pWindow;

	return 1;
}

CWindow * CNovaResource::GetWindow(void)
{
	return m_pWindow;
}

int CNovaResource::GetNumFields(void)
{
	return 0;
}

const std::string * CNovaResource::GetFieldNames(void)
{
	return NULL;
}

int CNovaResource::ShouldLoadDirect(void)
{
	return 0;
}

int CNovaResource::SaveDirect(std::ostream & output)
{
	return 1;
}

int CNovaResource::LoadDirect(std::istream & input, int iSize)
{
	return 1;
}

int CNovaResource::SaveToText(std::ostream & output)
{
	return 1;
}

int CNovaResource::SaveToTextEx(std::ostream & output, std::string & szFilePath, std::string & szFilename1, std::string & szFilename2, int iParam)
{
	return 1;
}

int CNovaResource::LoadFromText(std::istream & input)
{
	return 1;
}

int CNovaResource::LoadFromTextEx(std::istream & input, std::string & szFilePath)
{
	return 1;
}

void CNovaResource::SetIfDefaultInt(CControl* m_controls, short controlID, short oldV, short newV, short offset) {
	if (m_controls[controlID].GetInt() != 0 && m_controls[controlID].GetInt() != oldV + offset) return;
	m_controls[controlID].SetInt(newV + offset);
}

void CNovaResource::SetIfDefaultStr(CControl* m_controls, short controlID, short oldBit, short newBit) {
	std::string oldBitStr = std::to_string(oldBit);
	std::string bitsStr = m_controls[controlID].GetString();
	if (bitsStr.find(oldBitStr) == std::string::npos) return;
	std::string newBitStr = std::to_string(newBit);
	bitsStr.replace(bitsStr.find(oldBitStr), oldBitStr.length(), newBitStr);
	m_controls[controlID].SetString(bitsStr.c_str());
}
