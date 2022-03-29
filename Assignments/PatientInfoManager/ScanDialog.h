#pragma once
#include"Page2.h"

// CScanDialog dialog

class CScanDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CScanDialog)

public:
	CScanDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CScanDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_PatientName;
	CString m_PatientID;
	CString m_strFile;
	CString m_BodyPart;
	CString m_NumberOfImages;
	CPage2 p2;
	void SetData(CString, CString,CString,CString,CString);
	DWORD OpenImageFile();
	DWORD StoreImageFile(CString);
	virtual BOOL OnInitDialog();
	CProgressCtrl m_Progress;
	afx_msg void OnBnClickedAbort();
	LRESULT OnProgress(WPARAM wParam_i, LPARAM lParam_i);
	bool m_bCancelOperation;
	HANDLE m_hThreadHandle;
};
