
// Uppercase_dynamic_dllDlg.h : header file
//

#pragma once


// CUppercase_dynamic_dllDlg dialog
class CUppercase_dynamic_dllDlg : public CDialogEx
{
// Construction
public:
	CUppercase_dynamic_dllDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_UPPERCASE_DYNAMIC_DLL_DIALOG };

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
	HMODULE hdll;
    typedef CString(*uppercaseconvert)(CString);
};
