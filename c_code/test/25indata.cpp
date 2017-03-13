#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>

using namespace std;

class pos{
public:
    int x,y,o;
};

int sort_asce(const pos a,const pos b){
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}

int sort_desc(const pos a,const pos b){
    return a.o < b.o;
}

int main()
{
	ifstream inStream;
	int numTestCase;

	inStream.open("input.txt");
	inStream >> numTestCase;

	pos cafePos[100002];

	while (numTestCase--) {
		int cafeNum;
		int count,num;
		inStream >> cafeNum;
		for(int i = 1 ; i <=cafeNum ; i++){
            inStream >> cafePos[i].x >> cafePos[i].y;
		}
		sort(cafePos+1,cafePos+cafeNum+1,sort_asce);
        int last_y = 0, o = 1;
		for(int i=1;i<=cafeNum;i++){
            int t=i;
            for(int j=i+1;j<=cafeNum;++j){
                if(cafePos[i].x == cafePos[j].x)
                    t=j;
                else
                    break;
            }
            if(cafePos[i].y<last_y && last_y < cafePos[t].y ) for(;;);
            else if(cafePos[i].y >= last_y){
                for(int j=i;j<=t;j++) cafePos[j].o = o++;
                last_y = cafePos[t].y;
            }
            else{
                for(int j=t;j>=i;j--) cafePos[j].o = o++;
                last_y = cafePos[i].y;
            }
            i=t;
		}
		sort(cafePos+1,cafePos+cafeNum+1,sort_desc);
		inStream >> count;
		while(count--){
            inStream >> num;
            cout<<cafePos[num].x<<' '<<cafePos[num].y<<endl;
		}
	}
	inStream.close();
	return 0;
}

