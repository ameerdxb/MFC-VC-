// Page2.cpp : implementation file
//

#include "stdafx.h"
#include "SharedMemoryUsingThreadNew.h"
#include "Page2.h"
#include "Resource.h"
#include <tchar.h>

// CPage2 dialog

IMPLEMENT_DYNAMIC(CPage2, CPropertyPage)

CPage2::CPage2()
	: CPropertyPage(CPage2::IDD)
{

}
CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_tree);
}


BEGIN_MESSAGE_MAP(CPage2, CPropertyPage)
	ON_MESSAGE(WM_USER_MSG,onRecieve2)
END_MESSAGE_MAP()


// CPage2 message handlers

LRESULT CPage2::onRecieve2(WPARAM wp,LPARAM lp)
{
	PERSON* per = (PERSON*)lp;
	if(per!=NULL)
	{
	myMap[per->id] = *per;
	}
	insertToTree();
	/*HTREEITEM root = m_tree.InsertItem(per->id);
	m_tree.InsertItem(per->nam,root);*/
	return 0L;
}

void CPage2::insertToTree(void)
{
	m_tree.DeleteAllItems();
	POSITION POS = myMap.GetStartPosition();
	CString str;
	PERSON per;
	while(POS!=NULL)
	{
      myMap.GetNextAssoc(POS,str,per);
	  HTREEITEM root = m_tree.InsertItem(per.id);
	  m_tree.InsertItem(per.nam,root);

	}

}
