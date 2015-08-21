//{{AFX_INCLUDES()
#include "webbrowser3.h"
#include "WebPage.h"
//}}AFX_INCLUDES
#if !defined(AFX_LIGHTCONTRLDLG_H__8DDF862A_EB50_47F4_B03A_1674BFC4F8AA__INCLUDED_)
#define AFX_LIGHTCONTRLDLG_H__8DDF862A_EB50_47F4_B03A_1674BFC4F8AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// lightcontrldlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// lightcontrldlg dialog

class lightcontrldlg : public CDialog
{
// Construction
public:
	lightcontrldlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(lightcontrldlg)
	enum { IDD = IDD_DIALOG4 };
	CWebBrowser2	m_web;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(lightcontrldlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HICON m_hIcon;
	CWebPage web;
	// Generated message map functions
	//{{AFX_MSG(lightcontrldlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTCONTRLDLG_H__8DDF862A_EB50_47F4_B03A_1674BFC4F8AA__INCLUDED_)
