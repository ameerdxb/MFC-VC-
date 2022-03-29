// CMyPage2.cpp : implementation file
//

#include "pch.h"
#include "PatientData.h"
#include "CMyPage2.h"
#include "afxdialogex.h"


// CMyPage2 dialog

IMPLEMENT_DYNAMIC(CMyPage2, CPropertyPage)

CMyPage2::CMyPage2()
	: CPropertyPage(IDD_DIALOG2)
{

}

CMyPage2::~CMyPage2()
{
}

void CMyPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyPage2, CPropertyPage)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMyPage2::OnTvnSelchangedTree1)
END_MESSAGE_MAP()


// CMyPage2 message handlers


void CMyPage2::OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
