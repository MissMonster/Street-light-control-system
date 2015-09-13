//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES
#if !defined(AFX_ERRORMSGDLG_H__5F877A72_5BD8_4400_A65D_C8419069D1A1__INCLUDED_)
#define AFX_ERRORMSGDLG_H__5F877A72_5BD8_4400_A65D_C8419069D1A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// errormsgdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// errormsgdlg dialog

class errormsgdlg : public CDialog
{
// Construction
public:
	errormsgdlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(errormsgdlg)
	enum { IDD = IDD_errormsgdlg };
	CListCtrl	m_errorinfo;
	CWebBrowser2	m_web;
	CWebPage web;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(errormsgdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void showallerror();

	// Generated message map functions
	//{{AFX_MSG(errormsgdlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuitem32779();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERRORMSGDLG_H__5F877A72_5BD8_4400_A65D_C8419069D1A1__INCLUDED_)
