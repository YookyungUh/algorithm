#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEFAULT_ALLERGY_VALUE 0
#define DEBUG
#define USE_FILE
#define PRINT_TIME

#define FAIL -1
#define OK 0

#ifndef bool
typedef enum
{
	false,
	true
} bool;
#endif

typedef struct
{
	char name[11];
} FRIEND_INFO_T;

typedef struct
{
	long long allergy_info;
	bool bChecked;
} MENU_INFO_T;

typedef struct
{
	FRIEND_INFO_T *pFriendInfo;
	MENU_INFO_T *pMenuInfo;
	int friendNum;
	int menuNum;
	int minFoodNum;
	long long maxAllergyInfo;
} MAIN_DATA_STRUCT_T;

static MAIN_DATA_STRUCT_T gDataInfo;

#ifdef PRINT_TIME
void delay(clock_t n)
{
	clock_t start = clock();
	while(clock() - start < n);
}
#endif

int getNamePos (char *name)
{
	int cnt = 0;

	if (NULL == gDataInfo.pFriendInfo || NULL == name)
	{
		printf("[%s] [FAIL] Invalid parameter\n", __func__);
		return FAIL;
	}

	for (cnt = 0 ; cnt < gDataInfo.friendNum ; cnt++)
	{
		if (!strcmp(gDataInfo.pFriendInfo[cnt].name, name))
			return cnt;
	}

	return FAIL;
}

int setFriendInfo (int friendSize)
{
	int cnt = 0;
	
	if (NULL == gDataInfo.pFriendInfo)
	{
		printf("[%s] [FAIL] Invalid parameter\n", __func__);
		return FAIL;
	}

	for (cnt = 0 ; cnt < friendSize ; cnt++)
		scanf("%s\n", gDataInfo.pFriendInfo[cnt].name);

	return OK;
}

int setAllergyInfo (int menuSize)
{
	char name[11];
	int cnt = 0;
	int size = 0;
	
	if (NULL == gDataInfo.pMenuInfo)
	{
		printf("[%s] [FAIL] Invalid parameter\n", __func__);
		return FAIL;
	}

	for (cnt = 0 ; cnt < menuSize ; cnt++)
	{
		scanf("%d", &size);

		gDataInfo.pMenuInfo[cnt].allergy_info = DEFAULT_ALLERGY_VALUE;

		while(size-- > 0)
		{
			int temp = -1;

			scanf("%s", name);

			temp = getNamePos(name);
			
			if(FAIL == temp)
				return FAIL;

			gDataInfo.pMenuInfo[cnt].allergy_info |= 0x1 << temp;
		}
	}

	return 0;
}

void searchMinMenu (int searchPos, int depth, long long allergyInfo)
{
	int cnt = 0;
	long long tempAllergyInfo = DEFAULT_ALLERGY_VALUE;

	for (cnt = searchPos ; cnt < gDataInfo.menuNum ; cnt++)
	{
		if (gDataInfo.pMenuInfo[cnt].bChecked == true)
			continue;

		tempAllergyInfo = allergyInfo | gDataInfo.pMenuInfo[cnt].allergy_info;

		if (tempAllergyInfo == gDataInfo.maxAllergyInfo)
		{
			if (-1 == gDataInfo.minFoodNum || gDataInfo.minFoodNum > depth)
				goto EXIT;
		}

	}

	for (cnt = searchPos ; cnt < gDataInfo.menuNum ; cnt++)
	{
		if (gDataInfo.pMenuInfo[cnt].bChecked == true)
			continue;

		if (-1 != gDataInfo.minFoodNum && depth+1 >= gDataInfo.minFoodNum)
			return;

		tempAllergyInfo = allergyInfo | gDataInfo.pMenuInfo[cnt].allergy_info;

		gDataInfo.pMenuInfo[cnt].bChecked = true;
		searchMinMenu (cnt + 1, depth + 1, tempAllergyInfo);
		gDataInfo.pMenuInfo[cnt].bChecked = false;
	}

	return;

EXIT:
	{
		long long temp = 0;
		for (cnt = 0 ; cnt < gDataInfo.menuNum ; cnt++)
		{
			if (gDataInfo.pMenuInfo[cnt].bChecked == true)
				temp |= 0x1 << cnt;
		}
		printf("depth : %d (0x%08llx)\n", depth, temp);
	}
	gDataInfo.minFoodNum = depth;
	return;
}

int main(void)
{
	int test_case = 0;
#ifdef USE_FILE
	FILE *fp = freopen ("tc2.txt", "r", stdin);
	
	if (NULL == fp)
	{
		printf("[FAIL] file open\n");
		return -1;
	}
#endif
	
#ifdef PRINT_TIME
{
	clock_t start, end;
	start = clock();
#endif

	scanf("%d", &test_case);

	while (test_case-- > 0)
	{
		int cnt = 0;

		scanf("%d", &gDataInfo.friendNum);
		scanf("%d", &gDataInfo.menuNum);

		gDataInfo.pFriendInfo = (FRIEND_INFO_T*)malloc(sizeof(FRIEND_INFO_T) * gDataInfo.friendNum);
		gDataInfo.pMenuInfo = (MENU_INFO_T*)malloc(sizeof(MENU_INFO_T) * gDataInfo.menuNum);

		if(NULL == gDataInfo.pFriendInfo)
		{
			printf("[FAIL] allocate memory - FriendInfo\n");
			break;
		}

		if(NULL == gDataInfo.pMenuInfo)
		{
			free(gDataInfo.pFriendInfo);
			printf("[FAIL] allocate memory - MenuInfo\n");
			break;
		}

		gDataInfo.minFoodNum = -1;
		gDataInfo.maxAllergyInfo = DEFAULT_ALLERGY_VALUE;

		if(FAIL == setFriendInfo(gDataInfo.friendNum))
			break;

		if(FAIL == setAllergyInfo(gDataInfo.menuNum))
			break;

		for (cnt = 0 ; cnt < gDataInfo.friendNum ; cnt++)
		{
			gDataInfo.maxAllergyInfo <<= 1;
			gDataInfo.maxAllergyInfo |= 0x1;
		}

#ifdef DEBUG
		{
			int cnt = 0;
			for(; cnt<gDataInfo.menuNum;cnt++)
			{
				printf("pMenuInfo[%d].allergy_info : %lld\n", cnt, gDataInfo.pMenuInfo[cnt].allergy_info);
			}

			printf("Max allergy value : %lld\n", gDataInfo.maxAllergyInfo);
		}
#endif
		searchMinMenu(0, 1, 0);
		printf("%d\n", gDataInfo.minFoodNum);

		free(gDataInfo.pFriendInfo);
		free(gDataInfo.pMenuInfo);

		gDataInfo.pFriendInfo = NULL;
		gDataInfo.pMenuInfo = NULL;
		gDataInfo.friendNum = 0;
		gDataInfo.menuNum = 0;
	}

#ifdef PRINT_TIME
	end = clock();
	printf("Program run time : %0.3f\n", (float)(end - start)/CLOCKS_PER_SEC);
}
#endif

#ifdef USE_FILE
	fclose(fp);
#endif

	return 0;
}
