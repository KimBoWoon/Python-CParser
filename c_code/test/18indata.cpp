#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
//#include "String"
#define MAX 100002

using namespace std;

struct Coordinate {
	int x, y;
};

int Increase(const Coordinate&a, const Coordinate&b) //��������
{
	if (a.x != b.x) return a.x < b.x;
	else return a.y < b.y;
}

int Y_Decrease(const Coordinate &a, const Coordinate &b) //Y��ǥ ��������
{
	return a.y>b.y;
}

int main(void)
{
	ifstream inStream;
	int Num_TestCases;

	inStream.open("input.txt");

	if (inStream.fail())
	{
		cerr << "������ �ҷ����� ���߽��ϴ�.\n";
		exit(1);
	}

	inStream >> Num_TestCases;

	for (int i = 0; i < Num_TestCases; i++)
	{
		int Count_Cafe;
		struct Coordinate arr[MAX];
		inStream >> Count_Cafe;
		
		for (int j = 0; j < Count_Cafe; j++)
		{
			inStream >> arr[j].x >> arr[j].y;
		}
		
		sort(arr, arr+Count_Cafe, Increase); //x��ǥ ��������
		
		for (int j = 0; j < Count_Cafe;)
		{
			int temp = j;
			for (int k = j + 1; k < Count_Cafe; ++k)
			{
				if (arr[j].x == arr[k].x)
					temp = k;
				else
					break;
			}

			if (j != temp)
			{
				if (arr[j].y != arr[j - 1].y)
					sort(arr + j, arr + temp + 1, Y_Decrease);
					j = temp + 1;
			}
			else
				++j;
		}
		
		
		int Count;
		
		inStream >> Count;
		
		for (int j = 0; j < Count; j++)
		{
			int Cafe_Num;
			inStream >> Cafe_Num;
			cout << arr[Cafe_Num - 1].x << " " << arr[Cafe_Num - 1].y << endl;
		}
		
		

	}

	inStream.close();
}