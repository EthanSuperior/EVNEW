// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CRoidResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CRoidResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CRoidResource::CRoidResource(void)
{
	m_iStrength = 1;
	m_iSpinRate = 100;

	m_iYieldType   = -1;
	m_iYieldAmount =  0;

	m_iParticleCount = 0;
	m_iParticleColor = 0x00000000;

	m_iFragmentType1 = -1;
	m_iFragmentType2 = -1;
	m_iFragmentCount =  0;

	m_iExplosionType = -1;

	m_iMass = 1;
}

CRoidResource::~CRoidResource(void)
{

}

int CRoidResource::GetType(void)
{
	return CNR_TYPE_ROID;
}

int CRoidResource::GetSize(void)
{
	return 40;
}

int CRoidResource::GetDialogID(void)
{
	return IDD_EDIT_ROID;
}

DLGPROCNOCALLBACK CRoidResource::GetDialogProc(void)
{
	return RoidDlgProc;
}

int CRoidResource::GetNumFields(void)
{
	return NUM_ROID_FIELDS;
}

const std::string * CRoidResource::GetFieldNames(void)
{
	return g_szRoidFields;
}

int CRoidResource::Save(char *pOutput)
{
	SwapEndians();

	*(short *)pOutput = m_iStrength;      pOutput += sizeof(short);
	*(short *)pOutput = m_iSpinRate;      pOutput += sizeof(short);
	*(short *)pOutput = m_iYieldType;     pOutput += sizeof(short);
	*(short *)pOutput = m_iYieldAmount;   pOutput += sizeof(short);
	*(short *)pOutput = m_iParticleCount; pOutput += sizeof(short);
	*(UINT  *)pOutput = m_iParticleColor; pOutput += sizeof(UINT);
	*(short *)pOutput = m_iFragmentType1; pOutput += sizeof(short);
	*(short *)pOutput = m_iFragmentType2; pOutput += sizeof(short);
	*(short *)pOutput = m_iFragmentCount; pOutput += sizeof(short);
	*(short *)pOutput = m_iExplosionType; pOutput += sizeof(short);
	*(short *)pOutput = m_iMass;          pOutput += sizeof(short);

	SwapEndians();

	return 1;
}

int CRoidResource::Load(char *pInput, int iSize)
{
	m_iStrength      = *(short *)pInput; pInput += sizeof(short);
	m_iSpinRate      = *(short *)pInput; pInput += sizeof(short);
	m_iYieldType     = *(short *)pInput; pInput += sizeof(short);
	m_iYieldAmount   = *(short *)pInput; pInput += sizeof(short);
	m_iParticleCount = *(short *)pInput; pInput += sizeof(short);
	m_iParticleColor = *(UINT  *)pInput; pInput += sizeof(UINT);
	m_iFragmentType1 = *(short *)pInput; pInput += sizeof(short);
	m_iFragmentType2 = *(short *)pInput; pInput += sizeof(short);
	m_iFragmentCount = *(short *)pInput; pInput += sizeof(short);
	m_iExplosionType = *(short *)pInput; pInput += sizeof(short);
	m_iMass          = *(short *)pInput; pInput += sizeof(short);

	SwapEndians();

	return 1;
}

int CRoidResource::SwapEndians(void)
{
	m_iStrength      = SwapEndianShort(m_iStrength);
	m_iSpinRate      = SwapEndianShort(m_iSpinRate);
	m_iYieldType     = SwapEndianShort(m_iYieldType);
	m_iYieldAmount   = SwapEndianShort(m_iYieldAmount);
	m_iParticleCount = SwapEndianShort(m_iParticleCount);
	m_iParticleColor = SwapEndianInt(m_iParticleColor);
	m_iFragmentType1 = SwapEndianShort(m_iFragmentType1);
	m_iFragmentType2 = SwapEndianShort(m_iFragmentType2);
	m_iFragmentCount = SwapEndianShort(m_iFragmentCount);
	m_iExplosionType = SwapEndianShort(m_iExplosionType);
	m_iMass          = SwapEndianShort(m_iMass);

	return 1;
}

int CRoidResource::SaveToText(std::ostream & output)
{
	output << m_iStrength      << '\t'
		   << m_iSpinRate      << '\t'
		   << m_iYieldType     << '\t'
		   << m_iYieldAmount   << '\t'
		   << m_iParticleCount << '\t';

	PrintHex32Field(output, (char *)&m_iParticleColor, '\t');

	output << m_iFragmentType1 << '\t'
		   << m_iFragmentType2 << '\t'
		   << m_iFragmentCount << '\t'
		   << m_iExplosionType << '\t'
		   << m_iMass          << '\t';

	return 1;
}

int CRoidResource::LoadFromText(std::istream & input)
{
	input >> m_iStrength
		  >> m_iSpinRate
		  >> m_iYieldType
		  >> m_iYieldAmount
		  >> m_iParticleCount
		  >> m_iParticleColor;

	ReadHex32Field(input, (char *)&m_iParticleColor);

	input >> m_iFragmentType1
		  >> m_iFragmentType2
		  >> m_iFragmentCount
		  >> m_iExplosionType
		  >> m_iMass;

	input.ignore(1);

	return 1;
}

int CRoidResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "roid ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_ROID_EDIT1, CCONTROL_TYPE_INT, IDS_STRING624);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_ROID_EDIT2, CCONTROL_TYPE_INT, IDS_STRING625);
	m_controls[1].SetInt(m_iStrength);
	m_controls[2].Create(hwnd, IDC_EDIT_ROID_EDIT3, CCONTROL_TYPE_INT, IDS_STRING626);
	m_controls[2].SetInt(m_iSpinRate);
	m_controls[3].Create(hwnd, IDC_EDIT_ROID_EDIT4, CCONTROL_TYPE_INT, IDS_STRING627);
	m_controls[3].SetInt(m_iYieldType);
	m_controls[4].Create(hwnd, IDC_EDIT_ROID_EDIT5, CCONTROL_TYPE_INT, IDS_STRING628);
	m_controls[4].SetInt(m_iYieldAmount);
	m_controls[5].Create(hwnd, IDC_EDIT_ROID_EDIT6, CCONTROL_TYPE_INT, IDS_STRING629);
	m_controls[5].SetInt(m_iParticleCount);
	m_controls[6].Create(hwnd, IDC_EDIT_ROID_BUTTON7, CCONTROL_TYPE_COLOR, IDS_STRING630);
	m_controls[6].SetInt(m_iParticleColor);
	m_controls[7].Create(hwnd, IDC_EDIT_ROID_EDIT8, CCONTROL_TYPE_INT, IDS_STRING631);
	m_controls[7].SetInt(m_iFragmentType1);
	m_controls[8].Create(hwnd, IDC_EDIT_ROID_EDIT9, CCONTROL_TYPE_INT, IDS_STRING631);
	m_controls[8].SetInt(m_iFragmentType2);
	m_controls[9].Create(hwnd, IDC_EDIT_ROID_EDIT10, CCONTROL_TYPE_INT, IDS_STRING632);
	m_controls[9].SetInt(m_iFragmentCount);
	m_controls[10].Create(hwnd, IDC_EDIT_ROID_EDIT11, CCONTROL_TYPE_INT, IDS_STRING633);
	m_controls[10].SetInt(m_iExplosionType);
	m_controls[11].Create(hwnd, IDC_EDIT_ROID_EDIT12, CCONTROL_TYPE_INT, IDS_STRING634);
	m_controls[11].SetInt(m_iMass);
	m_controls[12].Create(hwnd, IDC_EDIT_ROID_EDIT13, CCONTROL_TYPE_STR256, IDS_STRING635);
	m_controls[12].SetString(m_szName);

	return 1;
}

int CRoidResource::CloseAndSave(void)
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

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[12].GetString()) != 0))
		iIDOrNameChanged = 1;

	m_iID            = m_controls[0].GetInt();

	m_iStrength      = m_controls[1].GetInt();
	m_iSpinRate      = m_controls[2].GetInt();

	m_iYieldType     = m_controls[3].GetInt();
	m_iYieldAmount   = m_controls[4].GetInt();

	m_iParticleCount = m_controls[5].GetInt();
	m_iParticleColor = m_controls[6].GetInt();

	m_iFragmentType1 = m_controls[7].GetInt();
	m_iFragmentType2 = m_controls[8].GetInt();
	m_iFragmentCount = m_controls[9].GetInt();

	m_iExplosionType = m_controls[10].GetInt();

	m_iMass          = m_controls[11].GetInt();

	strcpy(m_szName, m_controls[12].GetString());

	int i;

	for(i = 0; i < NUM_ROID_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CRoidResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_ROID_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CRoidResource::RoidDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CRoidResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CRoidResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_ROID_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_ROID_OK)
			{
				pResource->CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_ROID_CONTROLS; i++)
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
