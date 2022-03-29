
// ThreadSearchFilesView.h : interface of the CThreadSearchFilesView class
//

#pragma once

#include "resource.h"
#include "afxwin.h"
#include"ThreadSearchFilesDoc.h"

class CThreadSearchFilesView : public CFormView
{
protected: // create from serialization only
	CThreadSearchFilesView();
	DECLARE_DYNCREATE(CThreadSearchFilesView)

public:
	enum{ IDD = IDD_THREADSEARCHFILES_FORM };

// Attributes
public:
	CThreadSearchFilesDoc* GetDocument() const;
	HANDLE m_hThreadHandle,m_hKillEvent;	
	CWinThread* pThread;;
// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CThreadSearchFilesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	int x1, y1, x2, y2;
	CListBox m_List;
	CString strpath;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton2();
};

#ifndef _DEBUG  // debug version in ThreadSearchFilesView.cpp
inline CThreadSearchFilesDoc* CThreadSearchFilesView::GetDocument() const
   { return reinterpret_cast<CThreadSearchFilesDoc*>(m_pDocument); }
#endif

