//---------------------------------------------------------------------------
#pragma hdrstop 
#pragma comment(lib, "ws2_32.lib") 
#include <winsock2.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include "ControlCode.h"
#include "DataStructure.h"

using namespace std ;
//---------------------------------------------------------------------------

SOCKET sockClient ;
struct sockaddr_in addrServer ;
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
    addrServer.sin_addr.s_addr=inet_addr("127.0.0.1");//222.247.47.182");//
    addrServer.sin_port=htons(5555);//9090);
theend:;
    cout<<"���ӷ�����..."<<endl ;
    if(connect(sockClient,(const struct sockaddr*)&addrServer,sizeof(sockaddr))!=0)
    {
        cout<<"connect ʧ��"<<endl ;
        WSACleanup();
		Sleep(1000);
        goto theend ;
    }
    cout<<"��ʼ���Ͳ��԰�"<<endl ;
    //memset(buf,0,24);
    //while(true)
    LAMP_STATUS data;

	srand(time(NULL));
	data.UID=rand()%10000;
	data.NUM=20;
	data.CMD=rand()%3+7;
    int i;
	for(i=0;i<20;i++)
    {
	data.DATA[i].ID=rand()%100000;
		data.DATA[i].voltage=1.2;
		data.DATA[i].current=2.3;
		data.DATA[i].temp=3.4;
		data.DATA[i].brightness=45;
    }
    cout<<"���ͣ�"<<endl ;
	printf(":%d",sizeof(data));
    if(send(sockClient,(char*)&data,sizeof(data),0)<=0)
    {
        cout<<"sendʧ��,�������ӶϿ�"<<endl ;
        //break;
		Sleep(1000);
        goto theend ;
    }
    //���շ����Ӧ��
	char buf[24];
	if(recv(sockClient,buf,24,0)<=0)
	{
		cout<<"recvʧ��,�������ӶϿ�"<<endl ;
		//break;
		goto theend ;
	}
	//cout<<"003"<<endl;
	cout<<"������Ӧ��"<<buf<<endl ;
	memset(buf,0,24);
	WSACleanup();
    return 0 ;
}
