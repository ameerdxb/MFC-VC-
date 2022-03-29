#ifndef _SOCKET_COM_MGR_H_
#define _SOCKET_COM_MGR_H_
#pragma once
// CSocketClass command target

#include "Page2.h"
#include"Header.h"
//class CPage2;

#include <afxsock.h>
class CSocketClass :
    public CAsyncSocket
{

public:

    virtual void OnAccept(int nErrorCode_i);
    virtual void OnClose(int nErrorCode_i);
    virtual void OnConnect(int nErrorCode_i);
    virtual void OnOutOfBandData(int nErrorCode_i);
    virtual void OnReceive(int nErrorCode_i);
    virtual void OnSend(int nErrorCode_i);

public:

    CSocketClass();
    ~CSocketClass();
    bool SendData(const PATIENT& stPatInfo_i);
    bool ReceiveData(const CString& csBuffer_i, PATIENT& stPatInfo_o);
    void SetParent(CDialog* pWindowPtr_i)
    {
        m_pParentWindow = pWindowPtr_i;
    }

    void ParseSharedData(CString csBuffer);
    void GetBrowserPointer(CPage2& pag2);

private:
    CPage2* m_page2;
    CDialog* m_pParentWindow;
};

#endif
