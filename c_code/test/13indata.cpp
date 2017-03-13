#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

struct Point{
	int x;
	int y;
};


bool LessX(const Point &left, const Point &right){
	return left.x < right.x;
}



bool LessY(const Point &left, const Point &right){
	return left.y < right.y;
}

bool GreaterY(const Point &left, const Point &right){
	return left.y > right.y;
}



void DecideOrderOfStore(vector<Point> &store){
	int cnt = 0;

	//looking for starting point, (0, 0)
	for(int i = 0; i < store.size(); i++){
		if(store[i].x == 0){
			cnt++;
		}else{
			if(cnt == 1){
				break;
			}else{
				if(store[0].y != 0){
					if(store[0].y > 0)	sort(store.begin(), store.begin()+cnt, LessY);
					else	sort(store.begin(), store.begin()+cnt, GreaterY);
				}else{
					if(store[1].y > 0)	sort(store.begin(), store.begin()+cnt, LessY);
					else	sort(store.begin(), store.begin()+cnt, GreaterY);
				}
				break;
			}
		}
	}

	//decide order
	int y = 0;
	int x = 0;
	cnt = 0;

	for(int i=0; i < store.size(); i++){
		if(store[i].x == x){
			cnt++;
			if(i == store.size() - 1){
				for(int j=1; j<=cnt; j++){
					if(store[i-j].y > y){
						sort(store.begin() + i - cnt +1, store.end(), LessY);
						break;
					}else if(store[i-j].y < y){
						sort(store.begin() + i - cnt +1, store.end(), GreaterY);
						break;
					}
				}
			}

		}else{
			if(x != 0 && cnt > 1){
				for(int j=1; j<=cnt; j++){
					if(store[i-j].y > y){
						sort(store.begin() + i - cnt, store.begin() + i, LessY);
						break;
					}else if(store[i-j].y < y){
						sort(store.begin() + i - cnt, store.begin() + i, GreaterY);
						break;
					}
				}
			}
			y = store[i-1].y;	// 이전의 y
			x = store[i].x;
			cnt = 1;
		}
	}
}

int main(void){
	int numOfCase;
	ifstream fin;

	fin.open("input.txt");
	fin >> numOfCase;

	while(numOfCase--){
		int numOfStore;
		int numOfTestStore;
		int storeNumber[10];
		Point store;
		vector<Point> storeVector;
		vector<Point>::iterator iter;

		fin >> numOfStore;

		while(numOfStore--){
			fin >> store.x >> store.y;
			storeVector.push_back(store);
		}

		sort(storeVector.begin(), storeVector.end(), LessX);

		DecideOrderOfStore(storeVector);

		// for(iter = storeVector.begin(); iter != storeVector.end(); iter++){
		// 	cout << iter->x << " " << iter->y << endl;
		// }

		fin >> numOfTestStore;
		int temp=0;
		for(int i=0; i<numOfTestStore; i++){
			fin >> temp;
			cout << storeVector[temp-1].x << " " << storeVector[temp-1].y << endl;
		}

	}

	return 0;
}
