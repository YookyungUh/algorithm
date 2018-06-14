#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
	char info[20];
} BOARD_INFO_T;

BOARD_INFO_T *gBoardInfo = NULL;

bool checkValidArea (int h, int w, int gH, int gW, int pos)
{
	// 1	2	3	4
	// #.	.#	..	..
	// ..	..	#.	.#
	switch (pos)
	{
		case 1 :
			if (w == 0 || h == (gH - 1))
				return false;
			if (gBoardInfo[h + 1].info[w] == '#' || gBoardInfo[h + 1].info[w - 1] == '#')
				return false;
			return true; 
			break;
		case 2 :
			if (w == (gW - 1) || h == (gH - 1))
				return false;
			if (gBoardInfo[h + 1].info[w] == '#' || gBoardInfo[h + 1].info[w + 1] == '#')
				return false;
			return true;
			break;
		case 3 :
			if (w == (gW - 1) || h == (gH - 1))
				return false;
			if (gBoardInfo[h].info[w + 1] == '#' || gBoardInfo[h + 1].info[w + 1] == '#')
				return false;
			return true;
			break;
		case 4 :
			if (w == (gW - 1) || h == (gH - 1))
				return false;
			if (gBoardInfo[h].info[w + 1] == '#' || gBoardInfo[h + 1].info[w] == '#')
				return false;
			return true;
			break;
	}

	return false;
}

void markArea (int h, int w, int pos, char mark)
{
	// 1	2	3	4
	// #.	.#	..	..
	// ..	..	#.	.#
	// bMark == true ==> set '#'
	// bMark == false ==> set '.'
	switch (pos)
	{
		case 1 :
			gBoardInfo[h].info[w] = mark;
			gBoardInfo[h + 1].info[w] = mark;
			gBoardInfo[h + 1].info[w - 1] = mark;
			break;
		case 2 :
			gBoardInfo[h].info[w] = mark;
			gBoardInfo[h + 1].info[w] = mark;
			gBoardInfo[h + 1].info[w + 1] = mark;
			break;
		case 3 :
			gBoardInfo[h].info[w] = mark;
			gBoardInfo[h].info[w + 1] = mark;
			gBoardInfo[h + 1].info[w + 1] = mark;
			break;
		case 4 :
			gBoardInfo[h].info[w] = mark;
			gBoardInfo[h].info[w + 1] = mark;
			gBoardInfo[h + 1].info[w] = mark;
			break;
	}
}

int boardCover (int gH, int gW, int whiteBox)
{
	int _gH = 0;
	int _gW = 0;
	int ret = 0;

	if (whiteBox == 0)
		return 1;

	for (_gH = 0 ; _gH < gH ; _gH++)
	{
		for (_gW = 0 ; _gW < gW ; _gW++)
		{
			if (gBoardInfo[_gH].info[_gW] == '.')
			{
				int cnt = 0;
				for (cnt = 0 ; cnt <= 4 ; cnt++)
				{
					if (checkValidArea(_gH, _gW, gH, gW, cnt) == true)
					{
						markArea(_gH, _gW, cnt, '#');
						ret += boardCover (gH, gW, whiteBox - 3);
						markArea(_gH, _gW, cnt, '.');
					}
				}

				return ret;
			}

		}
	}

	return ret;
}

int main()
{
	int tc = 0;
	int _gW = 0;
	int _gH = 0;

	scanf ("%d", &tc);

	while (tc-- > 0)
	{
		int cntX, cntY= 0;
		int whiteBox = 0;
		int result = 0;
		char c;

		scanf("%d %d", &_gH, &_gW);

		gBoardInfo = (BOARD_INFO_T*)malloc(sizeof(BOARD_INFO_T) * _gH);
		if (gBoardInfo == NULL)
		{
			printf("[FAIL] allocate memory\n");
			break;
		}

		for (cntY = 0 ; cntY < _gH ; cntY++)
		{
			for (cntX = 0 ; cntX < _gW ; cntX++)
			{
				scanf (" %c", &gBoardInfo[cntY].info[cntX]);
				if (gBoardInfo[cntY].info[cntX] == '.')
					whiteBox++;
			}
		}

		if (whiteBox % 3 == 0)
			result = boardCover (_gH, _gW, whiteBox);

		printf("%d\n", result);

		free(gBoardInfo);
		gBoardInfo = NULL;
	}

	return 0;
}
