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

vector<CONTROLDATA> controller;
int controller_number=-1;
int light_number=-1;

/////////////////////////////////////////////////////////////////////////////
// CBaidumapDlg dialog

CBaidumapDlg::CBaidumapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBaidumapDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBaidumapDlg)
	m_long = _T("");
	m_lat = _T("");
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
	DDX_Text(pDX, IDC_EDIT2, m_long);
	DDX_Text(pDX, IDC_EDIT1, m_lat);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBaidumapDlg, CDialog)
	//{{AFX_MSG_MAP(CBaidumapDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkList2)
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

	//获取程序运行目录
	CString path;
    GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
    path.ReleaseBuffer();
    int pos = path.ReverseFind('\\');
    path = path.Left(pos);
	path+="\\baidumap.html";
	m_map.Navigate(path, NULL, NULL, NULL, NULL);

	//设置控制器列表主题
	m_list.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
        | LVS_EX_FULLROWSELECT		// 允许正航选中
        | LVS_EX_GRIDLINES			// 画出网格线
    );

	m_list.InsertColumn(0,"标识码"	,LVCFMT_CENTER, 60,0);
	m_list.InsertColumn(1,"信息"	,LVCFMT_CENTER, 60,0);
	m_list.InsertColumn(2,"纬度"	,LVCFMT_CENTER, 80,0);
	m_list.InsertColumn(3,"经度"	,LVCFMT_CENTER, 80,0);
	m_list.InsertColumn(4,"路灯数量",LVCFMT_CENTER, 70,0);
	m_list.InsertColumn(5,"运行方式",LVCFMT_CENTER, 70,0);

	//设置路灯列表主题
	m_list_light.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
        | LVS_EX_FULLROWSELECT		// 允许正航选中
        | LVS_EX_GRIDLINES			// 画出网格线
		);
	
	m_list_light.InsertColumn(0,"编号"	,LVCFMT_CENTER, 60,0);
	m_list_light.InsertColumn(1,"电压"	,LVCFMT_CENTER, 60,0);
	m_list_light.InsertColumn(2,"电流"	,LVCFMT_CENTER, 60,0);
	m_list_light.InsertColumn(3,"纬度"	,LVCFMT_CENTER, 80,0);
	m_list_light.InsertColumn(4,"经度"	,LVCFMT_CENTER, 80,0);
	m_list_light.InsertColumn(5,"状态"	,LVCFMT_CENTER, 60,0);

	//产生随机20个控制器数据
	for(int i=0;i<100;i++)
	{
		CONTROLDATA temp;
		temp.id=rand()%1000;
		temp.lightmessage[0]='A'+rand()%26;
		temp.lightmessage[1]='\0';
		temp.Latitude=28.190991+rand()%10000*0.00001;
		temp.Longitude=112.956087+rand()%10000*0.00001;
		temp.lightsum=100+rand()%50;
		temp.theway=rand()%2;
		controller.push_back(temp);

		CString str;
		str.Format(_T("%d"),temp.id);
		m_list.InsertItem(i,str);

		m_list.SetItemText(i,1,temp.lightmessage);
		
		str.Format(_T("%lf"),temp.Longitude);
		m_list.SetItemText(i,2,str);
		
		str.Format(_T("%lf"),temp.Latitude);
		m_list.SetItemText(i,3,str);
		
		str.Format(_T("%d"),temp.lightsum);
		m_list.SetItemText(i,4,str);
		
		str.Format(_T("%d"),temp.theway);
		m_list.SetItemText(i,5,str);

		//产生随机n个路灯数据
		for(int j=0;j<temp.lightsum;j++)
		{
			LIGHTDATA tempone;
			tempone.id=j+1;
			tempone.voltage=10+rand()%10;
			tempone.current=1+rand()%10*0.1;
			tempone.Latitude=controller[i].Latitude+rand()%1000*0.00001;
			tempone.Longitude=controller[i].Longitude+rand()%1000*0.00001;
			tempone.status=rand()%2;
			controller[i].lightline.push_back(tempone);
		}
	}

	/////////////////////////////////////////////////////////////////////
	//MessageBox("数据初始化完成!",NULL,MB_OK);
	/////////////////////////////////////////////////////////////////////

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

void setpointinmap(CWebBrowser2 m_map,double lat,double lon)
{
	// TODO: Add extra validation here
    CWebPage web;
     web.SetDocument(m_map.GetDocument());  
	CString latnum;
	CString longnum;
	latnum.Format(_T("%lf"),lat);
	longnum.Format(_T("%lf"),lon);
	web.CallJScript("setpiont",latnum,longnum,"0");
}

void CBaidumapDlg::OnOK() 
{
	// TODO: Add extra validation here
	//28.183518, 112.953093
	//google
	//-0.005969,-0.006506
	//28.189487,112.959599
	//baidu
	UpdateData(TRUE);  
    CWebPage web;
    web.SetDocument(m_map.GetDocument());  
    CComVariant varResult;   
	const CString funcName("setpiont"); 
    const CString m_latitude(m_lat);  //传递的参数：纬度  
    const CString m_longtitude(m_long);  //传递的参数：经度 
	//const CString m_latitude("28.190991");//传递的参数：纬度  
    //const CString m_longtitude("112.956086");//经度  
    //web.CallJScript(funcName,m_lat,m_long); 

	double tempnum[22][2]={112.941650,28.171610,
		112.942123,28.169699,
		112.946030,28.167139,
		112.947594,28.176163,
		112.944305,28.182743,
		112.941322,28.183662,
		112.942825,28.188023,
		112.942841,28.191589,
		112.944664,28.194380,
		112.944908,28.195711,
		112.945511,28.197603,
		112.944870,28.195898,
		112.942673,28.189238,
		112.941292,28.185274,
		112.943588,28.182659,
		112.947365,28.174421,
		112.946205,28.167265,
		112.943100,28.169024,
		112.941620,28.171564,
		112.943146,28.192247,
		112.947052,28.182596,
		112.947670,28.181625};
	for(int i=0;i<22;i++)
	{
		CString latnum;
		CString longnum;
		latnum.Format(_T("%lf"),tempnum[i][1]+0.002506);
		longnum.Format(_T("%lf"),tempnum[i][0]+0.011969);
		web.CallJScript(funcName,latnum,longnum,"0");
	}
	/*for(vector<CONTROLDATA>::iterator it=controller.begin();it<controller.end();it++)
	{
		CString latnum;
		CString longnum;
		latnum.Format(_T("%lf"),it->Latitude);
		longnum.Format(_T("%lf"),it->Longitude);
		web.CallJScript(funcName,latnum,longnum,"0");
	}*/
	//CDialog::OnOK();
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
	int nItem; //保存双击行的行号
	pos = m_list.GetFirstSelectedItemPosition();
	if(pos)
	{
		nItem = m_list.GetNextSelectedItem(pos); 
		//web.CallJScript("refresh"); 
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
	web.CallJScript("setpiont",latnum,longnum,"1");

	/////////////////////////////////////////////////////////////////////
	//CString str;
	//str.Format(_T("%d:%d"),nItem,controller[nItem].lightsum);
	//MessageBox(str,NULL,MB_OK);
	/////////////////////////////////////////////////////////////////////
	 
	//在列表上显示路灯
	m_list_light.DeleteAllItems();//重绘路灯列表
	for(int i=0;i<controller[nItem].lightsum;i++)
	{
		CString str;
		str.Format(_T("%03d"),controller[nItem].lightline[i].id);
		m_list_light.InsertItem(i,str);

		str.Format(_T("%8.3lf"),controller[nItem].lightline[i].voltage);
		m_list_light.SetItemText(i,1,str);
		
		str.Format(_T("%8.3lf"),controller[nItem].lightline[i].current);
		m_list_light.SetItemText(i,2,str);
		
		str.Format(_T("%lf"),controller[nItem].lightline[i].Longitude);
		m_list_light.SetItemText(i,3,str);
		
		str.Format(_T("%lf"),controller[nItem].lightline[i].Latitude);
		m_list_light.SetItemText(i,4,str);
		
		str.Format(_T("%d"),controller[nItem].lightline[i].status);
		m_list_light.SetItemText(i,5,str);

		latnum.Format(_T("%lf"),controller[nItem].lightline[i].Latitude);
		longnum.Format(_T("%lf"),controller[nItem].lightline[i].Longitude);
		web.CallJScript("setpiont",latnum,longnum,"0");
	}

	*pResult = 0;
}

void CBaidumapDlg::OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CWebPage web;
    web.SetDocument(m_map.GetDocument()); 
	POSITION pos;
	int nItem; //保存双击行的行号
	pos = m_list.GetFirstSelectedItemPosition();
	if(pos)
	{
		nItem = m_list.GetNextSelectedItem(pos); 
		//web.CallJScript("refresh"); 
	}
	else return ;
	if(nItem==light_number)return ;
	else light_number=nItem;
	CString latnum;
	CString longnum;
	latnum.Format(_T("%lf"),controller[controller_number].lightline[nItem].Latitude);
	longnum.Format(_T("%lf"),controller[controller_number].lightline[nItem].Longitude);
	//web.CallJScript("refresh");
	//web.CallJScript("removeall");
	web.CallJScript("movetoplace",latnum,longnum);

	*pResult = 0;
}

