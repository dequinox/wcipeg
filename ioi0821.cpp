/*
 *
 * IOI '08 - Cairo, Egypt
 *  Linear Garden
 *
*/

#include <stdio.h>
#include <iostream>

const int MAXN = 1000001;
	char garden[MAXN];
	long long int pow2[MAXN];

int main()
{
	int N;
        long long int M, answer = 0;

	scanf("%d%lld", &N, &M);
	scanf("%s", garden);

	pow2[0] = 1;
	for (int i = 1; i <= N; i++)
		pow2[i] = (pow2[i - 1] * 2) % M;

	int upper, lower, current, K = N;
	upper = lower = current = 0;

	for (int i = 0; i < N; i++)
	{
		K--;
		if (garden[i] == 'P')
		{
			int vupper = std::max(current + 1, upper);

			if (vupper - lower == 1) 
				answer = (answer + pow2[K / 2] + pow2[(K + 1) / 2] + M - 1) % M;
		        else if (vupper - lower == 2)
			{
				if (current == lower)
					answer = (answer + pow2[(K + 1) / 2]) % M;
				else 
					answer = (answer + pow2[K / 2]) % M;
			}
			current--;
			lower = std::min(lower, current);
		}
		else 
		{
			current++;
			upper = std::max(upper, current);
		}
	}

	printf("%lld\n", (answer + 1) % M);
	return 0;
            }
