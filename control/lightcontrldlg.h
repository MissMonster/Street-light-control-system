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
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(lightcontrldlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(lightcontrldlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTCONTRLDLG_H__289A42D7_C9F5_4990_B8CA_BDF21155D354__INCLUDED_)
