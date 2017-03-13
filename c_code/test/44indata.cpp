#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
using namespace std;

typedef struct point
{
public:
    int x, y, z;
    point()
    {
        x=y=z=0;
    }
    point(int a, int b)
    {
        x=a, y=b, z=0;
    }
    
}point;

bool coor1(point a, point b)
{
    return a.x < b.x;
}

bool coor2(point a, point b)
{
    if(a.x==b.x)
    {
        return a.z < b.z;
    }
    else
        return a.x < b.x;
}

int test, num, m;
point walkway[100000];

int main(void)
{
    
    ifstream fin;
    fin.open("input.txt");
    fin >> test;
    
    for(int i=1; i<=test; i++)
    {
        fin >> num;
        walkway[0].x = walkway[0].y=0;
        for(int j=1; j<=num; j++)
        {
            int x, y;
            fin >> x >> y;
            walkway[j] = point(x,y);
        }
        sort(walkway+1, walkway+num+1, coor1);
        
        point before = point(0,0);
        int l=0, MAX=0;
        for(int k=1; k<=num; k++)
        {
            if(walkway[k].x != walkway[k-1].x)
            {
                before.x=walkway[MAX].x;
                before.y=walkway[MAX].y;
                l=MAX;
                MAX=k;
            }
            walkway[k].z=abs(walkway[l].y-walkway[k].y);
            if(walkway[MAX].z < walkway[k].z)
            {
                MAX=k;
            }
        }
        sort(walkway+1, walkway+num+1, coor2);
        
        fin >> m;
        for(int e=1; e<=m; e++)
        {
            int load;
            fin >> load;
            cout << walkway[load].x << " " << walkway[load].y << endl;
        }
    }
}