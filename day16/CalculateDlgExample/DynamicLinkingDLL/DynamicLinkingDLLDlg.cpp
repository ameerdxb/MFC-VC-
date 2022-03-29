
// DynamicLinkingDLLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DynamicLinkingDLL.h"
#include "DynamicLinkingDLLDlg.h"
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


// CDynamicLinkingDLLDlg dialog




CDynamicLinkingDLLDlg::CDynamicLinkingDLLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDynamicLinkingDLLDlg::IDD, pParent)
	, m_Num1(0)
	, m_Num2(0)
	, m_Result(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDynamicLinkingDLLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Num1);
	DDX_Text(pDX, IDC_EDIT2, m_Num2);
	DDX_Text(pDX, IDC_EDIT3, m_Result);
}

BEGIN_MESSAGE_MAP(CDynamicLinkingDLLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDynamicLinkingDLLDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDynamicLinkingDLLDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDynamicLinkingDLLDlg message handlers

BOOL CDynamicLinkingDLLDlg::OnInitDialog()
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

	hDLL=LoadLibrary("MyDLL.dll"); //by default it will search in c://windows//system 32
	if(hDLL!=NULL)
		AfxMessageBox("dll loaded successfully");

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDynamicLinkingDLLDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDynamicLinkingDLLDlg::OnPaint()
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
HCURSOR CDynamicLinkingDLLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDynamicLinkingDLLDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	addPtr=(ADDFUN)GetProcAddress(hDLL,"add");
	UpdateData(1);
	//Sleep(2000);
	m_Result=addPtr(m_Num1,m_Num2);
	UpdateData(0);
}


void CDynamicLinkingDLLDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	subPtr=(ADDFUN)GetProcAddress(hDLL,"sub");
	UpdateData(1);
	//Sleep(2000);
	m_Result=subPtr(m_Num1,m_Num2);
	UpdateData(0);
}
