
// Assignment_Q3Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// CAssignment_Q3Dlg dialog
class CAssignment_Q3Dlg : public CDialogEx
{
// Construction
public:
	CAssignment_Q3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ASSIGNMENT_Q3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listOne;
	CListBox m_ListTwo;
	afx_msg void OnClickedButton1();
	afx_msg void OnClickedButton2();
	afx_msg void OnClickedButton3();
	afx_msg void OnClickedButton4();
	CStringList list;
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnLbnSelchangeList2();
};
