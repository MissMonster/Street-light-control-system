// maindlg.cpp : implementation file
//

#include "stdafx.h"
#include "LampServer.h"
#include "maindlg.h"
#include "controldlg.h"
#include "lightdlg.h"
#include "sensordlg.h"
#include "lightcontrldlg.h"
#include "errormsgdlg.h"
#include "usercontrol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// maindlg dialog


maindlg::maindlg(CWnd* pParent /*=NULL*/)
	: CDialog(maindlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(maindlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void maindlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(maindlg)
	DDX_Control(pDX, IDC_LIST2, m_list2);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(maindlg, CDialog)
	//{{AFX_MSG_MAP(maindlg)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
	ON_COMMAND(ID_MENUITEM32781, OnMenuitem32781)
	ON_BN_CLICKED(IDC_BUTTON12, OnButton12)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// maindlg message handlers

void maindlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

BOOL maindlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//设置列表主题
	m_list1.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
        | LVS_EX_FULLROWSELECT		// 允许正航选中
        | LVS_EX_GRIDLINES			// 画出网格线
		);
	
	m_list1.InsertColumn(0,"IP"	,LVCFMT_CENTER, 60,0);
	m_list1.InsertColumn(1,"控制器名称"	,LVCFMT_CENTER, 120,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void maindlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR maindlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//用户管理
void maindlg::OnButton12() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	
	usercontrol dlg;
	dlg.DoModal();
	
	ShowWindow(SW_SHOW);
}

//远端灯控制器管理
void maindlg::OnButton8() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	
	controldlg dlg;
	dlg.DoModal();
	
	ShowWindow(SW_SHOW);
}

//LED路灯监控
void maindlg::OnButton9() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	
	lightdlg dlg;
	dlg.DoModal();
	
	ShowWindow(SW_SHOW);
}

//传感器实时管理
void maindlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	
	sensordlg dlg;
	dlg.DoModal();
	
	ShowWindow(SW_SHOW);
}

//LED路灯控制
void maindlg::OnButton10() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	
	lightcontrldlg dlg;
	dlg.DoModal();
	
	ShowWindow(SW_SHOW);
}

//故障告警信息管理
void maindlg::OnButton11() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	
	errormsgdlg dlg;
	dlg.DoModal();
	
	ShowWindow(SW_SHOW);
}

//exit
void maindlg::OnMenuitem32781() 
{
	// TODO: Add your command handler code here
	OnCancel();
}


