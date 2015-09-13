//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES
#if !defined(AFX_SENSORDLG_H__C92A39DB_2F7D_4B5C_BCD4_B22533F17D92__INCLUDED_)
#define AFX_SENSORDLG_H__C92A39DB_2F7D_4B5C_BCD4_B22533F17D92__INCLUDED_

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
	enum { IDD = IDD_sensordlg };
	CListCtrl	m_sensorlist;
	CComboBox	m_sensor;
	CWebBrowser2	m_web;
	CWebPage web;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(sensordlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(sensordlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENSORDLG_H__C92A39DB_2F7D_4B5C_BCD4_B22533F17D92__INCLUDED_)
