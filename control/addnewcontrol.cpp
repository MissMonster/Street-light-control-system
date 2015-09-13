// addnewcontrol.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "addnewcontrol.h"
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

extern struct serverset serverinfo;

/////////////////////////////////////////////////////////////////////////////
// addnewcontrol dialog


addnewcontrol::addnewcontrol(CWnd* pParent /*=NULL*/)
	: CDialog(addnewcontrol::IDD, pParent)
{
	//{{AFX_DATA_INIT(addnewcontrol)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void addnewcontrol::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(addnewcontrol)
	DDX_Control(pDX, IDC_COMBO1, m_controllerAutorun);
	DDX_Control(pDX, IDC_EDIT5, m_streetlightNum);
	DDX_Control(pDX, IDC_EDIT4, m_controllerLatitude);
	DDX_Control(pDX, IDC_EDIT3, m_controllerLongitude);
	DDX_Control(pDX, IDC_EDIT2, m_controllerInfo);
	DDX_Control(pDX, IDC_EDIT1, m_controllerId);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(addnewcontrol, CDialog)
	//{{AFX_MSG_MAP(addnewcontrol)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// addnewcontrol message handlers

void addnewcontrol::OnOK() 
{
	// TODO: Add extra validation here
	CString column[6];
	m_controllerId.GetWindowText(column[0]);
	m_controllerInfo.GetWindowText(column[1]);
	m_controllerLongitude.GetWindowText(column[2]);
	m_controllerLatitude.GetWindowText(column[3]);
	m_streetlightNum.GetWindowText(column[4]);
	m_controllerAutorun.GetWindowText(column[5]);
	for(int i=0;i<6;i++)
	{
		if(column[i]=="")
		{
			MessageBox("信息未完整");
			return ;
		}
	}
	//MessageBox(column[5]);
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("数据库无法连接!");
		return ;
	}
	
	column[5].Format("%d",m_controllerAutorun.GetCurSel());
	
	string str="insert into t_controllerinfo(controllerId,controllerInfo,\
controllerLongitude,controllerLatitude,streetlightNum,controllerAutorun,flage) values(";
	str=str+column[0].GetBuffer(0)+",'";
	str=str+column[1].GetBuffer(0)+"',";
	str=str+column[2].GetBuffer(0)+",";
	str=str+column[3].GetBuffer(0)+",";
	str=str+column[4].GetBuffer(0)+",";
	str=str+column[5].GetBuffer(0)+",0)";
	
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	if(mysql_query(&mysql,str.c_str())!=NULL)
	{
		MessageBox("添加失败");
		mysql_close(&mysql);
	}
	else
	{
		MessageBox("添加成功");
		mysql_close(&mysql);
		CDialog::OnOK();
	}
}

void addnewcontrol::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL addnewcontrol::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_controllerAutorun.AddString("全关");
	m_controllerAutorun.AddString("全开");
	m_controllerAutorun.AddString("单号灯开");
	m_controllerAutorun.AddString("单号灯关");
	m_controllerAutorun.AddString("双号灯开");
	m_controllerAutorun.AddString("双号灯关");
	m_controllerAutorun.AddString("其他");

	m_controllerAutorun.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
