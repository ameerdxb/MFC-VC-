#pragma once
#include"Header.h"

// CPage1 dialog

class CPage1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage1)

public:
	CPage1();
	virtual ~CPage1();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	CString m_PatientID;
	CString m_PatientName;
	CButton m_Male;
	CButton m_Female;
	CString m_Date;
	CString m_Age;
	CComboBox m_Age1;
	CString m_Height;
	CString m_Weight;
	CString m_StudyComments;
	CComboBox m_ctrlBodyPart;
	CString m_BodyPart;
	CString m_NumberofImages;
	CString m_OperatorsName;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedRegister();
	CDateTimeCtrl m_Date1;
	void ParseFileContents();
	void ReadContents();
	CStringArray arr;
	CEdit m_PatientID1;
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	void CreateDir(CString& strFile);
	afx_msg void OnBnClickedEmergencyId();
	afx_msg void OnCbnSelchangeBodypart();
	afx_msg void OnBnClickedScan();
	
	CFile myFile;
	CWnd* m_pParentWindowPtr;
	void SetParentWindowPtr(CWnd* pWndPtr_i)
	{
		m_pParentWindowPtr = pWndPtr_i;
	}
	CString m_strFile;
};
