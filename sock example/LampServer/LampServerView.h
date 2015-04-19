// LampServerView.h : interface of the CLampServerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAMPSERVERVIEW_H__3A3F5716_E152_4403_81A0_F153449EEEB6__INCLUDED_)
#define AFX_LAMPSERVERVIEW_H__3A3F5716_E152_4403_81A0_F153449EEEB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include<afxtempl.h>
typedef CList<SOCKET,SOCKET&>SOCKET_ARRAY;
#define WM_SERVERMSG (WM_USER+100)//*******************************************



class CLampServerView : public CFormView
{
protected: // create from serialization only
	CLampServerView();
	DECLARE_DYNCREATE(CLampServerView)

public:
	//{{AFX_DATA(CLampServerView)
	enum { IDD = IDD_LAMPSERVER_FORM };
	CEdit m_Show;
	CString	m_strShow;
	CString	m_strMsg;
	//}}AFX_DATA

// Attributes
public:
	CLampServerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLampServerView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDragLeave();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	
	UINT m_uPort;
	SOCKET_ARRAY m_saList;
	SOCKADDR_IN m_addr;
	SOCKET m_hSocket;
	virtual ~CLampServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLampServerView)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg long OnServerMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LampServerView.cpp
inline CLampServerDoc* CLampServerView::GetDocument()
   { return (CLampServerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAMPSERVERVIEW_H__3A3F5716_E152_4403_81A0_F153449EEEB6__INCLUDED_)
