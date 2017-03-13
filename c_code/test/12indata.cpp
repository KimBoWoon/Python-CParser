/*************************************
*
*   Prob No.3 <Monotone Walkway>
*   Name : Jaeyoung Song
*   S/N  : 20113290
*   Exp  : x좌표를 역행하지 않고
*		   대각선으로 움직이지 않는
*		   외길의 체크 포인트
*
*************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

int main(void)
{
	ifstream inStream;
	int caseNum;

	inStream.open("input.txt");
	if (inStream.fail())
	{
		cerr << "Input file opening failed. \n";
		exit(1);
	}

	inStream >> caseNum;

	for (int i = 0; i<caseNum; i++)
	{
		int j, k, l, m, x, temp;
		int cafeNum, pointX, pointY;
		int checkCafe;

		inStream >> cafeNum;

		vector<pair<int, int> > cafe(cafeNum);
		
		for (j = 0; j < cafeNum; j++)				// data scan
		{
			inStream >> pointX >> pointY;

			cafe[j].first = pointX;
			cafe[j].second = pointY;
		}

		sort(cafe.begin(), cafe.end());

		for (j = 0; j < cafeNum-1; j++)
		{
			if (j==0 && cafe[j].second != 0)
			{
				for (k = j; cafe[j].first == cafe[k].first && k < cafeNum; ++k){}
				
				reverse(cafe.begin(), cafe.begin() + k);
			}
			if (cafe[j].first != cafe[j + 1].first)
			{
				if (cafe[j].second != cafe[j + 1].second)
				{
					for (k = j+1; k < cafeNum && cafe[j + 1].first == cafe[k].first; ++k){}

					if (k == cafeNum)
						reverse(cafe.begin() + j + 1, cafe.end());
					else
						reverse(cafe.begin() + j + 1, cafe.begin() + k);
				}
			}
		}

		inStream >> checkCafe;

		for (j = 0; j < checkCafe; j++)
		{
			inStream >> temp;
			cout << cafe[temp - 1].first << ' ' << cafe[temp - 1].second << endl;
		}
	}
	inStream.close();
}
