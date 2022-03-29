#pragma once


// CSearchDialog dialog

class CSearchDialog : public CDialog
{
	DECLARE_DYNAMIC(CSearchDialog)

public:
	CSearchDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSearchDialog();
	bool m_bCancelOperation;
	HANDLE m_hThreadHandle;
	CString m_SearchPath;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	LRESULT OnMsgSearchProgress(WPARAM wParam_i = 0, LPARAM lParam_i = 0);
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_Search;
	void SetSearchPath(const CString&  strPath);
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	//static DWORD SearchThreadProc(LPVOID lParam_i);
	//bool EnumerateFolders(CString strFile, LPVOID param);
	int nIndex;
	CStatic m_FileCount;
};
