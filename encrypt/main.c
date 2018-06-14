#include <stdio.h>
#include <string.h>

int main()
{
	int tc = 0;
	int cnt = 0;
	int strLen = 0;
	char str[101];

	scanf ("%d", &tc);

	while (tc-- > 0)
	{
		memset(str, 0, sizeof(str));

		scanf("%s", str);

		strLen = strlen(str);

		for (cnt = 0 ; cnt < strLen ; cnt += 2)
			printf("%c", str[cnt]);
		
		for (cnt = 1 ; cnt < strLen ; cnt +=2)
			printf("%c", str[cnt]);

		printf("\n");
	}

	return 0;
}
