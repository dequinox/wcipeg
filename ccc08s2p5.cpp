/*
 *
 * 2008 Canadian Computing Competition, Day 2
 * Day 2, Problem 2: Candy
 *
*/


#include <stdio.h>
#include <map>
#include <queue>
#include <string.h>
#include <iostream>

const int MAXN = 101;
const int MAXK = 501;
const int INF  = 1000000000;

int amount[MAXN];
int calorie[MAXN];
bool visited[MAXK * MAXN * 200];
int point[MAXK*MAXN*200];
int count[MAXK*MAXN*200];

int main()
{
	int N;
	int total = 0;

	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d%d", &amount[i], &calorie[i]);										                
		total += amount[i] * calorie[i];		
	}

	point[++point[0]] = 0;
	visited[0] = true;
	count[0] = 0;

	for (int i = 1; i <= N; i++)
	{
		memset(count, 0, total/2 * sizeof(int));

		for (int j = 1; j <= point[0]; j++)
		{
			if (point[j] + calorie[i] <= total / 2 && !visited[point[j] + calorie[i]] && count[point[j]] + 1 <= amount[i])
			{
				count[point[j] + calorie[i]] = count[point[j]] + 1;
				visited[point[j] + calorie[i]] = true;
				point[++point[0]] = point[j] + calorie[i];
			}
		}
	}

	for (int i = total / 2; i >= 0; i--)
	{
		if (visited[i])
		{
			printf("%d\n", total - i * 2);
			break;
		}
	}
	return 0;

}

