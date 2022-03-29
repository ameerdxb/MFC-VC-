#pragma once
#include "Header.h"

// CStudent command target

class CStudent : public CObject
{
public:
	DECLARE_SERIAL(CStudent)
	CStudent();
	virtual ~CStudent();
	virtual void Serialize(CArchive& ar);
	CStudent& operator = (STUDENT&);
	void ConvertToStruct(STUDENT&);
private:
	CString m_Name;
	CString m_Gender;
	//CString m_CurTime;
	CString m_Id;
	CString m_Date;
	CString m_Age;
	CString m_Marks;
	CString m_Mark1;
	CString m_Mark2;
	CString m_Mark3;
};


