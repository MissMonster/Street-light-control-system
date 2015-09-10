#if !defined(AFX_USERCONTROL_H__9B27A62C_8841_4499_8F99_0AEF443E4FA2__INCLUDED_)
#define AFX_USERCONTROL_H__9B27A62C_8841_4499_8F99_0AEF443E4FA2__INCLUDED_

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
	enum { IDD = IDD_usercontrol };
	CComboBox	m_newjurisdiction;
	CEdit	m_newpassword;
	CEdit	m_newname;
	CEdit	m_usernum;
	CListCtrl	m_userlist;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(usercontrol)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void deleteuser(string name);
	void syncuserinfo();

	// Generated message map functions
	//{{AFX_MSG(usercontrol)
	virtual BOOL OnInitDialog();
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenudeluser();
	afx_msg void Onadduser();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERCONTROL_H__9B27A62C_8841_4499_8F99_0AEF443E4FA2__INCLUDED_)
