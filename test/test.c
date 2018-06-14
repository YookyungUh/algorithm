#include <stdio.h>
#include <string.h>

int array[] = {1,2,3,4,5,6};

int main()
{
	printf("array : %x\n", array);
	printf("array+1 : %x\n", array+1);
	printf("&array : %x\n", &array);
	printf("&array+1 : %x\n", &array+1);
	
	return 0;
}
