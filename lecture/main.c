#include <stdio.h>

int main()
{
	int tc = 0;
	char str[1001];
	char *pStr = NULL;
	unsigned short *subStrNum;

	scanf ("%d", &tc);

	while (tc-- > 0)
	{
		scanf ("%s", str);
		pStr = str;

		while (*pStr != '\0')
		{
			subStrNum = (unsigned short*)pStr;
			printf("%d(%s)\n", *subStrNum,(char*) subStrNum);
			pStr += 2;
		}
		printf("===============\n");
	}

	return 0;
}
