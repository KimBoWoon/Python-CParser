#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#define MAX 100002

using namespace std;

struct Node{
    int x, y;
};

Node cafe[MAX]; 
Node Copy[MAX];

int ascendingX(const Node &a, const Node &b)
{
    return a.x < b.x;
}

int ascendingY(const Node &a, const Node &b)
{
    return a.y < b.y;
}

int descendingY(const Node &a, const Node &b)
{
	return a.y > b.y;
}

int main(void)
{
   ifstream inStream;
   inStream.open("input.txt");

   int testCases = 0;
   int count = 0;
   int numberOfCafe = 0;

   inStream >> testCases;

   while (testCases--)
   {
   	memset(cafe, -1, sizeof(cafe));
   	memset(Copy, -1, sizeof(Copy));

      inStream >> count;
      for (int i = 0; i<count; i++)	//카페의 총 수 만큼 좌표값 노드에 저장 
      {
         inStream >> cafe[i].x >> cafe[i].y;
      }   
      sort(cafe, cafe+count, ascendingX);		//x 값으로 정렬 후 저장 

      int previousY = 0;
      for(int i=0; i<count; i++)
      {
      	int end = i+1;		//바로 다음 인덱	
      	int k=0;
      	int start = i;
      	int cnt = 0;
      	while(cafe[i].x == cafe[end].x)		//x의 값이 같다면 몇개나 같은지 
      	{
      		i++;
      		end = i+1;
      		k++;
      	}

      	if(k != 0)		//i번째 x의 값과 i+1 x의 값이 같을 때 
      	{
      		for(int j=0; j<k+1; j++)
      		{
      			Copy[j].x = cafe[start+j].x;
      			Copy[j].y = cafe[start+j].y;
      		}

      		for(int j=0; j<k+1; j++)
      		{
      			if(start == 0)
      			{
      				if(0 < Copy[j].y)
      					cnt++;
      				else if(0 > Copy[j].y)
      					cnt--;	
      			}
      			else
      			{
      				if(cafe[start-1].y < Copy[j].y)			//내림차순을 위해
      					cnt++;
      				else if(cafe[start-1].y > Copy[j].y)	//오름차순을 위해 
      					cnt--;
      			}
      		}
      		if(cnt<=0)
      			sort(Copy, Copy+k+1, descendingY);		//내림차순
      		else 
      			sort(Copy, Copy+k+1, ascendingY);		//오름차순

      		for(int j=0; j<k+1; j++)
      		{
      			cafe[start+j].x = Copy[j].x;
      			cafe[start+j].y = Copy[j].y;
      		}
      	}
      }

      inStream >> numberOfCafe;
      for (int j = 0; j<numberOfCafe; j++)	//숫자와 카페번호가 같은 것들의 좌표를 출력
      {
         int number = 0;
         inStream >> number;
         cout<<cafe[number-1].x<<" "<<cafe[number-1].y<<endl;
      }
   }

   return 0;
}