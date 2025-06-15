// EVNEW - Escape Velocity: Nova Editor for Windows
// By Adam Rosenfield
// (c) 2003 All Rights Reserved

// File CDudeResource.cpp

////////////////////////////////////////////////////////////////
//////////////////////////	INCLUDES  //////////////////////////
////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>

#include "CWindow.h"

#include "EVNEW.h"
#include "CNovaResource.h"
#include "CDudeResource.h"

#include "resource.h"

////////////////////////////////////////////////////////////////
///////////////////  CLASS MEMBER FUNCTIONS  ///////////////////
////////////////////////////////////////////////////////////////

CDudeResource::CDudeResource(void)
{
	m_iAIType     = 1;
	m_iGovernment = -1;

	m_iInfoTypes = 0x0000;
	m_iFlags     = 0x0000;

	int i;

	for(i = 0; i < 16; i++)
	{
		m_iShipTypes[i]         = 0;
		m_iShipProbabilities[i] = 0;
	}
}

CDudeResource::~CDudeResource(void)
{

}

int CDudeResource::GetType(void)
{
	return CNR_TYPE_DUDE;
}

int CDudeResource::GetSize(void)
{
	return 88;
}

int CDudeResource::GetDialogID(void)
{
	return IDD_EDIT_DUDE;
}

DLGPROCNOCALLBACK CDudeResource::GetDialogProc(void)
{
	return DudeDlgProc;
}

int CDudeResource::GetNumFields(void)
{
	return NUM_DUDE_FIELDS;
}

const std::string * CDudeResource::GetFieldNames(void)
{
	return g_szDudeFields;
}

int CDudeResource::Save(char *pOutput)
{
	SwapEndians();

	*(short *)pOutput = m_iAIType;                pOutput += sizeof(short);
	*(short *)pOutput = m_iGovernment;            pOutput += sizeof(short);
	*(USHORT *)pOutput = m_iFlags;                pOutput += sizeof(USHORT);
	*(USHORT *)pOutput = m_iInfoTypes;            pOutput += sizeof(USHORT);
	*(short *)pOutput = m_iShipTypes[0];          pOutput += sizeof(short);
	*(short *)pOutput = m_iShipTypes[1];          pOutput += sizeof(short);
	*(short *)pOutput = m_iShipTypes[2];          pOutput += sizeof(short);
	*(short *)pOutput = m_iShipTypes[3];          pOutput += sizeof(short);
	*(short *)pOutput = m_iShipTypes[4];          pOutput += sizeof(short);
	*(short *)pOutput = m_iShipTypes[5];          pOutput += sizeof(short);
	*(short *)pOutput = m_iShipTypes[6];          pOutput += sizeof(short);
	*(short *)pOutput = m_iShipTypes[7];          pOutput += sizeof(short);
	*(short *)pOutput = m_iShipTypes[8];          pOutput += sizeof(short);
	*(short *)pOutput = m_iShipTypes[9];          pOutput += sizeof(short);
	*(short *)pOutput = m_iShipTypes[10];         pOutput += sizeof(short);
	*(short *)pOutput = m_iShipTypes[11];         pOutput += sizeof(short);
	*(short *)pOutput = m_iShipTypes[12];         pOutput += sizeof(short);
	*(short *)pOutput = m_iShipTypes[13];         pOutput += sizeof(short);
	*(short *)pOutput = m_iShipTypes[14];         pOutput += sizeof(short);
	*(short *)pOutput = m_iShipTypes[15];         pOutput += sizeof(short);
	*(short *)pOutput = m_iShipProbabilities[0];  pOutput += sizeof(short);
	*(short *)pOutput = m_iShipProbabilities[1];  pOutput += sizeof(short);
	*(short *)pOutput = m_iShipProbabilities[2];  pOutput += sizeof(short);
	*(short *)pOutput = m_iShipProbabilities[3];  pOutput += sizeof(short);
	*(short *)pOutput = m_iShipProbabilities[4];  pOutput += sizeof(short);
	*(short *)pOutput = m_iShipProbabilities[5];  pOutput += sizeof(short);
	*(short *)pOutput = m_iShipProbabilities[6];  pOutput += sizeof(short);
	*(short *)pOutput = m_iShipProbabilities[7];  pOutput += sizeof(short);
	*(short *)pOutput = m_iShipProbabilities[8];  pOutput += sizeof(short);
	*(short *)pOutput = m_iShipProbabilities[9];  pOutput += sizeof(short);
	*(short *)pOutput = m_iShipProbabilities[10]; pOutput += sizeof(short);
	*(short *)pOutput = m_iShipProbabilities[11]; pOutput += sizeof(short);
	*(short *)pOutput = m_iShipProbabilities[12]; pOutput += sizeof(short);
	*(short *)pOutput = m_iShipProbabilities[13]; pOutput += sizeof(short);
	*(short *)pOutput = m_iShipProbabilities[14]; pOutput += sizeof(short);
	*(short *)pOutput = m_iShipProbabilities[15]; pOutput += sizeof(short);

	SwapEndians();

	return 1;
}

int CDudeResource::Load(char *pInput, int iSize)
{
	m_iAIType                = *(short *)pInput; pInput += sizeof(short);
	m_iGovernment            = *(USHORT *)pInput; pInput += sizeof(short);
	m_iFlags                 = *(USHORT *)pInput; pInput += sizeof(USHORT);
	m_iInfoTypes             = *(short *)pInput; pInput += sizeof(USHORT);
	m_iShipTypes[0]          = *(short *)pInput; pInput += sizeof(short);
	m_iShipTypes[1]          = *(short *)pInput; pInput += sizeof(short);
	m_iShipTypes[2]          = *(short *)pInput; pInput += sizeof(short);
	m_iShipTypes[3]          = *(short *)pInput; pInput += sizeof(short);
	m_iShipTypes[4]          = *(short *)pInput; pInput += sizeof(short);
	m_iShipTypes[5]          = *(short *)pInput; pInput += sizeof(short);
	m_iShipTypes[6]          = *(short *)pInput; pInput += sizeof(short);
	m_iShipTypes[7]          = *(short *)pInput; pInput += sizeof(short);
	m_iShipTypes[8]          = *(short *)pInput; pInput += sizeof(short);
	m_iShipTypes[9]          = *(short *)pInput; pInput += sizeof(short);
	m_iShipTypes[10]         = *(short *)pInput; pInput += sizeof(short);
	m_iShipTypes[11]         = *(short *)pInput; pInput += sizeof(short);
	m_iShipTypes[12]         = *(short *)pInput; pInput += sizeof(short);
	m_iShipTypes[13]         = *(short *)pInput; pInput += sizeof(short);
	m_iShipTypes[14]         = *(short *)pInput; pInput += sizeof(short);
	m_iShipTypes[15]         = *(short *)pInput; pInput += sizeof(short);
	m_iShipProbabilities[0]  = *(short *)pInput; pInput += sizeof(short);
	m_iShipProbabilities[1]  = *(short *)pInput; pInput += sizeof(short);
	m_iShipProbabilities[2]  = *(short *)pInput; pInput += sizeof(short);
	m_iShipProbabilities[3]  = *(short *)pInput; pInput += sizeof(short);
	m_iShipProbabilities[4]  = *(short *)pInput; pInput += sizeof(short);
	m_iShipProbabilities[5]  = *(short *)pInput; pInput += sizeof(short);
	m_iShipProbabilities[6]  = *(short *)pInput; pInput += sizeof(short);
	m_iShipProbabilities[7]  = *(short *)pInput; pInput += sizeof(short);
	m_iShipProbabilities[8]  = *(short *)pInput; pInput += sizeof(short);
	m_iShipProbabilities[9]  = *(short *)pInput; pInput += sizeof(short);
	m_iShipProbabilities[10] = *(short *)pInput; pInput += sizeof(short);
	m_iShipProbabilities[11] = *(short *)pInput; pInput += sizeof(short);
	m_iShipProbabilities[12] = *(short *)pInput; pInput += sizeof(short);
	m_iShipProbabilities[13] = *(short *)pInput; pInput += sizeof(short);
	m_iShipProbabilities[14] = *(short *)pInput; pInput += sizeof(short);
	m_iShipProbabilities[15] = *(short *)pInput; pInput += sizeof(short);

	SwapEndians();

	return 1;
}

int CDudeResource::SwapEndians(void)
{
	m_iAIType                = SwapEndianShort(m_iAIType);
	m_iGovernment            = SwapEndianShort(m_iGovernment);
	m_iFlags                 = SwapEndianShort(m_iFlags);
	m_iInfoTypes             = SwapEndianShort(m_iInfoTypes);
	m_iShipTypes[0]          = SwapEndianShort(m_iShipTypes[0]);
	m_iShipTypes[1]          = SwapEndianShort(m_iShipTypes[1]);
	m_iShipTypes[2]          = SwapEndianShort(m_iShipTypes[2]);
	m_iShipTypes[3]          = SwapEndianShort(m_iShipTypes[3]);
	m_iShipTypes[4]          = SwapEndianShort(m_iShipTypes[4]);
	m_iShipTypes[5]          = SwapEndianShort(m_iShipTypes[5]);
	m_iShipTypes[6]          = SwapEndianShort(m_iShipTypes[6]);
	m_iShipTypes[7]          = SwapEndianShort(m_iShipTypes[7]);
	m_iShipTypes[8]          = SwapEndianShort(m_iShipTypes[8]);
	m_iShipTypes[9]          = SwapEndianShort(m_iShipTypes[9]);
	m_iShipTypes[10]         = SwapEndianShort(m_iShipTypes[10]);
	m_iShipTypes[11]         = SwapEndianShort(m_iShipTypes[11]);
	m_iShipTypes[12]         = SwapEndianShort(m_iShipTypes[12]);
	m_iShipTypes[13]         = SwapEndianShort(m_iShipTypes[13]);
	m_iShipTypes[14]         = SwapEndianShort(m_iShipTypes[14]);
	m_iShipTypes[15]         = SwapEndianShort(m_iShipTypes[15]);
	m_iShipProbabilities[0]  = SwapEndianShort(m_iShipProbabilities[0]);
	m_iShipProbabilities[1]  = SwapEndianShort(m_iShipProbabilities[1]);
	m_iShipProbabilities[2]  = SwapEndianShort(m_iShipProbabilities[2]);
	m_iShipProbabilities[3]  = SwapEndianShort(m_iShipProbabilities[3]);
	m_iShipProbabilities[4]  = SwapEndianShort(m_iShipProbabilities[4]);
	m_iShipProbabilities[5]  = SwapEndianShort(m_iShipProbabilities[5]);
	m_iShipProbabilities[6]  = SwapEndianShort(m_iShipProbabilities[6]);
	m_iShipProbabilities[7]  = SwapEndianShort(m_iShipProbabilities[7]);
	m_iShipProbabilities[8]  = SwapEndianShort(m_iShipProbabilities[8]);
	m_iShipProbabilities[9]  = SwapEndianShort(m_iShipProbabilities[9]);
	m_iShipProbabilities[10] = SwapEndianShort(m_iShipProbabilities[10]);
	m_iShipProbabilities[11] = SwapEndianShort(m_iShipProbabilities[11]);
	m_iShipProbabilities[12] = SwapEndianShort(m_iShipProbabilities[12]);
	m_iShipProbabilities[13] = SwapEndianShort(m_iShipProbabilities[13]);
	m_iShipProbabilities[14] = SwapEndianShort(m_iShipProbabilities[14]);
	m_iShipProbabilities[15] = SwapEndianShort(m_iShipProbabilities[15]);

	return 1;
}

int CDudeResource::SaveToText(std::ostream & output)
{
	output << m_iAIType                << '\t'
		   << m_iGovernment            << '\t'
		   << m_iShipTypes[0]          << '\t'
		   << m_iShipTypes[1]          << '\t'
		   << m_iShipTypes[2]          << '\t'
		   << m_iShipTypes[3]          << '\t'
		   << m_iShipTypes[4]          << '\t'
		   << m_iShipTypes[5]          << '\t'
		   << m_iShipTypes[6]          << '\t'
		   << m_iShipTypes[7]          << '\t'
		   << m_iShipTypes[8]          << '\t'
		   << m_iShipTypes[9]          << '\t'
		   << m_iShipTypes[10]         << '\t'
		   << m_iShipTypes[11]         << '\t'
		   << m_iShipTypes[12]         << '\t'
		   << m_iShipTypes[13]         << '\t'
		   << m_iShipTypes[14]         << '\t'
		   << m_iShipTypes[15]         << '\t'
		   << m_iShipProbabilities[0]  << '\t'
		   << m_iShipProbabilities[1]  << '\t'
		   << m_iShipProbabilities[2]  << '\t'
		   << m_iShipProbabilities[3]  << '\t'
		   << m_iShipProbabilities[4]  << '\t'
		   << m_iShipProbabilities[5]  << '\t'
		   << m_iShipProbabilities[6]  << '\t'
		   << m_iShipProbabilities[7]  << '\t'
		   << m_iShipProbabilities[8]  << '\t'
		   << m_iShipProbabilities[9]  << '\t'
		   << m_iShipProbabilities[10] << '\t'
		   << m_iShipProbabilities[11] << '\t'
		   << m_iShipProbabilities[12] << '\t'
		   << m_iShipProbabilities[13] << '\t'
		   << m_iShipProbabilities[14] << '\t'
		   << m_iShipProbabilities[15] << '\t';

	PrintHex16Field(output, (char *)&m_iFlags,     '\t');
	PrintHex16Field(output, (char *)&m_iInfoTypes, '\t');

	return 1;
}

int CDudeResource::LoadFromText(std::istream & input)
{
	input >> m_iAIType
		  >> m_iGovernment
		  >> m_iShipTypes[0]
		  >> m_iShipTypes[1]
		  >> m_iShipTypes[2]
		  >> m_iShipTypes[3]
		  >> m_iShipTypes[4]
		  >> m_iShipTypes[5]
		  >> m_iShipTypes[6]
		  >> m_iShipTypes[7]
		  >> m_iShipTypes[8]
		  >> m_iShipTypes[9]
		  >> m_iShipTypes[10]
		  >> m_iShipTypes[11]
		  >> m_iShipTypes[12]
		  >> m_iShipTypes[13]
		  >> m_iShipTypes[14]
		  >> m_iShipTypes[15]
		  >> m_iShipProbabilities[0]
		  >> m_iShipProbabilities[1]
		  >> m_iShipProbabilities[2]
		  >> m_iShipProbabilities[3]
		  >> m_iShipProbabilities[4]
		  >> m_iShipProbabilities[5]
		  >> m_iShipProbabilities[6]
		  >> m_iShipProbabilities[7]
		  >> m_iShipProbabilities[8]
		  >> m_iShipProbabilities[9]
		  >> m_iShipProbabilities[10]
		  >> m_iShipProbabilities[11]
		  >> m_iShipProbabilities[12]
		  >> m_iShipProbabilities[13]
		  >> m_iShipProbabilities[14]
		  >> m_iShipProbabilities[15];

	ReadHex16Field(input, (char *)&m_iFlags);
	ReadHex16Field(input, (char *)&m_iInfoTypes);

	return 1;
}

int CDudeResource::Initialize(HWND hwnd)
{
	std::string szTitle;

	szTitle = "dude ";
	szTitle += ToString(m_iID);
	szTitle += " (";
	szTitle += m_szName;
	szTitle += ") in ";
	szTitle += CEditor::GetCurrentEditor()->GetCurFilenameNoPath();

	m_pWindow->SetTitle(szTitle.c_str());

	m_controls[0].Create(hwnd, IDC_EDIT_DUDE_EDIT1, CCONTROL_TYPE_INT, IDS_STRING224);
	m_controls[0].SetInt(m_iID);
	m_controls[1].Create(hwnd, IDC_EDIT_DUDE_COMBO1, CCONTROL_TYPE_COMBOBOX, IDS_STRING225);
	m_controls[1].SetComboStrings(NUM_AITYPE_CHOICES, g_szAITypeChoices);
	m_controls[1].SetInt(m_iAIType - 1);
	m_controls[2].Create(hwnd, IDC_EDIT_DUDE_EDIT3, CCONTROL_TYPE_INT, IDS_STRING226);
	m_controls[2].SetInt(m_iGovernment);
	m_controls[3].Create(hwnd, IDC_EDIT_DUDE_EDIT4, CCONTROL_TYPE_INT, IDS_STRING239);
	m_controls[3].SetInt((m_iInfoTypes & 0x0FFF) + 7500);
	m_controls[4].Create(hwnd, IDC_EDIT_DUDE_EDIT5, CCONTROL_TYPE_INT, IDS_STRING240);
	m_controls[4].SetInt(m_iShipTypes[0]);
	m_controls[5].Create(hwnd, IDC_EDIT_DUDE_EDIT6, CCONTROL_TYPE_INT, IDS_STRING240);
	m_controls[5].SetInt(m_iShipTypes[1]);
	m_controls[6].Create(hwnd, IDC_EDIT_DUDE_EDIT7, CCONTROL_TYPE_INT, IDS_STRING240);
	m_controls[6].SetInt(m_iShipTypes[2]);
	m_controls[7].Create(hwnd, IDC_EDIT_DUDE_EDIT8, CCONTROL_TYPE_INT, IDS_STRING240);
	m_controls[7].SetInt(m_iShipTypes[3]);
	m_controls[8].Create(hwnd, IDC_EDIT_DUDE_EDIT9, CCONTROL_TYPE_INT, IDS_STRING240);
	m_controls[8].SetInt(m_iShipTypes[4]);
	m_controls[9].Create(hwnd, IDC_EDIT_DUDE_EDIT10, CCONTROL_TYPE_INT, IDS_STRING240);
	m_controls[9].SetInt(m_iShipTypes[5]);
	m_controls[10].Create(hwnd, IDC_EDIT_DUDE_EDIT11, CCONTROL_TYPE_INT, IDS_STRING240);
	m_controls[10].SetInt(m_iShipTypes[6]);
	m_controls[11].Create(hwnd, IDC_EDIT_DUDE_EDIT12, CCONTROL_TYPE_INT, IDS_STRING240);
	m_controls[11].SetInt(m_iShipTypes[7]);
	m_controls[12].Create(hwnd, IDC_EDIT_DUDE_EDIT13, CCONTROL_TYPE_INT, IDS_STRING240);
	m_controls[12].SetInt(m_iShipTypes[8]);
	m_controls[13].Create(hwnd, IDC_EDIT_DUDE_EDIT14, CCONTROL_TYPE_INT, IDS_STRING240);
	m_controls[13].SetInt(m_iShipTypes[9]);
	m_controls[14].Create(hwnd, IDC_EDIT_DUDE_EDIT15, CCONTROL_TYPE_INT, IDS_STRING240);
	m_controls[14].SetInt(m_iShipTypes[10]);
	m_controls[15].Create(hwnd, IDC_EDIT_DUDE_EDIT16, CCONTROL_TYPE_INT, IDS_STRING240);
	m_controls[15].SetInt(m_iShipTypes[11]);
	m_controls[16].Create(hwnd, IDC_EDIT_DUDE_EDIT17, CCONTROL_TYPE_INT, IDS_STRING240);
	m_controls[16].SetInt(m_iShipTypes[12]);
	m_controls[17].Create(hwnd, IDC_EDIT_DUDE_EDIT18, CCONTROL_TYPE_INT, IDS_STRING240);
	m_controls[17].SetInt(m_iShipTypes[13]);
	m_controls[18].Create(hwnd, IDC_EDIT_DUDE_EDIT19, CCONTROL_TYPE_INT, IDS_STRING240);
	m_controls[18].SetInt(m_iShipTypes[14]);
	m_controls[19].Create(hwnd, IDC_EDIT_DUDE_EDIT20, CCONTROL_TYPE_INT, IDS_STRING240);
	m_controls[19].SetInt(m_iShipTypes[15]);
	m_controls[20].Create(hwnd, IDC_EDIT_DUDE_EDIT21, CCONTROL_TYPE_INT, IDS_STRING241);
	m_controls[20].SetInt(m_iShipProbabilities[0]);
	m_controls[21].Create(hwnd, IDC_EDIT_DUDE_EDIT22, CCONTROL_TYPE_INT, IDS_STRING241);
	m_controls[21].SetInt(m_iShipProbabilities[1]);
	m_controls[22].Create(hwnd, IDC_EDIT_DUDE_EDIT23, CCONTROL_TYPE_INT, IDS_STRING241);
	m_controls[22].SetInt(m_iShipProbabilities[2]);
	m_controls[23].Create(hwnd, IDC_EDIT_DUDE_EDIT24, CCONTROL_TYPE_INT, IDS_STRING241);
	m_controls[23].SetInt(m_iShipProbabilities[3]);
	m_controls[24].Create(hwnd, IDC_EDIT_DUDE_EDIT25, CCONTROL_TYPE_INT, IDS_STRING241);
	m_controls[24].SetInt(m_iShipProbabilities[4]);
	m_controls[25].Create(hwnd, IDC_EDIT_DUDE_EDIT26, CCONTROL_TYPE_INT, IDS_STRING241);
	m_controls[25].SetInt(m_iShipProbabilities[5]);
	m_controls[26].Create(hwnd, IDC_EDIT_DUDE_EDIT27, CCONTROL_TYPE_INT, IDS_STRING241);
	m_controls[26].SetInt(m_iShipProbabilities[6]);
	m_controls[27].Create(hwnd, IDC_EDIT_DUDE_EDIT28, CCONTROL_TYPE_INT, IDS_STRING241);
	m_controls[27].SetInt(m_iShipProbabilities[7]);
	m_controls[28].Create(hwnd, IDC_EDIT_DUDE_EDIT29, CCONTROL_TYPE_INT, IDS_STRING241);
	m_controls[28].SetInt(m_iShipProbabilities[8]);
	m_controls[29].Create(hwnd, IDC_EDIT_DUDE_EDIT30, CCONTROL_TYPE_INT, IDS_STRING241);
	m_controls[29].SetInt(m_iShipProbabilities[9]);
	m_controls[30].Create(hwnd, IDC_EDIT_DUDE_EDIT31, CCONTROL_TYPE_INT, IDS_STRING241);
	m_controls[30].SetInt(m_iShipProbabilities[10]);
	m_controls[31].Create(hwnd, IDC_EDIT_DUDE_EDIT32, CCONTROL_TYPE_INT, IDS_STRING241);
	m_controls[31].SetInt(m_iShipProbabilities[11]);
	m_controls[32].Create(hwnd, IDC_EDIT_DUDE_EDIT33, CCONTROL_TYPE_INT, IDS_STRING241);
	m_controls[32].SetInt(m_iShipProbabilities[12]);
	m_controls[33].Create(hwnd, IDC_EDIT_DUDE_EDIT34, CCONTROL_TYPE_INT, IDS_STRING241);
	m_controls[33].SetInt(m_iShipProbabilities[13]);
	m_controls[34].Create(hwnd, IDC_EDIT_DUDE_EDIT35, CCONTROL_TYPE_INT, IDS_STRING241);
	m_controls[34].SetInt(m_iShipProbabilities[14]);
	m_controls[35].Create(hwnd, IDC_EDIT_DUDE_EDIT36, CCONTROL_TYPE_INT, IDS_STRING241);
	m_controls[35].SetInt(m_iShipProbabilities[15]);
	m_controls[36].Create(hwnd, IDC_EDIT_DUDE_CHECK1, CCONTROL_TYPE_CHECK, IDS_STRING227);
	m_controls[36].SetInt(m_iFlags & 0x0001);
	m_controls[37].Create(hwnd, IDC_EDIT_DUDE_CHECK2, CCONTROL_TYPE_CHECK, IDS_STRING228);
	m_controls[37].SetInt(m_iFlags & 0x0002);
	m_controls[38].Create(hwnd, IDC_EDIT_DUDE_CHECK3, CCONTROL_TYPE_CHECK, IDS_STRING229);
	m_controls[38].SetInt(m_iFlags & 0x0004);
	m_controls[39].Create(hwnd, IDC_EDIT_DUDE_CHECK4, CCONTROL_TYPE_CHECK, IDS_STRING230);
	m_controls[39].SetInt(m_iFlags & 0x0008);
	m_controls[40].Create(hwnd, IDC_EDIT_DUDE_CHECK5, CCONTROL_TYPE_CHECK, IDS_STRING231);
	m_controls[40].SetInt(m_iFlags & 0x0010);
	m_controls[41].Create(hwnd, IDC_EDIT_DUDE_CHECK6, CCONTROL_TYPE_CHECK, IDS_STRING232);
	m_controls[41].SetInt(m_iFlags & 0x0020);
	m_controls[42].Create(hwnd, IDC_EDIT_DUDE_CHECK7, CCONTROL_TYPE_CHECK, IDS_STRING233);
	m_controls[42].SetInt(m_iFlags & 0x0040);
	m_controls[43].Create(hwnd, IDC_EDIT_DUDE_CHECK8, CCONTROL_TYPE_CHECK, IDS_STRING234);
	m_controls[43].SetInt(m_iFlags & 0x0100);
	m_controls[44].Create(hwnd, IDC_EDIT_DUDE_CHECK9, CCONTROL_TYPE_CHECK, IDS_STRING235);
	m_controls[44].SetInt(m_iInfoTypes & 0x1000);
	m_controls[45].Create(hwnd, IDC_EDIT_DUDE_CHECK10, CCONTROL_TYPE_CHECK, IDS_STRING236);
	m_controls[45].SetInt(m_iInfoTypes & 0x2000);
	m_controls[46].Create(hwnd, IDC_EDIT_DUDE_CHECK11, CCONTROL_TYPE_CHECK, IDS_STRING237);
	m_controls[46].SetInt(m_iInfoTypes & 0x4000);
	m_controls[47].Create(hwnd, IDC_EDIT_DUDE_CHECK12, CCONTROL_TYPE_CHECK, IDS_STRING238);
	m_controls[47].SetInt(m_iInfoTypes & 0x8000);
	m_controls[48].Create(hwnd, IDC_EDIT_DUDE_EDIT37, CCONTROL_TYPE_STR256, IDS_STRING242);
	m_controls[48].SetString(m_szName);

	return 1;
}

int CDudeResource::CloseAndSave(void)
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

	if((m_iID != m_controls[0].GetInt()) || (strcmp(m_szName, m_controls[48].GetString()) != 0))
		iIDOrNameChanged = 1;

	m_iID         = m_controls[0].GetInt();

	m_iAIType     = m_controls[1].GetInt() + 1;
	m_iGovernment = m_controls[2].GetInt();

	m_iInfoTypes = 0x0000;

	m_iInfoTypes |= ((m_controls[3].GetInt() - 7500) & 0x0FFF);

	m_iShipTypes[0]  = m_controls[4].GetInt();
	m_iShipTypes[1]  = m_controls[5].GetInt();
	m_iShipTypes[2]  = m_controls[6].GetInt();
	m_iShipTypes[3]  = m_controls[7].GetInt();
	m_iShipTypes[4]  = m_controls[8].GetInt();
	m_iShipTypes[5]  = m_controls[9].GetInt();
	m_iShipTypes[6]  = m_controls[10].GetInt();
	m_iShipTypes[7]  = m_controls[11].GetInt();
	m_iShipTypes[8]  = m_controls[12].GetInt();
	m_iShipTypes[9]  = m_controls[13].GetInt();
	m_iShipTypes[10] = m_controls[14].GetInt();
	m_iShipTypes[11] = m_controls[15].GetInt();
	m_iShipTypes[12] = m_controls[16].GetInt();
	m_iShipTypes[13] = m_controls[17].GetInt();
	m_iShipTypes[14] = m_controls[18].GetInt();
	m_iShipTypes[15] = m_controls[19].GetInt();

	m_iShipProbabilities[0]  = m_controls[20].GetInt();
	m_iShipProbabilities[1]  = m_controls[21].GetInt();
	m_iShipProbabilities[2]  = m_controls[22].GetInt();
	m_iShipProbabilities[3]  = m_controls[23].GetInt();
	m_iShipProbabilities[4]  = m_controls[24].GetInt();
	m_iShipProbabilities[5]  = m_controls[25].GetInt();
	m_iShipProbabilities[6]  = m_controls[26].GetInt();
	m_iShipProbabilities[7]  = m_controls[27].GetInt();
	m_iShipProbabilities[8]  = m_controls[28].GetInt();
	m_iShipProbabilities[9]  = m_controls[29].GetInt();
	m_iShipProbabilities[10] = m_controls[30].GetInt();
	m_iShipProbabilities[11] = m_controls[31].GetInt();
	m_iShipProbabilities[12] = m_controls[32].GetInt();
	m_iShipProbabilities[13] = m_controls[33].GetInt();
	m_iShipProbabilities[14] = m_controls[34].GetInt();
	m_iShipProbabilities[15] = m_controls[35].GetInt();

	m_iFlags = 0x0000;

	m_iFlags |= m_controls[36].GetInt() << 0;
	m_iFlags |= m_controls[37].GetInt() << 1;
	m_iFlags |= m_controls[38].GetInt() << 2;
	m_iFlags |= m_controls[39].GetInt() << 3;
	m_iFlags |= m_controls[40].GetInt() << 4;
	m_iFlags |= m_controls[41].GetInt() << 5;
	m_iFlags |= m_controls[42].GetInt() << 6;
	m_iFlags |= m_controls[43].GetInt() << 8;

	m_iInfoTypes |= m_controls[44].GetInt() << 12;
	m_iInfoTypes |= m_controls[45].GetInt() << 13;
	m_iInfoTypes |= m_controls[46].GetInt() << 14;
	m_iInfoTypes |= m_controls[47].GetInt() << 15;

	strcpy(m_szName, m_controls[48].GetString());

	int i;

	for(i = 0; i < NUM_DUDE_CONTROLS; i++)
		m_controls[i].Destroy();

	m_iIsNew = 0;

	CEditor::GetCurrentEditor()->SetDirty();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, iIDOrNameChanged);

	return 1;
}

int CDudeResource::CloseAndDontSave(void)
{
	int i;

	for(i = 0; i < NUM_DUDE_CONTROLS; i++)
		m_controls[i].Destroy();

	CEditor::GetCurrentEditor()->RemoveEditDialog(m_pWindow, 0);

	return 1;
}

BOOL CDudeResource::DudeDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CWindow *pWindow;
	CDudeResource *pResource;

	pWindow = CWindow::GetWindow(hwnd, 1);

	if(pWindow != NULL)
		pResource = (CDudeResource *)pWindow->GetExtraData(2);

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

			if(iControlID == IDC_EDIT_DUDE_CANCEL)
			{
				pResource->CloseAndDontSave();
			}
			else if(iControlID == IDC_EDIT_DUDE_OK)
			{
				pResource->CloseAndSave();
			}
			else
			{
				for(i = 0; i < NUM_DUDE_CONTROLS; i++)
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

double CDudeResource::PercentAppear(short id)
{
	for (int i = 0; i < 16; i++)
		if (m_iShipTypes[i] == id)
			return m_iShipProbabilities[i];
	return 0;
}