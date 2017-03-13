#include <cstdio>
#include <algorithm>
using namespace std;
#define MAX 100002
 

struct Node{
    int x, y;
}node[MAX];
 

int compare(const Node &a, const Node &b){
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}
 

int compare2(const Node &a, const Node &b) {
    return a.y > b.y;
}
 
int main()
{
    FILE *inFile;
    inFile = fopen("input.txt", "r");
    int testCase, n, m;
 
    for (fscanf(inFile, "%d", &testCase); testCase--; )
    {
        fscanf(inFile, "%d", &n);
 
        for (int i=0; i<n; ++i)
            fscanf(inFile, "%d%d", &node[i].x, &node[i].y);
 
        // x 기준 오름차순 정렬
        sort(node, node+n, compare);
 
        for (int i=0; i<n; )
        {
            
            int t=i;
 
            
            for (int j=i+1; j<n; ++j)
            {
                if(node[i].x == node[j].x)
                    t=j;
                else
                    break;
            }
 
           
            if (i != t) {
                if (node[i-1].y != node[i].y)
                    sort(node + i, node + t+1, compare2);
                i = t+1;
            }
            else
                ++i;
        }
 
        for (fscanf(inFile, "%d", &m); m--;)
        {
            int k;
            fscanf(inFile, "%d", &k);
            printf("%d %d\n", node[k-1].x, node[k-1].y);
        }
    }
 
    fclose(inFile);

    return 0;
}
