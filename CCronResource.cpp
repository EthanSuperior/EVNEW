// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CCronResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CCronResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CCronResource::CCronResource(void)
{
	m_iFirstDay   = -1;
	m_iFirstMonth = -1;
	m_iFirstYear  = -1;

	m_iLastDay   = -1;
	m_iLastMonth = -1;
	m_iLastYear  = -1;

	m_iRandom   = 100;
	m_iDuration = 0;

	m_iPreHoldoff  = 0;
	m_iPostHoldoff = 0;

	m_iFlags = 0x0000;

	memset(m_szEnableOn, 0, 255 * sizeof(char));
	memset(m_szOnStart,  0, 255 * sizeof(char));
	memset(m_szOnEnd,    0, 256 * sizeof(char));

	int i;

	for(i = 0; i < 8; i++)
	{
		m_cContribute[i] = 0x00;
		m_cRequire[i]    = 0x00;
	}

	m_iGovernment1     = -1;
	m_iGovernmentNews1 = -1;
	m_iGovernment2     = -1;
	m_iGovernmentNews2 = -1;
	m_iGovernment3     = -1;
	m_iGovernmentNews3 = -1;
	m_iGovernment4     = -1;
	m_iGovernmentNews4 = -1;

	m_iIndependentNews = -1;
}

CCronResource::~CCronResource(void)
{

}

int CCronResource::GetType(void)
{
	return CNR_TYPE_CRON;
}

int CCronResource::GetSize(void)
{
	return 822;
}

int CCronResource::GetDialogID(void)
{
	return IDD_EDIT_CRON;
}

DLGPROCNOCALLBACK CCronResource::GetDialogProc(void)
{
	return CronDlgProc;
}

int CCronResource::GetNumFields(void)
{
	return NUM_CRON_FIELDS;
}

const std::string * CCronResource::GetFieldNames(void)
{
	return g_szCronFields;
}

int CCronResource::Save(char *pOutput)
{
	SwapEndians();

	*(short *)pOutput = m_iFirstDay;        pOutput += sizeof(short);
	*(short *)pOutput = m_iFirstMonth;      pOutput += sizeof(short);
	*(short *)pOutput = m_iFirstYear;       pOutput += sizeof(short);
	*(short *)pOutput = m_iLastDay;         pOutput += sizeof(short);
	*(short *)pOutput = m_iLastMonth;       pOutput += sizeof(short);
	*(short *)pOutput = m_iLastYear;        pOutput += sizeof(short);
	*(short *)pOutput = m_iRandom;          pOutput += sizeof(short);
	*(short *)pOutput = m_iDuration;        pOutput += sizeof(short);
	*(short *)pOutput = m_iPreHoldoff;      pOutput += sizeof(short);
	*(short *)pOutput = m_iPostHoldoff;     pOutput += sizeof(short);
	*(short *)pOutput = m_iIndependentNews; pOutput += sizeof(short);
	*(USHORT *)pOutput = m_iFlags;          pOutput += sizeof(USHORT);

	memcpy(pOutput, m_szEnableOn, 255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_szOnStart,  255 * sizeof(char)); pOutput += 255 * sizeof(char);
	memcpy(pOutput, m_szOnEnd,    256 * sizeof(char)); pOutput += 256 * sizeof(char);
	memcpy(pOutput, m_cContribute,  8 * sizeof(char)); pOutput +=   8 * sizeof(char);
	memcpy(pOutput, m_cRequire,     8 * sizeof(char)); pOutput +=   8 * sizeof(char);

	*(short *)pOutput = m_iGovernment1;     pOutput += sizeof(short);
	*(short *)pOutput = m_iGovernment2;     pOutput += sizeof(short);
	*(short *)pOutput = m_iGovernment3;     pOutput += sizeof(short);
	*(short *)pOutput = m_iGovernment4;     pOutput += sizeof(short);
	*(short *)pOutput = m_iGovernmentNews1; pOutput += sizeof(short);
	*(short *)pOutput = m_iGovernmentNews2; pOutput += sizeof(short);
	*(short *)pOutput = m_iGovernmentNews3; pOutput += sizeof(short);
	*(short *)pOutput = m_iGovernmentNews4; pOutput += sizeof(short);

	SwapEndians();

	return 1;
}

int CCronResource::Load(char *pInput, int iSize)
{
	m_iFirstDay        = *(short *)pInput; pInput += sizeof(short);
	m_iFirstMonth      = *(short *)pInput; pInput += sizeof(short);
	m_iFirstYear       = *(short *)pInput; pInput += sizeof(short);
	m_iLastDay         = *(short *)pInput; pInput += sizeof(short);
	m_iLastMonth       = *(short *)pInput; pInput += sizeof(short);
	m_iLastYear        = *(short *)pInput; pInput += sizeof(short);
	m_iRandom          = *(short *)pInput; pInput += sizeof(short);
	m_iDuration        = *(short *)pInput; pInput += sizeof(short);
	m_iPreHoldoff      = *(short *)pInput; pInput += sizeof(short);
	m_iPostHoldoff     = *(short *)pInput; pInput += sizeof(short);
	m_iIndependentNews = *(short *)pInput; pInput += sizeof(short);
	m_iFlags           = *(USHORT *)pInput; pInput += sizeof(USHORT);

	memcpy(m_szEnableOn,  pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	memcpy(m_szOnStart,   pInput, 255 * sizeof(char)); pInput += 255 * sizeof(char);
	memcpy(m_szOnEnd,     pInput, 256 * sizeof(char)); pInput += 256 * sizeof(char);
	memcpy(m_cContribute, pInput,   8 * sizeof(char)); pInput +=   8 * sizeof(char);
	memcpy(m_cRequire,    pInput,   8 * sizeof(char)); pInput +=   8 * sizeof(char);

	m_iGovernment1     = *(short *)pInput; pInput += sizeof(short);
	m_iGovernment2     = *(short *)pInput; pInput += sizeof(short);
	m_iGovernment3     = *(short *)pInput; pInput += sizeof(short);
	m_iGovernment4     = *(short *)pInput; pInput += sizeof(short);
	m_iGovernmentNews1 = *(short *)pInput; pInput += sizeof(short);
	m_iGovernmentNews2 = *(short *)pInput; pInput += sizeof(short);
	m_iGovernmentNews3 = *(short *)pInput; pInput += sizeof(short);
	m_iGovernmentNews4 = *(short *)pInput; pInput += sizeof(short);

	SwapEndians();

	return 1;
}

int CCronResource::SwapEndians(void)
{
	m_iFirstDay        = SwapEndianShort(m_iFirstDay);
	m_iFirstMonth      = SwapEndianShort(m_iFirstMonth);
	m_iFirstYear       = SwapEndianShort(m_iFirstYear);
	m_iLastDay         = SwapEndianShort(m_iLastDay);
	m_iLastMonth       = SwapEndianShort(m_iLastMonth);
	m_iLastYear        = SwapEndianShort(m_iLastYear);
	m_iRandom          = SwapEndianShort(m_iRandom);
	m_iDuration        = SwapEndianShort(m_iDuration);
	m_iPreHoldoff      = SwapEndianShort(m_iPreHoldoff);
	m_iPostHoldoff     = SwapEndianShort(m_iPostHoldoff);
	m_iIndependentNews = SwapEndianShort(m_iIndependentNews);
	m_iFlags           = SwapEndianShort(m_iFlags);
	m_iGovernment1     = SwapEndianShort(m_iGovernment1);
	m_iGovernment2     = SwapEndianShort(m_iGovernment2);
	m_iGovernment3     = SwapEndianShort(m_iGovernment3);
	m_iGovernment4     = SwapEndianShort(m_iGovernment4);
	m_iGovernmentNews1 = SwapEndianShort(m_iGovernmentNews1);
	m_iGovernmentNews2 = SwapEndianShort(m_iGovernmentNews2);
	m_iGovernmentNews3 = SwapEndianShort(m_iGovernmentNews3);
	m_iGovernmentNews4 = SwapEndianShort(m_iGovernmentNews4);

	return 1;
}

int CCronResource::SaveToText(std::ostream & output)
{
	output << m_iFirstDay        << '\t'
		   << m_iFirstMonth      << '\t'
		   << m_iFirstYear       << '\t'
		   << m_iLastDay         << '\t'
		   << m_iLastMonth       << '\t'
		   << m_iLastYear        << '\t'
		   << m_iRandom          << '\t'
		   << m_iDuration        << '\t'
		   << m_iPreHoldoff      << '\t'
		   << m_iPostHoldoff     << '\t';

	PrintTextField(output, m_szEnableOn, '\t');
	PrintTextField(output, m_szOnStart,  '\t');
	PrintTextField(output, m_szOnEnd,    '\t');

	PrintHex64Field(output, m_cContribute, '\t');
	PrintHex64Field(output, m_cRequire,    '\t');

	output << m_iGovernment1     << '\t'
		   << m_iGovernmentNews1 << '\t'
		   << m_iGovernment2     << '\t'
		   << m_iGovernmentNews2 << '\t'
		   << m_iGovernment3     << '\t'
		   << m_iGovernmentNews3 << '\t'
		   << m_iGovernment4     << '\t'
		   << m_iGovernmentNews4 << '\t'
		   << m_iIndependentNews << '\t';

	PrintHex16Field(output, (char *)&m_iFlags, '\t');

	return 1;
}

int CCronResource::LoadFromText(std::istream & input)
{
	input >> m_iFirstDay
		  >> m_iFirstMonth
		  >> m_iFirstYear
		  >> m_iLastDay
		  >> m_iLastMonth
		  >> m_iLastYear
		  >> m_iRandom
		  >> m_iDuration
		  >> m_iPreHoldoff
		  >> m_iPostHoldoff;

	input.ignore(1);

	ReadTextField(input, m_szEnableOn, 255);
	ReadTextField(input, m_szOnStart,  255);
	ReadTextField(input, m_szOnEnd,    256);

	ReadHex64Field(input, m_cContribute);
	ReadHex64Field(input, m_cRequire);

	input >> m_iGovernment1
		  >> m_iGovernmentNews1
		  >> m_iGovernment2
		  >> m_iGovernmentNews2
		  >> m_iGovernment3
		  >> m_iGovernmentNews3
		  >> m_iGovernment4
		  >> m_iGovernmentNews4
		  >> m_iIndependentNews;

	ReadHex16Field(input, (char *)&m_iFlags);

	return 1;
}

int CCronResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "cron ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_CRON_EDIT1, CCONTROL_TYPE_INT, IDS_STRING176);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_CRON_EDIT2, CCONTROL_TYPE_INT, IDS_STRING177);
	m_controls[1].SetInt(m_iFirstDay);
	m_controls[2].Create(hwnd, IDC_EDIT_CRON_EDIT3, CCONTROL_TYPE_INT, IDS_STRING178);
	m_controls[2].SetInt(m_iFirstMonth);
	m_controls[3].Create(hwnd, IDC_EDIT_CRON_EDIT4, CCONTROL_TYPE_INT, IDS_STRING179);
	m_controls[3].SetInt(m_iFirstYear);
	m_controls[4].Create(hwnd, IDC_EDIT_CRON_EDIT5, CCONTROL_TYPE_INT, IDS_STRING180);
	m_controls[4].SetInt(m_iLastDay);
	m_controls[5].Create(hwnd, IDC_EDIT_CRON_EDIT6, CCONTROL_TYPE_INT, IDS_STRING181);
	m_controls[5].SetInt(m_iLastMonth);
	m_controls[6].Create(hwnd, IDC_EDIT_CRON_EDIT7, CCONTROL_TYPE_INT, IDS_STRING182);
	m_controls[6].SetInt(m_iLastYear);
	m_controls[7].Create(hwnd, IDC_EDIT_CRON_EDIT8, CCONTROL_TYPE_INT, IDS_STRING183);
	m_controls[7].SetInt(m_iRandom);
	m_controls[8].Create(hwnd, IDC_EDIT_CRON_EDIT9, CCONTROL_TYPE_INT, IDS_STRING184);
	m_controls[8].SetInt(m_iDuration);
	m_controls[9].Create(hwnd, IDC_EDIT_CRON_EDIT10, CCONTROL_TYPE_INT, IDS_STRING185);
	m_controls[9].SetInt(m_iPreHoldoff);
	m_controls[10].Create(hwnd, IDC_EDIT_CRON_EDIT11, CCONTROL_TYPE_INT, IDS_STRING186);
	m_controls[10].SetInt(m_iPostHoldoff);
	m_controls[11].Create(hwnd, IDC_EDIT_CRON_EDIT12, CCONTROL_TYPE_STR255, IDS_STRING189);
	m_controls[11].SetString(m_szEnableOn);
	m_controls[12].Create(hwnd, IDC_EDIT_CRON_EDIT13, CCONTROL_TYPE_STR255, IDS_STRING190);
	m_controls[12].SetString(m_szOnStart);
	m_controls[13].Create(hwnd, IDC_EDIT_CRON_EDIT14, CCONTROL_TYPE_STR256, IDS_STRING191);
	m_controls[13].SetString(m_szOnEnd);
	m_controls[14].Create(hwnd, IDC_EDIT_CRON_EDIT15, CCONTROL_TYPE_HEXINT64, IDS_STRING192);
	m_controls[14].SetString(m_cContribute);
	m_controls[15].Create(hwnd, IDC_EDIT_CRON_EDIT16, CCONTROL_TYPE_HEXINT64, IDS_STRING193);
	m_controls[15].SetString(m_cRequire);
	m_controls[16].Create(hwnd, IDC_EDIT_CRON_EDIT17, CCONTROL_TYPE_INT, IDS_STRING194);
	m_controls[16].SetInt(m_iGovernment1);
	m_controls[17].Create(hwnd, IDC_EDIT_CRON_EDIT18, CCONTROL_TYPE_INT, IDS_STRING194);
	m_controls[17].SetInt(m_iGovernmentNews1);
	m_controls[18].Create(hwnd, IDC_EDIT_CRON_EDIT19, CCONTROL_TYPE_INT, IDS_STRING194);
	m_controls[18].SetInt(m_iGovernment2);
	m_controls[19].Create(hwnd, IDC_EDIT_CRON_EDIT20, CCONTROL_TYPE_INT, IDS_STRING194);
	m_controls[19].SetInt(m_iGovernmentNews2);
	m_controls[20].Create(hwnd, IDC_EDIT_CRON_EDIT21, CCONTROL_TYPE_INT, IDS_STRING194);
	m_controls[20].SetInt(m_iGovernment3);
	m_controls[21].Create(hwnd, IDC_EDIT_CRON_EDIT22, CCONTROL_TYPE_INT, IDS_STRING194);
	m_controls[21].SetInt(m_iGovernmentNews3);
	m_controls[22].Create(hwnd, IDC_EDIT_CRON_EDIT23, CCONTROL_TYPE_INT, IDS_STRING194);
	m_controls[22].SetInt(m_iGovernment4);
	m_controls[23].Create(hwnd, IDC_EDIT_CRON_EDIT24, CCONTROL_TYPE_INT, IDS_STRING194);
	m_controls[23].SetInt(m_iGovernmentNews4);
	m_controls[24].Create(hwnd, IDC_EDIT_CRON_EDIT25, CCONTROL_TYPE_INT, IDS_STRING195);
	m_controls[24].SetInt(m_iIndependentNews);
	m_controls[25].Create(hwnd, IDC_EDIT_CRON_CHECK1, CCONTROL_TYPE_CHECK, IDS_STRING187);
	m_controls[25].SetInt(m_iFlags & 0x0001);
	m_controls[26].Create(hwnd, IDC_EDIT_CRON_CHECK2, CCONTROL_TYPE_CHECK, IDS_STRING188);
	m_controls[26].SetInt(m_iFlags & 0x0002);
	m_controls[27].Create(hwnd, IDC_EDIT_CRON_EDIT26, CCONTROL_TYPE_STR256, IDS_STRING196);
	m_controls[27].SetString(m_szName);

	return 1;
}

int CCronResource::CloseAndSave(void)
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

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[27].GetString()) != 0))
		iIDOrNameChanged = 1;

	m_iID         = m_controls[0].GetInt();

	m_iFirstDay   = m_controls[1].GetInt();
	m_iFirstMonth = m_controls[2].GetInt();
	m_iFirstYear  = m_controls[3].GetInt();

	m_iLastDay   = m_controls[4].GetInt();
	m_iLastMonth = m_controls[5].GetInt();
	m_iLastYear  = m_controls[6].GetInt();

	m_iRandom   = m_controls[7].GetInt();
	m_iDuration = m_controls[8].GetInt();

	m_iPreHoldoff  = m_controls[9].GetInt();
	m_iPostHoldoff = m_controls[10].GetInt();

	strcpy(m_szEnableOn, m_controls[11].GetString());
	strcpy(m_szOnStart,  m_controls[12].GetString());
	strcpy(m_szOnEnd,    m_controls[13].GetString());

	memcpy(m_cContribute, m_controls[14].GetString(), 8 * sizeof(char));
	memcpy(m_cRequire,    m_controls[15].GetString(), 8 * sizeof(char));

	m_iGovernment1     = m_controls[16].GetInt();
	m_iGovernmentNews1 = m_controls[17].GetInt();
	m_iGovernment2     = m_controls[18].GetInt();
	m_iGovernmentNews2 = m_controls[19].GetInt();
	m_iGovernment3     = m_controls[20].GetInt();
	m_iGovernmentNews3 = m_controls[21].GetInt();
	m_iGovernment4     = m_controls[22].GetInt();
	m_iGovernmentNews4 = m_controls[23].GetInt();

	m_iIndependentNews = m_controls[24].GetInt();

	m_iFlags = 0x0000;

	m_iFlags |= m_controls[25].GetInt() << 0;
	m_iFlags |= m_controls[26].GetInt() << 1;

	strcpy(m_szName, m_controls[27].GetString());

	int i;

	for(i = 0; i < NUM_CRON_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CCronResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_CRON_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

void CCronResource::RegisterNCB()
{
	Workspace::RegisterNCB(m_szOnStart);
	Workspace::RegisterNCB(m_szOnEnd);
}


BOOL CCronResource::CronDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CCronResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CCronResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_CRON_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_CRON_OK)
			{
				pResource->CloseAndSave();
			}
			else if(iControlID == IDC_EDIT_CRON_BUTTON1)
			{
				char cValue[8];

				memcpy(cValue, pResource->m_controls[14].GetString(), 8);

				pResource->m_bitFieldControl.DoDialog(pResource->m_pWindow, 64, cValue);

				pResource->m_controls[14].SetString(cValue);
			}
			else if(iControlID == IDC_EDIT_CRON_BUTTON2)
			{
				char cValue[8];

				memcpy(cValue, pResource->m_controls[15].GetString(), 8);

				pResource->m_bitFieldControl.DoDialog(pResource->m_pWindow, 64, cValue);

				pResource->m_controls[15].SetString(cValue);
			}
			else
			{
				for(i = 0; i < NUM_CRON_CONTROLS; i++)
				{
					if(iControlID == pResource->m_controls[i].GetControlID())
					{
						pResource->m_controls[i].ProcessMessage(iNotifyCode);

						break;
					}
				}
			}

			if (iNotifyCode != EN_UPDATE && iNotifyCode != EN_CHANGE) return TRUE;

			if (iControlID == IDC_EDIT_CRON_EDIT9 || iControlID == IDC_EDIT_CRON_EDIT10 || iControlID == IDC_EDIT_CRON_EDIT11)
			{
				auto wait = [](int n) {
					std::string r;
					for (int i = 0; i < n; i++)r += "_ ";
					return r;
					};
				std::string szText = "_: Wait S:OnStart E:OnEnd B:Both ...:Non-teminating\n";
				int iPreHoldoff = pResource->m_controls[9].GetInt();
				if (iPreHoldoff < 0) iPreHoldoff = 0;
				int iPostHoldoff = pResource->m_controls[10].GetInt();
				if (iPostHoldoff < 0) iPostHoldoff = 0;
				int iDuration = pResource->m_controls[8].GetInt();
				if (iDuration < 0) szText = "Invalid duration - Will NEVER Execute";
				else if (iPreHoldoff == 0) {
					if (iDuration == 0) {
						if (iPostHoldoff == 0) szText += "B E;";
						else szText += "B "+ wait(--iPostHoldoff)+";";
					}
					else {
						if (iPostHoldoff == 0) szText += "S " + wait(--iDuration) + "E;";
						else szText += "S " + wait(--iPostHoldoff) + "E E E ...";
					}
				}
				else {
					if (iDuration == 0) {
						if (iPostHoldoff == 0) szText += wait(iPreHoldoff) + "B E;";
						else szText += wait(iPreHoldoff) + "B E "+ wait(iPreHoldoff) +";";
					}
					else {
						if (iPostHoldoff == 0) szText += wait(iPreHoldoff) + "S " + wait(--iDuration) + "E;";
						else {
							szText += wait(iPreHoldoff) + "S " + wait(--iDuration) + "E "
								+ wait(iPreHoldoff - 1) + "B. E " + wait(iPreHoldoff) +";";
						}
					}
				}
				Static_SetText(GetDlgItem(hwnd, IDC_EDIT_CRON_TEXT36), szText.c_str());			
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
