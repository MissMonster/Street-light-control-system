/**************************************
 *FILE    :DataStructure.h
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :4/22/2015
 *TEXT    :DataStructure for Street light control system
 *EMAIL   :gtsoft_wk@foxmail.com
***************************************/
#include <string>

typedef struct data
{
	int id;					//标识码
	char lightmessage[30];	//信息
	double Longitude;		//纬度
	double Latitude;		//经度
	int lightsum;			//路灯数量
	char theway;			//运行方式
	
}CONTROLDATA;