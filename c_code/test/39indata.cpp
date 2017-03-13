#include<iostream>
#include<fstream>
#include<cstdlib>
#include<algorithm>
#include<iterator>
using namespace std;
#define Max_num 100000
class Position {
public:
	int xpos;
	int ypos;
};

bool compare(Position const& a, Position const& b) {
	if (a.xpos != b.xpos) return a.xpos < b.xpos;
	if (a.xpos == b.xpos) return a.ypos < b.ypos;
	return a.xpos < b.xpos;
}

int main()
{
	ifstream in_stream;
	int num_cases, cafe_num, m, num2;
	in_stream.open("input.txt");
	if (in_stream.fail())
	{
		cerr << "input file opening failed.\n";
		exit(1);
	}
	in_stream >> num_cases;
	for (int i = 0; i < num_cases; i++)
	{
		in_stream >> cafe_num;
		int pos_X, pos_Y;
		int key = 0;
		Position Pos[Max_num] = { 0, };
		for (int j = 0; j < cafe_num; j++) {
			in_stream >> pos_X >> pos_Y;
			if (pos_X == 0)
				key++;
			Pos[j].xpos = pos_X;
			Pos[j].ypos = pos_Y;
		}
		sort(Pos, Pos + cafe_num, compare);

		if (Pos[0].xpos != 0 || Pos[0].ypos != 0)
			reverse(Pos, Pos + key);

		for (int j = 1; j < cafe_num; j++) {
			int a = j, b = j;
			if (Pos[j - 1].xpos != Pos[j].xpos) {

				for (int k = b; b <= cafe_num; b++) {
					if (Pos[a].xpos != Pos[b].xpos)
						break;
				}
				if (Pos[j - 1].ypos != Pos[a].ypos) {
					reverse(Pos + a, Pos + b);
				}
			}
		}
		in_stream >> m;
		for (int j = 0; j < m; j++) {
			in_stream >> num2;
			cout << Pos[num2 - 1].xpos << " " << Pos[num2 - 1].ypos << endl;
		}
	}
	in_stream.close();
}