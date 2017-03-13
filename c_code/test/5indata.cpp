#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct Node {
	int x, y;
}node[100002];

int sorting(const Node &ex, const Node &next) 
{
	return ex.x != next.x ? ex.x < next.x : ex.y < next.y;
}

int inverseSorting(const Node &ex, const Node &next) 
{
	return ex.y > next.y;
}

int main()
{
	ifstream in;
	int testCases, n, m;

	in.open("input.txt");

	in>>testCases;

	while(testCases--) 
	{
		in>>n;
		for(int i=0; i<n; i++)
		{
			int x,y;
			in>>x>>y;
			node[i].x=x;
			node[i].y=y;
		}
		// x sorting
		sort(node,node+n,sorting);

		// y sorting
		for(int i=0; i<n;) 
		{
			int index = i;
			for(int j=i+1;j<n;j++)
			{
				// x가 일치 않는다는 것은 정렬을 inverse
				if(node[i].x == node[j].x)
					index = j;
				else
					break;
			}

			if(i != index) 
			{
				if(node[i-1].y != node[i].y) 
					sort(node+i,node+index+1,inverseSorting); // sort inverse
				
				i = index+1;
			}
			else
				i++;
		}

		in>>m;
		while(m--)
		{
			int k;
			in>>k;
			cout<<node[k-1].x<<" "<<node[k-1].y<<endl;
		}
	} 

	in.close();
	return 0;
}