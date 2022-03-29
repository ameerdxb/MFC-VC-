// CMyPropertySheet.cpp : implementation file
//

#include "pch.h"
#include "PatientData.h"
#include "CMyPropertySheet.h"


// CMyPropertySheet

IMPLEMENT_DYNAMIC(CMyPropertySheet, CPropertySheet)

CMyPropertySheet::CMyPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CMyPropertySheet::CMyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&p1);
	AddPage(&p2);
}

CMyPropertySheet::~CMyPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CMyPropertySheet, CPropertySheet)
END_MESSAGE_MAP()


// CMyPropertySheet message handlers


BOOL CMyPropertySheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO:  Add your specialized code here
	
	SetActivePage(&p2);
	SetActivePage(&p1);
	CButton* b;

	b = (CButton*)GetDlgItem(IDOK);
	b->ShowWindow(SW_HIDE);

	b = (CButton*)GetDlgItem(IDCANCEL);
	b->ShowWindow(SW_HIDE);

	b = (CButton*)GetDlgItem(ID_APPLY_NOW);
	b->ShowWindow(SW_HIDE);

	b = (CButton*)GetDlgItem(IDHELP);
	b->ShowWindow(SW_HIDE);
	return bResult;
}
