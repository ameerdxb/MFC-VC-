#pragma once


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
	CString m_Name;
	CButton m_Male;
	CButton m_Female;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadio1();
	//int m_Id;
	afx_msg void OnEnChangeEdit2();
	CString m_Id;
	CString m_Date;
	CString m_Age;
	CString m_Mark1;
	CString m_Mark2;
	CString m_Mark3;
	afx_msg void OnBnClickedButton2();
};
