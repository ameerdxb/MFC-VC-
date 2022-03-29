#ifndef HEAD_H
#define HEAD_H
#include<afx.h>
#include<afxcoll.h>
#ifdef EXPORT_DLL
#define EXPORTSYMBOL extern"C" __declspec(dllexport)
#else
#define EXPORTSYMBOL extern"C" __declspec(dllimport)
#endif

EXPORTSYMBOL CString ReadFromFile(CString);
 void convert(CString&);
	

#endif