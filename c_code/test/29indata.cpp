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
		Node *point = NULL; //�� ī���� ��ǥ�� ������ �ִ� ��� �迭
		inStream >> numOfCaffe;
		point = new Node[numOfCaffe];
		for (int i = 0; i < numOfCaffe; i++) {
			Node node;
			inStream >> xPos >> yPos;
			node.x = xPos, node.y = yPos; //ī���� ��ǥ�� ����
			point[i] = node;
		}

		qsort(point, numOfCaffe, sizeof(Node), CompareX); //��ǥ �迭�� x�� �������� ����

		for (int i = 0; i < numOfCaffe - 1; i++) {
			if (point[i].x != point[i + 1].x && point[i].y != point[i + 1].y) { //���� x��ǥ, y��ǥ�� ��� �ٸ��� ���� ���������ӷ� ����� ���� ã�ƾ���
				for (int j = i + 1; j < numOfCaffe; j++) {
					if (point[i].y == point[j].y) { //�̾��� ���� ã�� ��ġ�� �ٲ����ν� ����
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
		for (int i = 0; i < caffeNum; i++) { //ī���� ��ȣ�� �´� ��ǥ ���
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