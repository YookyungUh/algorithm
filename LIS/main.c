#include <stdio.h>
#include <string.h>

#define MAX_ARRAY_LENGTH 500
#define MAX(x,y) ((x) < (y) ? (y) : (x))

int main()
{
	int tc = 0;

	scanf ("%d", &tc);

	while (tc-- > 0)
	{
		int array[MAX_ARRAY_LENGTH];
		int lis[MAX_ARRAY_LENGTH];
		int length = 0;
		int i, j = 0;
		int ret = 0;

		scanf ("%d", &length);

		for (i = 0 ; i < length ; i++)
		{
			scanf ("%d", &array[i]);
			lis[i] = 1;
		}

		for (i = 0 ; i < length ; i++)
		{
			for (j = 0 ; j < i ; j++)
			{
				if (array[j] < array[i])
				{
					lis[i] = MAX(lis[i], lis[j] + 1);
				}
			}
		}

		for (i = 0 ; i < length ; i++)
		{
			if (ret < lis[i])
				ret = lis[i];
		}

		printf("%d\n", ret);
	}

	return 0;
}
