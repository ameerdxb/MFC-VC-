#pragma once

#include "CMyPage1.h"
#include "CMyPage2.h"
#include "CSharedMemory.h"
// CMypropertySheet

class CMypropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMypropertySheet)

public:
	CMypropertySheet(UINT nIDCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	CMypropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	virtual ~CMypropertySheet();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnSecondPage(WPARAM, LPARAM);
	CMyPage1 p1;
	CMyPage2 p2;
public:
	virtual BOOL OnInitDialog();
	CMenu myMenu;
	afx_msg void OnCommunicationSharedmemory();
	CSharedMemory WriteManager;
	CSharedMemory ReadManager;
};


