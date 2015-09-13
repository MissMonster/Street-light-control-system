// errormsgdlg.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "errormsgdlg.h"
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
	//�����б�����
	m_errorinfo.SetExtendedStyle(
		LVS_EX_FLATSB				// ��ƽ������
        | LVS_EX_FULLROWSELECT		// ��������ѡ��
        | LVS_EX_GRIDLINES			// ����������
		);
	
	m_errorinfo.InsertColumn(0,"ʱ��"	    ,LVCFMT_CENTER, 140,0);
	m_errorinfo.InsertColumn(1,"����"	    ,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(2,"��ʶ��"	    ,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(3,"·�Ʊ��"	,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(4,"��������"	,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(5,"��ѹ"	    ,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(6,"����"	    ,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(7,"�¶�"	    ,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(8,"����"	    ,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(9,"����"	    ,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(10,"��Ϣ"	    ,LVCFMT_CENTER, 70,0);
	m_errorinfo.InsertColumn(11,"�������"	,LVCFMT_CENTER, 70,0);
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

//�������д�����Ϣ
void errormsgdlg::showallerror()
{
	MYSQL_RES *res;     //��ѯ�����
	MYSQL_ROW column;   //�����е���
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("���ݿ��޷�����!");
	}
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	
	//////////////////////////////////////////////////////////
	//ͬ��t_errorinfo
	if(mysql_query(&mysql,"select * from t_errorinfo")==NULL)
	{
		res=mysql_store_result(&mysql);//�����ѯ�������ݵ�result
		
		int j=mysql_num_fields(res);
		int index=0;
		m_errorinfo.DeleteAllItems();
		while(column=mysql_fetch_row(res))//��ȡ���������
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
		DWORD dwPos = GetMessagePos(); //���ر�ʾ��Ļ�����¹��λ�õĳ�����ֵ
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_MENU3 ) );
		CMenu* popup = menu.GetSubMenu(0); //ȡ�ñ�ָ���˵����������ʽ�˵����Ӳ˵��ľ��
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x, point.y, this ); //��ָ��λ����ʾ��ݲ˵��������ٲ˵����ѡ��	
	}

	*pResult = 0;
}

//��λ
void errormsgdlg::OnMenuitem32779() 
{
	// TODO: Add your command handler code here
	MYSQL_RES *res;     //��ѯ�����
	MYSQL_ROW column;   //�����е���
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("���ݿ��޷�����!");
		return ;
	}

	//while(m_errorinfo.GetNextItem(-1,LVNI_ALL|LVNI_SELECTED)!=-1)//�жϵ�/����
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
			res=mysql_store_result(&mysql);//�����ѯ�������ݵ�result
			//while(column=mysql_fetch_row(res))//��ȡ���������
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
					MessageBox("δ�ҵ�λ������");
				}
			}
		}
	}
	/////////////////////////////////////////////////////////////////////
	mysql_close(&mysql);
}

//˫��
void errormsgdlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnMenuitem32779();
	*pResult = 0;
}
