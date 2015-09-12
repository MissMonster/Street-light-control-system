// land.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "land.h"
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
extern struct userdata  userinfo;

/////////////////////////////////////////////////////////////////////////////
// land dialog

land::land(CWnd* pParent /*=NULL*/)
	: CDialog(land::IDD, pParent)
{
	//{{AFX_DATA_INIT(land)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void land::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(land)
	DDX_Control(pDX, IDC_EDIT2, m_password);
	DDX_Control(pDX, IDC_EDIT1, m_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(land, CDialog)
	//{{AFX_MSG_MAP(land)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// land message handlers

void land::OnOK() 
{
	// TODO: Add extra validation here
	MYSQL_RES *res;     //查询结果集
	MYSQL_ROW column;   //数据行的列
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("数据库无法连接!");
		return ;
	}

	CString str1;
	CString str2;
	m_name.GetWindowText(str1);
	m_password.GetWindowText(str2);

	string query = "select * from t_userinfo where name='"+str1+"' and password='"+str2+"'";
	//////////////////////////////////////////////////////////
	//MessageBoxA(query.c_str());
	//////////////////////////////////////////////////////////
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	if(mysql_real_query(&mysql,query.c_str(),(UINT)query.size())!=NULL)
	{
		MessageBox("数据库无法连接!");
		return ;
	}
	
	res = mysql_store_result(&mysql);
	column = mysql_fetch_row(res);
	//////////////////////////////////////////////////////////
	//获取符合条件数据条数
	if(mysql_num_rows(res)==0)
	{
		MessageBox("用户名或密码错误!");
		m_password.SetWindowText("");
		return ;
	}
	//////////////////////////////////////////////////////////
	//存储用户名和权限
	sprintf(userinfo.name,str1.GetBuffer(0));
	userinfo.jurisdiction=atoi(column[2]);
	//////////////////////////////////////////////////////////
	//记录登录时间
	CString strtime;
	strtime.Format("UPDATE t_userinfo SET time=now() WHERE name='%s'",userinfo.name);
	//MessageBox(strtime);
	mysql_query(&mysql,strtime.GetBuffer(0));
	//////////////////////////////////////////////////////////
	mysql_close(&mysql);

	CDialog::OnOK();
}

BOOL land::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	/*
	//////////////////////////////////////////////////////////
	//屏蔽输入法
	HIMC m_hImc;    // 全局或者成员变量
	HWND hWnd=GetDlgItem(IDC_EDIT1)->m_hWnd ;
    if(hWnd&&IsWindow(hWnd))
    {
        // Get input context for backup.
        m_hImc=ImmGetContext(hWnd);
        
        // Remove association the testing
        if(m_hImc)
			ImmAssociateContext(hWnd,NULL);
        
        // Release input context
        ImmReleaseContext(hWnd,m_hImc);
        :: SetFocus(hWnd);
    }
	//////////////////////////////////////////////////////////
	*/
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
