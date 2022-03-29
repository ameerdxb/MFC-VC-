// MyPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "SharedMemoryUsingThreadNew.h"
#include "MyPropertySheet.h"


// CMyPropertySheet

IMPLEMENT_DYNAMIC(CMyPropertySheet, CPropertySheet)

CMyPropertySheet::CMyPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	

}

CMyPropertySheet::CMyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
    AddPage(&p1);
	AddPage(&p2);
}

CMyPropertySheet::~CMyPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CMyPropertySheet, CPropertySheet)
	ON_MESSAGE(WM_USER_MSG,onrecieve1)
	ON_COMMAND(ID_COMMUNICATION_SHAREDMEMORY, &CMyPropertySheet::OnCommunicationSharedmemory)
	ON_COMMAND(ID_COMMUNICATION_SOCKET, &CMyPropertySheet::OnCommunicationSocket)
END_MESSAGE_MAP()


// CMyPropertySheet message handlers


LRESULT CMyPropertySheet::onrecieve1(WPARAM wp ,LPARAM lp)
{
   //SetActivePage(&p2);
	if(myMenu.GetMenuState(ID_COMMUNICATION_SHAREDMEMORY,MF_BYCOMMAND) == MF_CHECKED)
	{
		WriteManager.OnNewNotification(lp);
	}
	else if (myMenu.GetMenuState(ID_COMMUNICATION_SOCKET, MF_BYCOMMAND) == MF_CHECKED)
	{
		p2.OnNewItemNotification(wp,lp);		
	}
	else
	{
         p2.SendMessage(WM_USER_MSG,wp,lp);
		
	}
   return 0L;
}
BOOL CMyPropertySheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO:  Add your specialized code here
	myMenu.LoadMenuW(IDR_MENU1);
	SetMenu(&myMenu);
	SetActivePage(&p1);
	SetActivePage(&p2);

	WriteManager.GetBrowserPointer(p2);
	ReadManager.GetBrowserPointer(p2);
	//m_SocketListener.GetBrowserPointer(p2);
	//m_SocketSender.GetBrowserPointer(p2);
	//p2.SetParent(this);
	p1.SetParentWindowPtr(this);
	p2.SetParent(this);
	return bResult;
}

void CMyPropertySheet::OnCommunicationSharedmemory()
{
	// TODO: Add your command handler code here
	myMenu.CheckMenuItem(ID_COMMUNICATION_SHAREDMEMORY,MF_CHECKED);
	WriteManager.ThreadStart(_T("W"));
	ReadManager.ThreadStart(_T("R"));
}


void CMyPropertySheet::OnCommunicationSocket()
{
	// TODO: Add your command handler code here
	myMenu.CheckMenuItem(ID_COMMUNICATION_SOCKET, MF_CHECKED);
	p2.SetTransferMode();
}
