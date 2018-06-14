#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {zero, one, two, three, four, five, six, seven, eight, nine, ten, invalid} NUMBER_T;

static struct NUMBER_STR_T
{
	char *pStr;
	int num;
} gNumStrArray[] =
{
	{"zero", zero},
	{"one", one},
	{"two", two},
	{"three", three},
	{"four", four},
	{"five", five},
	{"six", six},
	{"seven", seven},
	{"eight", eight},
	{"nine", nine},
	{"ten", ten},
	{NULL, invalid}
};

static int convertStr2Num (char *pStr)
{
	int cnt = 0;
	while (gNumStrArray[cnt].pStr != NULL)
	{ 
		if (!strcmp(gNumStrArray[cnt].pStr, pStr))
			break;
		
		cnt++;
	}
	return gNumStrArray[cnt].num;
}

static char* convertNum2Str (int num)
{
	int cnt = 0;
	while (gNumStrArray[cnt].num != invalid)
	{ 
		if (gNumStrArray[cnt].num == num)
			break;
		cnt++;
	}
	return gNumStrArray[cnt].pStr;
}

static int doCalculate (int x, int y, char operator)
{
	int ret;
	switch (operator)
	{
		case '+' : 	ret = x + y; 	break;
		case '-' : 	ret = x - y; 	break;
		case '*' : 	ret = x * y; 	break;
		defult : 	ret = invalid;	break;
	}
	return ret;
}

static int compFunc (const void *x, const void *y)
{
	return *(char*)x - *(char*)y;
}

static void checkSolution (char *pSolution, char *pAnswer)
{
	char solution[11];

	if (pSolution == NULL)
	{
		printf("No\n");
		return;
	}

	if (strlen(pSolution) != strlen(pAnswer))
	{
		printf("No\n");
		return;
	}

	strcpy (solution, pSolution);

	qsort ((void*)solution, strlen(solution), sizeof(char), compFunc);
	qsort ((void*)pAnswer, strlen(pAnswer), sizeof(char), compFunc);

	if(!strcmp(solution, pAnswer))
		printf("Yes\n");
	else
		printf("No\n");
}

int main()
{
	int tc = 0;
	char left[6];
	char right[6];
	char answer[11];
	char operator;
	char equal;

	scanf ("%d", &tc);

	while (tc-- > 0)
	{
		scanf("%s %c %s %c %s\n", left, &operator, right, &equal, answer);

		checkSolution (convertNum2Str (doCalculate (convertStr2Num (left), convertStr2Num(right), operator)), answer);
	}

	return 0;
}
