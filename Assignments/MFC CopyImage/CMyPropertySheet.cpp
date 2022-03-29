// CMyPropertySheet.cpp : implementation file
//

#include "pch.h"
#include "MFCAssignment3.h"
#include "CMyPropertySheet.h"
#include "CMyPage2.h"
#include "CPatient.h"


// CMyPropertySheet

IMPLEMENT_DYNAMIC(CMyPropertySheet, CPropertySheet)

CMyPropertySheet::CMyPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CMyPropertySheet::CMyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif
	AddPage(&P1);
	AddPage(&P2);
}

CMyPropertySheet::~CMyPropertySheet()
{
}

LRESULT CMyPropertySheet::OnSecondPage(WPARAM wp, LPARAM lp)
{
	MessageBox(_T("FromPropertySheet"));
	P2.SendMessage(WM_USER_SECONDPAGE, wp, lp);
	return 0L;
	//return LRESULT();
}


BEGIN_MESSAGE_MAP(CMyPropertySheet, CPropertySheet)
	ON_MESSAGE(WM_USER_SECONDPAGE, &CMyPropertySheet::OnSecondPage)
	ON_MESSAGE(WM_USER_MSG, &CMyPropertySheet::onrecieve1)
	ON_COMMAND(ID_COMMUNICATION_SHAREDMEMORY, &CMyPropertySheet::OnCommunicationSharedmemory)
END_MESSAGE_MAP()


// CMyPropertySheet message handlers


BOOL CMyPropertySheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	
	// TODO:  Add your specialized code here
	CButton* pBtn;
	pBtn = (CButton*)GetDlgItem(IDOK);
	pBtn->ShowWindow(SW_HIDE);
	pBtn = (CButton*)GetDlgItem(IDCANCEL);
	pBtn->ShowWindow(SW_HIDE);
	pBtn = (CButton*)GetDlgItem(ID_APPLY_NOW);
	pBtn->ShowWindow(SW_HIDE);
	pBtn = (CButton*)GetDlgItem(IDHELP);
	pBtn->ShowWindow(SW_HIDE);

	SetActivePage(&P2);
	SetActivePage(&P1);
	
	menu.LoadMenuW(IDR_MENU1);
	SetMenu(&menu);

	WriteManager.GetBrowserPointer(P2);
	ReadManager.GetBrowserPointer(P2);

	return bResult;
}


BOOL CMyPropertySheet::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	P2.OnBnClickedButton1();

	return TRUE;// CPropertySheet::DestroyWindow();
}


void CMyPropertySheet::OnCommunicationSharedmemory()
{
	// TODO: Add your command handler code here
	menu.CheckMenuItem(ID_COMMUNICATION_SHAREDMEMORY, MF_CHECKED);
	WriteManager.ThreadStart(_T("W"));
	ReadManager.ThreadStart(_T("R"));
}

LRESULT CMyPropertySheet::onrecieve1(WPARAM wp, LPARAM lp)
{
	//SetActivePage(&p2);
	 //If it is(menu) checked it will send the data to the next application or page
	if (menu.GetMenuState(ID_COMMUNICATION_SHAREDMEMORY, MF_BYCOMMAND) == MF_CHECKED)
	{
		WriteManager.OnNewNotification(lp);
	}
	else
	{
		P2.SendMessage(WM_USER_MSG , wp, lp);
	}
	return 0L;
}
