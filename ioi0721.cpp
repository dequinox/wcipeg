/*
 *
 * IOI '07 - Zagreb, Croatia
 * Miners
 *
*/

#include <stdio.h>
#include <iostream>

const int MAXN = 100001;
const int INF = 1000000000;

int amount[14][14];
int newamount[14][14];
char shipment[MAXN];

int key(char c)
{
	switch (c)
	{
		case 'B': return 1;
		case 'F': return 2;
		case 'M': return 3;
		default : return 0;	
	}
}

int next(char c, int i)
{
	if (i == 0) return key(c);
	if (i < 4)  return i * 3 + key(c);
	return ((i - 1) % 3 + 1) * 3 + key(c);
}

int calc(int a, int b)
{
	if (a == 0) return 1;
	if (a < 4) return b % 4 == 0 ? 1 : 2;

	int x = (a - 1) / 3;
        int y = (a - 1) % 3 + 1;
        int z = (b - 1) % 3 + 1;
	
	if (x == y) return y == z ? 1 : 2;
	if (y == z) return x == z ? 1 : 2;
	if (x == z) return 2;
	
	return 3;
}

void copy()
{
	for (int f = 0; f < 13; f++)
		for (int s = 0; s < 13; s++)
		{
			amount[f][s] = newamount[f][s];
			newamount[f][s] = -INF;
		}
}

int main()
{
	int N;
	int maxcoal = 0;

	scanf("%d", &N);
	scanf("%s", shipment);

	for (int f = 0; f < 13; f++)
		for (int s = 0; s < 13; s++)
			newamount[f][s] = amount[f][s] = -INF;
	amount[0][0] = 0;
	
	for (int i = 0; i < N; i++)
	{
		for (int f = 0; f < 13; f++)
			for (int s = 0; s < 13; s++)
			{
				if (amount[f][s] == -INF)
					continue;

				char c = shipment[i];
				newamount[next(c, f)][s] = std::max(newamount[next(c, f)][s], amount[f][s] + calc(f,next(c, f)));
				newamount[f][next(c, s)] = std::max(newamount[f][next(c, s)], amount[f][s] + calc(s, next(c, s)));
			}
		copy();
	}

	for (int f = 0; f < 13; f++)
		for (int s = 0; s < 13; s++)
			maxcoal = std::max(maxcoal, amount[f][s]);

	printf("%d\n", maxcoal);

	return 0;
}
