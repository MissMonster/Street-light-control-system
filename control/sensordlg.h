#if !defined(AFX_SENSORDLG_H__C92A39DB_2F7D_4B5C_BCD4_B22533F17D92__INCLUDED_)
#define AFX_SENSORDLG_H__C92A39DB_2F7D_4B5C_BCD4_B22533F17D92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// sensordlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// sensordlg dialog

class sensordlg : public CDialog
{
// Construction
public:
	sensordlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(sensordlg)
	enum { IDD = IDD_sensordlg };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(sensordlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(sensordlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENSORDLG_H__C92A39DB_2F7D_4B5C_BCD4_B22533F17D92__INCLUDED_)
