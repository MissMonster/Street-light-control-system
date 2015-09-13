// controlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "controlDlg.h"
#include "about.h"
#include "controlmanage.h"
#include "lightdlg.h"
#include "sensordlg.h"
#include "lightcontrldlg.h"
#include "errormsgdlg.h"
#include "usercontrol.h"
#include "changename.h"
#include "changepassword.h"
#include "mysql/mysql.h"
#include "sqlite3.h"

//////////////////////////////////////////////////////////
//屏蔽输入法
#include <Imm.h>  
#pragma comment(lib,"imm32.lib")
//////////////////////////////////////////////////////////
#pragma comment(lib, "mysql/libmysql.lib")
#pragma comment(lib, "sqlite3.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern struct serverset serverinfo;
extern struct userdata  userinfo;

/////////////////////////////////////////////////////////////////////////////
// CControlDlg dialog

CControlDlg::CControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CControlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CControlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControlDlg)
	DDX_Control(pDX, IDC_EDIT1, m_sync_text);
	DDX_Control(pDX, IDC_LIST2, m_list2);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CControlDlg, CDialog)
	//{{AFX_MSG_MAP(CControlDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENUITEM32771, OnMenuitem32771)
	ON_COMMAND(ID_MENUITEM32772, OnMenuitem32772)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_COMMAND(ID_MENUITEM32773, OnMenuitem32773)
	ON_COMMAND(ID_MENUITEM32774, OnMenuitem32774)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlDlg message handlers

BOOL CControlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CString title="路灯远程控制    登录用户:";
	title+=userinfo.name;
	title+="  用户组:";
	CWnd *pWnd = GetDlgItem(IDC_BUTTON1);
	switch(userinfo.jurisdiction)
	{
	case 1:
		title+="普通用户";
		pWnd->EnableWindow(FALSE);
		break;
	case 2:
		title+="管理员";
		break;
	}
	SetWindowText(title);

	setsynctext("已同步");

	//设置列表主题
	m_list1.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
        | LVS_EX_FULLROWSELECT		// 允许正航选中
        | LVS_EX_GRIDLINES			// 画出网格线
		);
	
	m_list1.InsertColumn(0,"IP"	      ,LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(1,"识别码"	  ,LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(2,"名称"	  ,LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(3,"经度"     ,LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(4,"纬度"     ,LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(5,"路灯数量" ,LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(6,"运行方式" ,LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(7,"电压上限" ,LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(8,"电压下限" ,LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(9,"电流上限" ,LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(10,"电流下限",LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(11,"温度上限",LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(12,"温度下限",LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(13,"故障情况",LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(14,"在线"	  ,LVCFMT_CENTER, 70,0);

	//设置列表主题
	m_list2.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
        | LVS_EX_FULLROWSELECT		// 允许正航选中
        | LVS_EX_GRIDLINES			// 画出网格线
		);
	
	m_list2.InsertColumn(0,"时间"	  ,LVCFMT_CENTER, 70,0);
	m_list2.InsertColumn(1,"设备类型" ,LVCFMT_CENTER, 70,0);
	m_list2.InsertColumn(2,"标识码"	  ,LVCFMT_CENTER, 70,0);
	m_list2.InsertColumn(3,"路灯编号" ,LVCFMT_CENTER, 70,0);
	m_list2.InsertColumn(4,"类型"	  ,LVCFMT_CENTER, 70,0);
	m_list2.InsertColumn(5,"电压"	  ,LVCFMT_CENTER, 70,0);
	m_list2.InsertColumn(6,"电流"	  ,LVCFMT_CENTER, 70,0);
	m_list2.InsertColumn(7,"温度"     ,LVCFMT_CENTER, 70,0);
	m_list2.InsertColumn(8,"经度"	  ,LVCFMT_CENTER, 70,0);
	m_list2.InsertColumn(9,"纬度"	  ,LVCFMT_CENTER, 70,0);
	m_list2.InsertColumn(10,"信息"    ,LVCFMT_CENTER, 70,0);
	m_list2.InsertColumn(11,"处理情况",LVCFMT_CENTER, 70,0);

	//创建更新线程
	//DWORD dwThreadID = NULL;
	//HANDLE hThread=CreateThread(NULL,0,CControlDlg::Threadsyncdate,NULL,NULL,(LPDWORD)&dwThreadID);

	synccontrollerinfo();
	syncerrorinfo();

	SetTimer(1,1000,NULL);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CControlDlg::OnPaint() 
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
HCURSOR CControlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CControlDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CControlDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

//退出
void CControlDlg::OnMenuitem32771() 
{
	// TODO: Add your command handler code here
	CDialog::OnCancel();
}

//关于
void CControlDlg::OnMenuitem32772() 
{
	// TODO: Add your command handler code here
	about dlg;
	dlg.DoModal();
}

//用户管理
void CControlDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	//////////////////////////////////////////////////////////////////////////
	//要啥权限啊,好好的自行车不用
	//if(userinfo.jurisdiction!=2)
	//{
	//	MessageBox("没有权限!");
	//	return ;
	//}
	//////////////////////////////////////////////////////////////////////////

	ShowWindow(SW_HIDE);
	
	usercontrol dlg;
	dlg.DoModal();
	
	ShowWindow(SW_SHOW);
}

//远端灯控制器管理
void CControlDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	
	controlmanage dlg;
	dlg.DoModal();
	
	ShowWindow(SW_SHOW);
}

//LED路灯监控
void CControlDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	
	lightdlg dlg;
	dlg.DoModal();
	
	ShowWindow(SW_SHOW);
}

//传感器实时管理
void CControlDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	
	sensordlg dlg;
	dlg.DoModal();
	
	ShowWindow(SW_SHOW);
}

//LED路灯控制
void CControlDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	
	lightcontrldlg dlg;
	dlg.DoModal();
	
	ShowWindow(SW_SHOW);
}

//故障告警信息管理
void CControlDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	
	errormsgdlg dlg;
	dlg.DoModal();
	
	ShowWindow(SW_SHOW);
}

void CControlDlg::OnMenuitem32773() 
{
	// TODO: Add your command handler code here
	changepassword dlg;
	dlg.DoModal();
}

void CControlDlg::OnMenuitem32774() 
{
	// TODO: Add your command handler code here
	changename dlg;
	dlg.DoModal();
}

void CControlDlg::setsynctext(char str[])
{
	m_sync_text.SetWindowText(str);
}

//更新缓存
DWORD WINAPI CControlDlg::Threadsyncdate(LPVOID channel)
{
	return 0;
}

//定时器
void CControlDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//////////////////////////////////////////////////////////////////////////
	//卧槽,这方法写了几遍了都
	static int flage=-1;//同步标志
	switch(nIDEvent)
	{
	case 1:
		time_t rawtime;
		struct tm * timeinfo;
		time(&rawtime);
		timeinfo=localtime(&rawtime);
		if(flage&&timeinfo->tm_min%10==6)
		{
			setsynctext("同步中");
			synccontrollerinfo();
			syncerrorinfo();
			
			flage=0;
		}
		else
		{
			setsynctext("已同步");
			if(timeinfo->tm_min%10!=6)
			{
				flage=1;
			}
		}
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}

//同步控制器信息
void CControlDlg::synccontrollerinfo()
{
	MYSQL_RES *res;     //查询结果集
	MYSQL_ROW column;   //数据行的列
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("数据库无法连接!");
	}
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	
	//////////////////////////////////////////////////////////
	//同步t_controllerinfo
	if(mysql_query(&mysql,"select * from t_controllerinfo")==NULL)
	{
		res=mysql_store_result(&mysql);//保存查询到的数据到result
		
		int j=mysql_num_fields(res);
		int index=0;
		m_list1.DeleteAllItems();
		while(column=mysql_fetch_row(res))//获取具体的数据
		{
			m_list1.InsertItem(index,column[0]);
			for(int i=1;i<j;i++)
			{
				m_list1.SetItemText(index,i,column[i]);
			}
			index++;
		}
	}
	mysql_close(&mysql);
}

//同步错误信息
void CControlDlg::syncerrorinfo()
{
	MYSQL_RES *res;     //查询结果集
	MYSQL_ROW column;   //数据行的列
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("数据库无法连接!");
	}
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	
	//////////////////////////////////////////////////////////
	//同步t_errorinfo
	if(mysql_query(&mysql,"select * from t_errorinfo")==NULL)
	{
		res=mysql_store_result(&mysql);//保存查询到的数据到result
		
		int j=mysql_num_fields(res);
		int index=0;
		m_list2.DeleteAllItems();
		while(column=mysql_fetch_row(res))//获取具体的数据
		{
			m_list2.InsertItem(index,column[0]);
			for(int i=1;i<j;i++)
			{
				m_list2.SetItemText(index,i,column[i]);
			}
			index++;
		}
	}
	mysql_close(&mysql);
}
