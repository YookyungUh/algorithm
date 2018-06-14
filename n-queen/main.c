#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARRAY_SIZE 12
#define ABS(x) ((x) < 0 ? (-1) * (x) : (x))

int queenPosition[MAX_ARRAY_SIZE];

int bValidQueenPos (int row, int col)
{
	int cnt = 0;

	for (cnt = 0 ; cnt < row ; cnt++)
	{
		if (ABS(row - cnt) == ABS(col - queenPosition[cnt]) || col == queenPosition[cnt])
			return -1;
	}

	return 0;
}

int searchQueenPos (int row, int size)
{
	int col = 0;
	int ret = 0;

	if (row == size)
		return 1;

	for (col = 0 ; col < size ; col++)
	{
		if (0 == bValidQueenPos (row, col))
		{
			queenPosition[row] = col;
			ret += searchQueenPos(row + 1, size);
			queenPosition[row] = 0;
		}
	}

	return ret;
}

int main()
{
	int tc = 0;
	int size = 0 ;

	scanf ("%d", &tc);

	while (tc-- > 0)
	{
		memset (queenPosition, 0, sizeof(int) * MAX_ARRAY_SIZE);

		scanf("%d", &size);

		printf("%d\n", searchQueenPos (0, size));
	}

	return 0;
}
