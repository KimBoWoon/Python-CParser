#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

vector<int> cafe[100001];
vector<pair<int, int> > order;

int main(void){
    FILE *fp = fopen("input.txt", "r");
    
    int T;
    fscanf(fp, "%d", &T);
    
    while(T--){
        int numCafe;
        fscanf(fp, "%d", &numCafe);
        
        order.clear();
        for(int i=0; i<100001; ++i)
            cafe[i].clear();
        
        int x, y;
        for(int i=0; i<numCafe; ++i)
            fscanf(fp, "%d %d", &x, &y), cafe[x].push_back(y);
        
        int preY = 0;
        for(int i=0; i<100001; ++i){
            if(cafe[i].empty())
                continue;
            
            sort(cafe[i].begin(), cafe[i].end());
            
            if(preY == cafe[i].front())
                preY = cafe[i].back();
            else if(preY == cafe[i].back())
                preY = cafe[i].front(), reverse(cafe[i].begin(), cafe[i].end());
            
            for(int j=0; j<cafe[i].size(); ++j)
                order.push_back(make_pair(i, cafe[i][j]));
        }
        
        int numQ, q;
        fscanf(fp, "%d", &numQ);
        
        for(int i=0; i<numQ; ++i)
            fscanf(fp, "%d", &q), printf("%d %d\n", order[q-1].first, order[q-1].second);
    }
}