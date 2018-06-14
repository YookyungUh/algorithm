#include <stdio.h>

int  test[2][] =
{
	{1,2},
	{3,4}
};

int main()
{
	int cnt = 0 ;

	for (cnt = 0 ; cnt < 2 ; cnt++)
		printf("%d ", test[cnt][0]);
	printf("\n");

	return 0;
}
