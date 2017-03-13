#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;


struct Point
{
    int x, y;

    bool operator<(const Point &p) const {
    	if (x < p.x) return true;
    	if (x > p.x) return false;
    	if (y < p.y) return true;
    	return false;
	}	
};

int testCases;
int numOfPoint, numOfResult;

int main()
{
	ifstream inStream;
	inStream.open("input.txt");

	if(inStream.fail())
	{
		cout << "input file opening failed. \n";
		exit(1);
	}

	inStream >> testCases;

	for(int i=0;i<testCases;i++){

		inStream >> numOfPoint;

		vector<Point> points;
		Point tempPoint;

		tempPoint.x = -1; tempPoint.y = 0;  // 시작을 (0,0) 맞춰주기위한 좌표
		points.push_back(tempPoint);

		for(int j=0;j<numOfPoint;j++){

			inStream >> tempPoint.x >> tempPoint.y; 
			points.push_back(tempPoint);
		}

		sort(points.begin(), points.end()); // x,y 좌표 오름차순 정렬 

		int l = 0, r = 0, c = 1;

		int cnt = 0, p = 0, q = 0;

		while(p < numOfPoint)
		{
			cnt = 0;
			q = p + 1;

			if(points[p].x != points[q].x){
				for(int k=1;;k++){
					if(q+k > numOfPoint){
						cnt = k;
						break;
					}
					if(points[q].x != points[q+k].x){	
						cnt = k;
						break;
					}
				}
				if(points[p].y != points[q].y)
					reverse(points.begin() + q, points.begin() + q + cnt);
				p += cnt;
			}
			else p++;
		}
	
		inStream >> numOfResult;

		for(int j=0;j<numOfResult;j++){
			int result;
			inStream >> result;

			cout << points[result].x << " " << points[result].y << endl;
		}
	}
}










