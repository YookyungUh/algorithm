#include <stdio.h>
#include <string.h>

int gDateInfo[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char *gDayInfo[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", NULL};

int getDayOrder(char *dayStr)
{
	int cnt = 0;
	while(gDayInfo[cnt] != NULL)
	{
		if (!strcmp(gDayInfo[cnt], dayStr))
			return cnt;
		cnt++;
	}
	return -1;
}

int main()
{
	int tc = 0;
	int month = 0;
	int day = 0;
	int result[7];
	char dayStr[10];

	scanf ("%d", &tc);

	while (tc-- > 0)
	{
		int cnt = 0;
		int pos = 0;
		int tempDay = 0;

		scanf("%d %d %s", &month, &day, dayStr);

		pos = getDayOrder (dayStr);

		result[pos] = day;
		tempDay = day;
		month--;
		
		for (cnt = pos - 1 ; cnt >= 0 ; cnt--)
		{
			if (--tempDay == 0)
				tempDay = gDateInfo[(month+11)%12];
			result[cnt] = tempDay;
		}

		tempDay = day;

		for (cnt = pos + 1 ; cnt < 7 ; cnt++)
			result[cnt] = (tempDay++ % gDateInfo[month]) + 1;

		for (cnt = 0 ; cnt < 7 ; cnt++)
			printf("%d ", result[cnt]);
		printf("\n");
	}

	return 0;
}
