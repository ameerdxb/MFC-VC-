// CMyPage1.cpp : implementation file
//

#include "pch.h"
#include "MFCAssignment3.h"
#include "CMyPage1.h"
#include "afxdialogex.h"
#include "..\\MFCAssignment3DLL\Header.h"

// CMyPage1 dialog

IMPLEMENT_DYNAMIC(CMyPage1, CPropertyPage)

CMyPage1::CMyPage1()
	: CPropertyPage(IDD_DIALOG1)
	, m_PatientID(_T(""))
	, m_PatientName(_T(""))
	, m_DateRegistration(_T(""))
	, m_Height(_T(""))
	, m_Weight(_T(""))
	, m_Study(_T(""))
	, m_nImages(_T(""))
	, m_OperatorName(_T(""))
	, m_AgeEdit(_T(""))
	, m_BodyValue(_T(""))
	, m_AgeValue(_T(""))
{

}

CMyPage1::~CMyPage1()
{
}

void CMyPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_PatientID);
	DDX_Text(pDX, IDC_EDIT2, m_PatientName);
	DDX_Control(pDX, IDC_RADIO1, m_Male);
	DDX_Control(pDX, IDC_RADIO2, m_Female);
	DDX_Text(pDX, IDC_DATETIMEPICKER1, m_DateRegistration);
	DDX_Text(pDX, IDC_EDIT3, m_Height);
	DDX_Text(pDX, IDC_EDIT4, m_Weight);
	DDX_Text(pDX, IDC_EDIT5, m_Study);
	DDX_Text(pDX, IDC_EDIT6, m_nImages);
	DDX_Text(pDX, IDC_EDIT7, m_OperatorName);
	DDX_Control(pDX, IDC_COMBO1, m_Age);
	DDX_Control(pDX, IDC_COMBO2, m_BodyPart);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Text(pDX, IDC_EDIT8, m_AgeEdit);
	DDX_CBString(pDX, IDC_COMBO2, m_BodyValue);
	DDX_CBString(pDX, IDC_COMBO1, m_AgeValue);
	DDX_Control(pDX, IDC_EDIT1, m_PatIDControl);
}


BEGIN_MESSAGE_MAP(CMyPage1, CPropertyPage)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CMyPage1::OnDtnDatetimechangeDatetimepicker1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyPage1::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyPage1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyPage1::OnBnClickedButton2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMyPage1::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyPage1::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMyPage1 message handlers


void CMyPage1::OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


BOOL CMyPage1::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_List.InsertColumn(0, _T("Patient ID"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(1, _T("Patient Name"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(2, _T("Gender"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(3, _T("Date of Reg."), LVCFMT_LEFT, 120);
	m_List.InsertColumn(4, _T("Age"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(5, _T("Months/Years"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(6, _T("Height"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(7, _T("Weight"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(8, _T("Study Comment"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(9, _T("Body Part"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(10, _T("No. of Image"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(11, _T("Operator Name"), LVCFMT_LEFT, 120);

	m_Age.AddString(_T("Years"));
	m_Age.AddString(_T("Months"));

	FileToComboBox();
	
	//ReadContents();
	//m_BodyPart.AddString(_T("Head"));
	//m_BodyPart.AddString(_T("HandCFilePortion fileobj;

	CFilePortion fileobj;
	try
	{
		fileobj.ReadFromFile(_T("F:\\Work\\Training Quest 2\\MFCAssignment3DLL\\MyFile.txt"));
	}
	catch (...)
	{
		AfxMessageBox(_T("Error in opening"));
	}

	for (int i = 0; i < fileobj.GetSize(); i++)
	{
		m_BodyPart.AddString(fileobj.GetBodyPart());
	}




	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

//Button Register
void CMyPage1::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	CString m_Gender;
	if (m_Male.GetCheck())
	/// Set.Check is for making it checked while running the pgm///// GetCheck() is for checking whether it is selected or not

	{
		m_Gender = _T("Male");
	}
	if (m_Female.GetCheck())
	{
		m_Gender = _T("Female");
	}
	UpdateData(TRUE);
	//	MessageBox(str);
	int nIndex = m_List.InsertItem(0, m_PatientID);
	m_List.SetItemText(nIndex, 1, m_PatientName);
	m_List.SetItemText(nIndex, 2, m_Gender);
	m_List.SetItemText(nIndex, 3, m_DateRegistration);
	m_List.SetItemText(nIndex, 4, m_AgeEdit);
	m_List.SetItemText(nIndex, 5, m_AgeValue);
	m_List.SetItemText(nIndex, 6, m_Height);
	m_List.SetItemText(nIndex, 7, m_Weight);
	m_List.SetItemText(nIndex, 8, m_Study);
	m_List.SetItemText(nIndex, 9, m_BodyValue);
	m_List.SetItemText(nIndex, 10, m_nImages);
	m_List.SetItemText(nIndex, 11, m_OperatorName);

	PATIENT_INFO_t std;
	std.m_sPatientID = m_PatientID;
	std.m_sPatientName = m_PatientName;

	if (m_Male.GetCheck())
		/// Set.Check is for making it checked while running the pgm///// GetCheck() is for checking whether it is selected or not
	{
		std.m_sGender = _T("Male");
	}
	if (m_Female.GetCheck())
	{
		std.m_sGender = _T("Female");
	}
	
	std.m_PatientDateofReg = m_DateRegistration;
	std.m_sAge = m_AgeValue;
	std.oStudy.m_sHeight = m_Height;
	std.oStudy.m_sWeight = m_Weight;
	std.oStudy.m_sStudyComments = m_Study;
	std.oStudy.oSeries.m_sBodyPart= m_BodyValue;
	std.oStudy.oSeries.m_sNumberofImages = m_nImages;
	std.oStudy.oSeries.m_sOperatorsName = m_OperatorName;

	AfxGetMainWnd()->SendMessage(WM_USER_SECONDPAGE, (WPARAM)&std, 0);
	AfxGetMainWnd()->SendMessage(WM_USER_MSG, 0, (LPARAM)&std);
	AfxGetMainWnd()->SendMessage(WM_USER_WRITE_TO_SHARED_MEMORY, (WPARAM)&std, 0);
	UpdateData(FALSE);

}

//Button Clear
void CMyPage1::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	m_PatientID.Empty();
	m_PatientName.Empty();
	m_Male.SetCheck(BST_UNCHECKED);
	m_Female.SetCheck(BST_UNCHECKED);
	m_DateRegistration.Empty();
	m_AgeEdit.Empty();
	m_AgeValue.Empty();
	m_Height.Empty();
	m_Weight.Empty();
	m_Study.Empty();
	m_BodyValue.Empty();
	m_nImages.Empty();
	m_OperatorName.Empty();

	m_PatIDControl.EnableWindow(TRUE);
	UpdateData(0);

}

//Button Emergency ID
void CMyPage1::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	CTime oTime = CTime::GetCurrentTime();
	// we can only display time as CString 
	CString sTime1 = oTime.Format(_T("EM_ID_%D%H%M%S"));
	m_PatientID = sTime1;
	m_PatIDControl.EnableWindow(FALSE);
	CString sTime2 = oTime.Format(_T("EM_NAME_%D%H%M%S"));
	m_PatientName = sTime2;
	UpdateData(0);

}


void CMyPage1::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	UpdateData(1);
	m_PatientID = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem);
	m_PatientName = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem+1);
	CString gender= m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem+2);

	if (gender = "Male")
		m_Male.SetCheck(1);
	else
		m_Female.SetCheck(1);

	CString str = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem + 3);
	m_DateRegistration.SetString(str);

	m_AgeEdit = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem + 4);
	m_AgeValue = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem+5);
	m_Height = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem+6);
	m_Weight = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem + 7);
	m_Study= m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem + 8);
	m_BodyValue = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem + 9);
	m_nImages= m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem + 10);
	m_OperatorName = m_List.GetItemText(pNMLV->iItem, pNMLV->iSubItem + 11);

	UpdateData(0);
	*pResult = 0;
}


void CMyPage1::ParseFileContents(CString& strFile)
{
	//const CString BODY_PARTS = _T("BODY_PARTS");
	const CString SEPERATOR = _T(":");
	const CString VALUE_SEPERATOR = _T(",");
	const CString LINE_END = _T(";");

	CString ar[4] = { _T("BODY_PARTS"),_T("REFERENCE_IMAGE_PATH"),_T("STORE_IMAGE_PATH"),_T("DATABASE_PATH") };

	for (int i = 0; i < 4; i++)
	{
		CString SearchKey;
		SearchKey = ar[i] + SEPERATOR;// _T(":");

		//to find from file
		int nFound = strFile.Find(SearchKey, 0);

		//SearchKey.Format(_T("%s%s"), BODY_PARTS, SEPERATOR);
		//MessageBox(SearchKey);

		//int nFound = strFile.Find(SearchKey.operator LPCTSTR(), 0);

		if (-1 == nFound)
		{
			AfxMessageBox(_T("Not Found"));
		}

		//start index of fruits will be start
		//index of search key + length of search key
		strFile.Delete(0, nFound);
		nFound = 0;
		int  nStart = nFound + SearchKey.GetLength();

		nFound = strFile.Find(LINE_END, 0);

		if (-1 == nFound)
		{
			AfxMessageBox(_T("Not Found"));
		}

		int nEnd = nFound;

		//Parse list of fruits

		CString csBodyParts(strFile.Mid(nStart, nEnd - nStart));

		//AfxMessageBox(csFruits);


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

		if (i == 0)
		{
			for (int j = 0; j < arr.GetSize(); j++)
			{
				m_BodyPart.AddString(arr[j]);
				//m_BodyPart.SetCurSel(0);
			}
		}

		else if (i == 1)
		{
			for (int j = 0; j < arr.GetSize(); j++)
			{
				m_RefImageFile = arr[j];
				
			}
		}

		else if (i == 2)
		{
			for (int j = 0; j < arr.GetSize(); j++)
			{
				m_DesFile = arr[j];
			}
		}
		arr.RemoveAll();

	}
//	p1.AddData(arr);
	/*const CString PATH = _T("DATABASE_PATH");
	const CString PATH_SEPERATOR = _T(":");
	const CString PATH_VALUE_SEPERATOR = _T(",");
	const CString PATH_LINE_END = _T(";");*/

	//CString SearchKey1;
	//SearchKey1.Format(_T("%s%s"), PATH, PATH_SEPERATOR);
	//MessageBox(SearchKey1);

	//int nFound1 = strFile.Find(SearchKey1.operator LPCTSTR(), 0);

	//if (-1 == nFound1)
	//{
	//	AfxMessageBox(_T("Not Found"));
	//}
	//int  nStart1 = nFound1 + SearchKey1.GetLength();

	//nFound1 = strFile.Find(PATH_LINE_END, 0);

	//if (-1 == nFound1)
	//{
	//	AfxMessageBox(_T("Not Found"));
	//}

	//int nEnd1 = nFound1;

	////Parse list of fruits

	//CString csBodyParts1(strFile.Mid(nStart1));//, nEnd1 - nStart1));

	//AfxMessageBox(csBodyParts1);
	//p1.m_BodyPart.Insert(0, _T("head"));
}






void CMyPage1::ReadContents()
{
	//CFile myFile;
	/*if (!myFile.Open(_T("F:\\Work\\Training Quest 2\\MFCAssignment3\\PatInfoManagerConfig.txt"), CFile::modeRead))
	{
		AfxMessageBox(_T("No data retrieved"));
		return;
	}*/
	
	int nFileContentLength = 0;

	nFileContentLength = /*static_cast<int>(*/myFile.GetLength();

	//Allocate memory to read file
	char* pszFileBuffer = new char[nFileContentLength];

	//ZeroMemory(pszFileBuffer, nFileContentLength);
	myFile.Read(pszFileBuffer, nFileContentLength);


	//Converts char* to String
	CString csFileContents(pszFileBuffer);
	ParseFileContents(csFileContents);
	myFile.Close();

	delete[] pszFileBuffer;

	pszFileBuffer = 0;
}


//Scan Button
void CMyPage1::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	CScan scan;
	scan.GetDetails(m_PatientName, m_PatientID, m_BodyValue, m_nImages, m_RefImageFile, m_DesFile);
	scan.DoModal();
	/*CString csPath;
	CString sFolderName = _T("F:\\" + m_PatientID);
	CreateDirectory(sFolderName, 0);*/
	//m_BodyPart.GetLBText(m_BodyPart.GetCurSel(), csPath);

	//user defined fn to pass the value selected from combo box
	//scan.SetSearchPath(m_PatientID);
}

void CMyPage1::FileToComboBox()
{
	try
		{
			CString strFileName = _T("F:\\Work\\Training Quest 2\\MFCAssignment3\\PatInfoManagerConfig.txt");
			if (myFile.Open(strFileName, CFile::modeRead))
			{
				MessageBox(_T("Opened File"));
				//function call to read data
				ReadContents();
			}
			else
				throw "Exception";
		}
		catch (...)
		{
			MessageBox(_T("Cannot Open file"));
		}
}


