/**************************************
 *FILE    :D:\c\light\receive\s.cpp
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/8/16 11:10:34
 *TEXT    :
     This sample illustrates how to develop a simple echo server Winsock
     application using the completeion port I/O model. This	 
     sample is implemented as a console-style application and simply prints
     messages when connections are established and removed from the server.
     The application listens for TCP connections on port 5150 and accepts them
     as they arrive. When this application receives data from a client, it
     simply echos (this is why we call it an echo server) the data back in
     it's original form until the client closes the connection.
 *EMAIL   :gtsoft_wk@foxmail.com
 *CODE    :https://github.com/707wk
 *LOGO    :
               #########                       
              ############                     
              #############                    
             ##  ###########                   
            ###  ###### #####                  
            ### #######   ####                 
           ###  ########## ####                
          ####  ########### ####               
        #####   ###########  #####             
       ######   ### ########   #####           
       #####   ###   ########   ######         
      ######   ###  ###########   ######       
     ######   #### ##############  ######      
    #######  ##################### #######     
    #######  ##############################    
   #######  ###### ################# #######   
   #######  ###### ###### #########   ######   
   #######    ##  ######   ######     ######   
   #######        ######    #####     #####    
    ######        #####     #####     ####     
     #####        ####      #####     ###      
      #####      ;###        ###      #        
        ##       ####        ####              

***************************************/

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"mysql/libmysql.lib")
#include <winsock2.h>  
#include <mswsock.h> 
#include <windows.h>
#include <stdio.h>
#include "DataStructure.h"
#include "mysql/mysql.h"

#define PORT            5555                 //端口号
#define DATA_BUFSIZE    412                  //数据长度
#define DATA_TMP_SIZE   100                 //缓存长度
#define mysqlip         "127.0.0.1"      
#define mysqlname       "light"    
#define mysqlpassword   "123456"        
#define mysqldatatable  "light"   

MYSQL mysql;                                 //mysql数据库指针

FILE* fpout;                                 //log指针

typedef struct
{
	OVERLAPPED Overlapped;
	WSABUF DataBuf;
	CHAR Buffer[DATA_BUFSIZE];
	CHAR ip[20];
	UINT port;
	DWORD BytesSEND;
	DWORD BytesRECV;
	int index;
} PER_IO_OPERATION_DATA, * LPPER_IO_OPERATION_DATA;

LAMP_DATA_TMP data_tmp[DATA_TMP_SIZE];
int head;
int end;

typedef struct	 
{
	SOCKET Socket;
} PER_HANDLE_DATA, * LPPER_HANDLE_DATA;

DWORD WINAPI ServerWorkerThread(LPVOID CompletionPortID)	
{	
	HANDLE CompletionPort = (HANDLE) CompletionPortID;	
	DWORD BytesTransferred;	
	LPOVERLAPPED Overlapped;	
	//LPPER_HANDLE_DATA PerHandleData;	
	//LPPER_IO_OPERATION_DATA PerIoData;	
	DWORD SendBytes, RecvBytes;	
	DWORD Flags;	

	while(TRUE)
	{
		LPPER_HANDLE_DATA PerHandleData;	
		LPPER_IO_OPERATION_DATA PerIoData;	
			  
		if (GetQueuedCompletionStatus(CompletionPort, &BytesTransferred,	
			(LPDWORD)&PerHandleData, (LPOVERLAPPED *) &PerIoData, INFINITE) == 0)	
		{	
//			printf("GetQueuedCompletionStatus failed with error %d\n", GetLastError());	
//			return 0;	
		}

		////////////////////////////////////////////////////////////////////////
		if(BytesTransferred>0)
		{
			// Post another WSASend() request.	
			// Since WSASend() is not gauranteed to send all of the bytes requested,	
			// continue posting WSASend() calls until all received bytes are sent.	
	
			ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));	
	
			PerIoData->DataBuf.buf = PerIoData->Buffer + PerIoData->BytesSEND;	
			PerIoData->DataBuf.len = PerIoData->BytesRECV - PerIoData->BytesSEND;	
	
			printf("[%s:%u:%d]start",PerIoData->ip,PerIoData->port,PerIoData->index);
			memcpy(&data_tmp[PerIoData->index].data,PerIoData->DataBuf.buf,DATA_BUFSIZE);
	/*
			if (WSASend(PerHandleData->Socket, &(PerIoData->DataBuf), 1, &SendBytes, 0,	
				&(PerIoData->Overlapped), NULL) == SOCKET_ERROR)	
			{	
				if (WSAGetLastError() != ERROR_IO_PENDING)	
				{	
					printf("WSASend() failed with error %d\n", WSAGetLastError());	
					return 0;	
				}	
			}	
			ZeroMemory(PerIoData->DataBuf.buf,PerIoData->DataBuf.len);			  
*/
			//if (BytesTransferred == 0)	
			{	
				printf("[%s:%u]end!!\n",PerIoData->ip,PerIoData->port);	 
				if (closesocket(PerHandleData->Socket) == SOCKET_ERROR)	
				{	
					printf("closesocket() failed with error %d\n", WSAGetLastError());	
					return 0;	
				}	
	
				//GlobalFree(PerHandleData);	
				//GlobalFree(PerIoData);	
				//continue;	
			}	
		}	
		////////////////////////////////////////////////////////////////////////	
	}	
}  

//存储数据
DWORD WINAPI savedata(LPVOID channel)
{
	//string 
	int client_num;
	printf("writing data\n");
	int sum=0;
	int error=0;
	for(;;)
	{
		client_num=(end+DATA_TMP_SIZE-head)%DATA_TMP_SIZE;
		if(client_num>0)
		{
			//printf("start save\n");
			for(;client_num>0;client_num--)
			{
				LAMP_DATA_TMP* p=data_tmp+head;
				int len=p->data.NUM;
				if(len>0)
				{
				////////////////////////////////////////////////////////////////////////
				string str_into="\
replace into t_lightruninfo (time,id,controllerId,\
streetlightId,streetlightVoltage,streetlightCurrent,\
streetlightTemp,streetlightBrightness,streetlightWarning) values";
				char str[500];
				sprintf(str,"(NOW(),%d,'test',%d,%f,%f,%f,%d,'this is a test')",
					p->data.UID,
					p->data.DATA[0].ID,
					p->data.DATA[0].voltage,
					p->data.DATA[0].current,
					p->data.DATA[0].temp,
					p->data.DATA[0].brightness);
				str_into+=str;

				if(len!=20)printf("NUM=%d len=%d\n",head,len);
				for(int i=1;i<len;i++)
				{
					char str[500];
					sprintf(str,",(NOW(),%d,'test',%d,%f,%f,%f,%d,'this is a test')",
						p->data.UID,
						p->data.DATA[i].ID,
						p->data.DATA[i].voltage,
						p->data.DATA[i].current,
						p->data.DATA[i].temp,
						p->data.DATA[i].brightness);
					str_into+=str;
				}
				//printf("%s\n",str_into.c_str);
				//cout<<str_into<<endl;
				if(mysql_query(&mysql,str_into.c_str())==NULL)
				{
					//printf("into success\n");
				}
				else
				{
					printf("into fail\n");
					//mysql_real_connect(&mysql, mysqlip , mysqlname, mysqlpassword, mysqldatatable, 3306, NULL, 0);
				}
				}
				else
				{
					error++;
				}
				head=(head+1)%DATA_TMP_SIZE;
				//Sleep(1000);
				sum++;
			}
			/*string sql="INSERT INTO userinfo (name, password, email) VALUES('"+sql1+"', '"+sql2+"', '"+sql3+"')" ;
			
			if(mysql_query(&mysql,sql.c_str())==0)
			{
				return -1;
			}*/
			printf("save=%d error=%d\n",sum,error);
		}
		else
		{
			Sleep(1000);
		}
	}
}

void init()
{
	////////////////////////////////////////////////////////////////////////
	//初始化日志
	fpout=fopen("log.txt","a");
	if(fpout==NULL)
	{
		printf("error! log.txt can not writing\n");
	}
	else
	{
		printf("log start\n");
	}

	////////////////////////////////////////////////////////////////////////
	//初始化mysql
	mysql_init(&mysql);
	if (mysql_real_connect(&mysql, mysqlip , mysqlname, mysqlpassword, mysqldatatable, 3306, NULL, 0) == NULL)
	{
		printf("mysql can not connect!\n");
	}
	else
	{
		printf("mysql connect!\n");
	}

	//清空缓存
	if(mysql_query(&mysql,"TRUNCATE TABLE t_lightruninfo")==NULL)
	{
		//printf("into success\n");
		printf("table t_lightruninfo is clean\n");
	}
	else
	{
		printf("table t_lightruninfo clean fail\n");
	}

	printf("data block %dB\n",sizeof(data_tmp[0]));
	printf("data cash %.3fMB\n",sizeof(data_tmp)*1.0/1000/1000);

	////////////////////////////////////////////////////////////////////////
	//初始化缓存下标
	head=0;
	end=0;
}

void main(void)
{
	SOCKADDR_IN InternetAddr;
	SOCKET Listen;
	SOCKET Accept;
	HANDLE CompletionPort;
	SYSTEM_INFO SystemInfo;
	LPPER_HANDLE_DATA PerHandleData;
	LPPER_IO_OPERATION_DATA PerIoData;
	int i;
	DWORD RecvBytes;
	DWORD Flags;
	DWORD ThreadID;
	WSADATA wsaData;
	DWORD Ret;

	init();

	HANDLE hThrd;
    DWORD threadId;
	hThrd=CreateThread(NULL,0,savedata,NULL,0,(LPDWORD)&threadId);

	if ((Ret = WSAStartup(0x0202, &wsaData)) != 0)
	{
		printf("2WSAStartup failed with error %d\n", Ret);
		getchar();
		return;
	}
	printf("WSAStartup\n");
	// Setup an I/O completion port.

	if ((CompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0)) == NULL)
	{
		printf( "CreateIoCompletionPort failed with error: %d\n", GetLastError());
		return;
	}
	printf("CreateIoCompletionPort\n");

	// Determine how many processors are on the system.

	GetSystemInfo(&SystemInfo);

	// Create worker threads based on the number of processors available on the
	// system. Create two worker threads for each processor.

	for(i = 0; i < SystemInfo.dwNumberOfProcessors * 2; i++)
	{
		HANDLE ThreadHandle;

		// Create a server worker thread and pass the completion port to the thread.

		if ((ThreadHandle = CreateThread(NULL, 0, ServerWorkerThread, CompletionPort,
			0, &ThreadID)) == NULL)
		{
			printf("CreateThread() failed with error %d\n", GetLastError());
			return;
		}
		printf("%d:",i);

		// Close the thread handle
		CloseHandle(ThreadHandle);
	}
	printf("\n");

	// Create a listening socket

	if ((Listen = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0,
		WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		printf("3WSASocket() failed with error %d\n", WSAGetLastError());
		getchar();
		return;
	}
	printf("WSASocket()\n"); 

	InternetAddr.sin_family = AF_INET;
	InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	InternetAddr.sin_port = htons(PORT);

	if (bind(Listen, (PSOCKADDR) &InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR)
	{
		printf("bind() failed with error %d\n", WSAGetLastError());
		return;
	}
	printf("bind()\n");

	// Prepare socket for listening

	if (listen(Listen, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("listen() failed with error %d\n", WSAGetLastError());
		return;
	}
	printf("listen()\n");

	// Accept connections and assign to the completion port.
	sockaddr_in client;
	int len=sizeof(client);

	while(TRUE)
	{
		ZeroMemory(&client,sizeof(sockaddr_in));
		if ((Accept = WSAAccept(Listen, PSOCKADDR(&client), &len, NULL, 0)) == SOCKET_ERROR)
		{
			printf("4WSAAccept() failed with error %d\n", WSAGetLastError());
			getchar();
			return;
		}

		// Create a socket information structure to associate with the socket
		if ((PerHandleData = (LPPER_HANDLE_DATA) GlobalAlloc(GPTR,	 
			sizeof(PER_HANDLE_DATA))) == NULL)
		{
			printf("GlobalAlloc() failed with error %d\n", GetLastError());
			getchar();
			return;
		}

		// Associate the accepted socket with the original completion port.
		
		PerHandleData->Socket = Accept;

		if (CreateIoCompletionPort((HANDLE) Accept, CompletionPort, (DWORD) PerHandleData,
			0) == NULL)
		{
			printf("CreateIoCompletionPort failed with error %d\n", GetLastError());
			getchar();
			return;
		}

		// Create per I/O socket information structure to associate with the	 
		// WSARecv call below.

		if ((PerIoData = (LPPER_IO_OPERATION_DATA) GlobalAlloc(GPTR,			 sizeof(PER_IO_OPERATION_DATA))) == NULL)
		{
			printf("GlobalAlloc() failed with error %d\n", GetLastError());
			getchar();
			return;
		}

		////////////////////////////////////////////////////////////////////////
		//缓存用完则等待数据清空
		int client_num=(end+DATA_TMP_SIZE-head)%DATA_TMP_SIZE;
		//printf("%d\n",client_num);
		if(client_num>=DATA_TMP_SIZE-1)
		{
			printf("writing ");
			//getchar();
			for(;client_num>=DATA_TMP_SIZE-10;)
			{
				printf(".");
				Sleep(500);
				client_num=(end+DATA_TMP_SIZE-head)%DATA_TMP_SIZE;
			}
			printf("\n");
		}
		////////////////////////////////////////////////////////////////////////

		//PerIoData->ip=data_tmp[end].ip;
		ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));
		strncpy(PerIoData->ip,inet_ntoa(client.sin_addr),20);
		PerIoData->port=ntohs(client.sin_port);
		PerIoData->BytesSEND = 0;
		PerIoData->BytesRECV = 0;
		PerIoData->DataBuf.len = DATA_BUFSIZE;
		PerIoData->DataBuf.buf = PerIoData->Buffer;
		PerIoData->index=end;//存储地址
		//PerIoData->DataBuf.buf = (char*)&data_tmp[PerIoData->index].data;
		

		Flags = 0;
		if(WSARecv(Accept, &(PerIoData->DataBuf), 1, &RecvBytes, &Flags,
			&(PerIoData->Overlapped), NULL) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != ERROR_IO_PENDING)
			{
				printf("5WSARecv() failed with error %d\n", WSAGetLastError());
				//getchar();
				//return;
				//goto _next;
			}
		}

		//地址下移
		end=(end+1)%DATA_TMP_SIZE;
//_next:;
	}
}

