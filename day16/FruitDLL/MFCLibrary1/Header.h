#ifdef EXPORT_DLL
#define EXPORTSYMBOL extern "C"__declspec(dllexport)

#else
#define EXPORTSYMBOL extern "C" __declspec(dllimport)
#endif


#pragma once
#include "afx.h"
class __declspec(dllexport) CFilePortion
{
public:
	CFilePortion(void);
	~CFilePortion(void);

	void ReadFromFile(CString);

private:
	CFile m_File;
	CStringArray strArray;
	int Index;
public:
	void ParseFileContents(CString& str);

	CString GetFruits(void);//return the content from collection class
	int GetSize(void);//return size of collection class obj
};

