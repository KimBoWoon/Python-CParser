/*
 국민대학교 컴퓨터공학부
20123405 이주형
MonotoneWalkWay
*/
#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;

int compare(const void* A, const void* B);
int compare2(const void* A, const void* B);
int compare3(const void* A, const void* B);

class Point{
public:
	Point(){ x = 0; y = 0; }
	void printPoint();
	void setXY(int x, int y){ this->x = x; this->y = y; }
	int getX(){ return x; }
	int getY(){ return y; }
private:
	int x;
	int y;
};

int main(){
	ifstream in;
	in.open("input.txt");
	if (!in) return 1;

	int test_case;
	in >> test_case;
	while (test_case--){
		int n;
		in >> n;
		Point *p = new Point[n];
		for (int i = 0; i < n; i++){
			int x, y;
			in >> x >> y;
			p[i].setXY(x, y);
		}

		qsort(p, n, sizeof(Point), compare);
		
		int start = 0, temp = 0;

		for (int i = 0; i < n; i++){
			if (p[i].getX() != temp || i==n-1){
				if (i == n - 1) i++;
				qsort(p + start, i - start, sizeof(Point), compare2);
				if (start > 0 && p[start].getY() != p[start - 1].getY()){
					qsort(p + start, i - start, sizeof(Point), compare3);
				}
				else if (start == 0 && p[start].getY() != 0){
					qsort(p + start, i - start, sizeof(Point), compare3);
				}
				temp = p[i].getX();
				start = i;
			}
		}

		int m;
		in >> m;
		for (int i = 0; i < m; i++){
			int temp;
			in >> temp;
			p[temp - 1].printPoint();
		}
		delete []p;
	}
	in.close();
	return 0;
}
void Point::printPoint(){ cout << x << " " << y << endl; }
int compare(const void* A, const void* B) {
	return (*(Point*)A).getX() - (*(Point*)B).getX();
}
int compare2(const void* A, const void* B) {
	return (*(Point*)A).getY() - (*(Point*)B).getY();
}
int compare3(const void* A, const void* B) {
	return (*(Point*)B).getY() - (*(Point*)A).getY();
}