/*
	Algorithm HW 3
	MonotoneWalkway
	Kookmin University
	Computer Science
	20123408
	Jang Myeong Gyu
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>

using namespace std;

class coordi {

public :

	coordi() {
		x = 0;
		y = 0;
	}

	void setX(int pX) {
		x = pX;
	}

	void setY(int pY) {
		y = pY;
	}

	int x;
	int y;
};

bool comp(coordi p1, coordi p2) {
	if(p1.x != p2.x)
		return p1.x < p2.x;
	else
		return p1.y < p2.y;
}

bool comp2(coordi p1, coordi p2) {
	return p1.y > p2.y;
}

int main(void) {

	ifstream inStream;
	int numTestCases;

	inStream.open("input.txt");
	if(inStream.fail())
	{
		cerr << "input file opening failed.\n";
		exit(1);
	}

	inStream >> numTestCases;

	int cafe;

	for(int i = 0; i < numTestCases; i++) {

		inStream >> cafe;

		coordi coordi[100000];

		for(int j = 0; j < cafe; j++) {

			inStream >> coordi[j].x >> coordi[j].y;

		}

		sort(coordi, coordi + cafe, comp);

		for(int j = 0; j < cafe;) {

			int end = j;

			for(int k = j + 1; k < cafe; k++) {

				if(coordi[j].x == coordi[k].x)
					end = k;
				else
					break;
			
			}

			if(j != end) {

				if(coordi[j - 1].y != coordi[j].y)
					sort(coordi + j, coordi + end + 1, comp2);

				j = end + 1;

			}
			else
				j++;
		}

		int testCafe;
		int cafeNum;

		inStream >> testCafe;

		for(int j = 0; j < testCafe; j++) {

			inStream >> cafeNum;

			cout << coordi[cafeNum - 1].x << " " << coordi[cafeNum - 1].y << endl;

		}
		
		for(int j = 0; j < cafe; j++) {
			coordi[j].setX(0);
			coordi[j].setY(0);
		}
	}

	return 0;

}