#include "stdafx.h"
#include "Header.h"
int count = 0;
CFile m_File;

CString ReadFromFile(CString strFile)
{
	CString str = L"";
	if (m_File.Open(strFile, CFile::modeRead))
	{
		int nLen_Of_File = 0;
		nLen_Of_File = static_cast<int>(m_File.GetLength());
		char* pszBuffer = new char[nLen_Of_File];
		ZeroMemory(pszBuffer, nLen_Of_File);
		m_File.Read(pszBuffer, nLen_Of_File);
		CString str1(pszBuffer);
		convert(str1);
		m_File.Close();
		delete[] pszBuffer;
		return str1;
	}
	else
	{
		AfxMessageBox(_T("Failed to open file!!!!"));
		return str;
	}
	
}

void convert(CString& str)
{
	

	str.MakeUpper();

	}

