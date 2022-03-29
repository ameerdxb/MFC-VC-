// PAGE.cpp : implementation file
//

#include "stdafx.h"
#include "SharedMemoryUsingThreadNew.h"
#include "PAGE.h"


// CPAGE dialog

IMPLEMENT_DYNCREATE(CPAGE, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CPAGE, COlePropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &CPAGE::OnAdd)
END_MESSAGE_MAP()



// Initialize class factory and guid

// {8EE2AED8-B547-403B-83DE-F6BC4F2A01E3}
IMPLEMENT_OLECREATE_EX(CPAGE, "SharedMemoryUsingThreadNew.PAGE",
	0x8ee2aed8, 0xb547, 0x403b, 0x83, 0xde, 0xf6, 0xbc, 0x4f, 0x2a, 0x1, 0xe3)



// CPAGE::CPAGEFactory::UpdateRegistry -
// Adds or removes system registry entries for CPAGE

BOOL CPAGE::CPAGEFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Define string resource for page type; replace '0' below with ID.

	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, 0);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CPAGE::CPAGE - Constructor

// TODO: Define string resource for page caption; replace '0' below with ID.

CPAGE::CPAGE() :
	COlePropertyPage(IDD, 0)
		, val1(_T(""))
	{

}



// CPAGE::DoDataExchange - Moves data between page and properties

void CPAGE::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
	DDX_Text(pDX, IDC_EDIT1, val1);
}



// CPAGE message handlers

void CPAGE::OnAdd()
{
	// TODO: Add your control notification handler code here
}
