// Monotone Walkway
// 길따라가면서 만나는 카페에 번호 매기기 
// 동 -> 서 앞으로만 단, 좌우로는 갈 수 잇음
// C++ STL Vector를 이용해서 해결 + algorithm으로 sort 및 reverse

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX 100000

// x, y 좌표를 저장할 클래스
class Point {
private:
	int x;
	int y;
public:
	Point() :x(0), y(0) {}
	void insert(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
};

// 사용자정의 클래스를 정렬하기 위한 클래스
class PSort {
public:
	bool operator() (Point p, Point q) {
		return p.getX() < q.getX();
	}
};

class PSort2 {
public:
	bool operator() (Point p, Point q) {
		return p.getY() < q.getY();
	}
};


vector <Point> v;
Point p[MAX];

// 순서에 맞게 정렬하기 위한 함수
void race_sort();

int main() {
	ifstream in;
	in.open("input.txt");

	int T;
	in >> T;

	while (T--) {
		int n;
		in >> n;

		for (int i = 0; i < n; i++) {
			int x; int y;
			in >> x >> y;
			// 미리 생성해둔 Point클래스에 입력받은 x,y좌표를 입력한다
			p[i].insert(x, y);
			// x,y좌표가 입력된 Point클래스를 Vector에 넣어둔다.
			v.push_back(p[i]);
		}

		// Vector에 넣어둔 좌표를 문제에 맞게 정렬한다.
		race_sort();

		// 정렬된 좌표들 중 입력받은 순위에 좌표를 출력한다.
		int t_size;
		int t;
		in >> t_size;
		for (int i = 0; i < t_size; i++) {
			in >> t;
			cout << v[t - 1].getX() << " " << v[t - 1].getY() << endl;
		}

		// clear vector
		v.clear();
	}

	in.close();
	return 0;
}

// 같은 x좌표내에 y좌표가 다른 좌표가 몇개인지 카운트
int count_x(int index, int key) {
	int result = 0;
	while (index < v.size() && v[index].getX() == key ) {
		result++;
		index++;
	}

	return result;
}

void race_sort() {
	// sort vector
	PSort ps;
	sort(v.begin(), v.end(), ps);
	PSort2 ps2;

	// reverse vector
	// reverse(v.begin(), v.end());
	// 특정 위치부터 reverse는 이렇게
	// reverse(v.begin() + 3, v.end());

	int start, end;

	// x좌표가 달라질때 y좌표는 같아야 이동할 수 있으므로
	// y좌표가 달라진 경우 역순으로 정렬하여 이동할 수 있도록 만든다.
	int i = 0;
	while (i < v.size()) {
		start = i;
		end = count_x(i, v[i].getX());
		sort(v.begin() + start, v.begin() + start + end, ps2);
		if (i == 0 && v[i].getY() < 0) {
			reverse(v.begin() + start, v.begin() + start + end);
		}
		if (i != 0 && v[i].getX() != v[i - 1].getX() 
			&& v[i].getY() != v[i - 1].getY()) {
			reverse(v.begin() + start, v.begin() + start + end);
		}
		i += end;
	}
}