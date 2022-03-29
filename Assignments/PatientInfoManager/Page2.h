#pragma once
#include"Header.h"
#include"Page1.h"
// CPage2 dialog

class CPage2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage2)

public:
	CPage2();
	virtual ~CPage2();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	
public:
	CTreeCtrl m_Tree;
	CPage1 p1;
	CMenu m_TreeContextMenu;
	CString m_strStoreImagePath;
	void Setdata(CString&);
	CMap<CString, LPCTSTR, PATIENT, PATIENT&>myMap;
	afx_msg void OnNMRClickTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnAddToTree(WPARAM, LPARAM);
	CImageList m_Image;
	void LoadImageFiles(PATIENT&);
	virtual BOOL OnInitDialog();
	void InsertToTree();
	void ExpandAllItems(HTREEITEM hitem, bool expand = false);
	afx_msg void OnExpandCollapse();
	afx_msg void OnMenuCollapse();
	afx_msg void OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_List1;
	afx_msg void OnBnClickedSavedata();
	afx_msg void OnBnClickedRetrievedata();
	afx_msg void OnBnClickedExit();
	
	CStringArray arr;
	bool SetTransferMode();
	void ParseSharedData(CString csBuffer);
	CWnd* m_pParentWnd;

	bool AcceptConnection();
	bool ReceiveData();
	bool SendDataToSocket(const PATIENT& stPatInfo_i);

	inline void SetParent(CWnd* pParentWnd_i)
	{
		m_pParentWnd = pParentWnd_i;
	}
	LRESULT OnNewItemNotification(WPARAM wParam_i, LPARAM lParam_i);
	CListCtrl m_List3;
};
