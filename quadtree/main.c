#include <stdio.h>
#include <string.h>

#define MAX_STR_LENGTH 1001

char gStr[MAX_STR_LENGTH];
int gPos;

void solve(char *str)
{
	int i;
	char c;
	char locStr[4][MAX_STR_LENGTH] = {{0,}, {0,}, {0,}, {0,}};
					
	c = gStr[gPos];
	str[strlen(str)] = c;
	gPos++;
								
	if (c != 'x')
		return;
								
	for (i = 0 ; i < 4 ; i++)
		solve(locStr[i]);
										
	strcat(str, locStr[2]);
	strcat(str, locStr[3]);
	strcat(str, locStr[0]);
	strcat(str, locStr[1]);
}

int main()
{
	int tc;
			
	scanf("%d", &tc);
				
	while(tc-- > 0)
	{
		char locStr[MAX_STR_LENGTH] = {0,};
		memset(gStr, 0, sizeof(gStr));
		gPos = 0;
															
		scanf("%s", gStr);
																	
		solve(locStr);
		printf("%s\n", locStr);
	}
					
	return 0;
}
