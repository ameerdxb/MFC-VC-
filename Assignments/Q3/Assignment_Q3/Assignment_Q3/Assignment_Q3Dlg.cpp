
// Assignment_Q3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Assignment_Q3.h"
#include "Assignment_Q3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAssignment_Q3Dlg dialog



CAssignment_Q3Dlg::CAssignment_Q3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAssignment_Q3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAssignment_Q3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listOne);
	DDX_Control(pDX, IDC_LIST2, m_ListTwo);
}

BEGIN_MESSAGE_MAP(CAssignment_Q3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CAssignment_Q3Dlg::OnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAssignment_Q3Dlg::OnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAssignment_Q3Dlg::OnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAssignment_Q3Dlg::OnClickedButton4)
	ON_LBN_SELCHANGE(IDC_LIST1, &CAssignment_Q3Dlg::OnLbnSelchangeList1)
	ON_LBN_SELCHANGE(IDC_LIST2, &CAssignment_Q3Dlg::OnLbnSelchangeList2)
END_MESSAGE_MAP()


// CAssignment_Q3Dlg message handlers

BOOL CAssignment_Q3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);

	const TCHAR Fruits[][20] = {
		_T("Apple"),
		_T("Banana"),
		_T("Grapes"),
		_T("Mango"),
		_T("Orange"),
		_T("Guava"),
	};

	for (int i = 0; i < 6; i++)
		m_listOne.AddString(Fruits[i]);
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAssignment_Q3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAssignment_Q3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAssignment_Q3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAssignment_Q3Dlg::OnClickedButton1()
{
	// TODO: Add your control notification handler code here
	int nIndex = m_listOne.GetCurSel();
	CString strTemp;
	m_listOne.GetText(nIndex, strTemp);
	if (nIndex != LB_ERR)
	{
		m_listOne.DeleteString(nIndex);
		m_listOne.SetCurSel(0);
	}
	m_listOne.SetCurSel(nIndex);
	int nIndex2 = m_ListTwo.AddString(strTemp);
	m_ListTwo.SetCurSel(nIndex2);

	if (m_listOne.GetCount() == 0)
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	}
	if (m_ListTwo.GetCount() != 0)
	{
		GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);

	}
	UpdateData(TRUE);
}


void CAssignment_Q3Dlg::OnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CString strTemp;
	for (int i = 0; i < m_listOne.GetCount(); i++)
	{
		m_listOne.GetText(i, strTemp);
		int nIndex = m_ListTwo.AddString(strTemp);
		m_ListTwo.SetCurSel(nIndex);

	}
	//int count = m_listOne.GetCount();
		m_listOne.ResetContent();
	if (m_listOne.GetCount() == 0)
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);


	}
	if (m_ListTwo.GetCount() != 0)
	{
		GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);

	}
	UpdateData(TRUE);
}


void CAssignment_Q3Dlg::OnClickedButton3()
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ListTwo.GetCurSel();
	CString strTemp;
	m_ListTwo.GetText(nIndex, strTemp);
	if (nIndex != LB_ERR)
	{
		m_ListTwo.DeleteString(nIndex);
		m_ListTwo.SetCurSel(0);
	}
	m_ListTwo.SetCurSel(nIndex);
	int nIndex2 = m_listOne.AddString(strTemp);
	m_listOne.SetCurSel(nIndex2);

	if (m_ListTwo.GetCount() == 0)
	{
		GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	}
	if (m_listOne.GetCount() != 0)
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);

	}
	UpdateData(TRUE);

}


void CAssignment_Q3Dlg::OnClickedButton4()
{
	// TODO: Add your control notification handler code here
	CString strTemp;
	for (int i = 0; i < m_ListTwo.GetCount(); i++)
	{
		m_ListTwo.GetText(i, strTemp);
		int nIndex = m_listOne.AddString(strTemp);
		m_listOne.SetCurSel(nIndex);

	}
		m_ListTwo.ResetContent();
	if (m_ListTwo.GetCount() == 0)
	{
		GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);


	}
	if (m_listOne.GetCount() != 0)
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);

	}
	UpdateData(TRUE);
}


void CAssignment_Q3Dlg::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
}


void CAssignment_Q3Dlg::OnLbnSelchangeList2()
{
	// TODO: Add your control notification handler code here
}
