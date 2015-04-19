// baidumap.h : main header file for the BAIDUMAP application
//

#if !defined(AFX_BAIDUMAP_H__6095CE58_DF1B_400B_9FCB_5B16204934F8__INCLUDED_)
#define AFX_BAIDUMAP_H__6095CE58_DF1B_400B_9FCB_5B16204934F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBaidumapApp:
// See baidumap.cpp for the implementation of this class
//

class CBaidumapApp : public CWinApp
{
public:
	CBaidumapApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaidumapApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBaidumapApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BAIDUMAP_H__6095CE58_DF1B_400B_9FCB_5B16204934F8__INCLUDED_)
