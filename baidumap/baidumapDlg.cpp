// baidumapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "baidumap.h"
#include "baidumapDlg.h"
#include "webbrowser2.h"
#include "WebPage.h"
#include "DataStructure.h"
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
int controller_number = -1;
int light_number = -1;
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
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
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

	//�������20������������
	for(int i=0;i<100;i++)
	{
		CONTROLDATA temp;
		temp.id=rand()%1000;
		temp.lightmessage[0]='A'+rand()%26;
		temp.lightmessage[1]='\0';
		temp.Latitude=28.190991+rand()%10000*0.00001;
		temp.Longitude=112.956087+rand()%10000*0.00001;
		temp.lightsum=50+rand()%50;
		temp.theway=rand()%2;
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
			tempone.status=rand()%3;
			controller[i].lightline.push_back(tempone);
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

void CBaidumapDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here   
    CWebPage web;
    web.SetDocument(m_map.GetDocument()); 
    web.CallJScript("refresh"); 
}

void CBaidumapDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CWebPage web;
    web.SetDocument(m_map.GetDocument()); 
	POSITION pos;
	int nItem; //����˫���е��к�
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
	//web.CallJScript("refresh");
	web.CallJScript("removeall");
	web.CallJScript("movetoplace",latnum,longnum);

	/////////////////////////////////////////////////////////////////////
	//��ʾ��������Ϣ
	CString str;
	CString temp;
	str.Format(_T("%04d"),controller[nItem].id);
	temp="��ʶ��:"+str+"<br>";
	
	str.Format(_T("%d"),controller[nItem].lightmessage);
	temp=temp+"��Ϣ:"+str+"<br>";
	
	str.Format(_T("%8.3lf"),controller[nItem].Longitude);
	temp=temp+"γ��:"+str+"<br>";
	
	str.Format(_T("%lf"),controller[nItem].Latitude);
	temp=temp+"����:"+str+"<br>";
	
	str.Format(_T("%d"),controller[nItem].lightsum);
	temp=temp+"·������:"+str+"<br>";
	
	str.Format(_T("%d"),controller[nItem].theway);
	temp=temp+"���з�ʽ:"+str;

	web.CallJScript("setanipiont",latnum,longnum,temp);
	 
	/////////////////////////////////////////////////////////////////////
	//���б�����ʾ·��
	m_list_light.DeleteAllItems();//�ػ�·���б�
	for(int i=0;i<controller[nItem].lightsum;i++)
	{
		CString str;
		CString temp;
		str.Format(_T("%04d"),controller[nItem].lightline[i].id);
		m_list_light.InsertItem(i,str);
		temp="���:"+str+"<br>";

		str.Format(_T("%8.3lf"),controller[nItem].lightline[i].voltage);
		temp=temp+"��ѹ:"+str+"<br>";
		
		str.Format(_T("%8.3lf"),controller[nItem].lightline[i].current);
		temp=temp+"����:"+str+"<br>";
		
		str.Format(_T("%lf"),controller[nItem].lightline[i].Longitude);
		temp=temp+"γ��:"+str+"<br>";
		
		str.Format(_T("%lf"),controller[nItem].lightline[i].Latitude);
		temp=temp+"����:"+str+"<br>";
		
		switch(controller[nItem].lightline[i].status)
		{
		case 0:
			str="�ر�";
			break;
		case 1:
			str="����";
			break;
		case 2:
			str="����";
			break;
		}
		m_list_light.SetItemText(i,1,str);
		temp=temp+"״̬:"+str;

		latnum.Format(_T("%lf"),controller[nItem].lightline[i].Latitude);
		longnum.Format(_T("%lf"),controller[nItem].lightline[i].Longitude);

		web.CallJScript("setstapiont",latnum,longnum,temp);
	}
	/////////////////////////////////////////////////////////////////////

	*pResult = 0;
}

void CBaidumapDlg::OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CWebPage web;
    web.SetDocument(m_map.GetDocument()); 
	POSITION pos;
	int nItem; //����˫���е��к�
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
		//web.CallJScript("refresh");
		//web.CallJScript("removeall");
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

//���ӿ�����
void CBaidumapDlg::OnMenuitem32777() 
{
	// TODO: Add your command handler code here
	CString str;
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	int nItem = m_list.GetNextSelectedItem(pos);
	str.Format("��ǰѡ�е��ǵ�%d��",nItem+1);
	MessageBox(str,NULL,MB_OK);
}

//�޸Ŀ�����
void CBaidumapDlg::OnMenuitem32773() 
{
	// TODO: Add your command handler code here
	CString str;
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	int nItem = m_list.GetNextSelectedItem(pos);
	str.Format("��ǰѡ�е��ǵ�%d��",nItem+1);
	MessageBox(str,NULL,MB_OK);
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
	//POSITION pos = m_list.GetFirstSelectedItemPosition();
	controller_number = -1;//m_list.GetNextSelectedItem(pos); 

	/////////////////////////////////////////////////////////////////////
	//���������
	CWebPage web;
	web.SetDocument(m_map.GetDocument()); 
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
		m_list_light.SetItemText(nItem,1,"����");
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
		m_list_light.SetItemText(nItem,1,"�ر�");
	}
}
/////////////////////////////////////////////////////////////////////

