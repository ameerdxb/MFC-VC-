
// Thread_SearchFile_DialogBased_CancelSearch.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CThreadSearchFileDialogBasedCancelSearchApp:
// See Thread_SearchFile_DialogBased_CancelSearch.cpp for the implementation of this class
//

class CThreadSearchFileDialogBasedCancelSearchApp : public CWinApp
{
public:
	CThreadSearchFileDialogBasedCancelSearchApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CThreadSearchFileDialogBasedCancelSearchApp theApp;
