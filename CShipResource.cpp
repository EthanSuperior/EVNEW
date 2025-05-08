// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CShipResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CShipResource.h"

#include "resource.h"
#include "COutfResource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CShipResource::CShipResource(void)
{
	m_iCargo = 0;

	m_iShields        = 100;
	m_iShieldRecharge =   1;
	m_iArmor          = 100;
	m_iArmorRecharge  =   0;

	m_iAcceleration = 300;
	m_iMaxSpeed     = 300;
	m_iTurning      =  10;

	m_iFuel = 300;

	m_iFreeMass = 0;

	m_iMaxGuns    = 1;
	m_iMaxTurrets = 1;

	m_iTechLevel = 0;

	m_iCost = 0;

	m_iDeathDelay = 0;
	m_iExplosion1 = -1;
	m_iExplosion2 = -1;

	m_iDisplayWeight = 0;

	m_iMass     = 1;
	m_iLength   = 1;
	m_iCrew     = 1;
	m_iStrength = 1;

	m_iGovernment = -1;

	m_iEscapePodCount = 0;

	m_iFuelRegeneration = 0;

	m_iSkillVariation = 0;

	memset(m_szAvailability, 0, 255 * sizeof(char));
	memset(m_szAppearOn,     0, 255 * sizeof(char));
	memset(m_szOnPurchase,   0, 256 * sizeof(char));

	m_iDeionize      = 1;
	m_iMaxIonization = 1;

	m_iKeyCarried = -1;

	int i;

	for(i = 0; i < 8; i++)
	{
		m_cContribute[i] = 0x00;
		m_cRequire[i]    = 0x00;
	}

	m_iBuyRandom  = 100;
	m_iHireRandom = 100;

	memset(m_szOnCapture, 0, 255 * sizeof(char));
	memset(m_szOnRetire,  0, 255 * sizeof(char));

	memset(m_szSubtitle,  0, 64 * sizeof(char));
	memset(m_szShortName, 0, 64 * sizeof(char));
	memset(m_szCommName,  0, 32 * sizeof(char));
	memset(m_szLongName,  0, 128 * sizeof(char));

	memset(m_szMovieFile, 0, 32 * sizeof(char));

	m_iEscortAI          = 1;
	m_iEscortUpgradeTo   = -1;
	m_iEscortUpgradeCost = 0;
	m_iEscortSellValue   = 0;
	m_iEscortType        = -1;

	for(i = 0; i < 8; i++)
	{
		m_iWeapons[i]      = -1;
		m_iWeaponCounts[i] = 0;
		m_iWeaponAmmos[i]  = 0;
	}

	for(i = 0; i < 8; i++)
	{
		m_iOutfits[i]      = -1;
		m_iOutfitCounts[i] = 0;
	}

	m_iFlags1 = 0x0000;
	m_iFlags2 = 0x0000;
	m_iFlags3 = 0x0000;
}

CShipResource::~CShipResource(void)
{

}

int CShipResource::GetType(void)
{
	return CNR_TYPE_SHIP;
}

int CShipResource::GetSize(void)
{
	return 1860;
}

int CShipResource::GetDialogID(void)
{
	return IDD_EDIT_SHIP;
}

DLGPROCNOCALLBACK CShipResource::GetDialogProc(void)
{
	return ShipDlgProc;
}

int CShipResource::GetNumFields(void)
{
	return NUM_SHIP_FIELDS;
}

const std::string * CShipResource::GetFieldNames(void)
{
	return g_szShipFields;
}

int CShipResource::Save(char *pOutput)
{
	SwapEndians();

	*(short *)pOutput = m_iCargo;             pOutput += sizeof(short);
	*(short *)pOutput = m_iShields;           pOutput += sizeof(short);
	*(short *)pOutput = m_iAcceleration;      pOutput += sizeof(short);
	*(short *)pOutput = m_iMaxSpeed;          pOutput += sizeof(short);
	*(short *)pOutput = m_iTurning;           pOutput += sizeof(short);
	*(short *)pOutput = m_iFuel;              pOutput += sizeof(short);
	*(short *)pOutput = m_iFreeMass;          pOutput += sizeof(short);
	*(short *)pOutput = m_iArmor;             pOutput += sizeof(short);
	*(short *)pOutput = m_iShieldRecharge;    pOutput += sizeof(short);
	*(short *)pOutput = m_iWeapons[0];        pOutput += sizeof(short);
	*(short *)pOutput = m_iWeapons[1];        pOutput += sizeof(short);
	*(short *)pOutput = m_iWeapons[2];        pOutput += sizeof(short);
	*(short *)pOutput = m_iWeapons[3];        pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponCounts[0];   pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponCounts[1];   pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponCounts[2];   pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponCounts[3];   pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponAmmos[0];    pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponAmmos[1];    pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponAmmos[2];    pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponAmmos[3];    pOutput += sizeof(short);
	*(short *)pOutput = m_iMaxGuns;           pOutput += sizeof(short);
	*(short *)pOutput = m_iMaxTurrets;        pOutput += sizeof(short);
	*(short *)pOutput = m_iTechLevel;         pOutput += sizeof(short);
	*(int   *)pOutput = m_iCost;              pOutput += sizeof(int);
	*(short *)pOutput = m_iDeathDelay;        pOutput += sizeof(short);
	*(short *)pOutput = m_iArmorRecharge;     pOutput += sizeof(short);
	*(short *)pOutput = m_iExplosion1;        pOutput += sizeof(short);
	*(short *)pOutput = m_iExplosion2;        pOutput += sizeof(short);
	*(short *)pOutput = m_iDisplayWeight;     pOutput += sizeof(short);
	*(short *)pOutput = m_iMass;              pOutput += sizeof(short);
	*(short *)pOutput = m_iLength;            pOutput += sizeof(short);
	*(short *)pOutput = m_iEscortAI;          pOutput += sizeof(short);
	*(short *)pOutput = m_iCrew;              pOutput += sizeof(short);
	*(short *)pOutput = m_iStrength;          pOutput += sizeof(short);
	*(short *)pOutput = m_iGovernment;        pOutput += sizeof(short);
	*(USHORT *)pOutput = m_iFlags1;           pOutput += sizeof(USHORT);
	*(short *)pOutput = m_iEscapePodCount;    pOutput += sizeof(short);
	*(short *)pOutput = m_iOutfits[0];        pOutput += sizeof(short);
	*(short *)pOutput = m_iOutfits[1];        pOutput += sizeof(short);
	*(short *)pOutput = m_iOutfits[2];        pOutput += sizeof(short);
	*(short *)pOutput = m_iOutfits[3];        pOutput += sizeof(short);
	*(short *)pOutput = m_iOutfitCounts[0];   pOutput += sizeof(short);
	*(short *)pOutput = m_iOutfitCounts[1];   pOutput += sizeof(short);
	*(short *)pOutput = m_iOutfitCounts[2];   pOutput += sizeof(short);
	*(short *)pOutput = m_iOutfitCounts[3];   pOutput += sizeof(short);
	*(short *)pOutput = m_iFuelRegeneration;  pOutput += sizeof(short);
	*(short *)pOutput = m_iSkillVariation;    pOutput += sizeof(short);
	*(USHORT *)pOutput = m_iFlags2;           pOutput += sizeof(USHORT);

	memcpy(pOutput, m_cContribute,      8 * sizeof(char)); pOutput +=   8 * sizeof(char);
	memcpy(pOutput, m_szAvailability, 255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_szAppearOn,     255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_szOnPurchase,   256 * sizeof(char)); pOutput += 256 * sizeof(char);

	*(short *)pOutput = m_iDeionize;          pOutput += sizeof(short);
	*(short *)pOutput = m_iMaxIonization;     pOutput += sizeof(short);
	*(short *)pOutput = m_iKeyCarried;        pOutput += sizeof(short);
	*(short *)pOutput = m_iOutfits[4];        pOutput += sizeof(short);
	*(short *)pOutput = m_iOutfits[5];        pOutput += sizeof(short);
	*(short *)pOutput = m_iOutfits[6];        pOutput += sizeof(short);
	*(short *)pOutput = m_iOutfits[7];        pOutput += sizeof(short);
	*(short *)pOutput = m_iOutfitCounts[4];   pOutput += sizeof(short);
	*(short *)pOutput = m_iOutfitCounts[5];   pOutput += sizeof(short);
	*(short *)pOutput = m_iOutfitCounts[6];   pOutput += sizeof(short);
	*(short *)pOutput = m_iOutfitCounts[7];   pOutput += sizeof(short);

	memcpy(pOutput, m_cRequire, 8 * sizeof(char)); pOutput += 8 * sizeof(char);

	*(short *)pOutput = m_iBuyRandom;         pOutput += sizeof(short);
	*(short *)pOutput = m_iHireRandom;        pOutput += sizeof(short); pOutput += 68 * sizeof(char);

	ToMacString(m_szShortName);
	ToMacString(m_szCommName);
	ToMacString(m_szLongName);

	memcpy(pOutput, m_szOnCapture, 255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_szOnRetire,  255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_szShortName,  64 * sizeof(char)); pOutput +=  64 * sizeof(char);
	memcpy(pOutput, m_szCommName,   32 * sizeof(char)); pOutput +=  32 * sizeof(char);
	memcpy(pOutput, m_szLongName,  128 * sizeof(char)); pOutput += 128 * sizeof(char);
	memcpy(pOutput, m_szMovieFile,  32 * sizeof(char)); pOutput +=  32 * sizeof(char);

	ToWinString(m_szShortName);
	ToWinString(m_szCommName);
	ToWinString(m_szLongName);

	*(short *)pOutput = m_iWeapons[4];        pOutput += sizeof(short);
	*(short *)pOutput = m_iWeapons[5];        pOutput += sizeof(short);
	*(short *)pOutput = m_iWeapons[6];        pOutput += sizeof(short);
	*(short *)pOutput = m_iWeapons[7];        pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponCounts[4];   pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponCounts[5];   pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponCounts[6];   pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponCounts[7];   pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponAmmos[4];    pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponAmmos[5];    pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponAmmos[6];    pOutput += sizeof(short);
	*(short *)pOutput = m_iWeaponAmmos[7];    pOutput += sizeof(short);

	ToMacString(m_szSubtitle);

	memcpy(pOutput, m_szSubtitle, 64 * sizeof(char)); pOutput += 64 * sizeof(char);

	ToWinString(m_szSubtitle);

	*(USHORT *)pOutput = m_iFlags3;           pOutput += sizeof(USHORT);
	*(short *)pOutput = m_iEscortUpgradeTo;   pOutput += sizeof(short);
	*(int   *)pOutput = m_iEscortUpgradeCost; pOutput += sizeof(int);
	*(int   *)pOutput = m_iEscortSellValue;   pOutput += sizeof(int);
	*(short *)pOutput = m_iEscortType;        pOutput += sizeof(short);

	SwapEndians();

	return 1;
}

int CShipResource::Load(char *pInput, int iSize)
{
	m_iCargo             = *(short *)pInput; pInput += sizeof(short);
	m_iShields           = *(short *)pInput; pInput += sizeof(short);
	m_iAcceleration      = *(short *)pInput; pInput += sizeof(short);
	m_iMaxSpeed          = *(short *)pInput; pInput += sizeof(short);
	m_iTurning           = *(short *)pInput; pInput += sizeof(short);
	m_iFuel              = *(short *)pInput; pInput += sizeof(short);
	m_iFreeMass          = *(short *)pInput; pInput += sizeof(short);
	m_iArmor             = *(short *)pInput; pInput += sizeof(short);
	m_iShieldRecharge    = *(short *)pInput; pInput += sizeof(short);
	m_iWeapons[0]        = *(short *)pInput; pInput += sizeof(short);
	m_iWeapons[1]        = *(short *)pInput; pInput += sizeof(short);
	m_iWeapons[2]        = *(short *)pInput; pInput += sizeof(short);
	m_iWeapons[3]        = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponCounts[0]   = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponCounts[1]   = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponCounts[2]   = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponCounts[3]   = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponAmmos[0]    = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponAmmos[1]    = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponAmmos[2]    = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponAmmos[3]    = *(short *)pInput; pInput += sizeof(short);
	m_iMaxGuns           = *(short *)pInput; pInput += sizeof(short);
	m_iMaxTurrets        = *(short *)pInput; pInput += sizeof(short);
	m_iTechLevel         = *(short *)pInput; pInput += sizeof(short);
	m_iCost              = *(int   *)pInput; pInput += sizeof(int);
	m_iDeathDelay        = *(short *)pInput; pInput += sizeof(short);
	m_iArmorRecharge     = *(short *)pInput; pInput += sizeof(short);
	m_iExplosion1        = *(short *)pInput; pInput += sizeof(short);
	m_iExplosion2        = *(short *)pInput; pInput += sizeof(short);
	m_iDisplayWeight     = *(short *)pInput; pInput += sizeof(short);
	m_iMass              = *(short *)pInput; pInput += sizeof(short);
	m_iLength            = *(short *)pInput; pInput += sizeof(short);
	m_iEscortAI          = *(short *)pInput; pInput += sizeof(short);
	m_iCrew              = *(short *)pInput; pInput += sizeof(short);
	m_iStrength          = *(short *)pInput; pInput += sizeof(short);
	m_iGovernment        = *(short *)pInput; pInput += sizeof(short);
	m_iFlags1            = *(USHORT *)pInput; pInput += sizeof(USHORT);
	m_iEscapePodCount    = *(short *)pInput; pInput += sizeof(short);
	m_iOutfits[0]        = *(short *)pInput; pInput += sizeof(short);
	m_iOutfits[1]        = *(short *)pInput; pInput += sizeof(short);
	m_iOutfits[2]        = *(short *)pInput; pInput += sizeof(short);
	m_iOutfits[3]        = *(short *)pInput; pInput += sizeof(short);
	m_iOutfitCounts[0]   = *(short *)pInput; pInput += sizeof(short);
	m_iOutfitCounts[1]   = *(short *)pInput; pInput += sizeof(short);
	m_iOutfitCounts[2]   = *(short *)pInput; pInput += sizeof(short);
	m_iOutfitCounts[3]   = *(short *)pInput; pInput += sizeof(short);
	m_iFuelRegeneration  = *(short *)pInput; pInput += sizeof(short);
	m_iSkillVariation    = *(short *)pInput; pInput += sizeof(short);
	m_iFlags2            = *(USHORT *)pInput; pInput += sizeof(USHORT);

	memcpy(m_cContribute,    pInput,   8 * sizeof(char)); pInput +=   8 * sizeof(char);
	memcpy(m_szAvailability, pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	memcpy(m_szAppearOn,     pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	memcpy(m_szOnPurchase,   pInput, 256 * sizeof(char)); pInput += 256 * sizeof(char);

	m_iDeionize          = *(short *)pInput; pInput += sizeof(short);
	m_iMaxIonization     = *(short *)pInput; pInput += sizeof(short);
	m_iKeyCarried        = *(short *)pInput; pInput += sizeof(short);
	m_iOutfits[4]        = *(short *)pInput; pInput += sizeof(short);
	m_iOutfits[5]        = *(short *)pInput; pInput += sizeof(short);
	m_iOutfits[6]        = *(short *)pInput; pInput += sizeof(short);
	m_iOutfits[7]        = *(short *)pInput; pInput += sizeof(short);
	m_iOutfitCounts[4]   = *(short *)pInput; pInput += sizeof(short);
	m_iOutfitCounts[5]   = *(short *)pInput; pInput += sizeof(short);
	m_iOutfitCounts[6]   = *(short *)pInput; pInput += sizeof(short);
	m_iOutfitCounts[7]   = *(short *)pInput; pInput += sizeof(short);

	memcpy(m_cRequire, pInput, 8 * sizeof(char)); pInput += 8 * sizeof(char);

	m_iBuyRandom         = *(short *)pInput; pInput += sizeof(short);
	m_iHireRandom        = *(short *)pInput; pInput += sizeof(short); pInput += 68 * sizeof(char);

	memcpy(m_szOnCapture, pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	memcpy(m_szOnRetire,  pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	memcpy(m_szShortName, pInput,  64 * sizeof(char)); pInput +=  64 * sizeof(char);
	memcpy(m_szCommName,  pInput,  32 * sizeof(char)); pInput +=  32 * sizeof(char);
	memcpy(m_szLongName,  pInput, 128 * sizeof(char)); pInput += 128 * sizeof(char);
	memcpy(m_szMovieFile, pInput,  32 * sizeof(char)); pInput +=  32 * sizeof(char);

	ToWinString(m_szShortName);
	ToWinString(m_szCommName);
	ToWinString(m_szLongName);

	m_iWeapons[4]        = *(short *)pInput; pInput += sizeof(short);
	m_iWeapons[5]        = *(short *)pInput; pInput += sizeof(short);
	m_iWeapons[6]        = *(short *)pInput; pInput += sizeof(short);
	m_iWeapons[7]        = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponCounts[4]   = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponCounts[5]   = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponCounts[6]   = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponCounts[7]   = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponAmmos[4]    = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponAmmos[5]    = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponAmmos[6]    = *(short *)pInput; pInput += sizeof(short);
	m_iWeaponAmmos[7]    = *(short *)pInput; pInput += sizeof(short);

	memcpy(m_szSubtitle, pInput, 64 * sizeof(char)); pInput += 64 * sizeof(char);

	ToWinString(m_szSubtitle);

	m_iFlags3            = *(USHORT *)pInput; pInput += sizeof(USHORT);
	m_iEscortUpgradeTo   = *(short *)pInput; pInput += sizeof(short);
	m_iEscortUpgradeCost = *(int   *)pInput; pInput += sizeof(int);
	m_iEscortSellValue   = *(int   *)pInput; pInput += sizeof(int);
	m_iEscortType        = *(short *)pInput; pInput += sizeof(short);

	SwapEndians();

	return 1;
}

int CShipResource::SwapEndians(void)
{
	m_iCargo             = SwapEndianShort(m_iCargo);
	m_iShields           = SwapEndianShort(m_iShields);
	m_iAcceleration      = SwapEndianShort(m_iAcceleration);
	m_iMaxSpeed          = SwapEndianShort(m_iMaxSpeed);
	m_iTurning           = SwapEndianShort(m_iTurning);
	m_iFuel              = SwapEndianShort(m_iFuel);
	m_iFreeMass          = SwapEndianShort(m_iFreeMass);
	m_iArmor             = SwapEndianShort(m_iArmor);
	m_iShieldRecharge    = SwapEndianShort(m_iShieldRecharge);
	m_iWeapons[0]        = SwapEndianShort(m_iWeapons[0]);
	m_iWeapons[1]        = SwapEndianShort(m_iWeapons[1]);
	m_iWeapons[2]        = SwapEndianShort(m_iWeapons[2]);
	m_iWeapons[3]        = SwapEndianShort(m_iWeapons[3]);
	m_iWeaponCounts[0]   = SwapEndianShort(m_iWeaponCounts[0]);
	m_iWeaponCounts[1]   = SwapEndianShort(m_iWeaponCounts[1]);
	m_iWeaponCounts[2]   = SwapEndianShort(m_iWeaponCounts[2]);
	m_iWeaponCounts[3]   = SwapEndianShort(m_iWeaponCounts[3]);
	m_iWeaponAmmos[0]    = SwapEndianShort(m_iWeaponAmmos[0]);
	m_iWeaponAmmos[1]    = SwapEndianShort(m_iWeaponAmmos[1]);
	m_iWeaponAmmos[2]    = SwapEndianShort(m_iWeaponAmmos[2]);
	m_iWeaponAmmos[3]    = SwapEndianShort(m_iWeaponAmmos[3]);
	m_iMaxGuns           = SwapEndianShort(m_iMaxGuns);
	m_iMaxTurrets        = SwapEndianShort(m_iMaxTurrets);
	m_iTechLevel         = SwapEndianShort(m_iTechLevel);
	m_iCost              = SwapEndianInt(m_iCost);
	m_iDeathDelay        = SwapEndianShort(m_iDeathDelay);
	m_iArmorRecharge     = SwapEndianShort(m_iArmorRecharge);
	m_iExplosion1        = SwapEndianShort(m_iExplosion1);
	m_iExplosion2        = SwapEndianShort(m_iExplosion2);
	m_iDisplayWeight     = SwapEndianShort(m_iDisplayWeight);
	m_iMass              = SwapEndianShort(m_iMass);
	m_iLength            = SwapEndianShort(m_iLength);
	m_iEscortAI          = SwapEndianShort(m_iEscortAI);
	m_iCrew              = SwapEndianShort(m_iCrew);
	m_iStrength          = SwapEndianShort(m_iStrength);
	m_iGovernment        = SwapEndianShort(m_iGovernment);
	m_iFlags1            = SwapEndianShort(m_iFlags1);
	m_iEscapePodCount    = SwapEndianShort(m_iEscapePodCount);
	m_iOutfits[0]        = SwapEndianShort(m_iOutfits[0]);
	m_iOutfits[1]        = SwapEndianShort(m_iOutfits[1]);
	m_iOutfits[2]        = SwapEndianShort(m_iOutfits[2]);
	m_iOutfits[3]        = SwapEndianShort(m_iOutfits[3]);
	m_iOutfitCounts[0]   = SwapEndianShort(m_iOutfitCounts[0]);
	m_iOutfitCounts[1]   = SwapEndianShort(m_iOutfitCounts[1]);
	m_iOutfitCounts[2]   = SwapEndianShort(m_iOutfitCounts[2]);
	m_iOutfitCounts[3]   = SwapEndianShort(m_iOutfitCounts[3]);
	m_iFuelRegeneration  = SwapEndianShort(m_iFuelRegeneration);
	m_iSkillVariation    = SwapEndianShort(m_iSkillVariation);
	m_iFlags2            = SwapEndianShort(m_iFlags2);
	m_iDeionize          = SwapEndianShort(m_iDeionize);
	m_iMaxIonization     = SwapEndianShort(m_iMaxIonization);
	m_iKeyCarried        = SwapEndianShort(m_iKeyCarried);
	m_iOutfits[4]        = SwapEndianShort(m_iOutfits[4]);
	m_iOutfits[5]        = SwapEndianShort(m_iOutfits[5]);
	m_iOutfits[6]        = SwapEndianShort(m_iOutfits[6]);
	m_iOutfits[7]        = SwapEndianShort(m_iOutfits[7]);
	m_iOutfitCounts[4]   = SwapEndianShort(m_iOutfitCounts[4]);
	m_iOutfitCounts[5]   = SwapEndianShort(m_iOutfitCounts[5]);
	m_iOutfitCounts[6]   = SwapEndianShort(m_iOutfitCounts[6]);
	m_iOutfitCounts[7]   = SwapEndianShort(m_iOutfitCounts[7]);
	m_iBuyRandom         = SwapEndianShort(m_iBuyRandom);
	m_iHireRandom        = SwapEndianShort(m_iHireRandom);
	m_iWeapons[4]        = SwapEndianShort(m_iWeapons[4]);
	m_iWeapons[5]        = SwapEndianShort(m_iWeapons[5]);
	m_iWeapons[6]        = SwapEndianShort(m_iWeapons[6]);
	m_iWeapons[7]        = SwapEndianShort(m_iWeapons[7]);
	m_iWeaponCounts[4]   = SwapEndianShort(m_iWeaponCounts[4]);
	m_iWeaponCounts[5]   = SwapEndianShort(m_iWeaponCounts[5]);
	m_iWeaponCounts[6]   = SwapEndianShort(m_iWeaponCounts[6]);
	m_iWeaponCounts[7]   = SwapEndianShort(m_iWeaponCounts[7]);
	m_iWeaponAmmos[4]    = SwapEndianShort(m_iWeaponAmmos[4]);
	m_iWeaponAmmos[5]    = SwapEndianShort(m_iWeaponAmmos[5]);
	m_iWeaponAmmos[6]    = SwapEndianShort(m_iWeaponAmmos[6]);
	m_iWeaponAmmos[7]    = SwapEndianShort(m_iWeaponAmmos[7]);
	m_iFlags3            = SwapEndianShort(m_iFlags3);
	m_iEscortUpgradeTo   = SwapEndianShort(m_iEscortUpgradeTo);
	m_iEscortUpgradeCost = SwapEndianInt(m_iEscortUpgradeCost);
	m_iEscortSellValue   = SwapEndianInt(m_iEscortSellValue);
	m_iEscortType        = SwapEndianShort(m_iEscortType);

	return 1;
}

int CShipResource::SaveToText(std::ostream & output)
{
	output << m_iCargo            << '\t'
		   << m_iShields          << '\t'
		   << m_iShieldRecharge   << '\t'
		   << m_iArmor            << '\t'
		   << m_iArmorRecharge    << '\t'
		   << m_iAcceleration     << '\t'
		   << m_iMaxSpeed         << '\t'
		   << m_iTurning          << '\t'
		   << m_iFuel             << '\t'
		   << m_iFreeMass         << '\t'
		   << m_iMaxGuns          << '\t'
		   << m_iMaxTurrets       << '\t'
		   << m_iTechLevel        << '\t'
		   << m_iCost             << '\t'
		   << m_iDeathDelay       << '\t'
		   << m_iExplosion1       << '\t'
		   << m_iExplosion2       << '\t'
		   << m_iDisplayWeight    << '\t'
		   << m_iMass             << '\t'
		   << m_iLength           << '\t'
		   << m_iCrew             << '\t'
		   << m_iStrength         << '\t'
		   << m_iGovernment       << '\t'
		   << m_iEscapePodCount   << '\t'
		   << m_iFuelRegeneration << '\t'
		   << m_iSkillVariation   << '\t';

	PrintTextField(output, m_szAvailability, '\t');
	PrintTextField(output, m_szAppearOn,     '\t');
	PrintTextField(output, m_szOnPurchase,   '\t');

	output << m_iDeionize      << '\t'
		   << m_iMaxIonization << '\t'
		   << m_iKeyCarried    << '\t';

	PrintHex64Field(output, m_cContribute, '\t');
	PrintHex64Field(output, m_cRequire,    '\t');

	output << m_iBuyRandom  << '\t'
		   << m_iHireRandom << '\t';

	PrintTextField(output, m_szOnCapture, '\t');
	PrintTextField(output, m_szOnRetire,  '\t');
	PrintTextField(output, m_szSubtitle,  '\t');
	PrintTextField(output, m_szShortName, '\t');
	PrintTextField(output, m_szCommName,  '\t');
	PrintTextField(output, m_szLongName,  '\t');
	PrintTextField(output, m_szMovieFile, '\t');

	output << m_iEscortAI          << '\t'
		   << m_iEscortUpgradeTo   << '\t'
		   << m_iEscortUpgradeCost << '\t'
		   << m_iEscortSellValue   << '\t'
		   << m_iEscortType        << '\t'
		   << m_iWeapons[0]        << '\t'
		   << m_iWeapons[1]        << '\t'
		   << m_iWeapons[2]        << '\t'
		   << m_iWeapons[3]        << '\t'
		   << m_iWeapons[4]        << '\t'
		   << m_iWeapons[5]        << '\t'
		   << m_iWeapons[6]        << '\t'
		   << m_iWeapons[7]        << '\t'
		   << m_iWeaponCounts[0]   << '\t'
		   << m_iWeaponCounts[1]   << '\t'
		   << m_iWeaponCounts[2]   << '\t'
		   << m_iWeaponCounts[3]   << '\t'
		   << m_iWeaponCounts[4]   << '\t'
		   << m_iWeaponCounts[5]   << '\t'
		   << m_iWeaponCounts[6]   << '\t'
		   << m_iWeaponCounts[7]   << '\t'
		   << m_iWeaponAmmos[0]    << '\t'
		   << m_iWeaponAmmos[1]    << '\t'
		   << m_iWeaponAmmos[2]    << '\t'
		   << m_iWeaponAmmos[3]    << '\t'
		   << m_iWeaponAmmos[4]    << '\t'
		   << m_iWeaponAmmos[5]    << '\t'
		   << m_iWeaponAmmos[6]    << '\t'
		   << m_iWeaponAmmos[7]    << '\t'
		   << m_iOutfits[0]        << '\t'
		   << m_iOutfits[1]        << '\t'
		   << m_iOutfits[2]        << '\t'
		   << m_iOutfits[3]        << '\t'
		   << m_iOutfits[4]        << '\t'
		   << m_iOutfits[5]        << '\t'
		   << m_iOutfits[6]        << '\t'
		   << m_iOutfits[7]        << '\t'
		   << m_iOutfitCounts[0]   << '\t'
		   << m_iOutfitCounts[1]   << '\t'
		   << m_iOutfitCounts[2]   << '\t'
		   << m_iOutfitCounts[3]   << '\t'
		   << m_iOutfitCounts[4]   << '\t'
		   << m_iOutfitCounts[5]   << '\t'
		   << m_iOutfitCounts[6]   << '\t'
		   << m_iOutfitCounts[7]   << '\t';

	PrintHex16Field(output, (char *)&m_iFlags1, '\t');
	PrintHex16Field(output, (char *)&m_iFlags2, '\t');
	PrintHex16Field(output, (char *)&m_iFlags3, '\t');

	return 1;
}

int CShipResource::LoadFromText(std::istream & input)
{
	input >> m_iCargo
		  >> m_iShields
		  >> m_iShieldRecharge
		  >> m_iArmor
		  >> m_iArmorRecharge
		  >> m_iAcceleration
		  >> m_iMaxSpeed
		  >> m_iTurning
		  >> m_iFuel
		  >> m_iFreeMass
		  >> m_iMaxGuns
		  >> m_iMaxTurrets
		  >> m_iTechLevel
		  >> m_iCost
		  >> m_iDeathDelay
		  >> m_iExplosion1
		  >> m_iExplosion2
		  >> m_iDisplayWeight
		  >> m_iMass
		  >> m_iLength
		  >> m_iCrew
		  >> m_iStrength
		  >> m_iGovernment
		  >> m_iEscapePodCount
		  >> m_iFuelRegeneration
		  >> m_iSkillVariation;

	input.ignore(1);

	ReadTextField(input, m_szAvailability, 255);
	ReadTextField(input, m_szAppearOn,     255);
	ReadTextField(input, m_szOnPurchase,   256);

	input >> m_iDeionize
		  >> m_iMaxIonization
		  >> m_iKeyCarried;

	ReadHex64Field(input, m_cContribute);
	ReadHex64Field(input, m_cRequire);

	input >> m_iBuyRandom
		  >> m_iHireRandom;

	input.ignore(1);

	ReadTextField(input, m_szOnCapture, 255);
	ReadTextField(input, m_szOnRetire,  255);
	ReadTextField(input, m_szSubtitle,   64);
	ReadTextField(input, m_szShortName,  64);
	ReadTextField(input, m_szCommName,   32);
	ReadTextField(input, m_szLongName,  128);
	ReadTextField(input, m_szMovieFile,  32);

	input >> m_iEscortAI
		  >> m_iEscortUpgradeTo
		  >> m_iEscortUpgradeCost
		  >> m_iEscortSellValue
		  >> m_iEscortType
		  >> m_iWeapons[0]
		  >> m_iWeapons[1]
		  >> m_iWeapons[2]
		  >> m_iWeapons[3]
		  >> m_iWeapons[4]
		  >> m_iWeapons[5]
		  >> m_iWeapons[6]
		  >> m_iWeapons[7]
		  >> m_iWeaponCounts[0]
		  >> m_iWeaponCounts[1]
		  >> m_iWeaponCounts[2]
		  >> m_iWeaponCounts[3]
		  >> m_iWeaponCounts[4]
		  >> m_iWeaponCounts[5]
		  >> m_iWeaponCounts[6]
		  >> m_iWeaponCounts[7]
		  >> m_iWeaponAmmos[0]
		  >> m_iWeaponAmmos[1]
		  >> m_iWeaponAmmos[2]
		  >> m_iWeaponAmmos[3]
		  >> m_iWeaponAmmos[4]
		  >> m_iWeaponAmmos[5]
		  >> m_iWeaponAmmos[6]
		  >> m_iWeaponAmmos[7]
		  >> m_iOutfits[0]
		  >> m_iOutfits[1]
		  >> m_iOutfits[2]
		  >> m_iOutfits[3]
		  >> m_iOutfits[4]
		  >> m_iOutfits[5]
		  >> m_iOutfits[6]
		  >> m_iOutfits[7]
		  >> m_iOutfitCounts[0]
		  >> m_iOutfitCounts[1]
		  >> m_iOutfitCounts[2]
		  >> m_iOutfitCounts[3]
		  >> m_iOutfitCounts[4]
		  >> m_iOutfitCounts[5]
		  >> m_iOutfitCounts[6]
		  >> m_iOutfitCounts[7];

	ReadHex16Field(input, (char *)&m_iFlags1);
	ReadHex16Field(input, (char *)&m_iFlags2);
	ReadHex16Field(input, (char *)&m_iFlags3);

	return 1;
}

int CShipResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "ship ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_SHIP_EDIT1, CCONTROL_TYPE_INT, IDS_STRING640);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_SHIP_EDIT2, CCONTROL_TYPE_INT, IDS_STRING641);
	m_controls[1].SetInt(m_iCargo);
	m_controls[2].Create(hwnd, IDC_EDIT_SHIP_EDIT3, CCONTROL_TYPE_INT, IDS_STRING642);
	m_controls[2].SetInt(m_iShields);
	m_controls[3].Create(hwnd, IDC_EDIT_SHIP_EDIT4, CCONTROL_TYPE_INT, IDS_STRING643);
	m_controls[3].SetInt(m_iShieldRecharge);
	m_controls[4].Create(hwnd, IDC_EDIT_SHIP_EDIT5, CCONTROL_TYPE_INT, IDS_STRING644);
	m_controls[4].SetInt(m_iArmor);
	m_controls[5].Create(hwnd, IDC_EDIT_SHIP_EDIT6, CCONTROL_TYPE_INT, IDS_STRING645);
	m_controls[5].SetInt(m_iArmorRecharge);
	m_controls[6].Create(hwnd, IDC_EDIT_SHIP_EDIT7, CCONTROL_TYPE_INT, IDS_STRING646);
	m_controls[6].SetInt(m_iAcceleration);
	m_controls[7].Create(hwnd, IDC_EDIT_SHIP_EDIT8, CCONTROL_TYPE_INT, IDS_STRING647);
	m_controls[7].SetInt(m_iMaxSpeed);
	m_controls[8].Create(hwnd, IDC_EDIT_SHIP_EDIT9, CCONTROL_TYPE_INT, IDS_STRING648);
	m_controls[8].SetInt(m_iTurning);
	m_controls[9].Create(hwnd, IDC_EDIT_SHIP_EDIT10, CCONTROL_TYPE_INT, IDS_STRING649);
	m_controls[9].SetInt(m_iFuel);
	m_controls[10].Create(hwnd, IDC_EDIT_SHIP_EDIT11, CCONTROL_TYPE_INT, IDS_STRING650);
	m_controls[10].SetInt(m_iFreeMass);
	m_controls[11].Create(hwnd, IDC_EDIT_SHIP_EDIT36, CCONTROL_TYPE_INT, IDS_STRING654);
	m_controls[11].SetInt(m_iMaxGuns);
	m_controls[12].Create(hwnd, IDC_EDIT_SHIP_EDIT37, CCONTROL_TYPE_INT, IDS_STRING655);
	m_controls[12].SetInt(m_iMaxTurrets);
	m_controls[13].Create(hwnd, IDC_EDIT_SHIP_EDIT38, CCONTROL_TYPE_INT, IDS_STRING656);
	m_controls[13].SetInt(m_iTechLevel);
	m_controls[14].Create(hwnd, IDC_EDIT_SHIP_EDIT39, CCONTROL_TYPE_INT, IDS_STRING657);
	m_controls[14].SetInt(m_iCost);
	m_controls[15].Create(hwnd, IDC_EDIT_SHIP_EDIT40, CCONTROL_TYPE_INT, IDS_STRING658);
	m_controls[15].SetInt(m_iDeathDelay);
	m_controls[16].Create(hwnd, IDC_EDIT_SHIP_EDIT41, CCONTROL_TYPE_INT, IDS_STRING659);
	m_controls[16].SetInt(m_iExplosion1);
	m_controls[17].Create(hwnd, IDC_EDIT_SHIP_EDIT42, CCONTROL_TYPE_INT, IDS_STRING660);
	m_controls[17].SetInt(m_iExplosion2);
	m_controls[18].Create(hwnd, IDC_EDIT_SHIP_EDIT43, CCONTROL_TYPE_INT, IDS_STRING661);
	m_controls[18].SetInt(m_iDisplayWeight);
	m_controls[19].Create(hwnd, IDC_EDIT_SHIP_EDIT44, CCONTROL_TYPE_INT, IDS_STRING662);
	m_controls[19].SetInt(m_iMass);
	m_controls[20].Create(hwnd, IDC_EDIT_SHIP_EDIT45, CCONTROL_TYPE_INT, IDS_STRING663);
	m_controls[20].SetInt(m_iLength);
	m_controls[21].Create(hwnd, IDC_EDIT_SHIP_EDIT46, CCONTROL_TYPE_INT, IDS_STRING664);
	m_controls[21].SetInt(m_iCrew);
	m_controls[22].Create(hwnd, IDC_EDIT_SHIP_EDIT47, CCONTROL_TYPE_INT, IDS_STRING665);
	m_controls[22].SetInt(m_iStrength);
	m_controls[23].Create(hwnd, IDC_EDIT_SHIP_EDIT48, CCONTROL_TYPE_INT, IDS_STRING666);
	m_controls[23].SetInt(m_iGovernment);
	m_controls[24].Create(hwnd, IDC_EDIT_SHIP_EDIT49, CCONTROL_TYPE_INT, IDS_STRING667);
	m_controls[24].SetInt(m_iEscapePodCount);
	m_controls[25].Create(hwnd, IDC_EDIT_SHIP_EDIT50, CCONTROL_TYPE_INT, IDS_STRING668);
	m_controls[25].SetInt(m_iFuelRegeneration);
	m_controls[26].Create(hwnd, IDC_EDIT_SHIP_EDIT51, CCONTROL_TYPE_INT, IDS_STRING669);
	m_controls[26].SetInt(m_iSkillVariation);
	m_controls[27].Create(hwnd, IDC_EDIT_SHIP_EDIT68, CCONTROL_TYPE_STR255, IDS_STRING673);
	m_controls[27].SetString(m_szAvailability);
	m_controls[28].Create(hwnd, IDC_EDIT_SHIP_EDIT69, CCONTROL_TYPE_STR255, IDS_STRING674);
	m_controls[28].SetString(m_szAppearOn);
	m_controls[29].Create(hwnd, IDC_EDIT_SHIP_EDIT70, CCONTROL_TYPE_STR256, IDS_STRING675);
	m_controls[29].SetString(m_szOnPurchase);
	m_controls[30].Create(hwnd, IDC_EDIT_SHIP_EDIT71, CCONTROL_TYPE_INT, IDS_STRING676);
	m_controls[30].SetInt(m_iDeionize);
	m_controls[31].Create(hwnd, IDC_EDIT_SHIP_EDIT72, CCONTROL_TYPE_INT, IDS_STRING677);
	m_controls[31].SetInt(m_iMaxIonization);
	m_controls[32].Create(hwnd, IDC_EDIT_SHIP_EDIT73, CCONTROL_TYPE_INT, IDS_STRING678);
	m_controls[32].SetInt(m_iKeyCarried);
	m_controls[33].Create(hwnd, IDC_EDIT_SHIP_EDIT74, CCONTROL_TYPE_HEXINT64, IDS_STRING679);
	m_controls[33].SetString(m_cContribute);
	m_controls[34].Create(hwnd, IDC_EDIT_SHIP_EDIT75, CCONTROL_TYPE_HEXINT64, IDS_STRING680);
	m_controls[34].SetString(m_cRequire);
	m_controls[35].Create(hwnd, IDC_EDIT_SHIP_EDIT76, CCONTROL_TYPE_INT, IDS_STRING681);
	m_controls[35].SetInt(m_iBuyRandom);
	m_controls[36].Create(hwnd, IDC_EDIT_SHIP_EDIT77, CCONTROL_TYPE_INT, IDS_STRING682);
	m_controls[36].SetInt(m_iHireRandom);
	m_controls[37].Create(hwnd, IDC_EDIT_SHIP_EDIT78, CCONTROL_TYPE_STR255, IDS_STRING683);
	m_controls[37].SetString(m_szOnCapture);
	m_controls[38].Create(hwnd, IDC_EDIT_SHIP_EDIT79, CCONTROL_TYPE_STR255, IDS_STRING684);
	m_controls[38].SetString(m_szOnRetire);
	m_controls[39].Create(hwnd, IDC_EDIT_SHIP_EDIT80, CCONTROL_TYPE_STR64, IDS_STRING685);
	m_controls[39].SetString(m_szSubtitle);
	m_controls[40].Create(hwnd, IDC_EDIT_SHIP_EDIT81, CCONTROL_TYPE_STR64, IDS_STRING686);
	m_controls[40].SetString(m_szShortName);
	m_controls[41].Create(hwnd, IDC_EDIT_SHIP_EDIT82, CCONTROL_TYPE_STR32, IDS_STRING687);
	m_controls[41].SetString(m_szCommName);
	m_controls[42].Create(hwnd, IDC_EDIT_SHIP_EDIT83, CCONTROL_TYPE_STR128, IDS_STRING688);
	m_controls[42].SetString(m_szLongName);
	m_controls[43].Create(hwnd, IDC_EDIT_SHIP_EDIT89, CCONTROL_TYPE_STR32, IDS_STRING689);
	m_controls[43].SetString(m_szMovieFile);
	m_controls[44].Create(hwnd, IDC_EDIT_SHIP_COMBO1, CCONTROL_TYPE_COMBOBOX, IDS_STRING690);
	m_controls[44].SetComboStrings(NUM_AITYPE_CHOICES, g_szAITypeChoices);
	m_controls[44].SetInt(m_iEscortAI - 1);
	m_controls[45].Create(hwnd, IDC_EDIT_SHIP_EDIT85, CCONTROL_TYPE_INT, IDS_STRING691);
	m_controls[45].SetInt(m_iEscortUpgradeTo);
	m_controls[46].Create(hwnd, IDC_EDIT_SHIP_EDIT86, CCONTROL_TYPE_INT, IDS_STRING692);
	m_controls[46].SetInt(m_iEscortUpgradeCost);
	m_controls[47].Create(hwnd, IDC_EDIT_SHIP_EDIT87, CCONTROL_TYPE_INT, IDS_STRING693);
	m_controls[47].SetInt(m_iEscortSellValue);
	m_controls[48].Create(hwnd, IDC_EDIT_SHIP_COMBO2, CCONTROL_TYPE_COMBOBOX, IDS_STRING694);
	m_controls[48].SetComboStrings(NUM_SHIP_ESCORTTYPE_CHOICES, g_szShipEscortTypeChoices);
	m_controls[48].SetInt(m_iEscortType + 1);
	m_controls[49].Create(hwnd, IDC_EDIT_SHIP_EDIT12, CCONTROL_TYPE_INT, IDS_STRING651);
	m_controls[49].SetInt(m_iWeapons[0]);
	m_controls[50].Create(hwnd, IDC_EDIT_SHIP_EDIT13, CCONTROL_TYPE_INT, IDS_STRING651);
	m_controls[50].SetInt(m_iWeapons[1]);
	m_controls[51].Create(hwnd, IDC_EDIT_SHIP_EDIT14, CCONTROL_TYPE_INT, IDS_STRING651);
	m_controls[51].SetInt(m_iWeapons[2]);
	m_controls[52].Create(hwnd, IDC_EDIT_SHIP_EDIT15, CCONTROL_TYPE_INT, IDS_STRING651);
	m_controls[52].SetInt(m_iWeapons[3]);
	m_controls[53].Create(hwnd, IDC_EDIT_SHIP_EDIT16, CCONTROL_TYPE_INT, IDS_STRING651);
	m_controls[53].SetInt(m_iWeapons[4]);
	m_controls[54].Create(hwnd, IDC_EDIT_SHIP_EDIT17, CCONTROL_TYPE_INT, IDS_STRING651);
	m_controls[54].SetInt(m_iWeapons[5]);
	m_controls[55].Create(hwnd, IDC_EDIT_SHIP_EDIT18, CCONTROL_TYPE_INT, IDS_STRING651);
	m_controls[55].SetInt(m_iWeapons[6]);
	m_controls[56].Create(hwnd, IDC_EDIT_SHIP_EDIT19, CCONTROL_TYPE_INT, IDS_STRING651);
	m_controls[56].SetInt(m_iWeapons[7]);
	m_controls[57].Create(hwnd, IDC_EDIT_SHIP_EDIT20, CCONTROL_TYPE_INT, IDS_STRING652);
	m_controls[57].SetInt(m_iWeaponCounts[0]);
	m_controls[58].Create(hwnd, IDC_EDIT_SHIP_EDIT21, CCONTROL_TYPE_INT, IDS_STRING652);
	m_controls[58].SetInt(m_iWeaponCounts[1]);
	m_controls[59].Create(hwnd, IDC_EDIT_SHIP_EDIT22, CCONTROL_TYPE_INT, IDS_STRING652);
	m_controls[59].SetInt(m_iWeaponCounts[2]);
	m_controls[60].Create(hwnd, IDC_EDIT_SHIP_EDIT23, CCONTROL_TYPE_INT, IDS_STRING652);
	m_controls[60].SetInt(m_iWeaponCounts[3]);
	m_controls[61].Create(hwnd, IDC_EDIT_SHIP_EDIT24, CCONTROL_TYPE_INT, IDS_STRING652);
	m_controls[61].SetInt(m_iWeaponCounts[4]);
	m_controls[62].Create(hwnd, IDC_EDIT_SHIP_EDIT25, CCONTROL_TYPE_INT, IDS_STRING652);
	m_controls[62].SetInt(m_iWeaponCounts[5]);
	m_controls[63].Create(hwnd, IDC_EDIT_SHIP_EDIT26, CCONTROL_TYPE_INT, IDS_STRING652);
	m_controls[63].SetInt(m_iWeaponCounts[6]);
	m_controls[64].Create(hwnd, IDC_EDIT_SHIP_EDIT27, CCONTROL_TYPE_INT, IDS_STRING652);
	m_controls[64].SetInt(m_iWeaponCounts[7]);
	m_controls[65].Create(hwnd, IDC_EDIT_SHIP_EDIT28, CCONTROL_TYPE_INT, IDS_STRING653);
	m_controls[65].SetInt(m_iWeaponAmmos[0]);
	m_controls[66].Create(hwnd, IDC_EDIT_SHIP_EDIT29, CCONTROL_TYPE_INT, IDS_STRING653);
	m_controls[66].SetInt(m_iWeaponAmmos[1]);
	m_controls[67].Create(hwnd, IDC_EDIT_SHIP_EDIT30, CCONTROL_TYPE_INT, IDS_STRING653);
	m_controls[67].SetInt(m_iWeaponAmmos[2]);
	m_controls[68].Create(hwnd, IDC_EDIT_SHIP_EDIT31, CCONTROL_TYPE_INT, IDS_STRING653);
	m_controls[68].SetInt(m_iWeaponAmmos[3]);
	m_controls[69].Create(hwnd, IDC_EDIT_SHIP_EDIT32, CCONTROL_TYPE_INT, IDS_STRING653);
	m_controls[69].SetInt(m_iWeaponAmmos[4]);
	m_controls[70].Create(hwnd, IDC_EDIT_SHIP_EDIT33, CCONTROL_TYPE_INT, IDS_STRING653);
	m_controls[70].SetInt(m_iWeaponAmmos[5]);
	m_controls[71].Create(hwnd, IDC_EDIT_SHIP_EDIT34, CCONTROL_TYPE_INT, IDS_STRING653);
	m_controls[71].SetInt(m_iWeaponAmmos[6]);
	m_controls[72].Create(hwnd, IDC_EDIT_SHIP_EDIT35, CCONTROL_TYPE_INT, IDS_STRING653);
	m_controls[72].SetInt(m_iWeaponAmmos[7]);
	m_controls[73].Create(hwnd, IDC_EDIT_SHIP_EDIT52, CCONTROL_TYPE_INT, IDS_STRING670);
	m_controls[73].SetInt(m_iOutfits[0]);
	m_controls[74].Create(hwnd, IDC_EDIT_SHIP_EDIT53, CCONTROL_TYPE_INT, IDS_STRING670);
	m_controls[74].SetInt(m_iOutfits[1]);
	m_controls[75].Create(hwnd, IDC_EDIT_SHIP_EDIT54, CCONTROL_TYPE_INT, IDS_STRING670);
	m_controls[75].SetInt(m_iOutfits[2]);
	m_controls[76].Create(hwnd, IDC_EDIT_SHIP_EDIT55, CCONTROL_TYPE_INT, IDS_STRING670);
	m_controls[76].SetInt(m_iOutfits[3]);
	m_controls[77].Create(hwnd, IDC_EDIT_SHIP_EDIT56, CCONTROL_TYPE_INT, IDS_STRING670);
	m_controls[77].SetInt(m_iOutfits[4]);
	m_controls[78].Create(hwnd, IDC_EDIT_SHIP_EDIT57, CCONTROL_TYPE_INT, IDS_STRING670);
	m_controls[78].SetInt(m_iOutfits[5]);
	m_controls[79].Create(hwnd, IDC_EDIT_SHIP_EDIT58, CCONTROL_TYPE_INT, IDS_STRING670);
	m_controls[79].SetInt(m_iOutfits[6]);
	m_controls[80].Create(hwnd, IDC_EDIT_SHIP_EDIT59, CCONTROL_TYPE_INT, IDS_STRING670);
	m_controls[80].SetInt(m_iOutfits[7]);
	m_controls[81].Create(hwnd, IDC_EDIT_SHIP_EDIT60, CCONTROL_TYPE_INT, IDS_STRING672);
	m_controls[81].SetInt(m_iOutfitCounts[0]);
	m_controls[82].Create(hwnd, IDC_EDIT_SHIP_EDIT61, CCONTROL_TYPE_INT, IDS_STRING672);
	m_controls[82].SetInt(m_iOutfitCounts[1]);
	m_controls[83].Create(hwnd, IDC_EDIT_SHIP_EDIT62, CCONTROL_TYPE_INT, IDS_STRING672);
	m_controls[83].SetInt(m_iOutfitCounts[2]);
	m_controls[84].Create(hwnd, IDC_EDIT_SHIP_EDIT63, CCONTROL_TYPE_INT, IDS_STRING672);
	m_controls[84].SetInt(m_iOutfitCounts[3]);
	m_controls[85].Create(hwnd, IDC_EDIT_SHIP_EDIT64, CCONTROL_TYPE_INT, IDS_STRING672);
	m_controls[85].SetInt(m_iOutfitCounts[4]);
	m_controls[86].Create(hwnd, IDC_EDIT_SHIP_EDIT65, CCONTROL_TYPE_INT, IDS_STRING672);
	m_controls[86].SetInt(m_iOutfitCounts[5]);
	m_controls[87].Create(hwnd, IDC_EDIT_SHIP_EDIT66, CCONTROL_TYPE_INT, IDS_STRING672);
	m_controls[87].SetInt(m_iOutfitCounts[6]);
	m_controls[88].Create(hwnd, IDC_EDIT_SHIP_EDIT67, CCONTROL_TYPE_INT, IDS_STRING672);
	m_controls[88].SetInt(m_iOutfitCounts[7]);
	m_controls[89].Create(hwnd, IDC_EDIT_SHIP_CHECK1, CCONTROL_TYPE_CHECK, IDS_STRING695);
	m_controls[89].SetInt(m_iFlags1 & 0x0001);
	m_controls[90].Create(hwnd, IDC_EDIT_SHIP_CHECK2, CCONTROL_TYPE_CHECK, IDS_STRING696);
	m_controls[90].SetInt(m_iFlags1 & 0x0002);
	m_controls[91].Create(hwnd, IDC_EDIT_SHIP_CHECK3, CCONTROL_TYPE_CHECK, IDS_STRING697);
	m_controls[91].SetInt(m_iFlags1 & 0x0004);
	m_controls[92].Create(hwnd, IDC_EDIT_SHIP_CHECK4, CCONTROL_TYPE_CHECK, IDS_STRING698);
	m_controls[92].SetInt(m_iFlags1 & 0x0008);
	m_controls[93].Create(hwnd, IDC_EDIT_SHIP_CHECK5, CCONTROL_TYPE_CHECK, IDS_STRING699);
	m_controls[93].SetInt(m_iFlags1 & 0x0010);
	m_controls[94].Create(hwnd, IDC_EDIT_SHIP_CHECK6, CCONTROL_TYPE_CHECK, IDS_STRING700);
	m_controls[94].SetInt(m_iFlags1 & 0x0020);
	m_controls[95].Create(hwnd, IDC_EDIT_SHIP_CHECK7, CCONTROL_TYPE_CHECK, IDS_STRING701);
	m_controls[95].SetInt(m_iFlags1 & 0x0040);
	m_controls[96].Create(hwnd, IDC_EDIT_SHIP_CHECK8, CCONTROL_TYPE_CHECK, IDS_STRING702);
	m_controls[96].SetInt(m_iFlags1 & 0x0100);
	m_controls[97].Create(hwnd, IDC_EDIT_SHIP_CHECK9, CCONTROL_TYPE_CHECK, IDS_STRING703);
	m_controls[97].SetInt(m_iFlags1 & 0x0200);
	m_controls[98].Create(hwnd, IDC_EDIT_SHIP_CHECK10, CCONTROL_TYPE_CHECK, IDS_STRING704);
	m_controls[98].SetInt(m_iFlags1 & 0x0400);
	m_controls[99].Create(hwnd, IDC_EDIT_SHIP_CHECK11, CCONTROL_TYPE_CHECK, IDS_STRING705);
	m_controls[99].SetInt(m_iFlags1 & 0x1000);
	m_controls[100].Create(hwnd, IDC_EDIT_SHIP_CHECK12, CCONTROL_TYPE_CHECK, IDS_STRING706);
	m_controls[100].SetInt(m_iFlags1 & 0x2000);
	m_controls[101].Create(hwnd, IDC_EDIT_SHIP_CHECK13, CCONTROL_TYPE_CHECK, IDS_STRING707);
	m_controls[101].SetInt(m_iFlags1 & 0x4000);
	m_controls[102].Create(hwnd, IDC_EDIT_SHIP_CHECK14, CCONTROL_TYPE_CHECK, IDS_STRING708);
	m_controls[102].SetInt(m_iFlags1 & 0x8000);
	m_controls[103].Create(hwnd, IDC_EDIT_SHIP_CHECK15, CCONTROL_TYPE_CHECK, IDS_STRING709);
	m_controls[103].SetInt(m_iFlags2 & 0x0001);
	m_controls[104].Create(hwnd, IDC_EDIT_SHIP_CHECK16, CCONTROL_TYPE_CHECK, IDS_STRING710);
	m_controls[104].SetInt(m_iFlags2 & 0x0002);
	m_controls[105].Create(hwnd, IDC_EDIT_SHIP_CHECK17, CCONTROL_TYPE_CHECK, IDS_STRING711);
	m_controls[105].SetInt(m_iFlags2 & 0x0004);
	m_controls[106].Create(hwnd, IDC_EDIT_SHIP_CHECK18, CCONTROL_TYPE_CHECK, IDS_STRING712);
	m_controls[106].SetInt(m_iFlags2 & 0x0008);
	m_controls[107].Create(hwnd, IDC_EDIT_SHIP_CHECK19, CCONTROL_TYPE_CHECK, IDS_STRING713);
	m_controls[107].SetInt(m_iFlags2 & 0x0010);
	m_controls[108].Create(hwnd, IDC_EDIT_SHIP_CHECK20, CCONTROL_TYPE_CHECK, IDS_STRING714);
	m_controls[108].SetInt(m_iFlags2 & 0x0020);
	m_controls[109].Create(hwnd, IDC_EDIT_SHIP_CHECK21, CCONTROL_TYPE_CHECK, IDS_STRING715);
	m_controls[109].SetInt(m_iFlags2 & 0x0040);
	m_controls[110].Create(hwnd, IDC_EDIT_SHIP_CHECK22, CCONTROL_TYPE_CHECK, IDS_STRING716);
	m_controls[110].SetInt(m_iFlags2 & 0x0080);
	m_controls[111].Create(hwnd, IDC_EDIT_SHIP_CHECK23, CCONTROL_TYPE_CHECK, IDS_STRING717);
	m_controls[111].SetInt(m_iFlags2 & 0x0100);
	m_controls[112].Create(hwnd, IDC_EDIT_SHIP_CHECK24, CCONTROL_TYPE_CHECK, IDS_STRING718);
	m_controls[112].SetInt(m_iFlags2 & 0x0200);
	m_controls[113].Create(hwnd, IDC_EDIT_SHIP_CHECK25, CCONTROL_TYPE_CHECK, IDS_STRING719);
	m_controls[113].SetInt(m_iFlags2 & 0x0400);
	m_controls[114].Create(hwnd, IDC_EDIT_SHIP_CHECK26, CCONTROL_TYPE_CHECK, IDS_STRING720);
	m_controls[114].SetInt(m_iFlags2 & 0x0800);
	m_controls[115].Create(hwnd, IDC_EDIT_SHIP_CHECK27, CCONTROL_TYPE_CHECK, IDS_STRING721);
	m_controls[115].SetInt(m_iFlags2 & 0x1000);
	m_controls[116].Create(hwnd, IDC_EDIT_SHIP_CHECK28, CCONTROL_TYPE_CHECK, IDS_STRING722);
	m_controls[116].SetInt(m_iFlags2 & 0x2000);
	m_controls[117].Create(hwnd, IDC_EDIT_SHIP_CHECK29, CCONTROL_TYPE_CHECK, IDS_STRING723);
	m_controls[117].SetInt(m_iFlags2 & 0x4000);
	m_controls[118].Create(hwnd, IDC_EDIT_SHIP_CHECK30, CCONTROL_TYPE_CHECK, IDS_STRING724);
	m_controls[118].SetInt(m_iFlags3 & 0x0001);
	m_controls[119].Create(hwnd, IDC_EDIT_SHIP_CHECK31, CCONTROL_TYPE_CHECK, IDS_STRING725);
	m_controls[119].SetInt(m_iFlags3 & 0x0002);
	m_controls[120].Create(hwnd, IDC_EDIT_SHIP_CHECK32, CCONTROL_TYPE_CHECK, IDS_STRING726);
	m_controls[120].SetInt(m_iFlags3 & 0x0010);
	m_controls[121].Create(hwnd, IDC_EDIT_SHIP_CHECK33, CCONTROL_TYPE_CHECK, IDS_STRING727);
	m_controls[121].SetInt(m_iFlags3 & 0x0020);
	m_controls[122].Create(hwnd, IDC_EDIT_SHIP_CHECK34, CCONTROL_TYPE_CHECK, IDS_STRING728);
	m_controls[122].SetInt(m_iFlags3 & 0x0040);
	m_controls[123].Create(hwnd, IDC_EDIT_SHIP_CHECK35, CCONTROL_TYPE_CHECK, IDS_STRING729);
	m_controls[123].SetInt(m_iFlags3 & 0x0100);
	m_controls[124].Create(hwnd, IDC_EDIT_SHIP_CHECK36, CCONTROL_TYPE_CHECK, IDS_STRING730);
	m_controls[124].SetInt(m_iFlags3 & 0x0200);
	m_controls[125].Create(hwnd, IDC_EDIT_SHIP_CHECK37, CCONTROL_TYPE_CHECK, IDS_STRING731);
	m_controls[125].SetInt(m_iFlags3 & 0x4000);
	m_controls[126].Create(hwnd, IDC_EDIT_SHIP_EDIT90, CCONTROL_TYPE_STR256, IDS_STRING732);
	m_controls[126].SetString(m_szName);

	std::string s = m_szName;
	auto sc = s.find(';'), col = s.find(':', sc);
	if (m_iDiffID == 0 && sc != std::string::npos && col != std::string::npos) {
		try { 
			m_iDiffID = std::stoi(s.substr(col + 1));
			std::vector<CNovaResource*> values = Workspace::All(CNR_TYPE_SHIP);
			for (auto i = 0; i < values.size(); ++i)
				if (values[i]->GetID() == m_iDiffID) {
					m_iDiffID = i;
					break;
				}
		} catch (...) {}
	}

	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHIP_TEXT77), ToString(m_iID).c_str());
	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHIP_TEXT78), ToString(m_iID + 3000 - 128).c_str());
	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHIP_TEXT79), ToString(m_iID + 5000 - 128).c_str());
	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHIP_TEXT80), ToString(m_iID + 13000 - 128).c_str());
	Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHIP_TEXT81), ToString(m_iID + 14000 - 128).c_str());

	return 1;
}

int CShipResource::CloseAndSave(void)
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

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[126].GetString()) != 0))
		iIDOrNameChanged = 1;

	m_iID               = m_controls[0].GetInt();

	m_iCargo            = m_controls[1].GetInt();

	m_iShields          = m_controls[2].GetInt();
	m_iShieldRecharge   = m_controls[3].GetInt();
	m_iArmor            = m_controls[4].GetInt();
	m_iArmorRecharge    = m_controls[5].GetInt();

	m_iAcceleration     = m_controls[6].GetInt();
	m_iMaxSpeed         = m_controls[7].GetInt();
	m_iTurning          = m_controls[8].GetInt();

	m_iFuel             = m_controls[9].GetInt();

	m_iFreeMass         = m_controls[10].GetInt();

	m_iMaxGuns          = m_controls[11].GetInt();
	m_iMaxTurrets       = m_controls[12].GetInt();

	m_iTechLevel        = m_controls[13].GetInt();

	m_iCost             = m_controls[14].GetInt();

	m_iDeathDelay       = m_controls[15].GetInt();
	m_iExplosion1       = m_controls[16].GetInt();
	m_iExplosion2       = m_controls[17].GetInt();

	m_iDisplayWeight    = m_controls[18].GetInt();

	m_iMass             = m_controls[19].GetInt();
	m_iLength           = m_controls[20].GetInt();
	m_iCrew             = m_controls[21].GetInt();
	m_iStrength         = m_controls[22].GetInt();

	m_iGovernment       = m_controls[23].GetInt();

	m_iEscapePodCount   = m_controls[24].GetInt();

	m_iFuelRegeneration = m_controls[25].GetInt();

	m_iSkillVariation   = m_controls[26].GetInt();

	strcpy(m_szAvailability, m_controls[27].GetString());
	strcpy(m_szAppearOn,     m_controls[28].GetString());
	strcpy(m_szOnPurchase,   m_controls[29].GetString());

	m_iDeionize      = m_controls[30].GetInt();
	m_iMaxIonization = m_controls[31].GetInt();

	m_iKeyCarried = m_controls[32].GetInt();

	memcpy(m_cContribute, m_controls[33].GetString(), 8 * sizeof(char));
	memcpy(m_cRequire,    m_controls[34].GetString(), 8 * sizeof(char));

	m_iBuyRandom  = m_controls[35].GetInt();
	m_iHireRandom = m_controls[36].GetInt();

	strcpy(m_szOnCapture, m_controls[37].GetString());
	strcpy(m_szOnRetire,  m_controls[38].GetString());

	strcpy(m_szSubtitle,  m_controls[39].GetString());
	strcpy(m_szShortName, m_controls[40].GetString());
	strcpy(m_szCommName,  m_controls[41].GetString());
	strcpy(m_szLongName,  m_controls[42].GetString());

	strcpy(m_szMovieFile, m_controls[43].GetString());

	m_iEscortAI          = m_controls[44].GetInt() + 1;
	m_iEscortUpgradeTo   = m_controls[45].GetInt();
	m_iEscortUpgradeCost = m_controls[46].GetInt();
	m_iEscortSellValue   = m_controls[47].GetInt();
	m_iEscortType        = m_controls[48].GetInt() - 1;

	m_iWeapons[0]      = m_controls[49].GetInt();
	m_iWeapons[1]      = m_controls[50].GetInt();
	m_iWeapons[2]      = m_controls[51].GetInt();
	m_iWeapons[3]      = m_controls[52].GetInt();
	m_iWeapons[4]      = m_controls[53].GetInt();
	m_iWeapons[5]      = m_controls[54].GetInt();
	m_iWeapons[6]      = m_controls[55].GetInt();
	m_iWeapons[7]      = m_controls[56].GetInt();

	m_iWeaponCounts[0] = m_controls[57].GetInt();
	m_iWeaponCounts[1] = m_controls[58].GetInt();
	m_iWeaponCounts[2] = m_controls[59].GetInt();
	m_iWeaponCounts[3] = m_controls[60].GetInt();
	m_iWeaponCounts[4] = m_controls[61].GetInt();
	m_iWeaponCounts[5] = m_controls[62].GetInt();
	m_iWeaponCounts[6] = m_controls[63].GetInt();
	m_iWeaponCounts[7] = m_controls[64].GetInt();

	m_iWeaponAmmos[0]  = m_controls[65].GetInt();
	m_iWeaponAmmos[1]  = m_controls[66].GetInt();
	m_iWeaponAmmos[2]  = m_controls[67].GetInt();
	m_iWeaponAmmos[3]  = m_controls[68].GetInt();
	m_iWeaponAmmos[4]  = m_controls[69].GetInt();
	m_iWeaponAmmos[5]  = m_controls[70].GetInt();
	m_iWeaponAmmos[6]  = m_controls[71].GetInt();
	m_iWeaponAmmos[7]  = m_controls[72].GetInt();

	m_iOutfits[0]      = m_controls[73].GetInt();
	m_iOutfits[1]      = m_controls[74].GetInt();
	m_iOutfits[2]      = m_controls[75].GetInt();
	m_iOutfits[3]      = m_controls[76].GetInt();
	m_iOutfits[4]      = m_controls[77].GetInt();
	m_iOutfits[5]      = m_controls[78].GetInt();
	m_iOutfits[6]      = m_controls[79].GetInt();
	m_iOutfits[7]      = m_controls[80].GetInt();

	m_iOutfitCounts[0] = m_controls[81].GetInt();
	m_iOutfitCounts[1] = m_controls[82].GetInt();
	m_iOutfitCounts[2] = m_controls[83].GetInt();
	m_iOutfitCounts[3] = m_controls[84].GetInt();
	m_iOutfitCounts[4] = m_controls[85].GetInt();
	m_iOutfitCounts[5] = m_controls[86].GetInt();
	m_iOutfitCounts[6] = m_controls[87].GetInt();
	m_iOutfitCounts[7] = m_controls[88].GetInt();

	m_iFlags1 = 0x0000;
	m_iFlags2 = 0x0000;
	m_iFlags3 = 0x0000;

	m_iFlags1 |= m_controls[89].GetInt() << 0;
	m_iFlags1 |= m_controls[90].GetInt() << 1;
	m_iFlags1 |= m_controls[91].GetInt() << 2;
	m_iFlags1 |= m_controls[92].GetInt() << 3;
	m_iFlags1 |= m_controls[93].GetInt() << 4;
	m_iFlags1 |= m_controls[94].GetInt() << 5;
	m_iFlags1 |= m_controls[95].GetInt() << 6;
	m_iFlags1 |= m_controls[96].GetInt() << 8;
	m_iFlags1 |= m_controls[97].GetInt() << 9;
	m_iFlags1 |= m_controls[98].GetInt() << 10;
	m_iFlags1 |= m_controls[99].GetInt() << 12;
	m_iFlags1 |= m_controls[100].GetInt() << 13;
	m_iFlags1 |= m_controls[101].GetInt() << 14;
	m_iFlags1 |= m_controls[102].GetInt() << 15;

	m_iFlags2 |= m_controls[103].GetInt() << 0;
	m_iFlags2 |= m_controls[104].GetInt() << 1;
	m_iFlags2 |= m_controls[105].GetInt() << 2;
	m_iFlags2 |= m_controls[106].GetInt() << 3;
	m_iFlags2 |= m_controls[107].GetInt() << 4;
	m_iFlags2 |= m_controls[108].GetInt() << 5;
	m_iFlags2 |= m_controls[109].GetInt() << 6;
	m_iFlags2 |= m_controls[110].GetInt() << 7;
	m_iFlags2 |= m_controls[111].GetInt() << 8;
	m_iFlags2 |= m_controls[112].GetInt() << 9;
	m_iFlags2 |= m_controls[113].GetInt() << 10;
	m_iFlags2 |= m_controls[114].GetInt() << 11;
	m_iFlags2 |= m_controls[115].GetInt() << 12;
	m_iFlags2 |= m_controls[116].GetInt() << 13;
	m_iFlags2 |= m_controls[117].GetInt() << 14;

	m_iFlags3 |= m_controls[118].GetInt() << 0;
	m_iFlags3 |= m_controls[119].GetInt() << 1;
	m_iFlags3 |= m_controls[120].GetInt() << 4;
	m_iFlags3 |= m_controls[121].GetInt() << 5;
	m_iFlags3 |= m_controls[122].GetInt() << 6;
	m_iFlags3 |= m_controls[123].GetInt() << 8;
	m_iFlags3 |= m_controls[124].GetInt() << 9;
	m_iFlags3 |= m_controls[125].GetInt() << 14;

	strcpy(m_szName, m_controls[126].GetString());

	int i;

	for(i = 0; i < NUM_SHIP_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CShipResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_SHIP_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CShipResource::ShipDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CShipResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CShipResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_SHIP_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_SHIP_OK)
			{
				pResource->CloseAndSave();
			}
			else if(iControlID == IDC_EDIT_SHIP_BUTTON1)
			{
				char cValue[8];

				memcpy(cValue, pResource->m_controls[33].GetString(), 8);

				pResource->m_bitFieldControl.DoDialog(pResource->m_pWindow, 64, cValue);

				pResource->m_controls[33].SetString(cValue);
			}
			else if(iControlID == IDC_EDIT_SHIP_BUTTON2)
			{
				char cValue[8];

				memcpy(cValue, pResource->m_controls[34].GetString(), 8);

				pResource->m_bitFieldControl.DoDialog(pResource->m_pWindow, 64, cValue);

				pResource->m_controls[34].SetString(cValue);
			}
			for (i = 0; i < NUM_SHIP_CONTROLS; i++)
			{
				if (iControlID == pResource->m_controls[i].GetControlID())
				{
					pResource->m_controls[i].ProcessMessage(iNotifyCode);

					break;
				}
			}

			if((iControlID == IDC_EDIT_SHIP_EDIT1) && (iNotifyCode == EN_CHANGE))
			{
				if((pResource->m_controls[0].GetInt() >= 128) && (pResource->m_controls[0].GetInt() < 896))
				{
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHIP_TEXT77), ToString(pResource->m_controls[0].GetInt()).c_str());
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHIP_TEXT78), ToString(pResource->m_controls[0].GetInt() + 3000 - 128).c_str());
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHIP_TEXT79), ToString(pResource->m_controls[0].GetInt() + 5000 - 128).c_str());
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHIP_TEXT80), ToString(pResource->m_controls[0].GetInt() + 13000 - 128).c_str());
					Static_SetText(GetDlgItem(hwnd, IDC_EDIT_SHIP_TEXT81), ToString(pResource->m_controls[0].GetInt() + 14000 - 128).c_str());
				}
			}

			if (iControlID == IDC_EDIT_SHIP_BUTTON3 && iNotifyCode == BN_CLICKED) {
				CWindow* w = &pResource->m_wndDiff;
				w->SetDlgProc(CShipResource::DiffDlgProc);
				w->SetExtraData(0, (int)pWindow->GetExtraData(0));
				w->SetExtraData(1, (int)pWindow->GetExtraData(1));
				w->SetExtraData(2, (int)pResource);
				w->CreateAsDialog(pWindow->GetInstance(), IDD_SHIP_DIFF, 0, pWindow);
			}


			if (iNotifyCode == EN_CHANGE && pResource->m_wndDiff.GetHWND() != NULL)
				pResource->DiffUpdate();

			return TRUE;

			break;
		}
		default: { break; }
	}

	return FALSE;
}

void CShipResource::DiffOpen(void)
{
}

int CShipResource::DiffClose(void)
{
	m_iDiffID = m_diffCtrl.GetInt();
	m_diffCtrl.Destroy();
	m_wndDiff.Destroy();
	return 1;
}

BOOL CShipResource::DiffDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow* pWindow;
	CShipResource* pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if (pWindow != NULL)
		pResource = (CShipResource*)pWindow->GetExtraData(2);

	int i;

	switch (msg)
	{
	case WM_INITDIALOG:
	{
		pResource->DiffInitDialog(hwnd);
		return TRUE;
	}

	case WM_SYSCOMMAND:
	{
		if (wparam == SC_CLOSE)
		{
			pResource->DiffClose();

			return TRUE;
		}
		break;
	}

	case WM_COMMAND:
	{
		int iNotifyCode = HIWORD(wparam);
		if (LOWORD(wparam) == IDC_SHIP_DIFF_DROP1) {
			pResource->m_diffCtrl.ProcessMessage(iNotifyCode);
			if (iNotifyCode == CBN_SELCHANGE) pResource->DiffUpdate();
		}
		return TRUE;
	}

	default:
	{
		break;
	}
	}

	return FALSE;
}

std::string CShipResource::NumsToString(std::string name, int shields, int shieldReg,
	int armor, int armorReg, int fuel, int fuelReg, int ion, int ionReg, int cargo,
	int mass, int accel, int speed, int turn, int guns, int turrets, int cost,
	int weight,	int gravMass, int length, int crew, int str, int skill, short weaps[8],
	short wCnts[8], short wAmmo[8], short outfs[8], short oCnts[8]) {
	int usedMass = 0;
	long long usedCost = 0;
	int usedCargo = 0;
	std::string weapStr = "----LOADOUT (" + ToString(guns) + "[" + ToString(turrets) + "])----\n";

	auto matchingO = [](int mod, short weapId) {
		auto outfFilter = ([](int mod, short weapId) {
			return [mod, weapId](CNovaResource* o, int i) {
				auto r = (COutfResource*)o;
				for (int i = 0; i < 4; i++)
					if (r->m_iModTypes[i] == mod && r->m_iModValues[i] == weapId)
						return true;
				return false;
				};
			});
		return (COutfResource*)Workspace::FindWhere(CNR_TYPE_OUTF, outfFilter(mod, weapId));
	};

	for (int i = 0; i < 8; ++i) {
		if (weaps[i] < 128) continue;
		std::string wName = Workspace::RezStr(CNR_TYPE_WEAP, weaps[i]);
		auto r = matchingO(1, weaps[i]);
		if (r != NULL) {
			wName += "(" + ToString(r->GetID()) + ")";
			usedMass += r->m_iMass * wCnts[i];
			usedCost += r->m_iCost * wCnts[i];
		}
		weapStr += wName + " x" + ToString(wCnts[i]);
		if (wAmmo[i] > 0) {
			auto a = matchingO(3, weaps[i]);
			if (a != NULL) {
				usedMass += a->m_iMass * wAmmo[i];
				usedCost += a->m_iCost * wAmmo[i];
			}
			weapStr += " (" + ToString(wAmmo[i]) + ")";
		}
		weapStr += (i % 2 == 1) ? "\n" : "  ";
	}

	std::string outfStr = "\n----Equipment----\n";
	for (int i = 0; i < 8; ++i) {
		if (outfs[i] < 128) continue;
		COutfResource* r = (COutfResource*)Workspace::FindById(CNR_TYPE_OUTF, outfs[i]);
		std::string oName = r->GetName();
		usedMass += r->m_iMass*oCnts[i];
		usedCost += r->m_iCost*oCnts[i];
		for (int i = 0; i < 4; i++)
			if (r->m_iModTypes[i] == 2) usedCargo += r->m_iModValues[i];
		outfStr += oName + " x" + ToString(oCnts[i]);
		outfStr += (i % 2 == 1) ? "\n" : "  ";
	}

	std::string result = " ~~ " + name + "~~\n";
	result += "Shields: " + ToString(shields) + " (" + ToString(shieldReg) + "/frm)\n";
	result += "Armor: " + ToString(armor) + " (" + ToString(armorReg) + "/frm)\n";
	result += "Fuel: " + ToString(fuel) + " [" + ToString(fuel / 100) + " JMPs] (" + ToString(fuelReg) + "/frm)\n";
	result += "Ionization: " + ToString(ion) + " [" + ToString(ion / 100) + " EMPs] (" + ToString(ionReg) + "/frm)\n";

	std::string cargoStr = ((cargo < 0) ? "Fixed: " : "") + ToString(abs(cargo)+usedCargo);
	result += "Cargo: " + cargoStr + "t\n";

	result += "Mass: " + ToString(mass)+"t/"+ToString(usedMass+mass) + "t free" + "\n";
	result += "Accel: " + ToString(accel) + " [" + ToString(accel / 3) + "%]\n";
	result += "Speed: " + ToString(speed) + " [" + ToString(speed / 3) + "%]\n";
	result += "Maneuver: ~" + ToString(turn * 3) + " deg/sec\n";
	result += "Size: " + ToString(length) + "m; ";

	if (gravMass < 100) result += "Small\n";
	else if (gravMass < 200) result += "Medium\n";
	else result += "Large\n";

	result += "Crew: " + ToString(crew) + "  Str: " + ToString(str) + "  Skill: +/-"+ ToString(skill) + "%\n";
	result += weapStr + outfStr;
	auto FormatNumberShort = ([](int v) {
		char buffer[32];
		if (v >= 1'000'000'000) sprintf(buffer, "%.2fB", v / 1'000'000'000.0);
		else if (v >= 1'000'000) sprintf(buffer, "%.2fM", v / 1'000'000.0);
		else if (v >= 1'000) sprintf(buffer, "%.2fK", v / 1'000.0);
		else sprintf(buffer, "%d", v);
		return std::string(buffer);
	});
	result += "\n-----------------\n";
	result += "Cost: $" + FormatNumberShort(cost) + " [BASE: " + FormatNumberShort(cost-usedCost) + "]" + "\n"; //CALC TOTAL
	/*
	Sheilds: Val (Regen=(Val/1000)/Frame)
	Armor: Val (Regen=(Val/1000)/Frame)
	Fuel: Val[Val/100JMPs] (Regen=1/Val/Frame;3000/Val(s/jmp))
	Ion: Val[Val/100EMPs] (-Regen=Val/3000=sec)
	Cargo((if Val<0) "Fixed"): abs(Val)t/Tott
	Mass: Val/Tot(Outf+Val)
	Accel: Val [Val/300+%]
	Speed: Val [Val/300+%]
	Maneuver  ~(Val*3)deg/sec.
	Size: Valm; Valt (Small;Med;Large (<100,<200,+
	Crew: Val Str: Val Skill:+/-Val%
	----LOADOUT (Gun[Tur])----
	Name(short)xCnt(Amm?)  Name(short)xCnt(Amm?)
	Name(short)xCnt(Amm?)  Name(short)xCnt(Amm?)
	Name(short)xCnt(Amm?)  Name(short)xCnt(Amm?)
	Name(short)xCnt(Amm?)  Name(short)xCnt(Amm?)
	----Equipment----
	Outfit(short)xCnt  Outfit(short)xCnt
	Outfit(short)xCnt  Outfit(short)xCnt
	Outfit(short)xCnt  Outfit(short)xCnt
	Outfit(short)xCnt  Outfit(short)xCnt
	-----------------
	Cost: Val$([base]+Outf/Weap)
	*/
	return result;
}

void CShipResource::DiffUpdate(void) {
	//Lambda function to shorthand control access
	auto l = [ctr=m_controls](int i) { return ctr[i].GetInt(); };

	HWND ourTxt = GetDlgItem(m_wndDiff.GetHWND(), IDC_DIFF_SHIP_TEXT1);
	short weaps[8] = { l(49), l(50), l(51), l(52), l(53), l(54), l(55), l(56) };
	short wCnts[8] = { l(57), l(58), l(59), l(60), l(61), l(62), l(63), l(64) };
	short wAmmo[8] = { l(65), l(66), l(67), l(68), l(69), l(70), l(71), l(72) };
	short outfs[8] = { l(73), l(74), l(75), l(76), l(77), l(78), l(79), l(80) };
	short oCnts[8] = { l(81), l(82), l(83), l(84), l(85), l(86), l(87), l(88) };
	std::string output = NumsToString(m_controls[126].GetString(), l(2), l(3), l(4),
		l(5), l(9), l(25), l(31), l(30), l(1), l(10), l(6), l(7), l(8), l(11), l(12),
		l(14), l(18), l(19), l(20), l(21), l(22), l(26), weaps, wCnts, wAmmo, outfs, oCnts);
	Static_SetText(ourTxt, output.c_str());

	m_iDiffID = m_diffCtrl.GetInt();
	HWND enemyTxt = GetDlgItem(m_wndDiff.GetHWND(), IDC_DIFF_SHIP_TEXT3);

	CShipResource* comp = NULL;
	if (m_iDiffID > 0) comp = (CShipResource*)Workspace::FindByIdx(CNR_TYPE_SHIP, m_iDiffID);
	if (comp == NULL) comp = this;

	Static_SetText(enemyTxt, NumsToString(comp->m_szName, comp->m_iShields, comp->m_iShieldRecharge,
		comp->m_iArmor, comp->m_iArmorRecharge, comp->m_iFuel, comp->m_iFuelRegeneration, 
		comp->m_iMaxIonization, comp->m_iDeionize, comp->m_iCargo, comp->m_iFreeMass,
		comp->m_iAcceleration, comp->m_iMaxSpeed, comp->m_iTurning, comp->m_iMaxGuns,
		comp->m_iMaxTurrets, comp->m_iCost, comp->m_iDisplayWeight, comp->m_iMass,
		comp->m_iLength, comp->m_iCrew, comp->m_iStrength, comp->m_iSkillVariation,
		comp->m_iWeapons, comp->m_iWeaponCounts, comp->m_iWeaponAmmos,
		comp->m_iOutfits, comp->m_iOutfitCounts).c_str());
}

int CShipResource::DiffInitDialog(HWND hwnd)
{
	m_diffCtrl.Create(hwnd, IDC_SHIP_DIFF_DROP1, CCONTROL_TYPE_REZBOX, IDS_STRING640);
	m_diffCtrl.SetRezType(CNR_TYPE_SHIP);
	m_diffCtrl.SetInt(m_iDiffID);
	DiffUpdate();
	return 1;
}