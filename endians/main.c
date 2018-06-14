#include <stdio.h>

int main()
{
	unsigned int data = 0;
	unsigned int reverseData = 0;
	int tc = 0;
	int maxCnt = sizeof(int);
	int cnt = 0;

	scanf ("%d", &tc);

	while (tc-- > 0)
	{
		data = 0;
		reverseData = 0;

		scanf("%u", &data);

		for (cnt = 0 ; cnt < maxCnt ; cnt++)
		{
			reverseData <<= 8;
			reverseData |= data & 0x000000ff;
			data >>= 8;
		}
		
		printf("%u\n", reverseData);
	}	

	return 0;
}
