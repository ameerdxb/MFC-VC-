#pragma once
#include "Header.h"
#include "CScan.h"
// CMyPage1 dialog

class CMyPage1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CMyPage1)

public:
	CMyPage1();
	virtual ~CMyPage1();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	CString m_PatientID;
	CString m_PatientName;
	CButton m_Male;
	CButton m_Female;
	CString m_DateRegistration;
	CString m_Height;
	CString m_Weight;
	CString m_Study;
	CString m_nImages;
	CString m_OperatorName;
	CComboBox m_Age;
	CComboBox m_BodyPart;
	virtual BOOL OnInitDialog();
	CListCtrl m_List;
	afx_msg void OnBnClickedButton3();
	CString m_AgeEdit;
	CString m_BodyValue;
	CString m_AgeValue;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CEdit m_PatIDControl;
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);

	void ParseFileContents(CString& strFile);
	void ReadContents();
	CStringArray arr;
	afx_msg void OnBnClickedButton4();
	void FileToComboBox();
	CFile myFile;
	CString m_RefImageFile;
	CString m_DesFile;
};
