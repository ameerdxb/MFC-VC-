#pragma once
#include<afxwin.h>

struct SERIESINFO
{
	CString m_BodyPart;
	CString m_NumberofImages;
	CString m_OperatorsName;
};
struct STUDYINFO
{
	CString m_Height;
	CString m_Weight;
	CString m_StudyComments;
	SERIESINFO  series;
};
typedef struct PATIENTINFO
{
	CString m_PatientID;
	CString m_PatientName;
	CString m_Gender;
	CString m_Date;
	CString m_Age;
	STUDYINFO study;
}PATIENT;

#define WM_USER_SECONDPAGE   WM_USER + 0x0400
#define ON_MSG_PROGRESS  WM_USER + 0x0401
#define WM_USER_WRITE_TO_SHARED_MEMORY WM_USER + 0x0411
#define WM_USER_MSG    WM_USER + 0x0410
#define MSG_ON_PATIENT_REG   WM_USER + 0x0412