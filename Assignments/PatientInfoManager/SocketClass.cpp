// SocketClass.cpp : implementation file
//

#include "pch.h"
#include "PatientInfoManager.h"
#include "SocketClass.h"


// CSocketClass

CSocketClass::CSocketClass()
{
}

CSocketClass::~CSocketClass()
{
}


// CSocketClass member functions
void CSocketClass::OnAccept(int nErrorCode_i)
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


void CSocketClass::OnClose(int nErrorCode_i)
{
    try
    {
        CAsyncSocket::OnClose(nErrorCode_i);
    }
    catch (...)
    {
    }
}


void CSocketClass::OnConnect(int nErrorCode_i)
{
    try
    {
        CAsyncSocket::OnConnect(nErrorCode_i);
    }
    catch (...)
    {
    }
}


void CSocketClass::OnOutOfBandData(int nErrorCode_i)
{
    try
    {
        CAsyncSocket::OnOutOfBandData(nErrorCode_i);
    }
    catch (...)
    {
    }
}


void CSocketClass::OnReceive(int nErrorCode_i)
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


void CSocketClass::OnSend(int nErrorCode_i)
{
    try
    {
        CAsyncSocket::OnSend(nErrorCode_i);
    }
    catch (...)
    {
    }
}


bool CSocketClass::SendData(const PATIENT& stPatInfo_i)
{
    const LPCTSTR HOST_NAME = _T("localhost");
    try
    {
        // DWORD dwProcessID = GetCurrentProcessId();
       //  CString csMsgStr;
       //  csMsgStr.Format(_T("%s%d%s"), "$", dwProcessID, "$");
       //  AfxMessageBox(csMsgStr);

         //PatInfoCommonUtility::FormatInfoToBuffer(stPatInfo_i, csBuffer);
        CString csBuffer = stPatInfo_i.m_PatientID + _T("$") + stPatInfo_i.m_PatientName + _T("$") 
            + stPatInfo_i.m_Gender + _T("$") + stPatInfo_i.m_Date + _T("$") + stPatInfo_i.m_Age + _T("")
            + stPatInfo_i.study.m_Height + _T("$") + stPatInfo_i.study.m_Weight + _T("") + 
            stPatInfo_i.study.m_StudyComments + _T("$") + stPatInfo_i.study.series.m_BodyPart + _T("$")
            + stPatInfo_i.study.series.m_NumberofImages + _T("$") + stPatInfo_i.study.series.m_OperatorsName + _T("$");
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


bool CSocketClass::ReceiveData(const CString& csBuffer_i, PATIENT& stPatInfo_o)
{
    try
    {
        CString csReceivedBuf(csBuffer_i);
        ParseSharedData(csReceivedBuf);

    }
    catch (...)
    {
        return false;
    }
    return true;
}

void CSocketClass::ParseSharedData(CString csBuffer)
{
    PATIENT stPatInfo;
    int nFound = 0;
    int nStart = 0;
    int ncount;

    nFound = csBuffer.Find(_T("$"), nStart);
    ncount = nFound - nStart;
    stPatInfo.m_PatientID = csBuffer.Mid(nStart, ncount);
    nStart = nFound + 1;

    nFound = csBuffer.Find(_T("$"), nStart);
    ncount = nFound - nStart;
    stPatInfo.m_PatientName = csBuffer.Mid(nStart, ncount);
    nStart = nFound + 1;

    nFound = csBuffer.Find(_T("$"), nStart);
    ncount = nFound - nStart;
    stPatInfo.m_Gender = csBuffer.Mid(nStart, ncount);
    nStart = nFound + 1;

    nFound = csBuffer.Find(_T("$"), nStart);
    ncount = nFound - nStart;
    stPatInfo.m_Date = csBuffer.Mid(nStart, ncount);
    nStart = nFound + 1;

    nFound = csBuffer.Find(_T("$"), nStart);
    ncount = nFound - nStart;
    stPatInfo.m_Age = csBuffer.Mid(nStart, ncount);
    nStart = nFound + 1;

    nFound = csBuffer.Find(_T("$"), nStart);
    ncount = nFound - nStart;
    stPatInfo.study.m_Height = csBuffer.Mid(nStart, ncount);
    nStart = nFound + 1;

    nFound = csBuffer.Find(_T("$"), nStart);
    ncount = nFound - nStart;
    stPatInfo.study.m_Weight = csBuffer.Mid(nStart, ncount);
    nStart = nFound + 1;

    nFound = csBuffer.Find(_T("$"), nStart);
    ncount = nFound - nStart;
    stPatInfo.study.m_StudyComments = csBuffer.Mid(nStart, ncount);
    nStart = nFound + 1;

    nFound = csBuffer.Find(_T("$"), nStart);
    ncount = nFound - nStart;
    stPatInfo.study.series.m_BodyPart = csBuffer.Mid(nStart, ncount);
    nStart = nFound + 1;

    nFound = csBuffer.Find(_T("$"), nStart);
    ncount = nFound - nStart;
    stPatInfo.study.series.m_NumberofImages = csBuffer.Mid(nStart, ncount);
    nStart = nFound + 1;

    nFound = csBuffer.Find(_T("$"), nStart);
    ncount = nFound - nStart;
    stPatInfo.study.series.m_OperatorsName = csBuffer.Mid(nStart, ncount);
    nStart = nFound + 1;
    AfxMessageBox(stPatInfo.m_PatientID);
    AfxMessageBox(stPatInfo.m_PatientName);
    m_page2->myMap[stPatInfo.m_PatientID] = stPatInfo;
    m_page2->InsertToTree();
}

void CSocketClass::GetBrowserPointer(CPage2& pag2)
{
    TRACE("GetBrowserPointer");
    m_page2 = &pag2;
}