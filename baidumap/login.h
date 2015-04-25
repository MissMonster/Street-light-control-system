#if !defined(AFX_LOGIN_H__B11B6059_8970_4100_8BC6_8D87328BB064__INCLUDED_)
#define AFX_LOGIN_H__B11B6059_8970_4100_8BC6_8D87328BB064__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// login.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// login dialog

class login : public CDialog
{
// Construction
public:
	login(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(login)
	enum { IDD = IDD_DIALOG1 };
	CString	m_user;
	CString	m_password;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(login)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(login)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGIN_H__B11B6059_8970_4100_8BC6_8D87328BB064__INCLUDED_)
