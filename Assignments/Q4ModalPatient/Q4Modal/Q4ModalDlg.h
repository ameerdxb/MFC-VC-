
// Q4ModalDlg.h : header file
//

#pragma once


// CQ4ModalDlg dialog
class CQ4ModalDlg : public CDialogEx
{
// Construction
public:
	CQ4ModalDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Q4MODAL_DIALOG };
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
	int m_nID;
	CString m_sName;
	afx_msg void OnBnClickedOk();
};
