// googlemap.h : main header file for the GOOGLEMAP application
//

#if !defined(AFX_GOOGLEMAP_H__D2D695A8_1793_48C5_A5C9_4E8CD628C113__INCLUDED_)
#define AFX_GOOGLEMAP_H__D2D695A8_1793_48C5_A5C9_4E8CD628C113__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGooglemapApp:
// See googlemap.cpp for the implementation of this class
//

class CGooglemapApp : public CWinApp
{
public:
	CGooglemapApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGooglemapApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGooglemapApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOOGLEMAP_H__D2D695A8_1793_48C5_A5C9_4E8CD628C113__INCLUDED_)
