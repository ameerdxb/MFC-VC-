// CMyPage2.cpp : implementation file
//

#include "pch.h"
#include "MFCAssignment3.h"
#include "CMyPage2.h"
#include "afxdialogex.h"
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
	DDX_Control(pDX, IDC_LIST1, m_List2);
}

LRESULT CMyPage2::OnAddToTree(WPARAM wp, LPARAM lp)
{
	PATIENT_INFO_t* pStd = (PATIENT_INFO_t*)wp;
	
	//Storing the name in struct to map instead of tree
	if (NULL != pStd)
	{
		myMap[pStd->m_sPatientID] = *pStd;   //assigning key
		/*myMap[pStd->m_sPatientName] = *pStd;
		myMap[pStd->m_sGender] = *pStd;
		myMap[pStd->m_PatientDateofReg] = *pStd;
		myMap[pStd->m_sAge] = *pStd;
		myMap[pStd->oStudy.m_sHeight] = *pStd;
		myMap[pStd->oStudy.m_sWeight] = *pStd;
		myMap[pStd->oStudy.m_sStudyComments] = *pStd;
		myMap[pStd->oStudy.oSeries.m_sBodyPart] = *pStd;
		myMap[pStd->oStudy.oSeries.m_sNumberofImages] = *pStd;
		myMap[pStd->oStudy.oSeries.m_sOperatorsName] = *pStd;*/
	}

	InsertToTree();
	//Creating a user def fn to add data to tree
	return 0L;
}


BEGIN_MESSAGE_MAP(CMyPage2, CPropertyPage)
	ON_MESSAGE(WM_USER_SECONDPAGE, &CMyPage2::OnAddToTree)
	ON_MESSAGE(WM_USER_MSG, &CMyPage2::OnAddToTree)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMyPage2::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyPage2::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyPage2::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMyPage2 message handlers


void CMyPage2::InsertToTree()
{
	// TODO: Add your implementation code here.
	m_Tree.DeleteAllItems();
	POSITION pos = myMap.GetStartPosition(); //get first position of map
	while (pos != NULL) {
		CString strKey;
		PATIENT_INFO_t stdItem;
		myMap.GetNextAssoc(pos, strKey, stdItem);

		CString* pID = new CString(strKey);
		DWORD_PTR dwID = reinterpret_cast<DWORD_PTR>(pID);

		//TRACE(_T("Key=%s, Item=%s\n"), strKey, strItem);
		HTREEITEM hItem = m_Tree.InsertItem(stdItem.m_sPatientID);

		m_Tree.SetItemData(hItem, dwID);

		m_Tree.InsertItem(stdItem.m_sPatientName, hItem);
		m_Tree.InsertItem(stdItem.m_sGender, hItem);
		m_Tree.InsertItem(stdItem.m_PatientDateofReg, hItem);
		m_Tree.InsertItem(stdItem.m_sAge, hItem);
		hItem = m_Tree.InsertItem(_T("Study"),hItem);
		m_Tree.SetItemData(hItem, dwID);
		m_Tree.InsertItem(stdItem.oStudy.m_sHeight, hItem);
		

		m_Tree.InsertItem(stdItem.oStudy.m_sWeight, hItem);
		m_Tree.InsertItem(stdItem.oStudy.m_sStudyComments, hItem);
		hItem = m_Tree.InsertItem(_T("Series"), hItem);
		m_Tree.InsertItem(stdItem.oStudy.oSeries.m_sBodyPart, hItem);
		m_Tree.SetItemData(hItem, dwID);

		m_Tree.InsertItem(stdItem.oStudy.oSeries.m_sNumberofImages, hItem);
		m_Tree.InsertItem(stdItem.oStudy.oSeries.m_sOperatorsName, hItem);
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

	/*m_List2.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 120);
	int nIndex = m_List2.InsertItem(0, strName);
	m_List2.SetItemText(nIndex, 1, strName);*/

	//AfxMessageBox(strName);

	PATIENT_INFO_t std;
	if (myMap.Lookup(*pID, std))
	{
		if (strName == _T("Study"))
		{
			m_List2.DeleteAllItems();
			int nIndex = m_List2.InsertItem(0, _T("Height"));
			m_List2.SetItemText(nIndex, 1, std.oStudy.m_sHeight);

			nIndex = m_List2.InsertItem(0, _T("Weight"));
			m_List2.SetItemText(nIndex, 1, std.oStudy.m_sWeight);

			nIndex = m_List2.InsertItem(0, _T("Comment"));
			m_List2.SetItemText(nIndex, 1, std.oStudy.m_sStudyComments);

		}

		if (strName == _T("Series"))
		{
			m_List2.DeleteAllItems();
			int nIndex = m_List2.InsertItem(0, _T("Body Part"));
			m_List2.SetItemText(nIndex, 1, std.oStudy.oSeries.m_sBodyPart);

			nIndex = m_List2.InsertItem(0, _T("No. of Images"));
			m_List2.SetItemText(nIndex, 1, std.oStudy.oSeries.m_sNumberofImages);

			nIndex = m_List2.InsertItem(0, _T("Operator Name"));
			m_List2.SetItemText(nIndex, 1, std.oStudy.oSeries.m_sOperatorsName);
		}

		if (strName == std.m_sPatientID)
		{
			m_List2.DeleteAllItems();
			int nIndex = m_List2.InsertItem(0, _T("Patient ID"));
			m_List2.SetItemText(nIndex, 1, std.m_sPatientID);

			nIndex = m_List2.InsertItem(0, _T("Patient Name"));
			m_List2.SetItemText(nIndex, 1, std.m_sPatientName);

			nIndex = m_List2.InsertItem(0, _T("Patient Gender"));
			m_List2.SetItemText(nIndex, 1, std.m_sGender);

			nIndex = m_List2.InsertItem(0, _T("Date of Registration"));
			m_List2.SetItemText(nIndex, 1, std.m_PatientDateofReg);

			nIndex = m_List2.InsertItem(0, _T("Patient Age"));
			m_List2.SetItemText(nIndex, 1, std.m_sAge);

		}
		else
		{
			AfxMessageBox(_T("Test"));
		}
		//m_List2.SetWindowTextW(std.m_sPatientID);
		//AfxMessageBox(_T("Test"));

	}
	UpdateData(0);

	*pResult = 0;
}


BOOL CMyPage2::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here

	m_List2.InsertColumn(0, _T("Attributes"), LVCFMT_LEFT, 120);
	m_List2.InsertColumn(0, _T("Values"), LVCFMT_LEFT, 120);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

//Save Button
void CMyPage2::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	int nCount;
	CFile myFile;
	myFile.Open(_T("Patient.txt"), CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);
	CArchive ar(&myFile, CArchive::store);
	nCount = myMap.GetCount();
	ar << nCount;

	CString strKey;
	PATIENT_INFO_t stPatient;
	CPatient oPatient;

	POSITION pos = myMap.GetStartPosition();
	while (pos != NULL)
	{
		myMap.GetNextAssoc(pos, strKey, stPatient);
		oPatient = stPatient;
		oPatient.Serialize(ar);
	}
	ar.Close();
	myFile.Close();

	AfxMessageBox(_T("Saved Successfully"));
}

//Retrieve Button
void CMyPage2::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	CFile myFile;
	myFile.Open(_T("Patient.txt"), CFile::modeRead);
	CArchive ar(&myFile, CArchive::load);

	int nCount = 0;
	ar >> nCount;
	CPatient obj1;
	PATIENT_INFO_t std1;
	for (int i = 0; i < nCount; i++)
	{
		obj1.Serialize(ar);
		obj1.ConvertToStruct(std1);
		myMap[std1.m_sPatientID] = std1;
	}
	InsertToTree();
}


