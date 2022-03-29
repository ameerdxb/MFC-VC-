
// SharedMemoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SharedMemory.h"
#include "SharedMemoryDlg.h"
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


// CSharedMemoryDlg dialog



CSharedMemoryDlg::CSharedMemoryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSharedMemoryDlg::IDD, pParent)
	, m_Edit(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSharedMemoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edit);
}

BEGIN_MESSAGE_MAP(CSharedMemoryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSharedMemoryDlg::OnCreate)
	ON_BN_CLICKED(IDC_BUTTON2, &CSharedMemoryDlg::OnOpen)
	ON_BN_CLICKED(IDC_BUTTON3, &CSharedMemoryDlg::OnUpdate)
	ON_BN_CLICKED(IDC_BUTTON4, &CSharedMemoryDlg::OnDisplay)
END_MESSAGE_MAP()


// CSharedMemoryDlg message handlers

BOOL CSharedMemoryDlg::OnInitDialog()
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
	m_hMutex = CreateMutex(0, false, L"MyMutex");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSharedMemoryDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSharedMemoryDlg::OnPaint()
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
HCURSOR CSharedMemoryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSharedMemoryDlg::OnCreate()
{
	// TODO: Add your control notification handler code here

	m_hSharedMemory = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(stObj), L"MySharedMemory");
	 ptr = (SHMEM*)MapViewOfFile(m_hSharedMemory, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	memset(ptr, 0, sizeof(SHMEM));
}


void CSharedMemoryDlg::OnOpen()
{
	// TODO: Add your control notification handler code here
	m_hSharedMemory = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(stObj), L"MySharedMemory");
	ptr = (SHMEM*)MapViewOfFile(m_hSharedMemory, FILE_MAP_ALL_ACCESS, 0, 0, 0);
}


void CSharedMemoryDlg::OnUpdate()
{
	// TODO: Add your control notification handler code here
DWORD result =	WaitForSingleObject(m_hMutex, INFINITE);
if (WAIT_OBJECT_0 != result)
{

}
else
{
	ptr->stNum++;
	
	ReleaseMutex(m_hMutex);
}

}


void CSharedMemoryDlg::OnDisplay()
{
	// TODO: Add your control notification handler code here
	DWORD result = WaitForSingleObject(m_hMutex, INFINITE);
	if (WAIT_OBJECT_0 != result)
	{

	}
	else
	{
		m_Edit = ptr->stNum;
		UpdateData(0);
		ReleaseMutex(m_hMutex);
	}

}
