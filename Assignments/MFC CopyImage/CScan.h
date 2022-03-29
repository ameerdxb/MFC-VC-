#pragma once
#include "CMyPage1.h"

// CScan dialog

class CScan : public CDialog
{
	DECLARE_DYNAMIC(CScan)

public:
	CScan(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CScan();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_ScanPatID;
	CStatic m_ScanPatName;
	void SetSearchPath(const CString&);
	CString m_SearchPath;
	virtual BOOL OnInitDialog();
	HANDLE m_hThreadHandle;
	int nIndex;

	CString m_PatName1;
	CString m_PatID1;
	CString m_BodyPartCombo1;
	CString m_NumberOfImage1;
	CString m_ImageFile1;
	void GetDetails(CString& m_PatName, CString& m_PatID, CString& m_BodyPartCombo, CString& m_NumberOfImage, CString& m_ImageFile, CString& m_DesFile);
	afx_msg void OnBnClickedButton1();
	CProgressCtrl m_Progress;
	bool m_bCancelOperation;
	CString DesFile;
};
