// lightdlg.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "lightdlg.h"
#include "mysql/mysql.h"

//////////////////////////////////////////////////////////
//�������뷨
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

	//�����б�����
	m_lightlist.SetExtendedStyle(
		LVS_EX_FLATSB				// ��ƽ������
        | LVS_EX_FULLROWSELECT		// ��������ѡ��
        | LVS_EX_GRIDLINES			// ����������
		);
	m_lightlist.InsertColumn(0,"ʱ��"	      ,LVCFMT_CENTER, 120,0);
	m_lightlist.InsertColumn(1,"���"	      ,LVCFMT_CENTER, 70,0);
	m_lightlist.InsertColumn(2,"��������ʶ��" ,LVCFMT_CENTER, 70,0);
	m_lightlist.InsertColumn(3,"���"	      ,LVCFMT_CENTER, 70,0);
	m_lightlist.InsertColumn(4,"��ѹ"	      ,LVCFMT_CENTER, 70,0);
	m_lightlist.InsertColumn(5,"����"	      ,LVCFMT_CENTER, 70,0);
	m_lightlist.InsertColumn(6,"�¶�"	      ,LVCFMT_CENTER, 70,0);
	m_lightlist.InsertColumn(7,"����"	      ,LVCFMT_CENTER, 70,0);
	m_lightlist.InsertColumn(8,"�������"	  ,LVCFMT_CENTER, 70,0);
	m_lightlist.InsertColumn(9,"����"	      ,LVCFMT_CENTER, 70,0);

	Onaddcontrol();

	SetTimer(1,100,NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//�޸�����
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
		MessageBox("���ݿ��޷�����!");
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
		MessageBox("�޸ĳɹ�");
	}
	else
	{
		MessageBox("�޸�ʧ��");
	}

	mysql_close(&mysql);

	showalllightinfo();
	//CDialog::OnOK();
}

//���ؿ������б�
void lightdlg::Onaddcontrol()
{
	MYSQL_RES *res;     //��ѯ�����
	MYSQL_ROW column;   //�����е���
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("���ݿ��޷�����!");
		return ;
	}
	
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	if(mysql_query(&mysql,"select controllerId from t_controllerinfo")==NULL)
	{
		res=mysql_store_result(&mysql);//�����ѯ�������ݵ�result
		while(column=mysql_fetch_row(res))//��ȡ���������
		{
			m_controld.AddString(column[0]);
		}
	}
	mysql_close(&mysql);
}

//��ȡѡ������
void lightdlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	MYSQL_RES *res;     //��ѯ�����
	MYSQL_ROW column;   //�����е���
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("���ݿ��޷�����!");
		return ;
	}
	
	CString id;
	m_controld.GetWindowText(id);
	
	string str="select controllerInfo from t_controllerinfo where controllerId=";
	str+=id.GetBuffer(0);

	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	if(mysql_query(&mysql,str.c_str())==NULL)
	{
		res=mysql_store_result(&mysql);//�����ѯ�������ݵ�result
		column=mysql_fetch_row(res);
		if(column)
		{
			m_controllerInfo.SetWindowText(column[0]);
		}
		else
		{
			MessageBox("δ�ҵ���������Ϣ");
		}
	}
	mysql_close(&mysql);

	showalllightinfo();
}

//��ʾ·����Ϣ
void lightdlg::showalllightinfo()
{
	MYSQL_RES *res;     //��ѯ�����
	MYSQL_ROW column;   //�����е���
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("���ݿ��޷�����!");
		return ;
	}
	
	CString id;
	m_controld.GetWindowText(id);
	
	//////////////////////////////////////////////////////////////////////////
	//��ʾ��ǰ������·���б�
	string str="select * from t_lightruninfo where controllerId=";
	str+=id.GetBuffer(0);

	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	if(mysql_query(&mysql,str.c_str())==NULL)
	{
		res=mysql_store_result(&mysql);//�����ѯ�������ݵ�result
		m_lightlist.DeleteAllItems();
		int j=mysql_num_fields(res);
		int index=0;
		
		while(column=mysql_fetch_row(res))//��ȡ���������
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
	//��ʾ��ǰ����������·��λ��
	str="select * from t_lightlocation where controllerId=";
	str+=id.GetBuffer(0);

	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	if(mysql_query(&mysql,str.c_str())==NULL)
	{
		res=mysql_store_result(&mysql);//�����ѯ�������ݵ�result
		int j=mysql_num_fields(res);

		web.CallJScript("removeall");
		
		while(column=mysql_fetch_row(res))//��ȡ���������
		{
			web.CallJScript("setstapiont",column[3],column[4]);
		}
		if(column)
		{
			web.CallJScript("movetoplace",column[3],column[4]);
		}
		else
		{
			MessageBox("δ�ҵ�·��λ������");
		}
	}
	//////////////////////////////////////////////////////////////////////////

	mysql_close(&mysql);
}

//��ʱ��
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
