#pragma once
#include"Page1.h"
#include"Page2.h"
#include"SharedMemory.h"
#include"SocketClass.h"
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
	CPage1 p1;
	CPage2 p2;
	CMenu myMenu;
	CSharedMemory WriteManager;
	CSharedMemory ReadManager;
	
	afx_msg LRESULT OnSecondPage(WPARAM, LPARAM);
	afx_msg LRESULT onrecieve1(WPARAM, LPARAM);
public:
	CSocketClass m_SocketListener;
	CSocketClass m_SocketSender;
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnCommunicationSharedmemory();
	afx_msg void OnCommunicationSocket();
};


