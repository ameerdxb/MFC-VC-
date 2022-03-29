
// DynamicLinkingDLLDlg.h : header file
//

#pragma once


// CDynamicLinkingDLLDlg dialog
class CDynamicLinkingDLLDlg : public CDialogEx
{
// Construction
public:
	CDynamicLinkingDLLDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DYNAMICLINKINGDLL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	HMODULE hDLL;

	typedef int (*CALLBACK ADDFUN)(int,int);
	ADDFUN addPtr;
	ADDFUN subPtr;

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
	int m_Num1;
	int m_Num2;
	int m_Result;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
