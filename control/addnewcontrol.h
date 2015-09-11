#if !defined(AFX_ADDNEWCONTROL_H__6FCE46BF_2B11_4D4A_BA15_E2CA9AA2C21A__INCLUDED_)
#define AFX_ADDNEWCONTROL_H__6FCE46BF_2B11_4D4A_BA15_E2CA9AA2C21A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// addnewcontrol.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// addnewcontrol dialog

class addnewcontrol : public CDialog
{
// Construction
public:
	addnewcontrol(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(addnewcontrol)
	enum { IDD = IDD_addnewcontrol };
	CComboBox	m_controllerAutorun;
	CEdit	m_streetlightNum;
	CEdit	m_controllerLatitude;
	CEdit	m_controllerLongitude;
	CEdit	m_controllerInfo;
	CEdit	m_controllerId;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(addnewcontrol)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(addnewcontrol)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDNEWCONTROL_H__6FCE46BF_2B11_4D4A_BA15_E2CA9AA2C21A__INCLUDED_)
