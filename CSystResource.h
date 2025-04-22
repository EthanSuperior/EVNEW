// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CSystResource.h

#ifndef CSYSTRESOURCE_H_INCLUDED		// Prevent multiple inclusions
#define CSYSTRESOURCE_H_INCLUDED

////////////////////////////////////////////////////////////////
///////////////////////  CLASS FORWARDS  ///////////////////////
////////////////////////////////////////////////////////////////

class CSystResource;

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>

#include <string>

#include "CControl.h"
#include "CNovaResource.h"

////////////////////////////////////////////////////////////////
//////////////////////////  CONSTANTS  /////////////////////////
////////////////////////////////////////////////////////////////

constexpr int NUM_SYST_CONTROLS = 95;

constexpr int NUM_SYST_FIELDS = 78;

const std::string g_szSystFields[NUM_SYST_FIELDS] =
	{"X Position", "Y Position", "Hyperlink 1", "Hyperlink 2", "Hyperlink 3",
	 "Hyperlink 4", "Hyperlink 5", "Hyperlink 6", "Hyperlink 7", "Hyperlink 8",
	 "Hyperlink 9", "Hyperlink 10", "Hyperlink 11", "Hyperlink 12", "Hyperlink 13",
	 "Hyperlink 14", "Hyperlink 15", "Hyperlink 16", "Stellar 1", "Stellar 2",
	 "Stellar 3", "Stellar 4", "Stellar 5", "Stellar 6", "Stellar 7", "Stellar 8",
	 "Stellar 9", "Stellar 10", "Stellar 11", "Stellar 12", "Stellar 13", "Stellar 14",
	 "Stellar 15", "Stellar 16", "Dude 1", "Dude 2", "Dude 3", "Dude 4", "Dude 5",
	 "Dude 6", "Dude 7", "Dude 8", "Dude Probability 1", "Dude Probability 2",
	 "Dude Probability 3", "Dude Probability 4", "Dude Probability 5",
	 "Dude Probability 6", "Dude Probability 7", "Dude Probability 8", "Num Ships",
	 "Government", "Message Buoy", "Num Asteroids", "Interference", "Person 1",
	 "Person 2", "Person 3", "Person 4", "Person 5", "Person 6", "Person 7",
	 "Person 8", "Person Probability 1", "Person Probability 2",
	 "Person Probability 3", "Person Probability 4", "Person Probability 5",
	 "Person Probability 6", "Person Probability 7", "Person Probability 8",
	 "Visibility", "Background Color", "Murkiness", "Reinforcement Fleet",
	 "Reinforcement Time", "Reinforcement Interval", "Asteroid Types"};

////////////////////////////////////////////////////////////////
///////////////////////////  CLASSES  //////////////////////////
////////////////////////////////////////////////////////////////

class CSystResource : public CNovaResource
{
public:

	CSystResource(void);
	~CSystResource(void) override;

	int GetType(void) override;
	int GetSize(void) override;

	int GetDialogID(void) override;
	DLGPROCNOCALLBACK GetDialogProc(void) override;

	int GetNumFields(void) override;
	const std::string * GetFieldNames(void) override;

	int Initialize(HWND hwnd) override;

	int CloseAndSave(void) override;
	int CloseAndDontSave(void) override;

	int Save(char *pOutput) override;
	int Load(char *pInput, int iSize) override;

	int SaveToText(std::ostream & output) override;
	int LoadFromText(std::istream & input) override;

	static BOOL SystDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	int SwapEndians(void);

	short m_iXPosition;
	short m_iYPosition;

	short m_iHyperlinks[16];

	short m_iStellars[16];

	short m_iDudeTypes[8];
	short m_iDudeProbabilities[8];

	short m_iNumShips;

	short m_iGovernment;

	short m_iMessageBuoy;

	short m_iNumAsteroids;
	short m_iInterference;

	short m_iPersons[8];
	short m_iPersonProbabilities[8];

	char  m_szVisibility[256];

	UINT  m_iBackgroundColor;

	short m_iMurkiness;

	short m_iReinforcementFleet;
	short m_iReinforcementTime;
	short m_iReinforcementInterval;

	USHORT m_iAsteroidTypes;

	CControl m_controls[NUM_SYST_CONTROLS];
};

#endif		// #ifndef CSYSTRESOURCE_H_INCLUDED
