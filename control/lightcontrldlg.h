//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES
#if !defined(AFX_LIGHTCONTRLDLG_H__289A42D7_C9F5_4990_B8CA_BDF21155D354__INCLUDED_)
#define AFX_LIGHTCONTRLDLG_H__289A42D7_C9F5_4990_B8CA_BDF21155D354__INCLUDED_

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
	enum { IDD = IDD_lightcontrldlg };
	CEdit	m_lightnum;
	CEdit	m_controllerInfo;
	CEdit	m_Latitude;
	CEdit	m_Longitude;
	CEdit	m_streetlightBrightness;
	CEdit	m_streetlightTemp;
	CEdit	m_streetlightCurrent;
	CEdit	m_streetlightVoltage;
	CComboBox	m_streetlightId;
	CComboBox	m_controllerId;
	CWebBrowser2	m_web;
	CWebPage web;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(lightcontrldlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void showalllight();
	void showallcontrol();

	// Generated message map functions
	//{{AFX_MSG(lightcontrldlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton3();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnSelchangeCombo2();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton4();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTCONTRLDLG_H__289A42D7_C9F5_4990_B8CA_BDF21155D354__INCLUDED_)
