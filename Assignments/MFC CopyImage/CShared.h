#pragma once
#include "Header.h"
#include "CMyPage2.h"

class CShared
{
public:
	CShared();
	~CShared();

	DWORD m_dwWriteThreadId;
	DWORD m_dwReadThreadId;

	HANDLE m_hWriteSharedMemory;
	HANDLE m_hReadSharedMemory;

	wchar_t* m_pszSharedValues;
	void ThreadStart(CString csThreadType);

	void CreateBuffer(PATIENT_INFO_t& std, CString& str);

	void PerformWrite(CString csBuffer);
	void CreateSharedMemory();
	void PerformRead();

	void ParseSharedData(CString csBuffer);

	CMyPage2* p2;
	void GetBrowserPointer(CMyPage2& page2);
	void OnNewNotification(LPARAM);
};

