#if !defined(AFX_DLGLOGIN_H__924F69E7_4617_4450_81C1_EFEBD7EE6C8A__INCLUDED_)
#define AFX_DLGLOGIN_H__924F69E7_4617_4450_81C1_EFEBD7EE6C8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLogin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin dialog

class CDlgLogin : public CDialog
{
// Construction
public:
	CDlgLogin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLogin)
	enum { IDD = IDD_LOGIN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLogin)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CDlgLogin)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOGIN_H__924F69E7_4617_4450_81C1_EFEBD7EE6C8A__INCLUDED_)
