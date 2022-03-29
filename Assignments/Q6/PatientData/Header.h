#pragma once
#include <afxwin.h>
struct SERIES_INFO_t
{
	CString m_BodyPart;
	CString m_Images;
	CString m_Operator;;
};
struct STUDY_INFO_t
{
	CString m_Height;
	CString m_Weight;
	CString m_Comments;
	SERIES_INFO_t SERIES;
};
typedef struct PATIENT_INFO_t
{
	CString m_Id;
	CString m_Name;
	CString m_Gender;
	CString m_Date;
	CString m_Age;
	STUDY_INFO_t STUDY;
}PATIENT;