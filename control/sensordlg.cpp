// sensordlg.cpp : implementation file
//

#include "stdafx.h"
#include "LampServer.h"
#include "sensordlg.h"
//#include "webbrowser3.h"
//#include "WebPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// sensordlg dialog


sensordlg::sensordlg(CWnd* pParent /*=NULL*/)
	: CDialog(sensordlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(sensordlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void sensordlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(sensordlg)
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_EXPLORER1, m_web);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(sensordlg, CDialog)
	//{{AFX_MSG_MAP(sensordlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// sensordlg message handlers

BOOL sensordlg::OnInitDialog() 
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

void sensordlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}
