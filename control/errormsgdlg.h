//{{AFX_INCLUDES()
#include "webbrowser3.h"
#include "WebPage.h"
//}}AFX_INCLUDES
#if !defined(AFX_ERRORMSGDLG_H__333D73DB_2A21_4E3D_9119_9610616A141F__INCLUDED_)
#define AFX_ERRORMSGDLG_H__333D73DB_2A21_4E3D_9119_9610616A141F__INCLUDED_

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
	enum { IDD = IDD_DIALOG5 };
	CListCtrl	m_list1;
	CWebBrowser2	m_web;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(errormsgdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HICON m_hIcon;
	CWebPage web;
	// Generated message map functions
	//{{AFX_MSG(errormsgdlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERRORMSGDLG_H__333D73DB_2A21_4E3D_9119_9610616A141F__INCLUDED_)
