// LampServerView.cpp : implementation of the CLampServerView class
//

#include "stdafx.h"
#include "LampServer.h"

#include "LampServerDoc.h"
#include "LampServerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLampServerView

IMPLEMENT_DYNCREATE(CLampServerView, CFormView)

BEGIN_MESSAGE_MAP(CLampServerView, CFormView)
	//{{AFX_MSG_MAP(CLampServerView)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_MESSAGE(WM_SERVERMSG,OnServerMsg)//////////////////////////////******************************
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLampServerView construction/destruction

CLampServerView::CLampServerView()
	: CFormView(CLampServerView::IDD)
{
	//{{AFX_DATA_INIT(CLampServerView)
	m_strShow = _T("");
	m_strMsg = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CLampServerView::~CLampServerView()
{
}

void CLampServerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLampServerView)
	DDX_Text(pDX, IDC_EDIT1, m_strShow);
	DDX_Text(pDX, IDC_EDIT2, m_strMsg);
	//}}AFX_DATA_MAP
}

BOOL CLampServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CLampServerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CLampServerView diagnostics

#ifdef _DEBUG
void CLampServerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLampServerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CLampServerDoc* CLampServerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLampServerDoc)));
	return (CLampServerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLampServerView message handlers

void CLampServerView::OnButton1() 
{
	// TODO: Add your control notification handler code here
		try{
		WSADATA wsaData;
		WORD wVersionRequested=MAKEWORD(2,0);
		WSAStartup(wVersionRequested,&wsaData);
		m_hSocket = socket(AF_INET,SOCK_STREAM,0);
		UINT len=WSAGetLastError();
		if(len!=0)
			throw len;
		m_saList.RemoveAll();
		WSAAsyncSelect(m_hSocket,this->m_hWnd,WM_SERVERMSG,FD_ACCEPT|FD_READ|FD_WRITE|FD_CLOSE);
		m_uPort = 8080;
		m_addr.sin_family=AF_INET;
		m_addr.sin_addr.S_un.S_addr=INADDR_ANY;
		m_addr.sin_port=htons(m_uPort);
		bind(m_hSocket,(LPSOCKADDR)&m_addr,sizeof(m_addr));
		//bind(m_hSocket,(SOCKADDR*)&m_addr,sizeof(m_addr));
		listen(m_hSocket,3);
		len=WSAGetLastError();
		if(len!=0)
			throw len;
		m_strShow=_T("服务器启动成功………………\r\n");
	}
	catch(UINT &error)
	{
		switch(error)
		{
		case WSANOTINITIALISED:
			MessageBox("创建套接字失败!");
			m_strShow=_T("创建套接字失败");
			break;
		case WSAEINVAL:
			MessageBox("服务器端口已被占用!");
			m_strShow=_T("服务器启动失败");
			break;
		default:
			MessageBox("监听端口已被占用!");
			m_strShow=_T("服务器启动失败");
			break;
		}
	}
	UpdateData(FALSE);
}

void CLampServerView::OnButton2() 
{
	// TODO: Add your control notification handler code here
		m_strShow=_T("服务器已关闭………………\r\n");
		UpdateData(FALSE);
		closesocket(m_hSocket);
		WSAAsyncSelect(m_hSocket,this->m_hWnd,0,0);
		WSACleanup();
	
}

void CLampServerView::OnButton3() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	m_strShow+=_T("\r\n");
	m_strShow+=m_strMsg;
	SOCKET s;
	for(int i=0;i<m_saList.GetCount();i++)
	{
		s=m_saList.GetAt(m_saList.FindIndex(i));
		int t=send(s,m_strMsg.GetBuffer(0),m_strMsg.GetLength(),0);
		if(t<0)
		{
			closesocket(s);   
			m_saList.RemoveAt(m_saList.FindIndex(i));
		}
	}
	m_strMsg.Empty();
	UpdateData(FALSE);
	m_Show.LineScroll(m_Show.GetLineCount());


}

long CLampServerView::OnServerMsg(WPARAM wParam, LPARAM lParam)
{
	SOCKET socket,s;
	int i,j;
	char buf[1024],name[6],buf1[1024];
	int len;
	int mlen=sizeof(SOCKADDR);
	switch(lParam)
	{
	case FD_ACCEPT:
		socket=accept(m_hSocket,NULL,NULL);
		//socket=accept(m_hSocket,(SOCKADDR*)&m_addr,&mlen);
		for(i=0;i<m_saList.GetCount();i++)
		{
			s=m_saList.GetAt(m_saList.FindIndex(i));///////////////////////////////////////////
			//UintToChar(socket,name);
			m_strShow+="\r\n";
			itoa(socket,name,10);
			buf[0]=NULL;
			strcat(buf,"socket");
			strcat(buf,name);
			strcat(buf,"连接");
			len=send(s,buf,strlen(buf),0);////////////////////////////////////////////////////
			if(len<0)
			{
				closesocket(s);
				m_saList.RemoveAt(m_saList.FindIndex(i));
			}
		}
		m_strShow+="\r\n";
		itoa(socket,name,10);
		//UintToChar(socket,name);
		m_strShow+="socket";
		m_strShow+=name;
		m_strShow+="连接";
		UpdateData(FALSE);
		m_saList.AddHead(socket);
		return 0;
	case FD_READ:
	//	length=m_saList.GetCount();
		//for(i=0;i<length;i++)
		for(i=0;i<m_saList.GetCount();i++)
		{
			s=m_saList.GetAt(m_saList.FindIndex(i));
			if(s==wParam)
			{
			len=recv(s,buf,1024,0);
			//UintToChar(wParam,name);
			itoa(wParam,name,10);
			buf[len]=NULL;
			buf1[0]='\0';
			strcat(buf1,"socket");
			strcat(buf1,name);
			strcat(buf1,"发送");
			strcat(buf1,buf);
			for(j=0;j<m_saList.GetCount();j++)
			{
				s=m_saList.GetAt(m_saList.FindIndex(j));
				if(s!=wParam)
				{
					len=send(s,buf1,strlen(buf1),0);
					if(len<0)
					{
						closesocket(s);
						m_saList.RemoveAt(m_saList.FindIndex(j));
					}
				}
			}
			len=WSAGetLastError();
			len=WSAENOTCONN;
			m_strShow+="\r\n";
			m_strShow+=buf1;
			UpdateData(FALSE);
			return 0;
			}
		}
		return 0;
	case FD_WRITE:
		return 0;
	case FD_CLOSE:
		//UintToChar(wParam,name);
		itoa(wParam,name,10);
		m_strShow+="\r\n";
		m_strShow+="socket";
		m_strShow+=name;
		m_strShow+="断开";
		UpdateData(FALSE);
		return 0;
	}
}

void CLampServerView::OnDragLeave() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CFormView::OnDragLeave();
}

void CLampServerView::OnDestroy() 
{
	CFormView::OnDestroy();
	
	// TODO: Add your message handler code here
	WSAAsyncSelect(m_hSocket,this->m_hWnd,0,0);
	WSACleanup();
}
