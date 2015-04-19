// ClientDlg.h : header file
//

#if !defined(AFX_CLIENTDLG_H__1AE1AF63_940F_40F3_A8C1_E6A4BE7EC096__INCLUDED_)
#define AFX_CLIENTDLG_H__1AE1AF63_940F_40F3_A8C1_E6A4BE7EC096__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_CLIENTMSG (WM_USER+200)//********************************************
/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

class CClientDlg : public CDialog
{
// Construction
public:
	SOCKADDR_IN m_addr;
	SOCKET m_hSocket;
	void OnDestroy();
	CClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClientDlg)
	enum { IDD = IDD_CLIENT_DIALOG };
	CIPAddressCtrl	m_ip;
//	SOCKET m_hSocket;
//	SOCKADDR_IN m_addr;
	CEdit m_Show; 
	CString	m_strShow;
	CString	m_strMsg;
	UINT	m_uPort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg long OnClientMsg(WPARAM wParam, LPARAM lParam); 
	afx_msg void OnButton2();
	afx_msg void OnButton1();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDLG_H__1AE1AF63_940F_40F3_A8C1_E6A4BE7EC096__INCLUDED_)
