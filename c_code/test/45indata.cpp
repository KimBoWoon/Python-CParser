/*
	국민대학교 전자정보통신대학
	컴퓨터공학부 20143031 김기연
	알고리즘 hw#3 Monotone Walkway
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

struct point
{
	int x, y;
}store[100002];

bool cmp(const point &a, const point &b);
bool cmp_y(const point &a, const point &b);  //두 좌표중 y값을 기준으로 내림차순으로 정렬하기 위한 비교함수

int main()
{
	ifstream inputf;
	int testcase_num;

	inputf.open("input.txt");
	if (inputf.fail())
	{
		cout << "file open error" << endl;
		exit(1);
	}

	inputf >> testcase_num;
	while (testcase_num--)
	{
		int store_num;
		inputf >> store_num;
		int count = 0;

		while (store_num--)
		{
			inputf >> store[count].x >> store[count].y;
			++count;
		}
		//x좌표를 기준으로 정렬(모든 코너에서 90도 각도로 왼쪽/오른쪽으로 회전만 할 수 있어서)
		sort(store, store + count, cmp);
		int i = 0;

		while (i < count) 
		{
			int now_x = i;
			int next_dot = i + 1;

			for (; next_dot < count; ++next_dot)
			{
				if (store[i].x != store[next_dot].x)
					break;
				//확인해야 하는 현재 카페 좌표가 이전 카페 좌표와 같은 경우 현재 x좌표를 증가시켜준다
				else if (store[i].x == store[next_dot].x)
					now_x = next_dot;
				else
					break;
			}

			if (i == now_x)
				i += 1;
			else if(i != now_x)
			{
				if (store[i - 1].y != store[i].y)
				{  //다음 카페의 y좌표가 다르면 y좌표를 내림차순으로 정렬해서 다시 길을 이어준다
					sort(store + i, store + now_x + 1, cmp_y);
				}
				i = now_x + 1;
			}
		}

		int print_num;
		inputf >> print_num;
		while (print_num--)
		{
			int print_store_num;
			inputf >> print_store_num;
			//배열 index의 시작은 0부터 이므로 -1을 해주어야 함
			cout << store[print_store_num - 1].x << " " << store[print_store_num - 1].y << endl;
		}
	}

	return 0;
}

bool cmp(const point &a, const point &b)
{
	if (a.x != b.x)
		return a.x < b.x;
	else
		return a.y < b.y;
}

bool cmp_y(const point &a, const point &b)
{
	return a.y > b.y;
}