#include <iostream>
#include <fstream>

using namespace std;

void swap(int *a, int *b)
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
}
void quickSort(int *arr, int left, int right, int *arrY) // 오름
{
	int i, j;
	int pivot = arr[left];
	if(left < right)
	{
		i = left;
		j = right+1;
		while(i <= j)
		{
			do
			{
				i++;
			} while(arr[i] < pivot);			
			do
			{
				j--;
			} while(arr[j] > pivot);
			if(i < j)
			{
				swap(arr[i], arr[j]);
				swap(arrY[i], arrY[j]);
			}
			else
				break;
		}
		swap(arr[j], arr[left]);
		swap(arrY[j], arrY[left]);

		quickSort(arr, left, j - 1, arrY);
		quickSort(arr,  j + 1, right, arrY);
	}
}
void quickSortR(int *arr, int left, int right, int *arrY) // 내림차순
{
	int i, j;
	int pivot = arr[left];
	if(left < right)
	{
		i = left;
		j = right+1;
		while(i <= j)
		{
			do
			{
				i++;
			} while(arr[i] > pivot);  // 내림
			do
			{
				j--;
			} while(arr[j] < pivot);
			if(i < j)
			{
				swap(arr[i], arr[j]);
				swap(arrY[i], arrY[j]);
			}
			else
				break;
		}
		swap(arr[j], arr[left]);
		swap(arrY[j], arrY[left]);
		quickSortR(arr, left, j - 1, arrY);
		quickSortR(arr,  j + 1, right, arrY);
	}
}

int main()
{
	ifstream instream;
	instream.open("input.txt");
	if(instream.fail())
		cerr << "Error" << endl;
	int numTestCases;
	instream >> numTestCases;
	for(int i = 0; i < numTestCases; i++)
	{
		int numOfCafe;
		instream >> numOfCafe;
		int arrayX[100000] = {0};
		int arrayY[100000] = {0};

		for(int j = 0; j < numOfCafe; j++)
		{
			int x, y;
			instream >> x >> y;
			arrayX[j] = x;
			arrayY[j] = y;
		} // numOfCafe for문 종료 - 배열에 좌표 입력 완료
		quickSort(arrayX, 0, numOfCafe-1, arrayY); // x축기준으로 배열 sort
		//// 배열의 첫번째 (0,0)으로 만들기
		for(int k = 0; k < numOfCafe; k++)
		{
			int tempX, tempY;
			if(arrayX[k] == 0)
			{
				if(arrayY[k] == 0)
				{
					tempX = arrayX[0];
					tempY = arrayY[0];
					arrayX[0] = 0;
					arrayY[0] = 0;
					arrayX[k] = tempX;
					arrayY[k] = tempY;
					break;
				}
			}
		}
		/////////////// (0,0) 만들기 끝
		////// x값 정렬에 따른 y값 정렬하기
		int count = 0;
		int firstIdx = 0;
		for(int k = 0; k < numOfCafe; k++)
		{
			if(arrayX[k] == 0 && arrayY[k] == 0) // 만약에 0, 0 나오면 
				continue;

			if(arrayX[k] == arrayX[k+1]) // 같은 x좌표가 연속으로 나오면
			{
				if(count == 0)
				{
					firstIdx = k;
				}
				count++;
			}
			if((count != 0) && (arrayX[k] == 0) && (k == numOfCafe-2)) // x좌표가 다 0 이고 세로줄
			{
				if(arrayY[firstIdx] > 0) {
					quickSort(arrayY, firstIdx, firstIdx+count, arrayX); }
				else {
					quickSortR(arrayY, firstIdx, firstIdx+count, arrayX); }
				firstIdx = 0;
				count = 0;
				continue;
			}
			if((count != 0) && (arrayX[k] != arrayX[k+1]))
			{
				if(arrayX[firstIdx] == 0) // X좌표 0 연속으로 +
				{
					if(arrayY[firstIdx] > 0) {
						quickSort(arrayY, firstIdx, firstIdx+count, arrayX); }
					else {
						quickSortR(arrayY, firstIdx, firstIdx+count, arrayX); }
				}
				else
				{
					quickSortR(arrayY, firstIdx, firstIdx+count, arrayX); // x값 같은 범위 y값 우선 내림차순으로
					if(arrayY[firstIdx-1] != arrayY[firstIdx])
					{
						quickSort(arrayY, firstIdx, firstIdx+count, arrayX);
					}
				}
				firstIdx = 0;
				count = 0;
			}
		}
		/////// 찾을 카페의 번호 배열에 넣기
		int findNumOfCafe;
		instream >> findNumOfCafe;
		int arrayF[100] = {0};		
		for(int m = 0; m < findNumOfCafe; m++) // 정답출력 for문
		{
			instream >> arrayF[m];
			cout << arrayX[arrayF[m]-1] << " " << arrayY[arrayF[m]-1] << endl;
		}
	} // numTestCases for문 종료
}