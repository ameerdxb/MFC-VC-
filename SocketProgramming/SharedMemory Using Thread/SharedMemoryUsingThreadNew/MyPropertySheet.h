#pragma once

#include "SharedMemory.h"

#include "page11.h"
#include "Page2.h"
// CMyPropertySheet
#include "MySocket.h"

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
	MySocket m_SocketListener;
	MySocket m_SocketSender;
	
	
	virtual BOOL OnInitDialog();
	afx_msg void OnCommunicationSharedmemory();
	afx_msg void OnCommunicationSocket();
};


