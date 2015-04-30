/**************************************
 *FILE    :login.cpp
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :4/22/2015
 *TEXT    :DataStructure for Street light control system
 *EMAIL   :gtsoft_wk@foxmail.com
***************************************/

#include "stdafx.h"
#include "baidumap.h"
#include "login.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// login dialog


login::login(CWnd* pParent /*=NULL*/)
	: CDialog(login::IDD, pParent)
{
	//{{AFX_DATA_INIT(login)
	m_user = _T("");
	m_password = _T("");
	//}}AFX_DATA_INIT
}


void login::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(login)
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(login, CDialog)
	//{{AFX_MSG_MAP(login)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// login message handlers

// BKDR Hash
unsigned int BKDRHash(char *str)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;
	while (*str)
	{
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}

void login::OnOK() 
{
	// TODO: Add extra validation here
	string strtemp;
	unsigned int num;

	//获取程序运行目录
	CString path;
    GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
    path.ReleaseBuffer();
    int pos = path.ReverseFind('\\');
    path = path.Left(pos);

	path+="\\option.ini";
	ifstream rootdata(path);
	rootdata>>num;
	rootdata.close();
	this->UpdateData(true);
    CWnd *pWnd = NULL;
	strtemp = this->m_user + "." + this->m_password; 
    //if (this->m_user != "wangk"||this->m_password != "zxc")
	if(BKDRHash((char*)strtemp.data())!=num)
    {
        MessageBox("用户名/密码错误!请重试");
		pWnd = GetDlgItem(IDC_EDIT1);// 获取的控件指针
        pWnd->SetFocus();// 设置焦点
    }
    else
    {
        CDialog::OnOK();
    }
	//CDialog::OnOK();
}
