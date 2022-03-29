#pragma once

#ifdef _WIN32_WCE
#error "COlePropertyPage is not supported for Windows CE."
#endif 

// CPage1 : Property page dialog

class CPage1 : public PropertyPage
{
	DECLARE_DYNCREATE(CPage1)
	DECLARE_OLECREATE_EX(CPage1)

// Constructors
public:
	CPage1();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV support

// Message maps
protected:
	
	DECLARE_MESSAGE_MAP()
public:
	CString val1;
	afx_msg void Onadd();
};
