
// SieveThreadDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "SieveThread.h"
#include "SieveThreadDlg.h"
#include "afxdialogex.h"
#include "Header.h"

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


// CSieveThreadDlg dialog



CSieveThreadDlg::CSieveThreadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SIEVETHREAD_DIALOG, pParent)
	, m_Result(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSieveThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_Result);
}

BEGIN_MESSAGE_MAP(CSieveThreadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSieveThreadDlg::OnBnStart)
	ON_MESSAGE(WM_USER_PRIME_COUNT,&CSieveThreadDlg::OnPrimeCount)
END_MESSAGE_MAP()


// CSieveThreadDlg message handlers

BOOL CSieveThreadDlg::OnInitDialog()
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

void CSieveThreadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSieveThreadDlg::OnPaint()
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
HCURSOR CSieveThreadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int Sieve(int nMax)
{
	PBYTE pBuffer = new BYTE[nMax + 1];
	::FillMemory(pBuffer, nMax + 1, 1);

	int nLimit = 2;
	while (nLimit * nLimit < nMax)
		nLimit++;

	for (int i = 2; i <= nLimit; i++) {
		if (pBuffer[i]) {
			for (int k = i + i; k <= nMax; k += i)
				pBuffer[k] = 0;
		}
	}

	int nCount = 0;
	for (int i = 2; i <= nMax; i++)
		if (pBuffer[i])
			nCount++;

	delete[] pBuffer;
	TRACE("3. This is from Sieve Function\n");
	return nCount;

}

UINT ThreadFunc(LPVOID lParam)
{
	THREAD* pThread = (THREAD*)lParam;
	int nMax = pThread->nMax;
	HWND hwnd = pThread->hwnd;
	int nCount = Sieve(nMax);
	//m_Edit2 = nCount;
	TRACE("4. This is from Thread function before PostMessage\n");
	::PostMessage(hwnd, WM_USER_PRIME_COUNT,0, (LPARAM)nCount);
	TRACE("5. This is from Thread function after PostMessage\n");
	return 0;
}

void CSieveThreadDlg::OnBnStart()
{
	// TODO: Add your control notification handler code here
	int nMax = GetDlgItemInt(IDC_EDIT1);
	if (nMax < 10)
	{
		AfxMessageBox(_T("Value should be greater than 10"));
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
		pEdit->SetFocus();

	}
	GetDlgItem(IDC_BUTTON1)->EnableWindow(0);
	SetDlgItemText(IDC_EDIT2, _T(""));

	THREAD* pThread = new THREAD();
	pThread->nMax = nMax;
	pThread->hwnd = m_hWnd;
	TRACE("1. This is from Primary Thread before AfxBeginThread\n");
	AfxBeginThread(ThreadFunc, pThread);
	TRACE("2. This is from Primary Thread after AfxBeginThread\n");

}

LRESULT CSieveThreadDlg::OnPrimeCount(WPARAM wp, LPARAM lp)
{
	int nCount = (int)lp;
	m_Result = nCount;
	UpdateData(0);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(1);
	return 0L;
}