//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES
#if !defined(AFX_LIGHTDLG_H__165F3BB3_1917_41FB_A224_52CFAB3A7326__INCLUDED_)
#define AFX_LIGHTDLG_H__165F3BB3_1917_41FB_A224_52CFAB3A7326__INCLUDED_

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
	enum { IDD = IDD_lightdlg };
	CListCtrl	m_lightlist;
	CEdit	m_streetlightBrightness;
	CEdit	m_end;
	CEdit	m_start;
	CEdit	m_controllerInfo;
	CComboBox	m_controld;
	CWebBrowser2	m_web;
	CWebPage web;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(lightdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void showalllightinfo();
	void Onaddcontrol();

	// Generated message map functions
	//{{AFX_MSG(lightdlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTDLG_H__165F3BB3_1917_41FB_A224_52CFAB3A7326__INCLUDED_)
