#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class MyMono
{
private:
	int x;
	int y;

public:
	MyMono(int x = -1, int y = -1) :x(x), y(y) {};

	void setValue(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}

	void swapPoint(MyMono &p)
	{
		MyMono temp;
		temp.x = this->x;
		temp.y = this->y;

		this->x = p.x;
		this->y = p.y;

		p.x = temp.x;
		p.y = temp.y;
	}

	int getDistance(MyMono &temp)
	{
		return (temp.x - this->x)*(temp.x - this->x) + (temp.y - this->y)*(temp.y - this->y);
	}


	void printPoint()
	{
		cout << x << " " << y << " " << endl;
	}

};

void quick_sortX(MyMono *point, int left, int right)
{
	int i, j;
	int temp;
	int pivot = point[left].getX();
	if (left < right)
	{
		i = left;
		j = right + 1; //do while문경우 --연산먼저하므로 index를 1초과한값으로 시작
		while (i <= j)
		{
			do
				i++;
			while (point[i].getX() < pivot); //내림차순을 원할경우 <를 >로
			do
				j--;
			while (point[j].getX() > pivot); //내림차순을 원할경우 >를 <로
			if (i < j) // 엇갈리지않으면 두 요소를 스왑
			{
				point[j].swapPoint(point[i]);
			}
			else //찾은 두소요가 겹치거나 엇갈리면 한바퀴 끝
				break;
		}
		// j위치 요소를 기준이 되었던 pivot 과 Swap
		point[j].swapPoint(point[left]);
		//Swap ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		quick_sortX(point, left, j - 1); // 가운데가 된 pivot을 중심으로 왼쪽 영역 재귀
		quick_sortX(point, j + 1, right);// 가운데가 된 pivot을 중심으로 오른쪽 영역 재귀
	}
}
void quick_sortY1(MyMono *point, int left, int right)
{
	int i, j;
	int temp;
	int pivot = point[left].getY();
	if (left < right)
	{
		i = left;
		j = right + 1; //do while문경우 --연산먼저하므로 index를 1초과한값으로 시작
		while (i <= j)
		{
			do
				i++;
			while (
				point[i].getY() < pivot); //내림차순을 원할경우 <를 >로
			do
				j--;
			while (point[j].getY() > pivot); //내림차순을 원할경우 >를 <로
			if (i < j) // 엇갈리지않으면 두 요소를 스왑
			{
				point[j].swapPoint(point[i]);
			}
			else //찾은 두소요가 겹치거나 엇갈리면 한바퀴 끝
				break;
		}
		// j위치 요소를 기준이 되었던 pivot 과 Swap
		point[j].swapPoint(point[left]);
		//Swap ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		quick_sortY1(point, left, j - 1); // 가운데가 된 pivot을 중심으로 왼쪽 영역 재귀
		quick_sortY1(point, j + 1, right);// 가운데가 된 pivot을 중심으로 오른쪽 영역 재귀
	}
}

void quick_sortY2(MyMono *point, int left, int right)
{
	int i, j;
	int temp;
	int pivot = point[left].getY();
	if (left < right)
	{
		i = left;
		j = right + 1; //do while문경우 --연산먼저하므로 index를 1초과한값으로 시작
		while (i <= j)
		{
			do
				i++;
			while (point[i].getY() > pivot);
			do
				j--;
			while (point[j].getY() < pivot);
			if (i < j) // 엇갈리지않으면 두 요소를 스왑
			{
				point[j].swapPoint(point[i]);
			}
			else //찾은 두소요가 겹치거나 엇갈리면 한바퀴 끝
				break;
		}
		// j위치 요소를 기준이 되었던 pivot 과 Swap
		point[j].swapPoint(point[left]);
		//Swap ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		quick_sortY2(point, left, j - 1); // 가운데가 된 pivot을 중심으로 왼쪽 영역 재귀
		quick_sortY2(point, j + 1, right);// 가운데가 된 pivot을 중심으로 오른쪽 영역 재귀
	}
}

int main()
{
	ifstream inStream;
	int numTestCases;
	int numCafe;
	int x, y;
	int findNumCafe;
	int findPoint;

	inStream.open("input.txt"); //파일을 불러옵니다.
	if (inStream.fail())
	{
		cerr << "파일을 불러오지 못했습니다.\n";
		exit(1);
	}

	inStream >> numTestCases; //테스트케이스 수


	for (int i = 0; i < numTestCases; i++)
	{
		inStream >> numCafe;
		MyMono * point = new MyMono[numCafe+1];

		for (int j = 0; j < numCafe; j++)
		{
			inStream >> x >> y;
			point[j].setValue(x, y);
			if (x == 0 && y == 0)
			{
				point[j].swapPoint(point[0]); //원점 설정
			}
		}
		quick_sortX(point, 1, numCafe - 1); //x축에대해 내림차순으로 정렬
		
		int start = 0;
		int count = 0;
		bool upDown = false;

		for (int j = 1; j <= numCafe; j++)
		{
			if (point[j].getX() == point[j-1].getX())
			{
				if(count == 0)
				start = j-1;

				count++;
				if (point[start - 1].getY() < point[j-1].getY() || point[start - 1].getY() < point[j].getY()) upDown = true;
				else if (point[start - 1].getY() > point[j - 1].getY() || point[start - 1].getY() > point[j].getY()) 	upDown = false;
			}
				
			else
			{
				if (upDown == true && count>0)
				{
					quick_sortY1(point, start, count+start);
				} 
				else if (upDown == false && count > 0)
				{
					quick_sortY2(point, start, count+start);
				}
					
				
				count = 0;
			}
			
		}

		inStream >> findNumCafe;

		for (int k = 0; k < findNumCafe; k++)
		{
			inStream >> findPoint;

			point[findPoint - 1].printPoint();
		}

	}//numTestCases중괄호


	inStream.close();//파일을종료합니다.
	return 0;
} //메인함수 중괄호