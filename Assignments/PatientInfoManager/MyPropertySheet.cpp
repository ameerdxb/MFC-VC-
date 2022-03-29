// MyPropertySheet.cpp : implementation file
//

#include "pch.h"
#include "PatientInfoManager.h"
#include "MyPropertySheet.h"
#include"Header.h"

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
	ON_MESSAGE(WM_USER_SECONDPAGE, &CMyPropertySheet::OnSecondPage)
	ON_MESSAGE(WM_USER_MSG, onrecieve1)
	ON_COMMAND(ID_COMMUNICATION_SHAREDMEMORY, &CMyPropertySheet::OnCommunicationSharedmemory)
	ON_COMMAND(ID_COMMUNICATION_SOCKET, &CMyPropertySheet::OnCommunicationSocket)
END_MESSAGE_MAP()


// CMyPropertySheet message handlers
LRESULT CMyPropertySheet::OnSecondPage(WPARAM wp, LPARAM lp)
{
	
	p2.SendMessage(WM_USER_SECONDPAGE, wp, lp);
	return 0L;
}


LRESULT CMyPropertySheet::onrecieve1(WPARAM wp, LPARAM lp)
{
	
	if (myMenu.GetMenuState(ID_COMMUNICATION_SHAREDMEMORY, MF_BYCOMMAND) == MF_CHECKED)
	{
		WriteManager.OnNewNotification(lp);
	}
	else if (myMenu.GetMenuState(ID_COMMUNICATION_SOCKET, MF_BYCOMMAND) == MF_CHECKED)
	{
		p2.OnNewItemNotification(wp, lp);
	}
	else
	{
		p2.SendMessage(WM_USER_MSG, wp, lp);

	}
	return 0L;
}

BOOL CMyPropertySheet::OnInitDialog()
{
	BOOL bResult  = CPropertySheet::OnInitDialog();
	myMenu.LoadMenuW(IDR_MENU2);
	SetMenu(&myMenu);
	// TODO:  Add your specialized code here
	CButton* b;

	b = (CButton*)GetDlgItem(IDOK);
	b->ShowWindow(SW_HIDE);

	b = (CButton*)GetDlgItem(IDCANCEL);
	b->ShowWindow(SW_HIDE);

	b = (CButton*)GetDlgItem(ID_APPLY_NOW);
	b->ShowWindow(SW_HIDE);

	b = (CButton*)GetDlgItem(IDHELP);
	b->ShowWindow(SW_HIDE);

	SetActivePage(&p2);
	SetActivePage(&p1);
	p2.OnBnClickedRetrievedata();
	WriteManager.GetBrowserPointer(p2);
	ReadManager.GetBrowserPointer(p2);
	p1.SetParentWindowPtr(this);
	p2.SetParent(this);
	return bResult;
}


BOOL CMyPropertySheet::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	int n = MessageBox(
		_T("Do you wish to save the data!"),
		_T("Save data"),
		MB_ICONQUESTION| MB_YESNO | MB_DEFBUTTON1|MB_TASKMODAL
	);
	switch (n)
	{
	case IDYES:
		p2.OnBnClickedSavedata();
		break;
	case IDNO:
		AfxMessageBox(_T("Data not saved!!"));
		break;
	default:
		break;
	}
	return CPropertySheet::DestroyWindow();
}


void CMyPropertySheet::OnCommunicationSharedmemory()
{
	// TODO: Add your command handler code here
	myMenu.CheckMenuItem(ID_COMMUNICATION_SHAREDMEMORY, MF_CHECKED);
	WriteManager.ThreadStart(_T("W"));
	ReadManager.ThreadStart(_T("R"));

}


void CMyPropertySheet::OnCommunicationSocket()
{
	// TODO: Add your command handler code here
	myMenu.CheckMenuItem(ID_COMMUNICATION_SOCKET, MF_CHECKED);
	p2.SetTransferMode();
}
