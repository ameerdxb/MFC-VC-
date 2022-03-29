#include "stdafx.h"
#include "MySocket.h"


MySocket::MySocket() : m_pParentWindow(0)
{
}


MySocket::~MySocket()
{
}


void MySocket::OnAccept(int nErrorCode_i)
{
    try
    {
        AfxMessageBox(_T("OnAccept"));
        CPage2* pParentWnd = reinterpret_cast<CPage2*>(m_pParentWindow);
        if (0 != pParentWnd)
        {
            pParentWnd->AcceptConnection();
        }
        CAsyncSocket::OnAccept(nErrorCode_i);
    }
    catch (...)
    {
    }
}


void MySocket::OnClose(int nErrorCode_i)
{
    try
    {
        CAsyncSocket::OnClose(nErrorCode_i);
    }
    catch (...)
    {
    }
}


void MySocket::OnConnect(int nErrorCode_i)
{
    try
    {
        CAsyncSocket::OnConnect(nErrorCode_i);
    }
    catch (...)
    {
    }
}


void MySocket::OnOutOfBandData(int nErrorCode_i)
{
    try
    {
        CAsyncSocket::OnOutOfBandData(nErrorCode_i);
    }
    catch (...)
    {
    }
}


void MySocket::OnReceive(int nErrorCode_i)
{
    AfxMessageBox(_T("OnReceive"));
    try
    {
        CPage2* pParentWnd = reinterpret_cast<CPage2*>(m_pParentWindow);
        if (0 != pParentWnd)
        {
            pParentWnd->ReceiveData();
        }
        CAsyncSocket::OnReceive(nErrorCode_i);
    }
    catch (...)
    {
    }
}


void MySocket::OnSend(int nErrorCode_i)
{
    try
    {
        CAsyncSocket::OnSend(nErrorCode_i);
    }
    catch (...)
    {
    }
}


bool MySocket::SendData(const PERSON& stPatInfo_i)
{
    const LPCTSTR HOST_NAME = _T("localhost");
    try
    {
       // DWORD dwProcessID = GetCurrentProcessId();
      //  CString csMsgStr;
      //  csMsgStr.Format(_T("%s%d%s"), "$", dwProcessID, "$");
      //  AfxMessageBox(csMsgStr);
        
        //PatInfoCommonUtility::FormatInfoToBuffer(stPatInfo_i, csBuffer);
        CString csBuffer =   stPatInfo_i.id + _T("$") +  stPatInfo_i.nam + _T("$");
       int nStrLen = csBuffer.GetLength();
        char* pcszMsgStr = new char[nStrLen + 1];
        if (0 == pcszMsgStr)
        {
            return false;
        }
        ZeroMemory(pcszMsgStr, nStrLen + 1);
        nStrLen = wcstombs(pcszMsgStr, csBuffer, nStrLen);
        Connect(HOST_NAME, 2350);
        Send(pcszMsgStr, nStrLen);

        delete[] pcszMsgStr;
        pcszMsgStr = 0;
    }
    catch (...)
    {
        return false;
    }
    AfxMessageBox(_T("return true"));
    return true;
}


bool MySocket::ReceiveData(const CString& csBuffer_i, PERSON& stPatInfo_o)
{
    try
    {
        CString csReceivedBuf(csBuffer_i);
      //  DWORD dwProcessID = GetCurrentProcessId();
      //  CString csMsgStr;
     //   csMsgStr.Format(_T("%s%d%s"), "$", dwProcessID, "$");
      //  int nFindIdx = 0;
      //  nFindIdx = csReceivedBuf.Find(csMsgStr);
      //  if (-1 != nFindIdx)
       // {
            // Same process, no need to update.
       //     return false;
       // }
        ParseSharedData(csReceivedBuf);
       
    }
    catch (...)
    {
        return false;
    }
    return true;
}

void MySocket::ParseSharedData(CString csBuffer)
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
    m_page2->myMap[stPatInfo.id] = stPatInfo;
    m_page2->insertToTree();
}

void MySocket::GetBrowserPointer(CPage2& pag2)
{
    TRACE("GetBrowserPointer");
    m_page2 = &pag2;
}