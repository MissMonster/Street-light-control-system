#if !defined(AFX_LAND_H__0CA7EE6F_0CB9_4E24_8E53_A10773B36212__INCLUDED_)
#define AFX_LAND_H__0CA7EE6F_0CB9_4E24_8E53_A10773B36212__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// land.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// land dialog

class land : public CDialog
{
// Construction
public:
	land(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(land)
	enum { IDD = IDD_LANDED };
	CEdit	m_password;
	CEdit	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(land)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(land)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAND_H__0CA7EE6F_0CB9_4E24_8E53_A10773B36212__INCLUDED_)
