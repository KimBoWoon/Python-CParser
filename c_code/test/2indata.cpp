#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_FILE "input.txt"

/* 카페의 x, y 좌표를 담는 구조체*/
typedef struct
{
	int x;
	int y;
} CAFE;

/* qsort() 함수를 사용하기 위한 비교함수(함수포인터) */
int compare_aec(const void * a, const void * b); // 오름차순
int compare_des(const void * a, const void * b); // 내림차순
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

		/* 카페의 좌표들을 일단 그대로 받아온다. */
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
		/* qsort() 함수 사용. stdlib 에 지원되는 sort 함수. */
		qsort(&arr_cafe[1], cafe_count - 1, sizeof(CAFE), compare_aec);

		monotone_way(fp, arr_cafe, cafe_count);

		free(arr_cafe);
	}

	fclose(fp);

	return 0;
}

/* 오름차순에 사용될 비교함수 */
int compare_aec(const void * a, const void * b)
{
	const CAFE * arr1; 
	const CAFE * arr2;
	arr1 = (const CAFE *)a;
	arr2 = (const CAFE *)b;

	/* a < b 이면 -1, a > b 이면 1, a == b 이면 0을 리턴한다. */
	if (arr1->x < arr2->x)
		return -1;
	else if (arr1->x > arr2->x)
		return 1;
	else /* 만약 x값이 서로 같다면 y값을 기준으로 오름차순 정렬한다. */
	{
		if (arr1->y < arr2->y)
			return -1;
		else if (arr1->y > arr2->y)
			return 1;
		else
			return 0; 
	}
}

/* 내림차순에 사용될 비교함수 */
int compare_des(const void * a, const void * b)
{
	const CAFE * arr1;
	const CAFE * arr2;
	arr1 = (const CAFE *)a;
	arr2 = (const CAFE *)b;

	/* 오름차순 함수와 반대로 비교하고 return 하면 내림차순이 된다. */
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

	/* 오름차순으로 정렬된 배열의 값들을 비교하는 for문*/
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
			/* 만약 시작점이 0,0 이 아니고, 구간안에서 전 index의 y값이 다르면
			길이 이어지지 않기 때문에 y값이 다른 구간은 내림차순으로 역정렬해준다. */
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

	/* 출력 */
	for (j = 0; j < print_count; j++)
	{
		fscanf(fp, "%d", &print_cafe);
		printf("%d %d\n", arr_cafe[print_cafe - 1].x, arr_cafe[print_cafe - 1].y);
	}
}