
// FileCopyThreadDlg.h : header file
//

#pragma once


// CFileCopyThreadDlg dialog
class CFileCopyThreadDlg : public CDialogEx
{
// Construction
public:
	CFileCopyThreadDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FILECOPYTHREAD_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	HANDLE hevent;
	CCriticalSection m_cs;
};
