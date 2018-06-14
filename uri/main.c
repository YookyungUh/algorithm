#include <stdio.h>
#include <string.h>

int main()
{
	int tc = 0;
	int cnt = 0;
	int strLen = 0;
	char str[81];
	char subStr[4];

	scanf ("%d", &tc);

	while (tc-- > 0)
	{
		memset (subStr, 0, sizeof(subStr));
		scanf ("%s", str);

		strLen = strlen(str);

		for (cnt = 0 ; cnt < strLen ;)
		{
			if (str[cnt] != '%')
			{
				printf("%c", str[cnt]);
				cnt++;
				continue;
			}

			switch (str[cnt + 2])
			{
				case '0':
					printf (" ");
					break;
				case '1':
					printf ("!");
					break;
				case '4':
					printf ("$");
					break;
				case '5':
					printf ("%%");
					break;
				case '8':
					printf ("(");
					break;
				case '9':
					printf (")");
					break;
				case 'a':
					printf("*");
					break;
			}

			cnt += 3;
		}
		
		printf("\n");
	}

	return 0;
}
