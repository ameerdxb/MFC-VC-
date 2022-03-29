
// PropSheetDemo.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPropSheetDemoApp:
// See PropSheetDemo.cpp for the implementation of this class
//

class CPropSheetDemoApp : public CWinApp
{
public:
	CPropSheetDemoApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPropSheetDemoApp theApp;
