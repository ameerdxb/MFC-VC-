#include "pch.h"
#include "Header.h"
#include "afxwin.h"

CFilePortion::CFilePortion(void)
{
	Index = 0;
}


CFilePortion::~CFilePortion(void)
{
}

void CFilePortion::ReadFromFile(CString strFileName)
{
	if (m_File.Open(strFileName, CFile::modeRead))
	{
		int nLength = 0, i = 0;
		CString st, s;
		nLength = static_cast<int>(m_File.GetLength());

		char* pzBuffer = new char[nLength];
		ZeroMemory(pzBuffer, nLength);//initialize pzBuffer to 0

		m_File.Read(pzBuffer, nLength);
		CString str(pzBuffer);//Convert char* to CString

		AfxMessageBox(str);

		ParseFileContents(str);//Parsing the contents of file
		m_File.Close();
		delete[] pzBuffer;
	}
}

void CFilePortion::ParseFileContents(CString& str)
{
	const LPCTSTR FRUITS = _T("FRUITS");
	const LPCTSTR SEPERATOR = _T(":");
	const LPCTSTR VALUE_SEPERATOR = _T(",");
	const LPCTSTR LINE_END = _T(";");

	CString SearchKey;
	SearchKey.Format(_T("%s%s"), FRUITS, SEPERATOR);
	//AfxMessageBox(SearchKey);

	int found = str.Find(SearchKey);

	int start = found + SearchKey.GetLength();
	found = str.Find(LINE_END);
	int end = found;

	//Extracts string between 'FRUITS:' and ';'
	CString str1 = CString(str.Mid(start, end - start));

	//AfxMessageBox(str1);
	str1 = str1 + VALUE_SEPERATOR;
	AfxMessageBox(str1);

	found = 0;
	start = 0;
	while (-1 != found)
	{
		found = str1.Find(VALUE_SEPERATOR, found);

		if (found == -1)
		{
			break;
		}
		CString data = str1.Mid(start, found - start);
		strArray.SetAtGrow(Index++, data);
		AfxMessageBox(data);
		start = ++found;
	}
}

int CFilePortion::GetSize(void)
{
	return strArray.GetSize();
}

CString CFilePortion::GetFruits(void)
{
	return strArray[--Index];
}