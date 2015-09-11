// controlmanage.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "controlmanage.h"
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
// controlmanage dialog


controlmanage::controlmanage(CWnd* pParent /*=NULL*/)
	: CDialog(controlmanage::IDD, pParent)
{
	//{{AFX_DATA_INIT(controlmanage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void controlmanage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(controlmanage)
	DDX_Control(pDX, IDC_COMBO2, m_controllerAutorun);
	DDX_Control(pDX, IDC_EDIT12, m_tempThreadholdLow);
	DDX_Control(pDX, IDC_EDIT11, m_tempThreadholdHigh);
	DDX_Control(pDX, IDC_EDIT10, m_currentThreadholdLow);
	DDX_Control(pDX, IDC_EDIT9, m_currentThreadholdHigh);
	DDX_Control(pDX, IDC_EDIT8, m_voltageThreadholdLow);
	DDX_Control(pDX, IDC_EDIT7, m_voltageThreadholdHigh);
	DDX_Control(pDX, IDC_EDIT6, m_controllerLatitude);
	DDX_Control(pDX, IDC_EDIT5, m_controllerLongitude);
	DDX_Control(pDX, IDC_EDIT4, m_streetlightNum);
	DDX_Control(pDX, IDC_EDIT3, m_controllerInfo);
	DDX_Control(pDX, IDC_EDIT1, m_controllerId);
	DDX_Control(pDX, IDC_COMBO1, m_controld);
	DDX_Control(pDX, IDC_EXPLORER1, m_web);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(controlmanage, CDialog)
	//{{AFX_MSG_MAP(controlmanage)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// controlmanage message handlers

void controlmanage::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void controlmanage::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
}

BOOL controlmanage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_web.Navigate("http://45.114.8.81/baidumap.html", NULL, NULL, NULL, NULL);

	//while(m_web.GetDocument()==NULL);
	//web.SetDocument(m_web.GetDocument());

	Onaddcontrol();

	m_controllerAutorun.AddString("自动");
	m_controllerAutorun.AddString("手动");

	SetTimer(1,1000,NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//定位
void controlmanage::OnButton3() 
{
	// TODO: Add your control notification handler code here
	CString str;
	m_controld.GetWindowText(str);
	if(str=="")
	{
		return ;
	}

	CString latnum;
	CString longnum;

	m_controllerLongitude.GetWindowText(longnum);
	m_controllerLatitude.GetWindowText(latnum);

	web.CallJScript("removeall");
	web.CallJScript("setanipiont",longnum,latnum);
	web.CallJScript("movetoplace",longnum,latnum);
}

//删除
void controlmanage::OnButton4() 
{
	// TODO: Add your control notification handler code here
	CString str;
	m_controld.GetWindowText(str);
	if(str=="")
	{
		return ;
	}

	if(MessageBox("确定要删除？","删除控制器",MB_ICONINFORMATION|MB_YESNO)==IDNO)
	{
		return ;
	}

	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("数据库无法连接!");
		mysql_close(&mysql);
		return ;
	}
	CString del="delete from t_controllerinfo where controllerId="+str;
	//MessageBox(del);
	if(mysql_query(&mysql,del.GetBuffer(0))!=NULL)
	{
		MessageBox("删除失败!");
		mysql_close(&mysql);
		return ;
	}

	Onaddcontrol();
	mysql_close(&mysql);
}

//获取选中内容
void controlmanage::OnSelchangeCombo1() 
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
	m_controld.GetLBText(m_controld.GetCurSel(),id);

	string str="select * from t_controllerinfo where controllerId=";
	str+=id.GetBuffer(0);
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	if(mysql_query(&mysql,str.c_str())==NULL)
	{
		res=mysql_store_result(&mysql);//保存查询到的数据到result
		while(column=mysql_fetch_row(res))//获取具体的数据
		{
			m_controllerId.SetWindowText(column[1]);
			m_controllerInfo.SetWindowText(column[2]);
			m_controllerLongitude.SetWindowText(column[3]);
			m_controllerLatitude.SetWindowText(column[4]);
			m_streetlightNum.SetWindowText(column[5]);
			m_voltageThreadholdHigh.SetWindowText(column[7]);
			m_voltageThreadholdLow.SetWindowText(column[8]);
			m_currentThreadholdHigh.SetWindowText(column[9]);
			m_currentThreadholdLow.SetWindowText(column[10]);
			m_tempThreadholdHigh.SetWindowText(column[11]);
			m_tempThreadholdLow.SetWindowText(column[12]);
			//m_controllerAutorun.SetWindowText(column[6]);
			m_controllerAutorun.SetCurSel(atoi(column[6]));
		}
	}
	mysql_close(&mysql);

	//web.SetDocument(m_web.GetDocument());
	OnButton3();
}

//加载控制器列表
void controlmanage::Onaddcontrol()
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
		m_controld.ResetContent();
		res=mysql_store_result(&mysql);//保存查询到的数据到result
		while(column=mysql_fetch_row(res))//获取具体的数据
		{
			m_controld.AddString(column[0]);
		}
	}
	mysql_close(&mysql);
}

//定时器
void controlmanage::OnTimer(UINT nIDEvent) 
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

//新建控制器
void controlmanage::OnButton1() 
{
	// TODO: Add your control notification handler code here
	//web.SetDocument(m_web.GetDocument());

	addnewcontrol dlg;
	if(dlg.DoModal()==IDOK)
	{
		Onaddcontrol();
	}
}

//保存修改
void controlmanage::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CString column[12];
	m_controllerId.GetWindowText(column[0]);
	if(column[0]=="")
	{
		return ;
	}
	m_controllerInfo.GetWindowText(column[1]);
	m_controllerLongitude.GetWindowText(column[2]);
	m_controllerLatitude.GetWindowText(column[3]);
	m_streetlightNum.GetWindowText(column[4]);
	m_voltageThreadholdHigh.GetWindowText(column[5]);
	m_voltageThreadholdLow.GetWindowText(column[6]);
	m_currentThreadholdHigh.GetWindowText(column[7]);
	m_currentThreadholdLow.GetWindowText(column[8]);
	m_tempThreadholdHigh.GetWindowText(column[9]);
	m_tempThreadholdLow.GetWindowText(column[10]);
	m_controllerAutorun.GetWindowText(column[11]);
	//MessageBox(column[5]);
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("数据库无法连接!");
		return ;
	}

	column[11].Format("%d",m_controllerAutorun.GetCurSel());
	
	string str="update t_controllerinfo set controllerInfo='";
	str=str+column[1].GetBuffer(0)+"',controllerLongitude=";
	str=str+column[2].GetBuffer(0)+",controllerLatitude=";
	str=str+column[3].GetBuffer(0)+",streetlightNum=";
	str=str+column[4].GetBuffer(0)+",controllerAutorun=";
	str=str+column[11].GetBuffer(0)+",voltageThreadholdHigh=";
	str=str+column[5].GetBuffer(0)+",voltageThreadholdLow=";
	str=str+column[6].GetBuffer(0)+",currentThreadholdHigh=";
	str=str+column[7].GetBuffer(0)+",currentThreadholdLow=";
	str=str+column[8].GetBuffer(0)+",tempThreadholdHigh=";
	str=str+column[9].GetBuffer(0)+",tempThreadholdLow=";
	str=str+column[10].GetBuffer(0);
	str+=" where controllerId=";
	str+=column[0].GetBuffer(0);
	
	//MessageBox(str.c_str());
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	if(mysql_query(&mysql,str.c_str())!=NULL)
	{
		MessageBox("更新失败");
	}
	else
	{
		MessageBox("保存成功");
	}
	mysql_close(&mysql);
}

