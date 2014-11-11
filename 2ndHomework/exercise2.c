#include<stdio.h>
#include<stdlib.h>
#include<math.h>


typedef struct {
  float x;
  float y;
  float z;
} point;

point pointify(){
  /*
   * The point is given as a return value here. That means, that the point is defined
   * inside the scope of this function and then copied. 
   */
  point p;
  printf("Point 1:\n");
  scanf("%f %f %f",&p.x,&p.y,&p.z);
  return p;
}

void pointify2(point *p) {
    /*
     * The point has already been defined in the main function. Only the addres is passed 
     * to this function. The point is manipulated in place and does not get copied at all.
     */
    printf("Point 2:\n");
    scanf("%f %f %f",&(p->x),&(p->y),&(p->z));
}

float dist(point p, point q) {
  float d;
  d=sqrt((p.x-q.x)*(p.x-q.x)+(p.y-q.y)*(p.y-q.y)+(p.z-q.z)*(p.z-q.z));
  return d;
}

int main (int argc, char *argv) {
  int n=3,i;
  float distance;
  
  point a;
  point b;
  
  a=pointify();
  
  pointify2(&b);
  
  distance=dist(a,b);
  printf("Distance between the points is %f.\n",distance);
   
  
  return 0;
}