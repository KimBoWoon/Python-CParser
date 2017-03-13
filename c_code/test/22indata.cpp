#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std ;

typedef struct Node{
	int x, y;
}position ;

position T[100005] ;
char Com1( const position &a, const position &b);
char Com2( const position &a, const position &b);

int main()
{
	ifstream stream ;
	stream.open("input.txt") ;
	int no_cases ;
	stream >> no_cases ;

	while (no_cases--)
	{
		int no_position , numof, index ;
		stream >> no_position ;
		for (int i=0; i<no_position; ++i) stream >> T[i].x >> T[i].y ; 
		sort(T, T+no_position, Com1);
		// 일단 x에 대한 오름차순, x값이 같으면 y에대한 오름차순을 진행한다.

		for (int i=0; i<no_position ; )
		{
			int temp=i;
			for (int j=i+1; j<no_position; ++j)
			{
				if(T[i].x == T[j].x) temp=j; // x좌표가 같다면? x좌표가 같을때 현재 i와 가장 멀리있는 y좌표를 선택.
				else break ; // x좌표가 다르다면 break 
			}

			if (i != temp) { // x좌표가 다르다면 일로... 
				if (T[i-1].y != T[i].y)	sort(T + i, T + temp+1, Com2); // y좌표가 다름
				i = temp+1; 
			}
			else
				++i;
		}
		// 출력 부분
		stream >> numof ;
		while (numof--)
		{
			stream >> index ;
			cout << T[index-1].x << " " << T[index-1].y << endl;
		}

	}
	return 0;
}

char Com1( const position &a, const  position &b){

	if( a.x < b.x ) return 1 ;
	else if( a.x > b.x ) return 0 ;
	else
	{
		if(a.y < b.y ) return 1 ;
		else return 0 ;
	}
}

char Com2( const position &a, const position &b) {
	return (a.y > b.y) ;
}
