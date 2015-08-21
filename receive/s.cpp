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
#define DATA_TMP_SIZE   100
#define mysqlip         "127.0.0.1"      
#define mysqlname       "light"    
#define mysqlpassword   "123456"        
#define mysqldatatable  "light"   

typedef char sBit8;
MYSQL mysql;
MYSQL_RES *res1;             //这个结构代表返回行的一个查询结果集
MYSQL_ROW column1;           //一个行数据的类型安全(type-safe)的表示，表示数据行的列

FILE* fpout;

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
	// LPOVERLAPPED Overlapped;
	LPPER_HANDLE_DATA PerHandleData;
	LPPER_IO_OPERATION_DATA PerIoData;
	DWORD SendBytes;
	//DWORD RecvBytes;
	//DWORD Flags;
	//int tmp;

	while(TRUE)
	{
		//printf("2");
		if (GetQueuedCompletionStatus(CompletionPort, &BytesTransferred,
			(LPDWORD)&PerHandleData, (LPOVERLAPPED *) &PerIoData, INFINITE) == 0)
		{
			//			printf("GetQueuedCompletionStatus failed with error %d\n", GetLastError());
			//			return 0;
		}
	
		// First check to see if an error has occured on the socket and if so
		// then close the socket and cleanup the SOCKET_INFORMATION structure
		// associated with the socket.
	
		if (BytesTransferred == 0)
		{
			//printf("[%s:%u] is closed!!\n",PerIoData->ip,PerIoData->port);	 
			if (closesocket(PerHandleData->Socket) == SOCKET_ERROR)
			{
				printf("closesocket() failed with error %d\n", WSAGetLastError());
				return 0;
			}
		
			GlobalFree(PerHandleData);
			GlobalFree(PerIoData);
			continue;
		}
	
		// Check to see if the BytesRECV field equals zero. If this is so, then
		// this means a WSARecv call just completed so update the BytesRECV field
		// with the BytesTransferred value from the completed WSARecv() call.
	
		if (PerIoData->BytesRECV == 0)
		{
			PerIoData->BytesRECV = BytesTransferred;
			PerIoData->BytesSEND = 0;
		}
		else
		{
			PerIoData->BytesSEND += BytesTransferred;
		}
	
		if (PerIoData->BytesRECV > PerIoData->BytesSEND)
		{
			//recv and send
			// Post another WSASend() request.
			// Since WSASend() is not gauranteed to send all of the bytes requested,
			// continue posting WSASend() calls until all received bytes are sent.
		
			ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));
		
			PerIoData->DataBuf.buf = PerIoData->Buffer + PerIoData->BytesSEND;
			PerIoData->DataBuf.len = PerIoData->BytesRECV - PerIoData->BytesSEND;

			/*个判断问题...
			int client_num=(end+DATA_TMP_SIZE-head)%DATA_TMP_SIZE;
			for(;client_num>=DATA_TMP_SIZE-1;)
			{
				//for(;end==head;)
				{
					Sleep(10);
				}
				client_num=(end+DATA_TMP_SIZE-head)%DATA_TMP_SIZE;
			}*/
			//tmp=end;
			//end=(end+1)%DATA_TMP_SIZE;
			
			//卧槽居然不能直接用内存拷贝
			//2015年8月19日内存溢出
			//memcpy(data_tmp[tmp].Buffer,PerIoData->Buffer,DATA_BUFSIZE);
			//memcpy(data_tmp[tmp].BytesRECV,PerIoData->BytesRECV,DATA_BUFSIZE);
			//data_tmp[tmp].BytesRECV=PerIoData->BytesRECV;
			//memcpy(data_tmp[tmp].BytesSEND,PerIoData->BytesSEND,DATA_BUFSIZE);
			//data_tmp[tmp].BytesSEND=PerIoData->BytesSEND;
			//char str[412];
			memcpy(data_tmp[PerIoData->index].ip,PerIoData->ip,20);
			memcpy(&data_tmp[PerIoData->index].data,PerIoData->DataBuf.buf,412);
			//char* p=(char*)&data_tmp[tmp].data;
			//for(int i=0;i<412;i++)
			//{
			//	*p=str[i];
			//	p++;
			//}
			printf("index=%d head=%d end=%d :%s:\n",PerIoData->index,head,end,data_tmp[PerIoData->index].ip);
			//printf("%d ",tmp);
			//data_tmp[tmp].DataBuf=PerIoData->DataBuf;
			//memcpy(data_tmp[tmp].ip,PerIoData->ip,20);
			//strcpy(data_tmp[tmp].ip,PerIoData->ip);
			//printf("%d ",sizeof(PerIoData->ip));
			//memcpy(data_tmp[tmp].Overlapped,PerIoData->Overlapped,DATA_BUFSIZE);
			//data_tmp[tmp].Overlapped=PerIoData->Overlapped;
			//memcpy(data_tmp[tmp].port,PerIoData->port,DATA_BUFSIZE);
			//data_tmp[tmp].port=PerIoData->port;
			//printf("data cash %.3fMB\n",sizeof(data_tmp)*1.0/1000/1000);
			//data
			//printf("[%s:%u]->%s\n",PerIoData->ip,PerIoData->port,PerIoData->DataBuf.buf);
			strcpy(PerIoData->DataBuf.buf,"light");
		
			if (WSASend(PerHandleData->Socket, &(PerIoData->DataBuf), 1, &SendBytes, 0,
				&(PerIoData->Overlapped), NULL) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != ERROR_IO_PENDING)
				{
					printf("1WSASend() failed with error %d\n", WSAGetLastError());
					getchar();
					return 0;
				}
			}
			ZeroMemory(PerIoData->DataBuf.buf,PerIoData->DataBuf.len);		

			if (closesocket(PerHandleData->Socket) == SOCKET_ERROR)
			{
				printf("closesocket() failed with error %d\n", WSAGetLastError());
				return 0;
			}
			
			GlobalFree(PerHandleData);
			GlobalFree(PerIoData);

			if (PerIoData->BytesRECV == 0)
			{
				PerIoData->BytesRECV = BytesTransferred;
				PerIoData->BytesSEND = 0;
			}
			else
			{
				PerIoData->BytesSEND += BytesTransferred;
			}

			//continue;
		}
		/*else
		{
			PerIoData->BytesRECV = 0;
		
			// Now that there are no more bytes to send post another WSARecv() request.
		
			Flags = 0;
			ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));
		
			PerIoData->DataBuf.len = DATA_BUFSIZE;
			PerIoData->DataBuf.buf = PerIoData->Buffer;
		
			if (WSARecv(PerHandleData->Socket, &(PerIoData->DataBuf), 1, &RecvBytes, &Flags,
				&(PerIoData->Overlapped), NULL) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != ERROR_IO_PENDING)
				{
					printf("WSARecv() failed with error %d\n", WSAGetLastError());
					return 0;
				}
			}
		}*/
	}
	return 0;
}

//存储数据
DWORD WINAPI savedata(LPVOID channel)
{
	//string 
	int client_num;
	printf("writing data\n");
	int sum=0;
	for(;;)
	{
		client_num=(end+DATA_TMP_SIZE-head)%DATA_TMP_SIZE;
		if(client_num>0)
		{
			printf("start save\n");
			for(;client_num>0;client_num--)
			{
				LAMP_DATA_TMP* p=data_tmp+head;
				int len=p->data.NUM;
				string str_into="replace into t_lightruninfo (time,id,controllerId,\
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
			printf("save %d is end\n",sum);
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

	if (listen(Listen, 5) == SOCKET_ERROR)
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

		ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));
		strncpy(PerIoData->ip,inet_ntoa(client.sin_addr),20);
		PerIoData->port=ntohs(client.sin_port);
		PerIoData->BytesSEND = 0;
		PerIoData->BytesRECV = 0;
		PerIoData->DataBuf.len = DATA_BUFSIZE;
		PerIoData->DataBuf.buf = PerIoData->Buffer;
		PerIoData->index=end;//存储地址

		Flags = 0;
		if (WSARecv(Accept, &(PerIoData->DataBuf), 1, &RecvBytes, &Flags,
			&(PerIoData->Overlapped), NULL) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != ERROR_IO_PENDING)
			{
				printf("5WSARecv() failed with error %d\n", WSAGetLastError());
				getchar();
				return;
			}
		}

		//地址下移
		end=(end+1)%DATA_TMP_SIZE;
	}
}

