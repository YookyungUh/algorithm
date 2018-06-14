#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITY_RANGE 8

double gDistance[MAX_CITY_RANGE][MAX_CITY_RANGE];
bool gbChecked[MAX_CITY_RANGE];

double getMinDistance (int pos, int cityNum, double sum)
{
	int cnt = 0;
	double ret = -1;
	double temp = 0;

	for (cnt = 0 ; cnt < cityNum ; cnt++)
	{
		if (gbChecked[cnt] == true)
			continue;

		gbChecked[cnt] = true;
		temp = getMinDistance (cnt, cityNum, sum + gDistance[pos][cnt]);
		gbChecked[cnt] = false;
		
		if (ret == -1 || ret > temp)
			ret = temp;
	}

	return ret == -1 ? sum : ret;
}

int main()
{
	int tc = 0;
	int cityNum = 0;

	scanf ("%d", &tc);

	while (tc-- > 0)
	{
		int cntCol = 0;
		int cntRow = 0;
		double result = -1;
		double temp = 0;

		scanf ("%d", &cityNum);

		for (cntRow = 0 ; cntRow < cityNum ; cntRow++)
			for (cntCol = 0 ; cntCol < cityNum ; cntCol++)
				scanf ("%lf", &gDistance[cntRow][cntCol]);

		for (cntCol = 0 ; cntCol < cityNum ; cntCol++)
		{
			gbChecked[cntCol] = true;
			temp = getMinDistance (cntCol, cityNum, 0);
			if (result == -1 || result > temp)
				result = temp;
			gbChecked[cntCol] = false;
		}

		printf("%.10lf\n", result);

		memset(gDistance, 0, sizeof(double) * MAX_CITY_RANGE);
		memset(gbChecked, 0, sizeof(bool) * MAX_CITY_RANGE);
	}

	return 0;
}

