// lightdlg.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "lightdlg.h"
#include "mysql/mysql.h"

//////////////////////////////////////////////////////////
//屏蔽输入法
#include <Imm.h>  
#pragma comment(lib,"imm32.lib")
//////////////////////////////////////////////////////////
#pragma comment(lib, "mysql/libmysql.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// lightdlg dialog

extern struct serverset serverinfo;

lightdlg::lightdlg(CWnd* pParent /*=NULL*/)
	: CDialog(lightdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(lightdlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void lightdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(lightdlg)
	DDX_Control(pDX, IDC_LIST1, m_lightlist);
	DDX_Control(pDX, IDC_EDIT4, m_streetlightBrightness);
	DDX_Control(pDX, IDC_EDIT3, m_end);
	DDX_Control(pDX, IDC_EDIT2, m_start);
	DDX_Control(pDX, IDC_EDIT1, m_controllerInfo);
	DDX_Control(pDX, IDC_COMBO1, m_controld);
	DDX_Control(pDX, IDC_EXPLORER2, m_web);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(lightdlg, CDialog)
	//{{AFX_MSG_MAP(lightdlg)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// lightdlg message handlers

BOOL lightdlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_web.Navigate("http://45.114.8.81/baidumap.html", NULL, NULL, NULL, NULL);

	//设置列表主题
	m_lightlist.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
        | LVS_EX_FULLROWSELECT		// 允许正航选中
        | LVS_EX_GRIDLINES			// 画出网格线
		);
	m_lightlist.InsertColumn(0,"时间"	      ,LVCFMT_CENTER, 120,0);
	m_lightlist.InsertColumn(1,"序号"	      ,LVCFMT_CENTER, 70,0);
	m_lightlist.InsertColumn(2,"控制器标识码" ,LVCFMT_CENTER, 70,0);
	m_lightlist.InsertColumn(3,"编号"	      ,LVCFMT_CENTER, 70,0);
	m_lightlist.InsertColumn(4,"电压"	      ,LVCFMT_CENTER, 70,0);
	m_lightlist.InsertColumn(5,"电流"	      ,LVCFMT_CENTER, 70,0);
	m_lightlist.InsertColumn(6,"温度"	      ,LVCFMT_CENTER, 70,0);
	m_lightlist.InsertColumn(7,"亮度"	      ,LVCFMT_CENTER, 70,0);
	m_lightlist.InsertColumn(8,"故障情况"	  ,LVCFMT_CENTER, 70,0);
	m_lightlist.InsertColumn(9,"在线"	      ,LVCFMT_CENTER, 70,0);

	Onaddcontrol();

	SetTimer(1,100,NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//修改亮度
void lightdlg::OnOK() 
{
	// TODO: Add extra validation here
	CString column[3];
	m_start.GetWindowText(column[0]);
	m_end.GetWindowText(column[1]);
	m_streetlightBrightness.GetWindowText(column[2]);

	for(int i=0;i<3;i++)
	{
		if(column[i]=="")
		{
			return ;
		}
	}

	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("数据库无法连接!");
		return ;
	}
	
	CString id;
	m_controld.GetWindowText(id);
	
	//////////////////////////////////////////////////////////////////////////
	string str="update t_lightruninfo set streetlightBrightness=";
	str=str+column[2].GetBuffer(0)+" where controllerId="+id.GetBuffer(0)+" and streetlightId>="+column[0].GetBuffer(0)+" and streetlightId<="+column[1].GetBuffer(0);

	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	if(mysql_query(&mysql,str.c_str())==NULL)
	{
		MessageBox("修改成功");
	}
	else
	{
		MessageBox("修改失败");
	}

	mysql_close(&mysql);

	showalllightinfo();
	//CDialog::OnOK();
}

//加载控制器列表
void lightdlg::Onaddcontrol()
{
	MYSQL_RES *res;     //查询结果集
	MYSQL_ROW column;   //数据行的列
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("数据库无法连接!");
		return ;
	}
	
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	if(mysql_query(&mysql,"select controllerId from t_controllerinfo")==NULL)
	{
		res=mysql_store_result(&mysql);//保存查询到的数据到result
		while(column=mysql_fetch_row(res))//获取具体的数据
		{
			m_controld.AddString(column[0]);
		}
	}
	mysql_close(&mysql);
}

//获取选中内容
void lightdlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	MYSQL_RES *res;     //查询结果集
	MYSQL_ROW column;   //数据行的列
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("数据库无法连接!");
		return ;
	}
	
	CString id;
	m_controld.GetWindowText(id);
	
	string str="select controllerInfo from t_controllerinfo where controllerId=";
	str+=id.GetBuffer(0);

	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	if(mysql_query(&mysql,str.c_str())==NULL)
	{
		res=mysql_store_result(&mysql);//保存查询到的数据到result
		column=mysql_fetch_row(res);
		if(column)
		{
			m_controllerInfo.SetWindowText(column[0]);
		}
		else
		{
			MessageBox("未找到控制器信息");
		}
	}
	mysql_close(&mysql);

	showalllightinfo();
}

//显示路灯信息
void lightdlg::showalllightinfo()
{
	MYSQL_RES *res;     //查询结果集
	MYSQL_ROW column;   //数据行的列
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("数据库无法连接!");
		return ;
	}
	
	CString id;
	m_controld.GetWindowText(id);
	
	//////////////////////////////////////////////////////////////////////////
	//显示当前控制器路灯列表
	string str="select * from t_lightruninfo where controllerId=";
	str+=id.GetBuffer(0);

	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	if(mysql_query(&mysql,str.c_str())==NULL)
	{
		res=mysql_store_result(&mysql);//保存查询到的数据到result
		m_lightlist.DeleteAllItems();
		int j=mysql_num_fields(res);
		int index=0;
		
		while(column=mysql_fetch_row(res))//获取具体的数据
		{	
			m_lightlist.InsertItem(index,column[0]);
			for(int i=1;i<j;i++)
			{
				m_lightlist.SetItemText(index,i,column[i]);
			}
			index++;
		}
	}
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//显示当前控制器所有路灯位置
	str="select * from t_lightlocation where controllerId=";
	str+=id.GetBuffer(0);

	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	if(mysql_query(&mysql,str.c_str())==NULL)
	{
		res=mysql_store_result(&mysql);//保存查询到的数据到result
		int j=mysql_num_fields(res);

		web.CallJScript("removeall");
		
		while(column=mysql_fetch_row(res))//获取具体的数据
		{
			web.CallJScript("setstapiont",column[3],column[4]);
		}
		if(column)
		{
			web.CallJScript("movetoplace",column[3],column[4]);
		}
		else
		{
			MessageBox("未找到路灯位置数据");
		}
	}
	//////////////////////////////////////////////////////////////////////////

	mysql_close(&mysql);
}

//定时器
void lightdlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case 1:
		if(m_web.GetDocument()==NULL)
		{
			break;
		}
		web.SetDocument(m_web.GetDocument());
		KillTimer(1);
		break;
	}

	CDialog::OnTimer(nIDEvent);
}
