// changename.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "changename.h"
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
// changename dialog

changename::changename(CWnd* pParent /*=NULL*/)
	: CDialog(changename::IDD, pParent)
{
	//{{AFX_DATA_INIT(changename)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void changename::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(changename)
	DDX_Control(pDX, IDC_EDIT1, m_newname);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(changename, CDialog)
	//{{AFX_MSG_MAP(changename)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// changename message handlers

void changename::OnOK() 
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
	m_newname.GetWindowText(str1);

	string query = "select * from t_userinfo where name='"+str1+"'";
	//////////////////////////////////////////////////////////
	//MessageBoxA(query.c_str());
	//////////////////////////////////////////////////////////
	if(mysql_real_query(&mysql,query.c_str(),(UINT)query.size())!=NULL)
	{
		MessageBox("数据库无法连接!");
		return ;
	}
	
	res = mysql_store_result(&mysql);
	column = mysql_fetch_row(res);
	//////////////////////////////////////////////////////////
	//获取符合条件数据条数
	if(mysql_num_rows(res)!=0)
	{
		MessageBox("用户名已存在,请重新输入!");
		//m_newname.SetWindowText("");
		return ;
	}
	
	query = "update t_userinfo set name='"+str1+"' where name='"+userinfo.name+"'";
	//////////////////////////////////////////////////////////
	//MessageBoxA(query.c_str());
	//////////////////////////////////////////////////////////
	if(mysql_real_query(&mysql,query.c_str(),(UINT)query.size())!=NULL)
	{
		MessageBox("数据库无法连接!");
		return ;
	}
	else
	{
		MessageBox("用户名修改成功,请重新登录以使修改生效!");
	}

	strcpy(userinfo.name,str1.GetBuffer(0));
	//////////////////////////////////////////////////////////

	CDialog::OnOK();
}

void changename::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL changename::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
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
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
