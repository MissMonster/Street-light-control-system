// googlemapDlg.h : header file
//
//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES

#if !defined(AFX_GOOGLEMAPDLG_H__E57D1BFE_BD58_4410_A979_420C793E5980__INCLUDED_)
#define AFX_GOOGLEMAPDLG_H__E57D1BFE_BD58_4410_A979_420C793E5980__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGooglemapDlg dialog

class CGooglemapDlg : public CDialog
{
// Construction
public:
	CGooglemapDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGooglemapDlg)
	enum { IDD = IDD_GOOGLEMAP_DIALOG };
	CWebBrowser2	m_map;
	CString	m_lat;
	CString	m_long;
	CString	m_Zoom_Level;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGooglemapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGooglemapDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOOGLEMAPDLG_H__E57D1BFE_BD58_4410_A979_420C793E5980__INCLUDED_)
