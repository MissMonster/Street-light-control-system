// lightcontrldlg.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "lightcontrldlg.h"
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

extern struct serverset serverinfo;

/////////////////////////////////////////////////////////////////////////////
// lightcontrldlg dialog


lightcontrldlg::lightcontrldlg(CWnd* pParent /*=NULL*/)
	: CDialog(lightcontrldlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(lightcontrldlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void lightcontrldlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(lightcontrldlg)
	DDX_Control(pDX, IDC_EDIT9, m_lightnum);
	DDX_Control(pDX, IDC_EDIT8, m_controllerInfo);
	DDX_Control(pDX, IDC_EDIT7, m_Latitude);
	DDX_Control(pDX, IDC_EDIT6, m_Longitude);
	DDX_Control(pDX, IDC_EDIT5, m_streetlightBrightness);
	DDX_Control(pDX, IDC_EDIT4, m_streetlightTemp);
	DDX_Control(pDX, IDC_EDIT3, m_streetlightCurrent);
	DDX_Control(pDX, IDC_EDIT1, m_streetlightVoltage);
	DDX_Control(pDX, IDC_COMBO2, m_streetlightId);
	DDX_Control(pDX, IDC_COMBO1, m_controllerId);
	DDX_Control(pDX, IDC_EXPLORER1, m_web);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(lightcontrldlg, CDialog)
	//{{AFX_MSG_MAP(lightcontrldlg)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// lightcontrldlg message handlers

BOOL lightcontrldlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_web.Navigate("http://45.114.8.81/baidumap.html", NULL, NULL, NULL, NULL);

	showallcontrol();
	
	SetTimer(1,100,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void lightcontrldlg::OnTimer(UINT nIDEvent) 
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

//��ʾ���п�����
void lightcontrldlg::showallcontrol()
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
		m_controllerId.ResetContent();
		res=mysql_store_result(&mysql);//�����ѯ�������ݵ�result
		while(column=mysql_fetch_row(res))//��ȡ���������
		{
			m_controllerId.AddString(column[0]);
		}
	}

	mysql_close(&mysql);
}

//��ʾ������������·��
void lightcontrldlg::showalllight()
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
	m_controllerId.GetWindowText(id);
	
	string str="select streetlightId from t_lightruninfo where controllerId=";
	str+=id.GetBuffer(0);
	
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	if(mysql_query(&mysql,str.c_str())==NULL)
	{
		m_streetlightId.ResetContent();
		res=mysql_store_result(&mysql);//�����ѯ�������ݵ�result
		while(column=mysql_fetch_row(res))//��ȡ���������
		{
			m_streetlightId.AddString(column[0]);
		}
	}
	mysql_close(&mysql);

	//////////////////////////////////////////////////////////////////////////
	//�����Ϣ
	m_streetlightVoltage.SetWindowText("");
	m_streetlightCurrent.SetWindowText("");
	m_streetlightTemp.SetWindowText("");
	m_streetlightBrightness.SetWindowText("");
	m_Longitude.SetWindowText("");
	m_Latitude.SetWindowText("");
	//////////////////////////////////////////////////////////////////////////
}

//��ȡѡ�п�����
void lightcontrldlg::OnSelchangeCombo1() 
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
	//////////////////////////////////////////////////////////////////////////
	//��ʾ��������Ϣ
	CString id;
	m_controllerId.GetWindowText(id);
	
	string str="select controllerInfo,streetlightNum from t_controllerinfo where controllerId=";
	str+=id.GetBuffer(0);
	//MessageBox(str.c_str());
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	if(mysql_query(&mysql,str.c_str())==NULL)
	{
		//m_controld.ResetContent();
		res=mysql_store_result(&mysql);//�����ѯ�������ݵ�result
		//while(column=mysql_fetch_row(res))//��ȡ���������
		{
			column=mysql_fetch_row(res);
			if(column)
			{
				m_controllerInfo.SetWindowText(column[0]);
				m_lightnum.SetWindowText(column[1]);
			}
			else
			{
				MessageBox("δ�ҵ�����������");
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	mysql_close(&mysql);
	showalllight();
}

//��ȡѡ��·��
void lightcontrldlg::OnSelchangeCombo2() 
{
	// TODO: Add your control notification handler code here
	CString cid;
	CString lid;
	m_controllerId.GetWindowText(cid);
	m_streetlightId.GetWindowText(lid);

	MYSQL_RES *res;     //��ѯ�����
	MYSQL_ROW column;   //�����е���
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("���ݿ��޷�����!");
		return ;
	}
	//////////////////////////////////////////////////////////////////////////
	string str="select streetlightVoltage,streetlightCurrent,\
streetlightTemp,streetlightBrightness from t_lightruninfo where controllerId=";
	str=str+cid.GetBuffer(0)+" and streetlightId="+lid.GetBuffer(0);
	//MessageBox(str.c_str());
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	if(mysql_query(&mysql,str.c_str())==NULL)
	{
		//m_controld.ResetContent();
		res=mysql_store_result(&mysql);//�����ѯ�������ݵ�result
		//while(column=mysql_fetch_row(res))//��ȡ���������
		{
			column=mysql_fetch_row(res);
			if(column)
			{
				m_streetlightVoltage.SetWindowText(column[0]);
				m_streetlightCurrent.SetWindowText(column[1]);
				m_streetlightTemp.SetWindowText(column[2]);
				m_streetlightBrightness.SetWindowText(column[3]);
			}
			else
			{
				MessageBox("δ�ҵ�·������");
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	str="select Longitude,Latitude from t_lightlocation where controllerId=";
	str=str+cid.GetBuffer(0)+" and streetlightId="+lid.GetBuffer(0);
	//MessageBox(str.c_str());
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	if(mysql_query(&mysql,str.c_str())==NULL)
	{
		//m_controld.ResetContent();
		res=mysql_store_result(&mysql);//�����ѯ�������ݵ�result
		//while(column=mysql_fetch_row(res))//��ȡ���������
		{
			column=mysql_fetch_row(res);
			if(column)
			{
				m_Longitude.SetWindowText(column[0]);
				m_Latitude.SetWindowText(column[1]);
			}
			else
			{
				MessageBox("δ�ҵ�λ������");
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	mysql_close(&mysql);
}

//��·��
void lightcontrldlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CString longnum;
	CString latnum;
	
	m_Longitude.GetWindowText(longnum);
	m_Latitude.GetWindowText(latnum);

	if(longnum=="")return ;
	if(latnum=="")return ;
	
	web.CallJScript("removeall");
	web.CallJScript("setanipiont",longnum,latnum);
	web.CallJScript("movetoplace",longnum,latnum);
}

//�ر�·��
void lightcontrldlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	
}

//��λ·��
void lightcontrldlg::OnButton4() 
{
	// TODO: Add your control notification handler code here

}

void lightcontrldlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}
