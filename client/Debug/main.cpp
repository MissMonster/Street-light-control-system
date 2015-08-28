#include <iostream>

using namespace std;

int main()
{
	int i=0;
	for(;i<1000;i++)
	{
		printf("%d\r",i);
		system("start c.exe");
	}
	return 0;
}