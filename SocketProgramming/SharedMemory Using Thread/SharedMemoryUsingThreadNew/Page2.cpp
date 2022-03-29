// Page2.cpp : implementation file
//

#include "stdafx.h"
#include "SharedMemoryUsingThreadNew.h"
#include "Page2.h"
#include "Resource.h"
#include <tchar.h>

// CPage2 dialog

IMPLEMENT_DYNAMIC(CPage2, CPropertyPage)

CPage2::CPage2()
	: CPropertyPage(CPage2::IDD) 
{
    m_pParentWnd = 0;
}
CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_tree);
}


BEGIN_MESSAGE_MAP(CPage2, CPropertyPage)
	ON_MESSAGE(WM_USER_MSG,onRecieve2)
    ON_MESSAGE(MSG_ON_PATIENT_REG, &CPage2::OnNewItemNotification)
END_MESSAGE_MAP()


// CPage2 message handlers

LRESULT CPage2::onRecieve2(WPARAM wp,LPARAM lp)
{
	PERSON* per = (PERSON*)lp;
	if(per!=NULL)
	{
	myMap[per->id] = *per;
	}
	insertToTree();
	/*HTREEITEM root = m_tree.InsertItem(per->id);
	m_tree.InsertItem(per->nam,root);*/
   // SendDataToSocket(*per);
	return 0L;
}

void CPage2::insertToTree(void)
{
	m_tree.DeleteAllItems();
	POSITION POS = myMap.GetStartPosition();
	CString str;
	PERSON per;
	while(POS!=NULL)
	{
      myMap.GetNextAssoc(POS,str,per);
	  HTREEITEM root = m_tree.InsertItem(per.id);
	  m_tree.InsertItem(per.nam,root);

	}

}


bool CPage2::SetTransferMode()
{
	// TODO: Add your implementation code here.
    try
    {
        AfxSocketInit();
        CMyPropertySheet* wnd = (CMyPropertySheet*)AfxGetMainWnd();
        wnd->m_SocketListener.SetParent(this);
        int nResult = wnd->m_SocketListener.Create(2350);
        if (FALSE == nResult)
        {
            nResult = GetLastError();
            if (WSAEADDRINUSE == nResult)
            {
                // Server is running.
                AfxMessageBox(_T("This instance will act as a Client"));
            }
        }
        else
        {
            AfxMessageBox(_T("This instance will act as a Server"));
            if (FALSE == wnd->m_SocketListener.Listen())
            {
                return false;
            }
        }

        wnd->m_SocketSender.SetParent(this);
    }
    catch (...)
    {
        return false;
    }
    return true;
}


bool CPage2::AcceptConnection()
{
    CMyPropertySheet* wnd = (CMyPropertySheet*)AfxGetMainWnd();
    try
    {
        wnd->m_SocketListener.Accept(wnd->m_SocketSender);
    //   MessageBox(_T("Connection Accepted"));
    }
    catch (...)
    {
        return true;
    }
    return false;
}


bool CPage2::ReceiveData()
{
    CMyPropertySheet* wnd = (CMyPropertySheet*)AfxGetMainWnd();
    const int MAX_CHAR = 1024;
    try
    {
        char* pcszBuffer = new char[MAX_CHAR];
        if (0 == pcszBuffer)
        {
            return 0;
        }
        ZeroMemory(pcszBuffer, MAX_CHAR);
        int nLength = wnd->m_SocketSender.Receive(pcszBuffer, MAX_CHAR);

        if (0 >= nLength && 0 == pcszBuffer)
        {
            return 0;
        }

        CString csBuffer(pcszBuffer);
        PERSON stPatInfo;
        ParseSharedData(csBuffer);
           PERSON* pstPatInfo = new PERSON(stPatInfo);
            WPARAM wParam = reinterpret_cast<WPARAM>(pstPatInfo);
           if (0 != pstPatInfo)
            {
                PostMessage(MSG_ON_PATIENT_REG, wParam, 0);
            }       
        delete[] pcszBuffer;
        pcszBuffer = 0;
    }
    catch (...)
    {
        return false;
    }
    return true;
}

void CPage2::ParseSharedData(CString csBuffer)
{
    PERSON stPatInfo;
    int nFound = 0;
    int nStart = 0;
    int ncount;

    nFound = csBuffer.Find(_T("$"), nStart);
    ncount = nFound - nStart;
    stPatInfo.id = csBuffer.Mid(nStart, ncount);
    nStart = nFound + 1;

    nFound = csBuffer.Find(_T("$"), nStart);
    ncount = nFound - nStart;
    stPatInfo.nam = csBuffer.Mid(nStart, ncount);
    nStart = nFound + 1;
    AfxMessageBox(stPatInfo.id);
    AfxMessageBox(stPatInfo.nam);
    myMap[stPatInfo.id] = stPatInfo;
    insertToTree();




}
LRESULT CPage2::OnNewItemNotification(WPARAM wParam_i, LPARAM lParam_i)
{
  //  AfxMessageBox(_T("OnNewItemNotification"));
    UNREFERENCED_PARAMETER(lParam_i);
    try
    {
        PERSON* pstPatInfo = reinterpret_cast<PERSON*>(lParam_i);
        if (0 == pstPatInfo)
        {
            return 0;
        }
        if (pstPatInfo != NULL)
        {
            myMap[pstPatInfo->id] = *pstPatInfo;
        }
        insertToTree();
   
        SendDataToSocket(*pstPatInfo);

      //  delete pstPatInfo;
     // pstPatInfo = 0;
    }
    catch (...)
    {
    }
    return 0;
}


bool CPage2::SendDataToSocket(const PERSON& stPatInfo_i)
{
  //  AfxMessageBox(_T("SendDataToSocket"));
    
    CMyPropertySheet* wnd = (CMyPropertySheet*)AfxGetMainWnd();
   // if(wnd== NULL)
       // AfxMessageBox(_T("NULL"));
    try
    {
       if (FALSE == wnd->m_SocketSender.Create())
        {
            return false;
        }

       wnd->m_SocketSender.SendData(stPatInfo_i);
       wnd->m_SocketSender.Close();
    }
    catch (...)
    {
        return false;
    }
    return true;
}