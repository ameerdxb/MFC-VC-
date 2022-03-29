// CMyPage1.cpp : implementation file
//

#include "pch.h"
#include "Assignment_Q5.h"
#include "CMyPage1.h"
#include "afxdialogex.h"
#include "Header.h"


// CMyPage1 dialog

IMPLEMENT_DYNAMIC(CMyPage1, CPropertyPage)

CMyPage1::CMyPage1()
	: CPropertyPage(IDD_DIALOG1)
	, m_strId(_T(""))
	, m_strName(_T(""))
	, m_strAge(_T(""))
	, m_strMark1(_T(""))
	//, m(_T(""))
	, m_strMark2(_T(""))
	, m_strMark3(_T(""))
	//, m_strDate(COleDateTime::GetCurrentTime())
	, m_strDate(_T(""))
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
	DDX_Text(pDX, IDC_EDIT1, m_strId);
	DDX_Text(pDX, IDC_EDIT2, m_strName);
	DDX_Control(pDX, IDC_RADIO1, m_Male);
	DDX_Control(pDX, IDC_RADIO2, m_Female);
	DDX_Text(pDX, IDC_EDIT3, m_strAge);
	DDX_Text(pDX, IDC_EDIT4, m_strMark1);
	DDX_Text(pDX, IDC_EDIT5, m_strMark2);
	DDX_Text(pDX, IDC_EDIT6, m_strMark3);
	//DDX_Control(pDX, IDC_DATETIMEPICKER1, m_strDate);
}


BEGIN_MESSAGE_MAP(CMyPage1, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyPage1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyPage1::OnBnClickedButton2)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CMyPage1::OnDtnDatetimechangeDatetimepicker1)
END_MESSAGE_MAP()


// CMyPage1 message handlers


void CMyPage1::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	STUDENT std;
	UpdateData();
	std.m_Name = m_strName;
	std.m_Id = m_strId;
	std.m_Age = m_strAge;
	std.MARK.m_Mark1 = m_strMark1;
	std.MARK.m_Mark2 = m_strMark2;
	std.MARK.m_Mark3 = m_strMark3;
	std.m_DateReg = m_strDate;
	if (m_Male.GetCheck())
	{
		std.m_Gender = _T("Male");
	}
	if (m_Female.GetCheck())
	{
		std.m_Gender = _T("Female");
	}
	AfxGetMainWnd()->SendMessage(WM_USER_SECONDPAGE, (WPARAM)&std, 0);
	MessageBox(_T("Data saved"));
}


void CMyPage1::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	m_strName.SetString(_T(""));
	m_strAge.SetString(_T(""));
	m_strId.SetString(_T(""));
	m_strMark1.SetString(_T(""));
	m_strMark2.SetString(_T(""));
	m_strMark3.SetString(_T(""));
	UpdateData(FALSE);

}


void CMyPage1::OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_DATETIMEPICKER1, m_strDate);
	*pResult = 0;
}
