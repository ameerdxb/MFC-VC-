#pragma once
#include "page11.h"
#include "Page2.h"
#include "SharedMemory.h"


// CMyPropertySheet

class CMyPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMyPropertySheet)

public:
	Cpage11 p1;
	CPage2 p2;
	CMyPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CMyPropertySheet();

protected:
	afx_msg LRESULT onrecieve1(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
public:
	CSharedMemory WriteManager;
	CSharedMemory ReadManager;
	CMenu myMenu;
	virtual BOOL OnInitDialog();
	afx_msg void OnCommunicationSharedmemory();
};


