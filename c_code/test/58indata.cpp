#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;

typedef struct nodetype {
	int x, y;
}Node;
bool compare(const Node &a, const Node &b) {
	if (a.x > b.x) {
		return 0;
	}
	else if(a.x==b.x) {
		return a.y < b.y;
	}
	else {
		return 1;
	}
}
bool compare1(const Node &a, const Node &b) {
	return a.y > b.y;
}
int main()
{
	int t;
	ifstream input("input.txt");
	input>>t;
	while (t--) {
		int n, i, m;
		int cnt[100001];
		for (i = 0; i < 100001; i++) cnt[i] = 0;
		vector<Node> vec;
		input>>n;
		for (i = 0; i < n; i++) {
			int x, y;
			Node node;
		    input>>x>>y;
			node.x = x;
			node.y = y;
			cnt[x]++;
			vec.push_back(node);
		}
		Node tr = { 100001,0 };
		vec.push_back(tr);
		sort(vec.begin(), vec.end(), compare);
		input>>m;
		if (vec.at(0).x || vec.at(0).y) sort(&vec.at(0), &vec.at(cnt[0]), compare1);
		for (i = 0; i < n - 1; i++) {
			if (cnt[vec.at(i+1).x] == 1) continue;
			if (vec.at(i).x != vec.at(i + 1).x) {
				if (vec.at(i).y!=vec.at(i+1).y) {
					sort(&vec.at(i+1), &vec.at(i+1+ cnt[vec.at(i + 1).x]), compare1);
				}
			}
		}
		while (m--) {
			int k;
			input>>k;
			cout << vec.at(k-1).x << " " << vec.at(k-1).y << endl;
		}
	}
}