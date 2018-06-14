#include <stdio.h>
#include <string.h>
#include <time.h>

#define DEFAULT_ALLERGY_VALUE 0
//#define PRINT_TIME

#define MAX_FRIEND_NUM 50
#define MAX_MENU_NUM 50

typedef enum
{
	FOUND,
	NOT_FOUND
} RET_SEARCH_T;

typedef struct
{
	char name[MAX_FRIEND_NUM][11];
	long long allergyInfo[MAX_MENU_NUM];
	int friendNum;
	int menuNum;
	long long maxAllergyInfo;
} MAIN_DATA_STRUCT_T;

static MAIN_DATA_STRUCT_T gDataInfo;

int getNamePos (char *name)
{
	int cnt = 0;
	for (cnt = 0 ; cnt < gDataInfo.friendNum ; cnt++)
	{
		if (!strcmp(gDataInfo.name[cnt], name))
			return cnt;
	}
	return 0;
}

void setFriendInfo (int size)
{
	int cnt = 0;
	for (cnt = 0 ; cnt < size ; cnt++)
		scanf("%s\n", gDataInfo.name[cnt]);
}

void setAllergyInfo (int menuSize)
{
	char name[11];
	int cnt = 0;
	int size = 0;
	
	for (cnt = 0 ; cnt < menuSize ; cnt++)
	{
		scanf("%d", &size);
		gDataInfo.allergyInfo[cnt] = DEFAULT_ALLERGY_VALUE;

		while(size-- > 0)
		{
			scanf("%s", name);
			gDataInfo.allergyInfo[cnt] |= 0x1 << getNamePos(name);
		}
	}
}

RET_SEARCH_T searchMinMenu (int pos, int n, int r, long long allergyInfo)
{
	if (n == r || r == 0)
	{
		int cnt = 0;
		for (cnt = 0 ; cnt < r ; cnt++)
			allergyInfo |= gDataInfo.allergyInfo[pos + cnt];		
		return allergyInfo == gDataInfo.maxAllergyInfo ? FOUND : NOT_FOUND;
	}

	if (FOUND == searchMinMenu (pos + 1, n - 1, r - 1, allergyInfo | gDataInfo.allergyInfo[pos]))
		return FOUND;

	return searchMinMenu (pos + 1, n - 1, r, allergyInfo);
}

int main(void)
{
	int tc = 0;

#ifdef PRINT_TIME
{
	clock_t start, end, temp;
	start = clock();
	temp = clock();
#endif

	scanf("%d", &tc);

	while (tc-- > 0)
	{
		int cnt = 0;

		scanf("%d", &gDataInfo.friendNum);
		scanf("%d", &gDataInfo.menuNum);

		setFriendInfo(gDataInfo.friendNum);
		setAllergyInfo(gDataInfo.menuNum);

		gDataInfo.maxAllergyInfo = DEFAULT_ALLERGY_VALUE;
		for (cnt = 0 ; cnt < gDataInfo.friendNum ; cnt++)
		{
			gDataInfo.maxAllergyInfo <<= 1;
			gDataInfo.maxAllergyInfo |= 0x1;
		}

		for (cnt = 1 ; cnt <= gDataInfo.menuNum ; cnt++)
		{
			if (FOUND == searchMinMenu(0, gDataInfo.menuNum, cnt, 0))
				break;
		}

		printf("%d\n", cnt);
	}
	
#ifdef PRINT_TIME
	end = clock();
	printf("Program run time : %0.3f\n", (float)(end - start)/CLOCKS_PER_SEC);
}
#endif

	return 0;
}
