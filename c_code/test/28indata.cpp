#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct Cafe {
	int x;
	int y;

};

bool compare(Cafe a, Cafe b){
	return a.x < b.x;
}
bool compareYUp(Cafe a, Cafe b) {
	return a.y < b.y;
}
bool compareYDown(Cafe a, Cafe b) {
	return a.y > b.y;
}

int main() {
	int testCase;
	int numCase;
	int tempX;
	int tempY;
	int prev=0;
	int amountY;
	int toTell;
	int tellList;
	Cafe cafe[100000] = { 0, };
	ifstream inStream("input.txt");

	inStream >> testCase;
	for (int testNum = 0; testNum < testCase; testNum++) {
		inStream >> numCase;
		for (int index = 0; index < numCase; index++) {
			inStream >> tempX;
			inStream >> tempY;

			cafe[index].x = tempX;
			cafe[index].y = tempY;

		}
		sort(cafe, cafe + numCase, compare);
		amountY = 0;

		for (int copiedIndex = 0; cafe[copiedIndex].x ==  0; copiedIndex++) {
			if (copiedIndex == numCase)
				break;
			amountY++;
		}

		sort(cafe , cafe + amountY, compareYUp);

		if (cafe[0].y != 0)
			sort(cafe , cafe + amountY, compareYDown);

		for (int index = 1; index < numCase; index++) {
			if (cafe[index-1].x != cafe[index].x) {
				prev = cafe[index].x;
				amountY = 0;
				for (int copiedIndex = index; cafe[copiedIndex].x == prev; copiedIndex++) {
					amountY++;
				}

				sort(cafe + index, cafe + index + amountY, compareYUp);
				if (cafe[index - 1].y != cafe[index].y)
					sort(cafe + index, cafe + index + amountY, compareYDown);
			}

		}
		inStream >> toTell;
		for (int index = 0; index < toTell; index++) {
			inStream >> tellList;
			cout << cafe[tellList-1].x << " " << cafe[tellList-1].y << endl;
		}
	//	for (int index = 0; index < numCase; index++)
	//		cout << cafe[index].x << "," << cafe[index].y << endl;
	//	cout << "------------------------------" << endl;
	}

	return 0;
}