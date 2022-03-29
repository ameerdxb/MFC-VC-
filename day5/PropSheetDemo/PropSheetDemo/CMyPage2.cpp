// CMyPage2.cpp : implementation file
//

#include "pch.h"
#include "PropSheetDemo.h"
#include "CMyPage2.h"
#include "afxdialogex.h"
#include "Header.h"
#include "CStudent.h"

// CMyPage2 dialog

IMPLEMENT_DYNAMIC(CMyPage2, CPropertyPage)

CMyPage2::CMyPage2()
	: CPropertyPage(IDD_DIALOG2)
	, m_Name(_T(""))
	, m_Gender(_T(""))
{

}

CMyPage2::~CMyPage2()
{
}

void CMyPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
	DDX_Control(pDX, IDC_EDIT1, m_NameControl);
	DDX_Control(pDX, IDC_EDIT2, m_GenderControl);
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	DDX_Text(pDX, IDC_EDIT2, m_Gender);
}


BEGIN_MESSAGE_MAP(CMyPage2, CPropertyPage)
	ON_MESSAGE(WM_USER_SECONDPAGE, &CMyPage2::OnAddToTree)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMyPage2::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyPage2::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyPage2::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMyPage2 message handlers

LRESULT CMyPage2::OnAddToTree(WPARAM wp, LPARAM lp)
{
	//MessageBox(_T("Page 2"));
	STUDENT* std = (STUDENT*)wp;
	/*HTREEITEM hName = m_Tree.InsertItem(std->m_Name);
	m_Tree.InsertItem(std->m_Id, hName);
	m_Tree.InsertItem(std->m_Gender, hName);
	m_Tree.InsertItem(std->m_Date,hName);
	m_Tree.InsertItem(std->m_Age, hName);

	HTREEITEM hMarks = m_Tree.InsertItem(std->m_Marks, hName);
	m_Tree.InsertItem(std->m_Mark1, hMarks);
	m_Tree.InsertItem(std->m_Mark2, hMarks);
	m_Tree.InsertItem(std->m_Mark3, hMarks);*/

	if (NULL != std)
	{
		myMap[std->m_Name] = *std;
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
		STUDENT stdItem;
		myMap.GetNextAssoc(pos, strKey, stdItem);

		CString* pID = new CString(strKey);
		DWORD_PTR dwID = reinterpret_cast<DWORD_PTR>(pID);

		//TRACE(_T("Key=%s, Item=%s\n"), strKey, strItem);
		HTREEITEM hItem = m_Tree.InsertItem(stdItem.m_Name);
		m_Tree.SetItemData(hItem, dwID);

		hItem = m_Tree.InsertItem(stdItem.m_Gender,hItem);
		m_Tree.SetItemData(hItem, dwID);

		hItem = m_Tree.InsertItem(stdItem.m_CurTime, hItem);
		m_Tree.SetItemData(hItem, dwID);
		//m_Tree.SetItemText(nIndex, 1, strItem);
	}
}


void CMyPage2::OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	CString strName = m_Tree.GetItemText(hItem);

	DWORD_PTR dwID =  m_Tree.GetItemData(hItem);
	CString* pID = reinterpret_cast<CString*>(dwID);

	//AfxMessageBox(strName);
	//m_NameControl.SetWindowTextW(strName);
	STUDENT std;
	if (myMap.Lookup(*pID, std))
	{
		//m_GenderControl.SetWindowTextW(std.m_Gender);
		//m_NameControl.SetWindowTextW(std.m_Name);
		m_Name = std.m_Name;
		m_Gender = std.m_Gender;
	}
	UpdateData(0);

	*pResult = 0;
}


void CMyPage2::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CFile myFile;
	myFile.Open(_T("Student.txt"), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	CArchive ar(&myFile,CArchive::store);

	ar << myMap.GetCount();

	CString strKey;
	STUDENT std;
	CStudent obj;
	POSITION pos = myMap.GetStartPosition();
	while (pos != NULL)
	{
		myMap.GetNextAssoc(pos, strKey, std);
		obj = std;
		obj.Serialize(ar);
	}

	ar.Close();
	myFile.Close();

}


void CMyPage2::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CFile myFile;
	myFile.Open(_T("Student.txt"), CFile::modeRead);
	CArchive ar(&myFile, CArchive::load);

	int nCount = 0;
	ar >> nCount;
	CStudent obj1;
	STUDENT std1;
	for (int i = 0; i < nCount; i++)
	{
		obj1.Serialize(ar);
		obj1.ConvertToStruct(std1);
		myMap[std1.m_Name] = std1;
	}

	InsertToTree();

}
