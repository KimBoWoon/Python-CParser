#include<cstdio>
#include<algorithm>

using namespace std;

struct Position{
    int x, y;
};

bool assendingX(const Position & a, const Position & b){
    if(a.x < b.x)
        return true;
    else
        return false;
}
bool assendingY(const Position & a, const Position & b){
    if(a.y < b.y)
        return true;
    else
        return false;
}
bool decendingY(const Position & a, const Position & b){
    if(a.y > b.y)
        return true;
    else
        return false;
}

int main(){
    int testCase, countOfCafe, numberOfCafe, tmp;
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d", &testCase);
    for(int t=0;t<testCase;t++){
        scanf("%d", &countOfCafe);
        Position * p = new Position[countOfCafe];
        for(int i=0;i<countOfCafe;i++){
            scanf("%d %d", &p[i].x, &p[i].y);
            if(p[i].x == 0 && p[i].y == 0){
                Position tmp = p[0];
                p[0] = p[i];
                p[i] = tmp;
            }
        }
        sort(p+1,p+countOfCafe,assendingX);
        for(int i = 1; i<countOfCafe;i++){
            if (p[i].y == p[i-1].y) {
                continue;
            }
            else{
                int j=1;
                while(i+j<countOfCafe && p[i].x==p[i+j].x){
                    j++;
                }
                if(p[i-1].y<p[i].y){
                    sort(p+i, p+i+j, assendingY);
                }
                else{
                    sort(p+i, p+i+j, decendingY);
                }
                i+=j-1;
            }
        }
        scanf("%d", &numberOfCafe);
        for(int i=0;i<numberOfCafe;i++){
            scanf("%d", &tmp);
            printf("%d %d\n", p[tmp-1].x, p[tmp-1].y);
        }
        delete[] p;
    }
}