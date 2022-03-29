
// Q2Sort.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CQ2SortApp:
// See Q2Sort.cpp for the implementation of this class
//

class CQ2SortApp : public CWinApp
{
public:
	CQ2SortApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CQ2SortApp theApp;
