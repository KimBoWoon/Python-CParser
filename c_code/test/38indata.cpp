#include<iostream>
#include<fstream>
#include<algorithm>

using namespace std;
void sort2(class Cafe *cafes, int number);

class Cafe
{
public:
	int x, y;
	Cafe()
		:x(0), y(0)
	{}
};

bool compare(class Cafe a, class Cafe b)
{
	if (a.x == b.x)
		return a.y < b.y;
	return a.x < b.x;
}

int main(void)
{
	int test, number, x, y, count, obj,i,j;
	ifstream infile;

	infile.open("input.txt");
	infile >> test;
	for (i = 0; i < test; i++)
	{
		infile >> number;
		Cafe *cafes = new Cafe[number];
		for (j = 0; j < number; j++)
		{
			infile >> x >> y;
			cafes[j].x=x;
			cafes[j].y = y;
		}
		
		sort(cafes, cafes+number, compare);
		sort2(cafes, number);

		infile >> count;
		for (j = 0; j < count; j++)
		{
			infile >> obj;
			cout << cafes[obj - 1].x << ' ' << cafes[obj - 1].y << endl;
		}
		delete[] cafes;
	}
	infile.close();
	return 0;
}

void sort2(class Cafe *cafes, int number)
{
	int i,j,count;

	count = 0;
	if (cafes[0].x != 0 || cafes[0].y != 0)
	{
		for (i = 0;; i++)
		{
			count++;
			if (cafes[i].x == 0 && cafes[i].y == 0)
				break;
		}
		reverse(cafes, cafes + count);
	}

	for (i = 0; i < number-1; i++)
	{
		count = -1;
		if (cafes[i].x != cafes[i + 1].x && cafes[i].y != cafes[i + 1].y)
		{
			for (j = i + 1;; j++)
			{
				count++;
				if (cafes[j].x != cafes[i + 1].x)
					break;
			}
			reverse(cafes+i+1,cafes+i+1+count);
		}
	}

	
}