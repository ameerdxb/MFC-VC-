// CMyPage1.cpp : implementation file
//

#include "pch.h"
#include "PatientData.h"
#include "CMyPage1.h"
#include "afxdialogex.h"
#include"Header.h"


// CMyPage1 dialog

IMPLEMENT_DYNAMIC(CMyPage1, CPropertyPage)

CMyPage1::CMyPage1()
	: CPropertyPage(IDD_DIALOG1)
	, m_strId(_T(""))
	, m_strName(_T(""))
	, m_strAge(_T(""))
	, m_strHeight(_T(""))
	, m_strWeight(_T(""))
	, m_strComment(_T(""))
	, m_strImage(_T(""))
	, m_strOperator(_T(""))
{

}

CMyPage1::~CMyPage1()
{
}

void CMyPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_Date);
	DDX_Control(pDX, IDC_RADIO1, m_Male);
	DDX_Control(pDX, IDC_RADIO2, m_Female);
	DDX_Control(pDX, IDC_COMBO1, m_ctrlBodyPart);
	DDX_Text(pDX, IDC_ID, m_strId);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Text(pDX, IDC_AGE, m_strAge);
	DDX_Text(pDX, IDC_HEIGHT, m_strHeight);
	DDX_Text(pDX, IDC_WEIGHT, m_strWeight);
	DDX_Text(pDX, IDC_COMMENTS, m_strComment);
	DDX_Text(pDX, IDC_IMAGES, m_strImage);
	DDX_Text(pDX, IDC_OPERATOR, m_strOperator);
	DDX_Control(pDX, IDC_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(CMyPage1, CPropertyPage)
	ON_BN_CLICKED(IDC_CLEAR, &CMyPage1::OnBnClickedClear)
	ON_BN_CLICKED(IDC_EMERGENCYID, &CMyPage1::OnBnClickedEmergencyid)
	ON_BN_CLICKED(IDC_REGISTER, &CMyPage1::OnBnClickedRegister)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CMyPage1::OnDtnDatetimechangeDatetimepicker1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMyPage1::OnCbnSelchangeCombo1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMyPage1::OnLvnItemchangedList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CMyPage1::OnNMClickList1)
END_MESSAGE_MAP()


// CMyPage1 message handlers


void CMyPage1::OnBnClickedClear()
{
	// TODO: Add your control notification handler code here
	CTime t = CTime::GetCurrentTime();
	CString s = t.Format(_T("%Y%m%d%H%M%S"));
	SetDlgItemText(IDC_ID, _T("PAT_ID") + s);
	SetDlgItemText(IDC_NAME, _T(""));
	m_Male.SetCheck(1);
	m_Female.SetCheck(0);
	SetDlgItemText(IDC_AGE, _T(""));
	SetDlgItemText(IDC_HEIGHT, _T(""));
	SetDlgItemText(IDC_WEIGHT, _T(""));
	SetDlgItemText(IDC_COMMENTS, _T(""));
	SetDlgItemText(IDC_IMAGES, _T(""));
	SetDlgItemText(IDC_OPERATOR, _T(""));
	SYSTEMTIME Time;
	GetSystemTime(&Time);
	m_Date.SetTime(Time);
	m_ctrlBodyPart.SetCurSel(0);

}


BOOL CMyPage1::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	CTime t = CTime::GetCurrentTime();
	CString s = t.Format(_T("%Y%m%d%H%M%S"));
	SetDlgItemText(IDC_ID, _T("PAT_ID") + s);
	m_ctrlBodyPart.AddString(_T("HEAD"));
	m_ctrlBodyPart.AddString(_T("HAND"));
	m_ctrlBodyPart.AddString(_T("CHEST"));
	m_ctrlBodyPart.AddString(_T("HEART"));
	m_ctrlBodyPart.AddString(_T("ABDOMEN"));

	m_ctrlBodyPart.SetCurSel(0);
	m_Male.SetCheck(1);

	m_List.InsertColumn(0, _T("PATIENT ID"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(1, _T("PATIENT NAME"), LVCFMT_LEFT, 140);
	m_List.InsertColumn(2, _T("GENDER"), LVCFMT_LEFT, 85);
	m_List.InsertColumn(3, _T("DATE OF REG"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(4, _T("AGE"), LVCFMT_LEFT, 85);
	m_List.InsertColumn(5, _T("HEIGHT"), LVCFMT_LEFT,85 );
	m_List.InsertColumn(6, _T("WEIGHT"), LVCFMT_LEFT, 85);
	m_List.InsertColumn(7, _T("STUDY COMMENTS"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(8, _T("BODY PART"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(9, _T("NUMBER OF IMAGES"), LVCFMT_LEFT, 140);
	m_List.InsertColumn(10, _T("OPERATOR NAME"), LVCFMT_LEFT, 120);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CMyPage1::OnBnClickedEmergencyid()
{
	// TODO: Add your control notification handler code here
	CTime t = CTime::GetCurrentTime();
	CString s =t.Format(_T("%Y%m%d%H%M%S"));
	m_strDate = t.Format(_T("%d-%m-%Y"));
	SetDlgItemText(IDC_ID, _T("EM_ID") + s);
	SetDlgItemText(IDC_NAME, _T("EM_NAME") + s);

	m_Male.SetCheck(1);
	m_Female.SetCheck(0);
	SetDlgItemText(IDC_AGE, _T(""));
	SetDlgItemText(IDC_HEIGHT, _T(""));
	SetDlgItemText(IDC_WEIGHT, _T(""));
	SetDlgItemText(IDC_COMMENTS, _T(""));
	SetDlgItemText(IDC_IMAGES, _T(""));
	SetDlgItemText(IDC_OPERATOR, _T(""));
	SYSTEMTIME Time;
	GetSystemTime(&Time);
	m_Date.SetTime(Time);
	
	int nInd =m_ctrlBodyPart.FindStringExact(0, _T("HEAD"));
	m_ctrlBodyPart.SetCurSel(nInd);
	m_ctrlBodyPart.GetLBText(m_ctrlBodyPart.GetCurSel(), m_strBodyPart);
}


void CMyPage1::OnBnClickedRegister()
{
	// TODO: Add your control notification handler code here
	
		int nFlag = 0;
		UpdateData();
		for (int i = 0; i < m_List.GetItemCount(); i++)
		{
			if (m_List.GetItemText(i, 0) == m_strId)
			{
				nFlag = 1;
				std.m_Id = m_strId;
				std.m_Name = m_strName;
				std.m_Date = m_strDate;
				std.m_Age = m_strAge;
				if (m_Male.GetCheck())
				{
					std.m_Gender = _T("Male");
				}
				if (m_Female.GetCheck())
				{
					std.m_Gender = _T("Female");
				}

				std.STUDY.m_Height = m_strHeight;
				std.STUDY.m_Weight = m_strWeight;
				std.STUDY.m_Comments = m_strComment;

				std.STUDY.SERIES.m_Images = m_strImage;
				std.STUDY.SERIES.m_Operator = m_strOperator;
				std.STUDY.SERIES.m_BodyPart = m_strBodyPart;
				m_List.DeleteItem(i);
				int nIndexToInsert = m_List.GetItemCount();
				m_List.InsertItem(nIndexToInsert, std.m_Id);
				m_List.SetItemText(nIndexToInsert, 1, std.m_Name);
				m_List.SetItemText(nIndexToInsert, 2, std.m_Gender);
				m_List.SetItemText(nIndexToInsert, 3, std.m_Date);
				m_List.SetItemText(nIndexToInsert, 4, std.m_Age);
				m_List.SetItemText(nIndexToInsert, 5, std.STUDY.m_Height);
				m_List.SetItemText(nIndexToInsert, 6, std.STUDY.m_Weight);
				m_List.SetItemText(nIndexToInsert, 7, std.STUDY.m_Comments);
				m_List.SetItemText(nIndexToInsert, 8, std.STUDY.SERIES.m_BodyPart);
				m_List.SetItemText(nIndexToInsert, 9, std.STUDY.SERIES.m_Images);
				m_List.SetItemText(nIndexToInsert, 10, std.STUDY.SERIES.m_Operator);
				OnBnClickedClear();
				break;
			}
		}
		if(nFlag==0)
		{
			if (m_strName == "")
			{
				AfxMessageBox(_T("Please Enter Name"));
			}
			else
			{
				Reg();
			}

		}
		AfxGetMainWnd()->SendMessage(WM_USER_SECONDPAGE, (WPARAM)&std, 0);
		UpdateData(FALSE);
}




void CMyPage1::OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	GetDlgItemText(IDC_DATETIMEPICKER1, m_strDate);
	*pResult = 0;
}


void CMyPage1::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	m_ctrlBodyPart.GetLBText(m_ctrlBodyPart.GetCurSel(), m_strBodyPart);

}


void CMyPage1::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}


void CMyPage1::OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	// TODO: Add your control notification handler code here
	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	//int nIndex = m_List.GetItemCount();
	n = m_List.GetSelectionMark();
	SetDlgItemText(IDC_ID, m_List.GetItemText(n, 0));
	SetDlgItemText(IDC_NAME, m_List.GetItemText(n, 1));
	if (m_List.GetItemText(n, 2) == "Male")
	{
		m_Male.SetCheck(1);
		m_Female.SetCheck(0);
	}
	else
	{
		m_Male.SetCheck(0);
		m_Female.SetCheck(1);
	}

	COleDateTime date;
	date.ParseDateTime(m_List.GetItemText(n, 3));
	m_Date.SetTime(date);
	
	SetDlgItemText(IDC_AGE, m_List.GetItemText(n, 4));
	SetDlgItemText(IDC_HEIGHT, m_List.GetItemText(n, 5));
	SetDlgItemText(IDC_WEIGHT, m_List.GetItemText(n, 6));
	SetDlgItemText(IDC_COMMENTS, m_List.GetItemText(n, 7));

	int nInd = m_ctrlBodyPart.FindStringExact(0, m_List.GetItemText(n, 8));
	m_ctrlBodyPart.SetCurSel(nInd);

	SetDlgItemText(IDC_IMAGES, m_List.GetItemText(n, 9));
	SetDlgItemText(IDC_OPERATOR, m_List.GetItemText(n, 10));
	
	*pResult = 0;
}


void CMyPage1::Reg()
{
	// TODO: Add your implementation code here.
	std.m_Id = m_strId;
	std.m_Name = m_strName;
	std.m_Date = m_strDate;
	std.m_Age = m_strAge;
	if (m_Male.GetCheck())
	{
		std.m_Gender = _T("Male");
	}
	if (m_Female.GetCheck())
	{
		std.m_Gender = _T("Female");
	}

	std.STUDY.m_Height = m_strHeight;
	std.STUDY.m_Weight = m_strWeight;
	std.STUDY.m_Comments = m_strComment;

	std.STUDY.SERIES.m_Images = m_strImage;
	std.STUDY.SERIES.m_Operator = m_strOperator;
	std.STUDY.SERIES.m_BodyPart = m_strBodyPart;

	int nIndexToInsert = m_List.GetItemCount();
	m_List.InsertItem(nIndexToInsert, std.m_Id);
	m_List.SetItemText(nIndexToInsert, 1, std.m_Name);
	m_List.SetItemText(nIndexToInsert, 2, std.m_Gender);
	m_List.SetItemText(nIndexToInsert, 3, std.m_Date);
	m_List.SetItemText(nIndexToInsert, 4, std.m_Age);
	m_List.SetItemText(nIndexToInsert, 5, std.STUDY.m_Height);
	m_List.SetItemText(nIndexToInsert, 6, std.STUDY.m_Weight);
	m_List.SetItemText(nIndexToInsert, 7, std.STUDY.m_Comments);
	m_List.SetItemText(nIndexToInsert, 8, std.STUDY.SERIES.m_BodyPart);
	m_List.SetItemText(nIndexToInsert, 9, std.STUDY.SERIES.m_Images);
	m_List.SetItemText(nIndexToInsert, 10, std.STUDY.SERIES.m_Operator);
	OnBnClickedClear();
}
