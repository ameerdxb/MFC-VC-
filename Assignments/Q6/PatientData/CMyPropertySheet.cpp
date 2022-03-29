// CMyPropertySheet.cpp : implementation file
//

#include "pch.h"
#include "PatientData.h"
#include "CMyPropertySheet.h"
#include "Header.h"


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
	AddPage(&p1);
	AddPage(&p2);
}

CMyPropertySheet::~CMyPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CMyPropertySheet, CPropertySheet)
	ON_MESSAGE(WM_USER_SECONDPAGE, &CMyPropertySheet::OnSecondPage)
END_MESSAGE_MAP()


// CMyPropertySheet message handlers


BOOL CMyPropertySheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

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

LRESULT CMyPropertySheet::OnSecondPage(WPARAM wp, LPARAM lp)
{
	//MessageBox(_T("From Property Sheet"));
	p2.SendMessage(WM_USER_SECONDPAGE, wp, lp);
	return 0L;
}
