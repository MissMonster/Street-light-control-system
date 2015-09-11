//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES
#if !defined(AFX_CONTROLMANAGE_H__6831B0E8_33C5_48F7_8093_DBD4A5A68364__INCLUDED_)
#define AFX_CONTROLMANAGE_H__6831B0E8_33C5_48F7_8093_DBD4A5A68364__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// controlmanage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// controlmanage dialog

class controlmanage : public CDialog
{
// Construction
public:
	controlmanage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(controlmanage)
	enum { IDD = IDD_controldlg };
	CComboBox	m_controllerAutorun;
	CEdit	m_tempThreadholdLow;
	CEdit	m_tempThreadholdHigh;
	CEdit	m_currentThreadholdLow;
	CEdit	m_currentThreadholdHigh;
	CEdit	m_voltageThreadholdLow;
	CEdit	m_voltageThreadholdHigh;
	CEdit	m_controllerLatitude;
	CEdit	m_controllerLongitude;
	CEdit	m_streetlightNum;
	CEdit	m_controllerInfo;
	CEdit	m_controllerId;
	CComboBox	m_controld;
	CWebBrowser2	m_web;
	CWebPage web;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(controlmanage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Onaddcontrol();

	// Generated message map functions
	//{{AFX_MSG(controlmanage)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton1();
	afx_msg void OnButton2();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLMANAGE_H__6831B0E8_33C5_48F7_8093_DBD4A5A68364__INCLUDED_)
