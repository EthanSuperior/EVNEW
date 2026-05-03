// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CErrorLog.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <cstdio>
#include <cstdarg>
#include <windows.h>

#include "CErrorLog.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

std::basic_ostream<char, std::char_traits<char> > & (*CErrorLog::endl)(std::basic_ostream<char, std::char_traits<char> > &) = std::endl<char, std::char_traits<char> >;

CErrorLog * CErrorLog::ms_pCurrentLog = NULL;

CErrorLog::CErrorLog(void)
{
	m_iLogFileOpen = 0;

	m_szLogFileName = "";

	m_iAppend = 0;

	m_iLogFileAutoFlush = 0;

	m_iFatalError = 0;

	m_szFatalErrorMessage = "";

	m_iMaxWarningLevel = 9;
	m_iNumErrors       = 0;
}

CErrorLog::~CErrorLog(void)
{
	if(m_iLogFileOpen)
		CloseLogFile();
}

int CErrorLog::OpenLogFile(std::string szFilename, int iAppend)
{
	if(szFilename == "")
		return 0;

	m_szLogFileName = szFilename;

	m_iAppend = iAppend;

	if(m_iLogFileOpen)
		CloseLogFile();

	m_iLogFileOpen = 1;

	return 1;
}

int CErrorLog::CreateLogFile(void)
{
	int iFlags = std::ios::out | std::ios::trunc;

	if(m_iAppend)
		iFlags |= std::ios::app;

	m_foutLogFile.open(m_szLogFileName.c_str(), iFlags);

	if(!m_foutLogFile.is_open())
		return 0;

	return 1;
}

int CErrorLog::CloseLogFile(void)
{
	if(!m_iLogFileOpen)
		return 0;

	m_szLogFileName = "";

	m_foutLogFile.close();

	m_iLogFileOpen = 0;

	return 1;
}

int CErrorLog::WriteLogFile(char *szString, ...)
{
	if(!m_iLogFileOpen)
		return 0;

	char szBuffer[1024];

	va_list argList;

	va_start(argList, szString);
	vsprintf(szBuffer, szString, argList);
	va_end(argList);

	m_foutLogFile << szBuffer;

	if(m_iLogFileAutoFlush)
		m_foutLogFile.flush();

	return 1;
}

int CErrorLog::IsLogFileOpen(void)
{
	return (m_iLogFileOpen);
}

int CErrorLog::FlushLogFile(void)
{
	if(!m_iLogFileOpen)
		return 0;

	if(m_foutLogFile.is_open())
		m_foutLogFile.flush();

	return 1;
}

int CErrorLog::EnableLogFileAutoFlush(int iEnable)
{
	m_iLogFileAutoFlush = iEnable;

	return 1;
}

int CErrorLog::FatalError(std::string szError)
{
	m_iFatalError = 1;

	m_szFatalErrorMessage = szError;

	if(m_iLogFileOpen)
	{
		m_foutLogFile << "Fatal error: " << szError << std::endl;
		m_foutLogFile.flush();
	}

	MessageBox(NULL, szError.c_str(), "Fatal Error", MB_ICONEXCLAMATION | MB_OK);

	return 1;
}

int CErrorLog::FatalErrorDetected(void)
{
	return (m_iFatalError);
}

std::string CErrorLog::GetFatalErrorMessage(void)
{
	return (m_szFatalErrorMessage);
}

int CErrorLog::SetWarningLevel(int iLevel)
{
	m_iMaxWarningLevel = iLevel;

	return 1;
}

int CErrorLog::Error(int iLevel, std::string szError)
{
	m_iNumErrors++;

	int i;

	if((iLevel <= m_iMaxWarningLevel) && (m_iLogFileOpen))
	{
		for(i = 0; i < iLevel; i++)
			m_foutLogFile << ' ';

		m_foutLogFile << szError << std::endl;

		m_foutLogFile.flush();
	}

	return 1;
}

int CErrorLog::GetNumErrors(void)
{
	return (m_iNumErrors);
}

int CErrorLog::ClearErrors(void)
{
	m_iNumErrors = 0;

	return 1;
}

int CErrorLog::SetAsCurrentErrorLog(void)
{
	ms_pCurrentLog = this;

	return 1;
}

CErrorLog * CErrorLog::GetCurrentErrorLog(void)
{
	return ms_pCurrentLog;
}
