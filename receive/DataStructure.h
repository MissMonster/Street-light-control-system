/**************************************
 *FILE    :D:\c\light\receive\DataStructure.h
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/8/16 11:10:11
 *TEXT    :NULL
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

#ifndef _DataStructure_h_
#define _DataStructure_h_

#include <string>
#include <iostream>
#include <vector>

using namespace std;

#define PORT            5555                 //�˿ں�
#define DATA_BUFSIZE    412                  //���ݳ���
#define DATA_TMP_SIZE   100                  //���泤��
#define SAVEMIN         2                    //����ʱ����

////////////////////////////////////////////////////////////////////////
#define mysqlip         "127.0.0.1"      
#define mysqlname       "light"    
#define mysqlpassword   "123456"        
#define mysqldatatable  "light"   
////////////////////////////////////////////////////////////////////////

struct DATA_STATUS 
{
    int ID ;
    //·�Ʊ��
    float current ;
    //����ֵ
    float voltage ;
    //��ѹֵ
    float temp ;
    //�¶�ֵ
    BYTE brightness ;
    //��ǰ����
};

/*struct TIME 
{
    BYTE year ;
    //��
    BYTE month ;
    //��
    BYTE day ;
    //��
    BYTE hour ;
    //ʱ
    BYTE minute ;
    //��
    BYTE second ;
    //��
};*/

struct LAMP_STATUS 
{
    int UID ;
    //Ψһ�豸ʶ����
    BYTE CMD ;
    //������
    int NUM ;
    //�ƾ�����
    //TIME time ;
    //��ǰʱ��
    DATA_STATUS DATA[20];
    //״̬����
};

struct LAMP_DATA_TMP
{
	char ip[20];
	LAMP_STATUS data;//412
};

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

typedef struct	 
{
	SOCKET Socket;
} PER_HANDLE_DATA, * LPPER_HANDLE_DATA;

#endif