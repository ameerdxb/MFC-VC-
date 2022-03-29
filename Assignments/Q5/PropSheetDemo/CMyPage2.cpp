// CMyPage2.cpp : implementation file
//

#include "pch.h"
#include "PropSheetDemo.h"
#include "CMyPage2.h"
#include "afxdialogex.h"
#include "Header.h"

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
	DDX_Control(pDX, IDC_TREE1, m_Tree);
}


BEGIN_MESSAGE_MAP(CMyPage2, CPropertyPage)
	ON_MESSAGE(WM_USER_SECONDPAGE, &CMyPage2::OnAddToTree)
END_MESSAGE_MAP()


// CMyPage2 message handlers

LRESULT CMyPage2::OnAddToTree(WPARAM wp, LPARAM lp)
{
	//MessageBox(_T("Page 2"));
	STUDENT* std = (STUDENT*)wp;
	HTREEITEM hName = m_Tree.InsertItem(std->m_Name);
	m_Tree.InsertItem(std->m_Id, hName);
	m_Tree.InsertItem(std->m_Gender, hName);
	m_Tree.InsertItem(std->m_Date,hName);
	m_Tree.InsertItem(std->m_Age, hName);

	HTREEITEM hMarks = m_Tree.InsertItem(std->m_Marks, hName);
	m_Tree.InsertItem(std->m_Mark1, hMarks);
	m_Tree.InsertItem(std->m_Mark2, hMarks);
	m_Tree.InsertItem(std->m_Mark3, hMarks);

	return 0L;
}