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
	int id;					//��ʶ��
	char lightmessage[30];	//��Ϣ
	double Longitude;		//γ��
	double Latitude;		//����
	int lightsum;			//·������
	char theway;			//���з�ʽ
	
}CONTROLDATA;