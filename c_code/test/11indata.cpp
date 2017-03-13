#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <cstdlib>

using namespace std;

int main() {
	ifstream inStream;
	inStream.open("input.txt");
	if (inStream.fail())
		exit(1);

	int T;
	int n;
	inStream >> T;
	while (T--) {
		inStream >> n;
		vector<pair<int, int> > v(n + 1);
		v[0].first = -1;
		v[0].second = 0;
		for (int i = 1; i <= n; i++) 
			inStream>> v[i].first >>v[i].second;
		
		sort(v.begin(), v.end());

		for (int i = 1; i <= n; i++) {
			if (v[i - 1].first != v[i].first) {
				int left, right;
				left = right = i;
				for (; right <= n; right++) {
					if (v[left].first != v[right].first)
						break;
				}

				if (v[i - 1].second != v[i].second)
					reverse(v.begin() + left, v.begin() + right);
			}
		}

		int m, pos;
		inStream >> m;
		for (int i = 0; i < m; i++) {
			inStream >> pos;
			printf("%d %d\n", v[pos].first, v[pos].second);
		}
	}

	inStream.close();
	return 0;
}