#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <cmath>
#define MAX 100002
using namespace std;

class Cafe
{
public:
	int Xpos;
	int Ypos;
};
// x좌표 같으면 y 내림차순 x 다르면 x 내림차순

int sortRule(const Cafe &x ,const Cafe &y)
{
		return x.Xpos == y.Xpos ? x.Ypos < y.Ypos : x.Xpos < y.Xpos;
}

//x / y 좌표 다를때 쓸 y 오름차순
int sortRule2(const Cafe &x ,const Cafe &y)
{
	return x.Ypos> y.Ypos;
}

int main()
{
	clock_t begin , end;
	begin = clock();

	ifstream inStream;
	int testCases;
	int numOfCafe;
	int cafePointNum;
	int cafePoint;
	inStream.open("input.txt");
	inStream>>testCases;

	for(int i=0; i<testCases; i++)
	{
		inStream>>numOfCafe;
		Cafe cafePos[MAX]={0,};

		for(int i=1 ; i<=numOfCafe ; i++)
			inStream>>cafePos[i].Xpos>>cafePos[i].Ypos;
		cafePos[numOfCafe+1].Xpos=100001; cafePos[numOfCafe+1].Ypos=100001;

		sort(cafePos+1, cafePos+numOfCafe+1 , sortRule);
		// 모든 카페 위치 입력
		
		//x , y 좌표 전부 다를때 reverse
		for(int i=1; i<=numOfCafe; i++)
		{
			int sameX=i;
			
			for(int j= i+1;j<=numOfCafe+1; j++)
			{
				if(cafePos[i].Xpos==cafePos[j].Xpos)
					sameX=j;
				else
					break;
			}

			if( cafePos[i-1].Ypos != cafePos[i].Ypos)
				sort(cafePos + i, cafePos+sameX +1 , sortRule2);
			i= sameX;
			
		} 

		//출력부
		inStream>>cafePointNum;
		for(int i=0; i<cafePointNum; i++)
		{
			inStream>>cafePoint;
			cout<<cafePos[cafePoint].Xpos<<" "<<cafePos[cafePoint].Ypos<<endl;
		}
		
	}
	return 0;
}
