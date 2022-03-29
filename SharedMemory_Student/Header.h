#pragma once

#include<afxwin.h>
struct mark
{
	CString m_Mark1;
	CString m_Mark2;
	CString m_Mark3;
};
typedef struct tagStudent
{
	CString m_Name;
	CString m_Id;
	CString m_Age;
	CString m_Gender;
	CString m_DateReg;
	mark MARK;
}STUDENT;

#define WM_USER_SECONDPAGE WM_USER + 0x0400
#define WM_USER_WRITE_TO_SHARED_MEMORY WM_USER + 0x0401