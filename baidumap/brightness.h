#if !defined(AFX_BRIGHTNESS_H__2A26EC40_261D_43FC_A2E1_1129019085A5__INCLUDED_)
#define AFX_BRIGHTNESS_H__2A26EC40_261D_43FC_A2E1_1129019085A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// brightness.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// brightness dialog

class brightness : public CDialog
{
// Construction
public:
	brightness(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(brightness)
	enum { IDD = IDD_DIALOG4 };
	CSliderCtrl	m_slider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(brightness)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(brightness)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BRIGHTNESS_H__2A26EC40_261D_43FC_A2E1_1129019085A5__INCLUDED_)
