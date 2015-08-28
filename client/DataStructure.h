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
    //路灯编号
    float current ;
    //电流值
    float voltage ;
    //电压值
    float temp ;
    //温度值
    BYTE brightness ;
    //当前亮度
};

/*struct TIME 
{
    BYTE year ;
    //年
    BYTE month ;
    //月
    BYTE day ;
    //日
    BYTE hour ;
    //时
    BYTE minute ;
    //分
    BYTE second ;
    //秒
};*/

struct LAMP_STATUS 
{
    int UID ;
    //唯一设备识别码
    BYTE CMD ;
    //命令字
    int NUM ;
    //灯具数量
    //TIME time ;
    //当前时间
    DATA_STATUS DATA[20];
    //状态数据
};

struct LAMP_DATA_TMP
{
	char ip[20];
	LAMP_STATUS data;//412
};

#endif