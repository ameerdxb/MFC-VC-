#pragma once
#include <afx.h>
#include"Header.h"
class CPatient : public CObject
{
public:
	//Macro no semicolumn
	DECLARE_SERIAL(CPatient)

	//No arg constructor
	CPatient();
	virtual ~CPatient();

	//class view->Virtual fn->serialize
	virtual void Serialize(CArchive& ar);

	//Assi op overloading always ref, = , parameter struct
	CPatient& operator = (PATIENT&);
	void ConvertToStruct(PATIENT&);
private:
	CString m_Name = NULL;
	CString m_Gender = NULL;
	CString m_ID = NULL;
	CString m_Date = NULL;
	CString m_Age = NULL;
	CString m_Height = NULL;
	CString m_Weight = NULL;
	CString m_StudyComments = NULL;
	CString m_BodyPart = NULL;
	CString m_NumberofImages = NULL;
	CString m_OperatorsName = NULL;
};

