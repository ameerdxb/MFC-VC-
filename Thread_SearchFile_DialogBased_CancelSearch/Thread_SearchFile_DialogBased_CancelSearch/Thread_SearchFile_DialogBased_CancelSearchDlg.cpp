
// Thread_SearchFile_DialogBased_CancelSearchDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Thread_SearchFile_DialogBased_CancelSearch.h"
#include "Thread_SearchFile_DialogBased_CancelSearchDlg.h"
#include "afxdialogex.h"
#include "CSearchDialog.h"

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


// CThreadSearchFileDialogBasedCancelSearchDlg dialog



CThreadSearchFileDialogBasedCancelSearchDlg::CThreadSearchFileDialogBasedCancelSearchDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_THREAD_SEARCHFILE_DIALOGBASED_CANCELSEARCH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThreadSearchFileDialogBasedCancelSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_Path);
}

BEGIN_MESSAGE_MAP(CThreadSearchFileDialogBasedCancelSearchDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CThreadSearchFileDialogBasedCancelSearchDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CThreadSearchFileDialogBasedCancelSearchDlg message handlers

BOOL CThreadSearchFileDialogBasedCancelSearchDlg::OnInitDialog()
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
	m_Path.AddString(L"C:\\");
	m_Path.AddString(L"D:\\");
	m_Path.AddString(L"E:\\");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CThreadSearchFileDialogBasedCancelSearchDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CThreadSearchFileDialogBasedCancelSearchDlg::OnPaint()
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
HCURSOR CThreadSearchFileDialogBasedCancelSearchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CThreadSearchFileDialogBasedCancelSearchDlg::OnBnClickedButton1()
{
	CSearchDialog dlg;
	CString csPath;
	m_Path.GetLBText(m_Path.GetCurSel(),csPath);
	dlg.SetSearchPath(csPath);
	dlg.DoModal();
	// TODO: Add your control notification handler code here
}
