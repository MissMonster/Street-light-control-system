#if !defined(AFX_NEWUSERMESSAGE_H__D693ADF3_E5D0_4D27_96B0_993ECB71194A__INCLUDED_)
#define AFX_NEWUSERMESSAGE_H__D693ADF3_E5D0_4D27_96B0_993ECB71194A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// newusermessage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// newusermessage dialog

class newusermessage : public CDialog
{
// Construction
public:
	newusermessage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(newusermessage)
	enum { IDD = IDD_DIALOG5 };
	CString	m_newname;
	CString	m_newpassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(newusermessage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(newusermessage)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWUSERMESSAGE_H__D693ADF3_E5D0_4D27_96B0_993ECB71194A__INCLUDED_)
