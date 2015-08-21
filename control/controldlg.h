//{{AFX_INCLUDES()
#include "webbrowser3.h"
#include "WebPage.h"
//}}AFX_INCLUDES
#if !defined(AFX_CONTROLDLG_H__4ED308D0_742F_49BD_908F_A1E976E4E075__INCLUDED_)
#define AFX_CONTROLDLG_H__4ED308D0_742F_49BD_908F_A1E976E4E075__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// controldlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// controldlg dialog

class controldlg : public CDialog
{
// Construction
public:
	controldlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(controldlg)
	enum { IDD = IDD_DIALOG1 };
	CWebBrowser2	m_web;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(controldlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HICON m_hIcon;
	CWebPage web;
	// Generated message map functions
	//{{AFX_MSG(controldlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLDLG_H__4ED308D0_742F_49BD_908F_A1E976E4E075__INCLUDED_)
