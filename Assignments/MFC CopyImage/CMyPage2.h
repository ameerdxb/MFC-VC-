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
	CMap<CString, LPCTSTR, PATIENT_INFO_t, PATIENT_INFO_t&> myMap;
	CTreeCtrl m_Tree;
	

	void InsertToTree();
	afx_msg void OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_List2;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();


	afx_msg void OnBnClickedButton3();
	
};
