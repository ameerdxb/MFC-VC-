#include "pch.h"

#include "Patient.h"
IMPLEMENT_SERIAL(CPatient, CObject, 1)

// CStudent

CPatient::CPatient()
{
}

CPatient::~CPatient()
{
}


// CStudent member functions


void CPatient::Serialize(CArchive& ar)
{
	//write to file
	if (ar.IsStoring())
	{	// storing code
		ar << m_ID << m_Name << m_Gender << m_Date << m_Age << m_Height <<
			m_Weight << m_StudyComments << m_BodyPart << m_NumberofImages << m_OperatorsName;
	}
	else
		//read from file
	{	// loading code
		ar >> m_ID >> m_Name >> m_Gender >> m_Date >> m_Age >> m_Height >>
			m_Weight >> m_StudyComments >> m_BodyPart >> m_NumberofImages >> m_OperatorsName;
	}
}

CPatient& CPatient::operator=(PATIENT& s)
{
	// TODO: insert return statement here
	m_Name = s.m_PatientName;
	m_Gender = s.m_Gender;
	m_ID = s.m_PatientID;
	m_Date = s.m_Date;
	m_Age = s.m_Age;
	m_Height = s.study.m_Height;
	m_Weight = s.study.m_Weight;
	m_StudyComments = s.study.m_StudyComments;
	m_BodyPart = s.study.series.m_BodyPart;
	m_NumberofImages = s.study.series.m_NumberofImages;
	m_OperatorsName = s.study.series.m_OperatorsName;
	return *this;
}

void CPatient::ConvertToStruct(PATIENT& s)
{
	//Values stored in mem var to struct mems
	s.m_PatientID = m_ID;
	s.m_PatientName = m_Name;
	s.m_Gender = m_Gender;
	s.m_Date = m_Date;
	s.m_Age = m_Age;
	s.study.m_Height = m_Height;
	s.study.m_Weight = m_Weight;
	s.study.m_StudyComments = m_StudyComments;
	s.study.series.m_BodyPart = m_BodyPart;
	s.study.series.m_NumberofImages = m_NumberofImages;
	s.study.series.m_OperatorsName = m_OperatorsName;
}
