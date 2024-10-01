// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CException.cpp

////////////////////////////////////////////////////////////////
//////////////////////////  INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <cstdio>
#include <cstdarg>
#include <windows.h>

#include "CException.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CException::CException(void)
{
	m_szException = "Unspecified exception.";
}

CException::CException(char *szException, ...)
{
	if(szException != NULL)
	{
		char szBuffer[1024];

		va_list arglist;

		va_start(arglist, szException);

		vsprintf(szBuffer, szException, arglist);

		va_end(arglist);

		m_szException = szBuffer;
	}
	else
		m_szException = "Unspecified exception.";
}

CException::CException(const CException & exception)
{
	m_szException = exception.m_szException;
}

CException::~CException(void)
= default;

std::string CException::GetExceptionString(void)
{
	return m_szException;
}
