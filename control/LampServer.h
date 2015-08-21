// LampServer.h : main header file for the LAMPSERVER application
//

#if !defined(AFX_LAMPSERVER_H__CA495CEF_135B_4DCB_B908_F98B3E045DA8__INCLUDED_)
#define AFX_LAMPSERVER_H__CA495CEF_135B_4DCB_B908_F98B3E045DA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLampServerApp:
// See LampServer.cpp for the implementation of this class
//

class CLampServerApp : public CWinApp
{
public:
	CString m_password;
	CString m_database;
	CString m_username;
	CString m_server;
	CString m_currentUsername;
	CString exePath;
	CLampServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLampServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CLampServerApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAMPSERVER_H__CA495CEF_135B_4DCB_B908_F98B3E045DA8__INCLUDED_)
