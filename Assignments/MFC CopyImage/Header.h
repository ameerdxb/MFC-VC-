#pragma once

#include<afxwin.h>

//Structure SERIES_INFO_t
typedef struct tagSeries
{
	CString m_sBodyPart;
	CString m_sNumberofImages;
	CString m_sOperatorsName;
}SERIES_INFO_t;

//Structure STUDY_INFO_t
typedef struct tagStudy
{
	CString m_sHeight;
	CString m_sWeight;
	CString m_sStudyComments;
	SERIES_INFO_t oSeries;
}STUDY_INFO_t;

//Structure PATIENT_INFO_t
typedef struct tagPatientInfo
{
	CString m_sPatientName;
	CString m_sPatientID;
	CString m_PatientDateofReg;
	CString m_sGender;
	CString m_sAge;
	STUDY_INFO_t oStudy;
}PATIENT_INFO_t;


#define WM_USER_SECONDPAGE    WM_USER + 0x0400
#define WM_USER_WRITE_TO_SHARED_MEMORY WM_USER + 0x0401
#define WM_USER_MSG    WM_USER + 0x0410