// CMyPage2.cpp : implementation file
//

#include "pch.h"
#include "PatientData.h"
#include "CMyPage2.h"
#include "afxdialogex.h"
#include "Header.h"
#include "CPatient.h"


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
	DDX_Control(pDX, IDC_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(CMyPage2, CPropertyPage)
	ON_MESSAGE(WM_USER_SECONDPAGE,&CMyPage2::OnAddToTree)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMyPage2::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyPage2::OnBnClickedRetrieve)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyPage2::OnBnClickedSave)
	ON_BN_CLICKED(IDCANCEL, &CMyPage2::OnBnClickedExit)
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
		HTREEITEM Info = m_Tree.InsertItem(_T("Patient: ")+stdItem.m_Name);
		m_Tree.SetItemData(Info, dwID);

		HTREEITEM Study = m_Tree.InsertItem(_T("Study"), Info);
		m_Tree.SetItemData(Study, dwID);

		HTREEITEM Series = m_Tree.InsertItem(_T("Series"), Study);
		m_Tree.SetItemData(Series, dwID);
	}
}


void CMyPage2::OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	m_List.DeleteAllItems();
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	CString strNode = m_Tree.GetItemText(hItem);



	DWORD_PTR dwID = m_Tree.GetItemData(hItem);
	CString* pID = reinterpret_cast<CString*>(dwID);

	PATIENT std;
	if (myMap.Lookup(*pID, std))
	{
		if (strNode == (_T("Patient: ") + std.m_Name))
		{
			int nIndex = m_List.InsertItem(0, _T("Patient Name"));
			m_List.InsertItem(1, _T("Patient ID "));
			m_List.InsertItem(2, _T("Gender"));
			m_List.InsertItem(3, _T("Date Of Registration"));
			m_List.InsertItem(4, _T("Age"));
			m_List.SetItemText(0, 1, std.m_Name);
			m_List.SetItemText(1, 1, std.m_Id);
			m_List.SetItemText(2, 1, std.m_Gender);
			m_List.SetItemText(3, 1, std.m_Date);
			m_List.SetItemText(4, 1, std.m_Age);
		}
		else if (strNode == _T("Series"))
		{
			int nIndex = m_List.InsertItem(0, _T("Body Part"));
			m_List.InsertItem(1, _T("Number of Images"));
			m_List.InsertItem(2, _T("Operator's Name"));

			m_List.SetItemText(0, 1, std.STUDY.SERIES.m_BodyPart);
			m_List.SetItemText(1, 1, std.STUDY.SERIES.m_Images);
			m_List.SetItemText(2, 1, std.STUDY.SERIES.m_Operator);
		}
		else
		{
			int nIndex = m_List.InsertItem(0, _T("Height"));
			m_List.InsertItem(1, _T("Weight"));
			m_List.InsertItem(2, _T("Comments"));

			m_List.SetItemText(0, 1, std.STUDY.m_Height);
			m_List.SetItemText(1, 1, std.STUDY.m_Weight);
			m_List.SetItemText(2, 1, std.STUDY.m_Comments);
		}
	}



	*pResult = 0;
}


BOOL CMyPage2::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, _T("Attribute"), LVCFMT_LEFT, 250);
	m_List.InsertColumn(1, _T("Value"), LVCFMT_LEFT, 400);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CMyPage2::OnBnClickedRetrieve()
{
	// TODO: Add your control notification handler code here
	CFile MyFile;
	MyFile.Open(_T("Patient.txt"), CFile::modeRead);
	CArchive ar(&MyFile, CArchive::load);

	int nCount = 0;
	ar >> nCount;

	CPatient obj1;
	PATIENT std1;
	for (int i = 0; i < nCount; i++)
	{
		obj1.Serialize(ar);
		obj1.ConvertToStruct(std1);
		myMap[std1.m_Id] = std1;
	}

	InsertToTree();
}


void CMyPage2::OnBnClickedSave()
{
	// TODO: Add your control notification handler code here
	CFile MyFile;
	MyFile.Open(_T("Patient.txt"), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	CArchive ar(&MyFile, CArchive::store);
	ar << myMap.GetCount();
	CString strKey;
	PATIENT std;
	CPatient obj;
	POSITION pos = myMap.GetStartPosition();
	while (pos != NULL)
	{
		myMap.GetNextAssoc(pos, strKey, std);
		obj = std;
		obj.Serialize(ar);
	}
	ar.Close();
	MyFile.Close();
}


void CMyPage2::OnBnClickedExit()
{
	// TODO: Add your control notification handler code here
	OnBnClickedRetrieve();
	int ReturnValue = MessageBox(_T("Are you sure you want to exit"),
		_T("Information.."), MB_YESNO | MB_ICONQUESTION);
	if (ReturnValue == IDYES)
	{
		AfxMessageBox(_T("Saving the Data"));
		CMyPropertySheet:EndDialog(0);
	}
}
