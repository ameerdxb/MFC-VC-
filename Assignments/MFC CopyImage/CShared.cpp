#include "pch.h"
#include "CShared.h"

const CString SEP = _T("$");
HANDLE m_hEventHandle;
CShared::CShared()
{
	m_hEventHandle = CreateEvent(NULL, TRUE, FALSE, _T("MyEvent"));
}

CShared::~CShared()
{
}

UINT WriteProc(LPVOID lParam)
{
	TRACE("Inside WriteProc");
	CShared* pShared = (CShared*)lParam;
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		if (WM_USER_WRITE_TO_SHARED_MEMORY == msg.message)
		{
			PATIENT_INFO_t* pat = (PATIENT_INFO_t*)msg.wParam;
			CString csBuffer;
			pShared->CreateBuffer(*pat, csBuffer);
			AfxMessageBox(csBuffer);
			pShared->PerformWrite(csBuffer);
			//SetEvent(pShared->m_hEventHandle);
			SetEvent(m_hEventHandle);
		}
	}
	return 0;
}

UINT ReadProc(LPVOID lParam)
{
	CShared* pShared = (CShared*)lParam;
	while (1)
	{
		//WaitForSingleObject(pShared->m_hEventHandle, INFINITE);
		WaitForSingleObject(m_hEventHandle, INFINITE);
		pShared->PerformRead();
		//ResetEvent(pShared->m_hEventHandle);
		ResetEvent(m_hEventHandle);
	}
	return 0;
}

void CShared::ThreadStart(CString csThreadType)
{
	// TODO: Add your implementation code here.
	CWinThread* pThread;
	if (_T("W") == csThreadType)
	{
		pThread = AfxBeginThread(WriteProc, this);
		m_dwWriteThreadId = pThread->m_nThreadID;
	}
	else
	{
		pThread = AfxBeginThread(ReadProc, this);
		m_dwReadThreadId = pThread->m_nThreadID;
	}
}

void CShared::CreateBuffer(PATIENT_INFO_t& pat, CString& str)
{
	str = pat.m_sPatientID + SEP + 
		pat.m_sPatientName + SEP + 
		pat.m_sGender + SEP + 
		pat.m_PatientDateofReg + SEP + 
		pat.m_sAge + SEP + 
		pat.oStudy.m_sHeight + SEP + 
		pat.oStudy.m_sWeight + SEP + 
		pat.oStudy.m_sStudyComments + SEP;
	pat.oStudy.oSeries.m_sBodyPart + SEP;
	pat.oStudy.oSeries.m_sNumberofImages + SEP;
	pat.oStudy.oSeries.m_sOperatorsName + SEP;
}

void CShared::PerformWrite(CString csBuffer)
{
	CreateSharedMemory();
	int nBufferLength;
	nBufferLength = csBuffer.GetLength();
	wchar_t* pszBuffer = new wchar_t[nBufferLength + 1];
	wcscpy_s(pszBuffer, wcslen(pszBuffer) * sizeof(wchar_t), csBuffer);
	CopyMemory(m_pszSharedValues, pszBuffer, wcslen(pszBuffer) * sizeof(wchar_t));
	m_pszSharedValues = csBuffer.GetBuffer(csBuffer.GetLength());

}

void CShared::CreateSharedMemory()
{
	// TODO: Add your implementation code here.
	try
	{
		m_hWriteSharedMemory = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE | SEC_COMMIT, 0, 256 * 1024, _T("csname"));
		if (!m_hWriteSharedMemory)
		{
			AfxMessageBox(_T("failed in creating filemapping"));
		}
		m_pszSharedValues = (wchar_t*)::MapViewOfFile(m_hWriteSharedMemory, FILE_MAP_ALL_ACCESS, 0, 0, 256 * 1024);
		if (!m_pszSharedValues)
		{
			AfxMessageBox(_T("failed i n offfile"));
		}
		memset(m_pszSharedValues, 0, 256 * 1024);
	}
	catch (...)
	{
		AfxMessageBox(_T("Failed"));
	}
}

void CShared::PerformRead()
{
	// TODO: Add your implementation code here.
	try
	{
		m_hReadSharedMemory = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, _T("csname"));
		if (!m_hReadSharedMemory)
		{
			AfxMessageBox(_T("failed"));
		}
		wchar_t* pBuffer = (wchar_t*)::MapViewOfFile(m_hReadSharedMemory, FILE_MAP_ALL_ACCESS, 0, 0, 256 * 1024);
		if (!pBuffer)
		{
			AfxMessageBox(_T("failed for map offline"));
		}


		int  nSharedDataSize = wcslen(pBuffer) * sizeof(wchar_t);
		wchar_t* pszBuffer = new wchar_t[nSharedDataSize];
		CopyMemory(pszBuffer, pBuffer, nSharedDataSize);
		CString csBuffer(pszBuffer);
		ParseSharedData(csBuffer);
		delete[] pszBuffer;
		pszBuffer = 0;

	}
	catch (...)
	{
		AfxMessageBox(_T("Failed"));
	}
}

void CShared::ParseSharedData(CString csBuffer)
{
	// TODO: Add your implementation code here.

	PATIENT_INFO_t stPatInfo;
	int nFound = 0;
	int nStart = 0;
	int ncount;

	nFound = csBuffer.Find(_T("$"), nStart);
	ncount = nFound - nStart;
	stPatInfo.m_sPatientID = csBuffer.Mid(nStart, ncount);
	nStart = nFound + 1;

	nFound = csBuffer.Find(_T("$"), nStart);
	ncount = nFound - nStart;
	stPatInfo.m_sPatientName = csBuffer.Mid(nStart, ncount);
	nStart = nFound + 1;
	//AfxMessageBox(stPatInfo.id);
	//AfxMessageBox(stPatInfo.nam);
	p2->myMap[stPatInfo.m_sPatientID] = stPatInfo;
	p2->InsertToTree();
}

void CShared::GetBrowserPointer(CMyPage2& page2)
{
	p2 = &page2;
}

void CShared::OnNewNotification(LPARAM lp)
{
	::PostThreadMessage(m_dwWriteThreadId, WM_USER_WRITE_TO_SHARED_MEMORY, 0, lp);
}