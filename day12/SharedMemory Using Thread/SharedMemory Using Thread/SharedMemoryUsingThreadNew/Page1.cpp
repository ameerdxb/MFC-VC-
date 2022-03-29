// Page1.cpp : implementation file
//

#include "stdafx.h"
#include "SharedMemoryUsingThreadNew.h"
#include "Page1.h"


// CPage1 dialog

//IMPLEMENT_DYNCREATE(CPage1, COlePropertyPage)



// Message map

/*BEGIN_MESSAGE_MAP(CPage1, COlePropertyPage)
	//ON_BN_CLICKED(IDC_BUTTON1, &CPage1::Onadd)
END_MESSAGE_MAP()
*/


// Initialize class factory and guid

// {68A3F6B9-A2A2-476A-A464-36D76725BB42}
IMPLEMENT_OLECREATE_EX(CPage1, "SharedMemoryUsingThreadNew.Page1",
	0x68a3f6b9, 0xa2a2, 0x476a, 0xa4, 0x64, 0x36, 0xd7, 0x67, 0x25, 0xbb, 0x42)



// CPage1::CPage1Factory::UpdateRegistry -
// Adds or removes system registry entries for CPage1

BOOL CPage1::CPage1Factory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Define string resource for page type; replace '0' below with ID.

	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, 0);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CPage1::CPage1 - Constructor

// TODO: Define string resource for page caption; replace '0' below with ID.
/*
CPage1::CPage1() :
	COlePropertyPage(IDD, 0)
		, val1(_T(""))
	{

}*/



// CPage1::DoDataExchange - Moves data between page and properties

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
	DDX_Text(pDX, IDC_EDIT1, val1);
}



// CPage1 message handlers

void CPage1::Onadd()
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	PERSON per;
	per.nam = val1;
	AfxGetMainWnd()->SendMessage(WM_USER_MSG,0,(LPARAM)&per);
}
