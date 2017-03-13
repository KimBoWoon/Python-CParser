/*
	���δ��б� ����������Ŵ���
	��ǻ�Ͱ��к� 20143031 ��⿬
	�˰��� hw#3 Monotone Walkway
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
bool cmp_y(const point &a, const point &b);  //�� ��ǥ�� y���� �������� ������������ �����ϱ� ���� ���Լ�

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
		//x��ǥ�� �������� ����(��� �ڳʿ��� 90�� ������ ����/���������� ȸ���� �� �� �־)
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
				//Ȯ���ؾ� �ϴ� ���� ī�� ��ǥ�� ���� ī�� ��ǥ�� ���� ��� ���� x��ǥ�� ���������ش�
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
				{  //���� ī���� y��ǥ�� �ٸ��� y��ǥ�� ������������ �����ؼ� �ٽ� ���� �̾��ش�
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
			//�迭 index�� ������ 0���� �̹Ƿ� -1�� ���־�� ��
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