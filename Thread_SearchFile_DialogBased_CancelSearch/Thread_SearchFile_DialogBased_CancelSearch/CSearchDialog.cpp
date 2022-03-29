// CSearchDialog.cpp : implementation file
//

#include "pch.h"
#include "Thread_SearchFile_DialogBased_CancelSearch.h"
#include "CSearchDialog.h"
#include "afxdialogex.h"


// CSearchDialog dialog
CString str;
IMPLEMENT_DYNAMIC(CSearchDialog, CDialog)

CSearchDialog::CSearchDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent), m_bCancelOperation(false),
		m_hThreadHandle(0)
{
	 nIndex = 0;
}

CSearchDialog::~CSearchDialog()
{
}

void CSearchDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_Search);
	DDX_Control(pDX, IDC_SEARCHFILECOUNT, m_FileCount);
}


BEGIN_MESSAGE_MAP(CSearchDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CSearchDialog::OnBnClickedButton1)
	ON_MESSAGE(MSG_ON_PROGRESS, &CSearchDialog::OnMsgSearchProgress)
END_MESSAGE_MAP()


// CSearchDialog message handlers


void CSearchDialog::SetSearchPath(const CString& strPath)
{
	// TODO: Add your implementation code here.
	m_SearchPath = strPath;
}


void CSearchDialog::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	m_bCancelOperation = true;
/*	if (WAIT_OBJECT_0 == WaitForSingleObject(m_hThreadHandle, INFINITE))
	{
		CDialog::OnCancel();
	}*/

	::WaitForSingleObject(m_hThreadHandle, INFINITE);
	::CloseHandle(m_hThreadHandle);
	m_hThreadHandle = NULL;
	CDialog::OnCancel();

}

bool EnumerateFolders(CString strFile, LPVOID param)
{
	CSearchDialog *pview = (CSearchDialog *)param;
	WIN32_FIND_DATA file;
	CString csStrFoundFilePath;
	CString csStrFilePath;
	CString csStrTheNameOfTheFile;
	CString csStrPathToSearch = strFile;
	HANDLE hFile = FindFirstFile((csStrPathToSearch + "\\*.*"), &file);
	Sleep(500);
	try
	{
		// Check for cancel request.
		if (pview->m_bCancelOperation)
		{
			return false;
		}

			CTime t = CTime::GetCurrentTime();
			CString folderName = t.Format("%H_%M_%S");
			if (FALSE == CreateDirectory(folderName, 0))
			{

				return false;
			}

		do
		{
			// Check for cancel request.
			if (pview->m_bCancelOperation)
			{
				return false;
			}

			csStrTheNameOfTheFile = file.cFileName;

			if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if ((csStrTheNameOfTheFile != L".") && (csStrTheNameOfTheFile != L".."))
				{
					pview->m_Search.AddString(csStrTheNameOfTheFile);
					str = csStrTheNameOfTheFile;
					EnumerateFolders(csStrPathToSearch + L"\\" + csStrTheNameOfTheFile, param);
				}
				CString csNewFileName;
				csNewFileName.Format(_T("%s%d%s"), L"E:\\Quest training\\VC++\\SearchFile\\", pview->nIndex, L".bmp");
				if (FALSE == CopyFile(L"E:\\Quest training\\VC++\\RefImage\\Leg.bmp", csNewFileName, TRUE))
				{

				}


			}
			WPARAM wParam = pview->nIndex;
			PostMessage(pview->m_hWnd, MSG_ON_PROGRESS, wParam, 0);
			//::PostMessage(m_hWnd, WM_USER_THREAD_FINISHED, wParam, 0);

			pview->nIndex++;
		} while (FindNextFile(hFile, &file));
	}
	catch (...)
	{
		return false;
	}
	return true;
}

DWORD SearchThreadProc(LPVOID lParam_i)
{
	try
	{
		CSearchDialog* pDlgPtr = reinterpret_cast<CSearchDialog*>(lParam_i);
		if (0 == pDlgPtr)
		{
			return FALSE;
		}
		EnumerateFolders(pDlgPtr->m_SearchPath, lParam_i);
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}
BOOL CSearchDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	LPVOID lParam = reinterpret_cast<LPVOID>(this);
	DWORD dwThreadID = 0;
	m_hThreadHandle = ::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SearchThreadProc, lParam, 0, &dwThreadID);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}




LRESULT CSearchDialog::OnMsgSearchProgress(WPARAM wParam_i, LPARAM lParam_i)
{
	UNREFERENCED_PARAMETER(lParam_i);
	int nPos = wParam_i;
	CString s1;
	s1.Format(L"%d%s", nPos,L" files found");
	m_FileCount.SetWindowTextW(s1);
	return 0;
}
