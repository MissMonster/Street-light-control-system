/**************************************
 *FILE    :D:\c\light\receive\main.cpp
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/8/30 20:24:34
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

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"mysql/libmysql.lib")
#include <winsock2.h>  
#include <mswsock.h> 
#include <iostream>
#include <windows.h>
#include <time.h>
#include "DataStructure.h"

using namespace std;

int main()
{
	time_t rawtime;
	struct tm * timeinfo;
	for(;;)
	{
		//system("cls");
		time(&rawtime);
		timeinfo=localtime(&rawtime);
		int timer=timeinfo->tm_min%SAVEMIN;
		printf("[%4d-%02d-%02d %02d:%02d:%02d] ->start\n",
			1900+timeinfo->tm_year,
			1+timeinfo->tm_mon,
			timeinfo->tm_mday,
			timeinfo->tm_hour,
			timeinfo->tm_min,
			timeinfo->tm_sec,
			timer);

		system("server.exe server");

		time(&rawtime);
		timeinfo=localtime(&rawtime);
		printf("[%4d-%02d-%02d %02d:%02d:%02d] ->end\n",
			1900+timeinfo->tm_year,
			1+timeinfo->tm_mon,
			timeinfo->tm_mday,
			timeinfo->tm_hour,
			timeinfo->tm_min,
			timeinfo->tm_sec);
		Sleep((SAVEMIN/2-1)*60*1000);
		//break;
	}
	return 0;
}