
// SharedMemoryDlg.h : header file
//

#pragma once
typedef struct
{
	int stNum;
}SHMEM;

// CSharedMemoryDlg dialog
class CSharedMemoryDlg : public CDialogEx
{
// Construction
public:
	CSharedMemoryDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SHAREDMEMORY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int m_Edit;
	afx_msg void OnCreate();
	afx_msg void OnOpen();
	afx_msg void OnUpdate();
	afx_msg void OnDisplay();
	HANDLE m_hSharedMemory;
	SHMEM stObj;
	HANDLE m_hMutex;
	SHMEM* ptr;
};
