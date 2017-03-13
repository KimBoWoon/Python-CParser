#include <cstdio>
#include <iostream>
#include <algorithm>

#define MAX 100001

using namespace std;

class Position
{ 
    int x,y;
  public:
    Position(){}
    Position(const Position &p){this->x=p.x; this->y=p.y; }
    int getX(){ return x;}
    int getY(){ return y;}
    void setX(int x){ this->x=x;}
    void setY(int y){ this->y=y;}
    friend bool cmp(Position a,Position b);
    friend void swap(Position& a,Position& b);
    ~Position(){}
};

bool cmp(Position a,Position b) { 
  
  if(a.x!=b.x)
    return a.x<b.x; 
  else{

    if(a.x==0)
    {
      if(a.y==0) return true;
      if(b.y==0) return false;
      
      else{ 
              if(a.y<0)
                return a.y>b.y;
              else
                return a.y<b.y;
        }
    }

    return a.y<b.y; 

  }
}

void swap(Position& a,Position& b)
{
  Position c(a);
  a.x=b.x;
  a.y=b.y;
  b.x=c.x;
  b.y=c.y;
  
}


int main(int argc, char** argv) {

  freopen("input.txt", "r", stdin);

  setbuf(stdout, NULL);

  int T;
  int test_case;
    
  scanf("%d", &T);  
  
  for(test_case = 1; test_case <= T; ++test_case) {

    int cafe_num;
    scanf("%d", &cafe_num);
    
    int same_x[MAX];  // x좌표가 같은 카페들의 갯수 
    Position *cafe=new Position[cafe_num];

    for(int i=0; i<MAX; i++) same_x[i]=0;

    for(int i=0; i<cafe_num; i++)
    {
      int x,y;
      scanf("%d %d", &x,&y);
      cafe[i].setX(x);
      cafe[i].setY(y);      
      same_x[x]++;
    }

    sort(cafe,cafe+cafe_num,cmp);


    int same0=same_x[0];

    for(int i=same0; i<cafe_num-1; i++)
    {
      int pre_x=cafe[i-1].getX();
      int x=cafe[i].getX();
      int next_x=cafe[i+1].getX();

      if(pre_x!=x && next_x==x) // 이전과 다름 그리고 다음거랑 같음
      {
        int pre_y=cafe[i-1].getY();
        int y=cafe[i].getY();
        int sameNum=same_x[x];
        if(pre_y!=y)
        {
         // printf("@@@%d번째: %d %d\n",i+1,cafe[i].getX(),cafe[i].getY());
          for(int j=0; j<sameNum/2; j++)
            swap(cafe[i+j],cafe[i+sameNum-1-j]);

        }
        i+=sameNum-1;

      }
       
    }

    int test;
    scanf("%d", &test);

    for(int i=0; i<test; i++)
      { int num; scanf("%d", &num);  printf("%d %d\n",cafe[num-1].getX(),cafe[num-1].getY());}

    delete[] cafe;

  }

  return 0; // 정상종료 시 반드시 0을 리턴해야 합니다.
}

