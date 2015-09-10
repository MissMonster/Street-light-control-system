// usercontrol.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "usercontrol.h"
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
// usercontrol dialog


usercontrol::usercontrol(CWnd* pParent /*=NULL*/)
	: CDialog(usercontrol::IDD, pParent)
{
	//{{AFX_DATA_INIT(usercontrol)
	//}}AFX_DATA_INIT
}


void usercontrol::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(usercontrol)
	DDX_Control(pDX, IDC_COMBO1, m_newjurisdiction);
	DDX_Control(pDX, IDC_EDIT2, m_newpassword);
	DDX_Control(pDX, IDC_EDIT1, m_newname);
	DDX_Control(pDX, IDC_EDIT4, m_usernum);
	DDX_Control(pDX, IDC_LIST1, m_userlist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(usercontrol, CDialog)
	//{{AFX_MSG_MAP(usercontrol)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
	ON_COMMAND(ID_MENUITEM32778, OnMenudeluser)
	ON_BN_CLICKED(IDC_BUTTON1, Onadduser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// usercontrol message handlers

BOOL usercontrol::OnInitDialog() 
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

	//设置列表主题
	m_userlist.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
        | LVS_EX_FULLROWSELECT		// 允许正航选中
        | LVS_EX_GRIDLINES			// 画出网格线
		);

	m_userlist.InsertColumn(0,"用户名"	    ,LVCFMT_CENTER, 70,0);
	m_userlist.InsertColumn(1,"用户组"	    ,LVCFMT_CENTER, 70,0);
	m_userlist.InsertColumn(2,"最后登录时间",LVCFMT_CENTER, 140,0);

	syncuserinfo();

	m_newjurisdiction.AddString("普通用户");
	m_newjurisdiction.AddString("管理员");
	m_newjurisdiction.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//刷新用户列表
void usercontrol::syncuserinfo()
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
	if(mysql_query(&mysql,"select name,jurisdiction,time from t_userinfo")==NULL)
	{
		res=mysql_store_result(&mysql);//保存查询到的数据到result
		
		//////////////////////////////////////////////////////////////////////////
		//获取用户总数
		int j=mysql_num_fields(res);
		CString str;
		str.Format("[%4d]",mysql_num_rows(res));
		m_usernum.SetWindowText(str);
		//////////////////////////////////////////////////////////////////////////

		int index=0;
		m_userlist.DeleteAllItems();
		while(column=mysql_fetch_row(res))//获取具体的数据
		{
			//CString str="replace into t_controllerinfo values(";
			//如果用户名是当前用户则不显示
			if(strcmp(column[0],userinfo.name)==0)
			{
				continue;
			}
			m_userlist.InsertItem(index,column[0]);
			switch(atoi(column[1]))
			{
			case 1:
				m_userlist.SetItemText(index,1,"普通用户");
				break;
			case 2:
				m_userlist.SetItemText(index,1,"管理员");
				break;
			}
			for(int i=2;i<j;i++)
			{
				m_userlist.SetItemText(index,i,column[i]);
			}
			index++;
		}
	}
	mysql_close(&mysql);
}

//添加菜单
void usercontrol::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem != -1)
	{
		DWORD dwPos = GetMessagePos(); //返回表示屏幕坐标下光标位置的长整数值
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_MENU2 ) );
		CMenu* popup = menu.GetSubMenu(0); //取得被指定菜单激活的下拉式菜单或子菜单的句柄
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x, point.y, this ); //在指定位置显示快捷菜单，并跟踪菜单项的选择	
	}

	*pResult = 0;
}

//删除用户
void usercontrol::OnMenudeluser() 
{
	// TODO: Add your command handler code here
	if(MessageBox("确定要删除？","删除用户",MB_ICONINFORMATION|MB_YESNO)==IDNO)
	{
		return ;
	}
	while(m_userlist.GetNextItem(-1,LVNI_ALL|LVNI_SELECTED)!=-1)//判断单/多行
	{
		POSITION pos = m_userlist.GetFirstSelectedItemPosition();
		int nItem = m_userlist.GetNextSelectedItem(pos);
		string name=m_userlist.GetItemText(nItem,0);
		deleteuser(name);
		m_userlist.DeleteItem(nItem);
	}
	/////////////////////////////////////////////////////////////////////
}

//从数据库删除用户
void usercontrol::deleteuser(string name)
{
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("数据库无法连接!");
		return ;
	}
	string str="delete from t_userinfo where name='"+name+"'";
	//MessageBox(str.c_str());
	mysql_query(&mysql,str.c_str());
	mysql_close(&mysql);
}

//添加用户
void usercontrol::Onadduser() 
{
	// TODO: Add your control notification handler code here
	MYSQL mysql;

	CString name;
	CString password;
	char jurisdiction[]="1";
	jurisdiction[0]+=m_newjurisdiction.GetCurSel();
	m_newname.GetWindowText(name);
	m_newpassword.GetWindowText(password);

	if(name=="")return ;
	if(password=="")return ;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("数据库无法连接!");
		return ;
	}

	CString str="insert into t_userinfo (name,password,jurisdiction) VALUES('"+name+"','"+password+"',"+jurisdiction+")";
	//MessageBox(str);
	if(mysql_query(&mysql,str.GetBuffer(0))!=NULL)
	{
		MessageBox("添加用户失败!");
	}
	mysql_close(&mysql);

	//////////////////////////////////////////////////////////////////////////
	//刷新用户列表
	syncuserinfo();
	//////////////////////////////////////////////////////////////////////////
}

void usercontrol::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}
