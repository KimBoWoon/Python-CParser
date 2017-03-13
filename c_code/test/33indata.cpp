/************************************************
*												*
*국민대학교 전자정보통신대학 컴퓨터공학부 3학년	*
*						20123411 전효창			*
*												*
************************************************/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define MAX 100002

struct Location {
	int x;
	int y;
};

bool compare_xy(Location a, Location b);

int main() {
	int i, j, c;
	int data_num, cafe_num;
	int print_count, print_num;
	int zero_check;
	Location xy[MAX];
	Location temp;

	ifstream in_file;
	in_file.open("input.txt");

	in_file >> data_num;

	for (i = 0; i < data_num; i++)
	{
		zero_check = 0;

		in_file >> cafe_num;

		for (j = 0; j < cafe_num; j++)
		{
			in_file >> xy[j].x >> xy[j].y;
			if (xy[j].x == 0)
				zero_check++;
		}

		sort(xy, xy + cafe_num, compare_xy);

		if (xy[0].y < 0)
			reverse(xy, xy + zero_check);

		for (j = zero_check; j < cafe_num; j++)
		{
			if (xy[j - 1].x != xy[j].x)
			{
				for (c = j + 1; c < cafe_num; c++)
				{
					if (xy[j].x != xy[c].x)
						break;
				}

				if (xy[j - 1].y != xy[j].y)
					reverse(xy + j, xy + c);

				j += c - 2;
			}
		}

		in_file >> print_count;

		for (j = 0; j < print_count; j++)
		{
			in_file >> print_num;
			cout << xy[print_num - 1].x << " " << xy[print_num - 1].y << endl;
		}

	}

	in_file.close();

	return 0;
}

bool compare_xy(Location a, Location b)
{
	return a.x != b.x ? a.x < b.x : a.y < b.y;
}