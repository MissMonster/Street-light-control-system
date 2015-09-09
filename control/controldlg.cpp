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

int flage=-1;//同步标志

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
	switch(userinfo.jurisdiction)
	{
	case 1:
		title+="普通用户";
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
	
	m_list1.InsertColumn(0,"IP"	     ,LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(1,"识别码"	 ,LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(2,"名称"	 ,LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(3,"路灯数量",LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(4,"运行方式",LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(5,"经度"	 ,LVCFMT_CENTER, 70,0);
	m_list1.InsertColumn(6,"纬度"	 ,LVCFMT_CENTER, 70,0);

	//设置列表主题
	m_list2.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
        | LVS_EX_FULLROWSELECT		// 允许正航选中
        | LVS_EX_GRIDLINES			// 画出网格线
		);
	
	m_list2.InsertColumn(0,"时间"	 ,LVCFMT_CENTER, 70,0);
	m_list2.InsertColumn(1,"控制器"	 ,LVCFMT_CENTER, 70,0);
	m_list2.InsertColumn(2,"路灯号"	 ,LVCFMT_CENTER, 70,0);
	m_list2.InsertColumn(3,"故障原因",LVCFMT_CENTER, 70,0);
	m_list2.InsertColumn(4,"处理情况",LVCFMT_CENTER, 70,0);

	//创建更新线程
	DWORD dwThreadID = NULL;
	HANDLE hThread=CreateThread(NULL,0,CControlDlg::Threadsyncdate,NULL,NULL,(LPDWORD)&dwThreadID);

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
	if(userinfo.jurisdiction!=2)
	{
		MessageBox("没有权限!");
		return ;
	}

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
	MYSQL_RES *res;     //查询结果集
	MYSQL_ROW column;   //数据行的列
	MYSQL mysql;
	sqlite3* db ;
	time_t rawtime;
	struct tm * timeinfo;
	
	//////////////////////////////////////////////////////////
	//又用到了统计字符串算法
	//算法详见https://github.com/707wk/Senior-middle-school/blob/master/Filling%20in%20the%20gaps.c
	//////////////////////////////////////////////////////////
	for(;;)
	{
		time(&rawtime);
		timeinfo=localtime(&rawtime);
		if(flage&&timeinfo->tm_min%10==6)
		{
			flage=2;
			mysql_init(&mysql);
			if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
			{
				AfxMessageBox("数据库无法连接!");
				return 0;
			}
			/*
			if(fopen("cache.db","r")==NULL)
			{
				AfxMessageBox("未找到本地数据库!",NULL,MB_OK);
				return 0;
			}
			int result=sqlite3_open("cache.db",&db);
			if(result!=SQLITE_OK)
			{
				AfxMessageBox("本地数据库连接失败!",NULL,MB_OK);
				return 0;
			}
			*/
			mysql_query(&mysql,"SET NAMES 'UTF-8'");

			//////////////////////////////////////////////////////////
			//同步t_controllerinfo
			if(mysql_query(&mysql,"select * from t_controllerinfo")==NULL)
			{
				res=mysql_store_result(&mysql);//保存查询到的数据到result

				int j=mysql_num_fields(res);
				while(column=mysql_fetch_row(res))//获取具体的数据
				{
					//CString str="replace into t_controllerinfo values(";
					for(int i=0;i<j;i++)
					{
						/*
						//str+=column[i];
						char tmp[100];
						if(i<j-1)
						{
							sprintf(tmp,"%s",column[i]);
							if(strcmp("(null)",tmp))
							{
								sprintf(tmp,"'%s',",column[i]);
							}
							else
							{
								strcpy(tmp,"null,");
							}
						}
						else 
						{
							sprintf(tmp,"'%s');",column[i]);
						}
						//AfxMessageBox(tmp);
						str+=tmp;
						//str+=column[i];
						*/
					}
					//AfxMessageBox(str);
					//char* errMsg;
					/*
					if(SQLITE_OK!=sqlite3_exec(db,str.GetBuffer(0),0,0,NULL))
					{
						AfxMessageBox("插入错误",NULL,MB_OK);
					}
					*/
					//break;
				}
			}
			//////////////////////////////////////////////////////////
/*
			//////////////////////////////////////////////////////////
			//同步t_errorinfo
			if(mysql_query(&mysql,"select * from t_errorinfo")==NULL)
			{
				res=mysql_store_result(&mysql);//保存查询到的数据到result

				int j=mysql_num_fields(res);
				while(column=mysql_fetch_row(res))//获取具体的数据
				{
					CString str="replace into t_errorinfo values(";
					for(int i=0;i<j;i++)
					{
						//str+=column[i];
						char tmp[100];
						if(i<j-1)
						{
							sprintf(tmp,"%s",column[i]);
							if(strcmp("(null)",tmp))
							{
								sprintf(tmp,"'%s',",column[i]);
							}
							else
							{
								strcpy(tmp,"null,");
							}
						}
						else 
						{
							sprintf(tmp,"'%s');",column[i]);
						}
						//AfxMessageBox(tmp);
						str+=tmp;
						//str+=column[i];
					}
					//AfxMessageBox(str);
					//char* errMsg;
					if(SQLITE_OK!=sqlite3_exec(db,str.GetBuffer(0),0,0,NULL))
					{
						AfxMessageBox("插入错误",NULL,MB_OK);
					}
					//break;
				}
			}
			//////////////////////////////////////////////////////////

			//////////////////////////////////////////////////////////
			//同步t_lightlocation
			if(mysql_query(&mysql,"select * from t_lightlocation")==NULL)
			{
				res=mysql_store_result(&mysql);//保存查询到的数据到result

				int j=mysql_num_fields(res);
				while(column=mysql_fetch_row(res))//获取具体的数据
				{
					CString str="replace into t_lightlocation values(";
					for(int i=0;i<j;i++)
					{
						//str+=column[i];
						char tmp[100];
						if(i<j-1)
						{
							sprintf(tmp,"%s",column[i]);
							if(strcmp("(null)",tmp))
							{
								sprintf(tmp,"'%s',",column[i]);
							}
							else
							{
								strcpy(tmp,"null,");
							}
						}
						else 
						{
							sprintf(tmp,"'%s');",column[i]);
						}
						//AfxMessageBox(tmp);
						str+=tmp;
						//str+=column[i];
					}
					//AfxMessageBox(str);
					//char* errMsg;
					if(SQLITE_OK!=sqlite3_exec(db,str.GetBuffer(0),0,0,NULL))
					{
						AfxMessageBox("插入错误",NULL,MB_OK);
					}
					//break;
				}
			}
			//////////////////////////////////////////////////////////

			//////////////////////////////////////////////////////////
			//同步t_lightruninfo
			if(mysql_query(&mysql,"select * from t_lightruninfo")==NULL)
			{
				res=mysql_store_result(&mysql);//保存查询到的数据到result

				int j=mysql_num_fields(res);
				while(column=mysql_fetch_row(res))//获取具体的数据
				{
					CString str="replace into t_lightruninfo values(";
					for(int i=0;i<j;i++)
					{
						//str+=column[i];
						char tmp[100];
						if(i<j-1)
						{
							sprintf(tmp,"%s",column[i]);
							if(strcmp("(null)",tmp))
							{
								sprintf(tmp,"'%s',",column[i]);
							}
							else
							{
								strcpy(tmp,"null,");
							}
						}
						else 
						{
							sprintf(tmp,"'%s');",column[i]);
						}
						//AfxMessageBox(tmp);
						str+=tmp;
						//str+=column[i];
					}
					//AfxMessageBox(str);
					//char* errMsg;
					if(SQLITE_OK!=sqlite3_exec(db,str.GetBuffer(0),0,0,NULL))
					{
						AfxMessageBox("插入错误",NULL,MB_OK);
					}
					//break;
				}
			}
			//////////////////////////////////////////////////////////
	*/		
			mysql_close(&mysql);
			//sqlite3_close(db);
			
			flage=0;
		}
		else
		{
			Sleep(10*1000);
			if(timeinfo->tm_min%10!=6)
			{
				flage=1;
			}
		}
	}
	return 0;
}

void CControlDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case 1:
		if(flage==2)
		{
			setsynctext("同步中");
		}
		else
		{
			setsynctext("已同步");
		}
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}
