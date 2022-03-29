#pragma once
#include "Header.h"

// CMyPage2 dialog

class CMyPage2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CMyPage2)

public:
	CMyPage2();
	virtual ~CMyPage2();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnAddToTree(WPARAM, LPARAM);
public:
	CTreeCtrl m_Tree;
	CMap < CString, LPCTSTR, STUDENT, STUDENT&>myMap;
	void InsertToTree();
	CEdit m_NameControl;
	CEdit m_GenderControl;
	afx_msg void OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	CString m_Name;
	CString m_Gender;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
