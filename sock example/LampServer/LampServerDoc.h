// LampServerDoc.h : interface of the CLampServerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAMPSERVERDOC_H__F5F54E03_EF33_4BBF_A4ED_DC4F7879B13C__INCLUDED_)
#define AFX_LAMPSERVERDOC_H__F5F54E03_EF33_4BBF_A4ED_DC4F7879B13C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLampServerDoc : public CDocument
{
protected: // create from serialization only
	CLampServerDoc();
	DECLARE_DYNCREATE(CLampServerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLampServerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLampServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLampServerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAMPSERVERDOC_H__F5F54E03_EF33_4BBF_A4ED_DC4F7879B13C__INCLUDED_)
