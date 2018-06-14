#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define CLOCK_TIME_SIZE 16
#define CLOCK_SYNC_SIZE 10

typedef struct
{
	int info[5];
	int size;
} TIME_ROTATE_INFO_T;

int clockTimeInfo[CLOCK_TIME_SIZE];
TIME_ROTATE_INFO_T clockSyncInfo[] =
{
	{{0, 1, 2}, 3},			// 0
	{{3, 7, 9, 11}, 4},		// 1
	{{4, 10, 14, 15}, 4},	// 2
	{{0, 4, 5, 6, 7}, 5},	// 3
	{{6, 7, 8, 10, 12}, 5},	// 4
	{{0, 2, 14, 15}, 4},	// 5
	{{3, 14, 15}, 3},		// 6
	{{4, 5, 7, 14, 15},	5},	// 7
	{{1, 2, 3, 4, 5}, 5}, 	// 8
	{{3, 4, 5, 9, 13}, 5},	// 9
};

void rotateTimeInfo (int idx)
{
	int cnt = 0;
	int size = clockSyncInfo[idx].size;
	for (cnt = 0 ; cnt < size ; cnt++)
	{
		if (clockTimeInfo[clockSyncInfo[idx].info[cnt]] == 12)
			clockTimeInfo[clockSyncInfo[idx].info[cnt]] = 3;
		else
			clockTimeInfo[clockSyncInfo[idx].info[cnt]] += 3;
	}
}

bool checkTimeSynchronizing (void)
{
	int cnt = 0;
	for (cnt = 0 ; cnt < CLOCK_TIME_SIZE ; cnt++)
	{
		if (clockTimeInfo[cnt] != 12)
			return false;
	}
	return true;
}

int getMinClickButton (int pos, int clickNum)
{
	int cnt = 0;
	int ret = -1;
	int temp = 0;

	if (pos == CLOCK_SYNC_SIZE)
		return -1;

	for (cnt = 1 ; cnt <= 4 ; cnt++)
	{
		rotateTimeInfo (pos);

		if (checkTimeSynchronizing())
			return clickNum + cnt % 4;

		if (ret != -1 && ret < clickNum + cnt % 4)
			continue;

		temp = getMinClickButton (pos + 1, clickNum + cnt % 4);

		if (ret == -1 || ret < temp)
			ret = temp;
	}

	return ret;
}

int main()
{
	int tc = 0;
	int cnt = 0;

	scanf ("%d", &tc);

	while (tc-- > 0)
	{
		memset (clockTimeInfo, 0, sizeof(int) * CLOCK_TIME_SIZE);
		for (cnt = 0 ; cnt < CLOCK_TIME_SIZE ; cnt++)
			scanf ("%d", &clockTimeInfo[cnt]);
		printf("%d\n", getMinClickButton (0, 0));
	}

	return 0;
}
