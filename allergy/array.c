#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEFAULT_ALLERGY_VALUE 0
//#define DEBUG
#define USE_FILE
#define PRINT_TIME

#define FAIL -1
#define OK 0

#define MAX_TEST_CASE 50
#define MAX_FRIEND_NUM 50
#define MAX_MENU_NUM 50

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
	FRIEND_INFO_T friendInfo[MAX_FRIEND_NUM];
	MENU_INFO_T menuInfo[MAX_MENU_NUM];
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

	if (NULL == name)
	{
		printf("[%s] [FAIL] Invalid parameter\n", __func__);
		return FAIL;
	}

	for (cnt = 0 ; cnt < gDataInfo.friendNum ; cnt++)
	{
		if (!strcmp(gDataInfo.friendInfo[cnt].name, name))
			return cnt;
	}

	return FAIL;
}

int setFriendInfo (int friendSize)
{
	int cnt = 0;

	for (cnt = 0 ; cnt < friendSize ; cnt++)
		scanf("%s\n", gDataInfo.friendInfo[cnt].name);

	return OK;
}

int setAllergyInfo (int menuSize)
{
	char name[11];
	int cnt = 0;
	int size = 0;
	
	for (cnt = 0 ; cnt < menuSize ; cnt++)
	{
		scanf("%d", &size);

		gDataInfo.menuInfo[cnt].allergy_info = DEFAULT_ALLERGY_VALUE;

		while(size-- > 0)
		{
			int temp = -1;

			scanf("%s", name);

			temp = getNamePos(name);
			
			if(FAIL == temp)
				return FAIL;

			gDataInfo.menuInfo[cnt].allergy_info |= 0x1 << temp;
		}
	}

	return OK;
}

void searchMinMenu (int searchPos, int depth, long long allergyInfo)
{
	int cnt = 0;
	long long tempAllergyInfo = DEFAULT_ALLERGY_VALUE;

	for (cnt = searchPos ; cnt < gDataInfo.menuNum ; cnt++)
	{
		if (gDataInfo.menuInfo[cnt].bChecked == true)
			continue;

		tempAllergyInfo = allergyInfo | gDataInfo.menuInfo[cnt].allergy_info;

		if (tempAllergyInfo == gDataInfo.maxAllergyInfo)
		{
			if (-1 == gDataInfo.minFoodNum || gDataInfo.minFoodNum > depth)
				goto EXIT;
		}
	}

	for (cnt = searchPos ; cnt < gDataInfo.menuNum ; cnt++)
	{
		if (gDataInfo.menuInfo[cnt].bChecked == true)
			continue;

		if (-1 != gDataInfo.minFoodNum && depth+1 >= gDataInfo.minFoodNum)
			return;

		tempAllergyInfo = allergyInfo | gDataInfo.menuInfo[cnt].allergy_info;

		gDataInfo.menuInfo[cnt].bChecked = true;
		searchMinMenu (cnt + 1, depth + 1, tempAllergyInfo);
		gDataInfo.menuInfo[cnt].bChecked = false;
	}

	return;

EXIT:
	gDataInfo.minFoodNum = depth;
	return;
}

int main(void)
{
	int test_case = 0;
#ifdef USE_FILE
	FILE *fp = freopen ("tc3.txt", "r", stdin);
	
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
				printf("pMenuInfo[%d].allergy_info : %lld\n", cnt, gDataInfo.menuInfo[cnt].allergy_info);

			printf("Max allergy value : %lld\n", gDataInfo.maxAllergyInfo);
		}
#endif
		searchMinMenu(0, 1, 0);
		printf("%d\n", gDataInfo.minFoodNum);
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
