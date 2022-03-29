#pragma once
#include <afxwin.h>

typedef struct tagStudent
{
	CString m_Name;
	CString m_Gender;
	//int m_Id;
	CString m_Id;
	CString m_Date;
	CString m_Age;
	CString m_Marks = _T("Marks");
	CString m_Mark1;
	CString m_Mark2;
	CString m_Mark3;
}STUDENT;

#define WM_USER_SECONDPAGE	WM_USER	+ 0x0400