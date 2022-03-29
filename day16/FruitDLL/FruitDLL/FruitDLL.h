// FruitDLL.h : main header file for the FruitDLL DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFruitDLLApp
// See FruitDLL.cpp for the implementation of this class
//

class CFruitDLLApp : public CWinApp
{
public:
	CFruitDLLApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
