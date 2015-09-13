// errormsgdlg.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "errormsgdlg.h"
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
// errormsgdlg dialog


errormsgdlg::errormsgdlg(CWnd* pParent /*=NULL*/)
	: CDialog(errormsgdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(errormsgdlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void errormsgdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(errormsgdlg)
	DDX_Control(pDX, IDC_LIST1, m_errorinfo);
	DDX_Control(pDX, IDC_EXPLORER1, m_web);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(errormsgdlg, CDialog)
	//{{AFX_MSG_MAP(errormsgdlg)
	ON_WM_TIMER()
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
	ON_COMMAND(ID_MENUITEM32779, OnMenuitem32779)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// errormsgdlg message handlers

BOOL errormsgdlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_web.Navigate("http://45.114.8.81/baidumap.html", NULL, NULL, NULL, NULL);

	//////////////////////////////////////////////////////////
	//设置列表主题
	m_errorinfo.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
        | LVS_EX_FULLROWSELECT		// 允许正航选中
        | LVS_EX_GRIDLINES			// 画出网格线
		);
	
	m_errorinfo.InsertColumn(0,"时间"	    ,LVCFMT_CENTER, 140,0);
	m_errorinfo.InsertColumn(1,"类型"	    ,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(2,"标识码"	    ,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(3,"路灯编号"	,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(4,"错误类型"	,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(5,"电压"	    ,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(6,"电流"	    ,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(7,"温度"	    ,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(8,"经度"	    ,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(9,"经度"	    ,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(10,"信息"	    ,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(11,"处理情况"	,LVCFMT_CENTER, 70,0);
	//////////////////////////////////////////////////////////////////////////
	
	showallerror();

	SetTimer(1,100,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void errormsgdlg::OnTimer(UINT nIDEvent) 
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

//加载所有错误信息
void errormsgdlg::showallerror()
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
		m_errorinfo.DeleteAllItems();
		while(column=mysql_fetch_row(res))//获取具体的数据
		{
			m_errorinfo.InsertItem(index,column[0]);
			for(int i=1;i<j;i++)
			{
				m_errorinfo.SetItemText(index,i,column[i]);
			}
			index++;
		}
	}
	mysql_close(&mysql);
}

void errormsgdlg::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem != -1)
	{
		DWORD dwPos = GetMessagePos(); //返回表示屏幕坐标下光标位置的长整数值
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_MENU3 ) );
		CMenu* popup = menu.GetSubMenu(0); //取得被指定菜单激活的下拉式菜单或子菜单的句柄
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x, point.y, this ); //在指定位置显示快捷菜单，并跟踪菜单项的选择	
	}

	*pResult = 0;
}

//定位
void errormsgdlg::OnMenuitem32779() 
{
	// TODO: Add your command handler code here
	MYSQL_RES *res;     //查询结果集
	MYSQL_ROW column;   //数据行的列
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("数据库无法连接!");
		return ;
	}

	//while(m_errorinfo.GetNextItem(-1,LVNI_ALL|LVNI_SELECTED)!=-1)//判断单/多行
	{
		POSITION pos = m_errorinfo.GetFirstSelectedItemPosition();
		int nItem = m_errorinfo.GetNextSelectedItem(pos);
		CString cid=m_errorinfo.GetItemText(nItem,2);
		CString lid=m_errorinfo.GetItemText(nItem,3);

		//////////////////////////////////////////////////////////////////////////
		string str="select Longitude,Latitude from t_lightlocation where controllerId=";
		str=str+cid.GetBuffer(0)+" and streetlightId="+lid.GetBuffer(0);
		//MessageBox(str.c_str());
		mysql_query(&mysql,"SET NAMES 'UTF-8'");
		if(mysql_query(&mysql,str.c_str())==NULL)
		{
			//m_controld.ResetContent();
			res=mysql_store_result(&mysql);//保存查询到的数据到result
			//while(column=mysql_fetch_row(res))//获取具体的数据
			{
				column=mysql_fetch_row(res);
				if(column)
				{
					CString longnum=column[0];
					CString latnum=column[1];
					//m_Longitude.SetWindowText(column[0]);
					//m_Latitude.SetWindowText(column[1]);
					if(longnum=="")return ;
					if(latnum=="")return ;
					
					web.CallJScript("removeall");
					web.CallJScript("setanipiont",longnum,latnum);
					web.CallJScript("movetoplace",longnum,latnum);
				}
				else
				{
					MessageBox("未找到位置数据");
				}
			}
		}
	}
	/////////////////////////////////////////////////////////////////////
	mysql_close(&mysql);
}

//双击
void errormsgdlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnMenuitem32779();
	*pResult = 0;
}
