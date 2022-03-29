#include "pch.h"
#include "CSharedMemory.h"
#include "Header.h"
#include <cstdlib>


const CString SEP = _T("$");
HANDLE m_hEventHandle;

CSharedMemory::CSharedMemory()
{
	m_hEventHandle = CreateEvent(NULL, TRUE, FALSE, _T("MyEvent"));
}


CSharedMemory::~CSharedMemory()
{
}

UINT WriteProc(LPVOID lParam)
{
	CSharedMemory* pShared = (CSharedMemory*)lParam;
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		if (WM_USER_WRITE_TO_SHARED_MEMORY == msg.message)
		{
			STUDENT* std = (STUDENT*)msg.wParam;
			CString csBuffer;
			pShared->CreateBuffer(*std, csBuffer);
			AfxMessageBox(csBuffer);
			pShared->PerformWrite(csBuffer);
			SetEvent(m_hEventHandle);
		}
	}
	return 0;
}

UINT ReadProc(LPVOID lParam)
{
	CSharedMemory* pShared = (CSharedMemory*)lParam;
	while (1)
	{
		WaitForSingleObject(m_hEventHandle, INFINITE);
		pShared->PerformRead();
		ResetEvent(m_hEventHandle);
	}
	return 0;
}

void CSharedMemory::ThreadStart(CString csThreadType)
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


void CSharedMemory::OnNewNotification(WPARAM wp)
{
	// TODO: Add your implementation code here.
	PostThreadMessage(m_dwWriteThreadId, WM_USER_WRITE_TO_SHARED_MEMORY, wp, 0);
}


void CSharedMemory::CreateBuffer(STUDENT& std, CString& str)
{
	// TODO: Add your implementation code here.
	str = std.m_Name + SEP + std.m_Id + SEP + std.m_Gender + SEP + std.m_DateReg + SEP + std.m_Age + SEP + std.MARK.m_Mark1 + SEP + std.MARK.m_Mark2 + SEP + std.MARK.m_Mark2 + SEP;
}


void CSharedMemory::PerformWrite(CString csBuffer)
{
	// TODO: Add your implementation code here.
	CreateSharedMemory();
	int nBufferLength;
	nBufferLength = csBuffer.GetLength();
	wchar_t* pszBuffer = new wchar_t[nBufferLength + 1];
	wcscpy_s(pszBuffer, wcslen(pszBuffer) * sizeof(wchar_t),csBuffer);
	CopyMemory(m_pszSharedValues, pszBuffer, wcslen(pszBuffer) * sizeof(wchar_t));
	m_pszSharedValues = csBuffer.GetBuffer(csBuffer.GetLength());

}


void CSharedMemory::CreateSharedMemory()
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


void CSharedMemory::PerformRead()
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


void CSharedMemory::ParseSharedData(CString csBuffer)
{
	// TODO: Add your implementation code here.

	STUDENT stPatInfo;
	int nFound = 0;
	int nStart = 0;
	int ncount;

	nFound = csBuffer.Find(_T("$"), nStart);
	ncount = nFound - nStart;
	stPatInfo.m_Id = csBuffer.Mid(nStart, ncount);
	nStart = nFound + 1;

	nFound = csBuffer.Find(_T("$"), nStart);
	ncount = nFound - nStart;
	stPatInfo.m_Name = csBuffer.Mid(nStart, ncount);
	nStart = nFound + 1;
	//AfxMessageBox(stPatInfo.id);
	//AfxMessageBox(stPatInfo.nam);
	p2->myMap[stPatInfo.m_Id] = stPatInfo;
	p2->InsertToTree();
}


void CSharedMemory::GetBrowserPointer(CMyPage2& page2)
{
	// TODO: Add your implementation code here.
	p2 = &page2;
}
