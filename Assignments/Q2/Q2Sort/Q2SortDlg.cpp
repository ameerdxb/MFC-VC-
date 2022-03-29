
// Q2SortDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Q2Sort.h"
#include "Q2SortDlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CQ2SortDlg dialog



CQ2SortDlg::CQ2SortDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Q2SORT_DIALOG, pParent)
	, m_Value(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQ2SortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Value);
	DDV_MaxChars(pDX, m_Value, 25);
	DDX_Control(pDX, IDC_LIST1, m_ListControl);
}

BEGIN_MESSAGE_MAP(CQ2SortDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST1, &CQ2SortDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CQ2SortDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CQ2SortDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CQ2SortDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CQ2SortDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CQ2SortDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CQ2SortDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CQ2SortDlg message handlers

BOOL CQ2SortDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CQ2SortDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CQ2SortDlg::OnPaint()
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
HCURSOR CQ2SortDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CQ2SortDlg::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
}


void CQ2SortDlg::OnBnClickedButton1()
{
	// Add
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_ListControl.AddString(m_Value);
	m_Value.Empty();
	UpdateData(FALSE);

}


void CQ2SortDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CQ2SortDlg::OnBnClickedButton2()
{
	// Find
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int nIndex = 0;
	if ((nIndex = m_ListControl.FindString(nIndex, m_Value)) != LB_ERR)
	{
		MessageBoxW(_T("Found!!"));
	}
	else
	{
		MessageBoxW(_T("Not Found!!"));
	}
	UpdateData(FALSE);
}


void CQ2SortDlg::OnBnClickedButton3()
{
	// Delete
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int nIndex = m_ListControl.GetCurSel();
	m_ListControl.DeleteString(nIndex);
	UpdateData(FALSE);
}


void CQ2SortDlg::OnBnClickedButton4()
{
	// Sort Ascending
	// TODO: Add your control notification handler code here
	CString str;
	CString str1;
	int nIndex;
	for (int j = 0; j < m_ListControl.GetCount(); j++)
	{
		m_ListControl.SetCurSel(0);
		for (int i = 0; i < m_ListControl.GetCount(); i++)
		{
			nIndex = m_ListControl.GetCurSel();
			m_ListControl.GetText(nIndex, str);
			nIndex++;
			m_ListControl.SetCurSel(nIndex);
			if (nIndex != m_ListControl.GetCount())
			{
				m_ListControl.GetText(nIndex, str1);
			}
			else
			{
				return;
			}
			if (str > str1)
			{
				m_ListControl.AddString(str);
				m_ListControl.DeleteString(nIndex - 1);
			}
		}
	}
}


void CQ2SortDlg::OnBnClickedButton5()
{
	// Sort descending
	// TODO: Add your control notification handler code here
	CString str;
	CString str1;
	int nIndex;
	for (int j = 0; j < m_ListControl.GetCount(); j++)
	{
		m_ListControl.SetCurSel(0);
		for (int i = 0; i < m_ListControl.GetCount(); i++)
		{
			nIndex = m_ListControl.GetCurSel();
			m_ListControl.GetText(nIndex, str);
			nIndex++;
			m_ListControl.SetCurSel(nIndex);
			if (nIndex != m_ListControl.GetCount())
			{
				m_ListControl.GetText(nIndex, str1);
			}
			else
			{
				return;
			}
			if (str < str1)
			{
				m_ListControl.AddString(str);
				m_ListControl.DeleteString(nIndex - 1);
			}
		}
	}
}
