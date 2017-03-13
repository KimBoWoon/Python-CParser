
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
void swap(int i, int j, int a[][2]) {
   int temp = a[i][0];
   a[i][0] = a[j][0];
   a[j][0] = temp;

   temp = a[i][1];
   a[i][1] = a[j][1];
   a[j][1] = temp;
}
void swapY(int i, int j, int a[][2]) {
   //When the value of x and y is equal to how to sorting?
   int temp = a[i][1];
   a[i][1] = a[j][1];
   a[j][1] = temp;
}
void quicksortX(int arr[][2], int left, int right) {
   int min = (left + right) / 2;
   //   cout << "QS:" << left << "," << right << "\n";
   int i = left;
   int j = right;
   int pivot = arr[min][0];
   //First , based on the x-axis sorting
   while (left<j || i<right)
   {
      while (arr[i][0]<pivot)
         i++;
      while (arr[j][0]>pivot)
         j--;
      if (i <= j) {
         swap(i, j, arr);
         i++;
         j--;
      }
      else {
         if (left<j)
            quicksortX(arr, left, j);
         if (i<right)
            quicksortX(arr, i, right);
         return;
      }
   }
}
void quicksortY(int arr[][2], int left, int right) {
   int min = (left + right) / 2;
   //   cout << "QS:" << left << "," << right << "\n";
   int i = left;
   int j = right;
   int pivot = arr[min][1];
   //First , based on the x-axis sorting
   while (left<j || i<right)
   {
      while (arr[i][1]<pivot)
         i++;
      while (arr[j][1]>pivot)
         j--;
      if (i <= j) {
         swapY(i, j, arr);
         i++;
         j--;
      }
      else {
         if (left<j)
            quicksortY(arr, left, j);
         if (i<right)
            quicksortY(arr, i, right);
         return;
      }
   }
}
void quicksortInverseY(int arr[][2], int left, int right) {
   int min = (left + right) / 2;
   //   cout << "QS:" << left << "," << right << "\n";
   int i = left;
   int j = right;
   int pivot = arr[min][1];
   //First , based on the x-axis sorting
   while (left<j || i<right)
   {
      while (arr[i][1]>pivot)
         i++;
      while (arr[j][1]<pivot)
         j--;
      if (i <= j) {
         swapY(i, j, arr);
         i++;
         j--;
      }
      else {
         if (left<j)
            quicksortInverseY(arr, left, j);
         if (i<right)
            quicksortInverseY(arr, i, right);
         return;
      }
   }
}
int main() {
   fstream in;
   in.open("input.txt");
   int T;
   //   cin >> T;
   in >> T;
   for (int i = 0; i < T; i++) {
      int n, k, num;
      int cnt = 0;
      //      cin >> n;
      in >> n;
      int arr[100001][2];
      //max x,y
      for (int i = 0; i < 100001; i++) {
         arr[i][0] = 1000001;
         arr[i][1] = 1000001;
      }
      for (int j = 1; j <= n; j++) {
         //x, y
         //         cin >> arr[j][0] >> arr[j][1];
         in >> arr[j][0] >> arr[j][1];
      }
      //sorting
      quicksortX(arr, 1, n);
      for (int j = 1; j <= n; j++) {
         while (arr[j][0] == arr[j + cnt + 1][0]) {
            cnt++;
         }
         // Once sorted (ascending direction setting) in the y value
         quicksortY(arr, j, j + cnt);
         //0 when x is a bit more special
         if (arr[j][0] == 0) {
            if (arr[j][1] < 0) {
               quicksortInverseY(arr, j, j + cnt);
            }
         }
         // Select direction
         else if (abs(arr[j - 1][1]- arr[j][1])>abs(arr[j-1][1]-arr[j+cnt][1])) {
            // Descending
            quicksortInverseY(arr, j, j + cnt);
         }
         j += cnt;
         cnt = 0;
      }
      in >> k;
      for (int j = 1; j <= k; j++) {
         in >> num;
         cout << arr[num][0] << " " << arr[num][1] << endl;
      }
   }
   return 0;
}