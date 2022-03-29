#pragma once
#include "afxwin.h"


// Cpage11 dialog

class Cpage11 : public CPropertyPage
{
	DECLARE_DYNAMIC(Cpage11)

public:
	PERSON per;
	Cpage11();
	virtual ~Cpage11();

// Dialog Data
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString var1;
	afx_msg void OnAdd();
	CEdit m_id;
	CWnd* m_pParentWindowPtr;
	void SetParentWindowPtr(CWnd* pWndPtr_i)
	{
		m_pParentWindowPtr = pWndPtr_i;
	}
};
