// usercontrol.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "usercontrol.h"
#include "mysql/mysql.h"
#include "sqlite3.h"

//////////////////////////////////////////////////////////
//�������뷨
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
	//�������뷨
	HIMC m_hImc;    // ȫ�ֻ��߳�Ա����
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

	//�����б�����
	m_userlist.SetExtendedStyle(
		LVS_EX_FLATSB				// ��ƽ������
        | LVS_EX_FULLROWSELECT		// ��������ѡ��
        | LVS_EX_GRIDLINES			// ����������
		);

	m_userlist.InsertColumn(0,"�û���"	    ,LVCFMT_CENTER, 70,0);
	m_userlist.InsertColumn(1,"�û���"	    ,LVCFMT_CENTER, 70,0);
	m_userlist.InsertColumn(2,"����¼ʱ��",LVCFMT_CENTER, 140,0);

	syncuserinfo();

	m_newjurisdiction.AddString("��ͨ�û�");
	m_newjurisdiction.AddString("����Ա");
	m_newjurisdiction.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//ˢ���û��б�
void usercontrol::syncuserinfo()
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
	if(mysql_query(&mysql,"select name,jurisdiction,time from t_userinfo")==NULL)
	{
		res=mysql_store_result(&mysql);//�����ѯ�������ݵ�result
		
		//////////////////////////////////////////////////////////////////////////
		//��ȡ�û�����
		int j=mysql_num_fields(res);
		CString str;
		str.Format("[%4d]",mysql_num_rows(res));
		m_usernum.SetWindowText(str);
		//////////////////////////////////////////////////////////////////////////

		int index=0;
		m_userlist.DeleteAllItems();
		while(column=mysql_fetch_row(res))//��ȡ���������
		{
			//CString str="replace into t_controllerinfo values(";
			//����û����ǵ�ǰ�û�����ʾ
			if(strcmp(column[0],userinfo.name)==0)
			{
				continue;
			}
			m_userlist.InsertItem(index,column[0]);
			switch(atoi(column[1]))
			{
			case 1:
				m_userlist.SetItemText(index,1,"��ͨ�û�");
				break;
			case 2:
				m_userlist.SetItemText(index,1,"����Ա");
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

//��Ӳ˵�
void usercontrol::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem != -1)
	{
		DWORD dwPos = GetMessagePos(); //���ر�ʾ��Ļ�����¹��λ�õĳ�����ֵ
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_MENU2 ) );
		CMenu* popup = menu.GetSubMenu(0); //ȡ�ñ�ָ���˵����������ʽ�˵����Ӳ˵��ľ��
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x, point.y, this ); //��ָ��λ����ʾ��ݲ˵��������ٲ˵����ѡ��	
	}

	*pResult = 0;
}

//ɾ���û�
void usercontrol::OnMenudeluser() 
{
	// TODO: Add your command handler code here
	if(MessageBox("ȷ��Ҫɾ����","ɾ���û�",MB_ICONINFORMATION|MB_YESNO)==IDNO)
	{
		return ;
	}
	while(m_userlist.GetNextItem(-1,LVNI_ALL|LVNI_SELECTED)!=-1)//�жϵ�/����
	{
		POSITION pos = m_userlist.GetFirstSelectedItemPosition();
		int nItem = m_userlist.GetNextSelectedItem(pos);
		string name=m_userlist.GetItemText(nItem,0);
		deleteuser(name);
		m_userlist.DeleteItem(nItem);
	}
	/////////////////////////////////////////////////////////////////////
}

//�����ݿ�ɾ���û�
void usercontrol::deleteuser(string name)
{
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("���ݿ��޷�����!");
		return ;
	}
	string str="delete from t_userinfo where name='"+name+"'";
	//MessageBox(str.c_str());
	mysql_query(&mysql,str.c_str());
	mysql_close(&mysql);
}

//����û�
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
		MessageBox("���ݿ��޷�����!");
		return ;
	}

	CString str="insert into t_userinfo (name,password,jurisdiction) VALUES('"+name+"','"+password+"',"+jurisdiction+")";
	//MessageBox(str);
	if(mysql_query(&mysql,str.GetBuffer(0))!=NULL)
	{
		MessageBox("����û�ʧ��!");
	}
	mysql_close(&mysql);

	//////////////////////////////////////////////////////////////////////////
	//ˢ���û��б�
	syncuserinfo();
	//////////////////////////////////////////////////////////////////////////
}

void usercontrol::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}
