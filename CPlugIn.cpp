// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CPlugIn.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <iostream>
#include <fstream>

#include <algorithm>

#include "EVNEW.h"
#include "CPlugIn.h"

#include "CWindow.h"
#include "CErrorLog.h"

#include "CNovaResource.h"
#include "CBoomResource.h"
#include "CCharResource.h"
#include "CCicnResource.h"
#include "CColrResource.h"
#include "CCronResource.h"
#include "CDescResource.h"
#include "CDudeResource.h"
#include "CFletResource.h"
#include "CGovtResource.h"
#include "CIntfResource.h"
#include "CJunkResource.h"
#include "CMisnResource.h"
#include "CNebuResource.h"
#include "COopsResource.h"
#include "COutfResource.h"
#include "CPersResource.h"
#include "CPictResource.h"
#include "CRankResource.h"
#include "CRLEResource.h"
#include "CRoidResource.h"
#include "CShanResource.h"
#include "CShipResource.h"
#include "CSndResource.h"
#include "CSpinResource.h"
#include "CSpobResource.h"
#include "CStrResource.h"
#include "CStrlResource.h"
#include "CSystResource.h"
#include "CWeapResource.h"
#include "CUnkResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CPlugIn::CPlugIn(void)
{
	strcpy(m_szFilename, "");
	strcpy(m_szFilePath, "C:\\");
	strcpy(m_szFilenameNoPath, "Untitled.rez");

	m_iSaveAsText = 0;

	m_iFileOffset = 0;

	m_vResources.resize(NUM_RESOURCE_TYPES + 1);

	m_iShowErrorMessages = 1;
	m_iShowProgressBar   = 1;

	m_iCicnSave = 1;
	strcpy(m_szCicnSubdirectory, "Cicns");
	strcpy(m_szCicnFilenamePrefix, "cicn");
	strcpy(m_szCicnMaskSubdirectory, "Cicns");
	strcpy(m_szCicnMaskFilenamePrefix, "cicnmask");

	m_iPictSave = 1;
	strcpy(m_szPictSubdirectory, "Picts");
	strcpy(m_szPictFilenamePrefix, "pict");
	m_iPictImageFileType = 0;		// .bmp

	m_iRle8Save = 1;
	strcpy(m_szRle8Subdirectory, "Rle8s");
	strcpy(m_szRle8FilenamePrefix, "rle8_");
	strcpy(m_szRle8MaskSubdirectory, "Rle8s");
	strcpy(m_szRle8MaskFilenamePrefix, "rle8mask");
	m_iRle8ImageFileType = 0;		// .bmp
	m_iRle8MaskFileType  = 0;		// .bmp
	m_iRle8FramesPerRow  = 6;

	m_iRleDSave = 1;
	strcpy(m_szRleDSubdirectory, "RleDs");
	strcpy(m_szRleDFilenamePrefix, "rleD_");
	strcpy(m_szRleDMaskSubdirectory, "RleDs");
	strcpy(m_szRleDMaskFilenamePrefix, "rleDmask");
	m_iRleDImageFileType = 0;		// .bmp
	m_iRleDMaskFileType  = 0;		// .bmp
	m_iRleDFramesPerRow  = 6;

	m_iSndSave = 1;
	strcpy(m_szSndSubdirectory, "Sounds");
	strcpy(m_szSndFilenamePrefix, "snd");
}

CPlugIn::~CPlugIn(void)
{
	Clear();
}

char * CPlugIn::GetFilename(void)
{
	return m_szFilename;
}

char * CPlugIn::GetFilenameNoPath(void)
{
	return m_szFilenameNoPath;
}

int CPlugIn::GetCurFileOffset(void)
{
	return m_iFileOffset;
}

int CPlugIn::SetFilename(const char *szFilename)
{
	strcpy(m_szFilename, szFilename);

	char *pExtension = strrchr(m_szFilename, '.');

	if(pExtension == NULL)
		pExtension = m_szFilename;
	else
		pExtension++;

	if(strcmp(pExtension, "rez") == 0)
		m_iSaveAsText = 0;
	else
		m_iSaveAsText = 1;

	char *pLastSlash = strrchr(m_szFilename, '\\');

	if(pLastSlash == NULL)
	{
		pLastSlash = m_szFilename;

		strcpy(m_szFilePath, "C:\\");
	}
	else
	{
		pLastSlash++;

		strcpy(m_szFilePath, m_szFilename);

		m_szFilePath[pLastSlash - m_szFilename] = '\0';
	}

	strcpy(m_szFilenameNoPath, pLastSlash);

	return 1;
}

int CPlugIn::Clear(void)
{
	int i, j;

	for(i = 0; i < m_vResources.size(); i++)
	{
		for(j = 0; j < m_vResources[i].size(); j++)
			delete m_vResources[i][j];

		m_vResources[i].clear();
	}

	return 1;
}

int CPlugIn::ClearFilename(void)
{
	strcpy(m_szFilename, "");
	strcpy(m_szFilePath, "C:\\");
	strcpy(m_szFilenameNoPath, "Untitled.rez");

	m_iSaveAsText = 0;

	m_iFileOffset = 0;

	return 1;
}

int CPlugIn::SetOptions(int iShowErrorMessages, int iShowProgressBar)
{
	m_iShowErrorMessages = iShowErrorMessages;
	m_iShowProgressBar   = iShowProgressBar;

	return 1;
}

int CPlugIn::SetCicnSaveOptions(int iSave, char *szSubdirectory, char *szFilenamePrefix, char *szMaskSubdirectory, char *szMaskFilenamePrefix)
{
	m_iCicnSave = iSave;

	strcpy(m_szCicnSubdirectory,       szSubdirectory);
	strcpy(m_szCicnFilenamePrefix,     szFilenamePrefix);
	strcpy(m_szCicnMaskSubdirectory,   szMaskSubdirectory);
	strcpy(m_szCicnMaskFilenamePrefix, szMaskFilenamePrefix);

	return 1;
}

int CPlugIn::SetPictSaveOptions(int iSave, char *szSubdirectory, char *szFilenamePrefix, int iImageFileType)
{
	m_iPictSave = iSave;

	strcpy(m_szPictSubdirectory,   szSubdirectory);
	strcpy(m_szPictFilenamePrefix, szFilenamePrefix);

	m_iPictImageFileType = iImageFileType;

	return 1;
}

int CPlugIn::SetRle8SaveOptions(int iSave, char *szSubdirectory, char *szFilenamePrefix, char *szMaskSubdirectory, char *szMaskFilenamePrefix, int iImageFileType, int iMaskFileType, int iFramesPerRow)
{
	m_iRle8Save = iSave;

	strcpy(m_szRle8Subdirectory,       szSubdirectory);
	strcpy(m_szRle8FilenamePrefix,     szFilenamePrefix);
	strcpy(m_szRle8MaskSubdirectory,   szMaskSubdirectory);
	strcpy(m_szRle8MaskFilenamePrefix, szMaskFilenamePrefix);

	m_iRle8ImageFileType = iImageFileType;
	m_iRle8MaskFileType  = iMaskFileType;
	m_iRle8FramesPerRow  = iFramesPerRow;

	return 1;
}

int CPlugIn::SetRleDSaveOptions(int iSave, char *szSubdirectory, char *szFilenamePrefix, char *szMaskSubdirectory, char *szMaskFilenamePrefix, int iImageFileType, int iMaskFileType, int iFramesPerRow)
{
	m_iRleDSave = iSave;

	strcpy(m_szRleDSubdirectory,       szSubdirectory);
	strcpy(m_szRleDFilenamePrefix,     szFilenamePrefix);
	strcpy(m_szRleDMaskSubdirectory,   szMaskSubdirectory);
	strcpy(m_szRleDMaskFilenamePrefix, szMaskFilenamePrefix);

	m_iRleDImageFileType = iImageFileType;
	m_iRleDMaskFileType  = iMaskFileType;
	m_iRleDFramesPerRow  = iFramesPerRow;

	return 1;
}

int CPlugIn::SetSndSaveOptions(int iSave, char *szSubdirectory, char *szFilenamePrefix)
{
	m_iSndSave = iSave;

	strcpy(m_szSndSubdirectory,   szSubdirectory);
	strcpy(m_szSndFilenamePrefix, szFilenamePrefix);

	return 1;
}

int CPlugIn::Load(char *szFilename, CWindow *pWndParent)
{
	SetFilename(szFilename);

	int iError = 0;

	CErrorLog *pLog = CErrorLog::GetCurrentErrorLog();

	std::ifstream filein;

	int iOpenFlags = std::ios::in;

	if(m_iSaveAsText == 0)
		iOpenFlags |= std::ios::binary;

	filein.open(m_szFilename, iOpenFlags);

	std::string szBuffer;

	if(!filein.is_open())
	{
		szBuffer = "Error: Unable to open file \"";
		szBuffer += m_szFilename;
		szBuffer += "\"!";

		if(m_iShowErrorMessages)
			MessageBox(pWndParent->GetHWND(), szBuffer.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		*pLog << szBuffer << CErrorLog::endl;

		return -1;
	}

	int i, j, k;

	char c;

	char szResourceType[256];

	short iID;

	char szResourceName[256];

	char szJunk[16];

	m_iFileOffset = 0;

	if(m_iSaveAsText)
	{
		Clear();

		HWND hwndLoadingText;
		HWND hwndProgressBar;

		if((pWndParent != NULL) && (m_iShowProgressBar))
		{
			m_wndLoading.SetExtraData(0, (int)this);
			m_wndLoading.SetExtraData(1, (int)pLog);
			m_wndLoading.CreateAsDialog(pWndParent->GetInstance(), IDD_LOADING, 0, pWndParent);

			SetWindowText(m_wndLoading.GetHWND(), "Loading Resources");

			hwndLoadingText = GetDlgItem(m_wndLoading.GetHWND(), IDC_LOADING_TEXT1);
			hwndProgressBar = GetDlgItem(m_wndLoading.GetHWND(), IDC_LOADING_PROGRESS1);

			SendMessage(hwndProgressBar, PBM_SETRANGE, 0, MAKELPARAM(0, 32767));
		}

		int iNumResources = 0;
		int iCurIndex = 0;

		std::string szLoading;

		while(1)
		{
			while(((filein.peek() == '\n') || (filein.peek() == '\t')) && (!filein.eof()))
				filein.ignore(1);

			ReadTextField(filein, szResourceType, 256);

			if((filein.eof()) || (filein.fail()) || (filein.bad()) || (!filein.good()))
				break;

			if(strcmp(szResourceType, "Number of resources") == 0)
			{
				filein >> iNumResources;

				if(iNumResources > 0)
					SendMessage(hwndProgressBar, PBM_SETRANGE, 0, MAKELPARAM(0, (short)iNumResources - 1));

				c = filein.get();

				while((c != '\n') && (!filein.eof()))
					c = filein.get();
			}
			else
			{
				for(i = 0; i < NUM_RESOURCE_TYPES; i++)
				{
					if((strcmp(szResourceType, g_szResourceTypes[i].c_str()) == 0) || (strcmp(szResourceType, g_szMacResourceTypes[i].c_str()) == 0))
					{
						if((pWndParent != NULL) && (m_iShowProgressBar))
						{
							SendMessage(hwndProgressBar, PBM_DELTAPOS, 1, 0);

							szLoading = "Loading resource ";

							szLoading += ToString(iCurIndex + 1);
							szLoading += " of ";

							if(iNumResources > 0)
								szLoading += ToString(iNumResources);
							else
								szLoading += "?";

							Static_SetText(hwndLoadingText, szLoading.c_str());
						}

						m_vResources[i].push_back(AllocateResource(i));

						filein >> iID;

						filein.ignore(1);

						ReadTextField(filein, szResourceName, 256);

						m_iFileOffset = filein.tellg();

						m_vResources[i][m_vResources[i].size() - 1]->SetID(iID);
						m_vResources[i][m_vResources[i].size() - 1]->SetName(szResourceName);
						m_vResources[i][m_vResources[i].size() - 1]->SetIsNew(0);

						if(g_iResourceCanLoadSaveText[i])
						{
							if(m_vResources[i][m_vResources[i].size() - 1]->LoadFromText(filein) == 0)
								iError = 1;
						}
						else
						{
							if(m_vResources[i][m_vResources[i].size() - 1]->LoadFromTextEx(filein, std::string(m_szFilePath)) == 0)
								iError = 1;
						}

						ReadTextField(filein, szJunk, 4);

						iCurIndex++;

						break;
					}
				}

				if(i == NUM_RESOURCE_TYPES)
				{
					c = filein.get();

					while((c != '\n') && (!filein.eof()))
						c = filein.get();
				}
			}
		}

		filein.close();

		if((pWndParent != NULL) && (m_iShowProgressBar))
		{
			m_wndLoading.Destroy();
		}

		if(iError)
			return 0;

		return 1;
	}

	int iHeader;
	int iHeaderSize;
	int iFirstIndex;
	int iNumResources;
	int iJunk;

	filein.read((char *)&iHeader, sizeof(int));

	if((iHeader != 0x52475242) || (filein.eof()))
	{
		if(iHeader != 0x52475242)
			*pLog << "Error: 4-byte header of file \"" << m_szFilename << "\" did not match 0x42524752 (\"BRGR\")." << CErrorLog::endl;
		else
			*pLog << "Error: Early EOF in file \"" << m_szFilename << "\"!" << CErrorLog::endl;

		iError = 1;
	}

	if(iError == 0)
	{
		filein.read((char *)&iJunk,         sizeof(int));
		filein.read((char *)&iHeaderSize,   sizeof(int));
		filein.read((char *)&iJunk,         sizeof(int));
		filein.read((char *)&iFirstIndex,   sizeof(int));
		filein.read((char *)&iNumResources, sizeof(int));

		if(filein.eof())
		{
			*pLog << "Error: Early EOF in file \"" << m_szFilename << "\"!" << CErrorLog::endl;

			iError = 1;
		}
	}

	std::vector<int> vResourceOffsets;
	std::vector<int> vResourceLengths;

	if(iError == 0)
	{
		vResourceOffsets.resize(iNumResources);
		vResourceLengths.resize(iNumResources);

		for(i = 0; i < iNumResources; i++)
		{
			filein.read((char *)&vResourceOffsets[i], 4);

			filein.read((char *)&vResourceLengths[i], sizeof(int));
			filein.read((char *)&iJunk,               sizeof(int));

			if(filein.eof())
			{
				*pLog << "Error: Early EOF in file \"" << m_szFilename << "\"!" << CErrorLog::endl;

				iError = 1;

				break;
			}
		}
	}

	if(iError == 0)
	{
		filein.read(szJunk, 13 * sizeof(char));

		szJunk[13] = '\0';

		if(filein.eof())
		{
			*pLog << "Error: Early EOF in file \"" << m_szFilename << "\"!" << CErrorLog::endl;

			iError = 1;
		}
	}

	if(iError == 0)
	{
		if(strcmp(szJunk, "resource.map") != 0)
		{
			*pLog << "Error: In file \"" << m_szFilename << ", string at end of header (\"" << szJunk << "\") did not match \"resource.map\"." << CErrorLog::endl;

			iError = 1;
		}
	}

	int iResourceStart;
	int iResourceMapStart;

	if(iError == 0)
	{
		Clear();

		if((pWndParent != NULL) && (m_iShowProgressBar))
		{
			m_wndLoading.SetExtraData(0, (int)this);
			m_wndLoading.SetExtraData(1, (int)pLog);
			m_wndLoading.CreateAsDialog(pWndParent->GetInstance(), IDD_LOADING, 0, pWndParent);

			SetWindowText(m_wndLoading.GetHWND(), "Loading Resources");
		}

		iResourceStart    = filein.tellg();
		iResourceMapStart = vResourceOffsets[iNumResources - 1];

		filein.seekg(iResourceMapStart);

		if(filein.eof())
		{
			*pLog << "Error: Early EOF in file \"" << m_szFilename << "\"!" << CErrorLog::endl;

			iError = 1;
		}
	}

	int iNumResourceTypes;

	if(iError == 0)
	{
		filein.read((char *)&iJunk,             sizeof(int)); iJunk             = SwapEndianInt(iJunk);
		filein.read((char *)&iNumResourceTypes, sizeof(int)); iNumResourceTypes = SwapEndianInt(iNumResourceTypes);

		if(filein.eof())
		{
			*pLog << "Error: Early EOF in file \"" << m_szFilename << "\"!" << CErrorLog::endl;

			iError = 1;
		}
	}

	std::vector<std::string> vResourceTypes;
	std::vector<int> vFirstResourceOffsets;
	std::vector<int> vResourceTypeCounts;

	HWND hwndLoadingText;
	HWND hwndProgressBar;

	if(iError == 0)
	{
		vResourceTypes.resize(iNumResourceTypes);
		vFirstResourceOffsets.resize(iNumResourceTypes);
		vResourceTypeCounts.resize(iNumResourceTypes);

		if((pWndParent != NULL) && (m_iShowProgressBar))
		{
			hwndLoadingText = GetDlgItem(m_wndLoading.GetHWND(), IDC_LOADING_TEXT1);
			hwndProgressBar = GetDlgItem(m_wndLoading.GetHWND(), IDC_LOADING_PROGRESS1);

			SendMessage(hwndProgressBar, PBM_SETRANGE, 0, MAKELPARAM(0, (short)iNumResources - 1));
		}

		for(i = 0; i < iNumResourceTypes; i++)
		{
			filein.read(szResourceType, 4 * sizeof(char));

			if(filein.eof())
			{
				*pLog << "Error: Early EOF in file \"" << m_szFilename << "\"!" << CErrorLog::endl;

				iError = 1;

				break;
			}

			szResourceType[4] = '\0';

			vResourceTypes[i] = szResourceType;

			filein.read((char *)&vFirstResourceOffsets[i], sizeof(int)); vFirstResourceOffsets[i] = SwapEndianInt(vFirstResourceOffsets[i]);
			filein.read((char *)&vResourceTypeCounts[i],   sizeof(int)); vResourceTypeCounts[i]   = SwapEndianInt(vResourceTypeCounts[i]);

			if(filein.eof())
			{
				*pLog << "Error: Early EOF in file \"" << m_szFilename << "\"!" << CErrorLog::endl;

				iError = 1;

				break;
			}
		}
	}

	std::vector<int> vListTypes;

	std::vector<int> vResourceIndexes;
	std::vector<short> vResourceIDs;
	std::vector<std::string> vResourceNames;

	if(iError == 0)
	{
		vListTypes.resize(iNumResourceTypes);

		for(i = 0; i < iNumResourceTypes; i++)
		{
			for(j = 0; j < NUM_RESOURCE_TYPES; j++)
			{
				if(vResourceTypes[i] == g_szMacResourceTypes[j])
				{
					for(k = 0; k < vResourceTypeCounts[i]; k++)
					{
						m_vResources[j].push_back(AllocateResource(j));

						if(m_vResources[j][m_vResources[j].size() - 1] == NULL)
						{
							m_vResources[j].pop_back();

							j = NUM_RESOURCE_TYPES;

							iError = 1;

							break;
						}

						m_vResources[j][k]->SetIsNew(0);
					}

					vListTypes[i] = j;

					break;
				}
			}

			if(iError)
				break;

			if(j == NUM_RESOURCE_TYPES)
			{
				for(k = 0; k < vResourceTypeCounts[i]; k++)
				{
					m_vResources[CNR_TYPE_UNK].push_back(AllocateResource(CNR_TYPE_UNK));

					if(m_vResources[CNR_TYPE_UNK][m_vResources[CNR_TYPE_UNK].size() - 1] == NULL)
					{
						m_vResources[CNR_TYPE_UNK].pop_back();

						iError = 1;

						break;
					}

					((CUnkResource *)m_vResources[CNR_TYPE_UNK][m_vResources[CNR_TYPE_UNK].size() - 1])->SetTypeCode(vResourceTypes[i].c_str());
				}

				if(iError)
					break;

				vListTypes[i] = CNR_TYPE_UNK;

				*pLog << "Warning: Unknown resource type \"" << vResourceTypes[i] << "\" in file \"" << m_szFilename << "\".  Skipping..." << CErrorLog::endl;

				continue;
			}
		}
	}

	if(iError == 0)
	{
		vResourceIndexes.resize(iNumResources - 1);
		vResourceIDs.resize(iNumResources - 1);
		vResourceNames.resize(iNumResources - 1);

		for(i = 0; i < iNumResources - 1; i++)
		{
			filein.read((char *)&vResourceIndexes[i], sizeof(int)); vResourceIndexes[i] = SwapEndianInt(vResourceIndexes[i]);
			filein.read(szResourceType, 4 * sizeof(char));

			szResourceType[4] = '\0';

			filein.read((char *)&vResourceIDs[i], sizeof(short)); vResourceIDs[i] = SwapEndianShort(vResourceIDs[i]);
			filein.read(szResourceName, 256 * sizeof(char));

			if(filein.eof())
			{
				*pLog << "Error: Early EOF in file \"" << m_szFilename << "\"!" << CErrorLog::endl;

				iError = 1;

				break;
			}

			szResourceName[255] = '\0';

			ToWinString(szResourceName);

			vResourceNames[i] = szResourceName;
		}
	}

	if(iError == 0)
	{
		filein.seekg(iResourceStart);

		if(filein.eof())
		{
			*pLog << "Error: Early EOF in file \"" << m_szFilename << "\"!" << CErrorLog::endl;

			iError = 1;
		}
	}

	int iCurIndex = 0;

	char *pResourceData = NULL;

	std::string szLoading;

	int iIndex;

	int iUnkResourceIndex = 0;

	if(iError == 0)
	{
		for(i = 0; i < iNumResourceTypes; i++)
		{
			for(j = 0; j < vResourceTypeCounts[i]; j++)
			{
				if((pWndParent != NULL) && (m_iShowProgressBar))
				{
					SendMessage(hwndProgressBar, PBM_DELTAPOS, 1, 0);

					szLoading = "Loading resource ";

					szLoading += ToString(iCurIndex + 1);
					szLoading += " of ";
					szLoading += ToString(iNumResources - 1);

					Static_SetText(hwndLoadingText, szLoading.c_str());
				}

				m_iFileOffset = filein.tellg();

				if(vListTypes[i] == CNR_TYPE_UNK)
					iIndex = j + iUnkResourceIndex;
				else
					iIndex = j;


				filein.seekg(vResourceOffsets[iCurIndex]);

				if(m_vResources[vListTypes[i]][iIndex]->ShouldLoadDirect() == 0)
				{
					pResourceData = new char[vResourceLengths[iCurIndex]];

					if(pResourceData == NULL)
					{
						*pLog << "Error: Unable to allocate temporary buffer for resource!" << CErrorLog::endl;

						iError = 1;
					}
					else
					{
						filein.read(pResourceData, vResourceLengths[iCurIndex]);

						if(filein.eof())
						{
							*pLog << "Error: Early EOF in file \"" << m_szFilename << "\"!" << CErrorLog::endl;

							iError = 1;

							delete [] pResourceData;

							break;
						}

						m_vResources[vListTypes[i]][iIndex]->SetID(vResourceIDs[iCurIndex]);
						m_vResources[vListTypes[i]][iIndex]->SetName(vResourceNames[iCurIndex].c_str());

						if(m_vResources[vListTypes[i]][iIndex]->Load(pResourceData, vResourceLengths[iCurIndex]) == 0)
							iError = 1;

						delete [] pResourceData;

						pResourceData = NULL;
					}
				}
				else
				{
					m_vResources[vListTypes[i]][iIndex]->SetID(vResourceIDs[iCurIndex]);
					m_vResources[vListTypes[i]][iIndex]->SetName(vResourceNames[iCurIndex].c_str());

					if(m_vResources[vListTypes[i]][iIndex]->LoadDirect(filein, vResourceLengths[iCurIndex]) == 0)
						iError = 1;

					if(filein.eof())
					{
						*pLog << "Error: Early EOF in file \"" << m_szFilename << "\"!" << CErrorLog::endl;

						iError = 1;

						break;
					}
				}

				iCurIndex++;
			}

			if(vListTypes[i] == CNR_TYPE_UNK)
				iUnkResourceIndex += vResourceTypeCounts[i];

			if(iError)
				break;
		}
	}

	for(i = 0; i < NUM_RESOURCE_TYPES; i++)
	{
		if(m_vResources[i].size() > 0)
			std::sort(m_vResources[i].begin(), m_vResources[i].end(), SNovaResourceCompare());
	}

	if((pWndParent != NULL) && (m_iShowProgressBar))
	{
		m_wndLoading.Destroy();
	}

	filein.close();

	if(iError)
		return 0;

	return 1;
}

int CPlugIn::Save(CWindow *pWndParent)
{
	if(strcmp(m_szFilename, "") == 0)
		return 0;

	std::ofstream fileout;

	int iSaveFlags = std::ios::out | std::ios::trunc;

	if(m_iSaveAsText == 0)
		iSaveFlags |= std::ios::binary;

	fileout.open(m_szFilename, iSaveFlags);

	m_iFileOffset = 0;

	std::string szBuffer;

	CErrorLog *pLog = CErrorLog::GetCurrentErrorLog();

	if(!fileout.is_open())
	{
		szBuffer = "Error: Unable to open file \"";
		szBuffer += m_szFilename;
		szBuffer += "\"!";

		*pLog << szBuffer << CErrorLog::endl;

		if(m_iShowErrorMessages)
			MessageBox(pWndParent->GetHWND(), szBuffer.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	HWND hwndSavingText;
	HWND hwndProgressBar;

	if((pWndParent != NULL) && (m_iShowProgressBar))
	{
		m_wndLoading.SetExtraData(0, (int)this);
		m_wndLoading.SetExtraData(1, (int)pLog);
		m_wndLoading.CreateAsDialog(pWndParent->GetInstance(), IDD_LOADING, 0, pWndParent);

		SetWindowText(m_wndLoading.GetHWND(), "Saving Resources");

		hwndSavingText  = GetDlgItem(m_wndLoading.GetHWND(), IDC_LOADING_TEXT1);
		hwndProgressBar = GetDlgItem(m_wndLoading.GetHWND(), IDC_LOADING_PROGRESS1);
	}

	std::string szSaving;

	int i, j;

	int iNumResources = 0;

	for(i = 0; i < m_vResources.size(); i++)
		iNumResources += m_vResources[i].size();

	if((pWndParent != NULL) && (m_iShowProgressBar))
	{
		SendMessage(hwndProgressBar, PBM_SETRANGE, 0, MAKELPARAM(0, (short)iNumResources - 1));
	}

	int iCurIndex = 0;

	int iCount;

	const std::string *pSzFieldNames;

	std::string szImageOrSoundFilename1, szImageOrSoundFilename2;

	if(m_iSaveAsText)
	{
		fileout << "\"Format\""              "\t\"EVNEW text 1.0.1\""        "\n"
				   "\"Created by\""          "\t\"EVNEW 1.0.5\"" "\n"
				   "\"Number of resources\"" "\t"

				<< iNumResources << "\n\n";

		for(i = 0; i < NUM_RESOURCE_TYPES; i++)
		{
			if(((i == CNR_TYPE_CICN) && (!m_iCicnSave)) ||
			   ((i == CNR_TYPE_PICT) && (!m_iPictSave)) ||
			   ((i == CNR_TYPE_RLE8) && (!m_iRle8Save)) ||
			   ((i == CNR_TYPE_RLED) && (!m_iRleDSave)) ||
			   ((i == CNR_TYPE_SND)  && (!m_iSndSave)))
			{
				iCurIndex += m_vResources[i].size();

				continue;
			}

			if(m_vResources[i].size() > 0)
			{
				fileout << "\"Resource Type\"\t\"ID\"\t\"Name\"\t";

				iCount = m_vResources[i][0]->GetNumFields();

				pSzFieldNames = m_vResources[i][0]->GetFieldNames();

				for(j = 0; j < iCount; j++)
					PrintTextField(fileout, pSzFieldNames[j].c_str(), '\t');

				fileout << "\"End-of-resource\"\n";
			}

			for(j = 0; j < m_vResources[i].size(); j++, iCurIndex++)
			{
				if((pWndParent != NULL) && (m_iShowProgressBar))
				{
					SendMessage(hwndProgressBar, PBM_DELTAPOS, 1, 0);

					szSaving = "Saving resource ";

					szSaving += ToString(iCurIndex + 1);
					szSaving += " of ";
					szSaving += ToString(iNumResources);

					Static_SetText(hwndSavingText, szSaving.c_str());
				}

				PrintTextField(fileout, g_szResourceTypes[i].c_str(), '\t');

				fileout << m_vResources[i][j]->GetID() << '\t';
					
				PrintTextField(fileout, m_vResources[i][j]->GetName(), '\t');

				m_iFileOffset = fileout.tellp();

				if(i == CNR_TYPE_CICN)
				{
					szImageOrSoundFilename1 = GenerateFilename(m_szCicnSubdirectory,     m_szCicnFilenamePrefix,     ".bmp", m_vResources[i][j]->GetID());
					szImageOrSoundFilename2 = GenerateFilename(m_szCicnMaskSubdirectory, m_szCicnMaskFilenamePrefix, ".bmp", m_vResources[i][j]->GetID());

					m_vResources[i][j]->SaveToTextEx(fileout, std::string(m_szFilePath), szImageOrSoundFilename1, szImageOrSoundFilename2, 0);
				}
				else if(i == CNR_TYPE_PICT)
				{
					szImageOrSoundFilename1 = GenerateFilename(m_szPictSubdirectory, m_szPictFilenamePrefix, g_szImageTypeExtensions[m_iPictImageFileType].c_str(), m_vResources[i][j]->GetID());

					m_vResources[i][j]->SaveToTextEx(fileout, std::string(m_szFilePath), szImageOrSoundFilename1, std::string(""), m_iPictImageFileType);
				}
				else if(i == CNR_TYPE_RLE8)
				{
					szImageOrSoundFilename1 = GenerateFilename(m_szRle8Subdirectory,     m_szRle8FilenamePrefix,     g_szRleImageTypeExtensions[m_iRle8ImageFileType].c_str(), m_vResources[i][j]->GetID());
					szImageOrSoundFilename2 = GenerateFilename(m_szRle8MaskSubdirectory, m_szRle8MaskFilenamePrefix, g_szRleImageTypeExtensions[m_iRle8MaskFileType].c_str(),  m_vResources[i][j]->GetID());

					m_vResources[i][j]->SaveToTextEx(fileout, std::string(m_szFilePath), szImageOrSoundFilename1, szImageOrSoundFilename2, m_iRle8FramesPerRow);
				}
				else if(i == CNR_TYPE_RLED)
				{
					szImageOrSoundFilename1 = GenerateFilename(m_szRleDSubdirectory,     m_szRleDFilenamePrefix,     g_szRleImageTypeExtensions[m_iRleDImageFileType].c_str(), m_vResources[i][j]->GetID());
					szImageOrSoundFilename2 = GenerateFilename(m_szRleDMaskSubdirectory, m_szRleDMaskFilenamePrefix, g_szRleImageTypeExtensions[m_iRleDMaskFileType].c_str(),  m_vResources[i][j]->GetID());

					m_vResources[i][j]->SaveToTextEx(fileout, std::string(m_szFilePath), szImageOrSoundFilename1, szImageOrSoundFilename2, m_iRleDFramesPerRow);
				}
				else if(i == CNR_TYPE_SND)
				{
					szImageOrSoundFilename1 = GenerateFilename(m_szSndSubdirectory, m_szSndFilenamePrefix, ".wav", m_vResources[i][j]->GetID());

					m_vResources[i][j]->SaveToTextEx(fileout, std::string(m_szFilePath), szImageOrSoundFilename1, std::string(""), 0);
				}
				else
				{
					m_vResources[i][j]->SaveToText(fileout);
				}

				fileout << "\"EOR\"\n";
			}

			if(m_vResources[i].size() > 0)
			{
				fileout << '\n';
			}
		}

		fileout.close();

		m_wndLoading.Destroy();

		return 1;
	}

	m_iFileOffset = 0;

	int iHeader = 0x52475242;
	int iJunk   = 0x00000001;

	fileout.write((char *)&iHeader, sizeof(int));
	fileout.write((char *)&iJunk,   sizeof(int));

	int iHeaderEnd = 12 * iNumResources + 37;

	fileout.write((char *)&iHeaderEnd, sizeof(int));
	fileout.write((char *)&iJunk,      sizeof(int));

	int iFirstIndex = 1;

	fileout.write((char *)&iFirstIndex, sizeof(int));

	iNumResources++;

	fileout.write((char *)&iNumResources, sizeof(int));

	iNumResources--;

	std::vector<int> vResourceOffsets;
	std::vector<int> vResourceLengths;

	vResourceOffsets.resize(iNumResources + 1);
	vResourceLengths.resize(iNumResources + 1);

	int iPrevOffset = iHeaderEnd + 12;

	int iNumResourceTypes = 0;

	for(i = 0; i < m_vResources.size(); i++)
	{
		for(j = 0; j < m_vResources[i].size(); j++, iCurIndex++)
		{
			vResourceOffsets[iCurIndex] = iPrevOffset;
			vResourceLengths[iCurIndex] = m_vResources[i][j]->GetSize();

			iPrevOffset += vResourceLengths[iCurIndex];
		}

		if(m_vResources[i].size() > 0)
			iNumResourceTypes++;

		if(i == CNR_TYPE_UNK)
		{
			for(j = 1; j < m_vResources[i].size(); j++)
			{
				if(strcmp(((CUnkResource *)m_vResources[i][j])->GetTypeCode(), ((CUnkResource *)m_vResources[i][j - 1])->GetTypeCode()) != 0)
					iNumResourceTypes++;
			}
		}
	}

	vResourceOffsets[iCurIndex] = iPrevOffset;
	vResourceLengths[iCurIndex] = 12 * iNumResourceTypes + 266 * iNumResources + 8;

	iJunk = 0x00000000;

	for(i = 0; i <= iNumResources; i++)
	{
		fileout.write((char *)&vResourceOffsets[i], sizeof(int));
		fileout.write((char *)&vResourceLengths[i], sizeof(int));

		if(i == iNumResources)
			iJunk = 12 * iNumResources + 24;

		fileout.write((char *)&iJunk, sizeof(int));
	}

	char szResourceDotMap[13] = "resource.map";

	fileout.write(szResourceDotMap, 13 * sizeof(char));

	char *pResourceData = NULL;

	int iResourceSize;

	iCurIndex = 0;

	for(i = 0; i < m_vResources.size(); i++)
	{
		for(j = 0; j < m_vResources[i].size(); j++)
		{
			if((pWndParent != NULL) && (m_iShowProgressBar))
			{
				SendMessage(hwndProgressBar, PBM_DELTAPOS, 1, 0);

				szSaving = "Saving resource ";

				szSaving += ToString(iCurIndex + 1);
				szSaving += " of ";
				szSaving += ToString(iNumResources);

				Static_SetText(hwndSavingText, szSaving.c_str());
			}

			iResourceSize = m_vResources[i][j]->GetSize();

			if(m_vResources[i][j]->ShouldLoadDirect() == 0)
			{
				pResourceData = new char[iResourceSize];

				if(pResourceData == NULL)
				{
					*pLog << "Error: Unable to allocate temporary buffer for resource!" << CErrorLog::endl;

					continue;
				}

				memset(pResourceData, 0, iResourceSize * sizeof(char));

				m_iFileOffset = fileout.tellp();

				m_vResources[i][j]->Save(pResourceData);

				fileout.write(pResourceData, iResourceSize);

				delete [] pResourceData;

				pResourceData = NULL;
			}
			else
			{
				m_iFileOffset = fileout.tellp();

				m_vResources[i][j]->SaveDirect(fileout);
			}

			iCurIndex++;
		}
	}

	if((pWndParent != NULL) && (m_iShowProgressBar))
	{
		Static_SetText(hwndSavingText, "Saving resource map");
	}

	iJunk = 0x08000000;

	int iTemp = SwapEndianInt(iNumResourceTypes);

	fileout.write((char *)&iJunk, sizeof(int));
	fileout.write((char *)&iTemp, sizeof(int));

	iCurIndex = 0;

	int iMapOffset = 8;

	for(i = 0; i < m_vResources.size(); i++)
	{
		if(m_vResources[i].size() > 0)
			iMapOffset += 12;

		if(i == CNR_TYPE_UNK)
		{
			for(j = 1; j < m_vResources[i].size(); j++)
			{
				if(strcmp(((CUnkResource *)m_vResources[i][j])->GetTypeCode(), ((CUnkResource *)m_vResources[i][j - 1])->GetTypeCode()) != 0)
					iMapOffset += 12;
			}
		}
	}

	for(i = 0; i < m_vResources.size(); i++)
	{
		if(i != CNR_TYPE_UNK)
		{
			if(m_vResources[i].size() > 0)
			{
				fileout.write(g_szMacResourceTypes[i].c_str(), 4 * sizeof(char));

				iTemp = SwapEndianInt(iMapOffset);             fileout.write((char *)&iTemp, sizeof(int));
				iTemp = SwapEndianInt(m_vResources[i].size()); fileout.write((char *)&iTemp, sizeof(int));

				iMapOffset += 266 * m_vResources[i].size();

				iCurIndex += m_vResources[i].size();
			}
		}
		else
		{
			if(m_vResources[i].size() > 0)
			{
				fileout.write(((CUnkResource *)m_vResources[i][0])->GetTypeCode(), 4 * sizeof(char));

				iTemp = SwapEndianInt(iMapOffset); fileout.write((char *)&iTemp, sizeof(int));

				iCount = 1;

				for(j = 1; j < m_vResources[i].size(); j++)
				{
					if(strcmp(((CUnkResource *)m_vResources[i][j])->GetTypeCode(), ((CUnkResource *)m_vResources[i][j - 1])->GetTypeCode()) != 0)
					{
						iTemp = SwapEndianInt(iCount); fileout.write((char *)&iTemp, sizeof(int));

						iMapOffset += 266 * iCount;

						iCurIndex += iCount;

						fileout.write(((CUnkResource *)m_vResources[i][j])->GetTypeCode(), 4 * sizeof(char));

						iTemp = SwapEndianInt(iMapOffset); fileout.write((char *)&iTemp, sizeof(int));

						iCount = 0;
					}

					iCount++;
				}

				iTemp = SwapEndianInt(iCount); fileout.write((char *)&iTemp, sizeof(int));

				iMapOffset += 266 * iCount;

				iCurIndex += iCount;
			}
		}
	}

	iCurIndex = 0;

	short iID;

	char szResourceName[256];

	for(i = 0; i < m_vResources.size(); i++)
	{
		for(j = 0; j < m_vResources[i].size(); j++, iCurIndex++)
		{
			iTemp = SwapEndianInt(iCurIndex + 1); fileout.write((char *)&iTemp, sizeof(int));

			if(i != CNR_TYPE_UNK)
				fileout.write(g_szMacResourceTypes[i].c_str(), 4 * sizeof(char));
			else
				fileout.write(((CUnkResource *)m_vResources[i][j])->GetTypeCode(), 4 * sizeof(char));

			iID = SwapEndianShort(m_vResources[i][j]->GetID()); fileout.write((char *)&iID, sizeof(short));

			strcpy(szResourceName, m_vResources[i][j]->GetName());

			ToMacString(szResourceName);

			fileout.write(szResourceName, 256 * sizeof(char));
		}
	}

	fileout.close();

	if((pWndParent != NULL) && (m_iShowProgressBar))
	{
		m_wndLoading.Destroy();
	}

	return 1;
}

CNovaResource * CPlugIn::AllocateResource(int iType)
{
	CNovaResource * pResource = NULL;

	if(iType == CNR_TYPE_BOOM)
		pResource = new CBoomResource;
	else if(iType == CNR_TYPE_CHAR)
		pResource = new CCharResource;
	else if(iType == CNR_TYPE_CICN)
		pResource = new CCicnResource;
	else if(iType == CNR_TYPE_COLR)
		pResource = new CColrResource;
	else if(iType == CNR_TYPE_CRON)
		pResource = new CCronResource;
	else if(iType == CNR_TYPE_DESC)
		pResource = new CDescResource;
	else if(iType == CNR_TYPE_DUDE)
		pResource = new CDudeResource;
	else if(iType == CNR_TYPE_FLET)
		pResource = new CFletResource;
	else if(iType == CNR_TYPE_GOVT)
		pResource = new CGovtResource;
	else if(iType == CNR_TYPE_INTF)
		pResource = new CIntfResource;
	else if(iType == CNR_TYPE_JUNK)
		pResource = new CJunkResource;
	else if(iType == CNR_TYPE_MISN)
		pResource = new CMisnResource;
	else if(iType == CNR_TYPE_NEBU)
		pResource = new CNebuResource;
	else if(iType == CNR_TYPE_OOPS)
		pResource = new COopsResource;
	else if(iType == CNR_TYPE_OUTF)
		pResource = new COutfResource;
	else if(iType == CNR_TYPE_PERS)
		pResource = new CPersResource;
	else if(iType == CNR_TYPE_PICT)
		pResource = new CPictResource;
	else if(iType == CNR_TYPE_RANK)
		pResource = new CRankResource;
	else if(iType == CNR_TYPE_RLE8)
	{
		pResource = new CRLEResource;

		((CRLEResource *)pResource)->SetBPP(8);
	}
	else if(iType == CNR_TYPE_RLED)
	{
		pResource = new CRLEResource;

		((CRLEResource *)pResource)->SetBPP(16);
	}
	else if(iType == CNR_TYPE_ROID)
		pResource = new CRoidResource;
	else if(iType == CNR_TYPE_SHAN)
		pResource = new CShanResource;
	else if(iType == CNR_TYPE_SHIP)
		pResource = new CShipResource;
	else if(iType == CNR_TYPE_SND)
		pResource = new CSndResource;
	else if(iType == CNR_TYPE_SPIN)
		pResource = new CSpinResource;
	else if(iType == CNR_TYPE_SPOB)
		pResource = new CSpobResource;
	else if(iType == CNR_TYPE_STR)
		pResource = new CStrResource;
	else if(iType == CNR_TYPE_STRL)
		pResource = new CStrlResource;
	else if(iType == CNR_TYPE_SYST)
		pResource = new CSystResource;
	else if(iType == CNR_TYPE_WEAP)
		pResource = new CWeapResource;
	else if(iType == CNR_TYPE_UNK)
		pResource = new CUnkResource;
	else
		return NULL;

	if(pResource == NULL)
		throw CException("Error: could not allocate memory for resource type %d!", iType);

	return pResource;
}

std::string CPlugIn::GenerateFilename(char *szSubdirectory, char *szFilenamePrefix, const char *szExtension, short iID)
{
	std::string szFilename, szFilenameFinal;

	szFilename = m_szFilePath;

	if((strcmp(szSubdirectory, "") != 0) && (strcmp(szSubdirectory, "\\") != 0))
	{
		if(szSubdirectory[0] != '\\')
			szFilename += szSubdirectory;
		else
			szFilename += (szSubdirectory + 1);

		if(szSubdirectory[strlen(szSubdirectory) - 1] != '\\')
			szFilename += '\\';

		CreateDirectory(szFilename.c_str(), NULL);
	}

	szFilename += szFilenamePrefix;
	szFilename += ToString(iID);

	szFilenameFinal = szFilename;
	szFilenameFinal += szExtension;

	std::ifstream filein;

	filein.open(szFilenameFinal.c_str(), std::ios::in);

	int i;

	if(filein.is_open())
	{
		for(i = 2; i <= 32767; i++)
		{
			filein.close();

			szFilenameFinal = szFilename;
			szFilenameFinal += "_";
			szFilenameFinal += ToString(i);
			szFilenameFinal += szExtension;

			filein.open(szFilenameFinal.c_str(), std::ios::in);

			if(!filein.is_open())
				return szFilenameFinal.substr(strlen(m_szFilePath));
		}
	}
	else
		return szFilenameFinal.substr(strlen(m_szFilePath));

	return (std::string(""));
}
