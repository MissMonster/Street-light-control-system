/**************************************
 *FILE    :D:\c\light\receive\123.h
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/8/24 0:19:19
 *TEXT    :控制码
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

#define ALLCLOSE   0X00  //监控中心向远端灯控制器发送的 LED 路灯全关指令
#define ALLOPEN    0XFF  //监控中心向远端灯控制器发送的 LED 路灯全开指令
#define ODDOPEN    0X01  //监控中心向远端灯控制器发送的 LED 路灯单号灯开指令
#define ODDCLOSE   0X02  //监控中心向远端灯控制器发送的 LED 路灯单号灯关指令
#define EVENOPEN   0X03  //监控中心向远端灯控制器发送的 LED 路灯双号灯开指令
#define EVENCLOSE  0X04  //监控中心向远端灯控制器发送的 LED 路灯双号灯关指令
#define ALONEOPEN  0X05  //监控中心向远端灯控制器发送的 LED 路灯单灯开控制指令
#define ALONECLOSE 0X06  //监控中心向远端灯控制器发送的 LED 路灯单灯关控制指令
#define CONDITION  0X07  //远端灯控制器向监控中心上传 LED 路灯状态信息
#define LOCATION   0X08  //远端灯控制器向监控中心上传 LED 路灯位置信息