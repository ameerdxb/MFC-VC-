#pragma once
#include"Header.h"

// CPatient command target

class CPatient : public CObject
{
public:
	CPatient();
	DECLARE_SERIAL(CPatient);
	virtual ~CPatient();
	virtual void Serialize(CArchive& ar);
	CPatient& operator=(PATIENT&);
	void ConvertToStruct(PATIENT&);
private:
	CString m_Id;
	CString m_Name;
	CString m_Gender;
	CString m_Date;
	CString m_Age;
	CString m_Height;
	CString m_Weight;
	CString m_Comments;
	CString m_BodyPart;
	CString m_Images;
	CString m_Operator;
};
