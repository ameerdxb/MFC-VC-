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
	afx_msg void OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	CTreeCtrl m_Tree;
	CMap < CString, LPCTSTR, PATIENT, PATIENT& > myMap;
	void InsertToTree();
	CListCtrl m_List;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRetrieve();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedExit();
};
