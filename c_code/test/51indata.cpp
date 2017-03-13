#include <iostream>
#include <stdlib.h>
#include <fstream>

#define MAX_SIZE 100000

class cCafePoint{

	friend int CompareXPoint(const void *a, const void *b);
	friend int CompareYUp(const void *a, const void *b);
	friend int CompareYDown(const void *a, const void *b);

	private:
		int iCafeXPoint;
		int iCafeYPoint;
		
	public:
		int getXPoint(){	return iCafeXPoint;		}
		void setXPoint(int _iXPoint){	iCafeXPoint = _iXPoint;		}

		int getYPoint(){	return iCafeYPoint; 	}
		void setYPoint(int _iYPoint){	iCafeYPoint = _iYPoint;		}
};

int CompareXPoint(const void *a, const void *b){

	const cCafePoint* op1 = (const cCafePoint *)a;
	const cCafePoint* op2 = (const cCafePoint *)b;

	if(op1 -> iCafeXPoint < op2 -> iCafeXPoint)		return -1;
	if(op1 -> iCafeXPoint == op2 -> iCafeXPoint)	return 0;
	if(op1 -> iCafeXPoint > op2 -> iCafeXPoint)		return 1;
}

int CompareYUp(const void *a, const void *b){

	const cCafePoint* op1 = (const cCafePoint *)a;
	const cCafePoint* op2 = (const cCafePoint *)b;

	if(op1 -> iCafeYPoint < op2 -> iCafeYPoint)		return -1;
	if(op1 -> iCafeYPoint == op2 -> iCafeYPoint)	return 0;
	if(op1 -> iCafeYPoint > op2 -> iCafeYPoint)		return 1;
}

int CompareYDown(const void *a, const void *b){

	const cCafePoint* op1 = (const cCafePoint *)a;
	const cCafePoint* op2 = (const cCafePoint *)b;

	if(op1 -> iCafeYPoint > op2 -> iCafeYPoint)		return -1;
	if(op1 -> iCafeYPoint == op2 -> iCafeYPoint)	return 0;
	if(op1 -> iCafeYPoint < op2 -> iCafeYPoint)		return 1;
}

int main(){

	int iNumberOfCase;
	int iNumberOfCafe;
	int iNumberOfOutput;
	int iCafeNumber;
	int iXPoint,iYPoint;
	int iMaxYPoint;
	int iCounter;
	int iCursor;

	std::ifstream fsInputFile;
	fsInputFile.open("input.txt");
	
	fsInputFile >> iNumberOfCase;
		
	while(iNumberOfCase > 0){
		
		fsInputFile >> iNumberOfCafe;
		cCafePoint RoadMap[MAX_SIZE];

		for(int i = 0; i < iNumberOfCafe; ++i){

			fsInputFile >> iXPoint >> iYPoint;

			RoadMap[i].setXPoint(iXPoint);
			RoadMap[i].setYPoint(iYPoint);
		}

		// sorting cafe list with x point
		qsort(RoadMap,iNumberOfCafe,sizeof(cCafePoint),CompareXPoint);

		// sorting sorted cafe list with y distance
		iCounter = 0;
		iCursor = 0;
		iMaxYPoint = 0;

		for(int iter = 0; iter < iNumberOfCafe; ++iter){
			if(iter + 1 < iNumberOfCafe && RoadMap[iter].getXPoint() == RoadMap[iter + 1].getXPoint()){ 
				iMaxYPoint = iMaxYPoint > RoadMap[iter].getYPoint() ? iMaxYPoint : RoadMap[iter].getYPoint();
				++iCounter;
			}
			else{
				iMaxYPoint = iMaxYPoint > RoadMap[iter].getYPoint() ? iMaxYPoint : RoadMap[iter].getYPoint();
				if(RoadMap[iCursor - 1].getYPoint() < iMaxYPoint)
					qsort(&RoadMap[iCursor],(iCounter + 1),sizeof(cCafePoint),CompareYUp);
				else
					qsort(&RoadMap[iCursor],(iCounter + 1),sizeof(cCafePoint),CompareYDown);
				iMaxYPoint = RoadMap[iter].getYPoint();
				iCursor += (iCounter + 1);
				iCounter = 0;
			}

		}

		// print output

		fsInputFile >> iNumberOfOutput;

		for(int i = 0; i < iNumberOfOutput; ++i){
			fsInputFile >> iCafeNumber;
			std::cout << RoadMap[iCafeNumber - 1].getXPoint() << " " << RoadMap[iCafeNumber -1].getYPoint() << std::endl;
		}

		--iNumberOfCase;
	}

	fsInputFile.close();
	return 0;
}
