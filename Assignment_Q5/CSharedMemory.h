#pragma once
#include "Header.h"
class CSharedMemory
{
public:
	CSharedMemory();
	~CSharedMemory();

//private:
	DWORD m_dwWriteThreadId;
	DWORD m_dwReadThreadId;

	HANDLE m_hWriteSharedMemory;
	HANDLE m_hReadSharedMemory;
	HANDLE m_hEventHandle;
	wchar_t* m_pszSharedValues;
public:
	void ThreadStart(CString csThreadType);
	void OnNewNotification(WPARAM wp);
	void CreateBuffer(STUDENT& std, CString& str);

	void PerformWrite(CString csBuffer);
	void CreateSharedMemory();
};




