#include <iostream>
#include <fstream>
#include <queue>
#include <stdlib.h>
#include <algorithm>
#define BUCKET 10
using namespace std;
class coordinate;
int cmp(const void *a, const void *b);

class coordinate {

private:
	int XCoordinate;
	int YCoordinate;

public:
	coordinate() {
		this->XCoordinate = 0;
		this->YCoordinate = 0;
	}
	void setCoordinate(int XCoordinate, int YCoordinate) {
		this->XCoordinate = XCoordinate;
		this->YCoordinate = YCoordinate;
	}
	int getXCoordinate() {
		return XCoordinate;
	}
	int getYCoordinate() {
		return YCoordinate;
	}
	void printCoordinate() {
		cout << this->XCoordinate << ' ' << this->YCoordinate << endl;
	}
};

int cmp(const void *a, const void *b) {
	coordinate *ia = (coordinate*)a;
	coordinate *ib = (coordinate*)b;
	if (ia->getXCoordinate() > ib->getXCoordinate()) return 1;
	else if (ia->getXCoordinate() < ib->getXCoordinate()) return -1;
	else {
		if (ia->getYCoordinate() > ib->getYCoordinate()) return 1;
		else
			return -1;
	}
}

int main() {

	ifstream inFile;
	int testCases;
	int numOfCafe;
	int XCoordinate;
	int YCoordinate;
	int testCaseToPrint;
	int cafeNumToPrint;

	inFile.open("input.txt");

	if (inFile.fail())
		return 0;

	inFile >> testCases;

	for (int i = 0; i < testCases; i++) {
		inFile >> numOfCafe;

		coordinate *cafe = new coordinate[numOfCafe];
		for (int j = 0; j < numOfCafe; j++) {
			inFile >> XCoordinate >> YCoordinate;
			cafe[j].setCoordinate(XCoordinate,YCoordinate);
		}

		qsort(cafe, numOfCafe, sizeof(coordinate),cmp);

		int k;
		for (int j = 0; j < numOfCafe; j++) {
			if ((cafe[j].getXCoordinate() == 0) && (cafe[j].getYCoordinate() == 0)) {
				coordinate temp1 = cafe[j];
				for (int k = j-1; k > -1; k--) {
					cafe[k + 1] = cafe[k];
				}
				cafe[0] = temp1;
				break;
			}
		}

		int first = -1;
		int last = -1;
		for (int j = 0; j < numOfCafe - 1; j++) {
			if( ((cafe[j].getXCoordinate() != cafe[j + 1].getXCoordinate() ) && (cafe[j].getYCoordinate() != cafe[j + 1].getYCoordinate())) || 
				(j==numOfCafe-2) ||
				( j==0 && (cafe[j].getYCoordinate() != cafe[j + 1].getYCoordinate())) ) {

				if (first != -1) {
					last = j;
					if (numOfCafe - 2 == j)
						last = numOfCafe - 1;
					if (first != last) {
						for (int k = 0; k < (last - first + 1) / 2; k++) {
							coordinate temp = cafe[first+k];
							cafe[first+k] = cafe[last-k];
							cafe[last - k] = temp;
						}
						first = -1;
						last = -1;
					}
				}
				if(cafe[j].getYCoordinate() != cafe[j+1].getYCoordinate())
					first = j+1;
			}
		}

		inFile >> testCaseToPrint;

		for (int j = 0; j < testCaseToPrint; j++) {
			inFile >> cafeNumToPrint;
			cafe[cafeNumToPrint-1].printCoordinate();
		}
		delete []cafe;
	}
	inFile.close();
	return 0;
}