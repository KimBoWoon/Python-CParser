#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef struct Cafe_
{
	int x;
	int y;
}Cafe;

bool compare_up(const Cafe &a,const Cafe &b);
bool compare_down(const Cafe &a,const Cafe &b);

int main(void){
	FILE* in_file;
	int num_of_cases;
	in_file = fopen("input.txt","r");
	fscanf(in_file, "%d", &num_of_cases );

	while(num_of_cases--){
		int num_of_cafe; 
		int i;
		int num_of_confirm;
		Cafe *cafe_list_1;
		Cafe *cafe_list_2;
		Cafe *cafe_list_current;
		Cafe *cafe_list_result;

		fscanf(in_file, "%d", &num_of_cafe );


		//배열 할당
		cafe_list_1 = (Cafe*)malloc(num_of_cafe * sizeof(Cafe));
		cafe_list_2 = (Cafe*)malloc(num_of_cafe * sizeof(Cafe));

		cafe_list_result = (Cafe*)malloc(num_of_cafe * sizeof(Cafe));

		//cafe_list 초기화
		for(i=0; i<num_of_cafe; i++){
			fscanf(in_file, "%d %d",&cafe_list_1[i].x ,&cafe_list_1[i].y );
			
			cafe_list_2[i].x = cafe_list_1[i].x;
			cafe_list_2[i].y = cafe_list_1[i].y;
		}

		//sorting
		sort(cafe_list_1,cafe_list_1+num_of_cafe,compare_up);
		sort(cafe_list_2,cafe_list_2+num_of_cafe,compare_down);
		
		

		//where is (0,0)
		int route_current;
		if(cafe_list_1[0].x == 0 && cafe_list_1[0].y == 0){
			route_current = 1;
			cafe_list_current = cafe_list_1;
		}
		else{
			route_current = 2;
			cafe_list_current = cafe_list_2;
		}
		
		//go course
		for(i=0; i<num_of_cafe; i++){
			//다음 코스의 x값이 같으면 go

			//init (0,0)
			if(i == 0){
				cafe_list_result[i].x = cafe_list_current[i].x;
				cafe_list_result[i].y = cafe_list_current[i].y;
				//printf("current_course: x: %d, y: %d\n", cafe_list_result[i].x,cafe_list_result[i].y);
			}

			//end
			if(i == num_of_cafe-1)
				break;

			//다음 진행코스가 x또는 y가 같으면 전진(정렬 했으므로 ㄱㅊ)
			else if(cafe_list_result[i].x == cafe_list_current[i+1].x ||
				cafe_list_result[i].y == cafe_list_current[i+1].y){

				cafe_list_result[i+1].x = cafe_list_current[i+1].x;
				cafe_list_result[i+1].y = cafe_list_current[i+1].y;
				//printf("current_course: x: %d, y: %d\n", cafe_list_result[i+1].x,cafe_list_result[i+1].y);
			}

			//x,y 둘다 같은게 없으면 바꿔서 다시함
			else{
				if(route_current == 1){
					route_current = 2;
					cafe_list_current = cafe_list_2;
				}
				else{
					route_current = 1;
					cafe_list_current = cafe_list_1;
				}
				cafe_list_result[i+1].x = cafe_list_current[i+1].x;
				cafe_list_result[i+1].y = cafe_list_current[i+1].y;
				//printf("current_course: x: %d, y: %d\n", cafe_list_result[i+1].x,cafe_list_result[i+1].y);
			}
		}	

		fscanf(in_file,"%d",&num_of_confirm);
		
		//confirm
		for(int i=0; i<num_of_confirm; i++){
			int index;
			fscanf(in_file,"%d",&index);
			printf("%d %d\n", cafe_list_result[index-1].x, cafe_list_result[index-1].y);
		}
		free(cafe_list_1);
		free(cafe_list_2);
		free(cafe_list_result);
	}
	fclose(in_file);
}
bool compare_up(const Cafe &a, const Cafe &b)
{
    if(a.x == b.x)
    	return a.y < b.y;
    else
    	return a.x < b.x;

}

bool compare_down(const Cafe &a, const Cafe &b)
{
    if(a.x == b.x)
    	return a.y > b.y;
    else
    	return a.x < b.x;
}