
// Q4Modal.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CQ4ModalApp:
// See Q4Modal.cpp for the implementation of this class
//

class CQ4ModalApp : public CWinApp
{
public:
	CQ4ModalApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CQ4ModalApp theApp;
