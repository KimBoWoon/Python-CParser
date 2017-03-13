#include <iostream>
#include <fstream>
#include <algorithm>


class PosCafe {
	public:
		int x;
		int y;
};

int compareUp(const PosCafe &a, const PosCafe &b){
	return a.x != b.x ? a.x < b.x : a.y < b.y;
}


int compareYdown(const PosCafe &a, const PosCafe &b){
	return a.y > b.y;
}

int main(){

	std::ifstream inStream;
	int testCases, numDatas, testDatas, num, cafeNum;

	PosCafe cafe[100002];

	inStream.open("input.txt");
	inStream >> testCases;

	for(int i=0; i<testCases; i++){
		inStream >> numDatas;
		int count = 0;
		int start = 0;

		for(int j=0; j<numDatas; j++) // input cafe position data
			inStream >> cafe[j].x >> cafe[j].y;

		// 1. X sort 오름차순
		std::sort(cafe, cafe + numDatas, compareUp);
		// 2. Y 정렬
		for(int j=0; j<numDatas-1; j++){
			
			

			if(cafe[j].x == cafe[j+1].x){
				count++;
				if(j == (numDatas-2)){
					start = j - count + 1;	
					std::sort(cafe + start, cafe + start + count+1, compareYdown);
				}
			}

			else if (count > 0)
			{
				start = j - count;
				if(start > 0){
					if(cafe[start-1].y != cafe[start].y)
					{
						std::sort(cafe + start, cafe + start + count +1, compareYdown);
					}
					count = 0;
				}
				else if(start == 0)
				{
					if(cafe[start].y != 0 ){
						std::sort(cafe, cafe + count+1, compareYdown);
					}
					count = 0;
				}
			}
		}

		/* checker
		for(int j=0; j<numDatas; j++){
			std::cout << "[" << cafe[j].x << "/" << cafe[j].y << "]";
		}
		std::cout << std::endl;
		*/

		// 4. print cafe position

		inStream >> num;
		for(int j=0; j<num; j++){
			inStream >> cafeNum;
			std::cout << cafe[cafeNum-1].x << " " << cafe[cafeNum-1].y << std::endl;
		}

	}

	return 0;
}