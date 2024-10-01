// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File Utils.h

#ifndef UTILS_H_INCLUDED		// Prevent multiple inclusions
#define UTILS_H_INCLUDED

////////////////////////////////////////////////////////////////
//////////////////////////  INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

constexpr double EPSILON = 0.000001;
constexpr float EPSILONF = 0.000001f;

extern const char g_cWinToMacCharMap[];
extern const char g_cMacToWinCharMap[];

////////////////////////////////////////////////////////////////
//////////////////////  INLINE FUNCTIONS  //////////////////////
////////////////////////////////////////////////////////////////

#ifndef DELETE_SAFE_DEFINED
#define DELETE_SAFE_DEFINED

template <class T>
inline void DeleteSafe(T & p)
{
	if(p != NULL)
	{
		delete p;

		p = NULL;
	}
}

#endif		// #ifndef DELETE_SAFE_DEFINED

#ifndef DELETE_ARRAY_SAFE_DEFINED
#define DELETE_ARRAY_SAFE_DEFINED

template <class T>
inline void DeleteArraySafe(T & a)
{
	if(a != NULL)
	{
		delete [] a;

		a = NULL;
	}
}

#endif		// #ifndef DELETE_ARRAY_SAFE_DEFINED

#ifndef DELETE_MATRIX_SAFE_DEFINED
#define DELETE_MATRIX_SAFE_DEFINED

template <class T>
inline void DeleteMatrixSafe(T ** m, int n)
{
	int i;

	if(m != NULL)
	{
		for(i = 0; i < n; i++)
		{
			if(m[i] != NULL)
			{
				delete [] m[i];

				m[i] = NULL;
			}
		}

		delete [] m;

		m = NULL;
	}
}

#endif		// #ifndef DELETE_MATRIX_SAFE_DEFINED

#ifndef TOSTRING_DEFINED
#define TOSTRING_DEFINED

template <class T>
std::string ToString(T obj)
{
	std::stringstream ss;
	std::string str;

	ss.unsetf(std::ios::skipws);

	ss << obj;

	ss >> str;

	return str;
}

template <class T>
T FromString(std::string & str)
{
	std::stringstream ss;
	T obj = static_cast<T>(0);

	ss.unsetf(std::ios::skipws);

	ss << str;

	ss >> obj;

	return obj;
}

#endif		// #ifndef TOSTRING_DEFINED

#ifndef SWAPENDIAN_INT
#define SWAPENDIAN_INT

inline int SwapEndianInt(UINT x)
{
	return static_cast<int>((x >> 24) | ((x >> 8) & 0x0000FF00) | ((x << 8) & 0x00FF0000) | (x << 24));
}

inline short SwapEndianShort(USHORT x)
{
	return static_cast<short>((x >> 8) | (x << 8));
}

inline void SwapEndian64(char *pData)
{
	char cTemp;

	cTemp = pData[0];
	pData[0] = pData[7];
	pData[7] = cTemp;

	cTemp = pData[1];
	pData[1] = pData[6];
	pData[6] = cTemp;

	cTemp = pData[2];
	pData[2] = pData[5];
	pData[5] = cTemp;

	cTemp = pData[3];
	pData[3] = pData[4];
	pData[4] = cTemp;
}

inline void SwapEndian80(char *pData)
{
	char cTemp;

	cTemp = pData[0];
	pData[0] = pData[9];
	pData[9] = cTemp;

	cTemp = pData[1];
	pData[1] = pData[8];
	pData[8] = cTemp;

	cTemp = pData[2];
	pData[2] = pData[7];
	pData[7] = cTemp;

	cTemp = pData[3];
	pData[3] = pData[6];
	pData[6] = cTemp;

	cTemp = pData[4];
	pData[4] = pData[5];
	pData[5] = cTemp;
}

#endif		// #ifndef SWAPENDIAN_INT

////////////////////////////////////////////////////////////////
////////////////////////////  TYPES  ///////////////////////////
////////////////////////////////////////////////////////////////

typedef unsigned short USHORT;
typedef unsigned short WORD;
typedef unsigned char  UCHAR;
typedef unsigned char  BYTE;

////////////////////////////////////////////////////////////////
/////////////////////	FUNCTION PROTOTYPES  ///////////////////
////////////////////////////////////////////////////////////////

int FixIntegerField(HWND hwndEdit);
int FixPositiveIntegerField(HWND hwndEdit);
int FixHexIntegerField(HWND hwndEdit);
int GetIntegerField(HWND hwndEdit);

int DoColorChooser(CWindow *pWindow, UINT *piColor);

UINT SwapColorRedBlue(UINT iColor);

USHORT Color24To15(UINT iColor);
UINT   Color15To24(USHORT iColor);

int ToMacString(char *szStr);
int ToMacString(std::string & szStr);
int ToWinString(char *szStr);
int ToWinString(std::string & szStr);

int PrintTextField(std::ostream & output, const char *pData, char cDelim);
int ReadTextField(std::istream & input, char *pData, int iCount);

int PrintHex16Field(std::ostream & output, const char *pData, char cDelim);
int ReadHex16Field(std::istream & input, char *pData);
int PrintHex32Field(std::ostream & output, const char *pData, char cDelim);
int ReadHex32Field(std::istream & input, char *pData);
int PrintHex64Field(std::ostream & output, const char *pData, char cDelim);
int ReadHex64Field(std::istream & input, char *pData);
int ReadHexChar(std::istream & input, char *pData);

#endif		// #ifndef UTILS_H_INCLUDED
