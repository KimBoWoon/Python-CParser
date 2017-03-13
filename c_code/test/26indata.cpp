#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
const int MAX_X = 111111;
const int INF = 987654321;
vector<int> Y[MAX_X];

int main(){

	ifstream inStream("input.txt");
    int T;
    inStream>>T;
    while (T--){
        int n;
        int m;
        inStream >> n;
        for (int i = 0; i < MAX_X; i++) Y[i].clear();
        vector<pair<int, int> > points;
        vector<int> dir;//down 1, up 2
        for (int i = 0; i < n; i++){
            int x, y;
            inStream>>x>>y;
            Y[x].push_back(y);
        }
        inStream >> m;
         
        for (int i = 0; i < MAX_X; i++) sort(Y[i].begin(), Y[i].end());
        int y = 0;
        for (int i = 0; i < MAX_X; i++){
            if (Y[i].empty()){
                dir.push_back(0);
                continue;
            }
            if (Y[i].front() == Y[i].back()){
                y = Y[i].front();
                dir.push_back(1);
            }
            else if(Y[i].front() == y){
                y = Y[i].back();
                dir.push_back(2);
            }
            else{
                y = Y[i].front();
                dir.push_back(1);
            }
        }
        for (int i = 0; i < MAX_X; i++){
            if (dir[i] == 1){
                for (int j = (int)Y[i].size() - 1; j >= 0; j--){
                    points.push_back(make_pair(i, Y[i][j]));
                }
            }
            else if(dir[i]==2){
                for (int j = 0; j < Y[i].size(); j++){
                    points.push_back(make_pair(i, Y[i][j]));
                }
            }
        }
        for (int i = 0; i < m; i++){
            int t;
            inStream>>t;
            t--;
            cout<<points[t].first<<" "<<points[t].second<<endl;
        }
    }
}