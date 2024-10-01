// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CSystResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CSystResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CSystResource::CSystResource(void)
{
	m_iXPosition = 0;
	m_iYPosition = 0;

	int i;

	for(i = 0; i < 16; i++)
	{
		m_iHyperlinks[i] = -1;
		m_iStellars[i]   = -1;
	}

	for(i = 0; i < 8; i++)
	{
		m_iDudeTypes[i]         = -1;
		m_iDudeProbabilities[i] =  0;
	}

	m_iNumShips = 0;

	m_iGovernment = -1;

	m_iMessageBuoy = -1;

	m_iNumAsteroids = 0;
	m_iInterference = 0;

	for(i = 0; i < 8; i++)
	{
		m_iPersons[i]             = -1;
		m_iPersonProbabilities[i] =  0;
	}

	memset(m_szVisibility, 0, 256 * sizeof(char));

	m_iBackgroundColor = 0x00000000;

	m_iMurkiness = 0;

	m_iReinforcementFleet    = -1;
	m_iReinforcementTime     =  0;
	m_iReinforcementInterval =  0;

	m_iAsteroidTypes = 0x0000;
}

CSystResource::~CSystResource(void)
{

}

int CSystResource::GetType(void)
{
	return CNR_TYPE_SYST;
}

int CSystResource::GetSize(void)
{
	return 428;
}

int CSystResource::GetDialogID(void)
{
	return IDD_EDIT_SYST;
}

DLGPROCNOCALLBACK CSystResource::GetDialogProc(void)
{
	return SystDlgProc;
}

int CSystResource::GetNumFields(void)
{
	return NUM_SYST_FIELDS;
}

const std::string * CSystResource::GetFieldNames(void)
{
	return g_szSystFields;
}

int CSystResource::Save(char *pOutput)
{
	SwapEndians();

	*(short *)pOutput = m_iXPosition;              pOutput += sizeof(short);
	*(short *)pOutput = m_iYPosition;              pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[0];          pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[1];          pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[2];          pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[3];          pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[4];          pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[5];          pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[6];          pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[7];          pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[8];          pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[9];          pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[10];         pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[11];         pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[12];         pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[13];         pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[14];         pOutput += sizeof(short);
	*(short *)pOutput = m_iHyperlinks[15];         pOutput += sizeof(short);
	*(short *)pOutput = m_iStellars[0];            pOutput += sizeof(short);
	*(short *)pOutput = m_iStellars[1];            pOutput += sizeof(short);
	*(short *)pOutput = m_iStellars[2];            pOutput += sizeof(short);
	*(short *)pOutput = m_iStellars[3];            pOutput += sizeof(short);
	*(short *)pOutput = m_iStellars[4];            pOutput += sizeof(short);
	*(short *)pOutput = m_iStellars[5];            pOutput += sizeof(short);
	*(short *)pOutput = m_iStellars[6];            pOutput += sizeof(short);
	*(short *)pOutput = m_iStellars[7];            pOutput += sizeof(short);
	*(short *)pOutput = m_iStellars[8];            pOutput += sizeof(short);
	*(short *)pOutput = m_iStellars[9];            pOutput += sizeof(short);
	*(short *)pOutput = m_iStellars[10];           pOutput += sizeof(short);
	*(short *)pOutput = m_iStellars[11];           pOutput += sizeof(short);
	*(short *)pOutput = m_iStellars[12];           pOutput += sizeof(short);
	*(short *)pOutput = m_iStellars[13];           pOutput += sizeof(short);
	*(short *)pOutput = m_iStellars[14];           pOutput += sizeof(short);
	*(short *)pOutput = m_iStellars[15];           pOutput += sizeof(short);
	*(short *)pOutput = m_iDudeTypes[0];           pOutput += sizeof(short);
	*(short *)pOutput = m_iDudeTypes[1];           pOutput += sizeof(short);
	*(short *)pOutput = m_iDudeTypes[2];           pOutput += sizeof(short);
	*(short *)pOutput = m_iDudeTypes[3];           pOutput += sizeof(short);
	*(short *)pOutput = m_iDudeTypes[4];           pOutput += sizeof(short);
	*(short *)pOutput = m_iDudeTypes[5];           pOutput += sizeof(short);
	*(short *)pOutput = m_iDudeTypes[6];           pOutput += sizeof(short);
	*(short *)pOutput = m_iDudeTypes[7];           pOutput += sizeof(short);
	*(short *)pOutput = m_iDudeProbabilities[0];   pOutput += sizeof(short);
	*(short *)pOutput = m_iDudeProbabilities[1];   pOutput += sizeof(short);
	*(short *)pOutput = m_iDudeProbabilities[2];   pOutput += sizeof(short);
	*(short *)pOutput = m_iDudeProbabilities[3];   pOutput += sizeof(short);
	*(short *)pOutput = m_iDudeProbabilities[4];   pOutput += sizeof(short);
	*(short *)pOutput = m_iDudeProbabilities[5];   pOutput += sizeof(short);
	*(short *)pOutput = m_iDudeProbabilities[6];   pOutput += sizeof(short);
	*(short *)pOutput = m_iDudeProbabilities[7];   pOutput += sizeof(short);
	*(short *)pOutput = m_iNumShips;               pOutput += sizeof(short);
	*(short *)pOutput = m_iGovernment;             pOutput += sizeof(short);
	*(short *)pOutput = m_iMessageBuoy;            pOutput += sizeof(short);
	*(short *)pOutput = m_iNumAsteroids;           pOutput += sizeof(short);
	*(short *)pOutput = m_iInterference;           pOutput += sizeof(short);
	*(short *)pOutput = m_iPersons[0];             pOutput += sizeof(short);
	*(short *)pOutput = m_iPersons[1];             pOutput += sizeof(short);
	*(short *)pOutput = m_iPersons[2];             pOutput += sizeof(short);
	*(short *)pOutput = m_iPersons[3];             pOutput += sizeof(short);
	*(short *)pOutput = m_iPersons[4];             pOutput += sizeof(short);
	*(short *)pOutput = m_iPersons[5];             pOutput += sizeof(short);
	*(short *)pOutput = m_iPersons[6];             pOutput += sizeof(short);
	*(short *)pOutput = m_iPersons[7];             pOutput += sizeof(short);
	*(short *)pOutput = m_iPersonProbabilities[0]; pOutput += sizeof(short);
	*(short *)pOutput = m_iPersonProbabilities[1]; pOutput += sizeof(short);
	*(short *)pOutput = m_iPersonProbabilities[2]; pOutput += sizeof(short);
	*(short *)pOutput = m_iPersonProbabilities[3]; pOutput += sizeof(short);
	*(short *)pOutput = m_iPersonProbabilities[4]; pOutput += sizeof(short);
	*(short *)pOutput = m_iPersonProbabilities[5]; pOutput += sizeof(short);
	*(short *)pOutput = m_iPersonProbabilities[6]; pOutput += sizeof(short);
	*(short *)pOutput = m_iPersonProbabilities[7]; pOutput += sizeof(short);
	*(UINT  *)pOutput = m_iBackgroundColor;        pOutput += sizeof(UINT);
	*(short *)pOutput = m_iMurkiness;              pOutput += sizeof(short);
	*(USHORT *)pOutput = m_iAsteroidTypes;         pOutput += sizeof(USHORT);

	memcpy(pOutput, m_szVisibility, 256 * sizeof(char)); pOutput += 256 * sizeof(char);
	
	*(short *)pOutput = m_iReinforcementFleet;     pOutput += sizeof(short);
	*(short *)pOutput = m_iReinforcementTime;      pOutput += sizeof(short);
	*(short *)pOutput = m_iReinforcementInterval;  pOutput += sizeof(short);

	SwapEndians();

	return 1;
}

int CSystResource::Load(char *pInput, int iSize)
{
	m_iXPosition              = *(short *)pInput; pInput += sizeof(short);
	m_iYPosition              = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[0]          = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[1]          = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[2]          = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[3]          = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[4]          = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[5]          = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[6]          = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[7]          = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[8]          = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[9]          = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[10]         = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[11]         = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[12]         = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[13]         = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[14]         = *(short *)pInput; pInput += sizeof(short);
	m_iHyperlinks[15]         = *(short *)pInput; pInput += sizeof(short);
	m_iStellars[0]            = *(short *)pInput; pInput += sizeof(short);
	m_iStellars[1]            = *(short *)pInput; pInput += sizeof(short);
	m_iStellars[2]            = *(short *)pInput; pInput += sizeof(short);
	m_iStellars[3]            = *(short *)pInput; pInput += sizeof(short);
	m_iStellars[4]            = *(short *)pInput; pInput += sizeof(short);
	m_iStellars[5]            = *(short *)pInput; pInput += sizeof(short);
	m_iStellars[6]            = *(short *)pInput; pInput += sizeof(short);
	m_iStellars[7]            = *(short *)pInput; pInput += sizeof(short);
	m_iStellars[8]            = *(short *)pInput; pInput += sizeof(short);
	m_iStellars[9]            = *(short *)pInput; pInput += sizeof(short);
	m_iStellars[10]           = *(short *)pInput; pInput += sizeof(short);
	m_iStellars[11]           = *(short *)pInput; pInput += sizeof(short);
	m_iStellars[12]           = *(short *)pInput; pInput += sizeof(short);
	m_iStellars[13]           = *(short *)pInput; pInput += sizeof(short);
	m_iStellars[14]           = *(short *)pInput; pInput += sizeof(short);
	m_iStellars[15]           = *(short *)pInput; pInput += sizeof(short);
	m_iDudeTypes[0]           = *(short *)pInput; pInput += sizeof(short);
	m_iDudeTypes[1]           = *(short *)pInput; pInput += sizeof(short);
	m_iDudeTypes[2]           = *(short *)pInput; pInput += sizeof(short);
	m_iDudeTypes[3]           = *(short *)pInput; pInput += sizeof(short);
	m_iDudeTypes[4]           = *(short *)pInput; pInput += sizeof(short);
	m_iDudeTypes[5]           = *(short *)pInput; pInput += sizeof(short);
	m_iDudeTypes[6]           = *(short *)pInput; pInput += sizeof(short);
	m_iDudeTypes[7]           = *(short *)pInput; pInput += sizeof(short);
	m_iDudeProbabilities[0]   = *(short *)pInput; pInput += sizeof(short);
	m_iDudeProbabilities[1]   = *(short *)pInput; pInput += sizeof(short);
	m_iDudeProbabilities[2]   = *(short *)pInput; pInput += sizeof(short);
	m_iDudeProbabilities[3]   = *(short *)pInput; pInput += sizeof(short);
	m_iDudeProbabilities[4]   = *(short *)pInput; pInput += sizeof(short);
	m_iDudeProbabilities[5]   = *(short *)pInput; pInput += sizeof(short);
	m_iDudeProbabilities[6]   = *(short *)pInput; pInput += sizeof(short);
	m_iDudeProbabilities[7]   = *(short *)pInput; pInput += sizeof(short);
	m_iNumShips               = *(short *)pInput; pInput += sizeof(short);
	m_iGovernment             = *(short *)pInput; pInput += sizeof(short);
	m_iMessageBuoy            = *(short *)pInput; pInput += sizeof(short);
	m_iNumAsteroids           = *(short *)pInput; pInput += sizeof(short);
	m_iInterference           = *(short *)pInput; pInput += sizeof(short);
	m_iPersons[0]             = *(short *)pInput; pInput += sizeof(short);
	m_iPersons[1]             = *(short *)pInput; pInput += sizeof(short);
	m_iPersons[2]             = *(short *)pInput; pInput += sizeof(short);
	m_iPersons[3]             = *(short *)pInput; pInput += sizeof(short);
	m_iPersons[4]             = *(short *)pInput; pInput += sizeof(short);
	m_iPersons[5]             = *(short *)pInput; pInput += sizeof(short);
	m_iPersons[6]             = *(short *)pInput; pInput += sizeof(short);
	m_iPersons[7]             = *(short *)pInput; pInput += sizeof(short);
	m_iPersonProbabilities[0] = *(short *)pInput; pInput += sizeof(short);
	m_iPersonProbabilities[1] = *(short *)pInput; pInput += sizeof(short);
	m_iPersonProbabilities[2] = *(short *)pInput; pInput += sizeof(short);
	m_iPersonProbabilities[3] = *(short *)pInput; pInput += sizeof(short);
	m_iPersonProbabilities[4] = *(short *)pInput; pInput += sizeof(short);
	m_iPersonProbabilities[5] = *(short *)pInput; pInput += sizeof(short);
	m_iPersonProbabilities[6] = *(short *)pInput; pInput += sizeof(short);
	m_iPersonProbabilities[7] = *(short *)pInput; pInput += sizeof(short);
	m_iBackgroundColor        = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iMurkiness              = *(short *)pInput; pInput += sizeof(short);
	m_iAsteroidTypes          = *(USHORT *)pInput; pInput += sizeof(USHORT);

	memcpy(m_szVisibility, pInput, 256 * sizeof(char)); pInput += 256 * sizeof(char);

	m_iReinforcementFleet     = *(short *)pInput; pInput += sizeof(short);
	m_iReinforcementTime      = *(short *)pInput; pInput += sizeof(short);
	m_iReinforcementInterval  = *(short *)pInput; pInput += sizeof(short);

	SwapEndians();

	return 1;
}

int CSystResource::SwapEndians(void)
{
	m_iXPosition              = SwapEndianShort(m_iXPosition);
	m_iYPosition              = SwapEndianShort(m_iYPosition);
	m_iHyperlinks[0]          = SwapEndianShort(m_iHyperlinks[0]);
	m_iHyperlinks[1]          = SwapEndianShort(m_iHyperlinks[1]);
	m_iHyperlinks[2]          = SwapEndianShort(m_iHyperlinks[2]);
	m_iHyperlinks[3]          = SwapEndianShort(m_iHyperlinks[3]);
	m_iHyperlinks[4]          = SwapEndianShort(m_iHyperlinks[4]);
	m_iHyperlinks[5]          = SwapEndianShort(m_iHyperlinks[5]);
	m_iHyperlinks[6]          = SwapEndianShort(m_iHyperlinks[6]);
	m_iHyperlinks[7]          = SwapEndianShort(m_iHyperlinks[7]);
	m_iHyperlinks[8]          = SwapEndianShort(m_iHyperlinks[8]);
	m_iHyperlinks[9]          = SwapEndianShort(m_iHyperlinks[9]);
	m_iHyperlinks[10]         = SwapEndianShort(m_iHyperlinks[10]);
	m_iHyperlinks[11]         = SwapEndianShort(m_iHyperlinks[11]);
	m_iHyperlinks[12]         = SwapEndianShort(m_iHyperlinks[12]);
	m_iHyperlinks[13]         = SwapEndianShort(m_iHyperlinks[13]);
	m_iHyperlinks[14]         = SwapEndianShort(m_iHyperlinks[14]);
	m_iHyperlinks[15]         = SwapEndianShort(m_iHyperlinks[15]);
	m_iStellars[0]            = SwapEndianShort(m_iStellars[0]);
	m_iStellars[1]            = SwapEndianShort(m_iStellars[1]);
	m_iStellars[2]            = SwapEndianShort(m_iStellars[2]);
	m_iStellars[3]            = SwapEndianShort(m_iStellars[3]);
	m_iStellars[4]            = SwapEndianShort(m_iStellars[4]);
	m_iStellars[5]            = SwapEndianShort(m_iStellars[5]);
	m_iStellars[6]            = SwapEndianShort(m_iStellars[6]);
	m_iStellars[7]            = SwapEndianShort(m_iStellars[7]);
	m_iStellars[8]            = SwapEndianShort(m_iStellars[8]);
	m_iStellars[9]            = SwapEndianShort(m_iStellars[9]);
	m_iStellars[10]           = SwapEndianShort(m_iStellars[10]);
	m_iStellars[11]           = SwapEndianShort(m_iStellars[11]);
	m_iStellars[12]           = SwapEndianShort(m_iStellars[12]);
	m_iStellars[13]           = SwapEndianShort(m_iStellars[13]);
	m_iStellars[14]           = SwapEndianShort(m_iStellars[14]);
	m_iStellars[15]           = SwapEndianShort(m_iStellars[15]);
	m_iDudeTypes[0]           = SwapEndianShort(m_iDudeTypes[0]);
	m_iDudeTypes[1]           = SwapEndianShort(m_iDudeTypes[1]);
	m_iDudeTypes[2]           = SwapEndianShort(m_iDudeTypes[2]);
	m_iDudeTypes[3]           = SwapEndianShort(m_iDudeTypes[3]);
	m_iDudeTypes[4]           = SwapEndianShort(m_iDudeTypes[4]);
	m_iDudeTypes[5]           = SwapEndianShort(m_iDudeTypes[5]);
	m_iDudeTypes[6]           = SwapEndianShort(m_iDudeTypes[6]);
	m_iDudeTypes[7]           = SwapEndianShort(m_iDudeTypes[7]);
	m_iDudeProbabilities[0]   = SwapEndianShort(m_iDudeProbabilities[0]);
	m_iDudeProbabilities[1]   = SwapEndianShort(m_iDudeProbabilities[1]);
	m_iDudeProbabilities[2]   = SwapEndianShort(m_iDudeProbabilities[2]);
	m_iDudeProbabilities[3]   = SwapEndianShort(m_iDudeProbabilities[3]);
	m_iDudeProbabilities[4]   = SwapEndianShort(m_iDudeProbabilities[4]);
	m_iDudeProbabilities[5]   = SwapEndianShort(m_iDudeProbabilities[5]);
	m_iDudeProbabilities[6]   = SwapEndianShort(m_iDudeProbabilities[6]);
	m_iDudeProbabilities[7]   = SwapEndianShort(m_iDudeProbabilities[7]);
	m_iNumShips               = SwapEndianShort(m_iNumShips);
	m_iGovernment             = SwapEndianShort(m_iGovernment);
	m_iMessageBuoy            = SwapEndianShort(m_iMessageBuoy);
	m_iNumAsteroids           = SwapEndianShort(m_iNumAsteroids);
	m_iInterference           = SwapEndianShort(m_iInterference);
	m_iPersons[0]             = SwapEndianShort(m_iPersons[0]);
	m_iPersons[1]             = SwapEndianShort(m_iPersons[1]);
	m_iPersons[2]             = SwapEndianShort(m_iPersons[2]);
	m_iPersons[3]             = SwapEndianShort(m_iPersons[3]);
	m_iPersons[4]             = SwapEndianShort(m_iPersons[4]);
	m_iPersons[5]             = SwapEndianShort(m_iPersons[5]);
	m_iPersons[6]             = SwapEndianShort(m_iPersons[6]);
	m_iPersons[7]             = SwapEndianShort(m_iPersons[7]);
	m_iPersonProbabilities[0] = SwapEndianShort(m_iPersonProbabilities[0]);
	m_iPersonProbabilities[1] = SwapEndianShort(m_iPersonProbabilities[1]);
	m_iPersonProbabilities[2] = SwapEndianShort(m_iPersonProbabilities[2]);
	m_iPersonProbabilities[3] = SwapEndianShort(m_iPersonProbabilities[3]);
	m_iPersonProbabilities[4] = SwapEndianShort(m_iPersonProbabilities[4]);
	m_iPersonProbabilities[5] = SwapEndianShort(m_iPersonProbabilities[5]);
	m_iPersonProbabilities[6] = SwapEndianShort(m_iPersonProbabilities[6]);
	m_iPersonProbabilities[7] = SwapEndianShort(m_iPersonProbabilities[7]);
	m_iBackgroundColor        = SwapEndianInt(m_iBackgroundColor);
	m_iMurkiness              = SwapEndianShort(m_iMurkiness);
	m_iAsteroidTypes          = SwapEndianShort(m_iAsteroidTypes);
	m_iReinforcementFleet     = SwapEndianShort(m_iReinforcementFleet);
	m_iReinforcementTime      = SwapEndianShort(m_iReinforcementTime);
	m_iReinforcementInterval  = SwapEndianShort(m_iReinforcementInterval);

	return 1;
}

int CSystResource::SaveToText(std::ostream & output)
{
	output << m_iXPosition              << '\t'
		   << m_iYPosition              << '\t'
		   << m_iHyperlinks[0]          << '\t'
		   << m_iHyperlinks[1]          << '\t'
		   << m_iHyperlinks[2]          << '\t'
		   << m_iHyperlinks[3]          << '\t'
		   << m_iHyperlinks[4]          << '\t'
		   << m_iHyperlinks[5]          << '\t'
		   << m_iHyperlinks[6]          << '\t'
		   << m_iHyperlinks[7]          << '\t'
		   << m_iHyperlinks[8]          << '\t'
		   << m_iHyperlinks[9]          << '\t'
		   << m_iHyperlinks[10]         << '\t'
		   << m_iHyperlinks[11]         << '\t'
		   << m_iHyperlinks[12]         << '\t'
		   << m_iHyperlinks[13]         << '\t'
		   << m_iHyperlinks[14]         << '\t'
		   << m_iHyperlinks[15]         << '\t'
		   << m_iStellars[0]            << '\t'
		   << m_iStellars[1]            << '\t'
		   << m_iStellars[2]            << '\t'
		   << m_iStellars[3]            << '\t'
		   << m_iStellars[4]            << '\t'
		   << m_iStellars[5]            << '\t'
		   << m_iStellars[6]            << '\t'
		   << m_iStellars[7]            << '\t'
		   << m_iStellars[8]            << '\t'
		   << m_iStellars[9]            << '\t'
		   << m_iStellars[10]           << '\t'
		   << m_iStellars[11]           << '\t'
		   << m_iStellars[12]           << '\t'
		   << m_iStellars[13]           << '\t'
		   << m_iStellars[14]           << '\t'
		   << m_iStellars[15]           << '\t'
		   << m_iDudeTypes[0]           << '\t'
		   << m_iDudeTypes[1]           << '\t'
		   << m_iDudeTypes[2]           << '\t'
		   << m_iDudeTypes[3]           << '\t'
		   << m_iDudeTypes[4]           << '\t'
		   << m_iDudeTypes[5]           << '\t'
		   << m_iDudeTypes[6]           << '\t'
		   << m_iDudeTypes[7]           << '\t'
		   << m_iDudeProbabilities[0]   << '\t'
		   << m_iDudeProbabilities[1]   << '\t'
		   << m_iDudeProbabilities[2]   << '\t'
		   << m_iDudeProbabilities[3]   << '\t'
		   << m_iDudeProbabilities[4]   << '\t'
		   << m_iDudeProbabilities[5]   << '\t'
		   << m_iDudeProbabilities[6]   << '\t'
		   << m_iDudeProbabilities[7]   << '\t'
		   << m_iNumShips               << '\t'
		   << m_iGovernment             << '\t'
		   << m_iMessageBuoy            << '\t'
		   << m_iNumAsteroids           << '\t'
		   << m_iInterference           << '\t'
		   << m_iPersons[0]             << '\t'
		   << m_iPersons[1]             << '\t'
		   << m_iPersons[2]             << '\t'
		   << m_iPersons[3]             << '\t'
		   << m_iPersons[4]             << '\t'
		   << m_iPersons[5]             << '\t'
		   << m_iPersons[6]             << '\t'
		   << m_iPersons[7]             << '\t'
		   << m_iPersonProbabilities[0] << '\t'
		   << m_iPersonProbabilities[1] << '\t'
		   << m_iPersonProbabilities[2] << '\t'
		   << m_iPersonProbabilities[3] << '\t'
		   << m_iPersonProbabilities[4] << '\t'
		   << m_iPersonProbabilities[5] << '\t'
		   << m_iPersonProbabilities[6] << '\t'
		   << m_iPersonProbabilities[7] << '\t';

	PrintTextField(output, m_szVisibility, '\t');

	output << m_iBackgroundColor        << '\t'
		   << m_iMurkiness              << '\t'
		   << m_iReinforcementFleet     << '\t'
		   << m_iReinforcementTime      << '\t'
		   << m_iReinforcementInterval  << '\t';

	PrintHex16Field(output, (char *)&m_iAsteroidTypes, '\t');

	return 1;
}

int CSystResource::LoadFromText(std::istream & input)
{
	input >> m_iXPosition
		  >> m_iYPosition
		  >> m_iHyperlinks[0]
		  >> m_iHyperlinks[1]
		  >> m_iHyperlinks[2]
		  >> m_iHyperlinks[3]
		  >> m_iHyperlinks[4]
		  >> m_iHyperlinks[5]
		  >> m_iHyperlinks[6]
		  >> m_iHyperlinks[7]
		  >> m_iHyperlinks[8]
		  >> m_iHyperlinks[9]
		  >> m_iHyperlinks[10]
		  >> m_iHyperlinks[11]
		  >> m_iHyperlinks[12]
		  >> m_iHyperlinks[13]
		  >> m_iHyperlinks[14]
		  >> m_iHyperlinks[15]
		  >> m_iStellars[0]
		  >> m_iStellars[1]
		  >> m_iStellars[2]
		  >> m_iStellars[3]
		  >> m_iStellars[4]
		  >> m_iStellars[5]
		  >> m_iStellars[6]
		  >> m_iStellars[7]
		  >> m_iStellars[8]
		  >> m_iStellars[9]
		  >> m_iStellars[10]
		  >> m_iStellars[11]
		  >> m_iStellars[12]
		  >> m_iStellars[13]
		  >> m_iStellars[14]
		  >> m_iStellars[15]
		  >> m_iDudeTypes[0]
		  >> m_iDudeTypes[1]
		  >> m_iDudeTypes[2]
		  >> m_iDudeTypes[3]
		  >> m_iDudeTypes[4]
		  >> m_iDudeTypes[5]
		  >> m_iDudeTypes[6]
		  >> m_iDudeTypes[7]
		  >> m_iDudeProbabilities[0]
		  >> m_iDudeProbabilities[1]
		  >> m_iDudeProbabilities[2]
		  >> m_iDudeProbabilities[3]
		  >> m_iDudeProbabilities[4]
		  >> m_iDudeProbabilities[5]
		  >> m_iDudeProbabilities[6]
		  >> m_iDudeProbabilities[7]
		  >> m_iNumShips
		  >> m_iGovernment
		  >> m_iMessageBuoy
		  >> m_iNumAsteroids
		  >> m_iInterference
		  >> m_iPersons[0]
		  >> m_iPersons[1]
		  >> m_iPersons[2]
		  >> m_iPersons[3]
		  >> m_iPersons[4]
		  >> m_iPersons[5]
		  >> m_iPersons[6]
		  >> m_iPersons[7]
		  >> m_iPersonProbabilities[0]
		  >> m_iPersonProbabilities[1]
		  >> m_iPersonProbabilities[2]
		  >> m_iPersonProbabilities[3]
		  >> m_iPersonProbabilities[4]
		  >> m_iPersonProbabilities[5]
		  >> m_iPersonProbabilities[6]
		  >> m_iPersonProbabilities[7];

	input.ignore(1);

	ReadTextField(input, m_szVisibility, 256);

	input >> m_iBackgroundColor
		  >> m_iMurkiness
		  >> m_iReinforcementFleet
		  >> m_iReinforcementTime
		  >> m_iReinforcementInterval;

	input.ignore(1);

	ReadHex16Field(input, (char *)&m_iAsteroidTypes);

	return 1;
}

int CSystResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "syst ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_SYST_EDIT1, CCONTROL_TYPE_INT, IDS_STRING816);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_SYST_EDIT63, CCONTROL_TYPE_STR256, IDS_STRING817);
	m_controls[1].SetString(m_szName);
	m_controls[2].Create(hwnd, IDC_EDIT_SYST_EDIT2, CCONTROL_TYPE_INT, IDS_STRING818);
	m_controls[2].SetInt(m_iXPosition);
	m_controls[3].Create(hwnd, IDC_EDIT_SYST_EDIT3, CCONTROL_TYPE_INT, IDS_STRING819);
	m_controls[3].SetInt(m_iYPosition);
	m_controls[4].Create(hwnd, IDC_EDIT_SYST_EDIT4, CCONTROL_TYPE_INT, IDS_STRING820);
	m_controls[4].SetInt(m_iHyperlinks[0]);
	m_controls[5].Create(hwnd, IDC_EDIT_SYST_EDIT5, CCONTROL_TYPE_INT, IDS_STRING820);
	m_controls[5].SetInt(m_iHyperlinks[1]);
	m_controls[6].Create(hwnd, IDC_EDIT_SYST_EDIT6, CCONTROL_TYPE_INT, IDS_STRING820);
	m_controls[6].SetInt(m_iHyperlinks[2]);
	m_controls[7].Create(hwnd, IDC_EDIT_SYST_EDIT7, CCONTROL_TYPE_INT, IDS_STRING820);
	m_controls[7].SetInt(m_iHyperlinks[3]);
	m_controls[8].Create(hwnd, IDC_EDIT_SYST_EDIT8, CCONTROL_TYPE_INT, IDS_STRING820);
	m_controls[8].SetInt(m_iHyperlinks[4]);
	m_controls[9].Create(hwnd, IDC_EDIT_SYST_EDIT9, CCONTROL_TYPE_INT, IDS_STRING820);
	m_controls[9].SetInt(m_iHyperlinks[5]);
	m_controls[10].Create(hwnd, IDC_EDIT_SYST_EDIT10, CCONTROL_TYPE_INT, IDS_STRING820);
	m_controls[10].SetInt(m_iHyperlinks[6]);
	m_controls[11].Create(hwnd, IDC_EDIT_SYST_EDIT11, CCONTROL_TYPE_INT, IDS_STRING820);
	m_controls[11].SetInt(m_iHyperlinks[7]);
	m_controls[12].Create(hwnd, IDC_EDIT_SYST_EDIT12, CCONTROL_TYPE_INT, IDS_STRING820);
	m_controls[12].SetInt(m_iHyperlinks[8]);
	m_controls[13].Create(hwnd, IDC_EDIT_SYST_EDIT13, CCONTROL_TYPE_INT, IDS_STRING820);
	m_controls[13].SetInt(m_iHyperlinks[9]);
	m_controls[14].Create(hwnd, IDC_EDIT_SYST_EDIT14, CCONTROL_TYPE_INT, IDS_STRING820);
	m_controls[14].SetInt(m_iHyperlinks[10]);
	m_controls[15].Create(hwnd, IDC_EDIT_SYST_EDIT15, CCONTROL_TYPE_INT, IDS_STRING820);
	m_controls[15].SetInt(m_iHyperlinks[11]);
	m_controls[16].Create(hwnd, IDC_EDIT_SYST_EDIT16, CCONTROL_TYPE_INT, IDS_STRING820);
	m_controls[16].SetInt(m_iHyperlinks[12]);
	m_controls[17].Create(hwnd, IDC_EDIT_SYST_EDIT17, CCONTROL_TYPE_INT, IDS_STRING820);
	m_controls[17].SetInt(m_iHyperlinks[13]);
	m_controls[18].Create(hwnd, IDC_EDIT_SYST_EDIT18, CCONTROL_TYPE_INT, IDS_STRING820);
	m_controls[18].SetInt(m_iHyperlinks[14]);
	m_controls[19].Create(hwnd, IDC_EDIT_SYST_EDIT19, CCONTROL_TYPE_INT, IDS_STRING820);
	m_controls[19].SetInt(m_iHyperlinks[15]);
	m_controls[20].Create(hwnd, IDC_EDIT_SYST_EDIT20, CCONTROL_TYPE_INT, IDS_STRING821);
	m_controls[20].SetInt(m_iStellars[0]);
	m_controls[21].Create(hwnd, IDC_EDIT_SYST_EDIT21, CCONTROL_TYPE_INT, IDS_STRING821);
	m_controls[21].SetInt(m_iStellars[1]);
	m_controls[22].Create(hwnd, IDC_EDIT_SYST_EDIT22, CCONTROL_TYPE_INT, IDS_STRING821);
	m_controls[22].SetInt(m_iStellars[2]);
	m_controls[23].Create(hwnd, IDC_EDIT_SYST_EDIT23, CCONTROL_TYPE_INT, IDS_STRING821);
	m_controls[23].SetInt(m_iStellars[3]);
	m_controls[24].Create(hwnd, IDC_EDIT_SYST_EDIT24, CCONTROL_TYPE_INT, IDS_STRING821);
	m_controls[24].SetInt(m_iStellars[4]);
	m_controls[25].Create(hwnd, IDC_EDIT_SYST_EDIT25, CCONTROL_TYPE_INT, IDS_STRING821);
	m_controls[25].SetInt(m_iStellars[5]);
	m_controls[26].Create(hwnd, IDC_EDIT_SYST_EDIT26, CCONTROL_TYPE_INT, IDS_STRING821);
	m_controls[26].SetInt(m_iStellars[6]);
	m_controls[27].Create(hwnd, IDC_EDIT_SYST_EDIT27, CCONTROL_TYPE_INT, IDS_STRING821);
	m_controls[27].SetInt(m_iStellars[7]);
	m_controls[28].Create(hwnd, IDC_EDIT_SYST_EDIT28, CCONTROL_TYPE_INT, IDS_STRING821);
	m_controls[28].SetInt(m_iStellars[8]);
	m_controls[29].Create(hwnd, IDC_EDIT_SYST_EDIT29, CCONTROL_TYPE_INT, IDS_STRING821);
	m_controls[29].SetInt(m_iStellars[9]);
	m_controls[30].Create(hwnd, IDC_EDIT_SYST_EDIT30, CCONTROL_TYPE_INT, IDS_STRING821);
	m_controls[30].SetInt(m_iStellars[10]);
	m_controls[31].Create(hwnd, IDC_EDIT_SYST_EDIT31, CCONTROL_TYPE_INT, IDS_STRING821);
	m_controls[31].SetInt(m_iStellars[11]);
	m_controls[32].Create(hwnd, IDC_EDIT_SYST_EDIT32, CCONTROL_TYPE_INT, IDS_STRING821);
	m_controls[32].SetInt(m_iStellars[12]);
	m_controls[33].Create(hwnd, IDC_EDIT_SYST_EDIT33, CCONTROL_TYPE_INT, IDS_STRING821);
	m_controls[33].SetInt(m_iStellars[13]);
	m_controls[34].Create(hwnd, IDC_EDIT_SYST_EDIT34, CCONTROL_TYPE_INT, IDS_STRING821);
	m_controls[34].SetInt(m_iStellars[14]);
	m_controls[35].Create(hwnd, IDC_EDIT_SYST_EDIT35, CCONTROL_TYPE_INT, IDS_STRING821);
	m_controls[35].SetInt(m_iStellars[15]);
	m_controls[36].Create(hwnd, IDC_EDIT_SYST_EDIT36, CCONTROL_TYPE_INT, IDS_STRING822);
	m_controls[36].SetInt(m_iDudeTypes[0]);
	m_controls[37].Create(hwnd, IDC_EDIT_SYST_EDIT37, CCONTROL_TYPE_INT, IDS_STRING822);
	m_controls[37].SetInt(m_iDudeTypes[1]);
	m_controls[38].Create(hwnd, IDC_EDIT_SYST_EDIT38, CCONTROL_TYPE_INT, IDS_STRING822);
	m_controls[38].SetInt(m_iDudeTypes[2]);
	m_controls[39].Create(hwnd, IDC_EDIT_SYST_EDIT39, CCONTROL_TYPE_INT, IDS_STRING822);
	m_controls[39].SetInt(m_iDudeTypes[3]);
	m_controls[40].Create(hwnd, IDC_EDIT_SYST_EDIT40, CCONTROL_TYPE_INT, IDS_STRING822);
	m_controls[40].SetInt(m_iDudeTypes[4]);
	m_controls[41].Create(hwnd, IDC_EDIT_SYST_EDIT41, CCONTROL_TYPE_INT, IDS_STRING822);
	m_controls[41].SetInt(m_iDudeTypes[5]);
	m_controls[42].Create(hwnd, IDC_EDIT_SYST_EDIT42, CCONTROL_TYPE_INT, IDS_STRING822);
	m_controls[42].SetInt(m_iDudeTypes[6]);
	m_controls[43].Create(hwnd, IDC_EDIT_SYST_EDIT43, CCONTROL_TYPE_INT, IDS_STRING822);
	m_controls[43].SetInt(m_iDudeTypes[7]);
	m_controls[44].Create(hwnd, IDC_EDIT_SYST_EDIT44, CCONTROL_TYPE_INT, IDS_STRING823);
	m_controls[44].SetInt(m_iDudeProbabilities[0]);
	m_controls[45].Create(hwnd, IDC_EDIT_SYST_EDIT45, CCONTROL_TYPE_INT, IDS_STRING823);
	m_controls[45].SetInt(m_iDudeProbabilities[1]);
	m_controls[46].Create(hwnd, IDC_EDIT_SYST_EDIT46, CCONTROL_TYPE_INT, IDS_STRING823);
	m_controls[46].SetInt(m_iDudeProbabilities[2]);
	m_controls[47].Create(hwnd, IDC_EDIT_SYST_EDIT47, CCONTROL_TYPE_INT, IDS_STRING823);
	m_controls[47].SetInt(m_iDudeProbabilities[3]);
	m_controls[48].Create(hwnd, IDC_EDIT_SYST_EDIT48, CCONTROL_TYPE_INT, IDS_STRING823);
	m_controls[48].SetInt(m_iDudeProbabilities[4]);
	m_controls[49].Create(hwnd, IDC_EDIT_SYST_EDIT49, CCONTROL_TYPE_INT, IDS_STRING823);
	m_controls[49].SetInt(m_iDudeProbabilities[5]);
	m_controls[50].Create(hwnd, IDC_EDIT_SYST_EDIT50, CCONTROL_TYPE_INT, IDS_STRING823);
	m_controls[50].SetInt(m_iDudeProbabilities[6]);
	m_controls[51].Create(hwnd, IDC_EDIT_SYST_EDIT51, CCONTROL_TYPE_INT, IDS_STRING823);
	m_controls[51].SetInt(m_iDudeProbabilities[7]);
	m_controls[52].Create(hwnd, IDC_EDIT_SYST_EDIT52, CCONTROL_TYPE_INT, IDS_STRING824);
	m_controls[52].SetInt(m_iNumShips);
	m_controls[53].Create(hwnd, IDC_EDIT_SYST_EDIT53, CCONTROL_TYPE_INT, IDS_STRING825);
	m_controls[53].SetInt(m_iGovernment);
	m_controls[54].Create(hwnd, IDC_EDIT_SYST_EDIT54, CCONTROL_TYPE_INT, IDS_STRING826);
	m_controls[54].SetInt(m_iMessageBuoy);
	m_controls[55].Create(hwnd, IDC_EDIT_SYST_EDIT55, CCONTROL_TYPE_INT, IDS_STRING827);
	m_controls[55].SetInt(m_iNumAsteroids);
	m_controls[56].Create(hwnd, IDC_EDIT_SYST_EDIT56, CCONTROL_TYPE_INT, IDS_STRING828);
	m_controls[56].SetInt(m_iInterference);
	m_controls[57].Create(hwnd, IDC_EDIT_SYST_EDIT57, CCONTROL_TYPE_INT, IDS_STRING829);
	m_controls[57].SetInt(m_iPersons[0]);
	m_controls[58].Create(hwnd, IDC_EDIT_SYST_EDIT64, CCONTROL_TYPE_INT, IDS_STRING829);
	m_controls[58].SetInt(m_iPersons[1]);
	m_controls[59].Create(hwnd, IDC_EDIT_SYST_EDIT65, CCONTROL_TYPE_INT, IDS_STRING829);
	m_controls[59].SetInt(m_iPersons[2]);
	m_controls[60].Create(hwnd, IDC_EDIT_SYST_EDIT66, CCONTROL_TYPE_INT, IDS_STRING829);
	m_controls[60].SetInt(m_iPersons[3]);
	m_controls[61].Create(hwnd, IDC_EDIT_SYST_EDIT67, CCONTROL_TYPE_INT, IDS_STRING829);
	m_controls[61].SetInt(m_iPersons[4]);
	m_controls[62].Create(hwnd, IDC_EDIT_SYST_EDIT68, CCONTROL_TYPE_INT, IDS_STRING829);
	m_controls[62].SetInt(m_iPersons[5]);
	m_controls[63].Create(hwnd, IDC_EDIT_SYST_EDIT69, CCONTROL_TYPE_INT, IDS_STRING829);
	m_controls[63].SetInt(m_iPersons[6]);
	m_controls[64].Create(hwnd, IDC_EDIT_SYST_EDIT70, CCONTROL_TYPE_INT, IDS_STRING829);
	m_controls[64].SetInt(m_iPersons[7]);
	m_controls[65].Create(hwnd, IDC_EDIT_SYST_EDIT71, CCONTROL_TYPE_INT, IDS_STRING852);
	m_controls[65].SetInt(m_iPersonProbabilities[0]);
	m_controls[66].Create(hwnd, IDC_EDIT_SYST_EDIT72, CCONTROL_TYPE_INT, IDS_STRING852);
	m_controls[66].SetInt(m_iPersonProbabilities[1]);
	m_controls[67].Create(hwnd, IDC_EDIT_SYST_EDIT73, CCONTROL_TYPE_INT, IDS_STRING852);
	m_controls[67].SetInt(m_iPersonProbabilities[2]);
	m_controls[68].Create(hwnd, IDC_EDIT_SYST_EDIT74, CCONTROL_TYPE_INT, IDS_STRING852);
	m_controls[68].SetInt(m_iPersonProbabilities[3]);
	m_controls[69].Create(hwnd, IDC_EDIT_SYST_EDIT75, CCONTROL_TYPE_INT, IDS_STRING852);
	m_controls[69].SetInt(m_iPersonProbabilities[4]);
	m_controls[70].Create(hwnd, IDC_EDIT_SYST_EDIT76, CCONTROL_TYPE_INT, IDS_STRING852);
	m_controls[70].SetInt(m_iPersonProbabilities[5]);
	m_controls[71].Create(hwnd, IDC_EDIT_SYST_EDIT77, CCONTROL_TYPE_INT, IDS_STRING852);
	m_controls[71].SetInt(m_iPersonProbabilities[6]);
	m_controls[72].Create(hwnd, IDC_EDIT_SYST_EDIT78, CCONTROL_TYPE_INT, IDS_STRING852);
	m_controls[72].SetInt(m_iPersonProbabilities[7]);
	m_controls[73].Create(hwnd, IDC_EDIT_SYST_EDIT58, CCONTROL_TYPE_STR256, IDS_STRING830);
	m_controls[73].SetString(m_szVisibility);
	m_controls[74].Create(hwnd, IDC_EDIT_SYST_BUTTON1, CCONTROL_TYPE_COLOR, IDS_STRING831);
	m_controls[74].SetInt(m_iBackgroundColor);
	m_controls[75].Create(hwnd, IDC_EDIT_SYST_EDIT59, CCONTROL_TYPE_INT, IDS_STRING832);
	m_controls[75].SetInt(m_iMurkiness);
	m_controls[76].Create(hwnd, IDC_EDIT_SYST_EDIT60, CCONTROL_TYPE_INT, IDS_STRING833);
	m_controls[76].SetInt(m_iReinforcementFleet);
	m_controls[77].Create(hwnd, IDC_EDIT_SYST_EDIT61, CCONTROL_TYPE_INT, IDS_STRING834);
	m_controls[77].SetInt(m_iReinforcementTime);
	m_controls[78].Create(hwnd, IDC_EDIT_SYST_EDIT62, CCONTROL_TYPE_INT, IDS_STRING835);
	m_controls[78].SetInt(m_iReinforcementInterval);
	m_controls[79].Create(hwnd, IDC_EDIT_SYST_CHECK1, CCONTROL_TYPE_CHECK, IDS_STRING836);
	m_controls[79].SetInt(m_iAsteroidTypes & 0x0001);
	m_controls[80].Create(hwnd, IDC_EDIT_SYST_CHECK2, CCONTROL_TYPE_CHECK, IDS_STRING837);
	m_controls[80].SetInt(m_iAsteroidTypes & 0x0002);
	m_controls[81].Create(hwnd, IDC_EDIT_SYST_CHECK3, CCONTROL_TYPE_CHECK, IDS_STRING838);
	m_controls[81].SetInt(m_iAsteroidTypes & 0x0004);
	m_controls[82].Create(hwnd, IDC_EDIT_SYST_CHECK4, CCONTROL_TYPE_CHECK, IDS_STRING839);
	m_controls[82].SetInt(m_iAsteroidTypes & 0x0008);
	m_controls[83].Create(hwnd, IDC_EDIT_SYST_CHECK5, CCONTROL_TYPE_CHECK, IDS_STRING840);
	m_controls[83].SetInt(m_iAsteroidTypes & 0x0010);
	m_controls[84].Create(hwnd, IDC_EDIT_SYST_CHECK6, CCONTROL_TYPE_CHECK, IDS_STRING841);
	m_controls[84].SetInt(m_iAsteroidTypes & 0x0020);
	m_controls[85].Create(hwnd, IDC_EDIT_SYST_CHECK7, CCONTROL_TYPE_CHECK, IDS_STRING842);
	m_controls[85].SetInt(m_iAsteroidTypes & 0x0040);
	m_controls[86].Create(hwnd, IDC_EDIT_SYST_CHECK8, CCONTROL_TYPE_CHECK, IDS_STRING843);
	m_controls[86].SetInt(m_iAsteroidTypes & 0x0080);
	m_controls[87].Create(hwnd, IDC_EDIT_SYST_CHECK9, CCONTROL_TYPE_CHECK, IDS_STRING844);
	m_controls[87].SetInt(m_iAsteroidTypes & 0x0100);
	m_controls[88].Create(hwnd, IDC_EDIT_SYST_CHECK10, CCONTROL_TYPE_CHECK, IDS_STRING845);
	m_controls[88].SetInt(m_iAsteroidTypes & 0x0200);
	m_controls[89].Create(hwnd, IDC_EDIT_SYST_CHECK11, CCONTROL_TYPE_CHECK, IDS_STRING846);
	m_controls[89].SetInt(m_iAsteroidTypes & 0x0400);
	m_controls[90].Create(hwnd, IDC_EDIT_SYST_CHECK12, CCONTROL_TYPE_CHECK, IDS_STRING847);
	m_controls[90].SetInt(m_iAsteroidTypes & 0x0800);
	m_controls[91].Create(hwnd, IDC_EDIT_SYST_CHECK13, CCONTROL_TYPE_CHECK, IDS_STRING848);
	m_controls[91].SetInt(m_iAsteroidTypes & 0x1000);
	m_controls[92].Create(hwnd, IDC_EDIT_SYST_CHECK14, CCONTROL_TYPE_CHECK, IDS_STRING849);
	m_controls[92].SetInt(m_iAsteroidTypes & 0x2000);
	m_controls[93].Create(hwnd, IDC_EDIT_SYST_CHECK15, CCONTROL_TYPE_CHECK, IDS_STRING850);
	m_controls[93].SetInt(m_iAsteroidTypes & 0x4000);
	m_controls[94].Create(hwnd, IDC_EDIT_SYST_CHECK16, CCONTROL_TYPE_CHECK, IDS_STRING851);
	m_controls[94].SetInt(m_iAsteroidTypes & 0x8000);

	return 1;
}

int CSystResource::CloseAndSave(void)
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

	m_iXPosition = m_controls[2].GetInt();
	m_iYPosition = m_controls[3].GetInt();

	m_iHyperlinks[0]  = m_controls[4].GetInt();
	m_iHyperlinks[1]  = m_controls[5].GetInt();
	m_iHyperlinks[2]  = m_controls[6].GetInt();
	m_iHyperlinks[3]  = m_controls[7].GetInt();
	m_iHyperlinks[4]  = m_controls[8].GetInt();
	m_iHyperlinks[5]  = m_controls[9].GetInt();
	m_iHyperlinks[6]  = m_controls[10].GetInt();
	m_iHyperlinks[7]  = m_controls[11].GetInt();
	m_iHyperlinks[8]  = m_controls[12].GetInt();
	m_iHyperlinks[9]  = m_controls[13].GetInt();
	m_iHyperlinks[10] = m_controls[14].GetInt();
	m_iHyperlinks[11] = m_controls[15].GetInt();
	m_iHyperlinks[12] = m_controls[16].GetInt();
	m_iHyperlinks[13] = m_controls[17].GetInt();
	m_iHyperlinks[14] = m_controls[18].GetInt();
	m_iHyperlinks[15] = m_controls[19].GetInt();

	m_iStellars[0]    = m_controls[20].GetInt();
	m_iStellars[1]    = m_controls[21].GetInt();
	m_iStellars[2]    = m_controls[22].GetInt();
	m_iStellars[3]    = m_controls[23].GetInt();
	m_iStellars[4]    = m_controls[24].GetInt();
	m_iStellars[5]    = m_controls[25].GetInt();
	m_iStellars[6]    = m_controls[26].GetInt();
	m_iStellars[7]    = m_controls[27].GetInt();
	m_iStellars[8]    = m_controls[28].GetInt();
	m_iStellars[9]    = m_controls[29].GetInt();
	m_iStellars[10]   = m_controls[30].GetInt();
	m_iStellars[11]   = m_controls[31].GetInt();
	m_iStellars[12]   = m_controls[32].GetInt();
	m_iStellars[13]   = m_controls[33].GetInt();
	m_iStellars[14]   = m_controls[34].GetInt();
	m_iStellars[15]   = m_controls[35].GetInt();

	m_iDudeTypes[0]         = m_controls[36].GetInt();
	m_iDudeTypes[1]         = m_controls[37].GetInt();
	m_iDudeTypes[2]         = m_controls[38].GetInt();
	m_iDudeTypes[3]         = m_controls[39].GetInt();
	m_iDudeTypes[4]         = m_controls[40].GetInt();
	m_iDudeTypes[5]         = m_controls[41].GetInt();
	m_iDudeTypes[6]         = m_controls[42].GetInt();
	m_iDudeTypes[7]         = m_controls[43].GetInt();
	m_iDudeProbabilities[0] = m_controls[44].GetInt();
	m_iDudeProbabilities[1] = m_controls[45].GetInt();
	m_iDudeProbabilities[2] = m_controls[46].GetInt();
	m_iDudeProbabilities[3] = m_controls[47].GetInt();
	m_iDudeProbabilities[4] = m_controls[48].GetInt();
	m_iDudeProbabilities[5] = m_controls[49].GetInt();
	m_iDudeProbabilities[6] = m_controls[50].GetInt();
	m_iDudeProbabilities[7] = m_controls[51].GetInt();

	m_iNumShips = m_controls[52].GetInt();

	m_iGovernment = m_controls[53].GetInt();

	m_iMessageBuoy = m_controls[54].GetInt();

	m_iNumAsteroids = m_controls[55].GetInt();
	m_iInterference = m_controls[56].GetInt();

	m_iPersons[0]             = m_controls[57].GetInt();
	m_iPersons[1]             = m_controls[58].GetInt();
	m_iPersons[2]             = m_controls[59].GetInt();
	m_iPersons[3]             = m_controls[60].GetInt();
	m_iPersons[4]             = m_controls[61].GetInt();
	m_iPersons[5]             = m_controls[62].GetInt();
	m_iPersons[6]             = m_controls[63].GetInt();
	m_iPersons[7]             = m_controls[64].GetInt();
	m_iPersonProbabilities[0] = m_controls[65].GetInt();
	m_iPersonProbabilities[1] = m_controls[66].GetInt();
	m_iPersonProbabilities[2] = m_controls[67].GetInt();
	m_iPersonProbabilities[3] = m_controls[68].GetInt();
	m_iPersonProbabilities[4] = m_controls[69].GetInt();
	m_iPersonProbabilities[5] = m_controls[70].GetInt();
	m_iPersonProbabilities[6] = m_controls[71].GetInt();
	m_iPersonProbabilities[7] = m_controls[72].GetInt();

	strcpy(m_szVisibility, m_controls[73].GetString());

	m_iBackgroundColor = m_controls[74].GetInt();

	m_iMurkiness = m_controls[75].GetInt();

	m_iReinforcementFleet    = m_controls[76].GetInt();
	m_iReinforcementTime     = m_controls[77].GetInt();
	m_iReinforcementInterval = m_controls[78].GetInt();

	m_iAsteroidTypes = 0x0000;

	m_iAsteroidTypes |= m_controls[79].GetInt() << 0;
	m_iAsteroidTypes |= m_controls[80].GetInt() << 1;
	m_iAsteroidTypes |= m_controls[81].GetInt() << 2;
	m_iAsteroidTypes |= m_controls[82].GetInt() << 3;
	m_iAsteroidTypes |= m_controls[83].GetInt() << 4;
	m_iAsteroidTypes |= m_controls[84].GetInt() << 5;
	m_iAsteroidTypes |= m_controls[85].GetInt() << 6;
	m_iAsteroidTypes |= m_controls[86].GetInt() << 7;
	m_iAsteroidTypes |= m_controls[87].GetInt() << 8;
	m_iAsteroidTypes |= m_controls[88].GetInt() << 9;
	m_iAsteroidTypes |= m_controls[89].GetInt() << 10;
	m_iAsteroidTypes |= m_controls[90].GetInt() << 11;
	m_iAsteroidTypes |= m_controls[91].GetInt() << 12;
	m_iAsteroidTypes |= m_controls[92].GetInt() << 13;
	m_iAsteroidTypes |= m_controls[93].GetInt() << 14;
	m_iAsteroidTypes |= m_controls[94].GetInt() << 15;

	int i;

	for(i = 0; i < NUM_SYST_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CSystResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_SYST_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CSystResource::SystDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CSystResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CSystResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_SYST_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_SYST_OK)
			{
				pResource->CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_SYST_CONTROLS; i++)
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
