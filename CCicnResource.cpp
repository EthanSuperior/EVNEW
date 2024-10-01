// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CNovaResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CCicnResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CCicnResource::CCicnResource(void)
{
	m_iWidth  = 0;
	m_iHeight = 0;
	m_iBPP    = 0;

	m_iNumColors = 0;

	m_iTempWidth  = 0;
	m_iTempHeight = 0;
	m_iTempBPP    = 0;

	m_iTempNumColors = 0;
}

CCicnResource::~CCicnResource(void)
{

}

int CCicnResource::GetType(void)
{
	return CNR_TYPE_CICN;
}

int CCicnResource::GetSize(void)
{
	int iSize = 90;

	int iRowBytes = (m_iWidth * m_iBPP + 7) / 8;

	iRowBytes += iRowBytes & 1;

	int iMaskRowBytes = (m_iWidth + 7) / 8;

	iMaskRowBytes += (2 - (iMaskRowBytes & 1)) & 1;

	iSize += 2 * m_iHeight * iMaskRowBytes;
	iSize += m_iNumColors * 8;
	iSize += m_iHeight * iRowBytes;

	return iSize;
}

int CCicnResource::GetDialogID(void)
{
	return IDD_EDIT_CICN;
}

DLGPROCNOCALLBACK CCicnResource::GetDialogProc(void)
{
	return CicnDlgProc;
}

int CCicnResource::GetNumFields(void)
{
	return NUM_CICN_FIELDS;
}

const std::string * CCicnResource::GetFieldNames(void)
{
	return g_szCicnFields;
}

int CCicnResource::Save(char *pOutput)
{
	// Save PixMap

	*(int *)pOutput = SwapEndianInt(0x00000000); pOutput += sizeof(int);	// baseAddr

	short iRowBytes = (m_iWidth * m_iBPP) / 8;

	iRowBytes += iRowBytes & 1;

	iRowBytes |= 0x8000;

	*(short *)pOutput = SwapEndianShort(iRowBytes); pOutput += sizeof(short);	// rowBytes

	short iBoundsLeft   = 0;
	short iBoundsTop    = 0;
	short iBoundsRight  = (short)m_iWidth;
	short iBoundsBottom = (short)m_iHeight;

	*(short *)pOutput = SwapEndianShort(iBoundsTop);    pOutput += sizeof(short);	// bounds
	*(short *)pOutput = SwapEndianShort(iBoundsLeft);   pOutput += sizeof(short);
	*(short *)pOutput = SwapEndianShort(iBoundsBottom); pOutput += sizeof(short);
	*(short *)pOutput = SwapEndianShort(iBoundsRight);  pOutput += sizeof(short);

	*(short *)pOutput = SwapEndianShort(0x0000);   pOutput += sizeof(short);	// pmVersion
	*(short *)pOutput = SwapEndianShort(0x0000);   pOutput += sizeof(short);	// packType
	*(int   *)pOutput = SwapEndianInt(0x00000000); pOutput += sizeof(int);		// packSize
	*(int   *)pOutput = SwapEndianInt(0x00480000); pOutput += sizeof(int);		// hRes
	*(int   *)pOutput = SwapEndianInt(0x00480000); pOutput += sizeof(int);		// vRes
	*(short *)pOutput = SwapEndianShort(0x0000);	  pOutput += sizeof(short);	// pixelType

	short iBPP = (short)m_iBPP;

	*(short *)pOutput = SwapEndianShort(iBPP);     pOutput += sizeof(short);	// pixelSize
	*(short *)pOutput = SwapEndianShort(0x0001);   pOutput += sizeof(short);	// cmpCount
	*(short *)pOutput = SwapEndianShort(iBPP);     pOutput += sizeof(short);	// cmpSize
	*(int   *)pOutput = SwapEndianInt(0x00000000); pOutput += sizeof(int);		// planeBytes
	*(int   *)pOutput = SwapEndianInt(0x00000000); pOutput += sizeof(int);		// pmTable
	*(int   *)pOutput = SwapEndianInt(0x00000000); pOutput += sizeof(int);		// pmReserved

	// Save mask BitMap

	short iMaskRowBytes = (m_iWidth + 7) / 8;

	iMaskRowBytes += iMaskRowBytes & 1;

	*(int   *)pOutput = SwapEndianInt(0x00000000);      pOutput += sizeof(int);		// baseAddr
	*(short *)pOutput = SwapEndianShort(iMaskRowBytes); pOutput += sizeof(short);	// rowBytes
	*(short *)pOutput = SwapEndianShort(iBoundsTop);    pOutput += sizeof(short);	// bounds
	*(short *)pOutput = SwapEndianShort(iBoundsLeft);   pOutput += sizeof(short);
	*(short *)pOutput = SwapEndianShort(iBoundsBottom); pOutput += sizeof(short);
	*(short *)pOutput = SwapEndianShort(iBoundsRight);  pOutput += sizeof(short);

	// Save 1-bit BitMap

	*(int   *)pOutput = SwapEndianInt(0x00000000);      pOutput += sizeof(int);		// baseAddr
	*(short *)pOutput = SwapEndianShort(iMaskRowBytes); pOutput += sizeof(short);	// rowBytes
	*(short *)pOutput = SwapEndianShort(iBoundsTop);    pOutput += sizeof(short);	// bounds
	*(short *)pOutput = SwapEndianShort(iBoundsLeft);   pOutput += sizeof(short);
	*(short *)pOutput = SwapEndianShort(iBoundsBottom); pOutput += sizeof(short);
	*(short *)pOutput = SwapEndianShort(iBoundsRight);  pOutput += sizeof(short);

	// Save icon data

	*(int *)pOutput = SwapEndianInt(0x00000000); pOutput += sizeof(int);

	// Save mask data

	int i, j;

	UCHAR ucPixel;

	int iAlignment = ((m_iWidth + 7) / 8) & 1;

	for(i = 0; i < m_iHeight; i++)
	{
		ucPixel = 0x00;

		for(j = 0; j < m_iWidth; j++)
		{
			if(((j & 7) == 0) && (j > 0))
			{
				*pOutput = (char)ucPixel; pOutput++;

				ucPixel = 0x00;
			}

			if(m_vMaskData[(i * m_iWidth + j) * 3] == 0xFF)
				ucPixel |= 1 << (7 - (j & 7));
		}

		*pOutput = (char)ucPixel; pOutput++;

		if(iAlignment > 0)
		{
			memset(pOutput, 0x00, iAlignment); pOutput += iAlignment;
		}
	}

	// Save 1-bit data

	memset(pOutput, 0x00, m_iHeight * iMaskRowBytes); pOutput += m_iHeight * iMaskRowBytes;

	// Save color table

	*(int   *)pOutput = SwapEndianInt(0x00000000); pOutput += sizeof(int);		// ctSeed
	*(short *)pOutput = SwapEndianShort(0x0000);   pOutput += sizeof(short);	// ctFlags

	short iNumColors = m_iNumColors - 1;

	*(short *)pOutput = SwapEndianShort(iNumColors); pOutput += sizeof(short);

	USHORT iIndex;
	USHORT iRed, iGreen, iBlue;

	for(i = 0; i < m_vColorTable.size(); i++)
	{
		if(m_vColorTable[i] & 0x80000000)
		{
			iIndex = (USHORT)i;

			iRed   = (USHORT) ((m_vColorTable[i] & 0x000000FF)        * 0x0101);
			iGreen = (USHORT)(((m_vColorTable[i] & 0x0000FF00) >> 8)  * 0x0101);
			iBlue  = (USHORT)(((m_vColorTable[i] & 0x00FF0000) >> 16) * 0x0101);

			*(USHORT *)pOutput = SwapEndianShort(iIndex); pOutput += sizeof(USHORT);
			*(USHORT *)pOutput = SwapEndianShort(iRed);   pOutput += sizeof(USHORT);
			*(USHORT *)pOutput = SwapEndianShort(iGreen); pOutput += sizeof(USHORT);
			*(USHORT *)pOutput = SwapEndianShort(iBlue);  pOutput += sizeof(USHORT);
		}
	}

	// Save icon data

	if(m_iBPP == 1)
	{
		iAlignment = ((m_iWidth + 7) / 8) & 1;

		for(i = 0; i < m_iHeight; i++)
		{
			ucPixel = 0x00;

			for(j = 0; j < m_iWidth; j++)
			{
				if(((j & 7) == 0) && (j > 0))
				{
					*pOutput = (char)ucPixel; pOutput++;

					ucPixel = 0x00;
				}

				ucPixel |= (FindColor(m_vIconData[(i * m_iWidth + j) * 3 + 2], m_vIconData[(i * m_iWidth + j) * 3 + 1], m_vIconData[(i * m_iWidth + j) * 3]) & 0x01) << (7 - (j & 7));
			}

			*pOutput = (char)ucPixel; pOutput++;

			if(iAlignment > 0)
			{
				memset(pOutput, 0x00, iAlignment); pOutput += iAlignment;
			}
		}
	}
	else if(m_iBPP == 2)
	{
		iAlignment = ((m_iWidth + 3) / 4) & 1;

		for(i = 0; i < m_iHeight; i++)
		{
			ucPixel = 0x00;

			for(j = 0; j < m_iWidth; j++)
			{
				if(((j & 3) == 0) && (j > 0))
				{
					*pOutput = (char)ucPixel; pOutput++;

					ucPixel = 0x00;
				}

				ucPixel |= (FindColor(m_vIconData[(i * m_iWidth + j) * 3 + 2], m_vIconData[(i * m_iWidth + j) * 3 + 1], m_vIconData[(i * m_iWidth + j) * 3]) & 0x03) << ((3 - (j & 3)) << 1);
			}

			*pOutput = (char)ucPixel; pOutput++;

			if(iAlignment > 0)
			{
				memset(pOutput, 0x00, iAlignment); pOutput += iAlignment;
			}
		}
	}
	else if(m_iBPP == 4)
	{
		iAlignment = ((m_iWidth + 1) / 2) & 1;

		for(i = 0; i < m_iHeight; i++)
		{
			ucPixel = 0x00;

			for(j = 0; j < m_iWidth; j++)
			{
				if(((j & 1) == 0) && (j > 0))
				{
					*pOutput = (char)ucPixel; pOutput++;

					ucPixel = 0x00;
				}

				ucPixel |= (FindColor(m_vIconData[(i * m_iWidth + j) * 3 + 2], m_vIconData[(i * m_iWidth + j) * 3 + 1], m_vIconData[(i * m_iWidth + j) * 3]) & 0x0F) << ((1 - (j & 1)) << 2);
			}

			*pOutput = (char)ucPixel; pOutput++;

			if(iAlignment > 0)
			{
				memset(pOutput, 0x00, iAlignment); pOutput += iAlignment;
			}
		}
	}
	else if(m_iBPP == 8)
	{
		iAlignment = m_iWidth & 1;

		for(i = 0; i < m_iHeight; i++)
		{
			for(j = 0; j < m_iWidth; j++)
			{
				ucPixel = FindColor(m_vIconData[(i * m_iWidth + j) * 3 + 2], m_vIconData[(i * m_iWidth + j) * 3 + 1], m_vIconData[(i * m_iWidth + j) * 3]);

				*pOutput = (char)ucPixel; pOutput++;
			}

			if(iAlignment > 0)
			{
				memset(pOutput, 0x00, iAlignment); pOutput += iAlignment;
			}
		}
	}

	return 1;
}

int CCicnResource::Load(char *pInput, int iSize)
{
	CEditor *pEditor = CEditor::GetCurrentEditor();
	CErrorLog *pLog  = CErrorLog::GetCurrentErrorLog();

	// Load PixMap

	short iRowBytes;

	pInput += sizeof(int);	// baseAddr

	iRowBytes = *(short *)pInput; iRowBytes = SwapEndianShort(iRowBytes); pInput += sizeof(short);	// rowBytes

	iRowBytes &= 0x3FFF;

	short iBoundsLeft;
	short iBoundsTop;
	short iBoundsRight;
	short iBoundsBottom;

	iBoundsTop    = *(short *)pInput; iBoundsTop    = SwapEndianShort(iBoundsTop);    pInput += sizeof(short);	// bounds
	iBoundsLeft   = *(short *)pInput; iBoundsLeft   = SwapEndianShort(iBoundsLeft);   pInput += sizeof(short);
	iBoundsBottom = *(short *)pInput; iBoundsBottom = SwapEndianShort(iBoundsBottom); pInput += sizeof(short);
	iBoundsRight  = *(short *)pInput; iBoundsRight  = SwapEndianShort(iBoundsRight);  pInput += sizeof(short);

	m_iWidth  = iBoundsRight  - iBoundsLeft;
	m_iHeight = iBoundsBottom - iBoundsTop;

	pInput += sizeof(short);	// pmVersion
	pInput += sizeof(short);	// packType
	pInput += sizeof(int);		// packSize
	pInput += sizeof(int);		// hRes
	pInput += sizeof(int);		// vRes
	pInput += sizeof(short);	// pixelType

	short iBPP;

	iBPP = *(short *)pInput; iBPP = SwapEndianShort(iBPP); pInput += sizeof(short);

	m_iBPP = iBPP;

	pInput += sizeof(short);	// cmpCount
	pInput += sizeof(short);	// cmpSize
	pInput += sizeof(int);		// planeBytes
	pInput += sizeof(int);		// pmTable
	pInput += sizeof(int);		// pmReserved

	// Load mask BitMap

	short iMaskRowBytes;

	pInput += sizeof(int);			// baseAddr
	iMaskRowBytes = *(short *)pInput; iMaskRowBytes = SwapEndianShort(iMaskRowBytes); pInput += sizeof(short);
	pInput += 4 * sizeof(short);	// bounds

	// Load icon BitMap

	short iIcon1BitRowBytes;

	pInput += sizeof(int);			// baseAddr
	iIcon1BitRowBytes = *(short *)pInput; iIcon1BitRowBytes = SwapEndianShort(iIcon1BitRowBytes); pInput += sizeof(short);
	pInput += 4 * sizeof(short);	// bounds

	// Load icon data

	pInput += sizeof(int);

	// Load mask

	m_vMaskData.resize(m_iWidth * m_iHeight * 3 + 24);

	int i, j;

	UCHAR ucPixel;

	int iCurIndex = 0;

	int iAlignment = iMaskRowBytes - (m_iWidth + 7) / 8;

	for(i = 0; i < m_iHeight; i++)
	{
		iCurIndex = i * m_iWidth * 3;

		for(j = 0; j < (m_iWidth + 7) / 8; j++)
		{
			ucPixel = (UCHAR)*pInput; pInput++;

			m_vMaskData[iCurIndex] = m_vMaskData[iCurIndex + 1] = m_vMaskData[iCurIndex + 2] = ((ucPixel & 0x80) >> 7) * 0xFF; iCurIndex += 3;
			m_vMaskData[iCurIndex] = m_vMaskData[iCurIndex + 1] = m_vMaskData[iCurIndex + 2] = ((ucPixel & 0x40) >> 6) * 0xFF; iCurIndex += 3;
			m_vMaskData[iCurIndex] = m_vMaskData[iCurIndex + 1] = m_vMaskData[iCurIndex + 2] = ((ucPixel & 0x20) >> 5) * 0xFF; iCurIndex += 3;
			m_vMaskData[iCurIndex] = m_vMaskData[iCurIndex + 1] = m_vMaskData[iCurIndex + 2] = ((ucPixel & 0x10) >> 4) * 0xFF; iCurIndex += 3;
			m_vMaskData[iCurIndex] = m_vMaskData[iCurIndex + 1] = m_vMaskData[iCurIndex + 2] = ((ucPixel & 0x08) >> 3) * 0xFF; iCurIndex += 3;
			m_vMaskData[iCurIndex] = m_vMaskData[iCurIndex + 1] = m_vMaskData[iCurIndex + 2] = ((ucPixel & 0x04) >> 2) * 0xFF; iCurIndex += 3;
			m_vMaskData[iCurIndex] = m_vMaskData[iCurIndex + 1] = m_vMaskData[iCurIndex + 2] = ((ucPixel & 0x02) >> 1) * 0xFF; iCurIndex += 3;
			m_vMaskData[iCurIndex] = m_vMaskData[iCurIndex + 1] = m_vMaskData[iCurIndex + 2] =  (ucPixel & 0x01)       * 0xFF; iCurIndex += 3;
		}

		pInput += iAlignment;
	}

	// Load 1-bit data

	pInput += m_iHeight * iIcon1BitRowBytes;

	// Load color table

	pInput += sizeof(int);		// ctSeed
	pInput += sizeof(short);	// ctFlags

	short iNumColors;

	iNumColors = *(short *)pInput; m_iNumColors = SwapEndianShort(iNumColors) + 1; pInput += sizeof(short);

	m_vColorTable.resize(256);

	memset(&m_vColorTable[0], 0, m_vColorTable.size() * sizeof(int));

	short iIndex;
	short iRed;
	short iGreen;
	short iBlue;

	for(i = 0; i < m_iNumColors; i++)
	{
		iIndex = *(short *)pInput; iIndex = SwapEndianShort(iIndex); pInput += sizeof(short);

		iRed   = *(short *)pInput; iRed   = SwapEndianShort(iRed);   pInput += sizeof(short);
		iGreen = *(short *)pInput; iGreen = SwapEndianShort(iGreen); pInput += sizeof(short);
		iBlue  = *(short *)pInput; iBlue  = SwapEndianShort(iBlue);  pInput += sizeof(short);

		m_vColorTable[iIndex] = 0x80000000 | ((iRed >> 8) & 0xFF) | (((iGreen >> 8) & 0xFF) << 8) | (((iBlue >> 8) & 0xFF) << 16);
	}

	// Load icon data

	m_vIconData.resize(m_iWidth * m_iHeight * 3 + 24);

	iCurIndex = 0;

	if(m_iBPP == 1)
	{
		iAlignment = iRowBytes - (m_iWidth + 7) / 8;

		for(i = 0; i < m_iHeight; i++)
		{
			iCurIndex = i * m_iWidth * 3;

			for(j = 0; j < (m_iWidth + 7) / 8; j++)
			{
				ucPixel = (UCHAR)*pInput; pInput++;

				m_vIconData[iCurIndex]      = (UCHAR)((m_vColorTable[ ucPixel         >> 7] & 0x00FF0000) >> 16);
				m_vIconData[iCurIndex + 1]  = (UCHAR)((m_vColorTable[ ucPixel         >> 7] & 0x0000FF00) >> 8);
				m_vIconData[iCurIndex + 2]  = (UCHAR) (m_vColorTable[ ucPixel         >> 7] & 0x000000FF);
				m_vIconData[iCurIndex + 3]  = (UCHAR)((m_vColorTable[(ucPixel & 0x40) >> 6] & 0x00FF0000) >> 16);
				m_vIconData[iCurIndex + 4]  = (UCHAR)((m_vColorTable[(ucPixel & 0x40) >> 6] & 0x0000FF00) >> 8);
				m_vIconData[iCurIndex + 5]  = (UCHAR) (m_vColorTable[(ucPixel & 0x40) >> 6] & 0x000000FF);
				m_vIconData[iCurIndex + 6]  = (UCHAR)((m_vColorTable[(ucPixel & 0x20) >> 5] & 0x00FF0000) >> 16);
				m_vIconData[iCurIndex + 7]  = (UCHAR)((m_vColorTable[(ucPixel & 0x20) >> 5] & 0x0000FF00) >> 8);
				m_vIconData[iCurIndex + 8]  = (UCHAR) (m_vColorTable[(ucPixel & 0x20) >> 5] & 0x000000FF);
				m_vIconData[iCurIndex + 9]  = (UCHAR)((m_vColorTable[(ucPixel & 0x10) >> 4] & 0x00FF0000) >> 16);
				m_vIconData[iCurIndex + 10] = (UCHAR)((m_vColorTable[(ucPixel & 0x10) >> 4] & 0x0000FF00) >> 8);
				m_vIconData[iCurIndex + 11] = (UCHAR) (m_vColorTable[(ucPixel & 0x10) >> 4] & 0x000000FF);
				m_vIconData[iCurIndex + 12] = (UCHAR)((m_vColorTable[(ucPixel & 0x08) >> 3] & 0x00FF0000) >> 16);
				m_vIconData[iCurIndex + 13] = (UCHAR)((m_vColorTable[(ucPixel & 0x08) >> 3] & 0x0000FF00) >> 8);
				m_vIconData[iCurIndex + 14] = (UCHAR) (m_vColorTable[(ucPixel & 0x08) >> 3] & 0x000000FF);
				m_vIconData[iCurIndex + 15] = (UCHAR)((m_vColorTable[(ucPixel & 0x04) >> 2] & 0x00FF0000) >> 16);
				m_vIconData[iCurIndex + 16] = (UCHAR)((m_vColorTable[(ucPixel & 0x04) >> 2] & 0x0000FF00) >> 8);
				m_vIconData[iCurIndex + 17] = (UCHAR) (m_vColorTable[(ucPixel & 0x04) >> 2] & 0x000000FF);
				m_vIconData[iCurIndex + 18] = (UCHAR)((m_vColorTable[(ucPixel & 0x02) >> 1] & 0x00FF0000) >> 16);
				m_vIconData[iCurIndex + 19] = (UCHAR)((m_vColorTable[(ucPixel & 0x02) >> 1] & 0x0000FF00) >> 8);
				m_vIconData[iCurIndex + 20] = (UCHAR) (m_vColorTable[(ucPixel & 0x02) >> 1] & 0x000000FF);
				m_vIconData[iCurIndex + 21] = (UCHAR)((m_vColorTable[(ucPixel & 0x01)     ] & 0x00FF0000) >> 16);
				m_vIconData[iCurIndex + 22] = (UCHAR)((m_vColorTable[ ucPixel & 0x01      ] & 0x0000FF00) >> 8);
				m_vIconData[iCurIndex + 23] = (UCHAR) (m_vColorTable[ ucPixel & 0x01      ] & 0x000000FF);

				iCurIndex += 24;
			}

			pInput += iAlignment;
		}
	}
	else if(m_iBPP == 2)
	{
		iAlignment = iRowBytes - (m_iWidth + 3) / 4;

		for(i = 0; i < m_iHeight; i++)
		{
			iCurIndex = i * m_iWidth * 3;

			for(j = 0; j < (m_iWidth + 3) / 4; j++)
			{
				ucPixel = (UCHAR)*pInput; pInput++;

				m_vIconData[iCurIndex]      = (UCHAR)((m_vColorTable[ ucPixel         >> 6] & 0x00FF0000) >> 16);
				m_vIconData[iCurIndex + 1]  = (UCHAR)((m_vColorTable[ ucPixel         >> 6] & 0x0000FF00) >> 8);
				m_vIconData[iCurIndex + 2]  = (UCHAR) (m_vColorTable[ ucPixel         >> 6] & 0x000000FF);
				m_vIconData[iCurIndex + 3]  = (UCHAR)((m_vColorTable[(ucPixel & 0x30) >> 4] & 0x00FF0000) >> 16);
				m_vIconData[iCurIndex + 4]  = (UCHAR)((m_vColorTable[(ucPixel & 0x30) >> 4] & 0x0000FF00) >> 8);
				m_vIconData[iCurIndex + 5]  = (UCHAR) (m_vColorTable[(ucPixel & 0x30) >> 4] & 0x000000FF);
				m_vIconData[iCurIndex + 6]  = (UCHAR)((m_vColorTable[(ucPixel & 0x0C) >> 2] & 0x00FF0000) >> 16);
				m_vIconData[iCurIndex + 7]  = (UCHAR)((m_vColorTable[(ucPixel & 0x0C) >> 2] & 0x0000FF00) >> 8);
				m_vIconData[iCurIndex + 8]  = (UCHAR) (m_vColorTable[(ucPixel & 0x0C) >> 2] & 0x000000FF);
				m_vIconData[iCurIndex + 9]  = (UCHAR)((m_vColorTable[ ucPixel & 0x03      ] & 0x00FF0000) >> 16);
				m_vIconData[iCurIndex + 10] = (UCHAR)((m_vColorTable[ ucPixel & 0x03      ] & 0x0000FF00) >> 8);
				m_vIconData[iCurIndex + 11] = (UCHAR) (m_vColorTable[ ucPixel & 0x03      ] & 0x000000FF);

				iCurIndex += 12;
			}

			pInput += iAlignment;
		}
	}
	else if(m_iBPP == 4)
	{
		iAlignment = iRowBytes - (m_iWidth + 1) / 2;

		for(i = 0; i < m_iHeight; i++)
		{
			iCurIndex = i * m_iWidth * 3;

			for(j = 0; j < (m_iWidth + 1) / 2; j++)
			{
				ucPixel = (UCHAR)*pInput; pInput++;

				m_vIconData[iCurIndex]     = (UCHAR)((m_vColorTable[ucPixel >>   4] & 0x00FF0000) >> 16);
				m_vIconData[iCurIndex + 1] = (UCHAR)((m_vColorTable[ucPixel >>   4] & 0x0000FF00) >> 8);
				m_vIconData[iCurIndex + 2] = (UCHAR) (m_vColorTable[ucPixel >>   4] & 0x000000FF);
				m_vIconData[iCurIndex + 3] = (UCHAR)((m_vColorTable[ucPixel & 0x0F] & 0x00FF0000) >> 16);
				m_vIconData[iCurIndex + 4] = (UCHAR)((m_vColorTable[ucPixel & 0x0F] & 0x0000FF00) >> 8);
				m_vIconData[iCurIndex + 5] = (UCHAR) (m_vColorTable[ucPixel & 0x0F] & 0x000000FF);

				iCurIndex += 6;
			}

			pInput += iAlignment;
		}
	}
	else if(m_iBPP == 8)
	{
		iAlignment = iRowBytes - m_iWidth;

		for(i = 0; i < m_iHeight; i++)
		{
			iCurIndex = i * m_iWidth * 3;

			for(j = 0; j < m_iWidth; j++)
			{
				ucPixel = (UCHAR)*pInput; pInput++;

				m_vIconData[iCurIndex]     = (UCHAR)((m_vColorTable[ucPixel] & 0x00FF0000) >> 16);
				m_vIconData[iCurIndex + 1] = (UCHAR)((m_vColorTable[ucPixel] & 0x0000FF00) >> 8);
				m_vIconData[iCurIndex + 2] = (UCHAR) (m_vColorTable[ucPixel] & 0x000000FF);

				iCurIndex += 3;
			}

			pInput += iAlignment;
		}
	}
	else
	{
		if(pEditor->PrefGenerateLogFile())
			*pLog << "Error: Invalid number of bits per pixel (" << m_iBPP << ") found in color icon resource!" << CErrorLog::endl;

		m_iWidth  = 0;
		m_iHeight = 0;
		m_iBPP    = 0;

		m_vIconData.clear();
		m_vMaskData.clear();
	}

	return 1;
}

int CCicnResource::SaveToTextEx(std::ostream & output, std::string & szFilePath, std::string & szFilename1, std::string & szFilename2, int iParam)
{
	output << m_iWidth  << '\t'
		   << m_iHeight << '\t'
		   << m_iBPP    << '\t';

	PrintTextField(output, szFilename1.c_str(), '\t');
	PrintTextField(output, szFilename2.c_str(), '\t');

	std::string szIconFilename, szMaskFilename;

	szIconFilename = szFilePath + szFilename1;
	szMaskFilename = szFilePath + szFilename2;

	FileExport(1, szIconFilename.c_str(), 0);
	FileExport(0, szMaskFilename.c_str(), 0);

	return 1;
}

int CCicnResource::LoadFromTextEx(std::istream & input, std::string & szFilePath)
{
	int iWidth;
	int iHeight;
	int iBPP;

	input >> iWidth
		  >> iHeight
		  >> iBPP;

	input.ignore(1);

	char szIconFilename[256];
	char szMaskFilename[256];

	strcpy(szIconFilename, szFilePath.c_str());
	strcpy(szMaskFilename, szFilePath.c_str());

	ReadTextField(input, szIconFilename + strlen(szIconFilename), 256 - strlen(szIconFilename));
	ReadTextField(input, szMaskFilename + strlen(szMaskFilename), 256 - strlen(szMaskFilename));

	FileImport(1, szIconFilename, 0);
	FileImport(0, szMaskFilename, 0);

	return 1;
}

UCHAR CCicnResource::FindColor(UCHAR ucRed, UCHAR ucGreen, UCHAR ucBlue)
{
	if((m_vColorTable.size() == 0) || (m_iNumColors == 0))
		return 0;

	int i;

	UCHAR ucR, ucG, ucB;

	for(i = 0; i < m_vColorTable.size(); i++)
	{
		if(m_vColorTable[i] & 0x80000000)
		{
			ucR = (UCHAR) (m_vColorTable[i] & 0x000000FF);
			ucG = (UCHAR)((m_vColorTable[i] & 0x0000FF00) >> 8);
			ucB = (UCHAR)((m_vColorTable[i] & 0x00FF0000) >> 16);

			if((ucRed == ucR) && (ucGreen == ucG) && (ucBlue == ucB))
				return (UCHAR)i;
		}
	}

	return 0;
}

int CCicnResource::MakeBitmap(HWND hwnd, int iIsIcon)
{
	if(((m_iWidth == 0) || (m_iHeight == 0)) && ((m_iTempWidth == 0) || (m_iTempHeight == 0)))
		return 0;

	int iWidth;
	int iHeight;
	int iBPP;

	UCHAR *pSource;

	if(m_iTempWidth == 0)
	{
		iWidth  = m_iWidth;
		iHeight = m_iHeight;
		iBPP    = m_iBPP;

		if(iIsIcon)
			pSource = &m_vIconData[0];
		else
			pSource = &m_vMaskData[0];
	}
	else
	{
		iWidth  = m_iTempWidth;
		iHeight = m_iTempHeight;
		iBPP    = m_iTempBPP;

		if(iIsIcon)
			pSource = &m_vTempIconData[0];
		else
			pSource = &m_vTempMaskData[0];
	}

	if(pSource == NULL)
		return 0;

	HDC hdcDialog;
	HDC hdcMemory;
	HBITMAP hbmDDB;

	BITMAPINFO bmpInfo;

	hdcDialog = GetDC(hwnd);
	hdcMemory = CreateCompatibleDC(hdcDialog);
	hbmDDB    = CreateCompatibleBitmap(hdcDialog, iWidth, iHeight);

	SelectObject(hdcMemory, hbmDDB);

	int iBMPWidth  = iWidth;
	int iBMPHeight = iHeight;

	memset(&bmpInfo, 0, sizeof(BITMAPINFO));

	bmpInfo.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth       = iBMPWidth;
	bmpInfo.bmiHeader.biHeight      = iBMPHeight;
	bmpInfo.bmiHeader.biPlanes      = 1;
	bmpInfo.bmiHeader.biBitCount    = 24;
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	bmpInfo.bmiHeader.biSizeImage   = bmpInfo.bmiHeader.biWidth * bmpInfo.bmiHeader.biHeight * 3;

	iBMPWidth *= 3;
	iBMPWidth += (4 - (iBMPWidth & 3)) & 3;

	UCHAR *ppBits = NULL;

	if(iIsIcon)
		m_hbmIcon = CreateDIBSection(hdcMemory, &bmpInfo, DIB_RGB_COLORS, (void **)&ppBits, NULL, 0);
	else
		m_hbmMask = CreateDIBSection(hdcMemory, &bmpInfo, DIB_RGB_COLORS, (void **)&ppBits, NULL, 0);

	DeleteDC(hdcMemory);

	if(iIsIcon)
	{
		if(m_hbmIcon == NULL)
			return 0;
	}
	else
	{
		if(m_hbmMask == NULL)
			return 0;
	}

	int i;

	for(i = 0; i < iHeight; i++)
		memcpy(ppBits + (iBMPHeight - 1 - i) * iBMPWidth, pSource + i * iWidth * 3, iWidth * 3);

	if(iIsIcon)
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_CICN_PICT1), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hbmIcon);
	else
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_CICN_PICT2), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hbmMask);

	return 1;
}

int CCicnResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "cicn ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_CICN_EDIT1, CCONTROL_TYPE_INT, IDS_STRING1040);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_CICN_EDIT2, CCONTROL_TYPE_STR256, IDS_STRING1041);
	m_controls[1].SetString(m_szName);

	m_iTempWidth  = 0;
	m_iTempHeight = 0;
	m_iTempBPP    = 0;
	m_iTempNumColors = 0;

	m_vTempIconData.clear();
	m_vTempMaskData.clear();
	m_vTempColorTable.clear();

	std::string szBuffer;

	szBuffer = "Width: ";
	szBuffer += ToString(m_iWidth);

	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_CICN_TEXT5), szBuffer.c_str());

	szBuffer = "Height: ";
	szBuffer += ToString(m_iHeight);

	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_CICN_TEXT6), szBuffer.c_str());

	szBuffer = "BPP: ";
	szBuffer += ToString(m_iBPP);

	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_CICN_TEXT7), szBuffer.c_str());

	MakeBitmap(hwnd, 1);
	MakeBitmap(hwnd, 0);

	return 1;
}

int CCicnResource::CloseAndSave(void)
{
	std::string szError;

	if(CEditor::GetCurrentEditor()->IsUniqueResourceID(this, m_controls[0].GetInt()) == 0)
	{
		szError = ToString(m_controls[0].GetInt());
		szError += " is not a unique ";
		szError += g_szResourceTypes[GetType()];
		szError += " ID.  Please enter a unique ID.";

		MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}
	else if((m_controls[0].GetInt() < 128) || (m_controls[0].GetInt() > 32767))
	{
		szError = ToString(m_controls[0].GetInt());
		szError += " is not a valid ID.  Please enter an ID between 128 and 32767 inclusive.";

		MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	int iIDOrNameChanged = 0;

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[1].GetString()) != 0))
		iIDOrNameChanged = 1;

	m_iID = m_controls[0].GetInt();

	strcpy(m_szName, m_controls[1].GetString());

	int i;

	for(i = 0; i < NUM_CICN_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	if(m_iTempWidth != 0)
	{
		m_iWidth  = m_iTempWidth;
		m_iHeight = m_iTempHeight;

		if(m_iTempBPP != 0)
			m_iBPP = m_iTempBPP;

		if(m_iTempNumColors != 0)
			m_iNumColors = m_iTempNumColors;

		if(m_vTempIconData.size() > 0)
		{
			m_vIconData.resize(m_vTempIconData.size());

			memcpy(&m_vIconData[0], &m_vTempIconData[0], m_vTempIconData.size() * sizeof(UCHAR));
		}

		if(m_vTempMaskData.size() > 0)
		{
			m_vMaskData.resize(m_vTempMaskData.size());

			memcpy(&m_vMaskData[0], &m_vTempMaskData[0], m_vTempMaskData.size() * sizeof(UCHAR));
		}

		if(m_vTempColorTable.size() > 0)
		{
			m_vColorTable.resize(m_vTempColorTable.size());

			memcpy(&m_vColorTable[0], &m_vTempColorTable[0], m_vTempColorTable.size() * sizeof(UINT));
		}

		m_iTempWidth  = 0;
		m_iTempHeight = 0;
		m_iTempBPP    = 0;
		m_iTempNumColors = 0;

		m_vTempIconData.clear();
		m_vTempMaskData.clear();
		m_vTempColorTable.clear();

		CEditor::GetCurrentEditor()->SetDirty();
	}

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CCicnResource::CloseAndDontSave(void)
{
	m_iTempWidth  = 0;
	m_iTempHeight = 0;
	m_iTempBPP    = 0;
	m_iTempNumColors = 0;

	m_vTempIconData.clear();
	m_vTempMaskData.clear();
	m_vTempColorTable.clear();

	int i;

	for(i = 0; i < NUM_CICN_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

int CCicnResource::FileImport(int iIsIcon, const char *szFilename, int iShowErrorMessages)
{
	CEditor *pEditor = CEditor::GetCurrentEditor();
	CErrorLog *pLog  = CErrorLog::GetCurrentErrorLog();

	char szFilename2[MAX_PATH];

	if(szFilename == NULL)
	{
		strcpy(szFilename2, "");

		OPENFILENAME ofn;

		memset(&ofn, 0, sizeof(OPENFILENAME));

		ofn.lStructSize   = sizeof(OPENFILENAME);
		ofn.nMaxFile      = MAX_PATH;
		ofn.nMaxFileTitle = MAX_PATH;
		ofn.lpstrTitle    = "Import Color Icon Resource";
		ofn.lpstrFilter   = "Palleted Bitmaps (*.bmp)\0*.bmp\0";
		ofn.nFilterIndex  = 1;
		ofn.lpstrDefExt   = "bmp";
		ofn.Flags         = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
		ofn.hwndOwner     = m_pWindow->GetHWND();
		ofn.lpstrFile     = szFilename2;

		if(GetOpenFileName(&ofn) == 0)
			return 0;
	}
	else
	{
		strcpy(szFilename2, szFilename);
	}

	std::ifstream filein;

	filein.open(szFilename2, std::ios::in | std::ios::binary);

	if(filein.is_open() == 0)
	{
		if(pEditor->PrefGenerateLogFile())
			*pLog << "Error: Unable to open bitmap file \"" << szFilename2 << "\"!" << CErrorLog::endl;

		std::string szError = "Unable to load file \"";

		szError += szFilename2;
		szError += "\"!";

		if(pEditor->PrefGenerateLogFile())
			szError += "  Consult log.txt for details.";

		if(iShowErrorMessages)
			MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	// Load bitmap header

	BITMAPFILEHEADER bmfh;
	BITMAPINFO       bmi;

	filein.read((char *)&bmfh, sizeof(BITMAPFILEHEADER));
	filein.read((char *)&bmi,  sizeof(BITMAPINFO));

	int iBPP = bmi.bmiHeader.biBitCount;

	if(((iIsIcon) && (iBPP != 1) && (iBPP != 4) && (iBPP != 8)) || ((!iIsIcon) && (iBPP != 1)))
	{
		if(pEditor->PrefGenerateLogFile())
		{
			if(iIsIcon)
				*pLog << "Error: Invalid number of bits per pixel (" << iBPP << ") for color icon in file \"" << szFilename2 << "\"!" << CErrorLog::endl;
			else
				*pLog << "Error: Attempted to load non-monochrome color icon mask (" << iBPP << " BPP) in file \"" << szFilename2 << "\"!" << CErrorLog::endl;
		}

		std::string szError = "Invalid number of bits per pixel (";

		szError += ToString(iBPP);
		szError += ") in file \"";
		szError += szFilename;
		szError += "\"!";

		if(pEditor->PrefGenerateLogFile())
			szError += "  Consult log.txt for details.";

		if(iShowErrorMessages)
			MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	if(((m_iWidth != 0) && (bmi.bmiHeader.biWidth != m_iWidth)) || ((m_iHeight != 0) && (bmi.bmiHeader.biHeight != m_iHeight)) || ((m_iTempWidth != 0) && (bmi.bmiHeader.biWidth != m_iTempWidth)) || ((m_iTempHeight != 0) && (bmi.bmiHeader.biHeight != m_iTempHeight)))
	{
		if(pEditor->PrefGenerateLogFile())
			*pLog << "Error: Dimensions of bitmap are different from current color icon dimensions in file \"" << szFilename2 << "\"!" << CErrorLog::endl;

		std::string szError = "Invalid dimensions in file \"";

		szError += szFilename;
		szError += "\"!";

		if(pEditor->PrefGenerateLogFile())
			szError += "  Consult log.txt for details.";

		if(iShowErrorMessages)
			MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	m_iTempWidth  = bmi.bmiHeader.biWidth;
	m_iTempHeight = bmi.bmiHeader.biHeight;

	int i, j;

	if(iIsIcon)
	{
		m_iTempBPP = iBPP;

		m_iTempNumColors = 1 << iBPP;

		m_vTempIconData.resize(m_iTempWidth * m_iTempHeight * 3);

		if((m_vMaskData.size() == 0) && (m_vTempMaskData.size() == 0))
		{
			m_vTempMaskData.resize(m_iTempWidth * m_iTempHeight * 3);

			memset(&m_vTempMaskData[0], 0x00, m_vTempMaskData.size() * sizeof(UCHAR));
		}
	}
	else
	{
		if(m_iTempBPP == 0)
			m_iTempBPP = m_iBPP;

		if((m_vIconData.size() == 0) && (m_vTempIconData.size() == 0))
		{
			m_vTempIconData.resize(m_iTempWidth * m_iTempHeight * 3);

			memset(&m_vTempIconData[0], 0x00, m_vTempIconData.size() * sizeof(UCHAR));
		}

		if((m_vColorTable.size() == 0) && (m_vTempColorTable.size() == 0))
		{
			m_vTempColorTable.resize(256);

			m_vTempColorTable[0] = 0x80000000;

			for(i = 1; i < 256; i++)
				m_vTempColorTable[i] = 0x00000000;
		}

		m_vTempMaskData.resize(m_iTempWidth * m_iTempHeight * 3);
	}

	// Load pallette

	RGBQUAD rgbQuad;

	UCHAR ucRed, ucGreen, ucBlue;

	if(iIsIcon)
	{
		m_vTempColorTable.resize(256);

		memset(&m_vTempColorTable[0], 0x00, m_vTempColorTable.size() * sizeof(UINT));

		ucRed   = bmi.bmiColors[0].rgbRed;
		ucGreen = bmi.bmiColors[0].rgbGreen;
		ucBlue  = bmi.bmiColors[0].rgbBlue;

		m_vTempColorTable[0] = 0x80000000 | ((int)ucRed) | ((int)ucGreen << 8) | ((int)ucBlue << 16);

		if(iBPP == 1)
		{
			filein.read((char *)&rgbQuad, sizeof(RGBQUAD));

			ucRed   = rgbQuad.rgbRed;
			ucGreen = rgbQuad.rgbGreen;
			ucBlue  = rgbQuad.rgbBlue;

			m_vTempColorTable[1] = 0x80000000 | ((int)ucRed) | ((int)ucGreen << 8) | ((int)ucBlue << 16);
		}
		else if(iBPP == 4)
		{
			for(i = 1; i < 16; i++)
			{
				filein.read((char *)&rgbQuad, sizeof(RGBQUAD));

				ucRed   = rgbQuad.rgbRed;
				ucGreen = rgbQuad.rgbGreen;
				ucBlue  = rgbQuad.rgbBlue;

				m_vTempColorTable[i] = 0x80000000 | ((int)ucRed) | ((int)ucGreen << 8) | ((int)ucBlue << 16);
			}
		}
		else if(iBPP == 8)
		{
			for(i = 1; i < 256; i++)
			{
				filein.read((char *)&rgbQuad, sizeof(RGBQUAD));

				ucRed   = rgbQuad.rgbRed;
				ucGreen = rgbQuad.rgbGreen;
				ucBlue  = rgbQuad.rgbBlue;

				m_vTempColorTable[i] = 0x80000000 | ((int)ucRed) | ((int)ucGreen << 8) | ((int)ucBlue << 16);
			}
		}
	}
	else
	{
		filein.seekg(sizeof(RGBQUAD), std::ios::cur);
	}

	// Load data

	int iAlignment;

	UCHAR ucPixel = 0x00;

	int iIndex1;
	int iIndex2;

	if(iIsIcon)
	{
		if(m_iTempBPP == 1)
		{
			iAlignment = (4 - (((m_iTempWidth + 7) / 8) & 3)) & 3;

			for(i = 0; i < m_iTempHeight; i++)
			{
				for(j = 0; j < m_iTempWidth; j++)
				{
					if((j & 7) == 0)
						filein.read((char *)&ucPixel, sizeof(UCHAR));

					iIndex1 = ((m_iTempHeight - 1 - i) * m_iTempWidth + j) * 3;
					iIndex2 = (ucPixel >> (7 - (j & 7))) & 0x01;

					m_vTempIconData[iIndex1 + 2] = (UCHAR) (m_vTempColorTable[iIndex2]        & 0xFF);
					m_vTempIconData[iIndex1 + 1] = (UCHAR)((m_vTempColorTable[iIndex2] >> 8)  & 0xFF);
					m_vTempIconData[iIndex1]     = (UCHAR)((m_vTempColorTable[iIndex2] >> 16) & 0xFF);
				}

				if(iAlignment > 0)
					filein.seekg(iAlignment, std::ios::cur);
			}
		}
		else if(m_iTempBPP == 4)
		{
			iAlignment = (4 - (((m_iTempWidth + 1) / 2) & 3)) & 3;

			for(i = 0; i < m_iTempHeight; i++)
			{
				for(j = 0; j < m_iTempWidth; j++)
				{
					if((j & 1) == 0)
						filein.read((char *)&ucPixel, sizeof(UCHAR));

					iIndex1 = ((m_iTempHeight - 1 - i) * m_iTempWidth + j) * 3;
					iIndex2 = (ucPixel >> ((1 - (j & 1)) << 2)) & 0x0F;

					m_vTempIconData[iIndex1 + 2] = (UCHAR) (m_vTempColorTable[iIndex2]        & 0xFF);
					m_vTempIconData[iIndex1 + 1] = (UCHAR)((m_vTempColorTable[iIndex2] >> 8)  & 0xFF);
					m_vTempIconData[iIndex1]     = (UCHAR)((m_vTempColorTable[iIndex2] >> 16) & 0xFF);
				}

				if(iAlignment > 0)
					filein.seekg(iAlignment, std::ios::cur);
			}
		}
		else if(m_iTempBPP == 8)
		{
			iAlignment = (4 - (m_iTempWidth & 3)) & 3;

			for(i = 0; i < m_iTempHeight; i++)
			{
				for(j = 0; j < m_iTempWidth; j++)
				{
					filein.read((char *)&ucPixel, sizeof(UCHAR));

					iIndex1 = ((m_iTempHeight - 1 - i) * m_iTempWidth + j) * 3;

					m_vTempIconData[iIndex1 + 2] = (UCHAR) (m_vTempColorTable[ucPixel]        & 0xFF);
					m_vTempIconData[iIndex1 + 1] = (UCHAR)((m_vTempColorTable[ucPixel] >> 8)  & 0xFF);
					m_vTempIconData[iIndex1]     = (UCHAR)((m_vTempColorTable[ucPixel] >> 16) & 0xFF);
				}

				if(iAlignment > 0)
					filein.seekg(iAlignment, std::ios::cur);
			}
		}
	}
	else
	{
		iAlignment = (4 - (((m_iTempWidth + 7) / 8) & 3)) & 3;

		for(i = 0; i < m_iTempHeight; i++)
		{
			for(j = 0; j < m_iTempWidth; j++)
			{
				if((j & 7) == 0)
					filein.read((char *)&ucPixel, sizeof(UCHAR));

				if(ucPixel & (1 << (7 - (j & 7))))
				{
					iIndex1 = ((m_iTempHeight - 1 - i) * m_iTempWidth + j) * 3;

					m_vTempMaskData[iIndex1] = m_vTempMaskData[iIndex1 + 1] = m_vTempMaskData[iIndex1 + 2] = 0xFF;
				}
			}

			if(iAlignment > 0)
				filein.seekg(iAlignment, std::ios::cur);
		}
	}

	filein.close();

	HWND hwnd;

	std::string szBuffer;

	if(m_pWindow != NULL)
	{
		hwnd = m_pWindow->GetHWND();

		szBuffer = "Width: ";
		szBuffer += ToString(m_iTempWidth);

		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_CICN_TEXT5), szBuffer.c_str());

		szBuffer = "Height: ";
		szBuffer += ToString(m_iTempHeight);

		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_CICN_TEXT6), szBuffer.c_str());

		if(m_iTempBPP == 0)
			m_iTempBPP = m_iBPP;

		szBuffer = "BPP: ";
		szBuffer += ToString(m_iTempBPP);

		Static_SetText(GetDlgItem(hwnd, IDC_EDIT_CICN_TEXT7), szBuffer.c_str());

		MakeBitmap(hwnd, 1);
		MakeBitmap(hwnd, 0);
	}
	else
	{
		m_iWidth  = m_iTempWidth;
		m_iHeight = m_iTempHeight;

		if(m_iTempBPP != 0)
			m_iBPP = m_iTempBPP;

		if(m_iTempNumColors != 0)
			m_iNumColors = m_iTempNumColors;

		if(m_vTempIconData.size() > 0)
		{
			m_vIconData.resize(m_vTempIconData.size());

			memcpy(&m_vIconData[0], &m_vTempIconData[0], m_vTempIconData.size() * sizeof(UCHAR));
		}

		if(m_vTempMaskData.size() > 0)
		{
			m_vMaskData.resize(m_vTempMaskData.size());

			memcpy(&m_vMaskData[0], &m_vTempMaskData[0], m_vTempMaskData.size() * sizeof(UCHAR));
		}

		if(m_vTempColorTable.size() > 0)
		{
			m_vColorTable.resize(m_vTempColorTable.size());

			memcpy(&m_vColorTable[0], &m_vTempColorTable[0], m_vTempColorTable.size() * sizeof(UINT));
		}

		m_iTempWidth     = 0;
		m_iTempHeight    = 0;
		m_iTempBPP       = 0;
		m_iTempNumColors = 0;

		m_vTempIconData.clear();
		m_vTempMaskData.clear();
		m_vTempColorTable.clear();
	}

	return 1;
}

int CCicnResource::FileExport(int iIsIcon, const char *szFilename, int iShowErrorMessages)
{
	if(((m_iWidth == 0) || (m_iHeight == 0) || (m_iBPP == 0)) && ((m_iTempWidth == 0) || (m_iTempHeight == 0) || (m_iTempBPP == 0)))
		return 0;

	CEditor *pEditor = CEditor::GetCurrentEditor();
	CErrorLog *pLog  = CErrorLog::GetCurrentErrorLog();

	char szFilename2[MAX_PATH];

	if(szFilename == NULL)
	{
		strcpy(szFilename2, "");

		OPENFILENAME ofn;

		memset(&ofn, 0, sizeof(OPENFILENAME));

		ofn.lStructSize   = sizeof(OPENFILENAME);
		ofn.nMaxFile      = MAX_PATH;
		ofn.nMaxFileTitle = MAX_PATH;
		ofn.lpstrTitle    = "Export Color Icon Resource";
		ofn.lpstrFilter   = "Bitmap Files (*.bmp)\0*.bmp\0";
		ofn.nFilterIndex  = 1;
		ofn.lpstrDefExt   = "bmp";
		ofn.Flags         = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
		ofn.hwndOwner     = m_pWindow->GetHWND();
		ofn.lpstrFile     = szFilename2;

		if(GetSaveFileName(&ofn) == 0)
			return 0;
	}
	else
	{
		strcpy(szFilename2, szFilename);
	}

	std::ofstream outfile;

	outfile.open(szFilename2, std::ios::out | std::ios::trunc | std::ios::binary);

	if(outfile.is_open() == 0)
	{
		if(pEditor->PrefGenerateLogFile())
			*pLog << "Error: Unable to open bitmap file \"" << szFilename2 << "\"!" << CErrorLog::endl;

		std::string szError = "Unable to open file \"";

		szError += szFilename2;
		szError += "\"!";

		if(pEditor->PrefGenerateLogFile())
			szError += "  Consult log.txt for details.";

		if(iShowErrorMessages)
			MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	BITMAPFILEHEADER bmfh;
	BITMAPINFO bmi;

	memset(&bmfh, 0, sizeof(BITMAPFILEHEADER));
	memset(&bmi,  0, sizeof(BITMAPINFO));

	int iWidth;
	int iHeight;
	int iBPP;

	int iSizeImage;

	UCHAR *pSource;
	UINT  *pColorTable;

	int iColorTableSize;

	if(m_iTempWidth == 0)
	{
		iWidth  = m_iWidth;
		iHeight = m_iHeight;
		iBPP    = m_iBPP;

		if(iIsIcon)
			pSource = &m_vIconData[0];
		else
			pSource = &m_vMaskData[0];

		pColorTable = &m_vColorTable[0];

		iColorTableSize = m_vColorTable.size();
	}
	else
	{
		iWidth  = m_iTempWidth;
		iHeight = m_iTempHeight;
		iBPP    = m_iTempBPP;

		if(iIsIcon)
			pSource = &m_vTempIconData[0];
		else
			pSource = &m_vTempMaskData[0];

		pColorTable = &m_vTempColorTable[0];

		iColorTableSize = m_vTempColorTable.size();
	}

	if(!iIsIcon)
		iBPP = 1;

	if(iBPP == 2)
		iBPP = 4;

	iSizeImage = (iWidth * iBPP + 7) / 8;
	iSizeImage += (4 - (iSizeImage & 3)) & 3;
	iSizeImage *= m_iHeight;

	bmfh.bfType      = 0x4D42;	// 0x4D42 = "BM"
	bmfh.bfSize      = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO) + iSizeImage;
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits   = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO);

	bmi.bmiHeader.biSize          = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth         = iWidth;
	bmi.bmiHeader.biHeight        = iHeight;
	bmi.bmiHeader.biPlanes        = 1;
	bmi.bmiHeader.biBitCount      = iBPP;
	bmi.bmiHeader.biCompression   = BI_RGB;
	bmi.bmiHeader.biSizeImage     = iSizeImage;
	bmi.bmiHeader.biXPelsPerMeter = 0;
	bmi.bmiHeader.biYPelsPerMeter = 0;
	bmi.bmiHeader.biClrUsed       = 0;
	bmi.bmiHeader.biClrImportant  = 0;

	RGBQUAD rgbColors[256];

	memset(rgbColors, 0, 256 * sizeof(RGBQUAD));

	int i, j;

	UCHAR ucIndex;
	UCHAR ucRed, ucGreen, ucBlue;

	if(iIsIcon)
	{
		for(i = 0; i < iColorTableSize; i++)
		{
			if(pColorTable[i] & 0x80000000)
			{
				ucIndex = (UCHAR)i;

				ucRed   = (UCHAR) (pColorTable[i] & 0x000000FF);
				ucGreen = (UCHAR)((pColorTable[i] & 0x0000FF00) >> 8);
				ucBlue  = (UCHAR)((pColorTable[i] & 0x00FF0000) >> 16);

				rgbColors[ucIndex].rgbRed   = ucRed;
				rgbColors[ucIndex].rgbGreen = ucGreen;
				rgbColors[ucIndex].rgbBlue  = ucBlue;
			}
		}

		if(iBPP == 1)
			bmfh.bfOffBits += 1 * sizeof(RGBQUAD);
		else if(iBPP == 4)
			bmfh.bfOffBits += 15 * sizeof(RGBQUAD);
		else if(iBPP == 8)
			bmfh.bfOffBits += 255 * sizeof(RGBQUAD);
	}
	else
	{
		rgbColors[1].rgbRed   = 0xFF;
		rgbColors[1].rgbGreen = 0xFF;
		rgbColors[1].rgbBlue  = 0xFF;

		bmfh.bfOffBits += 1 * sizeof(RGBQUAD);
	}

	bmi.bmiColors[0] = rgbColors[0];

	outfile.write((char *)&bmfh, sizeof(BITMAPFILEHEADER));
	outfile.write((char *)&bmi,  sizeof(BITMAPINFO));

	if(iIsIcon)
	{
		if(iBPP == 1)
			outfile.write((char *)&rgbColors[1], 1 * sizeof(RGBQUAD));
		else if(iBPP == 4)
			outfile.write((char *)&rgbColors[1], 15 * sizeof(RGBQUAD));
		else if(iBPP == 8)
			outfile.write((char *)&rgbColors[1], 255 * sizeof(RGBQUAD));
	}
	else
	{
		outfile.write((char *)&rgbColors[1], 1 * sizeof(RGBQUAD));
	}

	int iAlignment;

	UCHAR ucPixel;

	char cJunk[4] = {0x00, 0x00, 0x00, 0x00};

	if(iIsIcon)
	{
		if(iBPP == 1)
		{
			iAlignment = (4 - (((iWidth + 7) / 8) & 3)) & 3;

			for(i = 0; i < iHeight; i++)
			{
				ucPixel = 0x00;

				for(j = 0; j < iWidth; j++)
				{
					if(((j & 7) == 0) && (j > 0))
					{
						outfile.write((char *)&ucPixel, sizeof(UCHAR));

						ucPixel = 0x00;
					}

					ucPixel |= (FindColor(pSource[((iHeight - 1 - i) * iWidth + j) * 3 + 2], pSource[((iHeight - 1 - i) * iWidth + j) * 3 + 1], pSource[((iHeight - 1 - i) * iWidth + j) * 3]) & 0x01) << (7 - (j & 7));
				}

				outfile.write((char *)&ucPixel, sizeof(UCHAR));

				if(iAlignment > 0)
					outfile.write(cJunk, iAlignment);
			}
		}
		else if(iBPP == 4)
		{
			iAlignment = (4 - (((iWidth + 1) / 2) & 3)) & 3;

			for(i = 0; i < iHeight; i++)
			{
				ucPixel = 0x00;

				for(j = 0; j < iWidth; j++)
				{
					if(((j & 1) == 0) && (j > 0))
					{
						outfile.write((char *)&ucPixel, sizeof(UCHAR));

						ucPixel = 0x00;
					}

					ucPixel |= (FindColor(pSource[((iHeight - 1 - i) * iWidth + j) * 3 + 2], pSource[((iHeight - 1 - i) * iWidth + j) * 3 + 1], pSource[((iHeight - 1 - i) * iWidth + j) * 3]) & 0x0F) << ((1 - (j & 1)) << 2);
				}

				outfile.write((char *)&ucPixel, sizeof(UCHAR));

				if(iAlignment > 0)
					outfile.write(cJunk, iAlignment);
			}
		}
		else if(iBPP == 8)
		{
			iAlignment = (4 - (iWidth & 3)) & 3;

			for(i = 0; i < iHeight; i++)
			{
				for(j = 0; j < iWidth; j++)
				{
					ucPixel = FindColor(pSource[((iHeight - 1 - i) * iWidth + j) * 3 + 2], pSource[((iHeight - 1 - i) * iWidth + j) * 3 + 1], pSource[((iHeight - 1 - i) * iWidth + j) * 3]);

					outfile.write((char *)&ucPixel, sizeof(UCHAR));
				}

				if(iAlignment > 0)
					outfile.write(cJunk, iAlignment);
			}
		}
	}
	else
	{
		iAlignment = (4 - (((m_iWidth + 7) / 8) & 3)) & 3;

		for(i = 0; i < iHeight; i++)
		{
			ucPixel = 0x00;

			for(j = 0; j < iWidth; j++)
			{
				if(((j & 7) == 0) && (j > 0))
				{
					outfile.write((char *)&ucPixel, sizeof(UCHAR));

					ucPixel = 0x00;
				}

				if(pSource[((iHeight - 1 - i) * iWidth + j) * 3] == 0xFF)
					ucPixel |= 1 << (7 - (j & 7));
			}

			outfile.write((char *)&ucPixel, sizeof(UCHAR));

			if(iAlignment > 0)
				outfile.write(cJunk, iAlignment);
		}
	}

	outfile.close();

	return 1;
}

BOOL CCicnResource::CicnDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CCicnResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CCicnResource *)pWindow->GetExtraData(2);

	int i;

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			pResource->Initialize(hwnd);

			return TRUE;

			break;
		}

		case WM_SYSCOMMAND:
		{
			if(wparam == SC_CLOSE)
			{
				pResource->CloseAndDontSave();

				return TRUE;
			}

			break;
		}

		case WM_COMMAND:
		{
			int iNotifyCode = HIWORD(wparam);
			int iControlID  = LOWORD(wparam);

			if(iControlID == IDC_EDIT_CICN_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_CICN_OK)
			{
				pResource->CloseAndSave();
			}
			else if(iControlID == IDM_CICN_FILE_IMPORTICON)
			{
				pResource->FileImport(1);
			}
			else if(iControlID == IDM_CICN_FILE_IMPORTMASK)
			{
				pResource->FileImport(0);
			}
			else if(iControlID == IDM_CICN_FILE_EXPORTICON)
			{
				pResource->FileExport(1);
			}
			else if(iControlID == IDM_CICN_FILE_EXPORTMASK)
			{
				pResource->FileExport(0);
			}
			else if(iControlID == IDM_CICN_FILE_CLOSEANDSAVE)
			{
				pResource->CloseAndSave();
			}
			else if(iControlID == IDM_CICN_FILE_CLOSEANDDONTSAVE)
			{
				pResource->CloseAndDontSave();
			}
			else
			{
				for(i = 0; i < NUM_CICN_CONTROLS; i++)
				{
					if(iControlID == pResource->m_controls[i].GetControlID())
					{
						pResource->m_controls[i].ProcessMessage(iNotifyCode);

						break;
					}
				}
			}

			return TRUE;

			break;
		}

		default:
		{
			break;
		}
	}

	return FALSE;
}
