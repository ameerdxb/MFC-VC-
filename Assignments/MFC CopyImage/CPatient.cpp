// CPatient.cpp : implementation file
//

#include "pch.h"
#include "MFCAssignment3.h"
#include "CPatient.h"


// CPatient
IMPLEMENT_SERIAL(CPatient, CObject, 1)

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
		ar << m_sPatientID << m_sPatientName << m_sGender << m_PatientDateofReg << m_sAge << m_sHeight << m_sWeight
			<< m_sStudyComments << m_sBodyPart << m_sNumberofImages << m_sOperatorsName;
	}
	else
	{	// loading code
		ar >> m_sPatientID >> m_sPatientName >> m_sGender >> m_PatientDateofReg >> m_sAge >> m_sHeight >> m_sWeight
			>> m_sStudyComments >> m_sBodyPart >> m_sNumberofImages >> m_sOperatorsName;
	}
}

CPatient& CPatient::operator=(PATIENT_INFO_t& Pat)
{
	m_sPatientID = Pat.m_sPatientID;
	m_sPatientName = Pat.m_sPatientName;
	m_sGender = Pat.m_sGender;
	m_PatientDateofReg = Pat.m_PatientDateofReg;
	m_sAge = Pat.m_sAge;
	m_sHeight = Pat.oStudy.m_sHeight;
	m_sWeight = Pat.oStudy.m_sWeight;
	m_sStudyComments = Pat.oStudy.m_sStudyComments;
	m_sBodyPart = Pat.oStudy.oSeries.m_sBodyPart;
	m_sNumberofImages = Pat.oStudy.oSeries.m_sNumberofImages;
	m_sOperatorsName = Pat.oStudy.oSeries.m_sOperatorsName;

	return*this;
}

void CPatient::ConvertToStruct(PATIENT_INFO_t& Pat)
{
	 Pat.m_sPatientID= m_sPatientID ;
	 Pat.m_sPatientName= m_sPatientName ;
	 Pat.m_sGender= m_sGender ;
	 Pat.m_PatientDateofReg= m_PatientDateofReg ;
	 Pat.m_sAge= m_sAge ;
	 Pat.oStudy.m_sHeight= m_sHeight ;
	 Pat.oStudy.m_sWeight= m_sWeight ;
	 Pat.oStudy.m_sStudyComments= m_sStudyComments ;
	 Pat.oStudy.oSeries.m_sBodyPart= m_sBodyPart ;
	 Pat.oStudy.oSeries.m_sNumberofImages= m_sNumberofImages ;
	 Pat.oStudy.oSeries.m_sOperatorsName= m_sOperatorsName ;
}
