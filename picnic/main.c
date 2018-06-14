#include <stdio.h>

#define MAX_STUDENT_RANGE 10

int friend_map[MAX_STUDENT_RANGE][MAX_STUDENT_RANGE];
int friend_checked_info[MAX_SUDENT_RANGE];
int N;
int M;
int R;

void init_map()
{
	int i;
	int x, y;
	for(i = 0 ; i < M ; i++)
	{
		scanf("%d %d", &x, &y);
		friend_map[x][y] = 1;
		friend_map[y][x] = 1;
	}
}

void solve()
{

}

int main()
{
	int tc = 0;

	scanf ("%d", &tc);

	while (tc-- > 0)
	{
		scanf("%d %d", &N, &M);

		int_map();

		solve();
		
		printf("%d\n", R);
	}

	return 0;
}
