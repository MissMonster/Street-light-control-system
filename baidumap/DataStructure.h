/**************************************
 *FILE    :DataStructure.h
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :4/22/2015
 *TEXT    :DataStructure for Street light control system
 *EMAIL   :gtsoft_wk@foxmail.com
***************************************/
#include <string>
#include <iostream>
#include <vector>

using namespace std;

typedef struct lightdata
{
	int id;					//编号
	double voltage;			//电压
	double current;			//电流
	double Longitude;		//纬度
	double Latitude;		//经度
	char status;			//状态
	
}LIGHTDATA;

typedef struct controldata
{
	int id;					//标识码
	char lightmessage[30];	//信息
	double Longitude;		//纬度
	double Latitude;		//经度
	int lightsum;			//路灯数量
	char theway;			//运行方式
	vector<LIGHTDATA> lightline;//路灯队列

}CONTROLDATA;