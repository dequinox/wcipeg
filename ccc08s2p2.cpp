/*
 * 
 * 2008 Canadian Computing Competition, Day 1
 * Day 1, Problem 2: King & Weber
 *
*/

#include <map>
#include <stdio.h>
#include <iostream>

const int MAXN = 200000;

int dsu[MAXN];
int size[MAXN];
int mod2[MAXN];
bool waterloo[MAXN];

int city = 0;
std::map<std::string, int> dictionary;

void make_set(int v)
{
	dsu[v] = v;
	mod2[v] = 0;
	size[v] = 1;
}

std::pair<int, int> dsu_get(int v)
{
	if (v == dsu[v])
		return std::make_pair(dsu[v], mod2[v]);
	std::pair<int, bool> parent = dsu_get(dsu[v]);
	dsu[v] = parent.first;
	mod2[v] = parent.second ^ mod2[v];
	return std::make_pair(dsu[v], mod2[v]);
}

void dsu_union(int v, int w, bool intersect)
{
	std::pair<int, int> vp = dsu_get(v);
	std::pair<int, int> wp = dsu_get(w);

	if (vp.first != wp.first)
	{
		if (size[vp.first] < size[wp.first])
			std::swap(vp, wp);
		dsu[wp.first] = vp.first;
		mod2[wp.first] = wp.second ^ intersect ^ vp.second;
		size[vp.first] += size[wp.first];
	}

	else 
	{
		if (vp.second ^ wp.second != intersect)
			waterloo[vp.first] = waterloo[wp.first] = true;
	}
}

int main()
{
	int m, n;
	std::string v, w, intersect;
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; i++)
	{
		std::cin >> v >> w >> intersect;
		if (dictionary[v] == 0)
		{
			dictionary[v] = ++city;
			make_set(city);
		}
		if (dictionary[w] == 0)
		{
			dictionary[w] = ++city;
			make_set(city);
		}
		if (intersect == "intersect")
			dsu_union(dictionary[v], dictionary[w], true);
		else 
			dsu_union(dictionary[v], dictionary[w], false);
	}

	for (int i = 1; i <= n; i++)
	{
		std::cin >> v >> w;
		std::pair<int, int> vp = dsu_get(dictionary[v]);
		std::pair<int, int> wp = dsu_get(dictionary[w]);

		if ((waterloo[vp.first] || waterloo[wp.first]))
		{
			std::cout << "Waterloo\n";
			break;	
		}	
		else if (vp.first != wp.first || dictionary[v] == 0 || dictionary[w] == 0)
			std::cout << "unknown\n";
		else if (vp.second ^ wp.second)
			std::cout << "intersect\n";
		else 
			std::cout << "parallel\n";
	}

	return 0;
}
