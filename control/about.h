#if !defined(AFX_ABOUT_H__DD6599B9_B364_400F_8400_F542D6722113__INCLUDED_)
#define AFX_ABOUT_H__DD6599B9_B364_400F_8400_F542D6722113__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// about.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// about dialog

class about : public CDialog
{
// Construction
public:
	about(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(about)
	enum { IDD = IDD_ABOUT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(about)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(about)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUT_H__DD6599B9_B364_400F_8400_F542D6722113__INCLUDED_)
