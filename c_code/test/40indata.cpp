#include <cstdio>
#include <algorithm>

#define MAX 100001
using namespace std;
struct mono_tone
{ //mono_tone 구조체
	int x; //x축값
	int y; //y축값
	int n; //cafe번호
	int d; //거리

};
void short_path_find(struct mono_tone *mo, int count_cafe);
int cmp(const mono_tone &a, const mono_tone &b);
int cmp2(const mono_tone &a, const mono_tone &b);
int cafe_find_x(int m, int count_cafe, struct mono_tone *mo);
int cafe_find_y(int m, int count_cafe, struct mono_tone *mo);
void short_path_find(struct mono_tone *mo, int count_cafe)
{
	int i, j, k, l;
	int x, y;
	
	
	sort(mo, mo + count_cafe, cmp);
	
	for (i = 0; i < count_cafe; i++)
	{
		int start = 0;
		int end = 0;

		start = i;
		int copystart = start;
		while (mo[copystart].x == 0 && mo[copystart].y<0)
		{
			end++;
			copystart++;
		}
		sort(mo + start, mo + start + end + 1, cmp2);
		break;


	}
	for (i = 0; i < count_cafe; i++)
	{
		int start = 0;
		int end = 0;
		if (mo[i].x != mo[i + 1].x && mo[i].y != mo[i + 1].y)
		{
			start = i + 1;
			int copystart = start;
			while (mo[copystart].x == mo[copystart + 1].x)
			{
				end++;
				copystart++;
			}
			sort(mo + start, mo + start + end + 1, cmp2);
			i += end;
		}

	}
	
	int num = 1;
	for (i = 0; i < count_cafe; i++)
	{
		mo[i].n = num++;
	}

}
int cmp(const mono_tone &a, const mono_tone &b) {
	return a.x != b.x ? a.x < b.x : a.y < b.y;
}
int cmp2(const mono_tone &a, const mono_tone &b) {
	return a.y > b.y;
}


int cafe_find_x(int m, int count_cafe, struct mono_tone *mo)
{
	int i;
	int caf_num;
	for (i = 0; i < count_cafe; i++)
	{
		if (mo[i].n == m)
			caf_num = mo[i].x;

	}
	return caf_num;
}
int cafe_find_y(int m, int count_cafe, struct mono_tone *mo)
{
	int i;
	int caf_num;
	for (i = 0; i < count_cafe; i++)
	{
		if (mo[i].n == m)
			caf_num = mo[i].y;

	}
	return caf_num;
}
int main(void)
{
	FILE *fp;
	fp = fopen("input.txt", "r");

	int test_case;

	fscanf(fp, "%d", &test_case);

	int i;


	for (i = 0; i < test_case; i++)
	{
		int count_cafe;
		struct mono_tone mo[MAX];

		fscanf(fp, "%d", &count_cafe);
	
		int j;


		for (j = 0; j < count_cafe; j++)
		{

			fscanf(fp, "%d", &mo[j].x);
			fscanf(fp, "%d", &mo[j].y);
	
		}

		int k;
		
		int l, m;
		int cafe_num;

		short_path_find(mo, count_cafe);
		
		
		fscanf(fp, "%d", &cafe_num);

		for (m = 0; m < cafe_num; m++)
		{
			int j;
			fscanf(fp, "%d", &j);
			printf("%d ", cafe_find_x(j, count_cafe, mo));
			printf("%d\n", cafe_find_y(j, count_cafe, mo));
		}
		
	}

}