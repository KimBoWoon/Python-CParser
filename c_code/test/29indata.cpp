#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

struct Node {
	int x, y;
};

int CompareX(const void* a, const void* b);

int main(void) {
	ifstream inStream;
	inStream.open("input.txt");

	if (inStream.fail()) {
		cerr << "No Input File" << endl;
		exit(1);
	}
	int numTestCase, numOfCaffe;
	int xPos, yPos;

	inStream >> numTestCase;
	for (int s = 0; s < numTestCase; s++) {
		Node *point = NULL; //각 카페의 좌표를 가지고 있는 노드 배열
		inStream >> numOfCaffe;
		point = new Node[numOfCaffe];
		for (int i = 0; i < numOfCaffe; i++) {
			Node node;
			inStream >> xPos >> yPos;
			node.x = xPos, node.y = yPos; //카페의 좌표를 저장
			point[i] = node;
		}

		qsort(point, numOfCaffe, sizeof(Node), CompareX); //좌표 배열을 x축 기준으로 정렬

		for (int i = 0; i < numOfCaffe - 1; i++) {
			if (point[i].x != point[i + 1].x && point[i].y != point[i + 1].y) { //점의 x좌표, y좌표가 모두 다르면 길이 끊어진것임로 연결된 점을 찾아야함
				for (int j = i + 1; j < numOfCaffe; j++) {
					if (point[i].y == point[j].y) { //이어진 길을 찾고 위치를 바꿈으로써 정렬
						Node temp = point[i + 1];
						point[i + 1] = point[j];
						point[j] = temp;
						break;
					}
					else
						continue;
				}
			}
			else
				continue;
		}

		int caffeNum, position;
		inStream >> caffeNum;
		for (int i = 0; i < caffeNum; i++) { //카페의 번호에 맞는 좌표 출력
			inStream >> position;
			cout << point[position - 1].x << " " << point[position - 1].y << endl;
		}
		delete[] point;
	}

	return 0;
}

int CompareX(const void* a, const void* b) {
	Node tempA = *(Node*)a;
	Node tempB = *(Node*)b;
	if (tempA.x == 0 && tempB.x == 0 && tempA.y <= 0 & tempB.y <= 0) {
		if (tempA.y > tempB.y)
			return -1;
		else
			return 1;
	}
	else {

		if (tempA.x > tempB.x) {
			return 1;
		}
		else if (tempA.x == tempB.x) {
			if (tempA.y > tempB.y)
				return 1;
			else {
				return -1;
			}
		}
		else {
			return -1;
		}
	}
}