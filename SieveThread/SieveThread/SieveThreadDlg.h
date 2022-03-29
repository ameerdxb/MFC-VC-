
// SieveThreadDlg.h : header file
//

#pragma once
typedef struct
{
	int nMax;
	HWND hwnd;
}THREAD;
#define WM_USER_THREAD_FINISH WM_USER + 0x0400
// CSieveThreadDlg dialog
class CSieveThreadDlg : public CDialogEx
{
// Construction
public:
	CSieveThreadDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SIEVETHREAD_DIALOG };

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
	afx_msg LRESULT OnThreadFinish(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
