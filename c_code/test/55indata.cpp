#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;

vector<int> y_coord[100001];
int ans[100001][2];

int main()
{
	ifstream in_stream;
	int T;
	int N;
	int x, y;
	int M;
	int cafe;

	in_stream.open("input.txt");
	if (in_stream.fail()) exit(1);

	in_stream >> T;

	while (T--)
	{
		in_stream >> N;

		for (int i = 0; i < N; i++)
		{
			in_stream >> x >> y;
			y_coord[x].push_back(y);
		}

		int idx = 0, cur_y = 0;
		for (int i = 0; i <= 100000 && idx < N; i++) {
			int size = y_coord[i].size(); if (!size) continue;

			sort(y_coord[i].begin(), y_coord[i].end());
			if (cur_y <= y_coord[i][0]) {
				for (int j = 0; j < size; j++) {
					ans[idx][0] = i; ans[idx][1] = y_coord[i][j]; idx++;
				}
				cur_y = y_coord[i][size - 1];
			}
			else {
				for (int j = size - 1; j >= 0; j--) {
					ans[idx][0] = i; ans[idx][1] = y_coord[i][j]; idx++;
				}
				cur_y = y_coord[i][0];
			}
			y_coord[i].clear();
		}

		in_stream >> M;

		for (int i = 0; i < M; i++)
		{
			in_stream >> cafe;
			cout << ans[cafe - 1][0] << ' ' << ans[cafe - 1][1] << endl;
		}
	}

}