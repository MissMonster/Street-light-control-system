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
        cout<<"WSAStartupʧ��"<<endl ;
        return-1 ;
    }
    
    if(LOBYTE(wsaData.wVersion)!=2||HIBYTE(wsaData.wVersion)!=2)
    {
        cout<<"SOCKET�汾����"<<endl ;
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
        cout<<"socket ʧ��"<<endl ;
        WSACleanup();
        goto theend ;
    }
    memset(&addrServer,0,sizeof(sockaddr_in));
    addrServer.sin_family=AF_INET ;
    addrServer.sin_addr.s_addr=inet_addr("192.168.1.31");//222.247.47.182");//
    addrServer.sin_port=htons(5555);//9090);
    cout<<"���ӷ�����..."<<endl ;
    if(connect(sockClient,(const struct sockaddr*)&addrServer,sizeof(sockaddr))!=0)
    {
        cout<<"connect ʧ��"<<endl ;
        WSACleanup();
        goto theend ;
    }
    cout<<"��ʼ���Ͳ��԰�"<<endl ;
    //memset(buf,0,24);
    //while(true)
    {
        cout<<"���ͣ�"<<buf<<endl ;
        if(send(sockClient,buf,432,0)<=0)
        {
            cout<<"sendʧ��,�������ӶϿ�"<<endl ;
            //break;
            goto theend ;
        }
		//cout<<"001"<<endl;
        memset(buf,0,24);
        //cout<<"002"<<endl;
        
		//���շ����Ӧ��
        if(recv(sockClient,buf,24,0)<=0)
        {
            cout<<"recvʧ��,�������ӶϿ�"<<endl ;
            //break;
            goto theend ;
        }
		//cout<<"003"<<endl;
        cout<<"������Ӧ��"<<buf<<endl ;
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
