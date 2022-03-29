// Page1.cpp : implementation file
//

#include "pch.h"
#include "PatientInfoManager.h"
#include "Page1.h"
#include "afxdialogex.h"
#include"Header.h"
#include"ScanDialog.h"
// CPage1 dialog

IMPLEMENT_DYNAMIC(CPage1, CPropertyPage)

CPage1::CPage1()
	: CPropertyPage(IDD_DIALOG1)
	, m_PatientID(_T(""))
	, m_PatientName(_T(""))
	, m_Date(_T(""))
	, m_Age(_T(""))
	, m_Height(_T(""))
	, m_Weight(_T(""))
	, m_StudyComments(_T(""))
	, m_NumberofImages(_T(""))
	, m_OperatorsName(_T(""))
	,m_BodyPart(_T(""))
{

}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Text(pDX, IDC_PATIENTID1, m_PatientID);
	DDX_Text(pDX, IDC_PATIENTNAME1, m_PatientName);
	DDX_Control(pDX, IDC_MALE, m_Male);
	DDX_Control(pDX, IDC_FEMALE, m_Female);
	DDX_Text(pDX, IDC_DATETIMEPICKER1, m_Date);
	DDX_Text(pDX, IDC_EDIT2, m_Age);
	DDX_Control(pDX, IDC_COMBO1, m_Age1);
	DDX_Text(pDX, IDC_HEIGHT1, m_Height);
	DDX_Text(pDX, IDC_HEIGHT3, m_Weight);
	DDX_Text(pDX, IDC_HEIGHT5, m_StudyComments);
	DDX_Control(pDX, IDC_BODYPART, m_ctrlBodyPart);
	DDX_Text(pDX, IDC_BODYPART, m_BodyPart);
	DDX_Text(pDX, IDC_NOOFIMAGES, m_NumberofImages);
	DDX_Text(pDX, IDC_OPERATORSNAME, m_OperatorsName);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_Date1);
	DDX_Control(pDX, IDC_PATIENTID1, m_PatientID1);
}


BEGIN_MESSAGE_MAP(CPage1, CPropertyPage)
	ON_BN_CLICKED(IDC_CLEAR, &CPage1::OnBnClickedClear)
	ON_BN_CLICKED(IDC_REGISTER, &CPage1::OnBnClickedRegister)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CPage1::OnLvnItemchangedList1)
	
	ON_BN_CLICKED(IDC_EMERGENCY_ID, &CPage1::OnBnClickedEmergencyId)
	ON_CBN_SELCHANGE(IDC_BODYPART, &CPage1::OnCbnSelchangeBodypart)
	ON_BN_CLICKED(IDC_SCAN, &CPage1::OnBnClickedScan)
END_MESSAGE_MAP()


// CPage1 message handlers


BOOL CPage1::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	UpdateData(1);
	m_List.InsertColumn(0, _T("Patient Name"), LVCFMT_CENTER, 120);
	m_List.InsertColumn(1, _T("Patient ID"), LVCFMT_CENTER, 140);
	m_List.InsertColumn(2, _T("Gender"), LVCFMT_CENTER, 100);
	m_List.InsertColumn(3, _T("Date of Registration"), LVCFMT_CENTER, 120);
	m_List.InsertColumn(4, _T("Age"), LVCFMT_CENTER, 80);
	m_List.InsertColumn(5, _T("Height"), LVCFMT_CENTER, 80);
	m_List.InsertColumn(6, _T("Weight"), LVCFMT_CENTER, 80);
	m_List.InsertColumn(7, _T("Study Comments"), LVCFMT_CENTER, 120);
	m_List.InsertColumn(8, _T("Body Part"), LVCFMT_CENTER, 100);
	m_List.InsertColumn(9, _T("Number of Images"), LVCFMT_CENTER, 100);
	m_List.InsertColumn(10, _T("Operators Name"), LVCFMT_CENTER, 120);
	CSize size;
	m_List.Scroll(size);
	m_Age1.InsertString(0,_T("years"));
	m_Age1.InsertString(1, _T("months"));
	m_Age1.InsertString(2, _T("days"));
	m_Age1.SelectString(0, _T("years"));
	ReadContents();
	m_Male.SetCheck(1);
	m_PatientID1.EnableWindow(0);
	SYSTEMTIME st;
	GetSystemTime(&st);
	CString str;
	str.Format(_T("PAT_ID_%d%d%d%d%d%d"), st.wYear, st.wMonth, st.wDay,st.wHour,st.wMinute,st.wSecond);
	m_PatientID = str;
	UpdateData(0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CPage1::OnBnClickedClear()
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	SYSTEMTIME st;
	GetSystemTime(&st);
	CString str;
	str.Format(_T("PAT_ID_%d%d%d%d%d%d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	m_PatientID = str;
	m_Date1.SetTime(&st);
	m_PatientName =  "";
	m_Male.SetCheck(1);
	m_Female.SetCheck(0);
	m_Age = "";
	m_Age1.SelectString(0, _T("years"));
	m_Height = "";
	m_Weight = "";
	m_StudyComments = "";
	m_BodyPart = _T("Head");
	m_NumberofImages = "";
	m_OperatorsName = "";
	UpdateData(0);
}


void CPage1::OnBnClickedRegister()
{
	UpdateData(1);
	
	int nFlag = 0;
	PATIENT pt;
	for (int i = 0; i < m_List.GetItemCount(); i++)
	{
		if (m_List.GetItemText(i, 1) == m_PatientID)
		{
			nFlag = 1;
			
			CString str1;
			int i = m_Age1.GetCurSel();
			m_Age1.GetLBText(i, str1);
			CString str2;
			int j = m_ctrlBodyPart.GetCurSel();
			m_ctrlBodyPart.GetLBText(j, str2);
			pt.m_PatientID = m_PatientID;
			pt.m_PatientName = m_PatientName;
			pt.m_Date = m_Date;
			pt.m_Age = m_Age;
			if (m_Male.GetCheck())
			{
				pt.m_Gender = _T("Male");
			}
			if (m_Female.GetCheck())
			{
				pt.m_Gender = _T("Female");
			}

			pt.study.m_Height = m_Height;
			pt.study.m_Weight = m_Weight;
			pt.study.m_StudyComments = m_StudyComments;
			int n = m_List.GetSelectionMark();
			pt.study.series.m_NumberofImages = m_NumberofImages;
			pt.study.series.m_OperatorsName = m_OperatorsName;
			pt.study.series.m_BodyPart = m_BodyPart;
			m_List.DeleteItem(n);
			int nIndexToInsert = m_List.GetItemCount();
			m_List.InsertItem(nIndexToInsert, pt.m_PatientName);
			m_List.SetItemText(nIndexToInsert, 1, pt.m_PatientID);
			m_List.SetItemText(nIndexToInsert, 2, pt.m_Gender);
			m_List.SetItemText(nIndexToInsert, 3, pt.m_Date);
			m_List.SetItemText(nIndexToInsert, 4, pt.m_Age);
			m_List.SetItemText(nIndexToInsert, 5, pt.study.m_Height);
			m_List.SetItemText(nIndexToInsert, 6, pt.study.m_Weight);
			m_List.SetItemText(nIndexToInsert, 7, pt.study.m_StudyComments);
			m_List.SetItemText(nIndexToInsert, 8, pt.study.series.m_BodyPart);
			m_List.SetItemText(nIndexToInsert, 9, pt.study.series.m_NumberofImages);
			m_List.SetItemText(nIndexToInsert, 10, pt.study.series.m_OperatorsName);
			OnBnClickedClear();
		
			break;
		}
	}
	if (nFlag == 0)
	{
		CString str1;
		int i = m_Age1.GetCurSel();
		m_Age1.GetLBText(i, str1);
		CString str2;
		int j = m_ctrlBodyPart.GetCurSel();
		m_ctrlBodyPart.GetLBText(j, str2);
		pt.m_PatientID = m_PatientID;
		pt.m_PatientName = m_PatientName;
		pt.m_Date = m_Date;
		pt.m_Age = m_Age;
		if (m_Male.GetCheck())
		{
			pt.m_Gender = _T("Male");
		}
		if (m_Female.GetCheck())
		{
			pt.m_Gender = _T("Female");
		}

		pt.study.m_Height = m_Height;
		pt.study.m_Weight = m_Weight;
		pt.study.m_StudyComments = m_StudyComments;

		pt.study.series.m_NumberofImages = m_NumberofImages;
		pt.study.series.m_OperatorsName = m_OperatorsName;
		pt.study.series.m_BodyPart = m_BodyPart;
		int nIndexToInsert = m_List.GetItemCount();
		m_List.InsertItem(nIndexToInsert, pt.m_PatientName);
		m_List.SetItemText(nIndexToInsert, 1, pt.m_PatientID);
		m_List.SetItemText(nIndexToInsert, 2, pt.m_Gender);
		m_List.SetItemText(nIndexToInsert, 3, pt.m_Date);
		m_List.SetItemText(nIndexToInsert, 4, pt.m_Age);
		m_List.SetItemText(nIndexToInsert, 5, pt.study.m_Height);
		m_List.SetItemText(nIndexToInsert, 6, pt.study.m_Weight);
		m_List.SetItemText(nIndexToInsert, 7, pt.study.m_StudyComments);
		m_List.SetItemText(nIndexToInsert, 8, pt.study.series.m_BodyPart);
		m_List.SetItemText(nIndexToInsert, 9, pt.study.series.m_NumberofImages);
		m_List.SetItemText(nIndexToInsert, 10, pt.study.series.m_OperatorsName);
		OnBnClickedClear();
	}
	AfxGetMainWnd()->SendMessage(WM_USER_SECONDPAGE, (WPARAM)&pt, 0);
	AfxGetMainWnd()->SendMessage(WM_USER_MSG, 0, (LPARAM)&pt);
	AfxGetMainWnd()->SendMessage(MSG_ON_PATIENT_REG, (WPARAM)&pt, 0);
	UpdateData(0);
}


void CPage1::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	UpdateData(1);
	m_PatientName = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem);
	m_PatientID = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem+1);
	CString gender = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem + 2);
	if ("Male" == gender)
	{
		m_Male.SetCheck(1);
	}
	else
	{
		m_Female.SetCheck(1);
		m_Male.SetCheck(0);
	}
	COleDateTime date;
	date.ParseDateTime(m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem+3));
	m_Date1.SetTime(date);
	CString Age = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem + 4);
	for (int i = 0; i < 2; i++)
	{
		m_Age += Age[i];
	}
	CString str;
	str = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem+3);
	m_Height = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem + 5);
	m_Weight = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem + 6);
	m_StudyComments = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem + 7);
	m_BodyPart = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem + 8);
	m_ctrlBodyPart.SelectString(0, m_BodyPart);
	m_NumberofImages = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem + 9);
	m_OperatorsName = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem + 10);
	UpdateData(0);

	*pResult = 0;
}


void CPage1::OnBnClickedEmergencyId()
{
	UpdateData(1);
	SYSTEMTIME st;
	GetSystemTime(&st);
	CString str;
	str.Format(_T("EMP_ID_%d%d%d%d%d%d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	m_PatientID = str;
	CString str1;
	str1.Format(_T("EMP_NAME_%d%d%d%d%d%d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	m_Date1.SetTime(&st);
	m_PatientName = str1;
	m_Male.SetCheck(1);
	m_Female.SetCheck(0);
	m_Age = "";
	m_Age1.SelectString(0, _T("years"));
	m_Height = "";
	m_Weight = "";
	m_StudyComments = "";
	m_BodyPart = _T("Head");
	m_NumberofImages = "";
	m_OperatorsName = "";
	UpdateData(0);
}


void CPage1::OnCbnSelchangeBodypart()
{
	// TODO: Add your control notification handler code here
	m_ctrlBodyPart.GetLBText(m_ctrlBodyPart.GetCurSel(), m_BodyPart);
}


void CPage1::ParseFileContents()
{
	const CString BODY_PARTS = _T("BODY_PARTS");
	const CString SEPERATOR = _T(":");
	const CString VALUE_SEPERATOR = _T(",");
	const CString LINE_END = _T(";");

	CString SearchKey;
	SearchKey.Format(_T("%s%s"), BODY_PARTS, SEPERATOR);
	//MessageBox(SearchKey);

	int nFound = m_strFile.Find(SearchKey.operator LPCTSTR(), 0);

	if (-1 == nFound)
	{
		AfxMessageBox(_T("Not Found"));
	}

	//start index of fruits will be start
	//index of search key + length of search key
	int  nStart = nFound + SearchKey.GetLength();

	nFound = m_strFile.Find(LINE_END, 0);

	if (-1 == nFound)
	{
		AfxMessageBox(_T("Not Found"));
	}

	int nEnd = nFound;

	//Parse list of fruits

	CString csBodyParts(m_strFile.Mid(nStart, nEnd - nStart));

	AfxMessageBox(csBodyParts);


	nFound = 0;
	nStart = 0;

	csBodyParts = csBodyParts + VALUE_SEPERATOR;

	while (-1 != nFound)
	{
		nFound = csBodyParts.Find(VALUE_SEPERATOR, nFound);
		if (-1 == nFound)
		{
			break;
		}


		CString data = csBodyParts.Mid(nStart, nFound - nStart);

		//AfxMessageBox(data);


		arr.Add(data); // Adding to Collection class
		
		
		nStart = ++nFound;
	}//while loop ends
	for (int i = 0; i < arr.GetSize(); i++)
	{
		m_ctrlBodyPart.AddString(arr[i]);
	}
	CreateDir(m_strFile);
	
	UpdateData();
	m_BodyPart = _T("Head");
}


void CPage1::ReadContents()
{
	if (!myFile.Open(_T("D:\PatInfoManagerConfig.txt"), CFile::modeRead))
	{
		AfxMessageBox(_T("No data retrieved"));
		return;
	}
	int nFileContentLength = 0;

	nFileContentLength = static_cast<int>(myFile.GetLength());

	//Allocate memory to read file
	char* pszFileBuffer = new char[nFileContentLength];

	ZeroMemory(pszFileBuffer, nFileContentLength);
	myFile.Read(pszFileBuffer, --nFileContentLength);


	//Converts char* to String
	CString csFileContents(pszFileBuffer);
	m_strFile = csFileContents;
	ParseFileContents();
	//OpenImageFile(csFileContents);
	//StoreImageFile(csFileContents);
	myFile.Close();

	delete[] pszFileBuffer;

	pszFileBuffer = 0;
}


void CPage1::CreateDir(CString& strFile)
{
	const CString PATH = _T("DATABASE_PATH");
	const CString PATH_SEPERATOR = _T(":");
	const CString PATH_VALUE_SEPERATOR = _T(",");
	const CString PATH_LINE_END = _T(";");

	CString SearchKey1;
	SearchKey1.Format(_T("%s%s"), PATH, PATH_SEPERATOR);
	MessageBox(SearchKey1);

	int nFound1 = strFile.Find(SearchKey1.operator LPCTSTR(), 0);

	if (-1 == nFound1)
	{
		AfxMessageBox(_T("Not Found"));
	}
	int  nStart1 = nFound1 + SearchKey1.GetLength();

	nFound1 = strFile.Find(PATH_LINE_END, 0);

	if (-1 == nFound1)
	{
		AfxMessageBox(_T("Not Found"));
	}

	int nEnd1 = nFound1;

	CString csBodyParts1(strFile.Mid(nStart1));

	if (CreateDirectory(csBodyParts1, NULL))
	{
		AfxMessageBox(csBodyParts1);
	}
}


void CPage1::OnBnClickedScan()
{
	// TODO: Add your control notification handler code here
	CScanDialog dlg;
	dlg.SetData(m_PatientName, m_PatientID,m_strFile,m_BodyPart,m_NumberofImages);
	dlg.DoModal();
	
}
