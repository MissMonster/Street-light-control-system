#if !defined(AFX_CHANGENAME_H__06071E88_5D33_401A_B6E4_1AC423DBDFA2__INCLUDED_)
#define AFX_CHANGENAME_H__06071E88_5D33_401A_B6E4_1AC423DBDFA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// changename.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// changename dialog

class changename : public CDialog
{
// Construction
public:
	changename(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(changename)
	enum { IDD = IDD_changename };
	CEdit	m_newname;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(changename)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(changename)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGENAME_H__06071E88_5D33_401A_B6E4_1AC423DBDFA2__INCLUDED_)
