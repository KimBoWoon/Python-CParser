/**************************************************
*                                                 *
*               문제3 모노톤 길                   *
*                20113309 이식                    *
*                                                 *
**************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 100003

typedef struct Cafe
{
	int x;
	int y;
}cafe;


int compare(const void *first, const void *second);
void mono3(cafe *monoCafe, int numCafe);
void reverseRecursive(cafe a[], int begin, int end);


int main(void)
{
	FILE* inFile;
	inFile = fopen("input.txt", "r");

	if (inFile == NULL)
	{
		printf("파일에 문제가 있습니다. \n");
		exit(1);
	}

	int testNum;
	int i;

	fscanf(inFile, "%d", &testNum);

	for (i = 0; i < testNum; i++)
	{
		int numCafe;
		int j;
		int pnCafe;

		fscanf(inFile, "%d", &numCafe);

		cafe monoCafe[MAXNUM];
		
		for (j = 0; j < numCafe; j++)
		{
			fscanf(inFile, "%d %d", &monoCafe[j].x, &monoCafe[j].y);
		}
	
		fscanf(inFile, "%d", &pnCafe);

		mono3(monoCafe, numCafe);

		int input;

		for (j = 0; j < pnCafe; j++)
		{
			fscanf(inFile, "%d", &input);

			printf("%d %d\n", monoCafe[input-1].x,monoCafe[input-1].y);
		}
	}
	return 0;
}


void mono3(cafe *monoCafe, int numCafe)
{
	qsort(monoCafe, numCafe, sizeof(cafe), compare);

	int zstartPoint=0;
	int zendPoint;

	if (monoCafe[0].y != 0)
	{
		int j;
		for (j = zstartPoint + 1; j<numCafe; j++)
		{
			if (monoCafe[zstartPoint].x == monoCafe[j].x)
				zendPoint = j;
			else
				break;
		}
		if (zstartPoint != zendPoint)
			reverseRecursive(monoCafe, zstartPoint, zendPoint);

	}

	int startPoint = 0;

	while(startPoint<numCafe)
	{
		int endPoint = startPoint;
		int j;
		for (j = startPoint + 1; j<numCafe; j++)
		{
			if (monoCafe[startPoint].x == monoCafe[j].x)
				endPoint = j;
			else
				break;
		}

		if (startPoint != endPoint) {
			if (monoCafe[startPoint - 1].y != monoCafe[startPoint].y && startPoint != 0)
				reverseRecursive(monoCafe, startPoint, endPoint);
			startPoint = endPoint + 1;
		}
		else
			startPoint = startPoint + 1;
	}
}


int compare(const void *first,const void *second)
{
	cafe *one, *two;

	one = (cafe*)first;
	two = (cafe*)second;


	if (one->x > two->x)
	{
		return 1;
	}
	else if (one->x < two->x)
		return -1;
	else
	{
		if (one->y >= two->y)
			return 1;
		else
			return -1;
	}
}

void swap(cafe arr[], int a, int b)
{
	cafe temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void reverseRecursive(cafe a[], int begin, int end)
{
	if (begin < end)
	{
		swap(a, begin, end);
		reverseRecursive(a, begin + 1, end - 1);
	}
}