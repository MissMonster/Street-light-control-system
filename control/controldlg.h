// controlDlg.h : header file
//

#if !defined(AFX_CONTROLDLG_H__5474CAE8_EB86_4975_83F5_C717FBF5AF94__INCLUDED_)
#define AFX_CONTROLDLG_H__5474CAE8_EB86_4975_83F5_C717FBF5AF94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CControlDlg dialog

class CControlDlg : public CDialog
{
// Construction
public:
	CControlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CControlDlg)
	enum { IDD = IDD_CONTROL_DIALOG };
	CEdit	m_sync_text;
	CListCtrl	m_list2;
	CListCtrl	m_list1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	static DWORD WINAPI Threadsyncdate(LPVOID channel);
	void setsynctext(char str[]);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CControlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnMenuitem32771();
	afx_msg void OnMenuitem32772();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnMenuitem32773();
	afx_msg void OnMenuitem32774();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLDLG_H__5474CAE8_EB86_4975_83F5_C717FBF5AF94__INCLUDED_)
