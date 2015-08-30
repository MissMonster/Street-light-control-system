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
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "ControlCode.h"                     //控制码
#include "DataStructure.h"                   //数据结构
#include "mysql/mysql.h"

MYSQL mysql;                                 //mysql数据库指针

LAMP_DATA_TMP data_tmp[DATA_TMP_SIZE];       //缓存
int head;
int end;

//存储错误信息
void savelog(char str[])
{
	FILE* fpout;
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	fpout=fopen("log.txt","a");
	if(fpout==NULL)
	{
		printf("error! log.txt can not writing\n");
		return ;
	}
	fprintf(fpout,"[%4d-%02d-%02d %02d:%02d:%02d] ",
		1900+timeinfo->tm_year,
		1+timeinfo->tm_mon,
		timeinfo->tm_mday,
		timeinfo->tm_hour,
		timeinfo->tm_min,
		timeinfo->tm_sec);
	fprintf(fpout,"%s\n",str);
	fclose(fpout);
}

//工作线程
DWORD WINAPI ServerWorkerThread(LPVOID CompletionPortID)	
{	
	HANDLE CompletionPort = (HANDLE) CompletionPortID;	
	DWORD BytesTransferred;	
	LPOVERLAPPED Overlapped;	
	LPPER_HANDLE_DATA PerHandleData;	
	LPPER_IO_OPERATION_DATA PerIoData;	
	DWORD SendBytes, RecvBytes;	
	DWORD Flags;	

	while(TRUE)
	{  
		if (GetQueuedCompletionStatus(CompletionPort, &BytesTransferred,	
			(LPDWORD)&PerHandleData, (LPOVERLAPPED *) &PerIoData, INFINITE) == 0)	
		{	
			printf("GetQueuedCompletionStatus failed with error %d\n", GetLastError());
			if(GetLastError()==ERROR_INVALID_HANDLE)
			{
				break;		
			}
		}
		//printf("\n:%d:%d:\n",PerIoData->BytesRECV,PerIoData->BytesSEND);
		if (PerIoData->BytesRECV == 0)	
		{	
			PerIoData->BytesRECV = BytesTransferred;	
			PerIoData->BytesSEND = 0;	
		}	
		else	
		{	
			PerIoData->BytesSEND += BytesTransferred;	
		}	
		//if (BytesTransferred > 0)	
		if (PerIoData->BytesRECV > PerIoData->BytesSEND)
		////////////////////////////////////////////////////////////////////////
		//if(BytesTransferred>0)
		{
			ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));	
	
			PerIoData->DataBuf.buf = PerIoData->Buffer + PerIoData->BytesSEND;	
			PerIoData->DataBuf.len = PerIoData->BytesRECV - PerIoData->BytesSEND;	
	
			//printf("[%s:%u:%d]recv",PerIoData->ip,PerIoData->port,PerIoData->index);
			memcpy(&data_tmp[PerIoData->index].ip,PerIoData->ip,20);
			memcpy(&data_tmp[PerIoData->index].data,PerIoData->DataBuf.buf,DATA_BUFSIZE);

			memcpy(PerIoData->DataBuf.buf,"ok",3);
			//strcpy(PerIoData->Buffer,"ok");
			ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));		
			if (WSASend(PerHandleData->Socket, &(PerIoData->DataBuf), 1, &SendBytes, 0,&(PerIoData->Overlapped), NULL) == SOCKET_ERROR)	
			{	
				if (WSAGetLastError() != ERROR_IO_PENDING)	
				{	
					printf("WSASend() failed with error %d\n", WSAGetLastError());	
				//return 0;	
				}	
			}	
			else
			{
				//cout<<":"<<PerIoData->DataBuf.buf<<":";
			}
			ZeroMemory(PerIoData->DataBuf.buf,PerIoData->DataBuf.len);
	
			//printf("[%s:%u]end\n",PerIoData->ip,PerIoData->port);	 
			printf("[%s:%u:%d]end\r",PerIoData->ip,PerIoData->port,PerIoData->index);
			if (closesocket(PerHandleData->Socket) == SOCKET_ERROR)	
			{	
				printf("closesocket() failed with error %d\n", WSAGetLastError());	
				return 0;	
			}
			GlobalFree(PerHandleData);	
			GlobalFree(PerIoData);	
		}	
		////////////////////////////////////////////////////////////////////////	
	}
	return NULL;
}

void saveerror(int UID,DATA_STATUS light)
{
	string str_into="\
INSERT into t_errorinfo (time,controllerId,\
streetlightId,lightVoltage,ightCurrent,lightTemp) values";
	char str[500];
	sprintf(str,"(NOW(),%d,%d,%f,%f,%f)",
			UID,
			light.ID,
			light.voltage,
			light.current,
			light.temp);
	str_into+=str;

	if(mysql_query(&mysql,str_into.c_str())==NULL)
	{
		//printf("into success\n");
	}
	else
	{
		printf("error save fail\n");
	}
}

void controlleractive(int UID)
{
	string str_into="UPDATA into t_lightlocation (controllerId,flage) values";
	char str[100];
	sprintf(str,"(%d,'1')",UID);
	str_into+=str;

	if(mysql_query(&mysql,str_into.c_str())==NULL)
	{
		//printf("into success\n");
	}
	else
	{
		printf("controller save fail\n");
	}
}

//存储数据
DWORD WINAPI savedata(LPVOID channel)
{
	time_t rawtime;
    struct tm * timeinfo;
    
	int client_num;
	int sum=0;
	int error=0;
	int flage=1;
	
	//printf("writing data\n");
	for(;;)
	{
		client_num=(end+DATA_TMP_SIZE-head)%DATA_TMP_SIZE;
		if(client_num>0)
		{
			Sleep(1000);
			//printf("start save\n");
			for(;client_num>0;client_num--)
			{
				LAMP_DATA_TMP* p=data_tmp+head;
				int len=p->data.NUM;
				if(len>0)
				{
					string str_into;
					if(p->data.CMD==CONDITION)
					{
						////////////////////////////////////////////////////////////////////////
						//保存路灯状态
						str_into="\
replace into t_lightruninfo (time,id,controllerId,\
streetlightId,streetlightVoltage,streetlightCurrent,\
streetlightTemp,streetlightBrightness,streetlightWarning,flage) values";
						char str[500];
						sprintf(str,"(NOW(),1,%d,%d,%f,%f,%f,%d,'this is a test','1')",
							p->data.UID,
							p->data.DATA[0].ID,
							p->data.DATA[0].voltage,
							p->data.DATA[0].current,
							p->data.DATA[0].temp,
							p->data.DATA[0].brightness);
						str_into+=str;

						if(p->data.DATA[0].voltage==0||
							p->data.DATA[0].current==0||
							p->data.DATA[0].temp==0)
						{
							saveerror(p->data.UID,p->data.DATA[0]);
						}

						//if(len!=20)printf("NUM=%d len=%d\n",head,len);
						for(int i=1;i<len;i++)
						{
							char str[500];
							sprintf(str,",(NOW(),1,%d,%d,%f,%f,%f,%d,'this is a test','1')",
								p->data.UID,
								p->data.DATA[i].ID,
								p->data.DATA[i].voltage,
								p->data.DATA[i].current,
								p->data.DATA[i].temp,
								p->data.DATA[i].brightness);
							str_into+=str;

							if(p->data.DATA[0].voltage==0||
								p->data.DATA[0].current==0||
								p->data.DATA[0].temp==0)
							{
								saveerror(p->data.UID,p->data.DATA[0]);
							}
						}
						////////////////////////////////////////////////////////////////////////
					}
					else if(p->data.CMD==LOCATION)
					{
						////////////////////////////////////////////////////////////////////////
						//保存路灯位置
						str_into="\
replace into t_lightlocation (id,controllerId,\
streetlightId,Longitude,Latitude) values";
						char str[500];
						sprintf(str,"(1,%d,%d,%f,%f)",
							p->data.UID,
							p->data.DATA[0].ID,
							p->data.DATA[0].voltage,
							p->data.DATA[0].current);
						str_into+=str;
						
						//if(len!=20)printf("NUM=%d len=%d\n",head,len);
						for(int i=1;i<len;i++)
						{
							char str[500];
							sprintf(str,",(1,%d,%d,%f,%f)",
								p->data.UID,
								p->data.DATA[i].ID,
								p->data.DATA[i].voltage,
								p->data.DATA[i].current);
							str_into+=str;
						}
						////////////////////////////////////////////////////////////////////////
					}
					else if(p->data.CMD==CONTROLLER)
					{
						////////////////////////////////////////////////////////////////////////
						//保存控制器位置
						str_into="\
replace into t_controllerinfo (IP,controllerId,\
controllerLongitude,controllerLatitude,flage) values";
						char str[500];
						sprintf(str,"('%s',%d,%f,%f,'1')",
							p->ip,
							p->data.UID,
							p->data.DATA[0].voltage,
							p->data.DATA[0].current);
						str_into+=str;
						////////////////////////////////////////////////////////////////////////
					}
					else
					{
						char str[100];
						sprintf(str,"client [%s] CMD is %X",p->ip,p->data.CMD);
						savelog(str);
					}
					////////////////////////////////////////////////////////////////////////
					//卧槽，这bug隐藏够深的
					p->data.NUM=0;
					////////////////////////////////////////////////////////////////////////
					//printf("%s\n",str_into.c_str);
					//cout<<str_into<<endl;
					////////////////////////////////////////////////////////////////////////
					controlleractive(p->data.UID);
					////////////////////////////////////////////////////////////////////////
					
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
					char str[100];
					sprintf(str,"client [%s] WSARecv() failed with error 10054",p->ip);
					savelog(str);
				}
				head=(head+1)%DATA_TMP_SIZE;
				//Sleep(1000);
				sum++;
			}
			printf("save=%d error=%d\r",sum,error);
		}
		else
		{
			Sleep(1000);
			////////////////////////////////////////////////////////////////////////
			//定时保存
			time(&rawtime);
			timeinfo=localtime(&rawtime);
			int timer=timeinfo->tm_min%SAVEMIN;
			//printf("%d\n",timer);
			if(flage&&timer==5)
			{
				//printf("%d\n",timer);
				//savetabledata();
				if(mysql_query(&mysql,"INSERT INTO t_lightrunhistory SELECT * FROM t_lightruninfo")==NULL)
				{
					//savelog("save history success");
					//printf("save history success\n");
				}
				else
				{
					savelog("save history fail");
					printf("save history fail\n");
				}
				////////////////////////////////////////////////////////////////////////
				//清空故障信息
				if(mysql_query(&mysql,"TRUNCATE TABLE t_errorinfo")==NULL)
				{
					//printf("into success\n");
					//printf("table t_errorinfo is clean\n");
				}
				else
				{
					printf("table t_errorinfo clean fail\n");
				}
				if(mysql_query(&mysql,"INSERT INTO t_errorinfohistory SELECT * FROM t_errorinfo")==NULL)
				{
					//savelog("save errorhistory success");
					//printf("save errorhistory success\n");
				}
				else
				{
					savelog("save errorhistory fail");
					printf("save errorhistory fail\n");
				}

				////////////////////////////////////////////////////////////////////////
				//清空缓存
				if(mysql_query(&mysql,"UPDATE t_lightruninfo SET flage='0'")==NULL)
				{
					//printf("into success\n");
					//printf("table t_lightruninfo is clean\n");
				}
				else
				{
					printf("table t_lightruninfo clean fail\n");
				}
				////////////////////////////////////////////////////////////////////////
				if(mysql_query(&mysql,"UPDATE t_controllerinfo SET flage='0'")==NULL)
				{
					//printf("into success\n");
					//printf("table t_controllerinfo is clean\n");
				}
				else
				{
					printf("table t_controllerinfo clean fail\n");
				}
				////////////////////////////////////////////////////////////////////////
				flage=0;
				printf("finish server\n");
				exit(0);
			}
			/*
			else
			{
				if(timer>SAVEMIN/4&&timer<SAVEMIN*3/4)
				{
					flage=1;
					exit(0);
				}
			}*/
			////////////////////////////////////////////////////////////////////////
		}
	}
}

void init()
{
	////////////////////////////////////////////////////////////////////////
	//初始化mysql
	mysql_init(&mysql);
	if (mysql_real_connect(&mysql, mysqlip , mysqlname, mysqlpassword, mysqldatatable, 3306, NULL, 0) == NULL)
	{
		printf("mysql can not connect!\n");
	}
	else
	{
		//printf("mysql connect!\n");
	}
/*
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
*/
	printf("data block %dB\n",sizeof(data_tmp[0]));
	printf("data cash %.3fMB\n",sizeof(data_tmp)*1.0/1000/1000);

	////////////////////////////////////////////////////////////////////////
	//初始化缓存下标
	head=0;
	end=0;
}

int main(int argc,char* argv[])
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

	if(argc!=2)return 0;
	if(strcmp(argv[1],"server"))return 0;

	init();

	HANDLE hThrd;
    DWORD threadId;
	hThrd=CreateThread(NULL,0,savedata,NULL,0,(LPDWORD)&threadId);

	if ((Ret = WSAStartup(0x0202, &wsaData)) != 0)
	{
		printf("2WSAStartup failed with error %d\n", Ret);
		//getchar();
		return 0;
	}
	//printf("WSAStartup\n");
	// Setup an I/O completion port.

	if ((CompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0)) == NULL)
	{
		printf( "CreateIoCompletionPort failed with error: %d\n", GetLastError());
		return 0;
	}
	//printf("CreateIoCompletionPort\n");

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
			return 0;
		}
		//printf("%d:",i);

		// Close the thread handle
		CloseHandle(ThreadHandle);
	}
	printf("Server have %d WorkerThread\n",i);

	// Create a listening socket

	if ((Listen = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0,
		WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		printf("3WSASocket() failed with error %d\n", WSAGetLastError());
		//getchar();
		return 0;
	}
	//printf("WSASocket()\n"); 

	InternetAddr.sin_family = AF_INET;
	InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	InternetAddr.sin_port = htons(PORT);

	if (bind(Listen, (PSOCKADDR) &InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR)
	{
		printf("bind() failed with error %d\n", WSAGetLastError());
		return 0;
	}
	//printf("bind()\n");

	// Prepare socket for listening

	if (listen(Listen, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("listen() failed with error %d\n", WSAGetLastError());
		return 0;
	}
	//printf("listen()\n");

	// Accept connections and assign to the completion port.
	sockaddr_in client;
	int len=sizeof(client);

	printf("start server\n");
	while(TRUE)
	{
		ZeroMemory(&client,sizeof(sockaddr_in));
		if ((Accept = WSAAccept(Listen, PSOCKADDR(&client), &len, NULL, 0)) == SOCKET_ERROR)
		{
			printf("4WSAAccept() failed with error %d\n", WSAGetLastError());
			//getchar();
			//return;
		}

		// Create a socket information structure to associate with the socket
		if ((PerHandleData = (LPPER_HANDLE_DATA) GlobalAlloc(GPTR,	 
			sizeof(PER_HANDLE_DATA))) == NULL)
		{
			printf("GlobalAlloc() failed with error %d\n", GetLastError());
			//getchar();
			//return;
		}

		// Associate the accepted socket with the original completion port.
		
		PerHandleData->Socket = Accept;

		if (CreateIoCompletionPort((HANDLE) Accept, CompletionPort, (DWORD) PerHandleData,
			0) == NULL)
		{
			printf("CreateIoCompletionPort failed with error %d\n", GetLastError());
			//getchar();
			//return;
		}

		// Create per I/O socket information structure to associate with the	 
		// WSARecv call below.

		if ((PerIoData = (LPPER_IO_OPERATION_DATA) GlobalAlloc(GPTR,			 sizeof(PER_IO_OPERATION_DATA))) == NULL)
		{
			printf("GlobalAlloc() failed with error %d\n", GetLastError());
			//getchar();
			//return;
		}

		////////////////////////////////////////////////////////////////////////
		//缓存用完则等待数据清空
		int client_num=(end+DATA_TMP_SIZE-head)%DATA_TMP_SIZE;
		//printf("%d\n",client_num);
		if(client_num>=DATA_TMP_SIZE-1)
		{
			savelog("缓存不足");
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
			}
		}

		//地址下移
		end=(end+1)%DATA_TMP_SIZE;
	}
	return 0;
}
