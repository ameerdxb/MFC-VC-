
// ThreadSearchFilesView.cpp : implementation of the CThreadSearchFilesView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ThreadSearchFiles.h"
#endif

#include "ThreadSearchFilesDoc.h"
#include "ThreadSearchFilesView.h"
#include"MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CString str;

// CThreadSearchFilesView

IMPLEMENT_DYNCREATE(CThreadSearchFilesView, CFormView)

BEGIN_MESSAGE_MAP(CThreadSearchFilesView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CThreadSearchFilesView::OnBnClickedButton1)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON2, &CThreadSearchFilesView::OnBnClickedButton2)
END_MESSAGE_MAP()

// CThreadSearchFilesView construction/destruction

CThreadSearchFilesView::CThreadSearchFilesView()
	: CFormView(CThreadSearchFilesView::IDD)
{
	// TODO: add construction code here

}

CThreadSearchFilesView::~CThreadSearchFilesView()
{
}

void CThreadSearchFilesView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
}

BOOL CThreadSearchFilesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CThreadSearchFilesView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CThreadSearchFilesView diagnostics

#ifdef _DEBUG
void CThreadSearchFilesView::AssertValid() const
{
	CFormView::AssertValid();
}

void CThreadSearchFilesView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CThreadSearchFilesDoc* CThreadSearchFilesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CThreadSearchFilesDoc)));
	return (CThreadSearchFilesDoc*)m_pDocument;
}
#endif //_DEBUG

void EnumerateFolders(CString strFile, LPVOID param)
{
	CThreadSearchFilesView *pview = (CThreadSearchFilesView *)param;
	WIN32_FIND_DATA file;
	CString csStrFoundFilePath;
	CString csStrFilePath;
	CString csStrTheNameOfTheFile;
	CString csStrPathToSearch = strFile;
	HANDLE hFile = FindFirstFile((csStrPathToSearch + "\\*.*"), &file);
	Sleep(1000);


	do
	{
		csStrTheNameOfTheFile = file.cFileName;
		
		if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
		{
			if ((csStrTheNameOfTheFile != L".") && (csStrTheNameOfTheFile != L".."))
			{
				pview->m_List.AddString(csStrTheNameOfTheFile);
				str = csStrTheNameOfTheFile;
				EnumerateFolders(csStrPathToSearch + L"\\" + csStrTheNameOfTheFile, param);
			}

		}


	} while (FindNextFile(hFile, &file));
}
// CThreadSearchFilesView message handlers
UINT _cdecl Search(LPVOID lparam)
{/*
	CThreadSearchFilesView *pview = (CThreadSearchFilesView *)lparam;
	pview->m_List.AddString(L"Hello");

	HANDLE hFile;
	WIN32_FIND_DATA fd;
	hFile = FindFirstFile(L"*.*", &fd);
	

	do
	{
		pview->m_List.AddString(fd.cFileName);
		pview->strpath = fd.cFileName;
		Sleep(1000);
	 } while (FindNextFile(hFile, &fd));
*/
	EnumerateFolders(L"E:\\", lparam);

	return 0;
}

void CThreadSearchFilesView::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	AfxBeginThread(Search, this);
	/*CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetPaneText(1, str);*/
	
}


void CThreadSearchFilesView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	x1 = point.x;
	y1 = point.y;
	CFormView::OnLButtonDown(nFlags, point);
}


void CThreadSearchFilesView::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	// TODO: Add your message handler code here and/or call default
	if (nFlags & MK_LBUTTON)
	{
		x2 = point.x;
		y2 = point.y;
		dc.MoveTo(x1, y1);
		dc.LineTo(x2, y2);

	}
	x1 = x2;
	y1 = y2;

	CFormView::OnMouseMove(nFlags, point);
}


void CThreadSearchFilesView::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here

}
