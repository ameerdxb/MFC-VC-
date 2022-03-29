
// Assignment_Q3.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CAssignment_Q3App:
// See Assignment_Q3.cpp for the implementation of this class
//

class CAssignment_Q3App : public CWinApp
{
public:
	CAssignment_Q3App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CAssignment_Q3App theApp;