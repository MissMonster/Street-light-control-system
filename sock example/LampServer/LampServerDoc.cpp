// LampServerDoc.cpp : implementation of the CLampServerDoc class
//

#include "stdafx.h"
#include "LampServer.h"

#include "LampServerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLampServerDoc

IMPLEMENT_DYNCREATE(CLampServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CLampServerDoc, CDocument)
	//{{AFX_MSG_MAP(CLampServerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLampServerDoc construction/destruction

CLampServerDoc::CLampServerDoc()
{
	// TODO: add one-time construction code here

}

CLampServerDoc::~CLampServerDoc()
{
}

BOOL CLampServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLampServerDoc serialization

void CLampServerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLampServerDoc diagnostics

#ifdef _DEBUG
void CLampServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLampServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLampServerDoc commands
