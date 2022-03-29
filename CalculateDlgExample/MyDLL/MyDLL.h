// MyDLL.h : main header file for the MyDLL DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMyDLLApp
// See MyDLL.cpp for the implementation of this class
//

class CMyDLLApp : public CWinApp
{
public:
	CMyDLLApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
