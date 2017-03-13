#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

class Point{
private :
    int x, y;
public :
    bool isEntrance(){
        return x == 0 && y == 0;
    }
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
    friend ofstream & operator<<(ofstream & foutStream, const Point & p);
    friend ifstream & operator>>(ifstream & finStream, Point & p);
    friend bool compareByXAscending(const Point & left, const Point & right);
    friend bool compareByYAscending(const Point & left, const Point & right);
    friend bool compareByYDescending(const Point & left, const Point & right);
};

ofstream & operator<<(ofstream & foutStream, const Point & p){
    foutStream << p.x << " " << p.y;
    return foutStream;
}

ifstream & operator>>(ifstream & finStream, Point & p){
    finStream >> p.x >> p.y;
    return finStream;
}

bool compareByXAscending(const Point & left, const Point & right){
    return left.x < right.x;
}

bool compareByYAscending(const Point & left, const Point & right){
    return left.y < right.y;
}

bool compareByYDescending(const Point & left, const Point & right){
    return left.y > right.y;
}

int main()
{
    ifstream fin;
    ofstream fout;
    fin.open("input.txt");
    fout.open("output.txt");
    int test_case;
    fin >> test_case;
    while(test_case--){
        int n;
        int idx;
        fin >> n;
        Point * pointArr = new Point[n];
        for(int i=0;i<n;i++){
            fin >> pointArr[i];
            if(pointArr[i].isEntrance())
                idx = i;
        }
        Point tmp = pointArr[idx];
        pointArr[idx] = pointArr[0];
        pointArr[0] = tmp;
        sort(pointArr+1, pointArr+n, compareByXAscending);
        int minY, maxY, preY;
        minY = maxY = preY = 0;
        int sortStartIdx = 0;
        for(int i=1;i<n;i++){
            if(pointArr[i].getX() == pointArr[i-1].getX()){
                int y = pointArr[i].getY();
                if(y > maxY)
                    maxY = y;
                if(y < minY)
                    minY = y;
            }
            else{
                if(minY == preY){
                    sort(pointArr+sortStartIdx, pointArr+i, compareByYAscending);
                    preY = maxY;
                }
                else{
                    sort(pointArr+sortStartIdx, pointArr+i, compareByYDescending);
                    preY = minY;
                }
                sortStartIdx = i;
                maxY = minY = pointArr[i].getY();
            }
        }
        if(minY == preY)
            sort(pointArr+sortStartIdx, pointArr+n, compareByYAscending);
        else
            sort(pointArr+sortStartIdx, pointArr+n, compareByYDescending);
        int m;
        fin >> m;
        for(int i=0;i<m;i++){
            int cafeNum;
            fin >> cafeNum;
            fout << pointArr[cafeNum-1] << endl;
        }
    }
    return 0;
}
