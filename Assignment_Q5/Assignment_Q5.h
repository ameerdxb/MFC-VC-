
// Assignment_Q5.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CAssignmentQ5App:
// See Assignment_Q5.cpp for the implementation of this class
//

class CAssignmentQ5App : public CWinApp
{
public:
	CAssignmentQ5App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CAssignmentQ5App theApp;
