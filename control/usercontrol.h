#if !defined(AFX_USERCONTROL_H__3048E473_9596_42E3_877C_4A79D97DE287__INCLUDED_)
#define AFX_USERCONTROL_H__3048E473_9596_42E3_877C_4A79D97DE287__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// usercontrol.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// usercontrol dialog

class usercontrol : public CDialog
{
// Construction
public:
	usercontrol(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(usercontrol)
	enum { IDD = IDD_DIALOG6 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(usercontrol)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(usercontrol)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERCONTROL_H__3048E473_9596_42E3_877C_4A79D97DE287__INCLUDED_)
