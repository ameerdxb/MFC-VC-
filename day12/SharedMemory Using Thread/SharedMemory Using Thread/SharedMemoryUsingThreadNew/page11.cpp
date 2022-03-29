// page11.cpp : implementation file
//

#include "stdafx.h"
#include "SharedMemoryUsingThreadNew.h"
#include "page11.h"
#include "time.h"
#include "ctime"


// Cpage11 dialog

IMPLEMENT_DYNAMIC(Cpage11, CPropertyPage)

Cpage11::Cpage11()
	: CPropertyPage(Cpage11::IDD)
	, var1(_T(""))
{

}

Cpage11::~Cpage11()
{
}

void Cpage11::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, var1);
	DDX_Control(pDX, IDC_EDIT2, m_id);
}


BEGIN_MESSAGE_MAP(Cpage11, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &Cpage11::OnAdd)
END_MESSAGE_MAP()


// Cpage11 message handlers

void Cpage11::OnAdd()
{
	// TODO: Add your control notification handler code here
	
	time_t time3 = time(0);
    tm *tm3 = new tm;
    localtime_s(tm3,&time3);
	int mo = tm3->tm_mon;
	int ye = tm3->tm_year;
	int da = tm3->tm_mday;
	int se = tm3->tm_sec;

	CString str ;
	str.Format(_T("%d%d%d%d"),ye,mo,da,se);
	UpdateData(1);
	
	per.nam = var1;
	m_id.SetWindowTextW(str);
	per.id = str;
	AfxGetMainWnd()->SendMessage(WM_USER_MSG,0,(LPARAM)&per);
}
