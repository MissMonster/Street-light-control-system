#if !defined(AFX_CONTROLINFO_H__52D12382_DD72_44E5_BD86_8EE7FA602013__INCLUDED_)
#define AFX_CONTROLINFO_H__52D12382_DD72_44E5_BD86_8EE7FA602013__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// controlinfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// controlinfo dialog

class controlinfo : public CDialog
{
// Construction
public:
	controlinfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(controlinfo)
	enum { IDD = IDD_DIALOG2 };
	CComboBox	m_status;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(controlinfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(controlinfo)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLINFO_H__52D12382_DD72_44E5_BD86_8EE7FA602013__INCLUDED_)
