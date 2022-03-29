
// Thread_SearchFile_DialogBased_CancelSearchDlg.h : header file
//

#pragma once


// CThreadSearchFileDialogBasedCancelSearchDlg dialog
class CThreadSearchFileDialogBasedCancelSearchDlg : public CDialogEx
{
// Construction
public:
	CThreadSearchFileDialogBasedCancelSearchDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THREAD_SEARCHFILE_DIALOGBASED_CANCELSEARCH_DIALOG };
#endif

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
//	CComboBox m_Combo;
	CComboBox m_Path;
};
