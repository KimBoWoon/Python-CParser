/**********************************************
* Student ID : 20133232
* Student Name : 신연수
* Program  :Monotone Walkway
****************************************************/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;

struct Pair {
	int x, y;
};

int ascend(const Pair &a, const Pair &b) { //x기준으로 오름차순 정렬
	if (a.x != b.x)
		return a.x < b.x;
	else
		return a.y < b.y;
}

int descend(const Pair &a, const Pair &b) { //y 내림차순 정렬
	return a.y > b.y;
}


int main(void) {

	ifstream inStream;
	int T, n, m;


	inStream.open("input.txt");
	if (inStream.fail()) {
		return 1;
	}

	inStream >> T; //numtestcases

	for (int i = 0; i < T; i++) {

		inStream >> n; //카페의 수 
		vector<Pair> p;
		p.push_back({ -1, 0});

		for (int i = 0; i < n; i++) {
			int x, y;
			inStream >> x >> y;
			p.push_back({ x,y }); 
		}
		sort(p.begin(), p.end(), ascend); //x좌표 기준으로 오름차순정렬 

		 //바로 전 좌표와 x,y 모두 같지 않으면 길이 끊어지므로 그다음 x가 바뀌기 전까지 y를 내림차순한다.
		for (int i = 1; i <= n; i++) {
			if (p[i-1].x != p[i].x) { //바로 전 좌표와 x좌표가 다르면  
				int begin, end;//begin~end y를 내림차순 해야할 구간 
				begin = end = i;

				for (end = i; end <= n; end++) {
					if (p[begin].x != p[end].x) break;
				}

				if (p[i - 1].y != p[begin].y)
					sort(p.begin()+begin, p.begin() + end, descend); //y 내림차순 정렬 
			}
		}


		/////출력 
		inStream >> m;
		for (int i = 0; i < m; i++) {
			int cafeNum;
			inStream >> cafeNum;//카페번호 입력
			printf("%d %d\n", p[cafeNum].x, p[cafeNum].y);//카페 좌표 출력
		}
	}

	inStream.close();
	return 0;
}
