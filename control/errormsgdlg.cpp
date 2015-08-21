// errormsgdlg.cpp : implementation file
//

#include "stdafx.h"
#include "LampServer.h"
#include "errormsgdlg.h"
//#include "webbrowser3.h"
//#include "WebPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// errormsgdlg dialog


errormsgdlg::errormsgdlg(CWnd* pParent /*=NULL*/)
	: CDialog(errormsgdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(errormsgdlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void errormsgdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(errormsgdlg)
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_EXPLORER1, m_web);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(errormsgdlg, CDialog)
	//{{AFX_MSG_MAP(errormsgdlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// errormsgdlg message handlers

BOOL errormsgdlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CString path;
    GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
    path.ReleaseBuffer();
    int pos = path.ReverseFind('\\');
    path = path.Left(pos);
	path+="\\baidumap.html";
	m_web.Navigate(path, NULL, NULL, NULL, NULL);

	web.SetDocument(m_web.GetDocument());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void errormsgdlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}
