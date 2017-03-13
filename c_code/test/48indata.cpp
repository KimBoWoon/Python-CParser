#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

struct Cafe
{
	int x, y;
};

Cafe cafe[100001];

bool compare1(const Cafe& a, const Cafe& b)
{
	if (a.x == b.x)
	{
		return a.y < b.y;
	}
	else
	{
		return a.x < b.x;
	}
}

int main(void)
{
	FILE * infile;

	infile = fopen("input.txt", "r");

	int numCases;

	fscanf(infile, "%d", &numCases);
	memset(cafe, 0xFF, sizeof(cafe));
	
	for (int i = 0; i < numCases; i++)
	{
		int cafeCount;

		fscanf(infile, "%d", &cafeCount);

		for (int j = 0; j < cafeCount; j++)
		{
			int x, y;
			
			fscanf(infile, "%d %d", &x, &y);
			
			cafe[j].x = x;
			cafe[j].y = y;
		}
	
		std::sort(cafe, cafe + cafeCount, compare1);

		for (int j = 0; j < cafeCount;)
		{
			for (int k = 0; ; k++)
			{
				if (cafe[j + k].x != cafe[j].x)
				{
					if (cafe[j-1].y - cafe[j].y != 0)
					{
						std::reverse(cafe + j, cafe + j + k);
					}

					j = j + k;
					break;
				}
			}
		}

		int m, n;

		fscanf(infile, "%d", &m);

		for (int j = 0; j < m; j++)
		{
			fscanf(infile, "%d", &n);
			std::cout << cafe[n-1].x << " " << cafe[n-1].y << std::endl;
		}
	}
	return 0;
}