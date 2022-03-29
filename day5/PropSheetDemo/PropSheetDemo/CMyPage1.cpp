// CMyPage1.cpp : implementation file
//

#include "pch.h"
#include "PropSheetDemo.h"
#include "CMyPage1.h"
#include "afxdialogex.h"
#include "Header.h"

// CMyPage1 dialog

IMPLEMENT_DYNAMIC(CMyPage1, CPropertyPage)

CMyPage1::CMyPage1()
	: CPropertyPage(IDD_DIALOG1)
	, m_Name(_T(""))
	//, m_Id(0)
	, m_Id(_T(""))
	, m_Date(_T(""))
	, m_Age(_T(" years old"))
	, m_Mark1(_T(""))
	, m_Mark2(_T(""))
	, m_Mark3(_T(""))
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CMyPage1::~CMyPage1()
{
}

void CMyPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	DDX_Control(pDX, IDC_RADIO1, m_Male);
	DDX_Control(pDX, IDC_RADIO2, m_Female);
	//DDX_Text(pDX, IDC_EDIT2, m_Id);
	DDX_Text(pDX, IDC_EDIT2, m_Id);
	DDX_Text(pDX, IDC_DATETIMEPICKER1, m_Date);
	DDX_Text(pDX, IDC_EDIT4, m_Age);
	DDX_Text(pDX, IDC_EDIT5, m_Mark1);
	DDX_Text(pDX, IDC_EDIT6, m_Mark2);
	DDX_Text(pDX, IDC_EDIT7, m_Mark3);
}


BEGIN_MESSAGE_MAP(CMyPage1, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyPage1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &CMyPage1::OnBnClickedRadio1)
	ON_EN_CHANGE(IDC_EDIT2, &CMyPage1::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyPage1::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMyPage1 message handlers


BOOL CMyPage1::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_Male.SetCheck(1);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CMyPage1::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	STUDENT std;
	UpdateData();
	std.m_Name = m_Name;
	if (m_Male.GetCheck())
	{
		std.m_Gender = _T("Male");
	}
	if (m_Female.GetCheck())
	{
		std.m_Gender = _T("Female");
	}
	std.m_Id = m_Id;
	std.m_Date = m_Date;
	std.m_Age = m_Age;
	std.m_Mark1 = m_Mark1;
	std.m_Mark2 = m_Mark2;
	std.m_Mark3 = m_Mark3;
	CTime t = CTime::GetCurrentTime();
	CString id = t.Format(_T("%I%M%S"));
	std.m_CurTime = id;
	AfxGetMainWnd()->SendMessage(WM_USER_SECONDPAGE, (WPARAM)&std, 0);
}


void CMyPage1::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
}


void CMyPage1::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CMyPage1::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here

	m_Id = ""; // m_Id.Empty();
	m_Name = "";
	m_Male.SetCheck(1);
	m_Female.SetCheck(0);
	m_Date = "";
	m_Age = " years old";
	m_Mark1 = "";
	m_Mark2 = "";
	m_Mark3 = "";
	
	UpdateData(0);
}
