// CScan.cpp : implementation file
//

#include "pch.h"
#include "MFCAssignment3.h"
#include "CScan.h"
#include "afxdialogex.h"


// CScan dialog

IMPLEMENT_DYNAMIC(CScan, CDialog)

CScan::CScan(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG3, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CScan::~CScan()
{
}

void CScan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_ScanPatID);
	DDX_Control(pDX, IDC_STATIC2, m_ScanPatName);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}

void CScan::SetSearchPath(const CString& strPath)
{
		// TODO: Add your implementation code here.
		m_SearchPath = strPath;

}


BEGIN_MESSAGE_MAP(CScan, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CScan::OnBnClickedButton1)
END_MESSAGE_MAP()


// CScan message handlers

bool EnumerateFolders(/*CString strFile,*/ LPVOID param)
{
	CScan* pview = (CScan*)param;
	int nIndex = 1;
	//WIN32_FIND_DATA file;
	//CString csStrFoundFilePath;
	//CString csStrFilePath;
	CString csStrTheNameOfTheFile;
	CString csExt;
	//CString csStrPathToSearch = strFile;
	//HANDLE hFile = FindFirstFile((csStrPathToSearch + "\\*.*"), &file);
	//Sleep(500);
	try
	{
		// Check for cancel request.
		if (pview->m_bCancelOperation)
		{
			return false;
		}

		//CTime t = CTime::GetCurrentTime();
		//CString folderName = _T("F:\\");//t.Format("%H_%M_%S");
		//CMyPage1* page1;

		//CString folderName = page1->GetDlgItem(IDC_EDIT1);// Format("%H_%M_%S");


		CString folderName = pview->DesFile+ _T("\\") + pview->m_PatID1;


		if (FALSE == CreateDirectory(folderName, 0))
		{
			return false;
		}

		csExt.Format(_T("%s"), L".bmp");
		pview->m_ImageFile1 = pview->m_ImageFile1  +_T("\\") + pview->m_BodyPartCombo1 + csExt;
		int temp = _ttoi(pview->m_NumberOfImage1);
		pview->m_Progress.SetRange(nIndex, temp);

		do
		{
			// Check for cancel request.
			if (pview->m_bCancelOperation)
			{
				return false;
			}

			csExt.Format(_T("%s%d%s"),L"\\",nIndex, L".bmp");

			csStrTheNameOfTheFile = pview->DesFile +_T("\\") + pview->m_PatID1 + csExt;

			//csStrTheNameOfTheFile = file.cFileName;

			//if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			//{
			//	if ((csStrTheNameOfTheFile != L".") && (csStrTheNameOfTheFile != L".."))
			//	{
			//		//pview->m_Search.AddString(csStrTheNameOfTheFile);
			//		//str = csStrTheNameOfTheFile;
			//		EnumerateFolders(csStrPathToSearch + L"\\" + csStrTheNameOfTheFile, param);
			//	}
			//	CString csNewFileName;
			//	csNewFileName.Format(_T("%s%d%s"), L"F:\\Work\\Training Quest 2\\FileSearch_Cancel_Modal\\SearchFile\\", pview->nIndex, L".bmp");
			//	if (FALSE == CopyFile(L"C:\\RefImage\\Leg.bmp", csNewFileName, TRUE))
			//	{

			//	}


			//}

			CopyFile(pview->m_ImageFile1, csStrTheNameOfTheFile, TRUE);
			Sleep(100);
			pview->m_Progress.SetPos(nIndex);

			//WPARAM wParam = pview->nIndex;
			//PostMessage(pview->m_hWnd, MSG_ON_PROGRESS, wParam, 0);
			//::PostMessage(m_hWnd, WM_USER_THREAD_FINISHED, wParam, 0);

			nIndex++;
		} while (nIndex <= temp);
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
		CScan* pDlgPtr = reinterpret_cast<CScan*>(lParam_i);
		if (0 == pDlgPtr)
		{
			return FALSE;
		}
		EnumerateFolders(/*pDlgPtr->m_SearchPath, */ lParam_i);
	}
	catch (...)
	{
		return FALSE;
	}

	return 1;
}

BOOL CScan::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	LPVOID lParam = reinterpret_cast<LPVOID>(this);
	DWORD dwThreadID = 0;
	m_hThreadHandle = ::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SearchThreadProc, lParam, 0, &dwThreadID);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CScan::GetDetails(CString& m_PatName, CString& m_PatID, CString& m_BodyPartCombo, CString& m_NumberOfImage, CString& m_ImageFile, CString& m_DesFile)
{
	m_PatName1 = m_PatName;
	m_PatID1 = m_PatID;
	m_BodyPartCombo1 = m_BodyPartCombo;
	m_NumberOfImage1 = m_NumberOfImage;
	m_ImageFile1 = m_ImageFile;
	DesFile = m_DesFile;

}


//Abort Button
void CScan::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	m_bCancelOperation = true;
}
