// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CErrorLog.h

#ifndef CERRORLOG_H		// Prevent multiple inclusions
#define CERRORLOG_H

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CErrorLog;

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <fstream>
#include <string>

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CErrorLog
{
public:
	CErrorLog(void);		// Constructor
	~CErrorLog(void);		// Destructor

	int OpenLogFile(std::string szFilename, int iAppend);	// Open the log file
	int CloseLogFile(void);									// Close the log file
	int WriteLogFile(char *szString, ...);					// Write to the log file using printf style

	template <class T> CErrorLog & operator << (T obj)	// Write data to the log file
	{													// using C++ iostream operator <<
		if(m_iLogFileOpen)
		{
			if(m_iLogFileOpen == 1)
			{
				if(CreateLogFile() == 0)
					return (*this);

				m_iLogFileOpen = 2;
			}

			m_foutLogFile << obj;

			if(m_iLogFileAutoFlush)
				m_foutLogFile.flush();
		}

		return (*this);
	}

	int IsLogFileOpen(void);				// Is the log file open
	int FlushLogFile(void);					// Flush the log file
	int EnableLogFileAutoFlush(int iEnable = 1);	// Enable/disable automatic file flushing

	int FatalError(std::string szError); 	// Alert a fatal error
	int FatalErrorDetected(void);			// Has a fatal error been detected
	std::string GetFatalErrorMessage(void);	// Get the fatal error message

	int SetWarningLevel(int iLevel);				// Set the maximum error/warning level
	int Error(int iLevel, std::string szError);		// Alert an error

	int GetNumErrors(void);			// Get the number of errors
	int ClearErrors(void);			// Clear the errors

	int SetAsCurrentErrorLog(void);

	static CErrorLog * GetCurrentErrorLog(void);

	static std::basic_ostream<char, std::char_traits<char> > & (*endl)(std::basic_ostream<char, std::char_traits<char> > &);

private:

	int CreateLogFile(void);

	int  m_iLogFileOpen;			// Is the log file open
	std::string m_szLogFileName; 	// The log file name
	int  m_iLogFileAutoFlush;		// Is automatic file flushing on

	int m_iAppend;

	std::ofstream m_foutLogFile; 		// The file output object

	int m_iFatalError;					// Has a fatal error been detected
	std::string m_szFatalErrorMessage; 	// The fatal error message

	int m_iMaxWarningLevel;			// The maximum error/warning level to be processed
	int m_iNumErrors;

	static CErrorLog * ms_pCurrentLog;
};

#endif		// #ifndef _ERRORLOG_H
