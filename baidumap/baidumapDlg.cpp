/**************************************
 *FILE    :baidumapDlg.cpp
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :4/22/2015
 *TEXT    :DataStructure for Street light control system
 *EMAIL   :gtsoft_wk@foxmail.com
***************************************/

#include "stdafx.h"
#include "baidumap.h"
#include "baidumapDlg.h"
#include "webbrowser2.h"
#include "WebPage.h"
#include "controlinfo.h"
#include "brightness.h"
#include "DataStructure.h"
#include "aboutdlg.h"
#include "login.h"
#include "newusermessage.h"
#include <iostream>
#include <vector>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////
vector<CONTROLDATA> controller;
vector<CONTROLDATA>::iterator p_cuntroller;
CONTROLDATA continfo;
int controller_number = -1;
int light_number = -1;
unsigned char light_brightness;
CWebPage web;
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CBaidumapDlg dialog

CBaidumapDlg::CBaidumapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBaidumapDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBaidumapDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBaidumapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBaidumapDlg)
	DDX_Control(pDX, IDC_LIST3, m_list_error);
	DDX_Control(pDX, IDC_LIST2, m_list_light);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_EXPLORER1, m_map);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBaidumapDlg, CDialog)
	//{{AFX_MSG_MAP(CBaidumapDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkList2)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, OnRclickList2)
	ON_COMMAND(ID_MENUITEM32777, OnMenuitem32777)
	ON_COMMAND(ID_MENUITEM32773, OnMenuitem32773)
	ON_COMMAND(ID_MENUITEM32774, OnMenuitem32774)
	ON_COMMAND(ID_MENUITEM32775, OnMenuitem32775)
	ON_COMMAND(ID_MENUITEM32776, OnMenuitem32776)
	ON_COMMAND(ID_MENUITEM32784, OnMenuitem32784)
	ON_COMMAND(ID_MENUITEM32791, OnMenuitem32791)
	ON_COMMAND(ID_MENUITEM32792, OnMenuitem32792)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, OnDblclkList3)
	ON_COMMAND(ID_MENUITEM32802, OnMenuitem32802)
	ON_COMMAND(ID_MENUITEM32800, OnMenuitem32800)
	ON_COMMAND(ID_MENUITEM32781, OnMenuitem32781)
	ON_COMMAND(ID_MENUITEM32794, OnMenuitem32794)
	ON_COMMAND(ID_MENUITEM32795, OnMenuitem32795)
	ON_COMMAND(ID_MENUITEM32796, OnMenuitem32796)
	ON_COMMAND(ID_MENUITEM32797, OnMenuitem32797)
	ON_COMMAND(ID_MENUITEM32798, OnMenuitem32798)
	ON_COMMAND(ID_MENUITEM32799, OnMenuitem32799)
	ON_COMMAND(ID_MENUITEM32785, OnMenuitem32785)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaidumapDlg message handlers

BOOL CBaidumapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//��ȡ��������Ŀ¼
	CString path;
    GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
    path.ReleaseBuffer();
    int pos = path.ReverseFind('\\');
    path = path.Left(pos);
	path+="\\baidumap.html";
	m_map.Navigate(path, NULL, NULL, NULL, NULL);

	web.SetDocument(m_map.GetDocument());

	//���ÿ������б�����
	m_list.SetExtendedStyle(
		LVS_EX_FLATSB				// ��ƽ������
        | LVS_EX_FULLROWSELECT		// ��������ѡ��
        | LVS_EX_GRIDLINES			// ����������
    );

	m_list.InsertColumn(0,"��ʶ��"	,LVCFMT_CENTER, 60,0);
	m_list.InsertColumn(1,"��Ϣ"	,LVCFMT_CENTER, 60,0);
	m_list.InsertColumn(2,"·������",LVCFMT_CENTER, 70,0);
	m_list.InsertColumn(3,"���з�ʽ",LVCFMT_CENTER, 70,0);

	//����·���б�����
	m_list_light.SetExtendedStyle(
		LVS_EX_FLATSB				// ��ƽ������
        | LVS_EX_FULLROWSELECT		// ��������ѡ��
        | LVS_EX_GRIDLINES			// ����������
		);
	
	m_list_light.InsertColumn(0,"���"	,LVCFMT_CENTER, 60,0);
	m_list_light.InsertColumn(1,"״̬"	,LVCFMT_CENTER, 60,0);
	m_list_light.InsertColumn(2,"����"	,LVCFMT_CENTER, 60,0);
	m_list_light.InsertColumn(3,"��ѹ"	,LVCFMT_CENTER, 60,0);
	m_list_light.InsertColumn(4,"����"	,LVCFMT_CENTER, 60,0);
	m_list_light.InsertColumn(5,"�¶�"	,LVCFMT_CENTER, 60,0);
	m_list_light.InsertColumn(6,"γ��"	,LVCFMT_CENTER, 80,0);
	m_list_light.InsertColumn(7,"����"	,LVCFMT_CENTER, 80,0);

	//���ù����б�����
	m_list_error.SetExtendedStyle(
		LVS_EX_FLATSB				// ��ƽ������
        | LVS_EX_FULLROWSELECT		// ��������ѡ��
        | LVS_EX_GRIDLINES			// ����������
		);
	
	m_list_error.InsertColumn(0,"��ʶ��"	,LVCFMT_CENTER, 60,0);
	m_list_error.InsertColumn(1,"��Ϣ"		,LVCFMT_CENTER, 70,0);
	m_list_error.InsertColumn(2,"���"		,LVCFMT_CENTER, 70,0);
	m_list_error.InsertColumn(3,"γ��"		,LVCFMT_CENTER, 80,0);
	m_list_error.InsertColumn(4,"����"		,LVCFMT_CENTER, 80,0);
	m_list_error.InsertColumn(5,"����ԭ��"	,LVCFMT_CENTER, 80,0);
	m_list_error.InsertColumn(6,"����״̬"	,LVCFMT_CENTER, 80,0);

	//�������n������������
	int error_number=0;
	for(int i=0;i<23;i++)
	{
		CONTROLDATA temp;
		temp.id=rand()%1000;
		temp.lightmessage[0]='A'+rand()%26;
		temp.lightmessage[1]='\0';
		temp.Latitude=28.190991+rand()%10000*0.00001;
		temp.Longitude=112.956087+rand()%10000*0.00001;
		temp.lightsum=30+rand()%25;
		temp.theway=rand()%6;
		controller.push_back(temp);

		CString str;
		str.Format(_T("%d"),temp.id);
		m_list.InsertItem(i,str);

		m_list.SetItemText(i,1,temp.lightmessage);
		
		str.Format(_T("%d"),temp.lightsum);
		m_list.SetItemText(i,2,str);
		
		str.Format(_T("%d"),temp.theway);
		m_list.SetItemText(i,3,str);

		//�������n��·������
		for(int j=0;j<temp.lightsum;j++)
		{
			LIGHTDATA tempone;
			tempone.id=j+1;
			tempone.voltage=10+rand()%10;
			tempone.current=1+rand()%10*0.1;
			tempone.Latitude=controller[i].Latitude+rand()%1000*0.00001;
			tempone.Longitude=controller[i].Longitude+rand()%1000*0.00001;
			tempone.temperature=100+rand()%10+rand()%10*0.1;
			tempone.status=rand()%3;

			if(tempone.status==_OPENLIGHT_)
			{
				tempone.bright=1+rand()%254;
			}
			else tempone.bright=0;

			controller[i].lightline.push_back(tempone);

			//������·����Ϣ����������б�
			if(tempone.status==2)
			{
				str.Format(_T("%d"),temp.id);
				m_list_error.InsertItem(error_number,str);

				m_list_error.SetItemText(error_number,1,temp.lightmessage);

				str.Format(_T("%d"),tempone.id);
				m_list_error.SetItemText(error_number,2,str);

				str.Format(_T("%lf"),tempone.Latitude);
				m_list_error.SetItemText(error_number,3,str);

				str.Format(_T("%lf"),tempone.Longitude);
				m_list_error.SetItemText(error_number,4,str);

				str=rand()%2?"��·":"��·";
				m_list_error.SetItemText(error_number,5,str);

				m_list_error.SetItemText(error_number,6,"δ����");

				error_number++;
			}
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBaidumapDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBaidumapDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//��ʾѡ�п�������·���б�
void CBaidumapDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	int nItem; //����ѡ���е��к�
	pos = m_list.GetFirstSelectedItemPosition();
	if(pos)
	{
		nItem = m_list.GetNextSelectedItem(pos);
	}
	else return ;
	if(nItem==controller_number)return ;
	else
	{
		light_number=-1;
		controller_number=nItem;
	}
	CString latnum;
	CString longnum;
	latnum.Format(_T("%lf"),controller[nItem].Latitude);
	longnum.Format(_T("%lf"),controller[nItem].Longitude);

	web.CallJScript("removeall");
	web.CallJScript("movetoplace",latnum,longnum);

	/////////////////////////////////////////////////////////////////////
	web.CallJScript("setanipiont",latnum,longnum);
	 
	/////////////////////////////////////////////////////////////////////
	//���б�����ʾ·��
	m_list_light.DeleteAllItems();//�ػ�·���б�
	for(int i=0;i<controller[nItem].lightsum;i++)
	{
		CString str;
		//CString temp;
		str.Format(_T("%04d"),controller[nItem].lightline[i].id);
		m_list_light.InsertItem(i,str);
		
		switch(controller[nItem].lightline[i].status)
		{
		case _CLOSELIGHT_:
			str="�ر�";
			break;
		case _OPENLIGHT_:
			str="����";
			break;
		case _BADLIGHT_:
			str="����";
			break;
		}
		m_list_light.SetItemText(i,1,str);

		str.Format(_T("%d"),controller[nItem].lightline[i].bright);
		m_list_light.SetItemText(i,2,str);

		str.Format(_T("%.02f"),controller[nItem].lightline[i].voltage);
		m_list_light.SetItemText(i,3,str);
		
		str.Format(_T("%0.2f"),controller[nItem].lightline[i].current);
		m_list_light.SetItemText(i,4,str);

		str.Format(_T("%.02f"),controller[nItem].lightline[i].temperature);
		m_list_light.SetItemText(i,5,str);
		
		str.Format(_T("%lf"),controller[nItem].lightline[i].Longitude);
		m_list_light.SetItemText(i,6,str);
		
		str.Format(_T("%lf"),controller[nItem].lightline[i].Latitude);
		m_list_light.SetItemText(i,7,str);

		latnum.Format(_T("%lf"),controller[nItem].lightline[i].Latitude);
		longnum.Format(_T("%lf"),controller[nItem].lightline[i].Longitude);

		web.CallJScript("setstapiont",latnum,longnum);
	}
	/////////////////////////////////////////////////////////////////////

	*pResult = 0;
}

//����·��λ��
void CBaidumapDlg::OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	int nItem; //����ѡ���е��к�
	pos = m_list_light.GetFirstSelectedItemPosition();
	if(pos)
	{
		nItem = m_list_light.GetNextSelectedItem(pos); 
	}
	else return ;

	if(nItem!=light_number)
	{
		light_number=nItem;
		CString latnum;
		CString longnum;
		latnum.Format(_T("%lf"),controller[controller_number].lightline[nItem].Latitude);
		longnum.Format(_T("%lf"),controller[controller_number].lightline[nItem].Longitude);
		web.CallJScript("movetoplace",latnum,longnum);
	}

	*pResult = 0;
}


void CBaidumapDlg::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem != -1)
	{
		DWORD dwPos = GetMessagePos(); //���ر�ʾ��Ļ�����¹��λ�õĳ�����ֵ
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_MENU1 ) );
		CMenu* popup = menu.GetSubMenu(0); //ȡ�ñ�ָ���˵����������ʽ�˵����Ӳ˵��ľ��
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x, point.y, this ); //��ָ��λ����ʾ��ݲ˵��������ٲ˵����ѡ��	
	}
	
	*pResult = 0;
}

void CBaidumapDlg::OnRclickList2(NMHDR* pNMHDR, LRESULT* pResult) 
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

//���������� �˵���
void CBaidumapDlg::OnMenuitem32785() 
{
	// TODO: Add your command handler code here
	OnMenuitem32777();
}

//���ӿ�����
void CBaidumapDlg::OnMenuitem32777() 
{
	// TODO: Add your command handler code here
	controlinfo dlg;
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	int nItem = m_list.GetNextSelectedItem(pos);
	continfo.id=-1;
	if(dlg.DoModal()==IDOK)
	{
		int index=controller.size();
		
		CString str;
		str.Format(_T("%03d"),continfo.id);
		m_list.InsertItem(index,str);
		
		m_list.SetItemText(index,1,continfo.lightmessage);
		
		str.Format(_T("%d"),continfo.lightsum);
		m_list.SetItemText(index,2,str);
		
		str.Format(_T("%d"),continfo.theway);
		m_list.SetItemText(index,3,str);
		
		controller.push_back(continfo);

		nItem=controller.size();
		for(int j=0;j<continfo.lightsum;j++)
		{
			LIGHTDATA tempone;
			tempone.id=j+1;
			tempone.voltage=10+rand()%10;
			tempone.current=1+rand()%10*0.1;
			tempone.Latitude=controller[nItem-1].Latitude+rand()%1000*0.00001;
			tempone.Longitude=controller[nItem-1].Longitude+rand()%1000*0.00001;
			tempone.temperature=100+rand()%10+rand()%10*0.1;
			tempone.status=rand()%3;
			
			if(tempone.status!=_OPENLIGHT_)
			{
				tempone.bright=1+rand()%254;
			}
			else tempone.bright=0;

			controller[nItem-1].lightline.push_back(tempone);
		}

	}
}

//�޸Ŀ�����
void CBaidumapDlg::OnMenuitem32773() 
{
	// TODO: Add your command handler code here
	controlinfo dlg;
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	int nItem = m_list.GetNextSelectedItem(pos);
	continfo=controller[nItem];
	if(dlg.DoModal()==IDOK)
	{
		CString str;
		str.Format(_T("%03d"),continfo.id);
		m_list.SetItemText(nItem,0,str);
		
		m_list.SetItemText(nItem,1,continfo.lightmessage);
		
		str.Format(_T("%d"),continfo.lightsum);
		m_list.SetItemText(nItem,2,str);
		
		str.Format(_T("%d"),continfo.theway);
		m_list.SetItemText(nItem,3,str);

		controller[nItem]=continfo;
	}
}

//ɾ��������
void CBaidumapDlg::OnMenuitem32774() 
{
	// TODO: Add your command handler code here
	if(MessageBox("ȷ��Ҫɾ����","ɾ��������",MB_ICONINFORMATION|MB_YESNO)==IDNO)return ;
	while(m_list.GetNextItem(-1,LVNI_ALL|LVNI_SELECTED)!=-1)//�жϵ�/����
	{
		POSITION pos = m_list.GetFirstSelectedItemPosition();
		int nItem = m_list.GetNextSelectedItem(pos);
		p_cuntroller=controller.begin();
		p_cuntroller+=nItem;
		controller.erase(p_cuntroller);
		m_list.DeleteItem(nItem);
	}
	m_list_light.DeleteAllItems();
	/////////////////////////////////////////////////////////////////////
	//������λ�ó�ʼ��
	controller_number = -1;

	/////////////////////////////////////////////////////////////////////
	//���������
	web.CallJScript("removeall");
	/////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////
//��·��
void CBaidumapDlg::OnMenuitem32775() 
{
	// TODO: Add your command handler code here
	POSITION pos = m_list_light.GetFirstSelectedItemPosition();
	while(pos)//�жϵ�/����
	{
		int nItem = m_list_light.GetNextSelectedItem(pos);
		controller[controller_number].lightline[nItem].status=1;
		controller[controller_number].lightline[nItem].bright=255;
		m_list_light.SetItemText(nItem,1,"����");
		m_list_light.SetItemText(nItem,2,"255");
	}
}

//�ر�·��
void CBaidumapDlg::OnMenuitem32776() 
{
	// TODO: Add your command handler code here
	POSITION pos = m_list_light.GetFirstSelectedItemPosition();
	while(pos)//�жϵ�/����
	{
		
		int nItem = m_list_light.GetNextSelectedItem(pos);
		controller[controller_number].lightline[nItem].status=0;
		controller[controller_number].lightline[nItem].bright=0;
		m_list_light.SetItemText(nItem,1,"�ر�");
		m_list_light.SetItemText(nItem,2,"0");
	}
}
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//��ʾ·���б�
void CBaidumapDlg::OnMenuitem32784() 
{
	// TODO: Add your command handler code here
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	int nItem = m_list.GetNextSelectedItem(pos);
	controller_number=nItem;

	CString latnum;
	CString longnum;
	latnum.Format(_T("%lf"),controller[nItem].Latitude);
	longnum.Format(_T("%lf"),controller[nItem].Longitude);
	web.CallJScript("removeall");
	web.CallJScript("movetoplace",latnum,longnum);

	/////////////////////////////////////////////////////////////////////
	//��ʾ��������Ϣ
	web.CallJScript("setanipiont",latnum,longnum);

	/////////////////////////////////////////////////////////////////////
	//���б�����ʾ·��
	m_list_light.DeleteAllItems();//�ػ�·���б�
	for(int i=0;i<controller[nItem].lightsum;i++)
	{
		CString str;
		//CString temp;
		str.Format(_T("%04d"),controller[nItem].lightline[i].id);
		m_list_light.InsertItem(i,str);
		
		switch(controller[nItem].lightline[i].status)
		{
		case _CLOSELIGHT_:
			str="�ر�";
			break;
		case _OPENLIGHT_:
			str="����";
			break;
		case _BADLIGHT_:
			str="����";
			break;
		}
		m_list_light.SetItemText(i,1,str);
		
		str.Format(_T("%d"),controller[nItem].lightline[i].bright);
		m_list_light.SetItemText(i,2,str);
		
		str.Format(_T("%.02f"),controller[nItem].lightline[i].voltage);
		m_list_light.SetItemText(i,3,str);
		
		str.Format(_T("%0.2f"),controller[nItem].lightline[i].current);
		m_list_light.SetItemText(i,4,str);
		
		str.Format(_T("%.02f"),controller[nItem].lightline[i].temperature);
		m_list_light.SetItemText(i,5,str);
		
		str.Format(_T("%lf"),controller[nItem].lightline[i].Longitude);
		m_list_light.SetItemText(i,6,str);
		
		str.Format(_T("%lf"),controller[nItem].lightline[i].Latitude);
		m_list_light.SetItemText(i,7,str);
		
		latnum.Format(_T("%lf"),controller[nItem].lightline[i].Latitude);
		longnum.Format(_T("%lf"),controller[nItem].lightline[i].Longitude);
		
		web.CallJScript("setstapiont",latnum,longnum);
	}
	/////////////////////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////

//����
void CBaidumapDlg::OnMenuitem32791() 
{
	// TODO: Add your command handler code here
	aboutdlg dlg;
	dlg.DoModal();
}

//�˳�
void CBaidumapDlg::OnMenuitem32792() 
{
	// TODO: Add your command handler code here
	DestroyWindow( );
}

//��λ����·��
void CBaidumapDlg::OnDblclkList3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	int nItem;  //����ѡ���е��к�
	pos = m_list_error.GetFirstSelectedItemPosition();
	if(pos)
	{
		nItem = m_list_error.GetNextSelectedItem(pos);
	}

	CString latnum;
	CString longnum;

	latnum=m_list_error.GetItemText(nItem,3);
	longnum=m_list_error.GetItemText(nItem,4);

	web.CallJScript("removeall");
	web.CallJScript("setanipiont",latnum,longnum);
	web.CallJScript("movetoplace",latnum,longnum);

	/////////////////////////////////////////////////////////////////////
	//������λ�ó�ʼ��
	controller_number = -1;
	m_list_light.DeleteAllItems();
	
	*pResult = 0;
}

//·�ƶ�λ
void CBaidumapDlg::OnMenuitem32802() 
{
	// TODO: Add your command handler code here
	POSITION pos;
	int nItem; //����ѡ���е��к�

	pos = m_list_light.GetFirstSelectedItemPosition();
	if(pos)
	{
		nItem = m_list_light.GetNextSelectedItem(pos); 
	}
	else return ;
	
	if(nItem!=light_number)
	{
		light_number=nItem;
		CString latnum;
		CString longnum;
		latnum.Format(_T("%lf"),controller[controller_number].lightline[nItem].Latitude);
		longnum.Format(_T("%lf"),controller[controller_number].lightline[nItem].Longitude);
		web.CallJScript("movetoplace",latnum,longnum);
	}
}

//·������
void CBaidumapDlg::OnMenuitem32800() 
{
	// TODO: Add your command handler code here
	brightness dlg;
	POSITION pos;
	int nItem; //����ѡ���е��к�
	
	pos = m_list_light.GetFirstSelectedItemPosition();
	if(pos)
	{
		nItem = m_list_light.GetNextSelectedItem(pos); 
	}
	else return ;

	light_brightness=controller[controller_number].lightline[nItem].bright;
	if(dlg.DoModal()==IDOK)
	{
		controller[controller_number].lightline[nItem].bright=light_brightness;
		CString str;
		str.Format("%d",light_brightness);
		m_list_light.SetItemText(nItem,2,str);
	}
}

//�޸��û���������
void CBaidumapDlg::OnMenuitem32781() 
{
	// TODO: Add your command handler code here
	login ldlg;
	if(ldlg.DoModal()==IDOK)
	{
		//MessageBox("ok","�޸��û���",MB_OK);
		newusermessage userdlg;
		userdlg.DoModal();
	}
}

void CBaidumapDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

//ȫ��
void CBaidumapDlg::OnMenuitem32794() 
{
	// TODO: Add your command handler code here
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	int nItem = m_list.GetNextSelectedItem(pos);
	//controller_number=nItem;
	
	/////////////////////////////////////////////////////////////////////
	//
	//m_list_light.DeleteAllItems();//�ػ�·���б�
	for(int i=0;i<controller[nItem].lightsum;i++)
	{
		if(controller[nItem].lightline[i].status!=_BADLIGHT_)
		{
			controller[nItem].lightline[i].status=_OPENLIGHT_;
			controller[nItem].lightline[i].bright=255;
		}
	}

	//�ж�ѡ�еĿ������Ƿ���ʾ��·���б�
	if(controller_number==nItem)
	{
		for(int i=0;i<controller[nItem].lightsum;i++)
		{
			if(controller[nItem].lightline[i].status!=_BADLIGHT_)
			{
				m_list_light.SetItemText(i,1,"����");
				m_list_light.SetItemText(i,2,"255");
			}
		}
	}
	/////////////////////////////////////////////////////////////////////
}

//ȫ��
void CBaidumapDlg::OnMenuitem32795() 
{
	// TODO: Add your command handler code here
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	int nItem = m_list.GetNextSelectedItem(pos);
	//controller_number=nItem;
	
	/////////////////////////////////////////////////////////////////////
	//
	//m_list_light.DeleteAllItems();//�ػ�·���б�
	for(int i=0;i<controller[nItem].lightsum;i++)
	{
		if(controller[nItem].lightline[i].status!=_BADLIGHT_)
		{
			controller[nItem].lightline[i].status=_CLOSELIGHT_;
			controller[nItem].lightline[i].bright=0;
		}
	}

	//�ж�ѡ�еĿ������Ƿ���ʾ��·���б�
	if(controller_number==nItem)
	{
		for(int i=0;i<controller[nItem].lightsum;i++)
		{
			if(controller[nItem].lightline[i].status!=_BADLIGHT_)
			{
				m_list_light.SetItemText(i,1,"�ر�");
				m_list_light.SetItemText(i,2,"0");
			}
		}
	}
	/////////////////////////////////////////////////////////////////////
}

//���ŵƿ�
void CBaidumapDlg::OnMenuitem32796() 
{
	// TODO: Add your command handler code here
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	int nItem = m_list.GetNextSelectedItem(pos);
	//controller_number=nItem;
	
	/////////////////////////////////////////////////////////////////////
	//
	//m_list_light.DeleteAllItems();//�ػ�·���б�
	for(int i=0;i<controller[nItem].lightsum;i++)
	{
		if((i+1)%2&&controller[nItem].lightline[i].status!=_BADLIGHT_)
		{
			controller[nItem].lightline[i].status=_OPENLIGHT_;
			controller[nItem].lightline[i].bright=255;
		}
	}
	
	//�ж�ѡ�еĿ������Ƿ���ʾ��·���б�
	if(controller_number==nItem)
	{
		for(int i=0;i<controller[nItem].lightsum;i++)
		{
			if((i+1)%2&&controller[nItem].lightline[i].status!=_BADLIGHT_)
			{
				m_list_light.SetItemText(i,1,"����");
				m_list_light.SetItemText(i,2,"255");
			}
		}
	}
	/////////////////////////////////////////////////////////////////////
}

//���ŵƹ�
void CBaidumapDlg::OnMenuitem32797() 
{
	// TODO: Add your command handler code here
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	int nItem = m_list.GetNextSelectedItem(pos);
	//controller_number=nItem;
	
	/////////////////////////////////////////////////////////////////////
	//
	//m_list_light.DeleteAllItems();//�ػ�·���б�
	for(int i=0;i<controller[nItem].lightsum;i++)
	{
		if((i+1)%2&&controller[nItem].lightline[i].status!=_BADLIGHT_)
		{
			controller[nItem].lightline[i].status=_CLOSELIGHT_;
			controller[nItem].lightline[i].bright=0;
		}
	}
	
	//�ж�ѡ�еĿ������Ƿ���ʾ��·���б�
	if(controller_number==nItem)
	{
		for(int i=0;i<controller[nItem].lightsum;i++)
		{
			if((i+1)%2&&controller[nItem].lightline[i].status!=_BADLIGHT_)
			{
				m_list_light.SetItemText(i,1,"�ر�");
				m_list_light.SetItemText(i,2,"0");
			}
		}
	}
	/////////////////////////////////////////////////////////////////////
}

//˫�ŵƿ�
void CBaidumapDlg::OnMenuitem32798() 
{
	// TODO: Add your command handler code here
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	int nItem = m_list.GetNextSelectedItem(pos);
	//controller_number=nItem;
	
	/////////////////////////////////////////////////////////////////////
	//
	//m_list_light.DeleteAllItems();//�ػ�·���б�
	for(int i=0;i<controller[nItem].lightsum;i++)
	{
		if(i%2&&controller[nItem].lightline[i].status!=_BADLIGHT_)
		{
			controller[nItem].lightline[i].status=_OPENLIGHT_;
			controller[nItem].lightline[i].bright=255;
		}
	}
	
	//�ж�ѡ�еĿ������Ƿ���ʾ��·���б�
	if(controller_number==nItem)
	{
		for(int i=0;i<controller[nItem].lightsum;i++)
		{
			if(i%2&&controller[nItem].lightline[i].status!=_BADLIGHT_)
			{
				m_list_light.SetItemText(i,1,"����");
				m_list_light.SetItemText(i,2,"255");
			}
		}
	}
	/////////////////////////////////////////////////////////////////////
}

//˫�ŵƹ�
void CBaidumapDlg::OnMenuitem32799() 
{
	// TODO: Add your command handler code here
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	int nItem = m_list.GetNextSelectedItem(pos);
	//controller_number=nItem;
	
	/////////////////////////////////////////////////////////////////////
	//
	//m_list_light.DeleteAllItems();//�ػ�·���б�
	for(int i=0;i<controller[nItem].lightsum;i++)
	{
		if(i%2&&controller[nItem].lightline[i].status!=_BADLIGHT_)
		{
			controller[nItem].lightline[i].status=_CLOSELIGHT_;
			controller[nItem].lightline[i].bright=0;
		}
	}
	
	//�ж�ѡ�еĿ������Ƿ���ʾ��·���б�
	if(controller_number==nItem)
	{
		for(int i=0;i<controller[nItem].lightsum;i++)
		{
			if(i%2&&controller[nItem].lightline[i].status!=_BADLIGHT_)
			{
				m_list_light.SetItemText(i,1,"�ر�");
				m_list_light.SetItemText(i,2,"0");
			}
		}
	}
	/////////////////////////////////////////////////////////////////////
}
