#include <iostream>
#include <fstream>
#include <cstdlib>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

int Large_Y(pair<int, int> v1, pair<int, int> v2){
	return v2.second < v1.second;
}

int main(){

	ifstream inStream;
	int num_cases;

	inStream.open("input.txt");
	if (inStream.fail()){
		cerr << "Input file opening failed.\n";
		exit(1);
	}

	inStream >> num_cases;

	while(num_cases--){

		int m, x, y, n;
		int pre_Y, max_x, position;
		vector <pair <int, int> > v;
		int num_X[100001][2];

		memset(num_X, 0, sizeof(num_X));
		inStream >> m;   //카페의 수


		for (int i = 0; i < m; i++){
			inStream >> x >> y;  //좌표 입력
			v.push_back(make_pair(x, y));
		}

		sort(v.begin(), v.end());
		max_x = v[m - 1].first;     //가장큰 x좌표

		for (int i = 0; i < m; i++)
			num_X[v[i].first][0]++;

		num_X[max_x + 1][0] = 1;
		num_X[0][1] = 0;

		for (int i = 1; i <= max_x + 1; i++)
			num_X[i][1] = num_X[i - 1][1] + num_X[i - 1][0];

		pre_Y = 0;
		for (int i = 0; i <= max_x; i++){
			if (num_X[i][0] > 1){
				position = num_X[i][1];
				if (v[position].second < pre_Y || v[position + 1].second < pre_Y)
					sort(v.begin() + position, v.begin() + position + num_X[i][0], Large_Y);

				pre_Y = v[num_X[i + 1][1] - 1].second;
			}
		}

		inStream >> n;     //출력할 좌표의 수 입력
		while (n--){
			inStream >> x;
			cout << v[x - 1].first << " " << v[x - 1].second << "\n";
		}
	}

	inStream.close();

	return 0;

}

