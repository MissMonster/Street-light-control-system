
#ifndef _DataStructure_h_
#define _DataStructure_h_

#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct serverset
{
	char ip[20];
	char name[100];
	char password[100];
	char database[100];
	int  port;
};

struct userdata
{
	char name[100];
	int jurisdiction;//х╗оч
};

#endif