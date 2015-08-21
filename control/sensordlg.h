//{{AFX_INCLUDES()
#include "webbrowser3.h"
#include "WebPage.h"
//}}AFX_INCLUDES
#if !defined(AFX_SENSORDLG_H__F9D713EB_BBF4_49E3_9ACE_72FE2202CAF7__INCLUDED_)
#define AFX_SENSORDLG_H__F9D713EB_BBF4_49E3_9ACE_72FE2202CAF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// sensordlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// sensordlg dialog

class sensordlg : public CDialog
{
// Construction
public:
	sensordlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(sensordlg)
	enum { IDD = IDD_DIALOG3 };
	CListCtrl	m_list1;
	CWebBrowser2	m_web;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(sensordlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HICON m_hIcon;
	CWebPage web;
	// Generated message map functions
	//{{AFX_MSG(sensordlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENSORDLG_H__F9D713EB_BBF4_49E3_9ACE_72FE2202CAF7__INCLUDED_)
