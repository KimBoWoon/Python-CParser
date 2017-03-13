/**************************************************/
/*    국민대학교 전자정보통신대학                 */
/*    컴퓨터공학부 20143052 남궁은                */
/**************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

struct cafe_spot {
	int x, y;
};

int compare_x(const void *a, const void *b) {
	cafe_spot *cafe1 = (cafe_spot *)a;
	cafe_spot *cafe2 = (cafe_spot *)b;

	if (cafe1->x == cafe2->x)
		return cafe1->y - cafe2->y;
	return cafe1->x - cafe2->x;
}

int compare_y(const void *a, const void *b) {
	return (*(cafe_spot *)b).y - (*(cafe_spot *)a).y;
}

int main(int argc, char * argv[]) {
	ifstream file;
	file.open("input.txt");

	if (file.fail()) {
		cout << "Input file opening failed." << endl;
		exit(1);
	}

	int test_case;
	file >> test_case;
	do {
		int cafe_num;
		file >> cafe_num;

		cafe_spot *cafe_arr = new cafe_spot[cafe_num];
		for (int i = 0; i < cafe_num; i++) {
			int x, y;
			file >> x >> y;
			cafe_arr[i].x = x;
			cafe_arr[i].y = y;
		}
		qsort(cafe_arr, cafe_num, sizeof(cafe_spot), compare_x);

		for (int pre = 0, j = 1, i = 0; j != cafe_num; i++, j++) {
			int same_count = 0;
			int start_spot, cur, next;
			cur = cafe_arr[i].x;
			next = cafe_arr[j].x;
			if (cur == next) {
				if (i != 0)
					pre = cafe_arr[i - 1].y;

				for (start_spot = i; j != cafe_num; i++, j++) {
					if (cafe_arr[i].x == cafe_arr[j].x)
						same_count++;
					else
						break;
				}
				
				if(pre != cafe_arr[start_spot].y)
					qsort(cafe_arr + start_spot, same_count+1, sizeof(cafe_spot), compare_y);
				same_count = 0;
				i--;
				j--;
			}
		}

		int print_cafe_num;
		file >> print_cafe_num;
		do {
			int cafe_name;
			file >> cafe_name;

			cout << cafe_arr[cafe_name - 1].x << ' ' << cafe_arr[cafe_name - 1].y << endl;
		} while (--print_cafe_num);
		free(cafe_arr);

	} while (--test_case);

	return 0;
}