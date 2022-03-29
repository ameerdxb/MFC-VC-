#include "pch.h"
#include "CSharedMemory.h"
#include "Header.h"

const CString SEP = _T("$");

CSharedMemory::CSharedMemory(void)
{
	m_hEventHandle = ::CreateEvent(NULL, TRUE, FALSE, _T("MyEvent"));
}
CSharedMemory::~CSharedMemory(void)
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
			SetEvent(pShared->m_hEventHandle);
		}
	}
	return 0;
}

UINT ReadProc(LPVOID lParam)
{
	CSharedMemory* pShared = (CSharedMemory*)lParam;
	WaitForSingleObject(pShared->m_hEventHandle, INFINITE);

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
	str = std.m_Name + SEP + std.m_Id + SEP + std.m_Gender + SEP + std.m_DateReg + SEP + std.m_Age + SEP + std.MARK.m_Mark1 + SEP + std.MARK.m_Mark2 + SEP + std.MARK.m_Mark3 + SEP;
}


void CSharedMemory::PerformWrite(CString csBuffer)
{
	// TODO: Add your implementation code here.
	CreateSharedMemory();
	int nBufferLength;
	nBufferLength = csBuffer.GetLength();
	wchar_t* pszBuffer = new wchar_t[nBufferLength + 1];
	wcscpy(pszBuffer, csBuffer);

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
