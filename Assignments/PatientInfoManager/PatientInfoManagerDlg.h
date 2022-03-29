
// PatientInfoManagerDlg.h : header file
//

#pragma once


// CPatientInfoManagerDlg dialog
class CPatientInfoManagerDlg : public CDialogEx
{
// Construction
public:
	CPatientInfoManagerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PATIENTINFOMANAGER_DIALOG };
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
	CListCtrl m_List1;
	CString m_PatientID;
	
	
	
};
