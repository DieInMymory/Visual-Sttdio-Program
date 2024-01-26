#include <stdio.h>
int main(void)
{
	int a, b;
	b = 3;
	while (1)
	{
		scanf("%d", &a);
		if (a == b)
		{
			printf("这两个数相等");
		}
		else
		{
			printf("这两个数不相等");
		}
	}
	
	return 0;

}