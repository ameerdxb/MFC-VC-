// CMypropertySheet.cpp : implementation file
//

#include "pch.h"
#include "Assignment_Q5.h"
#include "CMypropertySheet.h"
#include "Header.h"



// CMypropertySheet

IMPLEMENT_DYNAMIC(CMypropertySheet, CPropertySheet)

CMypropertySheet::CMypropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CMypropertySheet::CMypropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif
	AddPage(&p1);
	AddPage(&p2);
}

CMypropertySheet::~CMypropertySheet()
{
}


BEGIN_MESSAGE_MAP(CMypropertySheet, CPropertySheet)
	ON_MESSAGE(WM_USER_SECONDPAGE,&CMypropertySheet::OnSecondPage)
	ON_COMMAND(ID_COMMUNICATION_SHAREDMEMORY, &CMypropertySheet::OnCommunicationSharedmemory)
END_MESSAGE_MAP()


// CMypropertySheet message handlers


LRESULT CMypropertySheet::OnSecondPage(WPARAM wp, LPARAM lp)
{
	if (myMenu.GetMenuState(ID_COMMUNICATION_SHAREDMEMORY, MF_BYCOMMAND) == MF_CHECKED)
	{
		WriteManager.OnNewNotification(wp);
	}
	else
	{
		p2.SendMessage(WM_USER_SECONDPAGE, wp, lp);
	}
	return 0L;
}

BOOL CMypropertySheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	myMenu.LoadMenuW(IDR_MENU1);
	SetMenu(&myMenu);

	// TODO:  Add your specialized code here
	CButton* b;
	b = (CButton*)GetDlgItem(IDOK);
	b->ShowWindow(SW_HIDE);
	b = (CButton*)GetDlgItem(IDCANCEL);
	b->ShowWindow(SW_HIDE);
	b = (CButton*)GetDlgItem(ID_APPLY_NOW);
	b->ShowWindow(SW_HIDE);
	b = (CButton*)GetDlgItem(IDHELP);
	b->ShowWindow(SW_HIDE);

	SetActivePage(&p2);
	SetActivePage(&p1);

	return bResult;
}


void CMypropertySheet::OnCommunicationSharedmemory()
{
	// TODO: Add your command handler code here
	myMenu.CheckMenuItem(ID_COMMUNICATION_SHAREDMEMORY,MF_CHECKED);
	WriteManager.ThreadStart(_T("W"));
	ReadManager.ThreadStart(_T("R"));
}
