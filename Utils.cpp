// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File Utils.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include "Utils.h"

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

#pragma warning (disable: 4305)		// 'initializing' : truncation from 'const int' to 'const char'
#pragma warning (disable: 4309)		// 'initializing' : truncation of constant value

const char g_cWinToMacCharMap[256] =
	{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
	 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
	 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
	 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
	 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
	 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
	 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
	 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
	 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
	 0xA0, 0xC1, 0xA2, 0xA3, 0xA4, 0xB4, 0xA6, 0xA4, 0xAC, 0xA9, 0xAA, 0xC7, 0xC2, 0xAD, 0xA8, 0xF8,
	 0xB0, 0xB1, 0xB2, 0xB3, 0xAB, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xC8, 0xBC, 0xBD, 0xBE, 0xC0,
	 0xCB, 0xE7, 0xE5, 0xC3, 0x80, 0xC5, 0xC6, 0x82, 0xE9, 0x83, 0xE6, 0xE8, 0xED, 0xEA, 0xEB, 0xEC,
	 0xD0, 0x84, 0xF1, 0xEE, 0xEF, 0xCD, 0x85, 0xD7, 0xAF, 0xF4, 0xDA, 0xF3, 0x86, 0xDD, 0xDE, 0xDF,
	 0x88, 0x87, 0x89, 0x8B, 0x8A, 0x8C, 0xBE, 0x8D, 0x8F, 0x8E, 0x90, 0x91, 0x93, 0x92, 0x94, 0x95,
	 0xF0, 0x96, 0x98, 0x97, 0x99, 0xF5, 0x9A, 0xD6, 0xBF, 0xF9, 0xFA, 0xFB, 0x9F, 0xFD, 0xFE, 0xFF};

const char g_cMacToWinCharMap[256] =
	{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
	 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
	 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
	 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
	 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
	 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
	 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
	 0xC4, 0x81, 0xC7, 0xC9, 0xD1, 0xD6, 0xDC, 0xE1, 0xE0, 0xE2, 0xE4, 0xE3, 0xE5, 0xE7, 0xE9, 0xE8,
	 0xEA, 0xEB, 0xED, 0xEC, 0xEE, 0xEF, 0xF1, 0xF3, 0xF2, 0xF4, 0xF6, 0x9B, 0x9C, 0x9D, 0x9E, 0xFC,
	 0xA0, 0xA1, 0xA2, 0xA3, 0xA7, 0xA5, 0xA6, 0xA7, 0xAE, 0xA9, 0xAA, 0xB4, 0xA8, 0xAD, 0xAE, 0xD8,
	 0xB0, 0xB1, 0xB2, 0xB3, 0xA5, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xE6, 0xF8,
	 0xBF, 0xA1, 0xAC, 0xC3, 0xC4, 0xC5, 0xC6, 0xAB, 0xBB, 0xC9, 0xCA, 0xC0, 0xCC, 0xD5, 0xCE, 0xCF,
	 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xF7, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
	 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xC2, 0xCA, 0xC1, 0xCB, 0xC8, 0xCD, 0xCE, 0xCF, 0xCC, 0xD3, 0xD4,
	 0xF0, 0xD2, 0xF2, 0xDB, 0xD9, 0xF5, 0xF6, 0xF7, 0xAF, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF};

#pragma warning (default: 4305)
#pragma warning (default: 4309)

////////////////////////////////////////////////////////////////
//////////////////////////	FUNCTIONS  /////////////////////////
////////////////////////////////////////////////////////////////

int FixIntegerField(HWND hwndEdit)
{
	char szBuffer[1024];

	Edit_GetText(hwndEdit, szBuffer, 1024);

	DWORD dwSelection;

	dwSelection = Edit_GetSel(hwndEdit);

	int size = strlen(szBuffer);

	std::string szResult;

	if(size == 0)
		return 0;

	if((szBuffer[0] == '-') || ((szBuffer[0] >= '0') && (szBuffer[0] <= '9')))
		szResult = szBuffer[0];

	int i;

	for(i = 1; i < size; i++)
	{
		if((szBuffer[i] >= '0') && (szBuffer[i] <= '9'))
			szResult += szBuffer[i];
	}

	if(szResult != szBuffer)
	{
		Edit_SetText(hwndEdit, szResult.c_str());

		Edit_SetSel(hwndEdit, LOWORD(dwSelection), HIWORD(dwSelection));

		return 0;
	}

	return 1;
}

int FixPositiveIntegerField(HWND hwndEdit)
{
	char szBuffer[1024];

	Edit_GetText(hwndEdit, szBuffer, 1024);

	DWORD dwSelection;

	dwSelection = Edit_GetSel(hwndEdit);

	int size = strlen(szBuffer);

	std::string szResult;

	if(size == 0)
		return 0;

	int i;

	for(i = 0; i < size; i++)
	{
		if((szBuffer[i] >= '0') && (szBuffer[i] <= '9'))
			szResult += szBuffer[i];
	}

	if(szResult != szBuffer)
	{
		Edit_SetText(hwndEdit, szResult.c_str());

		Edit_SetSel(hwndEdit, LOWORD(dwSelection), HIWORD(dwSelection));

		return 0;
	}

	return 1;
}

int FixHexIntegerField(HWND hwndEdit)
{
	char szBuffer[1024];

	Edit_GetText(hwndEdit, szBuffer, 1024);

	DWORD dwSelection;

	dwSelection = Edit_GetSel(hwndEdit);

	int size = strlen(szBuffer);

	std::string szResult;

	if(size == 0)
		return 0;

	int i;

	for(i = 0; i < size; i++)
	{
		if(((szBuffer[i] >= '0') && (szBuffer[i] <= '9')) || ((szBuffer[i] >= 'A') && (szBuffer[i] <= 'F')))
			szResult += szBuffer[i];
		else if((szBuffer[i] >= 'a') && (szBuffer[i] <= 'f'))
			szResult += szBuffer[i] + 'A' - 'a';
	}

	if(szResult != szBuffer)
	{
		Edit_SetText(hwndEdit, szResult.c_str());

		Edit_SetSel(hwndEdit, LOWORD(dwSelection), HIWORD(dwSelection));

		return 0;
	}

	return 1;
}

int GetIntegerField(HWND hwndEdit)
{
	char szBuffer[1024];

	Edit_GetText(hwndEdit, szBuffer, 1024);

	return (FromString<int>((std::string)szBuffer));
}

int DoColorChooser(CWindow *pWindow, UINT *piColor)
{
	if((pWindow == NULL) || (piColor == NULL))
		return 0;

	COLORREF iCustomColors[16];

	CHOOSECOLOR cc;

	memset(&cc, 0, sizeof(CHOOSECOLOR));

	cc.lStructSize  = sizeof(CHOOSECOLOR);
	cc.hwndOwner    = pWindow->GetHWND();
	cc.rgbResult    = SwapColorRedBlue(*piColor);
	cc.lpCustColors = iCustomColors;
	cc.Flags        = CC_ANYCOLOR | CC_FULLOPEN | CC_RGBINIT;

	if(ChooseColor(&cc) != 0)
		*piColor = SwapColorRedBlue(cc.rgbResult);

	return 1;
}

UINT SwapColorRedBlue(UINT iColor)
{
	return ((iColor & 0xFF00FF00) | ((iColor >> 16) & 0x000000FF) | ((iColor << 16) & 0x00FF0000));
}

USHORT Color24To15(UINT iColor)
{
	return (USHORT)(((iColor & 0x00F80000) >> 9) | ((iColor & 0x0000F800) >> 6) | ((iColor & 0x000000F8) >> 3));
}

UINT Color15To24(USHORT iColor)
{
	return (UINT)((((UINT)iColor & 0x7C00) << 9) | (((UINT)iColor & 0x7000) << 4) | (((UINT)iColor & 0x03E0) << 6) | (((UINT)iColor & 0x0380) << 1) | (((UINT)iColor & 0x001F) << 3) | (((UINT)iColor & 0x001C) >> 2));
}

int ToMacString(char *szStr)
{
	int i;

	int iLength = strlen(szStr);

	for(i = 0; i < iLength; i++)
		szStr[i] = g_cWinToMacCharMap[(UCHAR)szStr[i]];

	return 1;
}

int ToMacString(std::string & szStr)
{
	int i;

	for(i = 0; i < szStr.size(); i++)
		szStr[i] = g_cWinToMacCharMap[(UCHAR)szStr[i]];

	return 1;
}

int ToWinString(char *szStr)
{
	int i;

	int iLength = strlen(szStr);

	for(i = 0; i < iLength; i++)
		szStr[i] = g_cMacToWinCharMap[(UCHAR)szStr[i]];

	return 1;
}

int ToWinString(std::string & szStr)
{
	int i;

	for(i = 0; i < szStr.size(); i++)
		szStr[i] = g_cMacToWinCharMap[(UCHAR)szStr[i]];

	return 1;
}

int PrintTextField(std::ostream & output, const char *pData, char cDelim)
{
	int iLength = strlen(pData);

	output << "\"";

	int i;

	for(i = 0; i < iLength; i++)
	{
		if(pData[i] == '\\')
			output << "\\\\";
		else if(pData[i] == '\"')
			output << "\\q";
		else if(pData[i] == '\n')
			output << "\\n";
		else if(pData[i] == '\r')
			output << "\\r";
		else if(pData[i] == '\t')
			output << "\\t";
		else
			output << pData[i];
	}

	output << "\"" << cDelim;

	return 1;
}

int ReadTextField(std::istream & input, char *pData, int iCount)
{
	char c;

	c = input.get();

	int iIsQuoted = 0;

	int i;

	if(c == '\"')
	{
		iIsQuoted = 1;

		i = 0;
	}
	else
	{
		if(c == '\\')
		{
			c = input.get();

			if(c == '\\')
				pData[0] = '\\';
			else if((c == 'q') || (c == '\"'))
				pData[0] = '\"';
			else if(c == 'n')
				pData[0] = '\n';
			else if(c == 'r')
				pData[0] = '\r';
			else if(c == 't')
				pData[0] = '\t';
			else
				pData[0] = c;
		}
		else if((c == '\t') || (c == '\n'))
		{
			pData[0] = '\0';

			return 1;
		}
		else
			pData[0] = c;

		i = 1;
	}

	for( ; i < iCount; i++)
	{
		c = input.get();

		if((!iIsQuoted) && ((c == '\t') || (c == '\n')))
		{
			pData[i] = '\0';

			break;
		}

		if((iIsQuoted) && (c == '\"'))
		{
			pData[i] = '\0';

			input.ignore(1);

			break;
		}

		if(c == '\\')
		{
			c = input.get();

			if(c == '\\')
				pData[i] = '\\';
			else if((c == 'q') || (c == '\"'))
				pData[i] = '\"';
			else if(c == 'n')
				pData[i] = '\n';
			else if(c == 'r')
				pData[i] = '\r';
			else if(c == 't')
				pData[i] = '\t';
			else
				pData[i] = c;
		}
		else
			pData[i] = c;
	}

	if(i == iCount)
	{
		while(!input.eof())
		{
			c = input.get();

			if((iIsQuoted) && ((c == '\t') || (c == '\n')))
				break;

			if((iIsQuoted) && (c == '\"'))
			{
				input.ignore(1);

				break;
			}

			if(c == '\\')
				input.ignore(1);
		}
	}

	pData[iCount - 1] = '\0';

	if(input.eof())
		return 0;

	return 1;
}

int PrintHex16Field(std::ostream & output, const char *pData, char cDelim)
{
	output << "0x";

	int i;

	static const char s_cHexChars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	for(i = 1; i >= 0; i--)
		output << s_cHexChars[(pData[i] >> 4) & 0x0F] << s_cHexChars[pData[i] & 0x0F];

	output << cDelim;

	return 1;
}

int ReadHex16Field(std::istream & input, char *pData)
{
	pData[0] = 0x00;
	pData[1] = 0x00;

	char c1, c2;

	c1 = input.peek();

	while(((c1 == ' ') || (c1 == '\n') || (c1 == '\t')) && (!input.eof()))
	{
		input.ignore(1);

		c1 = input.peek();
	}

	if(input.eof())
		return 0;

	if(c1 == '0')
	{
		c1 = input.get();

		if((c2 = input.get()) != 'x')
		{
			if((c2 >= '0') && (c2 <= '9'))
				c2 -= '0';
			else if((c2 >= 'a') && (c2 <= 'z'))
				c2 += 10 - 'a';
			else if((c2 >= 'A') && (c2 <= 'A'))
				c2 += 10 - 'A';
			else
				return 0;

			pData[1] |= c2;

			if(ReadHexChar(input, pData + 0) == 0)
				return 0;
		}
		else
		{
			if((ReadHexChar(input, pData + 1) == 0) ||
			   (ReadHexChar(input, pData + 0) == 0))
			   return 0;
		}
	}
	else if(((c1 >= '1') && (c1 <= '9')) || ((c1 >= 'a') && (c1 <= 'f')) || ((c1 >= 'A') && (c1 <= 'F')))
	{
		if((ReadHexChar(input, pData + 1) == 0) ||
		   (ReadHexChar(input, pData + 0) == 0))
		   return 0;
	}
	else if((c1 != '#') && (c1 != '$'))
		return 0;

	input.ignore(1);

	if(input.eof())
		return 0;

	return 1;
}

int PrintHex32Field(std::ostream & output, const char *pData, char cDelim)
{
	output << "0x";

	int i;

	static const char s_cHexChars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	for(i = 3; i >= 0; i--)
		output << s_cHexChars[(pData[i] >> 4) & 0x0F] << s_cHexChars[pData[i] & 0x0F];

	output << cDelim;

	return 1;
}

int ReadHex32Field(std::istream & input, char *pData)
{
	pData[0] = 0x00;
	pData[1] = 0x00;
	pData[2] = 0x00;
	pData[3] = 0x00;

	char c1, c2;

	c1 = input.peek();

	while(((c1 == ' ') || (c1 == '\n') || (c1 == '\t')) && (!input.eof()))
	{
		input.ignore(1);

		c1 = input.peek();
	}

	if(input.eof())
		return 0;

	if(c1 == '0')
	{
		c1 = input.get();

		if((c2 = input.get()) != 'x')
		{
			if((c2 >= '0') && (c2 <= '9'))
				c2 -= '0';
			else if((c2 >= 'a') && (c2 <= 'z'))
				c2 += 10 - 'a';
			else if((c2 >= 'A') && (c2 <= 'A'))
				c2 += 10 - 'A';
			else
				return 0;

			pData[3] |= c2;

			if((ReadHexChar(input, pData + 2) == 0) ||
			   (ReadHexChar(input, pData + 1) == 0) ||
			   (ReadHexChar(input, pData + 0) == 0))
				return 0;
		}
		else
		{
			if((ReadHexChar(input, pData + 3) == 0) ||
			   (ReadHexChar(input, pData + 2) == 0) ||
			   (ReadHexChar(input, pData + 1) == 0) ||
			   (ReadHexChar(input, pData + 0) == 0))
				return 0;
		}
	}
	else if(((c1 >= '1') && (c1 <= '9')) || ((c1 >= 'a') && (c1 <= 'f')) || ((c1 >= 'A') && (c1 <= 'F')))
	{
		if((ReadHexChar(input, pData + 3) == 0) ||
		   (ReadHexChar(input, pData + 2) == 0) ||
		   (ReadHexChar(input, pData + 1) == 0) ||
		   (ReadHexChar(input, pData + 0) == 0))
			return 0;
	}
	else if((c1 != '#') && (c1 != '$'))
		return 0;

	input.ignore(1);

	if(input.eof())
		return 0;

	return 1;
}

int PrintHex64Field(std::ostream & output, const char *pData, char cDelim)
{
	output << "0x";

	int i;

	static const char s_cHexChars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	for(i = 0; i < 8; i++)
		output << s_cHexChars[(pData[i] >> 4) & 0x0F] << s_cHexChars[pData[i] & 0x0F];

	output << cDelim;

	return 1;
}

int ReadHex64Field(std::istream & input, char *pData)
{
	pData[0] = 0x00;
	pData[1] = 0x00;
	pData[2] = 0x00;
	pData[3] = 0x00;
	pData[4] = 0x00;
	pData[5] = 0x00;
	pData[6] = 0x00;
	pData[7] = 0x00;

	char c1, c2;

	c1 = input.peek();

	while(((c1 == ' ') || (c1 == '\n') || (c1 == '\t')) && (!input.eof()))
	{
		input.ignore(1);

		c1 = input.peek();
	}

	if(input.eof())
		return 0;

	if(c1 == '0')
	{
		c1 = input.get();

		if((c2 = input.get()) != 'x')
		{
			if((c2 >= '0') && (c2 <= '9'))
				c2 -= '0';
			else if((c2 >= 'a') && (c2 <= 'z'))
				c2 += 10 - 'a';
			else if((c2 >= 'A') && (c2 <= 'A'))
				c2 += 10 - 'A';
			else
				return 0;

			pData[0] |= c2;

			if((ReadHexChar(input, pData + 1) == 0) ||
			   (ReadHexChar(input, pData + 2) == 0) ||
			   (ReadHexChar(input, pData + 3) == 0) ||
			   (ReadHexChar(input, pData + 4) == 0) ||
			   (ReadHexChar(input, pData + 5) == 0) ||
			   (ReadHexChar(input, pData + 6) == 0) ||
			   (ReadHexChar(input, pData + 7) == 0))
				return 0;
		}
		else
		{
			if((ReadHexChar(input, pData + 0) == 0) ||
			   (ReadHexChar(input, pData + 1) == 0) ||
			   (ReadHexChar(input, pData + 2) == 0) ||
			   (ReadHexChar(input, pData + 3) == 0) ||
			   (ReadHexChar(input, pData + 4) == 0) ||
			   (ReadHexChar(input, pData + 5) == 0) ||
			   (ReadHexChar(input, pData + 6) == 0) ||
			   (ReadHexChar(input, pData + 7) == 0))
				return 0;
		}
	}
	else if(((c1 >= '1') && (c1 <= '9')) || ((c1 >= 'a') && (c1 <= 'f')) || ((c1 >= 'A') && (c1 <= 'F')))
	{
		if((ReadHexChar(input, pData + 0) == 0) ||
		   (ReadHexChar(input, pData + 1) == 0) ||
		   (ReadHexChar(input, pData + 2) == 0) ||
		   (ReadHexChar(input, pData + 3) == 0) ||
		   (ReadHexChar(input, pData + 4) == 0) ||
		   (ReadHexChar(input, pData + 5) == 0) ||
		   (ReadHexChar(input, pData + 6) == 0) ||
		   (ReadHexChar(input, pData + 7) == 0))
			return 0;
	}
	else if((c1 != '#') && (c1 != '$'))
		return 0;

	input.ignore(1);

	if(input.eof())
		return 0;

	return 1;
}

int ReadHexChar(std::istream & input, char *pData)
{
	char c1, c2;

	c1 = input.get();

	*pData = 0x00;

	if((c1 >= '0') && (c1 <= '9'))
		*pData |= (c1 - '0') << 4;
	else if((c1 >= 'a') && (c1 <= 'f'))
		*pData |= (c1 - 'a' + 10) << 4;
	else if((c1 >= 'A') && (c1 <= 'F'))
		*pData |= (c1 - 'A' + 10) << 4;
	else
		return 0;

	c2 = input.get();

	if((c2 >= '0') && (c2 <= '9'))
		*pData |= c2 - '0';
	else if((c2 >= 'a') && (c2 <= 'f'))
		*pData |= c2 - 'a' + 10;
	else if((c2 >= 'A') && (c2 <= 'F'))
		*pData |= c2 - 'A' + 10;
	else
		return 0;

	return 1;
}
