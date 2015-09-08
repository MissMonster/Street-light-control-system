#if !defined(AFX_CONTROLMANAGE_H__6831B0E8_33C5_48F7_8093_DBD4A5A68364__INCLUDED_)
#define AFX_CONTROLMANAGE_H__6831B0E8_33C5_48F7_8093_DBD4A5A68364__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// controlmanage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// controlmanage dialog

class controlmanage : public CDialog
{
// Construction
public:
	controlmanage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(controlmanage)
	enum { IDD = IDD_controldlg };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(controlmanage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(controlmanage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLMANAGE_H__6831B0E8_33C5_48F7_8093_DBD4A5A68364__INCLUDED_)
