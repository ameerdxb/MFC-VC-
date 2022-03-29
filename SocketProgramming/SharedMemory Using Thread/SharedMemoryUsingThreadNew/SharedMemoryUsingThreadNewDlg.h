// SharedMemoryUsingThreadNewDlg.h : header file
//

#pragma once


// CSharedMemoryUsingThreadNewDlg dialog
class CSharedMemoryUsingThreadNewDlg : public CDialog
{
// Construction
public:
	CSharedMemoryUsingThreadNewDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SHAREDMEMORYUSINGTHREADNEW_DIALOG };

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
};
