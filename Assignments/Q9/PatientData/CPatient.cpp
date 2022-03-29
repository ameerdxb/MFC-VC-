// CPatient.cpp : implementation file
//

#include "pch.h"
#include "PatientData.h"
#include "CPatient.h"

IMPLEMENT_SERIAL(CPatient, CObject, 1)
// CPatient

CPatient::CPatient()
{
}

CPatient::~CPatient()
{
}


// CPatient member functions


void CPatient::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_Id
			<< m_Name
			<< m_Gender
			<< m_Date
			<< m_Age
			<< m_Height
			<< m_Weight
			<< m_Comments
			<< m_BodyPart
			<< m_Images
			<< m_Operator;
	}
	else
	{	// loading code
		ar >> m_Id
			>> m_Name
			>> m_Gender
			>> m_Date
			>> m_Age
			>> m_Height
			>> m_Weight
			>> m_Comments
			>> m_BodyPart
			>> m_Images
			>> m_Operator;
	}
}

CPatient& CPatient::operator = (PATIENT& p)
{
	m_Id = p.m_Id;
	m_Name = p.m_Name;
	m_Gender = p.m_Gender;
	m_Date = p.m_Date;
	m_Age = p.m_Age;
	m_Height = p.STUDY.m_Height;
	m_Weight = p.STUDY.m_Weight;
	m_Comments = p.STUDY.m_Comments;
	m_BodyPart = p.STUDY.SERIES.m_BodyPart;
	m_Images = p.STUDY.SERIES.m_Images;
	m_Operator = p.STUDY.SERIES.m_Operator;
	return *this;
}
void CPatient::ConvertToStruct(PATIENT& p)
{
	p.m_Id = m_Id;
	p.m_Name = m_Name;
	p.m_Gender = m_Gender;
	p.m_Date = m_Date;
	p.m_Age = m_Age;
	p.STUDY.m_Height = m_Height;
	p.STUDY.m_Weight + m_Weight;
	p.STUDY.m_Comments = m_Comments;
	p.STUDY.SERIES.m_BodyPart = m_BodyPart;
	p.STUDY.SERIES.m_Images = m_Images;
	p.STUDY.SERIES.m_Operator = m_Operator;
}
