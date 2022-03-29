#pragma once
#include"Header.h"

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
	afx_msg void OnBnClickedClear();
	CDateTimeCtrl m_Date;
	CButton m_Male;
	CButton m_Female;
	CComboBox m_ctrlBodyPart;
	virtual BOOL OnInitDialog();
	CString m_strId;
	CString m_strName;
	CString m_strAge;
	CString m_strHeight;
	CString m_strWeight;
	CString m_strComment;
	CString m_strImage;
	CString m_strOperator;
	CString m_strDate;
	CString m_strBodyPart;
	int n;
	PATIENT std;
	afx_msg void OnBnClickedEmergencyid();
	afx_msg void OnBnClickedRegister();
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCbnSelchangeCombo1();
	CListCtrl m_List;
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	void Reg();
};
