#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>

struct Point {
	int x;
	int y;
};

int Cmp_Point_x(Point a, Point b) {

	return a.x < b.x;

}
int Cmp_Point_y_down(Point a, Point b) {

	return a.y < b.y;

}
int Cmp_Point_y_up(Point a, Point b) {
	return a.y > b.y;
}


int main(void) {

	std::ifstream instream;
	instream.open("input.txt");

	int num_testcase;
	int num_of_cafe;

	instream >> num_testcase;

	int num_out_testcase;
	int out_testcase;
	struct Point p[100010];
	int start, end;
	int flag = 1;
	int up_down_flag = 0;
	int temp = 0;

	for (int i = 0; i < num_testcase; i++) {

		instream >> num_of_cafe;
		flag = 1;
		up_down_flag = 0;
		for (int j = 0; j < num_of_cafe; j++) {

			instream >> p[j].x >> p[j].y;
		}//end for
		std::sort(p, p + num_of_cafe, Cmp_Point_x);
		//x좌표로 정렬을 한다.
	
			for (int z = 0; z < num_of_cafe; z++) {
				temp = z ;
				if (p[z].x != 0) {
					temp = z - 1;
					break;
				}
			}
				if (p[0].y > 0) {

					std::sort(p, p + temp+1, Cmp_Point_y_down);

				}
				else if (p[0].y < 0) {
					std::sort(p, p + temp+1, Cmp_Point_y_up);
				}
				else
				{
					if (p[1].y > 0) {
						std::sort(p+1, p + temp + 1, Cmp_Point_y_down);
					}
					else {
						std::sort(p+1, p + temp + 1, Cmp_Point_y_up);
					}

				}

		//y좌표 정렬
		for (int h = 0; h < num_of_cafe; h++) {
			if (flag) {
				if (p[h].x != p[h + 1].x) {
					flag--;
					start = h + 1;

					if (p[h].y > p[h + 1].y) // 현제 y값이 가장 큰값이므로 오름 차순해야함
						up_down_flag++; //오름 차순하는 flag

					else if (p[h].y == p[h + 1].y) { //현제와 다음이 같은대 그 다음것을비교함 
						if (p[h].y > p[h + 2].y)
							up_down_flag++;
					}

				}
			}//end if
			else {
				if (p[h].x != p[h + 1].x) {
					end = h;
					if (up_down_flag) {
						std::sort(p + start, p + end+1, Cmp_Point_y_up); //오름 차순으로
						up_down_flag--;

					}
					else {
						std::sort(p + start, p + end+1, Cmp_Point_y_down); //내림 차순으로
					}
					
					flag++;
					h--;

				}
			}//end else

		}
	/*	std::cout << " ************* 출력 테스트 ****************" << std::endl;
		for (int k = 0; k < num_of_cafe; k++) {
			std::cout << p[k].x << " " << p[k].y << std::endl;
		}

		std::cout << " *********************************************" << std::endl;*/
	instream >> num_out_testcase;
	for (int v = 0; v < num_out_testcase; v++) {
		instream >> out_testcase;
		std::cout << p[out_testcase - 1].x << " " << p[out_testcase - 1].y << std::endl;

		}
	}//end for

	return 0;
} //end main
