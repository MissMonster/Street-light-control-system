// sensordlg.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "sensordlg.h"
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
// sensordlg dialog


sensordlg::sensordlg(CWnd* pParent /*=NULL*/)
	: CDialog(sensordlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(sensordlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void sensordlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(sensordlg)
	DDX_Control(pDX, IDC_LIST1, m_sensorlist);
	DDX_Control(pDX, IDC_COMBO1, m_sensor);
	DDX_Control(pDX, IDC_EXPLORER1, m_web);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(sensordlg, CDialog)
	//{{AFX_MSG_MAP(sensordlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// sensordlg message handlers

BOOL sensordlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_web.Navigate("http://45.114.8.81/baidumap.html", NULL, NULL, NULL, NULL);

	//////////////////////////////////////////////////////////
	//设置列表主题
	m_sensorlist.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
        | LVS_EX_FULLROWSELECT		// 允许正航选中
        | LVS_EX_GRIDLINES			// 画出网格线
		);

	m_sensorlist.InsertColumn(0,"序号"	    ,LVCFMT_CENTER, 140,0);
	m_sensorlist.InsertColumn(0,"标识码"	    ,LVCFMT_CENTER, 70,0);
	m_sensorlist.InsertColumn(0,"传感器类型"	    ,LVCFMT_CENTER, 70,0);
	m_sensorlist.InsertColumn(0,"编号"	    ,LVCFMT_CENTER, 70,0);
	m_sensorlist.InsertColumn(0,"监测值"	    ,LVCFMT_CENTER, 70,0);
	m_sensorlist.InsertColumn(0,"经度"	    ,LVCFMT_CENTER, 70,0);
	m_sensorlist.InsertColumn(0,"纬度"	    ,LVCFMT_CENTER, 70,0);
	m_sensorlist.InsertColumn(0,"故障情况"	    ,LVCFMT_CENTER, 70,0);

	SetTimer(1,100,NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void sensordlg::OnTimer(UINT nIDEvent) 
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
