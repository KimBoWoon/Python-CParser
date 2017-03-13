//
//  main.cpp
//  algo3
//
//  20113313 이창현 2016. 8. 31..
//  Monotone
//

#include <stdio.h>
#include <stdlib.h>

typedef struct point{
    int x;
    int y;
}point;

int partition_x(point a[], int lower, int upper, int mode);
int partition_y(point a[], int lower, int upper, int mode);
void quicks(point a[], int lower, int upper, int type, int mode);
int compareVAL_x_i( const void *arg1 , const void * arg2);
int compareVAL_y_i( const void *arg1 , const void * arg2);
int compareVAL_y_d( const void *arg1 , const void * arg2);


int main(int argc, const char * argv[]) {
    int test_num;
    FILE *file = fopen("input.txt", "r");
    fscanf(file, "%d", &test_num);
    int z, i;
    
    for(z=0;z<test_num;z++){
        point* cafe_spot;
        int max_x = 0;
        int cafe_num, print_index;
        int visit_num, position_y;
        int ynum[100000] = {0,};
        int print_num = 0;
        
        fscanf(file, "%d", &cafe_num);
        cafe_spot = (point*)malloc(sizeof(point)*cafe_num);
        for(i=0;i<cafe_num;i++){
            fscanf(file, "%d %d", &cafe_spot[i].x, &cafe_spot[i].y);
            if(max_x<cafe_spot[i].x) max_x = cafe_spot[i].x;
            ynum[cafe_spot[i].x]++;
        }
        qsort(cafe_spot, cafe_num, sizeof(point), compareVAL_x_i);
    
        position_y = 0;
        visit_num = 0;
        for(i=0;i<=max_x;i++){
            if(ynum[i] == 0)
                continue;
            else if(ynum[i]==1){
                visit_num++;
                continue;
            }
            if(position_y < cafe_spot[visit_num].y || position_y < cafe_spot[visit_num+1].y)
                qsort(cafe_spot+visit_num, ynum[i], sizeof(point), compareVAL_y_i);
            else
                qsort(cafe_spot+visit_num, ynum[i], sizeof(point), compareVAL_y_d);
            visit_num += ynum[i];
            position_y = cafe_spot[visit_num-1].y;
        }
        
        fscanf(file, "%d", &print_num);
        for(i=0;i<print_num;i++){
            fscanf(file, "%d", &print_index);
            printf("%d %d\n", cafe_spot[print_index-1].x, cafe_spot[print_index-1].y);
        }
    }
    return 0;
}

int compareVAL_x_i( const void *arg1 , const void * arg2){
    float v1 , v2;
    v1 = ((point *)arg1)->x;
    v2 = ((point *)arg2)->x;
    
    if(v1 < v2) return -1;
    else if(v1 == v2) return 0;
    else return 1;
}

int compareVAL_y_i( const void *arg1 , const void * arg2){
    float v1 , v2;
    v1 = ((point *)arg1)->y;
    v2 = ((point *)arg2)->y;
    
    if(v1 < v2) return -1;
    else if(v1 == v2) return 0;
    else return 1;
}

int compareVAL_y_d( const void *arg1 , const void * arg2){
    float v1 , v2;
    v1 = ((point *)arg1)->y;
    v2 = ((point *)arg2)->y;
    
    if(v1 > v2) return -1;
    else if(v1 == v2) return 0;
    else return 1;
}