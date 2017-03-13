#include <stdio.h>
#pragma warning(disable:4996)


int T, N, M;
int arr[100000][2];
int tmp[100000][2];
int result[100000][2];
int aa;

void quicksort(int start, int end)
{
	int p = arr[(start + end) / 2][0];
	int s = start;
	int e = end;

	while (s <= e)
	{
		while (arr[s][0] < p && s <= e) s++;
		while (p < arr[e][0] && s <= e) e--;

		if (s <= e)
		{
			int tmp1 = arr[s][0];
			int tmp2 = arr[s][1];
			arr[s][0] = arr[e][0];
			arr[s][1] = arr[e][1];
			arr[e][0] = tmp1;
			arr[e][1] = tmp2;

			s++; e--;
		}
	}

	if (start < e) quicksort(start, e);
	if (s < end) quicksort(s, end);
}

void quick(int start, int end)
{
	int p = tmp[(start + end) / 2][1];
	int s = start;
	int e = end;

	while (s <= e)
	{
		while (tmp[s][1] < p && s <= e) s++;
		while (p < tmp[e][1] && s <= e) e--;

		if (s <= e)
		{
			int tmp1 = tmp[s][0];
			int tmp2 = tmp[s][1];
			tmp[s][0] = tmp[e][0];
			tmp[s][1] = tmp[e][1];
			tmp[e][0] = tmp1;
			tmp[e][1] = tmp2;

			s++; e--;
		}
	}

	if (start < e) quick(start, e);
	if (s < end) quick(s, end);
}

void find(int x, int y)
{
	int j = 0;
	int i = 0, k = 0, a = 0;
	for (i = aa; i < N; i++)
	{
		if (arr[i][0] != x)
			break;
		tmp[j][0] = arr[i][0];
		tmp[j++][1] = arr[i][1];
	}

	quick(0, j - 1);

	if (tmp[0][0] == x && tmp[0][1] == y)
	{
		for (k = 0; k < j; k++)
		{
			result[aa][0] = tmp[k][0];
			result[aa++][1] = tmp[k][1];
		}
		if (aa != N)
			find(arr[aa][0], tmp[j - 1][1]);
	}
	else
	{
		for (a = j - 1; a >= 0; a--)
		{
			result[aa][0] = tmp[a][0];
			result[aa++][1] = tmp[a][1];
		}
		if (aa != N)
			find(arr[aa][0], tmp[0][1]);
	}
}

int main()
{
	FILE* in_file;

	in_file = fopen("input.txt", "r");

	fscanf(in_file, "%d", &T);

	int p, q;

	while (T--)
	{
		aa = 0;

		fscanf(in_file, "%d", &N);
		for (p = 0; p < N; p++)
			fscanf(in_file, "%d %d", &arr[p][0], &arr[p][1]);

		quicksort(0, N - 1);

		find(0, 0);

		fscanf(in_file, "%d", &M);
		int tmp;
		for (q = 0; q < M; q++)
		{
			fscanf(in_file, "%d", &tmp);
			printf("%d %d\n", result[tmp - 1][0], result[tmp - 1][1]);
		}
	}

	return 0;
}