#include <stdio.h>
#include <string.h>

#define MAX_FRIEND_RANGE 10

int map[MAX_FRIEND_RANGE][MAX_FRIEND_RANGE];
int select[MAX_FRIEND_RANGE];
int N;
int M;
int R;

void init_map()
{
	int i;
	int x, y;
	
	for(i = 0 ; i < N ; i++)
		memset(map + i, 0, sizeof(int) * MAX_FRIEND_RANGE);
	memset(select, 0, sizeof(int) * MAX_FRIEND_RANGE);
	
	R = 0;
	
	for(i = 1 ; i <= M ; i++)
	{
		scanf("%d %d", &x, &y);
		map[x][y] = 1;
		map[y][x] = 1;
	}
}

void solve(int pos, int c)
{
	int i;

	if (c == N)
	{
		R++;
		return;
	}
	
	select[pos] = 1;
	
	for(i = 0 ; i < N ; i++)
	{
		int t = pos + 1;
		
		if (map[pos][i] == 0)
			continue;
		
		if (select[i] == 1)
			continue;
		
		select[i] = 1;
		
		while (t <= MAX_FRIEND_RANGE)
		{
			if (select[t] == 0)
				break;
			t++;
		}
		
		solve(t, c + 2);
		
		select[i] = 0;
	}
	
	select[pos] = 0;
}

int main()
{
	int tc;
	scanf("%d", &tc);
	
	while(tc-- > 0)
	{
		scanf("%d %d", &N, &M);
		
		init_map();
		
		if (M != 0)
			solve(0, 0);
		
		printf("%d\n", R);
	}
	
	return 0;
}