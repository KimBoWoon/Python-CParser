#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct CORD {
    int x;
    int y;
};

bool compare(const CORD &a, const CORD &b) {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
};

int main() {
    FILE * p;
    p = fopen ("input.txt","r");
    int amountOfCase;
    fscanf(p, "%d", &amountOfCase);
    while(amountOfCase--) {
        int amountOfCafe;
        fscanf(p, "%d", &amountOfCafe);
        vector<struct CORD> cafe;
        int xCord[100010] = {0, };
        int maxX = 0;
        for (int i=0; i<amountOfCafe; i++) {
            int x, y;
            fscanf(p, "%d %d", &x, &y);
            xCord[x] += 1;
            struct CORD temp;
            temp.x = x;
            temp.y = y;
            cafe.push_back(temp);
            if (maxX < x)
                maxX = x;
        }
        sort(cafe.begin(), cafe.end(), compare);
        if (xCord[0] > 1 && cafe[0].y != 0) {
            reverse (cafe.begin(), cafe.begin() + xCord[0]);
        }
        int idx = -1;
        for (int i=1;i <= maxX;i++) {
            idx += xCord[i-1];
            if (idx <= amountOfCafe && cafe[idx+1].x == i && cafe[idx].y != cafe[idx+1].y) {
                if (cafe[idx+1].x == maxX)
                    reverse (cafe.begin()+idx+1, cafe.end());
                else 
                    reverse (cafe.begin()+idx+1, cafe.begin()+idx+xCord[cafe[idx + 1].x]+1);
            }
        }
        int amountOfOutput;
        fscanf(p, "%d", &amountOfOutput);

        while (amountOfOutput--) {
            int outputIdx;
            fscanf(p, "%d", &outputIdx);
            printf("%d %d\n", cafe[outputIdx-1].x, cafe[outputIdx-1].y);
        }
    }
    return 0;
}
