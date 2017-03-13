/*
Date: 16.09.01
Author: Seongmin Jeong
Goal: Monotone Walkway
*/

#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

typedef struct
{
	int xPos, yPos;
}Point;

std::istream& operator>>(std::ifstream& is, Point& pos)
{
	is >> pos.xPos >> pos.yPos;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Point& pos)
{
	os << pos.xPos << " " << pos.yPos;
	return os;
}

bool CmpXYPosAsc(const Point a, const Point b)
{
	if (a.xPos < b.xPos)
		return true;
	if (a.xPos > b.xPos)
		return false;
	
	return a.yPos < b.yPos;
}

int IterSameXPos(const std::vector<Point> totalPath, int initIter, int valueXPos)
{
	for (int iCafePath = initIter; iCafePath != totalPath.size()-1; iCafePath++)
	{
		if (totalPath.at(iCafePath).xPos != totalPath.at(iCafePath + 1).xPos)
			return iCafePath;
	}
	return initIter;
}

int main()
{
	std::ifstream inFile("input.txt");
	int testCases;

	inFile >> testCases;

	while (testCases--)
	{
		int iNumberOfCafe;
		std::vector<Point> totalCafePath;

		inFile >> iNumberOfCafe;

		Point cafeLocation;
		for (int inputPath = 0; inputPath < iNumberOfCafe; inputPath++) // 카페의 총 좌표 입력
		{
			inFile >> cafeLocation;

			totalCafePath.push_back(cafeLocation);
		}

		std::sort(totalCafePath.begin(), totalCafePath.end(), CmpXYPosAsc); // X좌표에 대해서 sorting

		int preYPos = 0; // 이전 자취에서의 y값, 이걸 알아야 y포지션의 소팅 방법을 알 수 있음
		for (int iCafePath = 1; iCafePath < iNumberOfCafe; iCafePath++) // YPos sorting
		{
			Point curPos = totalCafePath[iCafePath - 1];
			Point nextPos = totalCafePath[iCafePath];
			

			if (curPos.xPos == nextPos.xPos) // 현재 카페와 다음 카페의 x값이 같다면
			{
				int iCafePathEnd = iCafePath;
				int maxY = curPos.yPos;

				while (true) // 어디까지 같은지 알아내보자
				{
					int tmpCurX = totalCafePath[iCafePathEnd - 1].xPos;
					int tmpNextX = totalCafePath[iCafePathEnd].xPos;

					if (tmpCurX != tmpNextX) // 다르면 그만 찾자
						break;

					if (maxY < totalCafePath[iCafePathEnd].yPos) // x좌표가 같은 놈들중에서 MAX y값 찾자
						maxY = totalCafePath[iCafePathEnd].yPos;

					iCafePathEnd++;
					if (iCafePathEnd == iNumberOfCafe)
						break;
				}

				if (preYPos == maxY) // 같다면 내림차순으로 하자
					std::reverse(totalCafePath.begin() + iCafePath-1, totalCafePath.begin() + iCafePathEnd);
				
				iCafePath = iCafePathEnd - 1;
			}
			preYPos = totalCafePath[iCafePath-1].yPos;
		}

		/*for (std::vector<Point>::iterator i = totalCafePath.begin(); i != totalCafePath.end(); i++)
			std::cout << *i << std::endl;*/

		inFile >> iNumberOfCafe;
		for (int i = 0; i < iNumberOfCafe; i++)
		{
			int cafeNumber;
			inFile >> cafeNumber;

			std::cout << totalCafePath.at(cafeNumber-1) << std::endl;
		}

	}

	inFile.close();
	return 0;
}