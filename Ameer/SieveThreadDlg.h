
// SieveThreadDlg.h : header file
//

#pragma once


// CSieveThreadDlg dialog
class CSieveThreadDlg : public CDialogEx
{
// Construction
public:
	CSieveThreadDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIEVETHREAD_DIALOG };
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
	afx_msg LRESULT OnPrimeCount(WPARAM, LPARAM);
public:
	afx_msg void OnBnStart();
	int m_Result;
};
