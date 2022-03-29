#pragma once
#include "Header.h"

// CPatient command target

class CPatient : public CObject
{
public:
	DECLARE_SERIAL(CPatient)

	CPatient();
	virtual ~CPatient();
	virtual void Serialize(CArchive& ar);

	CPatient& operator=(PATIENT_INFO_t& Pat);

	void ConvertToStruct(PATIENT_INFO_t&);

private:
	CString m_sBodyPart;
	CString m_sNumberofImages;
	CString m_sOperatorsName;

	CString m_sHeight;
	CString m_sWeight;
	CString m_sStudyComments;
	//SERIES_INFO_t oSeries;

	CString m_sPatientName;
	CString m_sPatientID;
	CString m_PatientDateofReg;
	CString m_sGender;
	CString m_sAge;
	//STUDY_INFO_t oStudy;
};


