
// FileCopyThread.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFileCopyThreadApp:
// See FileCopyThread.cpp for the implementation of this class
//

class CFileCopyThreadApp : public CWinApp
{
public:
	CFileCopyThreadApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CFileCopyThreadApp theApp;