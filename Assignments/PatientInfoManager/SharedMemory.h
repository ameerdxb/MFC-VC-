#pragma once
#include"Page2.h"
#include"Header.h"
class CSharedMemory
{
public:
	CSharedMemory(void);
	~CSharedMemory(void);

	wchar_t* m_pszSharedValues;
	HANDLE m_hWriteSharedMemory;
	HANDLE m_hReadSharedMemory;

	void ThreadStart(CString csThreadType);
	void OnNewNotification(LPARAM);
	void CreateBuffer(PATIENT&, CString&);
	void PerformWrite(CString csBuffer);
	void CreateSharedmemory();
	void PerformRead(void);
	void ParseSharedData(CString);


	CPage2* m_page2;
	void GetBrowserPointer(CPage2& pag2);

private:
	DWORD m_dwWriteThreadId;
	DWORD m_dwReadThreadId;
};

