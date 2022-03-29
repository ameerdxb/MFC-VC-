// CMyPage2.cpp : implementation file
//

#include "pch.h"
#include "PatientData.h"
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
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMyPage2::OnTvnSelchangedTree1)
END_MESSAGE_MAP()


// CMyPage2 message handlers

LRESULT CMyPage2::OnAddToTree(WPARAM wp, LPARAM lp)
{
	PATIENT* std = (PATIENT*)wp;
	if (NULL != std)
	{
		//myMap[std->m_Name] = *std;
		myMap[std->m_Id] = *std;
		//myMap[std->m_Age] = *std;
		//myMap[std->m_Gender] = *std;
		//myMap[std->m_Date] = *std;
	}
	InsertToTree();

	return 0L;
}

void CMyPage2::InsertToTree()
{
	// TODO: Add your implementation code here.
	m_Tree.DeleteAllItems();
	POSITION pos = myMap.GetStartPosition();
	while (pos != NULL) {
		CString strKey;
		PATIENT stdItem;
		myMap.GetNextAssoc(pos, strKey, stdItem);

		CString* pID = new CString(strKey);
		DWORD_PTR dwID = reinterpret_cast<DWORD_PTR>(pID);

		//TRACE(_T("Key=%s, Item=%s\n"), strKey, strItem);
		HTREEITEM hItem = m_Tree.InsertItem(stdItem.m_Name);

		m_Tree.SetItemData(hItem, dwID);

		m_Tree.InsertItem(stdItem.m_Id, hItem);
		//m_Tree.SetItemData(hItem, dwID);

		m_Tree.InsertItem(stdItem.m_Gender, hItem);
		//m_Tree.SetItemData(hItem, dwID);

		
		m_Tree.InsertItem(stdItem.m_Date, hItem);
		//m_Tree.SetItemData(hItem, dwID);
		m_Tree.InsertItem(stdItem.m_Age, hItem);
		//m_Tree.SetItemData(hItem, dwID);
		//m_Tree.SetItemText(nIndex, 1, strItem);
	}
}


void CMyPage2::OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	CString strName = m_Tree.GetItemText(hItem);

	DWORD_PTR dwID = m_Tree.GetItemData(hItem);
	CString* pID = reinterpret_cast<CString*>(dwID);


	UpdateData(0);

	*pResult = 0;
}
