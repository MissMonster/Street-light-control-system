//{{AFX_INCLUDES()
#include "webbrowser3.h"
#include "WebPage.h"
//}}AFX_INCLUDES
#if !defined(AFX_LIGHTDLG_H__A32B4E20_2DD4_461E_9A36_96D95ACDECDB__INCLUDED_)
#define AFX_LIGHTDLG_H__A32B4E20_2DD4_461E_9A36_96D95ACDECDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// lightdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// lightdlg dialog

class lightdlg : public CDialog
{
// Construction
public:
	lightdlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(lightdlg)
	enum { IDD = IDD_DIALOG2 };
	CListCtrl	m_list2;
	CListCtrl	m_list1;
	CWebBrowser2	m_web;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(lightdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HICON m_hIcon;
	CWebPage web;
	// Generated message map functions
	//{{AFX_MSG(lightdlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTDLG_H__A32B4E20_2DD4_461E_9A36_96D95ACDECDB__INCLUDED_)
