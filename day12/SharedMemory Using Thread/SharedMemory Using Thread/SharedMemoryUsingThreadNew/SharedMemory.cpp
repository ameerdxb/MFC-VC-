#include "StdAfx.h"
#include "SharedMemory.h"

HANDLE m_hEventHandle;
const CString SEP = _T("$");
CSharedMemory::CSharedMemory(void)
{
	m_hEventHandle = ::CreateEvent(NULL,TRUE,FALSE,_T("WriteEvent"));
}

CSharedMemory::~CSharedMemory(void)
{
}


UINT __cdecl WriteProc(LPVOID lParam )
{
	TRACE("Inside WriteProc");
	MSG stThreadMessage;
	CSharedMemory* pshared = (CSharedMemory*)lParam;//////d nt
	while(::GetMessage(&stThreadMessage,0,0,0))
	{
		if(WM_USER_WRITE_TO_SHARED_MEMORY == stThreadMessage.message)//
		{
			PERSON* per = (PERSON*)stThreadMessage.lParam;
			CString csBuffer;
			pshared->CreateBuffer(*per,csBuffer);
			AfxMessageBox(csBuffer);

			pshared->PerformWrite(csBuffer);
			SetEvent(m_hEventHandle);
		}
	}
  return 0;
}
UINT __cdecl ReadProc(LPVOID lParam )
{
   CSharedMemory* pshared = (CSharedMemory*)lParam;
   while(1)
   {
	   WaitForSingleObject(m_hEventHandle,INFINITE);
	   pshared->PerformRead();

	   ResetEvent(m_hEventHandle);
   }
  return 0;
}


void CSharedMemory::ThreadStart(CString csThreadType)
{
  CWinThread* pThread;
  if(_T("W") == csThreadType)
  {
	  pThread = AfxBeginThread(WriteProc,this);
	  m_dwWriteThreadId = pThread->m_nThreadID;

  }
  else
  {
   pThread = AfxBeginThread(ReadProc,this);
	  m_dwReadThreadId = pThread->m_nThreadID;
  }
}

void CSharedMemory::OnNewNotification(LPARAM lp)
{
	::PostThreadMessage(m_dwWriteThreadId,WM_USER_WRITE_TO_SHARED_MEMORY,0,lp);
}

void CSharedMemory::CreateBuffer(PERSON& per,CString& str)
{
	str = per.id + SEP + per.nam + SEP;
}

void CSharedMemory::CreateSharedmemory()
{
	try
	{
		m_hWriteSharedMemory = ::CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE|SEC_COMMIT,0,256*1024,_T("csname"));
		if(!m_hWriteSharedMemory)
		{
			AfxMessageBox(_T("failed in creating filemapping"));
		}
		m_pszSharedValues = (wchar_t*)::MapViewOfFile(m_hWriteSharedMemory,FILE_MAP_ALL_ACCESS,0,0,256*1024);
	     if(!m_pszSharedValues)
		{
			AfxMessageBox(_T("failed i n offfile"));
		}
		 memset(m_pszSharedValues,0,256*1024);
	} 
	catch(...)
	{
		AfxMessageBox(_T("Failed"));
	}
}

void CSharedMemory::PerformWrite(CString csBuffer)
{
	CreateSharedmemory();
	int nBufferLength;
	nBufferLength = csBuffer.GetLength();
	wchar_t* pszBuffer= new wchar_t[nBufferLength + 1];
	wcscpy(pszBuffer,csBuffer);
	CopyMemory(m_pszSharedValues,pszBuffer,wcslen(pszBuffer)*sizeof(wchar_t));

	m_pszSharedValues = csBuffer.GetBuffer(csBuffer.GetLength());


}



void CSharedMemory::PerformRead(void)
{
	try
	{
		m_hReadSharedMemory = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,_T("csname"));
        if(!m_hReadSharedMemory)
		{
			AfxMessageBox(_T("failed"));
		}
		wchar_t* pBuffer = (wchar_t*)::MapViewOfFile(m_hReadSharedMemory,FILE_MAP_ALL_ACCESS,0,0,256*1024);
         if(!pBuffer)
		{
			AfxMessageBox(_T("failed for map offline"));
		}


		 int  nSharedDataSize = wcslen(pBuffer)*sizeof(wchar_t);
	wchar_t* pszBuffer= new wchar_t[nSharedDataSize];
	CopyMemory(pszBuffer,pBuffer,nSharedDataSize);
	CString csBuffer(pszBuffer);
	ParseSharedData(csBuffer);
	delete[] pszBuffer;
	pszBuffer = 0;

	}
	catch(...)
	{
      AfxMessageBox(_T("Failed"));
	}
}

void CSharedMemory::ParseSharedData(CString csBuffer)
{
	PERSON stPatInfo;
	int nFound = 0;
	int nStart = 0;
	int ncount;
	
	nFound = csBuffer.Find(_T("$"),nStart);
	ncount = nFound - nStart;
	stPatInfo.id = csBuffer.Mid(nStart,ncount);
	nStart = nFound + 1;
      
	nFound = csBuffer.Find(_T("$"),nStart);
	ncount = nFound - nStart;
	stPatInfo.nam = csBuffer.Mid(nStart,ncount);
	nStart = nFound + 1;
	AfxMessageBox(stPatInfo.id);
	AfxMessageBox(stPatInfo.nam);
	m_page2->myMap[stPatInfo.id] = stPatInfo;
	m_page2->insertToTree();




}

void CSharedMemory::GetBrowserPointer(CPage2& pag2)
{
	TRACE("GetBrowserPointer");
	m_page2 = &pag2;
}
