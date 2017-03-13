#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

class Cafe {
public:
	int x;
	int y;
};

void swap(int *a, int *b);
bool ascX(class Cafe a, class Cafe b);// x축 오름차순 정렬함수
bool ascY(class Cafe a, class Cafe b); // x축 오름차순 정렬함수
bool decY(class Cafe a, class Cafe b); // y축 내림차순 정렬함수

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt를 열 수 없습니다." << endl;
		return -1;
	}
	int testCases;
	instream >> testCases;
	for (int cases = 0; cases < testCases; cases++) {
		int num;
		instream >> num;
		Cafe *cafe = new Cafe[num]; // num만큼 cafe객체 동적할당
		for (int initialization = 0; initialization < num; initialization++) { // num만큼 초기화
			cafe[initialization].x = 0;
			cafe[initialization].y = 0;
		}
		for (int i = 0; i < num; i++) 
			instream >> cafe[i].x >> cafe[i].y;
		if (cafe[0].x != 0 || cafe[0].y != 0) { // 첫 시작이 0,0이 아니라면
			for (int i = 1; i < num; i++) { // 0,0을 찾아서 맨 앞으로 뽑아준다
				if (cafe[i].x == 0 && cafe[i].y == 0) {
					swap(cafe[0].x, cafe[i].x);
					swap(cafe[0].y, cafe[i].y);
				}
			}
		}
		sort(cafe+1, cafe + num, ascX); // x 오름차순 정렬
		int cnt = 1;
		if (cafe[1].x == 0) { // 0,0 이외에 0이 존재한다면
			for (int i = 2; i < num; i++) {
				if (cafe[i].x != 0) // 0이 아닌 값이 나오면
					break; // 찾기중단
				cnt++;
			}
			if (cafe[1].y < 0)  // -이므로 내려가는 그래프 즉 내림차순 
				sort(cafe + 1, cafe + cnt + 1, decY); // 내림차순 정렬
			else // 올라가는 그래프 즉 오름차순
				sort(cafe + 1, cafe + cnt + 1, ascY); // 오름차순 정렬
		}
		// 여기까지 시작점 0,0 && x 오름차순 정렬 완료 && x=0 일때 y 정렬 완료
		// 이제부터 0 초과의 y정렬을 해야한다
		for (int i = cnt; i < num; i++) {
			int store = i;
			int count = 1;
			if (cafe[i].x == cafe[i + 1].x) { // 중복되는 x값이 있으면
				for (int j = i + 1; j < num; j++) {
					if (cafe[j].x != cafe[store].x) // 다른값이 나오면
						break; // 찾기중단
					count++;
					i++;
				}
				for (int j = store + 1; j < num; j++) { // 애초에 전 y축과 같은것 이라면 스왑할 필요가 없음
					if (cafe[j].y == cafe[store - 1].y) { // 전 y축과 같은 것을 찾는다
						swap(cafe[j].y, cafe[store].y);
						break;
					}
				}
				// 여기까지 다른숫자 첫번째에 배치 완료
				if (cafe[store].y < cafe[store + 1].y) // 올라가는 그래프라면
					sort(cafe + store, cafe + count + store, ascY); // 오름차순 정렬
				else // 내려가는 그래프라면
					sort(cafe + store, cafe + count + store, decY); // 내림차순 정렬
			}
		}
		//for (int i = 0; i < num; i++)
			//cout << cafe[i].x << " " << cafe[i].y << endl;

		int m; // 구해야할 갯수 m
		instream >> m;
		for (int k = 0; k < m; k++) {
			int n; // 카페의 번호 n
			instream >> n;
			cout << cafe[n - 1].x << " " << cafe[n - 1].y; // -1 해주는 이유는 번호는 1번부터시작하고 배열은 0번부터 시작하므로
			cout << endl;
		}
	}
	return 0;
}

void swap(int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

bool ascX(class Cafe a, class Cafe b) {
	return a.x < b.x;
}
bool ascY(class Cafe a, class Cafe b) {
	return a.y < b.y;
}
bool decY(class Cafe a, class Cafe b) {
	return a.y > b.y;
}