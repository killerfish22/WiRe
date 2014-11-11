#include<stdio.h>
#include<stdlib.h>

int main (int argc, char *argv) {
  
  int n=0;
  int i;
  float *A;
  float min,max,avg;
  
  
  printf("Enter number of measurements:\n");
  scanf("%i",&n);
  
  A=malloc(n*sizeof(double));
  
  printf("\nEnter measurements (seperated by spaces):\n");
  for(i=0;i<n;i++) {
    scanf("%f",&A[i]);
  }
  
  min=A[0];
  max=A[0];
  avg=A[0];
 
  for(i=1;i<n;i++) {    
    min= A[i]<min ? A[i] : min;
    max= A[i]>max ? A[i] : max;
    avg=avg+A[i];
  }
  avg=avg/n;
  
  printf("Minimum: %f\n",min);
  printf("Maximum: %f\n",max);
  printf("Average: %f\n",avg);
  
  free(A);
  return 0;
}