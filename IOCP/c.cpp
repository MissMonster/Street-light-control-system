//---------------------------------------------------------------------------

#pragma hdrstop 
#pragma comment(lib, "ws2_32.lib") 
#include <winsock2.h>
#include <stdio.h>
#include <iostream>

using namespace std ;
//---------------------------------------------------------------------------

//#pragma argsused 

SOCKET sockClient ;
struct sockaddr_in addrServer ;
char buf[432]="this is a test message,it is 432.........\
..............................................................\
..............................................................\
..............................................................\
..............................................................\
..............................................................\
................................................................................";
int n=0 ;

int Init()
{
    WSAData wsaData ;
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
    {
        cout<<"WSAStartup失败"<<endl ;
        return-1 ;
    }
    
    if(LOBYTE(wsaData.wVersion)!=2||HIBYTE(wsaData.wVersion)!=2)
    {
        cout<<"SOCKET版本不对"<<endl ;
        WSACleanup();
        return-1 ;
    }
    return 0 ;
}

int main(int argc,char*argv[])
{
    if(Init()!=0)
    goto theend ;
    
    sockClient=socket(AF_INET,SOCK_STREAM,0);
    if(sockClient==INVALID_SOCKET)
    {
        cout<<"socket 失败"<<endl ;
        WSACleanup();
        goto theend ;
    }
    memset(&addrServer,0,sizeof(sockaddr_in));
    addrServer.sin_family=AF_INET ;
    addrServer.sin_addr.s_addr=inet_addr("192.168.1.31");//222.247.47.182");//
    addrServer.sin_port=htons(5555);//9090);
    cout<<"连接服务器..."<<endl ;
    if(connect(sockClient,(const struct sockaddr*)&addrServer,sizeof(sockaddr))!=0)
    {
        cout<<"connect 失败"<<endl ;
        WSACleanup();
        goto theend ;
    }
    cout<<"开始发送测试包"<<endl ;
    //memset(buf,0,24);
    //while(true)
    {
        cout<<"发送："<<buf<<endl ;
        if(send(sockClient,buf,432,0)<=0)
        {
            cout<<"send失败,可能连接断开"<<endl ;
            //break;
            goto theend ;
        }
		//cout<<"001"<<endl;
        memset(buf,0,24);
        //cout<<"002"<<endl;
        
		//接收服务端应答
        if(recv(sockClient,buf,24,0)<=0)
        {
            cout<<"recv失败,可能连接断开"<<endl ;
            //break;
            goto theend ;
        }
		//cout<<"003"<<endl;
        cout<<"服务器应答："<<buf<<endl ;
        memset(buf,0,24);
        
        Sleep(200);
        n++;
    }
    if(0)
	{
		theend :
		WSACleanup();
		//getchar();
		Sleep(5000);
	}
	else
	{
		WSACleanup();
	}
    return 0 ;
}
