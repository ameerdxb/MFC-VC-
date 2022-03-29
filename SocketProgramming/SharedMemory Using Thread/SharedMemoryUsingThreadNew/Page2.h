#pragma once
//class MySocket;
#include "afxcmn.h"
#include "Resource.h"




// CPage2 dialog

class CPage2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage2)

public:
	LRESULT OnNewItemNotification(WPARAM wParam_i, LPARAM lParam_i);
	CPage2();
	virtual ~CPage2();

// Dialog Data
 	enum {IDD = IDD_DIALOG2  };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
     afx_msg LRESULT onRecieve2(WPARAM,LPARAM);
	 
	DECLARE_MESSAGE_MAP()
public:



	CMap<CString,LPCTSTR,PERSON,PERSON> myMap;
	CTreeCtrl m_tree;
	void insertToTree(void);
	bool SetTransferMode();
	void ParseSharedData(CString csBuffer);
	CWnd* m_pParentWnd;

	bool AcceptConnection();
	bool ReceiveData();
	bool SendDataToSocket(const PERSON& stPatInfo_i);

	inline void SetParent(CWnd* pParentWnd_i)
	{
		m_pParentWnd = pParentWnd_i;
	}
};
