#if !defined(AFX_MAINDLG_H__C857D205_7EA9_4695_926E_FF2AD7537EBD__INCLUDED_)
#define AFX_MAINDLG_H__C857D205_7EA9_4695_926E_FF2AD7537EBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// maindlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// maindlg dialog

class maindlg : public CDialog
{
// Construction
public:
	maindlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(maindlg)
	enum { IDD = IDD_MAIN };
	CListCtrl	m_list2;
	CListCtrl	m_list1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(maindlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(maindlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton4();
	afx_msg void OnButton10();
	afx_msg void OnButton11();
	afx_msg void OnMenuitem32781();
	afx_msg void OnButton12();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__C857D205_7EA9_4695_926E_FF2AD7537EBD__INCLUDED_)
