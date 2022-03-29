#pragma once

#ifdef _WIN32_WCE
#error "COlePropertyPage is not supported for Windows CE."
#endif 

// CPAGE : Property page dialog

class CPAGE : public COlePropertyPage
{
	DECLARE_DYNCREATE(CPAGE)
	DECLARE_OLECREATE_EX(CPAGE)

// Constructors
public:
	CPAGE();

// Dialog Data
	enum { IDD = IDD_DIALOG3 };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString val1;
	afx_msg void OnAdd();
};
