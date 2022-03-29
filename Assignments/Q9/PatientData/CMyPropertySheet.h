#pragma once
#include"CMyPage1.h"
#include"CMyPage2.h"



// CMyPropertySheet

class CMyPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMyPropertySheet)

public:
	CMyPropertySheet(UINT nIDCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	CMyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	virtual ~CMyPropertySheet();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnSecondPage(WPARAM, LPARAM);
	CMyPage1 p1;
	CMyPage2 p2;
public:
	virtual BOOL OnInitDialog();
};


