// baidumapDlg.h : header file
//
//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES

#if !defined(AFX_BAIDUMAPDLG_H__42FBE1F2_099B_4CD7_9B77_0F7E6468C1A9__INCLUDED_)
#define AFX_BAIDUMAPDLG_H__42FBE1F2_099B_4CD7_9B77_0F7E6468C1A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBaidumapDlg dialog

class CBaidumapDlg : public CDialog
{
// Construction
public:
	CBaidumapDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBaidumapDlg)
	enum { IDD = IDD_BAIDUMAP_DIALOG };
	CListCtrl	m_list;
	CWebBrowser2	m_map;
	CString	m_long;
	CString	m_lat;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaidumapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBaidumapDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BAIDUMAPDLG_H__42FBE1F2_099B_4CD7_9B77_0F7E6468C1A9__INCLUDED_)