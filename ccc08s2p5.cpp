#include <stdio.h>
#include <map>
#include <iostream>

const int MAXN = 101;
const int MAXK = 501;
const int INF  = 1000000000;

int diff[MAXN][MAXK];
	int amount[MAXN];
	int calorie[MAXN];

int mindifference = INF;
int boundary = 0;
bool visited[MAXN][MAXK * 20000];

void run(int N, int difference)
{
	if (visited[N][std::abs(difference)]) return;
	visited[N][std::abs(difference)] = true;

	//if (difference > boundary || difference < -boundary) return;


	if (N == 0) 
	{
		mindifference = std::min(mindifference, std::abs(difference));
		return;
	}
	for (int i = 0; i <= amount[N]; i++)
	{
		run(N - 1, difference - (amount[N] - i) * calorie[N] + i * calorie[N]);
	}
}

int main()
{
	int N;

	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d%d", &amount[i], &calorie[i]);
		boundary += amount[i] * calorie[i];
	}
	boundary /= 1.5;

	run(N, 0);

	printf("%d\n", mindifference);
	return 0;
	
}
