// CMyPage2.cpp : implementation file
//

#include "pch.h"
#include "Assignment_Q5.h"
#include "CMyPage2.h"
#include "afxdialogex.h"
#include "Header.h"


// CMyPage2 dialog

IMPLEMENT_DYNAMIC(CMyPage2, CPropertyPage)

CMyPage2::CMyPage2()
	: CPropertyPage(IDD_DIALOG2)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

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
	ON_MESSAGE(WM_USER_SECONDPAGE,&CMyPage2::OnAddToTree)
END_MESSAGE_MAP()


// CMyPage2 message handlers

LRESULT CMyPage2::OnAddToTree(WPARAM wp, LPARAM lp)
{
	STUDENT* std = (STUDENT*)wp;
	HTREEITEM hName = m_Tree.InsertItem(std->m_Name);
	m_Tree.InsertItem(std->m_Id, hName);
	m_Tree.InsertItem(std->m_Gender, hName);
	m_Tree.InsertItem(std->m_Age, hName);
	m_Tree.InsertItem(std->m_DateReg, hName);
	HTREEITEM hMark = m_Tree.InsertItem(_T("Marks"), hName);
	m_Tree.InsertItem(std->MARK.m_Mark1, hMark);
	m_Tree.InsertItem(std->MARK.m_Mark1, hMark);
	m_Tree.InsertItem(std->MARK.m_Mark1, hMark);
	return 0L;
}