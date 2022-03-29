#include "pch.h"
#include "PatientData.h"
#include "CScanDialog.h"
#include "afxdialogex.h"
#include "Header.h"
#include <string>

IMPLEMENT_DYNAMIC(CScanDialog, CDialogEx)

CScanDialog::CScanDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, m_PatientName(_T(""))
	, m_PatientID(_T(""))
	, m_hThreadHandle(0)
	, m_bCancelOperation(false)
{

}

CScanDialog::~CScanDialog()
{
}

void CScanDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PATIENTID, m_PatientName);
	DDX_Text(pDX, IDC_PATIENTNAME, m_PatientName);
	DDX_Text(pDX, IDC_PATIENTID, m_PatientID);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}

BEGIN_MESSAGE_MAP(CScanDialog, CDialogEx)
	ON_BN_CLICKED(IDABORT, &CScanDialog::OnBnClickedAbort)
	ON_MESSAGE(ON_MSG_PROGRESS, &CScanDialog::OnProgress)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CScanDialog::OnNMCustomdrawProgress1)
	ON_BN_CLICKED(IDC_ABORT, &CScanDialog::OnBnClickedAbort)
END_MESSAGE_MAP()


// CScanDialog message handlers

void CScanDialog::SetData(CString PatientName, CString PatientID, CString strFile, CString BodyPart
	, CString NumberofImages)
{
	m_PatientName = PatientName;
	m_PatientID = PatientID;
	m_strFile = strFile;
	m_BodyPart = BodyPart;
	m_NumberOfImages = NumberofImages;
}


DWORD CScanDialog::OpenImageFile()
{
	if (m_bCancelOperation)
	{
		return false;
	}
	const CString PATH = _T("REFERENCE_IMAGE_PATH");
	const CString PATH_SEPERATOR = _T(":");
	const CString PATH_VALUE_SEPERATOR = _T(",");
	const CString PATH_LINE_END = _T(";");

	CString SearchKey1;
	SearchKey1.Format(_T("%s%s"), PATH, PATH_SEPERATOR);
	MessageBox(SearchKey1);

	int nFound1 = m_strFile.Find(SearchKey1.operator LPCTSTR(), 0);

	if (-1 == nFound1)
	{
		AfxMessageBox(_T("Not Found"));
	}
	int  nStart1 = nFound1 + SearchKey1.GetLength();

	nFound1 = m_strFile.Find(PATH_LINE_END, nStart1);

	if (-1 == nFound1)
	{
		AfxMessageBox(_T("Not Found"));
	}

	int nEnd1 = nFound1;

	CString csBodyParts1(m_strFile.Mid(nStart1, nEnd1 - nStart1));

	AfxMessageBox(csBodyParts1);
	StoreImageFile(csBodyParts1);
	return true;
}


DWORD CScanDialog::StoreImageFile(CString File)
{
	const CString PATH = _T("STORE_IMAGE_PATH");
	const CString PATH_SEPERATOR = _T(":");
	const CString PATH_VALUE_SEPERATOR = _T(",");
	const CString PATH_LINE_END = _T(";");

	CString SearchKey1;
	SearchKey1.Format(_T("%s%s"), PATH, PATH_SEPERATOR);
	MessageBox(SearchKey1);

	int nFound1 = m_strFile.Find(SearchKey1.operator LPCTSTR(), 0);

	if (-1 == nFound1)
	{
		AfxMessageBox(_T("Not Found"));
	}
	int  nStart1 = nFound1 + SearchKey1.GetLength();

	nFound1 = m_strFile.Find(PATH_LINE_END, nStart1);

	if (-1 == nFound1)
	{
		AfxMessageBox(_T("Not Found"));
	}

	int nEnd1 = nFound1;

	CString csBodyParts1(m_strFile.Mid(nStart1, nEnd1 - nStart1));

	if (CreateDirectory(csBodyParts1, NULL))
	{
		AfxMessageBox(csBodyParts1);
	}

	if (!CreateDirectory(csBodyParts1 + "\\" + m_PatientID, NULL))
	{
		AfxMessageBox(csBodyParts1 + "\\" + m_PatientID);
	}
	try
	{
		CFile oFile;
		CString str;
		int nCount = 1;
		CString str2 = _T(".bmp");
		int nNumberOfImages = _ttoi(m_NumberOfImages);
		str.Format(_T("%s%s%s%s"), File, "\\", m_BodyPart, str2);
		for (int i = 0; i < nNumberOfImages; i++)
		{
			if (m_bCancelOperation)
			{
				return false;
			}
			CString str1;
			str1.Format(_T("%s%s%s%s%s%d%s"), csBodyParts1, "\\", m_PatientID, "\\", m_BodyPart, nCount, str2);
			WPARAM param = nCount;
			PostMessage(ON_MSG_PROGRESS, param, 0);
			nCount++;
			if (!CopyFile(str, str1, TRUE))
			{
				AfxMessageBox(_T("Not Copied"));
			}
			Sleep(100);
		}
	}
	catch (...)
	{
		return false;
	}
	return true;
}

DWORD ThreadStart(LPVOID lParam_i)
{
	try
	{
		CScanDialog* pDlgPtr = reinterpret_cast<CScanDialog*>(lParam_i);
		if (0 == pDlgPtr)
		{
			return FALSE;
		}
		pDlgPtr->OpenImageFile();
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CScanDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	LPVOID lParam = reinterpret_cast<LPVOID>(this);
	DWORD dwThreadID = 0;
	m_hThreadHandle = ::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ThreadStart, lParam, 0, &dwThreadID);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}



LRESULT CScanDialog::OnProgress(WPARAM wParam_i, LPARAM lParam_i)
{
	UNREFERENCED_PARAMETER(lParam_i);
	int nCount = wParam_i;
	m_Progress.SetRange(0, nCount);
	for (int i = 0; i < nCount; i++)
	{
		m_Progress.SetPos(nCount);
	}
	return 0L;
}

void CScanDialog::OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CScanDialog::OnBnClickedAbort()
{
	// TODO: Add your control notification handler code here
	m_bCancelOperation = true;

	::WaitForSingleObject(m_hThreadHandle, INFINITE);
	::CloseHandle(m_hThreadHandle);
	m_hThreadHandle = NULL;
	CScanDialog::OnCancel();

}
