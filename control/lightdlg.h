#if !defined(AFX_LIGHTDLG_H__165F3BB3_1917_41FB_A224_52CFAB3A7326__INCLUDED_)
#define AFX_LIGHTDLG_H__165F3BB3_1917_41FB_A224_52CFAB3A7326__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// lightdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// lightdlg dialog

class lightdlg : public CDialog
{
// Construction
public:
	lightdlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(lightdlg)
	enum { IDD = IDD_lightdlg };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(lightdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(lightdlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTDLG_H__165F3BB3_1917_41FB_A224_52CFAB3A7326__INCLUDED_)
