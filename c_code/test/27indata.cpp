/****************************************************************
*      과제 : homework #3 : Monotone Walkway				     *
*      학번 : 20123396								             *
*      이름 : 이 동 혁										     *
****************************************************************/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>


#define MAX 100002 // 최대 카페수 

using namespace std;

class Cafe
{
public:
	int Xpos; //카페의 x좌표
	int Ypos; //카페의 y좌표
};

int asc(const Cafe &x, const Cafe &y) // 오름차순 정렬함수
{
	return x.Xpos == y.Xpos ? x.Ypos < y.Ypos : x.Xpos < y.Xpos;
}


int desc(const Cafe &x, const Cafe &y) // 내림차순 정렬함수
{
	return x.Ypos> y.Ypos;
}

int main()
{

	ifstream inStream;
	int numTestCases; // 테스트 할 수
	int numOfCafe; // 입력받을 카페의 수

	int answerNumCafe; // 정답을 알고 싶은 카페의 수
	int answerCafePoint; // 카페의 번호

	inStream.open("input.txt");
	inStream >> numTestCases;

	for (int i = 0; i<numTestCases; i++)
	{
		inStream >> numOfCafe;
		Cafe cafePos[MAX] = { 0, }; // 초기 카페의 좌표는 0으로 초기화

		for (int i = 1; i <= numOfCafe; i++)
		
			inStream >> cafePos[i].Xpos >> cafePos[i].Ypos; // 카페의 x좌표와 y좌표를 입력받음
			cafePos[numOfCafe + 1].Xpos = 100001; cafePos[numOfCafe + 1].Ypos = 100001;

			sort(cafePos + 1, cafePos + numOfCafe + 1, asc);
			
			/*
				x에대해 오름차순으로 정렬하고
				x가같으면 y에대해서 오름차순으로 정렬한다.
			*/
		

		//카페를 검색하다가 x , y 좌표가 다르면 차순을 뒤집는다.
		for (int i = 1; i <= numOfCafe; i++)
		{
			int numOfSameX = i; // x좌표가 같은 카페의 수를 카운팅한다.

			for (int j = i + 1; j <= numOfCafe + 1; j++)
			{
				if (cafePos[i].Xpos == cafePos[j].Xpos)
					numOfSameX = j;
				else
					break;
			}

			if (cafePos[i - 1].Ypos != cafePos[i].Ypos) // y좌표가 같지 않으면 내림차순 정렬
				sort(cafePos + i, cafePos + numOfSameX + 1, desc);
			i = numOfSameX;

		}

		inStream >> answerNumCafe;
		for (int i = 0; i<answerNumCafe; i++)
		{
			inStream >> answerCafePoint;
			cout << cafePos[answerCafePoint].Xpos << " " << cafePos[answerCafePoint].Ypos << endl;
		}

	}
	return 0;
}