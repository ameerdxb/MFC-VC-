
// FileCopyThreadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileCopyThread.h"
#include "FileCopyThreadDlg.h"
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


// CFileCopyThreadDlg dialog



CFileCopyThreadDlg::CFileCopyThreadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileCopyThreadDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileCopyThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFileCopyThreadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFileCopyThreadDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CFileCopyThreadDlg message handlers

BOOL CFileCopyThreadDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFileCopyThreadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFileCopyThreadDlg::OnPaint()
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
HCURSOR CFileCopyThreadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
/*
UINT _cdecl InitalWrite(LPVOID lparam)
{
	CFileCopyThreadDlg* hwnd = (CFileCopyThreadDlg*)lparam;
	CFile file;
	file.Open(L"Sample1.txt", CFile::modeCreate | CFile::modeWrite);
	CString str = L"In any moment of decision, the best thing you can do is the right thing, the next best thing is the wrong thing, and the worst thing you can do is nothing.";
	file.Write(str, str.GetLength()*2);
	return 0;
	
}
*/

UINT _cdecl ReadSample1(LPVOID lparam)
{
	CFileCopyThreadDlg* hwnd = (CFileCopyThreadDlg*)lparam;
	CFile file;
	file.Open(L"Sample1.txt", CFile::modeRead);
	int size = file.GetLength();
	TCHAR *chBuffer = new TCHAR[size/2];
	file.Read(chBuffer, size);
	chBuffer[size/2] = '\0';
	file.Close();
	CString str(chBuffer);
    file.Open(L"Sample2.txt", CFile::modeCreate | CFile::modeWrite);
	file.Write(str, str.GetLength() * 2);
	file.Close();
	SetEvent(hwnd->hevent);
	return 0;

}



UINT _cdecl ReadSample2(LPVOID lparam)
{

	CFileCopyThreadDlg* hwnd = (CFileCopyThreadDlg*)lparam;
	WaitForSingleObject(hwnd->hevent, INFINITE);
	CFile file;
	file.Open(L"Sample2.txt", CFile::modeRead);
	int size = file.GetLength();
	TCHAR *chBuffer = new TCHAR[size / 2];
	file.Read(chBuffer, size);
	chBuffer[size / 2] = '\0';
	file.Close();
	CString str(chBuffer);
	file.Open(L"Sample3.txt", CFile::modeCreate | CFile::modeWrite);
	file.Write(str, str.GetLength() * 2);
	file.Close();
	return 0;

}

void CFileCopyThreadDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	//AfxBeginThread(InitalWrite, this);
	hevent = CreateEvent(NULL, FALSE, FALSE, NULL);
	AfxBeginThread(ReadSample2, this);
	AfxBeginThread(ReadSample1, this);

	

}
