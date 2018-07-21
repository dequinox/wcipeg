/*   
 *
 * 2007 Canadian Computing Competition, Stage 2
 * Day 2, Problem 3: Road Construction   
 *
*/

#include <stdio.h>
#include <vector>
#include <stack>
#include <iostream>

const int MAXN = 1001;


std::vector <int> g[MAXN];
std::stack <int> S;

int ancestor[MAXN];
bool visited[MAXN];
int lowlink[MAXN];
int links[MAXN];
int id[MAXN];
int component[MAXN];

int counter;
int components;

void dfs(int v, int parent)
{
	lowlink[v] = id[v] = counter++;
	visited[v] = true;
	S.push(v);

	for (int to : g[v])
	{
		if (to == parent)
			continue;
		if (visited[to])
			lowlink[v] = std::min(lowlink[v], id[to]);
		else 
		{
			dfs(to, v);
			lowlink[v] = std::min(lowlink[v], lowlink[to]);
		}
	}

	if (lowlink[v] == id[v])
	{
		components++;
		int to;
		while (true)
		{
			to = S.top(); S.pop();
			component[to] = components;
			if (to == v)
				break;	
		}
	}
}

void recreate(int nodes)
{
	for (int i = 1; i <= nodes; i++)
	{
		for (int to : g[i])
		{
			if (component[i] != component[to])
			{
				links[component[i]]++;
			}
		}
	}
}

int main() {
	int n, r;
	int leaves = 0;
	int v, w;
	scanf("%d%d", &n, &r);

	for (int i = 0; i < r; i++)
	{
		scanf("%d%d", &v, &w);
		g[v].push_back(w);
		g[w].push_back(v);
	}


	counter = 0;
	components = 0;
	dfs(1, -1);

	recreate(n);

	for (int c = 1; c <= components; c++)
	{
		if (links[c] == 1)
			leaves++;
	}

	printf("%d\n", (leaves + 1) / 2);

	return 0;
}
