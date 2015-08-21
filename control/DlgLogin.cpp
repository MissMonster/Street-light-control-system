// DlgLogin.cpp : implementation file
//

#include "stdafx.h"
#include "LampServer.h"
#include "DlgLogin.h"
//#include "../include/md5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin dialog


CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLogin)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLogin)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialog)
	//{{AFX_MSG_MAP(CDlgLogin)
	ON_WM_TIMER()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin message handlers

void CDlgLogin::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlgLogin::OnOK() 
{
	// TODO: Add extra validation here
	CString strusername,strPassword;
	GetDlgItemText(IDC_EDIT1,strusername);
	GetDlgItemText(IDC_EDIT2,strPassword);

	if(strusername==""||strPassword=="")
	{
		AfxMessageBox(_T("用户名或密码都不能为空!"));
		return;
	}
	string dbName = theApp.m_database;
	string host = theApp.m_server;
	string user = theApp.m_username;
	string password = theApp.m_password;
	Database_Param Database_p(host,user,password,dbName,0,NULL,0);
	CMysql mysql;
	if(mysql.ConnectDB(&Database_p))
	{
	//	MD5 cmd5;
	//	string pwd=strPassword;
	//	cmd5.update(pwd);
	//	CString strIn;
	//	string strTemp=cmd5.toString();
	//	strIn.Format(_T("%s"),strTemp.c_str());
	//	strIn.Format(_T("%s"),pwd);
	string strSQL="select * from t_userinfo where UserName='"+strusername+"' and Password='"+strPassword+"'";
		if(mysql.FindSave(strSQL))
		{
			int rows=mysql.GetRowNum();
			if(rows)
			{
				theApp.m_currentUsername=strusername;
				CDialog::OnOK();	
			}
			else
			{
					AfxMessageBox("用户名或者密码错误!");
			}
		}
		else
		{
			AfxMessageBox("执行失败");
		}	
	}
	else
	{
		string ss=mysql.OutErrors();
		AfxMessageBox("连接失败！");
	}


/*
	if( strusername=="admin"&&strPassword=="111")
		CDialog::OnOK();
	else
		AfxMessageBox("用户名或者密码错误!");
//	CDialog::OnOK();*/
}

BOOL CDlgLogin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	SetTimer(0,100,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLogin::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==0)
	{
		GetDlgItem(IDC_EDIT1)->SetFocus();
		KillTimer(0);
	}
	CDialog::OnTimer(nIDEvent);
}

BOOL CDlgLogin::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( pMsg->message == WM_KEYDOWN )
	{
		UINT nKey = (int)pMsg->wParam; 
		
		 if( VK_RETURN == nKey )
		{
			OnOK();
			return TRUE ;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgLogin::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}
