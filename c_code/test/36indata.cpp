#include <stdio.h>
#include <stdlib.h>

typedef struct Coordinate
{
	int x;
	int y;
}Coordinate;

int Cmp(const void *a, const void *b);
int Cmp2(const void *a, const void *b);
void Change_Sort(Coordinate * Info, int Number_Coordinate);

void main(void)
{
	FILE *fp;
	fp = fopen("input.txt", "r");

	int Test_Cases;
	int Number_Coordinate;
	int Number_Order;
	int Order;
	int i;

	fscanf(fp, "%d", &Test_Cases);
	while (Test_Cases--)
	{
		fscanf(fp, "%d", &Number_Coordinate);
		Coordinate* Info = (Coordinate*)malloc(sizeof(Coordinate) * Number_Coordinate);

		for (i = 0; i<Number_Coordinate; i++)
			fscanf(fp, "%d %d", &Info[i].x, &Info[i].y); // x y 좌표를 받아옴

		qsort(Info, Number_Coordinate, sizeof(Coordinate), Cmp); // 좌표 오름차순 퀵소트
		Change_Sort(Info, Number_Coordinate);
		
		fscanf(fp, "%d", &Number_Order);
		for (i = 0; i < Number_Order; i++)
		{
			fscanf(fp, "%d", &Order);
			printf("%d %d\n", Info[Order-1].x, Info[Order-1].y);
		}
	}
}

int Cmp(const void *a, const void *b)
{
	const Coordinate *m = (const Coordinate *)a;
	const Coordinate *n = (const Coordinate *)b;

	if (m->x < n->x)
		return -1;
	else if (m->x == n->x)
	{
		if (m->y < n->y)
			return 0;
		else if(m->y > n->y)
			return 1;
	}
	else 
		return 1;
}

int Cmp2(const void *a, const void *b)
{
	const Coordinate *m = (const Coordinate *)a;
	const Coordinate *n = (const Coordinate *)b;

	if (m->x < n->x)
		return -1;
	else if (m->x == n->x)
	{
		if (m->y < n->y)
			return 1;
		else if (m->y > n->y)
			return 0;
	}
	else
		return 1;
}


void Change_Sort(Coordinate * Info , int Number_Coordinate)
{
	int i, j, p, q;
	int Start;
	int Border;
	int temp;

	for (i = 0; i < Number_Coordinate - 1; i++)
	{
		if(Info[0].x ==0 && Info[0].y != 0)
			qsort(Info, Number_Coordinate, sizeof(Coordinate), Cmp2);

		else if ( (Info[i].x != Info[i + 1].x) && (Info[i].y != Info[i + 1].y) )
		{
			Start = i+1;
			for (j = Start; j < Number_Coordinate - 1; j++)
			{
				if (Info[j].x != Info[j + 1].x)
				{
					Border = j + 1;
					break;
				}
				if (j + 1 == Number_Coordinate - 1)
					Border = Number_Coordinate ;
			}

			p = Start;

			for (p; p < Border-1; p++) // 뒤집기
			{
				for (q=p+1; q < Border; q++)
				{
					temp = Info[p].y;
					Info[p].y = Info[q].y;
					Info[q].y = temp;
				}
			}
		}
	}
}