
// Uppercase_dynamic_dll.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CUppercase_dynamic_dllApp:
// See Uppercase_dynamic_dll.cpp for the implementation of this class
//

class CUppercase_dynamic_dllApp : public CWinApp
{
public:
	CUppercase_dynamic_dllApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CUppercase_dynamic_dllApp theApp;