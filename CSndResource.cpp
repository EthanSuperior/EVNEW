// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CSndResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CSndResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CSndResource::CSndResource(void)
{
	m_iFormat     = 1;
	m_iFormatCopy = 1;

	m_iIsDirty = 0;

	m_pSndHeader  = NULL;
	m_pSnd2Header = NULL;
	m_pSndInfo    = NULL;
	m_pSndData    = NULL;
}

CSndResource::~CSndResource(void)
= default;

int CSndResource::GetType(void)
{
	return CNR_TYPE_SND;
}

int CSndResource::GetSize(void)
{
	return m_vData.size();
}

int CSndResource::GetDialogID(void)
{
	return IDD_EDIT_SND;
}

DLGPROCNOCALLBACK CSndResource::GetDialogProc(void)
{
	return SndDlgProc;
}

int CSndResource::GetNumFields(void)
{
	return NUM_SND_FIELDS;
}

const std::string * CSndResource::GetFieldNames(void)
{
	return g_szSndFields;
}

int CSndResource::ShouldLoadDirect(void)
{
	return 1;
}

int CSndResource::SaveDirect(std::ostream & output)
{
	if(m_vData.size() > 0)
	{
		SwapEndians();

		output.write((char *)&m_vData[0], m_vData.size() * sizeof(UCHAR));

		SwapEndians();
	}

	return 1;
}

int CSndResource::LoadDirect(std::istream & input, int iSize)
{
	m_vData.resize(iSize);

	input.read((char *)&m_vData[0], iSize);

	if(*(short *)&m_vData[0] == 0x0100)
	{
		m_iFormat = 1;

		m_pSndHeader  = (qt::SndListResource *)&m_vData[0];
		m_pSnd2Header = NULL;
		m_pSndInfo    = (qt::CmpSoundHeader *)&m_pSndHeader->dataPart[0];
	}
	else
	{
		m_iFormat = 2;

		m_pSndHeader  = NULL;
		m_pSnd2Header = (qt::Snd2ListResource *)&m_vData[0];
		m_pSndInfo    = (qt::CmpSoundHeader *)&m_pSnd2Header->dataPart[0];
	}

	if(m_pSndInfo->encode == qt::stdSH)
		m_pSndData = (UCHAR *)&m_pSndInfo->numFrames;
	else
		m_pSndData = (UCHAR *)&m_pSndInfo->sampleArea[0];

	SwapEndians();

	return 1;
}

int CSndResource::Save(char *pOutput)
{
	if(m_vData.size() > 0)
	{
		SwapEndians();

		memcpy(pOutput, &m_vData[0], m_vData.size());

		SwapEndians();
	}

	return 1;
}

int CSndResource::Load(char *pInput, int iSize)
{
	m_vData.resize(iSize);

	memcpy(&m_vData[0], pInput, iSize);

	if(*(short *)&m_vData[0] == 0x0100)
	{
		m_iFormat = 1;

		m_pSndHeader  = (qt::SndListResource *)&m_vData[0];
		m_pSnd2Header = NULL;
		m_pSndInfo    = (qt::CmpSoundHeader *)&m_pSndHeader->dataPart[0];
	}
	else
	{
		m_iFormat = 2;

		m_pSndHeader  = NULL;
		m_pSnd2Header = (qt::Snd2ListResource *)&m_vData[0];
		m_pSndInfo    = (qt::CmpSoundHeader *)&m_pSnd2Header->dataPart[0];
	}

	if(m_pSndInfo->encode == qt::stdSH)
		m_pSndData = (UCHAR *)&m_pSndInfo->numFrames;
	else
		m_pSndData = (UCHAR *)&m_pSndInfo->sampleArea[0];

	SwapEndians();

	return 1;
}

int CSndResource::SwapEndians(void)
{
	if((m_pSndHeader == NULL) && (m_pSnd2Header == NULL))
		return 0;

	if(m_iFormat == 1)
	{
		m_pSndHeader->format                    = SwapEndianShort(m_pSndHeader->format);
		m_pSndHeader->numModifiers              = SwapEndianShort(m_pSndHeader->numModifiers);
		m_pSndHeader->modifierPart[0].modNumber = SwapEndianShort(m_pSndHeader->modifierPart[0].modNumber);
		m_pSndHeader->modifierPart[0].modInit   = SwapEndianInt(  m_pSndHeader->modifierPart[0].modInit);
		m_pSndHeader->numCommands               = SwapEndianShort(m_pSndHeader->numCommands);
		m_pSndHeader->commandPart[0].cmd        = SwapEndianShort(m_pSndHeader->commandPart[0].cmd);
		m_pSndHeader->commandPart[0].param1     = SwapEndianShort(m_pSndHeader->commandPart[0].param1);
		m_pSndHeader->commandPart[0].param2     = SwapEndianInt(  m_pSndHeader->commandPart[0].param2);
	}
	else
	{
		m_pSnd2Header->format                = SwapEndianShort(m_pSnd2Header->format);
		m_pSnd2Header->refCount              = SwapEndianShort(m_pSnd2Header->refCount);
		m_pSnd2Header->numCommands           = SwapEndianShort(m_pSnd2Header->numCommands);
		m_pSnd2Header->commandPart[0].cmd    = SwapEndianShort(m_pSnd2Header->commandPart[0].cmd);
		m_pSnd2Header->commandPart[0].param1 = SwapEndianShort(m_pSnd2Header->commandPart[0].param1);
		m_pSnd2Header->commandPart[0].param2 = SwapEndianInt(  m_pSnd2Header->commandPart[0].param2);
	}

	m_pSndInfo->samplePtr   = (char *)SwapEndianInt((int)m_pSndInfo->samplePtr);
	m_pSndInfo->numChannels = SwapEndianInt(m_pSndInfo->numChannels);
	m_pSndInfo->sampleRate  = SwapEndianInt(m_pSndInfo->sampleRate);
	m_pSndInfo->loopStart   = SwapEndianInt(m_pSndInfo->loopStart);
	m_pSndInfo->loopEnd     = SwapEndianInt(m_pSndInfo->loopEnd);
	m_pSndInfo->numFrames   = SwapEndianInt(m_pSndInfo->numFrames);

	SwapEndian80((char *)&m_pSndInfo->AIFFSampleRate);

	m_pSndInfo->markerChunk     = (char *)SwapEndianInt((int)m_pSndInfo->markerChunk);
	m_pSndInfo->format          = SwapEndianInt(m_pSndInfo->format);
	m_pSndInfo->futureUse2      = SwapEndianInt(m_pSndInfo->futureUse2);
	m_pSndInfo->stateVars       = (qt::StateBlock *)SwapEndianInt((int)m_pSndInfo->stateVars);
	m_pSndInfo->leftOverSamples = (qt::LeftOverBlock *)SwapEndianInt((int)m_pSndInfo->leftOverSamples);
	m_pSndInfo->compressionID   = SwapEndianShort(m_pSndInfo->compressionID);
	m_pSndInfo->packetSize      = SwapEndianShort(m_pSndInfo->packetSize);
	m_pSndInfo->snthID          = SwapEndianShort(m_pSndInfo->snthID);
	m_pSndInfo->sampleSize      = SwapEndianShort(m_pSndInfo->sampleSize);

	return 1;
}

int CSndResource::SaveToTextEx(std::ostream & output, std::string & szFilePath, std::string & szFilename1, std::string & szFilename2, int iParam)
{
	PrintTextField(output, szFilename1.c_str(), '\t');

	std::string szFilename = szFilePath + szFilename1;

	FileExport(szFilename.c_str(), 0);

	return 1;
}

int CSndResource::LoadFromTextEx(std::istream & input, std::string & szFilePath)
{
	char szFilename[MAX_PATH];

	strcpy_s(szFilename, szFilePath.c_str());

	ReadTextField(input, szFilename + strlen(szFilename), MAX_PATH - strlen(szFilename));

	FileImport(szFilename, 0);

	return 1;
}

int CSndResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "snd ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_SND_EDIT1, CCONTROL_TYPE_INT, -1);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_SND_EDIT2, CCONTROL_TYPE_STR256, -1);
	m_controls[1].SetString(m_szName);

	if(m_vData.size() > 0)
	{
		HWND hwndTextSampleRate = GetDlgItem(hwnd, IDC_EDIT_SND_TEXT3);
		HWND hwndTextDataSize   = GetDlgItem(hwnd, IDC_EDIT_SND_TEXT4);

		std::string szText = "Sample rate: ";
		szText += ToString(static_cast<double>(m_pSndInfo->sampleRate) / 65536.0);
		szText += " Hz";
		Static_SetText(hwndTextSampleRate, szText.c_str());

		szText = "Size: ";
		szText += ToString(m_vData.size() - (m_pSndData - &m_vData[0]));
		szText += " bytes";
		Static_SetText(hwndTextDataSize, szText.c_str());
	}

	m_iIsDirty = 0;

	return 1;
}

int CSndResource::CloseAndSave(void)
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

	strcpy_s(m_szName, m_controls[1].GetString());

	if(m_iIsDirty)
	{
		m_vData.resize(m_vData2.size());

		memcpy(&m_vData[0], &m_vData2[0], m_vData2.size());

		m_vData2.clear();

		m_iFormat = m_iFormatCopy;

		if(m_iFormat == 1)
		{
			m_pSndHeader  = (qt::SndListResource *)&m_vData[0];
			m_pSnd2Header = NULL;
			m_pSndInfo    = (qt::CmpSoundHeader *)&m_pSndHeader->dataPart[0];
		}
		else
		{
			m_pSndHeader  = NULL;
			m_pSnd2Header = (qt::Snd2ListResource *)&m_vData[0];
			m_pSndInfo    = (qt::CmpSoundHeader *)&m_pSnd2Header->dataPart[0];
		}

		if(m_pSndInfo->encode == qt::stdSH)
			m_pSndData = (UCHAR *)&m_pSndInfo->numFrames;
		else
			m_pSndData = (UCHAR *)&m_pSndInfo->sampleArea[0];

		m_iIsDirty = 0;

		CEditor::GetCurrentEditor()->SetDirty();
	}

	int i;

	for(i = 0; i < NUM_SND_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CSndResource::CloseAndDontSave(void)
{
	if(m_iIsDirty)
	{
		if(m_iFormat == 1)
		{
			m_pSndHeader  = (qt::SndListResource *)&m_vData[0];
			m_pSnd2Header = NULL;
			m_pSndInfo    = (qt::CmpSoundHeader *)&m_pSndHeader->dataPart[0];
			m_pSndData    = &m_pSndInfo->sampleArea[0];
		}
		else
		{
			m_pSndHeader  = NULL;
			m_pSnd2Header = (qt::Snd2ListResource *)&m_vData[0];
			m_pSndInfo    = (qt::CmpSoundHeader *)&m_pSnd2Header->dataPart[0];
			m_pSndData    = (UCHAR *)&m_pSndInfo->numFrames;
		}

		m_iIsDirty = 0;
	}

	int i;

	for(i = 0; i < NUM_SND_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

int CSndResource::PlaySound(void)
{
	HWND hwndPlayButton = GetDlgItem(m_pWindow->GetHWND(), IDC_EDIT_SND_BUTTON1);

	Button_SetText(hwndPlayButton, "Playing...");

	UCHAR *pSoundResource;

	if(!m_iIsDirty)
		pSoundResource = &m_vData[0];
	else
		pSoundResource = &m_vData2[0];

	qt::OSErr qtErr;

	qtErr = qt::SndPlay(nil, (qt::SndListResource **)&pSoundResource, FALSE);

	Button_SetText(hwndPlayButton, "Play");

	return 1;
}

int CSndResource::FileImport(const char *szFilename, int iShowErrorMessages)
{
	CEditor *pEditor = CEditor::GetCurrentEditor();
	CErrorLog *pLog  = CErrorLog::GetCurrentErrorLog();

	char szFilename2[MAX_PATH];

	if(szFilename == NULL)
	{
		strcpy_s(szFilename2, "");

		OPENFILENAME ofn;

		memset(&ofn, 0, sizeof(OPENFILENAME));

		ofn.lStructSize   = sizeof(OPENFILENAME);
		ofn.nMaxFile      = MAX_PATH;
		ofn.nMaxFileTitle = MAX_PATH;
		ofn.lpstrTitle    = "Import Sound Resource";
		ofn.lpstrFilter   = "Wave Files (*.wav)\0*.wav\0";
		ofn.nFilterIndex  = 1;
		ofn.lpstrDefExt   = "wav";
		ofn.Flags         = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
		ofn.hwndOwner     = m_pWindow->GetHWND();
		ofn.lpstrFile     = szFilename2;

		if(GetOpenFileName(&ofn) == 0)
			return 0;
	}
	else
	{
		strcpy_s(szFilename2, szFilename);
	}

	std::ifstream filein;

	filein.open(szFilename2, std::ios::in | std::ios::binary);

	if(filein.is_open() == 0)
	{
		if(pEditor->PrefGenerateLogFile())
			*pLog << "Error: Unable to open sound file \"" << szFilename2 << "\"!" << CErrorLog::endl;

		std::string szError = "Unable to load file \"";

		szError += szFilename2;
		szError += "\"!";

		if(pEditor->PrefGenerateLogFile())
			szError += "  Consult log.txt for details.";

		if(iShowErrorMessages)
			MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	int iNext = 0;

	char szChunk[5];

	int iChunkSize;

	char szRiffType[5];

	short  wFormatTag;
	USHORT wChannels;
	UINT   dwSamplesPerSec;
	UINT   dwAvgBytesPerSec;
	USHORT wBlockAlign;
	USHORT wBitsPerSample;

	std::vector<UCHAR> vData;

	while(1)
	{
		filein.read(szChunk, 4);
		filein.read((char *)&iChunkSize, sizeof(int));

		if(filein.eof())
			break;

		szChunk[4] = '\0';

		if(iNext == 0)
		{
			if(strcmp(szChunk, "RIFF") != 0)
			{
				if(pEditor->PrefGenerateLogFile())
					*pLog << "Error: Sound file \"" << szFilename2 << "\" does not begin with RIFF chunk!" << CErrorLog::endl;

				std::string szError = "Unable to load file \"";

				szError += szFilename2;
				szError += "\"!";

				if(pEditor->PrefGenerateLogFile())
					szError += "  Consult log.txt for details.";

				if(iShowErrorMessages)
					MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

				return 0;
			}
			else
			{
				iNext = 1;

				filein.read(szRiffType, 4);

				szRiffType[4] = '\0';

				if(strcmp(szRiffType, "WAVE") != 0)
				{
					if(pEditor->PrefGenerateLogFile())
						*pLog << "Error: Sound file \"" << szFilename2 << "\" contains unsupported RIFF format \"" << szRiffType << "\"!" << CErrorLog::endl;

					std::string szError = "Unable to load file \"";

					szError += szFilename2;
					szError += "\"!";

					if(pEditor->PrefGenerateLogFile())
						szError += "  Consult log.txt for details.";

					if(iShowErrorMessages)
						MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

					return 0;
				}

				continue;
			}
		}
		else
		{
			if(strcmp(szChunk, "fmt ") == 0)
			{
				filein.read((char *)&wFormatTag,       sizeof(short));
				filein.read((char *)&wChannels,        sizeof(USHORT));
				filein.read((char *)&dwSamplesPerSec,  sizeof(UINT));
				filein.read((char *)&dwAvgBytesPerSec, sizeof(UINT));
				filein.read((char *)&wBlockAlign,      sizeof(USHORT));
				filein.read((char *)&wBitsPerSample,   sizeof(USHORT));

				if(wFormatTag != 0x0001)
				{
					if(pEditor->PrefGenerateLogFile())
						*pLog << "Error: Sound file \"" << szFilename2 << "\" contains unsupported compression format (" << wFormatTag << ")!" << CErrorLog::endl;

					std::string szError = "Unable to load file \"";

					szError += szFilename2;
					szError += "\"!";

					if(pEditor->PrefGenerateLogFile())
						szError += "  Consult log.txt for details.";

					if(iShowErrorMessages)
						MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

					return 0;
				}

				iNext = 2;

				filein.seekg(iChunkSize - 16, std::ios::cur);
			}
			else if(strcmp(szChunk, "data") == 0)
			{
				if(iNext != 2)
				{
					if(pEditor->PrefGenerateLogFile())
						*pLog << "Error: Sound file \"" << szFilename2 << "\" contains data chunk before format chunk!" << CErrorLog::endl;

					std::string szError = "Unable to load file \"";

					szError += szFilename2;
					szError += "\"!";

					if(pEditor->PrefGenerateLogFile())
						szError += "  Consult log.txt for details.";

					if(iShowErrorMessages)
						MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

					return 0;
				}

				vData.resize(iChunkSize);

				filein.read((char *)&vData[0], iChunkSize);
			}
			else
			{
				if(pEditor->PrefGenerateLogFile())
					*pLog << "Warning: Sound file \"" << szFilename2 << "\" contains unsupported chunk.  Skipping." << CErrorLog::endl;

				filein.seekg(iChunkSize, std::ios::cur);
			}
		}
	}

	filein.close();

	int iResourceOffset = 42;

	m_vData2.resize(iResourceOffset + vData.size() / wBlockAlign);

	int iTemp;

#ifdef _MSC_VER
	__int64 iTemp64;
#else
	long long iTemp64;
#endif

	int i, j;

	if(wBitsPerSample == 8)
	{
		if(wChannels == 1)
		{
			memcpy(&m_vData2[iResourceOffset], &vData[0], vData.size());
		}
		else
		{
			for(i = 0; i < vData.size(); i += wChannels)
			{
				iTemp = 0;

				for(j = 0; j < wChannels; j++)
					iTemp += vData[i + j];

				iTemp /= wChannels;

				m_vData2[iResourceOffset + i / wChannels] = static_cast<UCHAR>(iTemp);
			}
		}
	}
	else if(wBitsPerSample == 16)
	{
		for(i = 0; i < vData.size() / 2; i += wChannels)
		{
			iTemp = 0;

			for(j = 0; j < wChannels; j++)
				iTemp += *(short *)&vData[(i + j) * 2];

			iTemp /= wChannels;

			iTemp >>= 8;

			iTemp += 0x80;

			m_vData2[iResourceOffset + i / wChannels] = static_cast<UCHAR>(iTemp);
		}
	}
	else if(wBitsPerSample == 24)
	{
		for(i = 0; i < vData.size() / 3; i += wChannels)
		{
			iTemp = 0;

			for(j = 0; j < wChannels; j++)
				iTemp += static_cast<int>(vData[(i + j) * 3]) | (int)(vData[(i + j) * 3 + 1] << 8) | (int)(vData[(i + j) * 3 + 2] << 16);

			iTemp /= wChannels;

			iTemp >>= 16;

			iTemp += 0x80;

			m_vData2[iResourceOffset + i / wChannels] = static_cast<UCHAR>(iTemp);
		}
	}
	else if(wBitsPerSample == 32)
	{
		for(i = 0; i < vData.size() / 4; i += wChannels)
		{
			iTemp64 = 0;

			for(j = 0; j < wChannels; j++)
				iTemp64 += *(int *)vData[(i + j) * 4];

			iTemp64 /= wChannels;

			iTemp64 >>= 24;

			iTemp64 += 0x80;

			m_vData2[iResourceOffset + i / wChannels] = static_cast<UCHAR>(iTemp64);
		}
	}
	else
	{
		if(pEditor->PrefGenerateLogFile())
			*pLog << "Error: Sound file \"" << szFilename2 << "\" contains bad number of bits per sample!" << CErrorLog::endl;

		std::string szError = "Unable to load file \"";

		szError += szFilename2;
		szError += "\"!";

		if(pEditor->PrefGenerateLogFile())
			szError += "  Consult log.txt for details.";

		if(iShowErrorMessages)
			MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		m_vData2.clear();

		m_pSndHeader  = NULL;
		m_pSnd2Header = NULL;
		m_pSndInfo    = NULL;
		m_pSndData    = NULL;

		return 0;
	}

	m_iIsDirty = 1;

	m_pSndHeader  = (qt::SndListResource *)&m_vData2[0];
	m_pSnd2Header = NULL;
	m_pSndInfo    = (qt::CmpSoundHeader *)&m_pSndHeader->dataPart[0];
	m_pSndData    = (UCHAR *)&m_pSndInfo->numFrames;

	m_pSndHeader->format                    = 0x0001;
	m_pSndHeader->numModifiers              = 1;
	m_pSndHeader->modifierPart[0].modNumber = 0x0005;
	m_pSndHeader->modifierPart[0].modInit   = 0x00000080;
	m_pSndHeader->numCommands               = 1;
	m_pSndHeader->commandPart[0].cmd        = 0x8051;
	m_pSndHeader->commandPart[0].param1     = 0x0000;
	m_pSndHeader->commandPart[0].param2     = 20;

	m_pSndInfo->samplePtr     = NULL;
	m_pSndInfo->numChannels   = m_vData2.size() - iResourceOffset;	// numChannels -> length
	m_pSndInfo->sampleRate    = dwSamplesPerSec << 16;
	m_pSndInfo->loopStart     = 0;
	m_pSndInfo->loopEnd       = 0;
	m_pSndInfo->encode        = qt::stdSH;
	m_pSndInfo->baseFrequency = 0x3C;

	m_iFormatCopy = 1;

	if(m_pWindow != NULL)
	{
		HWND hwndTextSampleRate = GetDlgItem(m_pWindow->GetHWND(), IDC_EDIT_SND_TEXT3);
		HWND hwndTextDataSize   = GetDlgItem(m_pWindow->GetHWND(), IDC_EDIT_SND_TEXT4);

		std::string szText = "Sample rate: ";
		szText += ToString(static_cast<double>(m_pSndInfo->sampleRate) / 65536.0);
		szText += " Hz";
		Static_SetText(hwndTextSampleRate, szText.c_str());

		szText = "Size: ";
		szText += ToString(m_vData2.size() - (m_pSndData - &m_vData2[0]));
		szText += " bytes";
		Static_SetText(hwndTextDataSize, szText.c_str());
	}
	else
	{
		m_vData.resize(m_vData2.size());

		memcpy(&m_vData[0], &m_vData2[0], m_vData2.size());

		m_vData2.clear();

		m_iFormat = m_iFormatCopy;

		if(m_iFormat == 1)
		{
			m_pSndHeader  = (qt::SndListResource *)&m_vData[0];
			m_pSnd2Header = NULL;
			m_pSndInfo    = (qt::CmpSoundHeader *)&m_pSndHeader->dataPart[0];
		}
		else
		{
			m_pSndHeader  = NULL;
			m_pSnd2Header = (qt::Snd2ListResource *)&m_vData[0];
			m_pSndInfo    = (qt::CmpSoundHeader *)&m_pSnd2Header->dataPart[0];
		}

		if(m_pSndInfo->encode == qt::stdSH)
			m_pSndData = (UCHAR *)&m_pSndInfo->numFrames;
		else
			m_pSndData = (UCHAR *)&m_pSndInfo->sampleArea[0];

		m_iIsDirty = 0;
	}

	return 1;
}

int CSndResource::FileExport(const char *szFilename, int iShowErrorMessages)
{
	if(m_vData.size() == 0)
		return 0;

	CEditor *pEditor = CEditor::GetCurrentEditor();
	CErrorLog *pLog  = CErrorLog::GetCurrentErrorLog();

	char szFilename2[MAX_PATH];

	if(szFilename == NULL)
	{
		strcpy_s(szFilename2, "");

		OPENFILENAME ofn;

		memset(&ofn, 0, sizeof(OPENFILENAME));

		ofn.lStructSize   = sizeof(OPENFILENAME);
		ofn.nMaxFile      = MAX_PATH;
		ofn.nMaxFileTitle = MAX_PATH;
		ofn.lpstrTitle    = "Export Sound Resource";
		ofn.lpstrFilter   = "Wave Files (*.wav)\0*.wav\0";
		ofn.nFilterIndex  = 1;
		ofn.lpstrDefExt   = "wav";
		ofn.Flags         = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
		ofn.hwndOwner     = m_pWindow->GetHWND();
		ofn.lpstrFile     = szFilename2;

		if(GetSaveFileName(&ofn) == 0)
			return 0;
	}
	else
	{
		strcpy_s(szFilename2, szFilename);
	}

	std::ofstream outfile;

	outfile.open(szFilename2, std::ios::out | std::ios::trunc | std::ios::binary);

	if(outfile.is_open() == 0)
	{
		if(pEditor->PrefGenerateLogFile())
			*pLog << "Error: Unable to open sound file \"" << szFilename2 << "\"!" << CErrorLog::endl;

		std::string szError = "Unable to load file \"";

		szError += szFilename2;
		szError += "\"!";

		if(pEditor->PrefGenerateLogFile())
			szError += "  Consult log.txt for details.";

		if(iShowErrorMessages)
			MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

		return 0;
	}

	char szRiff[5]        = "RIFF";
	char szRiffType[5]    = "WAVE";
	char szFormatChunk[5] = "fmt ";
	char szDataChunk[5]   = "data";

	int iSize;

	short  wFormatTag;
	USHORT wChannels;
	UINT   dwSamplesPerSec;
	UINT   dwAvgBytesPerSec;
	USHORT wBlockAlign;
	USHORT wBitsPerSample;

	std::vector<UCHAR> vOutputData;

	if(m_pSndInfo->encode == 0x00)
	{
		outfile.write(szRiff, 4);

		iSize = 36 + m_pSndInfo->numChannels;

		outfile.write((char *)&iSize, sizeof(int));
		outfile.write(szRiffType, 4);
		outfile.write(szFormatChunk, 4);

		iSize = 16;

		outfile.write((char *)&iSize, sizeof(int));

		wFormatTag = 0x0001;

		if((m_iFormat == 1) && ((m_pSndHeader->modifierPart[0].modInit) & (qt::initStereoMask) == qt::initStereo))
			wChannels = 2;
		else
			wChannels = 1;

		dwSamplesPerSec  = m_pSndInfo->sampleRate >> 16;
		dwAvgBytesPerSec = dwSamplesPerSec * wChannels;
		wBlockAlign      = wChannels;
		wBitsPerSample   = 8;

		outfile.write((char *)&wFormatTag,       sizeof(short));
		outfile.write((char *)&wChannels,        sizeof(USHORT));
		outfile.write((char *)&dwSamplesPerSec,  sizeof(UINT));
		outfile.write((char *)&dwAvgBytesPerSec, sizeof(UINT));
		outfile.write((char *)&wBlockAlign,      sizeof(USHORT));
		outfile.write((char *)&wBitsPerSample,   sizeof(USHORT));

		outfile.write(szDataChunk, 4);

		iSize = m_pSndInfo->numChannels;

		outfile.write((char *)&iSize, sizeof(int));

		outfile.write((char *)m_pSndData, iSize);
	}
	else
	{
		qt::SoundComponentData sndInputFormat;
		qt::SoundComponentData sndOutputFormat;

		UINT iInputFrames;
		UINT iInputBytes;
		UINT iInputBytesCopy;
		UINT iOutputBytes;

		qt::OSErr qtErr;

		memset(&sndInputFormat,  0, sizeof(qt::SoundComponentData));
		memset(&sndOutputFormat, 0, sizeof(qt::SoundComponentData));

		qtErr = qt::ParseSndHeader(&m_pSndHeader, &sndInputFormat, (ULONG *)&iInputFrames, NULL);

//		sndInputFormat.format      = m_pSndInfo->format;
//		sndInputFormat.numChannels = (short)m_pSndInfo->numChannels;
//		sndInputFormat.sampleSize  = m_pSndInfo->sampleSize;
//		sndInputFormat.sampleRate  = m_pSndInfo->sampleRate;
//		sndInputFormat.sampleCount = m_pSndInfo->numFrames;
//		sndInputFormat.buffer      = NULL;
//		sndInputFormat.reserved    = 0;

		sndOutputFormat.format      = qt::kSoundNotCompressed;
		sndOutputFormat.numChannels = sndInputFormat.numChannels;
		sndOutputFormat.sampleSize  = sndInputFormat.sampleSize;
		sndOutputFormat.sampleRate  = sndInputFormat.sampleRate;
		sndOutputFormat.sampleCount = 0;
		sndOutputFormat.buffer      = NULL;
		sndOutputFormat.reserved    = 0;

		qt::SoundConverter soundConverter;

		qtErr = qt::SoundConverterOpen(&sndInputFormat, &sndOutputFormat, &soundConverter);

		if(qtErr != qt::noErr)
		{
			if(pEditor->PrefGenerateLogFile())
				*pLog << "Error: Unable to open sound converter for compressed data!" << CErrorLog::endl;

			std::string szError = "Export failed.";

			if(pEditor->PrefGenerateLogFile())
				szError += "  Consult log.txt for details.";

			if(iShowErrorMessages)
				MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

			return 0;
		}

		iInputBytes = m_vData.size() - 84;
		iInputBytesCopy = iInputBytes;

		qtErr = qt::SoundConverterBeginConversion(soundConverter);

//		qtErr = qt::SoundConverterGetBufferSizes(soundConverter, iInputBytes, (ULONG *)&iInputFrames, (ULONG *)&iInputBytesCopy, (ULONG *)&iOutputBytes);

		iOutputBytes = sndInputFormat.sampleCount * (sndOutputFormat.sampleSize >> 3);

		vOutputData.resize(iOutputBytes);

		UINT iOutputFrames;

		qtErr = qt::SoundConverterConvertBuffer(soundConverter, &m_vData[84], m_pSndInfo->numFrames, &vOutputData[0], (ULONG *)&iOutputFrames, (ULONG *)&iOutputBytes);

		qtErr = qt::SoundConverterEndConversion(soundConverter, &vOutputData[iOutputBytes], (ULONG *)&iOutputFrames, (ULONG *)&iOutputBytes);

		if(qtErr != qt::noErr)
		{
			if(pEditor->PrefGenerateLogFile())
				*pLog << "Error: Sound data decompression failed!" << CErrorLog::endl;

			std::string szError = "Export failed.";

			if(pEditor->PrefGenerateLogFile())
				szError += "  Consult log.txt for details.";

			if(iShowErrorMessages)
				MessageBox(m_pWindow->GetHWND(), szError.c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);

			return 0;
		}

		qtErr = qt::SoundConverterClose(soundConverter);

		outfile.write(szRiff, 4);

		iSize = 36 + vOutputData.size();

		outfile.write((char *)&iSize, sizeof(int));
		outfile.write(szRiffType, 4);
		outfile.write(szFormatChunk, 4);

		iSize = 16;

		outfile.write((char *)&iSize, sizeof(int));

		wFormatTag       = 0x0001;
		wChannels        = m_pSndInfo->numChannels;
		dwSamplesPerSec  = m_pSndInfo->sampleRate >> 16;
		wBitsPerSample   = m_pSndInfo->sampleSize;
		wBlockAlign      = wChannels * ((wBitsPerSample + 7) >> 3);
		dwAvgBytesPerSec = dwSamplesPerSec * wBlockAlign;

		outfile.write((char *)&wFormatTag,       sizeof(short));
		outfile.write((char *)&wChannels,        sizeof(USHORT));
		outfile.write((char *)&dwSamplesPerSec,  sizeof(UINT));
		outfile.write((char *)&dwAvgBytesPerSec, sizeof(UINT));
		outfile.write((char *)&wBlockAlign,      sizeof(USHORT));
		outfile.write((char *)&wBitsPerSample,   sizeof(USHORT));

		outfile.write(szDataChunk, 4);

		iSize = vOutputData.size();

		outfile.write((char *)&iSize, sizeof(int));

		outfile.write((char *)&vOutputData[0], iSize);
	}

	outfile.close();

	return 1;
}

BOOL CSndResource::SndDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CSndResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CSndResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_SND_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_SND_OK)
			{
				pResource->CloseAndSave();
			}
			else if(iControlID == IDC_EDIT_SND_BUTTON1)
			{
				pResource->PlaySound();
			}
			else if(iControlID == IDM_SND_FILE_IMPORT)
			{
				pResource->FileImport(NULL, 1);
			}
			else if(iControlID == IDM_SND_FILE_EXPORT)
			{
				pResource->FileExport(NULL, 1);
			}
			else if(iControlID == IDM_SND_FILE_CLOSEANDSAVE)
			{
				pResource->CloseAndSave();
			}
			else if(iControlID == IDM_SND_FILE_CLOSEANDDONTSAVE)
			{
				pResource->CloseAndDontSave();
			}
			else
			{
				for(i = 0; i < NUM_SND_CONTROLS; i++)
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
