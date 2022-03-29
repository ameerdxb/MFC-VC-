// CScanModalChild.cpp : implementation file
//

#include "pch.h"
#include "Q4Modal.h"
#include "CScanModalChild.h"
#include "afxdialogex.h"


// CScanModalChild dialog

IMPLEMENT_DYNAMIC(CScanModalChild, CDialog)

CScanModalChild::CScanModalChild(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_ID(0)
	, m_Name(_T(""))
{

}

CScanModalChild::~CScanModalChild()
{
}

void CScanModalChild::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ID);
	DDX_Text(pDX, IDC_EDIT2, m_Name);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}


BEGIN_MESSAGE_MAP(CScanModalChild, CDialog)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CScanModalChild::OnNMCustomdrawProgress1)
END_MESSAGE_MAP()


// CScanModalChild message handlers


void CScanModalChild::OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}


BOOL CScanModalChild::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_Progress.EnableWindow(TRUE);
	m_Progress.SetRange(1, 100);
	for (int i = 0; i <= 100; i++)
	{
		m_Progress.SetPos(i);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
