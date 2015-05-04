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
	int id;					//���
	float voltage;			//��ѹ
	float current;			//����
	float temperature;		//�¶�
	double Longitude;		//γ��
	double Latitude;		//����
	char status;			//״̬
	unsigned char bright;	//����
	
}LIGHTDATA;

typedef struct controldata
{
	int id;						//��ʶ��
	char lightmessage[30];		//��Ϣ
	double Longitude;			//γ��
	double Latitude;			//����
	int lightsum;				//·������
	char theway;				//���з�ʽ
	vector<LIGHTDATA> lightline;//·�ƶ���

}CONTROLDATA;

