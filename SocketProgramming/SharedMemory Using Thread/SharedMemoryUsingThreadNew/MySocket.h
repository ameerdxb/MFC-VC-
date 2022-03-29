#ifndef _SOCKET_COM_MGR_H_
#define _SOCKET_COM_MGR_H_
#include "Page2.h"

//class CPage2;

#include <afxsock.h>
class MySocket :
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

    MySocket();
    ~MySocket();
    bool SendData(const PERSON& stPatInfo_i);
    bool ReceiveData(const CString& csBuffer_i, PERSON& stPatInfo_o);
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