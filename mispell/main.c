#include <stdio.h>
#include <string.h>

int main()
{
	int tc = 0;
	int cnt = 1;
	int misNum = 0;
	char str[81];

	scanf ("%d", &tc);

	while (tc-- > 0)
	{
		memset(str, 0, sizeof(str));
		
		scanf ("%d %s", &misNum, str);

		str[misNum - 1] = '\0';

		printf("%d %s%s\n", cnt++, str, str + misNum);
	}

	return 0;
}
