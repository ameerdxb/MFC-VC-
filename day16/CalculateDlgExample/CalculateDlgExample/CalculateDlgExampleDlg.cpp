
// CalculateDlgExampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CalculateDlgExample.h"
#include "CalculateDlgExampleDlg.h"
#include "afxdialogex.h"
//#include "..\\MyDLL\\MyHeader.h"

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


// CCalculateDlgExampleDlg dialog




CCalculateDlgExampleDlg::CCalculateDlgExampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCalculateDlgExampleDlg::IDD, pParent)
	, m_Num1(0)
	, m_Num2(0)
	, m_Result(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculateDlgExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Num1);
	DDX_Text(pDX, IDC_EDIT2, m_Num2);
	DDX_Text(pDX, IDC_EDIT3, m_Result);
}

BEGIN_MESSAGE_MAP(CCalculateDlgExampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCalculateDlgExampleDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCalculateDlgExampleDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CCalculateDlgExampleDlg message handlers

BOOL CCalculateDlgExampleDlg::OnInitDialog()
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

	hDll = LoadLibrary(L"MyDLL.dll");
	if (hDll)
	{
		AfxMessageBox(L"Success");
	}
	return TRUE; // return TRUE  unless you set the focus to a control
}

void CCalculateDlgExampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalculateDlgExampleDlg::OnPaint()
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
HCURSOR CCalculateDlgExampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalculateDlgExampleDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	AddPtr aPtr;
	aPtr = (AddPtr)GetProcAddress(hDll, "add");
	m_Result=aPtr(m_Num1,m_Num2);
	UpdateData(0);
}


void CCalculateDlgExampleDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	SubPtr sPtr;
	sPtr = (SubPtr)GetProcAddress(hDll, "sub");
	m_Result=sPtr(m_Num1,m_Num2);
	UpdateData(0);
}
