/*
 *
 * 2003 Canadian Computing Competition, Stage 1
 * Problem S5: Trucking Troubles
 *
*/

#include <queue>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <iostream>

const int MAXC = 10001;
const int INF  = 1000000000;

int dest[MAXC];
int weight[MAXC];
std::vector< std::pair<int,int> > g[MAXC];


int main()
{
	int c, r, d;
	int x, y, w, v, to;
	scanf("%d%d%d", &c, &r, &d);

	for (int i = 1; i <= r; i++)
	{
		scanf("%d%d%d", &x, &y, &w);
		g[x].push_back(std::make_pair(y, w));
		g[y].push_back(std::make_pair(x, w));
	}

	for (int i = 1; i <= d; i++)
		scanf("%d", &dest[i]);


	memset(weight, 0, c * sizeof(int));
	
	weight[1] = 0;
	std::priority_queue< std::pair<int,int> > Q;
	Q.push(std::make_pair(0, 1));
	
	while (!Q.empty())
	{
		v = Q.top().second;
		w = Q.top().first;
		Q.pop();

		if (weight[v] > w) continue;

		for (std::pair<int,int> road : g[v])
		{
			int to = road.first;
			int w = road.second;
			if (weight[to] < w)
			{
				weight[to] = w;
				Q.push(std::make_pair(w, to));
			}
		}
	}

	int maxweight = INF;
	for (int i = 1; i <= d; i++)
		maxweight = std::min(maxweight, weight[dest[i]]);

	printf("%d\n", maxweight);
	return 0;
}
