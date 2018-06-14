#include <stdio.h>

typedef enum {
	PAIR,
	NOT_PAIR
} PAIR_INFO_T;

char brackets[10001];
char bracketsStack[10000];
int stackSize;

PAIR_INFO_T checkPairCharacter (char c)
{
	PAIR_INFO_T ret = NOT_PAIR;

	if (stackSize == 0)
		return ret;

	switch (c)
	{
		case '}' :
			if (bracketsStack[stackSize-1] != '{')
				break;
			ret = PAIR;
			break;
		case ']' :
			if (bracketsStack[stackSize-1] != '[')
				break;
			ret = PAIR;
			break;
		case ')' :
			if (bracketsStack[stackSize-1] != '(')
				break;
			ret = PAIR;
			break;
	}

	if (PAIR == ret)
		stackSize--;

	return ret;
}

int main()
{
	int tc = 0;

	scanf ("%d", &tc);

	while (tc-- > 0)
	{
		char *pStr = NULL;
		PAIR_INFO_T ret = NOT_PAIR;

		scanf ("%s", brackets);

		stackSize = 0;
		pStr = brackets;


		while (*pStr != '\0')
		{
			if (*pStr == '{' || *pStr == '[' || *pStr == '(')
				bracketsStack[stackSize++] = *pStr;
			else if (*pStr == '}' || *pStr == ']' || *pStr == ')')
			{
				ret = checkPairCharacter(*pStr);
				if (NOT_PAIR == ret)
				   break;
			}
			else 
			{
				ret = NOT_PAIR;
				break;
			}

			pStr++;
		}

		if (PAIR == ret && stackSize == 0)
			printf("YES\n");
		else
			printf("NO\n");
	}

	return 0;
}
