#pragma once


// CScanModalChild dialog

class CScanModalChild : public CDialog
{
	DECLARE_DYNAMIC(CScanModalChild)

public:
	CScanModalChild(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CScanModalChild();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_ID;
	CString m_Name;
	afx_msg void OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult);
	CProgressCtrl m_Progress;
	virtual BOOL OnInitDialog();
};
