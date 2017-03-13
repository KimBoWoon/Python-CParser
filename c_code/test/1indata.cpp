#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(pair<int,int> a, pair<int, int> b); // y축으로 내림차순 정렬을 위한 함수

int main() {

	ifstream in("input.txt");
	if (in.fail()) {
		cout << "file open fail." << endl;
		return 1;
	}

	int numOfData;
	in >> numOfData;

	for (int i = 0; i < numOfData; i++) { // case의 수만큼
		int numOfCoord, numOfCafe;
		int x, y, count;
		int cafeNumber;

		vector<pair<int, int> > coord; // vector의 pair를 이용해 2개의 x, y pair integer 생성

		in >> numOfCoord; // 좌표의 수를 받는다

		for (int j = 0; j < numOfCoord; j++) {
			in >> x >> y;
			coord.push_back(pair<int, int>(x, y)); // 좌표를 받고 초기화
		}

		sort(coord.begin(), coord.end()); // algorith lib의 sort를 이용해 x, y 순서로 오름차순 정렬
		
		if ((coord[0].first != 0) || (coord[0].second != 0)) { // 시작좌표가 (0,0)이 아닐 경우 (0, 음수)가 있다는 말과 같음
			count = 1;
			for (int j = 1; j < numOfCoord - 1; j++) {
				if (coord[j].first != coord[j + 1].first) // 다음 좌표부터 몇번째 까지 같은 x인지 확인함
					break;
				count++;
			}
			sort(coord.begin(), coord.begin() + count + 1, compare); // y 순서로 내림차순 정렬
		}

		for (int j = 1; j < numOfCoord - 1; j++) { // 시작은 (0,0) 2번째부터 탐색
			count = 0;

			// 앞과 뒤 좌표의 x, y 중 같은것이 없다면
			if ((coord[j].first != coord[j + 1].first) && (coord[j].second != coord[j + 1].second)) {
				for (int k = j+1; k < numOfCoord - 1; k++) {
					if (coord[k].first != coord[k + 1].first) // 다음 좌표부터 몇번째 까지 같은 x인지 확인함
						break;
					count++;
				}

				sort(coord.begin() + j + 1, coord.begin() + j + count + 2, compare); // y 순서로 내림차순 정렬

			}
		}

		in >> numOfCafe; 
		for (int j = 0; j < numOfCafe; j++) { // cafe(좌표)의 수만큼
			in >> cafeNumber;
			cout << coord[cafeNumber-1].first << " " << coord[cafeNumber-1].second << endl;
		}
	}
	
	in.close();

	return 0;
}

// y축으로 내림차순 정렬을 위한 함수
bool compare(pair<int, int> a, pair<int, int> b) {
	return a.second > b.second;
}