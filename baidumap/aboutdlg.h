#if !defined(AFX_ABOUTDLG_H__210C1568_B222_4F65_B136_75B3F50322DA__INCLUDED_)
#define AFX_ABOUTDLG_H__210C1568_B222_4F65_B136_75B3F50322DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// aboutdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// aboutdlg dialog

class aboutdlg : public CDialog
{
// Construction
public:
	aboutdlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(aboutdlg)
	enum { IDD = IDD_DIALOG3 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(aboutdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(aboutdlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTDLG_H__210C1568_B222_4F65_B136_75B3F50322DA__INCLUDED_)
