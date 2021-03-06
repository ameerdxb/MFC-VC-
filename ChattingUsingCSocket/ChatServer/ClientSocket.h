#if !defined(AFX_CLIENTSOCKET_H__6BBED275_E438_401F_8760_09FA79D217BD__INCLUDED_)
#define AFX_CLIENTSOCKET_H__6BBED275_E438_401F_8760_09FA79D217BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSocket.h : header file
//
#include "Afxsock.h"

/////////////////////////////////////////////////////////////////////////////
// ClientSocket command target

class ClientSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	ClientSocket();
	virtual ~ClientSocket();

// Overrides
public:
	CDialog * pDlg;

	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ClientSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(ClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCKET_H__6BBED275_E438_401F_8760_09FA79D217BD__INCLUDED_)
