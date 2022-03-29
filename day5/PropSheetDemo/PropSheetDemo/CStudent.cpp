// CStudent.cpp : implementation file
//

#include "pch.h"
#include "PropSheetDemo.h"
#include "CStudent.h"
#include "Header.h"

IMPLEMENT_SERIAL(CStudent,CObject,1)
// CStudent

CStudent::CStudent()
{
}

CStudent::~CStudent()
{
}


// CStudent member functions


void CStudent::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_Name;
		ar << m_Gender;
			//<< m_Id << m_Date << m_Age << m_Marks << m_Mark1 << m_Mark2 << m_Mark3;	
	}
	else
	{	// loading code
		ar >> m_Name;
		ar >> m_Gender;
			//>> m_Id >> m_Date >> m_Age >> m_Marks >> m_Mark1 >> m_Mark2 >> m_Mark3;
	}
}

CStudent& CStudent ::operator=(STUDENT& s)
{
	m_Name = s.m_Name;
	m_Gender = s.m_Gender;
	m_Id = s.m_Id;
	m_Date = s.m_Date;
	m_Age = s.m_Age;
	m_Marks = s.m_Marks;
	m_Mark1 = s.m_Mark1;
	m_Mark2 = s.m_Mark2;
	m_Mark3 = s.m_Mark3;

	return *this;
}

void CStudent::ConvertToStruct(STUDENT& s)
{
	s.m_Name = m_Name;
	s.m_Gender = m_Gender;
	s.m_Id = m_Id;
	s.m_Date = m_Date;
	s.m_Age = m_Age;
	s.m_Marks = m_Marks;
	s.m_Mark1 = m_Mark1;
	s.m_Mark2 = m_Mark2;
	s.m_Mark3 = m_Mark3;
}