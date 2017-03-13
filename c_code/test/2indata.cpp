#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_FILE "input.txt"

/* ī���� x, y ��ǥ�� ��� ����ü*/
typedef struct
{
	int x;
	int y;
} CAFE;

/* qsort() �Լ��� ����ϱ� ���� ���Լ�(�Լ�������) */
int compare_aec(const void * a, const void * b); // ��������
int compare_des(const void * a, const void * b); // ��������
void monotone_way(FILE * fp, CAFE * arr_cafe, int cafe_count);

int main()
{
	FILE * fp = NULL;
	int test_case, cafe_count;
	int i, j;
	CAFE * arr_cafe = NULL;

	fp = fopen(PATH_FILE, "r");
	fscanf(fp, "%d", &test_case);

	for (i = 0; i < test_case; i++)
	{
		fscanf(fp, "%d", &cafe_count);

		arr_cafe = (CAFE *)malloc(sizeof(CAFE) * cafe_count);
		memset(arr_cafe, 0, sizeof(cafe_count));

		/* ī���� ��ǥ���� �ϴ� �״�� �޾ƿ´�. */
		for (j = 0; j < cafe_count; j++)
		{
			fscanf(fp, "%d%d", &arr_cafe[j].x, &arr_cafe[j].y);
			if (arr_cafe[j].x == 0 && arr_cafe[j].y == 0)
			{
				arr_cafe[j].x = arr_cafe[0].x;
				arr_cafe[j].y= arr_cafe[0].y;
				arr_cafe[0].x = 0;
				arr_cafe[0].y = 0;
			}
		}
		/* qsort() �Լ� ���. stdlib �� �����Ǵ� sort �Լ�. */
		qsort(&arr_cafe[1], cafe_count - 1, sizeof(CAFE), compare_aec);

		monotone_way(fp, arr_cafe, cafe_count);

		free(arr_cafe);
	}

	fclose(fp);

	return 0;
}

/* ���������� ���� ���Լ� */
int compare_aec(const void * a, const void * b)
{
	const CAFE * arr1; 
	const CAFE * arr2;
	arr1 = (const CAFE *)a;
	arr2 = (const CAFE *)b;

	/* a < b �̸� -1, a > b �̸� 1, a == b �̸� 0�� �����Ѵ�. */
	if (arr1->x < arr2->x)
		return -1;
	else if (arr1->x > arr2->x)
		return 1;
	else /* ���� x���� ���� ���ٸ� y���� �������� �������� �����Ѵ�. */
	{
		if (arr1->y < arr2->y)
			return -1;
		else if (arr1->y > arr2->y)
			return 1;
		else
			return 0; 
	}
}

/* ���������� ���� ���Լ� */
int compare_des(const void * a, const void * b)
{
	const CAFE * arr1;
	const CAFE * arr2;
	arr1 = (const CAFE *)a;
	arr2 = (const CAFE *)b;

	/* �������� �Լ��� �ݴ�� ���ϰ� return �ϸ� ���������� �ȴ�. */
	if (arr1->y < arr2->y)
		return 1;
	else if (arr1->y > arr2->y)
		return -1;
	else
		return 0;
}

void monotone_way(FILE * fp, CAFE * arr_cafe, int cafe_count)
{
	int print_count, print_cafe;
	int start_ind = 1, end_ind = 0;
	int j = 0, k = 0;

	/* ������������ ���ĵ� �迭�� ������ ���ϴ� for��*/
	for (j = 1; j < cafe_count; j++)
	{
		if (j == cafe_count - 1 && arr_cafe[j].x == arr_cafe[j - 1].x)
			end_ind = j;
		else
		{
			if (arr_cafe[j].x == arr_cafe[j + 1].x && arr_cafe[j].x != arr_cafe[j - 1].x)
				if (arr_cafe[j].y != arr_cafe[j - 1].y)
					start_ind = j;

			if (arr_cafe[j].x != arr_cafe[j + 1].x && arr_cafe[j].x == arr_cafe[j - 1].x)
				end_ind = j;
			/* ���� �������� 0,0 �� �ƴϰ�, �����ȿ��� �� index�� y���� �ٸ���
			���� �̾����� �ʱ� ������ y���� �ٸ� ������ ������������ ���������ش�. */
		}
		if (start_ind < end_ind)
		{
			if (arr_cafe[start_ind].x != arr_cafe[start_ind - 1].x && arr_cafe[start_ind].y != arr_cafe[start_ind - 1].y)
				qsort(arr_cafe + start_ind, end_ind - start_ind + 1, sizeof(CAFE), compare_des);
			else
				if(arr_cafe[start_ind].x == 0 && arr_cafe[start_ind].y < 0)
					qsort(arr_cafe + start_ind, end_ind - start_ind + 1, sizeof(CAFE), compare_des);
		}
	}

	fscanf(fp, "%d", &print_count);

	/* ��� */
	for (j = 0; j < print_count; j++)
	{
		fscanf(fp, "%d", &print_cafe);
		printf("%d %d\n", arr_cafe[print_cafe - 1].x, arr_cafe[print_cafe - 1].y);
	}
}