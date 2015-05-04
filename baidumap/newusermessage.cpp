// newusermessage.cpp : implementation file
//

#include "stdafx.h"
#include "baidumap.h"
#include "newusermessage.h"
#include "DataStructure.h"
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
// newusermessage dialog


newusermessage::newusermessage(CWnd* pParent /*=NULL*/)
	: CDialog(newusermessage::IDD, pParent)
{
	//{{AFX_DATA_INIT(newusermessage)
	m_newname = _T("");
	m_newpassword = _T("");
	//}}AFX_DATA_INIT
}


void newusermessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(newusermessage)
	DDX_Text(pDX, IDC_EDIT1, m_newname);
	DDX_Text(pDX, IDC_EDIT2, m_newpassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(newusermessage, CDialog)
	//{{AFX_MSG_MAP(newusermessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// newusermessage message handlers

void newusermessage::OnOK() 
{
	// TODO: Add extra validation here
	string strtemp;
	extern unsigned int BKDRHash(char *str);
	
	//获取程序运行目录
	CString path;
    GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
    path.ReleaseBuffer();
    int pos = path.ReverseFind('\\');
    path = path.Left(pos);
	
	path+="\\option.ini";
	ofstream rootdata(path);
	
	this->UpdateData(true);
	strtemp = this->m_newname + "." + this->m_newpassword;
	rootdata<<BKDRHash((char*)strtemp.data());
	rootdata.close();
	
    MessageBox("用户名和密码修改成功!");
	CDialog::OnOK();
}
