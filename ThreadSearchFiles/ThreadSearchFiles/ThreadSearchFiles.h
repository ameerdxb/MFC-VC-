
// ThreadSearchFiles.h : main header file for the ThreadSearchFiles application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CThreadSearchFilesApp:
// See ThreadSearchFiles.cpp for the implementation of this class
//

class CThreadSearchFilesApp : public CWinApp
{
public:
	CThreadSearchFilesApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CThreadSearchFilesApp theApp;
