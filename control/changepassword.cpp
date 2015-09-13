// changepassword.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "changepassword.h"
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
// changepassword dialog

changepassword::changepassword(CWnd* pParent /*=NULL*/)
	: CDialog(changepassword::IDD, pParent)
{
	//{{AFX_DATA_INIT(changepassword)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void changepassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(changepassword)
	DDX_Control(pDX, IDC_EDIT3, m_newpassword2);
	DDX_Control(pDX, IDC_EDIT2, m_newpassword1);
	DDX_Control(pDX, IDC_EDIT1, m_oldpassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(changepassword, CDialog)
	//{{AFX_MSG_MAP(changepassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// changepassword message handlers

void changepassword::OnOK() 
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
	CString str3;
	m_oldpassword.GetWindowText(str1);
	m_newpassword1.GetWindowText(str2);
	m_newpassword2.GetWindowText(str3);

	if(str2!=str3)
	{
		MessageBox("密码不一致!");
		return ;
	}
	
	string query = "select * from t_userinfo where name='";
	query=query+userinfo.name+"' and password='"+str1.GetBuffer(0)+"'";

	if(mysql_real_query(&mysql,query.c_str(),(UINT)query.size())!=NULL)
	{
		MessageBox("数据库无法连接!");
		return ;
	}
	
	//////////////////////////////////////////////////////////////////////////
	res = mysql_store_result(&mysql);
	column = mysql_fetch_row(res);
	//////////////////////////////////////////////////////////
	//获取符合条件数据条数
	if(mysql_num_rows(res)==0)
	{
		MessageBox("密码错误!");
		m_oldpassword.SetWindowText("");
		return ;
	}
	//////////////////////////////////////////////////////////
	
	query = "update t_userinfo set password='"+str2+"' where name='"+userinfo.name+"'";
	//////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////
	if(mysql_real_query(&mysql,query.c_str(),(UINT)query.size())!=NULL)
	{
		MessageBox("数据库无法连接!");
		return ;
	}
	else
	{
		MessageBox("密码修改成功!");
	}

	CDialog::OnOK();
}

void changepassword::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
