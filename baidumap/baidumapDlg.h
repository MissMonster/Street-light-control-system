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
	CListCtrl	m_list_error;
	CListCtrl	m_list_light;
	CListCtrl	m_list;
	CWebBrowser2	m_map;
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
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuitem32777();
	afx_msg void OnMenuitem32773();
	afx_msg void OnMenuitem32774();
	afx_msg void OnMenuitem32775();
	afx_msg void OnMenuitem32776();
	afx_msg void OnMenuitem32784();
	afx_msg void OnMenuitem32791();
	afx_msg void OnMenuitem32792();
	afx_msg void OnDblclkList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuitem32802();
	afx_msg void OnMenuitem32800();
	afx_msg void OnMenuitem32781();
	afx_msg void OnMenuitem32780();
	virtual void OnOK();
	afx_msg void OnMenuitem32794();
	afx_msg void OnMenuitem32795();
	afx_msg void OnMenuitem32796();
	afx_msg void OnMenuitem32797();
	afx_msg void OnMenuitem32798();
	afx_msg void OnMenuitem32799();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BAIDUMAPDLG_H__42FBE1F2_099B_4CD7_9B77_0F7E6468C1A9__INCLUDED_)
