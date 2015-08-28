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

#endif