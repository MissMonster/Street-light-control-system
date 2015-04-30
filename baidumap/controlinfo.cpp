/**************************************
 *FILE    :controlinfo.cpp
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :4/22/2015
 *TEXT    :DataStructure for Street light control system
 *EMAIL   :gtsoft_wk@foxmail.com
***************************************/

#include "stdafx.h"
#include "baidumap.h"
#include "controlinfo.h"
#include "DataStructure.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// controlinfo dialog


controlinfo::controlinfo(CWnd* pParent /*=NULL*/)
	: CDialog(controlinfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(controlinfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void controlinfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(controlinfo)
	DDX_Control(pDX, IDC_COMBO1, m_status);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(controlinfo, CDialog)
	//{{AFX_MSG_MAP(controlinfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// controlinfo message handlers

BOOL controlinfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	extern CONTROLDATA continfo; 
	//拿到Combo box的输入框（Combo box的第一个子窗口：GW_CHILD）。m_GZZ为CComboBox对象
	CEdit* pEdit = (CEdit*)m_status.GetWindow(GW_CHILD);
	// 将输入框色设置为只读
	pEdit->SetReadOnly(TRUE);
	
	//修改
	if(continfo.id!=-1)
	{
		CString str;
		str.Format("%d",continfo.id);
		GetDlgItem(IDC_EDIT1)->SetWindowText(str);
		
		//continfo.lightmessage;
		GetDlgItem(IDC_EDIT2)->SetWindowText(continfo.lightmessage);
		
		str.Format("%lf",continfo.Longitude);
		GetDlgItem(IDC_EDIT3)->SetWindowText(str);
		
		str.Format("%lf",continfo.Latitude);
		GetDlgItem(IDC_EDIT4)->SetWindowText(str);
		
		str.Format("%d",continfo.lightsum);
		GetDlgItem(IDC_EDIT5)->SetWindowText(str);

		m_status.SetCurSel(continfo.theway);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void controlinfo::OnOK() 
{
	// TODO: Add extra validation here
	extern CONTROLDATA continfo;
	CString str;
	GetDlgItem(IDC_EDIT2)->GetWindowText(str);
	if(str.GetLength()<30)
	{	
		GetDlgItem(IDC_EDIT1)->GetWindowText(str);
		continfo.id=atoi(str.GetBuffer(10)); 
	
		GetDlgItem(IDC_EDIT2)->GetWindowText(str);
		memcpy(continfo.lightmessage,str,str.GetLength());
		continfo.lightmessage[str.GetLength()]='\0';
	
		GetDlgItem(IDC_EDIT3)->GetWindowText(str);
		continfo.Longitude=atof(str);
	
		GetDlgItem(IDC_EDIT4)->GetWindowText(str);
		continfo.Latitude=atof(str);
	
		GetDlgItem(IDC_EDIT5)->GetWindowText(str);
		continfo.lightsum=atoi(str.GetBuffer(10));

		continfo.theway=m_status.GetCurSel();

		CDialog::OnOK();
	}
	else MessageBox("信息文字过长，请重新输入!",NULL,MB_OK);
}
