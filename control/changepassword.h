#if !defined(AFX_CHANGEPASSWORD_H__E036007A_CB0E_466E_A563_0543A246DB82__INCLUDED_)
#define AFX_CHANGEPASSWORD_H__E036007A_CB0E_466E_A563_0543A246DB82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// changepassword.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// changepassword dialog

class changepassword : public CDialog
{
// Construction
public:
	changepassword(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(changepassword)
	enum { IDD = IDD_changepassword };
	CEdit	m_newpassword2;
	CEdit	m_newpassword1;
	CEdit	m_oldpassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(changepassword)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(changepassword)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGEPASSWORD_H__E036007A_CB0E_466E_A563_0543A246DB82__INCLUDED_)
