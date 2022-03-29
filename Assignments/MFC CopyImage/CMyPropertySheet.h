#pragma once
#include "CMyPage1.h"
#include "CMyPage2.h"
#include "Header.h"
#include "CShared.h"

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
	afx_msg LRESULT onrecieve1(WPARAM, LPARAM);

	CMyPage1 P1;
	CMyPage2 P2;

public:
	//CMap<CString, LPCTSTR, PATIENT_INFO_t, PATIENT_INFO_t&> myMap;
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();

	CMenu menu;
	afx_msg void OnCommunicationSharedmemory();

	CShared WriteManager;
	CShared ReadManager;
};


