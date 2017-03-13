#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;

struct Point
{
	int x, y;
};

bool compare(const Point &a, const Point &b)
{
	if (a.x == b.x)
		return a.y < b.y;
	return a.x < b.x;
}

bool compareY(const Point &a, const Point &b)
{
	return a.y > b.y;
}

int main()
{
	ifstream fin;
	fin.open("input.txt");
	int testCase;
	fin >> testCase;

	while (testCase--)
	{
		int number;
		fin >> number;
		Point point[100010] = { 0, };

		for (int i = 1; i <= number; i++)
			fin >> point[i].x >> point[i].y;

		point[number + 1].x = point[number + 1].y = 100010;
		sort(&point[1], &point[number + 1], compare);

		for (int i = 1; i < number; i++)
		{
			if (point[i].x == point[i + 1].x)
			{
				int tmp = i;
				for (int j = i; j <= number; j++)
				{
					if (point[j].x != point[j + 1].x)
					{
						tmp = j;
						break;
					}
				}

				if (point[i - 1].y != point[i].y)
					sort(&point[i], &point[tmp + 1], compareY);

				i = tmp;
			}
		}

		fin >> number;
		for (int i = 0; i < number; i++)
		{
			int resultCase;
			fin >> resultCase;
			cout << point[resultCase].x << " " << point[resultCase].y << endl;
		}
	}
}