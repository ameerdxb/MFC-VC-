// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ClientSocket.h"

//#include "Userdata.h"

#include "ChatServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ClientSocket

ClientSocket::ClientSocket()
{
}

ClientSocket::~ClientSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CSocket)
	//{{AFX_MSG_MAP(CClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSocket member functions

void ClientSocket::OnReceive(int nErrorCode) 
{
	
	char buff[1000];
	
	int ibuf =Receive(buff,sizeof(buff));
	buff[ibuf] ='\0';

	UserInfo_t *udata;
	udata = (UserInfo_t*)buff;

	((CChatServerDlg*)pDlg)->AddMsg(udata);


	CSocket::OnReceive(nErrorCode);
}
