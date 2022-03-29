// Page2.cpp : implementation file
//

#include "pch.h"
#include "PatientInfoManager.h"
#include "Page2.h"
#include "afxdialogex.h"
#include"Header.h"
#include"Patient.h"
#include"MyPropertySheet.h"
#include <afxsock.h>
// CPage2 dialog

IMPLEMENT_DYNAMIC(CPage2, CPropertyPage)

CPage2::CPage2()
	: CPropertyPage(IDD_DIALOG2)
{

}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
	DDX_Control(pDX, IDC_LIST2, m_List1);
	DDX_Control(pDX, IDC_LIST1, m_List3);
}


BEGIN_MESSAGE_MAP(CPage2, CPropertyPage)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CPage2::OnNMRClickTree1)
	ON_MESSAGE(WM_USER_SECONDPAGE , &CPage2::OnAddToTree)
	ON_MESSAGE(WM_USER_MSG, &CPage2::OnAddToTree)
	ON_MESSAGE(MSG_ON_PATIENT_REG, &CPage2::OnNewItemNotification)
	ON_COMMAND(ID_EXPAND_COLLAPSE, &CPage2::OnExpandCollapse)
	ON_COMMAND(ID_MENU_COLLAPSE, OnMenuCollapse)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CPage2::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_SAVEDATA, &CPage2::OnBnClickedSavedata)
	ON_BN_CLICKED(IDC_RETRIEVEDATA, &CPage2::OnBnClickedRetrievedata)
	ON_BN_CLICKED(IDC_EXIT, &CPage2::OnBnClickedExit)
	
	
	//ON_CBN_SELCHANGE(IDC_BODYPART, &CPage2::OnCbnSelchangeBodypart)
END_MESSAGE_MAP()


// CPage2 message handlers


void CPage2::Setdata(CString& filepath)
{
	m_strStoreImagePath = _T("C:\\StoreImage");
		
}

void CPage2::OnNMRClickTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CMenu* pPopupMenu;

	pPopupMenu = m_TreeContextMenu.GetSubMenu(0);

	CPoint MousePos;
	GetCursorPos(&MousePos);

	pPopupMenu->TrackPopupMenu(TPM_LEFTALIGN, MousePos.x, MousePos.y, this);

	*pResult = 0;
}

LRESULT CPage2::OnAddToTree(WPARAM wp, LPARAM lp)
{
	PATIENT* pt = (PATIENT*)wp;
	m_Tree.DeleteAllItems();
	if (NULL != pt)
	{
		myMap[pt->m_PatientID] = *pt;

	}
	
	InsertToTree();
	
	return LRESULT();
}




void CPage2::LoadImageFiles(PATIENT& pt)
{
	CString str;
	CString str1 = _T(".bmp");
	int nCount = 1;
	CString str2;
	str.Format(_T("%s%s%s"), m_strStoreImagePath, "\\", pt.m_PatientID
		);
	
	WIN32_FIND_DATA file;
	HANDLE hfile = FindFirstFile(str, &file);
	do
	{
		str2.Format(_T("%s%s%s%s%s%d%s"), m_strStoreImagePath, "\\", pt.m_PatientID, "\\",
			pt.study.series.m_BodyPart, nCount, str1);
		HANDLE hBitMap = ::LoadImage(AfxGetInstanceHandle(), str2,
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		//int nIndex = 0;
		CBitmap myBitmap;
		myBitmap.Attach((HBITMAP)hBitMap);
		m_Image.Add(&myBitmap, RGB(0, 255, 0));
		m_List3.InsertItem(0, _T("Head"));
		nCount++;
	} while (FindNextFile(hfile, &file));
}

BOOL CPage2::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_List1.InsertColumn(0, _T("Attributes"), LVCFMT_CENTER, 120);
	m_List1.InsertColumn(1, _T("Values"), LVCFMT_CENTER, 120);
	m_List1.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_JUSTIFYCOLUMNS);
	m_Image.Create(IDB_BITMAP2, 32, 1, RGB(255, 0, 0));
	//CBitmap myBitmap;
	//myBitmap.LoadBitmapW(_T("C:\RefImage\Head.bmp"));
	m_List3.SetImageList(&m_Image, LVSIL_NORMAL);

	m_TreeContextMenu.LoadMenu(IDR_MENU1);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage2::InsertToTree()
{
	
	POSITION pos = myMap.GetStartPosition();
	while (pos != NULL)
	{
		CString strKey;
		PATIENT ptItem;
		myMap.GetNextAssoc(pos, strKey, ptItem);
		CString* pID = new CString(strKey);
			//converting the pointer type to DWORD type
			DWORD_PTR dwID = reinterpret_cast<DWORD_PTR>(pID);
			HTREEITEM hItem = m_Tree.InsertItem(ptItem.m_PatientName);
			m_Tree.SetItemData(hItem, dwID);
			m_Tree.InsertItem(ptItem.m_PatientID, hItem);
			m_Tree.InsertItem(ptItem.m_Gender, hItem);
			m_Tree.InsertItem(ptItem.m_Date, hItem);
			m_Tree.InsertItem(ptItem.m_Age, hItem);
			HTREEITEM hSubItem = m_Tree.InsertItem(_T("Study"), hItem);
			m_Tree.SetItemData(hSubItem, dwID);
			m_Tree.InsertItem(ptItem.study.m_Height, hSubItem);
			m_Tree.InsertItem(ptItem.study.m_Weight, hSubItem);
			m_Tree.InsertItem(ptItem.study.m_StudyComments, hSubItem);
			HTREEITEM hNextItem = m_Tree.InsertItem(_T("Series"), hSubItem);
			m_Tree.SetItemData(hNextItem, dwID);
			m_Tree.InsertItem(ptItem.study.series.m_BodyPart, hNextItem);
			m_Tree.InsertItem(ptItem.study.series.m_NumberofImages, hNextItem);
			m_Tree.InsertItem(ptItem.study.series.m_OperatorsName, hNextItem);
			
	}
}

void CPage2::ExpandAllItems(HTREEITEM hitem, bool expand)
{
	HTREEITEM hItemHandle;
	//HTREEITEM hItemHandle1;
	if (m_Tree.ItemHasChildren(hitem))
	{
		if (!expand)
		{
			m_Tree.Expand(hitem, TVE_EXPAND);
		}

		else
		{
			m_Tree.Expand(hitem, TVE_COLLAPSE);
		}

		hItemHandle = m_Tree.GetChildItem(hitem);

		if (NULL != hItemHandle)
		{
			ExpandAllItems(hItemHandle, expand);
		}

		hItemHandle = m_Tree.GetNextItem(hitem, TVGN_NEXT);

		if (NULL != hItemHandle)
		{
			ExpandAllItems(hItemHandle, expand);
		}
		
		if (!expand)
		{
			m_Tree.Expand(hItemHandle, TVE_EXPAND);
		}
		else
		{
			m_Tree.Expand(hItemHandle, TVE_COLLAPSE);
		}
		
	}
	
}


void CPage2::OnExpandCollapse()
{
	// TODO: Add your command handler code here
	HTREEITEM hitem = m_Tree.GetRootItem();
	ExpandAllItems(hitem);
}

void CPage2::OnMenuCollapse()
{
	// TODO: Add your command handler code here
	HTREEITEM hitem = m_Tree.GetRootItem();
	ExpandAllItems(hitem, true);

}

void CPage2::OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	HTREEITEM hnew1 = m_Tree.GetSelectedItem();
	CString strName = m_Tree.GetItemText(hnew1);
	DWORD_PTR dwID = m_Tree.GetItemData(hnew1);
	
	CString* pID = reinterpret_cast<CString*>(dwID);
	
	PATIENT pt;
	UpdateData();
	
	if (pID != NULL)
	{
		if (myMap.Lookup(*pID, pt))
		{
			//Here value variable is used
			if (strName == pt.m_PatientName)
			{
				m_List1.DeleteAllItems();
				int nIndex = m_List1.InsertItem(0, _T("Patient Name"));
				m_List1.SetItemText(nIndex, 1, pt.m_PatientName);
				nIndex = m_List1.InsertItem(0, _T("Patient ID"));
				m_List1.SetItemText(nIndex, 1, pt.m_PatientID);
				nIndex = m_List1.InsertItem(0, _T("Gender"));
				m_List1.SetItemText(nIndex, 1, pt.m_Gender);
				nIndex = m_List1.InsertItem(0, _T("Date of Registration"));
				m_List1.SetItemText(nIndex, 1, pt.m_Date);
				nIndex = m_List1.InsertItem(0, _T("Age"));
				m_List1.SetItemText(nIndex, 1, pt.m_Age);
				//HANDLE hBitMap = ::LoadImage(AfxGetInstanceHandle(), _T("C:\RefImage\Head.bmp"), 
				//	IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				////int nIndex = 0;
				//CBitmap myBitmap;
				//myBitmap.Attach((HBITMAP)hBitMap);
				//m_Image.Add(&myBitmap, RGB(0, 255, 0));
			 //   m_List3.InsertItem(0, _T("Head"));
				//LoadImageFiles(pt);
				HANDLE hBitMap = ::LoadImage(AfxGetInstanceHandle(), _T("C:\RefImage\Head.bmp"),
					IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				CBitmap myBitmap;
				//myBitmap.LoadBitmapW(_T("C:\RefImage\Head.bmp"));
				myBitmap.Attach((HBITMAP)hBitMap);
				m_Image.Add(&myBitmap, RGB(0, 255, 0));
				m_List3.InsertItem(0, _T("Head"));
			}
			if (strName == _T("Study"))
			{
				m_List1.DeleteAllItems();
				int nIndex = m_List1.InsertItem(0, _T("Patient Height"));
				m_List1.SetItemText(nIndex, 1, pt.study.m_Height);
				nIndex = m_List1.InsertItem(0, _T("Patient Weight"));
				m_List1.SetItemText(nIndex, 1, pt.study.m_Weight);
				nIndex = m_List1.InsertItem(0, _T("Study Comments"));
				m_List1.SetItemText(nIndex, 1, pt.study.m_StudyComments);
			}
			if (strName == _T("Series"))
			{
				m_List1.DeleteAllItems();
				int nIndex = m_List1.InsertItem(0, _T("Body Part"));
				m_List1.SetItemText(nIndex, 1, pt.study.series.m_BodyPart);
				nIndex = m_List1.InsertItem(0, _T("Number of Images"));
				m_List1.SetItemText(nIndex, 1, pt.study.series.m_NumberofImages);
				nIndex = m_List1.InsertItem(0, _T("Operators Name"));
				m_List1.SetItemText(nIndex, 1, pt.study.series.m_OperatorsName);
			}
		}
	}
	else
	{
		AfxMessageBox(_T("Data not found"));
	}
	UpdateData(0);
	CFile myFile;

	*pResult = 0;
}


void CPage2::OnBnClickedSavedata()
{
	// TODO: Add your control notification handler code here
	
	CFile myFile;
	if (!myFile.Open(_T("Patient2.txt"), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate))
	{
		AfxMessageBox(_T("Data not Saved"));
		return;
	}
	CArchive ar(&myFile, CArchive::store);

	//write all contents of map into file, getcount for getting total count
	int nCount = myMap.GetCount();
	ar << nCount;

	CString strkey;
	PATIENT pt;
	CPatient optdata;
	POSITION pos = myMap.GetStartPosition();
	while (pos != NULL)
	{
		myMap.GetNextAssoc(pos, strkey, pt);
		if (strkey != "")
		{
			optdata = pt;

			//save the member variuable values to Test.txt
			optdata.Serialize(ar);
		}
		
	}
	//transfer contents of structure to the class for that create obj of the class
	//Contents retrieved from map will be struct type that is converted to class type, since serailize fn is provided in class
	//= opeartor overloading in oStudent = std, overload = in Student.h, right side struct then oper over para is struct objest
	ar.Close();
	myFile.Close();
	AfxMessageBox(_T("Data Saved Successfully"));
}


void CPage2::OnBnClickedRetrievedata()
{
	// TODO: Add your control notification handler code here
	
	
		CFile myFile;
		if (!myFile.Open(_T("Patient2.txt"), CFile::modeRead))
		{
			AfxMessageBox(_T("No data retrieved"));
			return;
		}
		CArchive ar(&myFile, CArchive::load);
		int nCount = 0;
		ar >> nCount;

		CPatient pPatient;
		PATIENT pt1;
		for (int i = 0; i < nCount; i++)
		{
			
			    pPatient.Serialize(ar);

				pPatient.ConvertToStruct(pt1);
					
				myMap[pt1.m_PatientID] = pt1;
				
		}
		InsertToTree();
	AfxMessageBox(_T("Retrieved Data Successfully"));
	
}


void CPage2::OnBnClickedExit()
{
	// TODO: Add your control notification handler code here
	OnBnClickedSavedata();
	exit(1);
}


bool CPage2::SetTransferMode()
{
	// TODO: Add your implementation code here.
	try
	{
		AfxSocketInit();
		CMyPropertySheet* wnd = (CMyPropertySheet*)AfxGetMainWnd();
		wnd->m_SocketListener.SetParent(this);
		int nResult = wnd->m_SocketListener.Create(2350);
		if (FALSE == nResult)
		{
			nResult = GetLastError();
			if (WSAEADDRINUSE == nResult)
			{
				// Server is running.
				AfxMessageBox(_T("This instance will act as a Client"));
			}
		}
		else
		{
			AfxMessageBox(_T("This instance will act as a Server"));
			if (FALSE == wnd->m_SocketListener.Listen())
			{
				return false;
			}
		}

		wnd->m_SocketSender.SetParent(this);
	}
	catch (...)
	{
		return false;
	}
	return true;
}


bool CPage2::AcceptConnection()
{
	CMyPropertySheet* wnd = (CMyPropertySheet*)AfxGetMainWnd();
	try
	{
		wnd->m_SocketListener.Accept(wnd->m_SocketSender);
		//   MessageBox(_T("Connection Accepted"));
	}
	catch (...)
	{
		return true;
	}
	return false;
}


bool CPage2::ReceiveData()
{
	CMyPropertySheet* wnd = (CMyPropertySheet*)AfxGetMainWnd();
	const int MAX_CHAR = 1024;
	try
	{
		char* pcszBuffer = new char[MAX_CHAR];
		if (0 == pcszBuffer)
		{
			return 0;
		}
		ZeroMemory(pcszBuffer, MAX_CHAR);
		int nLength = wnd->m_SocketSender.Receive(pcszBuffer, MAX_CHAR);

		if (0 >= nLength && 0 == pcszBuffer)
		{
			return 0;
		}

		CString csBuffer(pcszBuffer);
		PATIENT stPatInfo;
		ParseSharedData(csBuffer);
		PATIENT* pstPatInfo = new PATIENT(stPatInfo);
		WPARAM wParam = reinterpret_cast<WPARAM>(pstPatInfo);
		if (0 != pstPatInfo)
		{
			PostMessage(MSG_ON_PATIENT_REG, wParam, 0);
		}
		delete[] pcszBuffer;
		pcszBuffer = 0;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

void CPage2::ParseSharedData(CString csBuffer)
{
	PATIENT stPatInfo;
	int nFound = 0;
	int nStart = 0;
	int ncount;

	nFound = csBuffer.Find(_T("$"), nStart);
	ncount = nFound - nStart;
	stPatInfo.m_PatientID = csBuffer.Mid(nStart, ncount);
	nStart = nFound + 1;

	nFound = csBuffer.Find(_T("$"), nStart);
	ncount = nFound - nStart;
	stPatInfo.m_PatientName = csBuffer.Mid(nStart, ncount);
	nStart = nFound + 1;

	nFound = csBuffer.Find(_T("$"), nStart);
	ncount = nFound - nStart;
	stPatInfo.m_Gender = csBuffer.Mid(nStart, ncount);
	nStart = nFound + 1;

	nFound = csBuffer.Find(_T("$"), nStart);
	ncount = nFound - nStart;
	stPatInfo.m_Date = csBuffer.Mid(nStart, ncount);
	nStart = nFound + 1;

	nFound = csBuffer.Find(_T("$"), nStart);
	ncount = nFound - nStart;
	stPatInfo.m_Age = csBuffer.Mid(nStart, ncount);
	nStart = nFound + 1;

	nFound = csBuffer.Find(_T("$"), nStart);
	ncount = nFound - nStart;
	stPatInfo.study.m_Height = csBuffer.Mid(nStart, ncount);
	nStart = nFound + 1;

	nFound = csBuffer.Find(_T("$"), nStart);
	ncount = nFound - nStart;
	stPatInfo.study.m_Weight = csBuffer.Mid(nStart, ncount);
	nStart = nFound + 1;

	nFound = csBuffer.Find(_T("$"), nStart);
	ncount = nFound - nStart;
	stPatInfo.study.m_StudyComments = csBuffer.Mid(nStart, ncount);
	nStart = nFound + 1;

	nFound = csBuffer.Find(_T("$"), nStart);
	ncount = nFound - nStart;
	stPatInfo.study.series.m_BodyPart = csBuffer.Mid(nStart, ncount);
	nStart = nFound + 1;

	nFound = csBuffer.Find(_T("$"), nStart);
	ncount = nFound - nStart;
	stPatInfo.study.series.m_NumberofImages = csBuffer.Mid(nStart, ncount);
	nStart = nFound + 1;

	nFound = csBuffer.Find(_T("$"), nStart);
	ncount = nFound - nStart;
	stPatInfo.study.series.m_OperatorsName = csBuffer.Mid(nStart, ncount);
	nStart = nFound + 1;
	AfxMessageBox(stPatInfo.m_PatientID);
	AfxMessageBox(stPatInfo.m_PatientName);
	myMap[stPatInfo.m_PatientID] = stPatInfo;
	InsertToTree();

}


LRESULT CPage2::OnNewItemNotification(WPARAM wParam_i, LPARAM lParam_i)
{
	//  AfxMessageBox(_T("OnNewItemNotification"));
	UNREFERENCED_PARAMETER(lParam_i);
	try
	{
		PATIENT* pstPatInfo = reinterpret_cast<PATIENT*>(lParam_i);
		if (0 == pstPatInfo)
		{
			return 0;
		}
		if (pstPatInfo != NULL)
		{
			myMap[pstPatInfo->m_PatientID] = *pstPatInfo;
		}
		InsertToTree();

		SendDataToSocket(*pstPatInfo);

		//  delete pstPatInfo;
	   // pstPatInfo = 0;
	}
	catch (...)
	{
	}
	return 0;
}


bool CPage2::SendDataToSocket(const PATIENT& stPatInfo_i)
{
	//  AfxMessageBox(_T("SendDataToSocket"));

	CMyPropertySheet* wnd = (CMyPropertySheet*)AfxGetMainWnd();
	// if(wnd== NULL)
		// AfxMessageBox(_T("NULL"));
	try
	{
		if (FALSE == wnd->m_SocketSender.Create())
		{
			return false;
		}

		wnd->m_SocketSender.SendData(stPatInfo_i);
		wnd->m_SocketSender.Close();
	}
	catch (...)
	{
		return false;
	}
	return true;
}

