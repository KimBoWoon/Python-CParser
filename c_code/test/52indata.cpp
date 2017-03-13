#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 100001

typedef struct position
{
	int x, y;
}Position;

int CompareX(const void* a, const void* b);
int CompareY(const void* a, const void* b);
void SortY(Position cafes[], int numOfCafes);
//void PrintArr(Position* pos, int length);
int posY=0;  //거리를 구하기위한 y좌표

int main(void)
{
	FILE* fp = NULL;
	Position cafes[MAXSIZE];
	int testCases;
	int numOfCafe;
	int i, j, numOfOutput, tempOutput;
	fp = fopen("input.txt", "r");
	if (fp == NULL)
		exit(1);

	fscanf(fp, "%d", &testCases);
	while (testCases--)
	{
		posY = 0;
		memset(cafes, 0, sizeof(cafes));
		fscanf(fp, "%d", &numOfCafe);
		
		//Input cafe's position
		for (i = 0; i < numOfCafe; i++)
			fscanf(fp, "%d %d", &((cafes + i)->x),&((cafes + i)->y));

		qsort(cafes, numOfCafe, sizeof(Position), CompareX);
		SortY(cafes, numOfCafe);

		fscanf(fp, "%d", &numOfOutput);
		for (i = 0; i < numOfOutput; i++)  //출력
		{
			fscanf(fp, "%d", &tempOutput);
			printf("%d %d\n", (cafes + tempOutput-1)->x, (cafes + tempOutput-1)->y);
		}
	}
	
	return 0;
}

int CompareX(const void* a, const void* b)  //X좌표 정렬(오름차순)
{
	if (((Position*)a)->x > ((Position*)b)->x)
		return 1;
	else if (((Position*)a)->x == ((Position*)b)->x)
		return 0;
	return -1;
}

int CompareY(const void* a, const void* b) //Y좌표 정렬(오름차순)
{
	if (abs(posY - ((Position*)a)->y) > abs(posY - ((Position*)b)->y))
		return 1;
	else if (abs(posY - ((Position*)a)->y) < abs(posY - ((Position*)b)->y))
		return -1;
	return 0;
}

void SortY(Position cafes[], int numOfCafes)
{
	int i=0, j, numOfSameX, index, same=1;
	
	while (1)
	{
		numOfSameX = 0, same = 1;
		if (i >= numOfCafes-1)
			break;

		if (cafes[i].x != cafes[i + 1].x)  //X좌표가 다른 경우
		{
			posY = cafes[i].y;
			i++;
			continue;
		}

		while (cafes[i + numOfSameX].x == cafes[i + numOfSameX + 1].x && i + numOfSameX < numOfCafes && i+same<numOfCafes)
		{
			same++;
			numOfSameX++;
		}

		qsort(&cafes[i], same, sizeof(Position), CompareY);
		//PrintArr(cafes, numOfCafes);
		i = i + numOfSameX;
	}
}


void PrintArr(Position* pos, int length)
{
	int i = 0;
	for(i=0;i<length;i++)
		printf(">>%d    %d                   ypos>> %d\n", pos[i].x, pos[i].y, posY);
}