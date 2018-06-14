#include <stdio.h>
#include <string.h>

#define MAX_COORDINATE_NUM 2
#define LOOP_COUNT 3

typedef struct 
{
	int pos;
	int count;
} COORDINATE_INFO_T;

static COORDINATE_INFO_T rectX[MAX_COORDINATE_NUM];
static COORDINATE_INFO_T rectY[MAX_COORDINATE_NUM];

static void setRectInfo (COORDINATE_INFO_T* pInfo, int pos)
{
	int cnt = 0;

	for (cnt = 0 ; cnt < MAX_COORDINATE_NUM ; cnt++, pInfo++)
	{
		if (pInfo->count == 0)
		{
			pInfo->pos = pos;
			pInfo->count++;
			break;
		}
		else if (pInfo->count == 1 && pInfo->pos == pos)
		{
			pInfo->count++;
			break;
		}
	}
}

int main()
{
	int tc = 0 ;
	int x = 0;
	int y = 0;
	int cnt = 0;

	scanf("%d", &tc);

	while(tc-- > 0)
	{
		memset(rectX, 0, sizeof(COORDINATE_INFO_T) * MAX_COORDINATE_NUM);
		memset(rectY, 0, sizeof(COORDINATE_INFO_T) * MAX_COORDINATE_NUM);

		for (cnt = 0 ; cnt < LOOP_COUNT ; cnt++)
		{
			scanf("%d", &x);
			scanf("%d", &y);

			setRectInfo(rectX, x);
			setRectInfo(rectY, y);
		}

		for (cnt = 0 ; cnt < MAX_COORDINATE_NUM ; cnt++)
		{
			if (rectX[cnt].count == 1)
				printf("%d ", rectX[cnt].pos);
		}

		for (cnt = 0 ; cnt < MAX_COORDINATE_NUM ; cnt++)
		{
			if (rectY[cnt].count == 1)
				printf("%d\n", rectY[cnt].pos);
		}
	}

	return 0;
}
