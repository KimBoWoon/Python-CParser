#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm> 
using namespace std;

struct CD {
	int nx, ny;
}cd[100002];

int comp(const CD &a, const CD &b);
int comp2(const CD &a, const CD &b);

int main()
{
	FILE *f;
	f = fopen("input.txt", "r");
	int ncase, n, m, p;
	int i, j, k, o;
	int c;
	fscanf(f, "%d", &ncase);
	for (i = 0; i<ncase; i++)
	{
		fscanf(f, "%d", &n);

		for (j = 0; j<n; ++j)
			fscanf(f, "%d%d", &cd[j].nx, &cd[j].ny);

		sort(cd, cd + n, comp);

		for (k = 0; k<n; )
		{

			c = k;

			for (int l = k + 1; l<n; ++l)
			{
				if (cd[k].nx == cd[l].nx)
					c = l;
				else
					break;
			}

			if (k != c)
			{
				if (cd[k - 1].ny != cd[k].ny)
					sort(cd + k, cd + c + 1, comp2);

				k = c + 1;
			}
			else
				++k;
		}
		fscanf(f, "%d", &m);
		for (o = 0; o<m; o++) {
			fscanf(f, "%d", &p);
			printf("%d %d\n", cd[p - 1].nx, cd[p - 1].ny);
		}
	}

	return 0;

}

int comp(const CD &a, const CD &b) {
	return a.nx != b.nx ? a.nx < b.nx : a.ny < b.ny;
}

int comp2(const CD &a, const CD &b) {
	return a.ny > b.ny;
}