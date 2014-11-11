#include<stdio.h>
#include<stdlib.h>

int main (int argc, char *argv) {
  
  //input array and lenght
  int *A;
  int n;
  
  //current index
  int i;
  
  //start and end index of the sum with the current max value
  int left=0;
  int right=0;
  
  //start index of the max sum, ending at the current position
  int left2=0;
  
  //value of the sums
  int maxSum=0;
  int maxSum2=0;
  
  //scan data
  scanf("%i\n",&n);
  A=malloc(n*sizeof(int));
  for(i=0;i<n;i++) {
    scanf("%i\n",&A[i]);
  }
  
  
  for(i=0;i<n;i++) 
  {
    if (maxSum2+A[i]<0) 
    {
      //begin new summation at i+1
      maxSum2=0;
      left2=i+1;
    }
    else 
    {
      maxSum2=maxSum2+A[i];
    }
    
    if (maxSum2>maxSum) 
    {
      //update current max sum
      maxSum=maxSum2;
      left=left2;
      right=i;
    }
  }
  printf("left=%i, right=%i, sum=%i\n",left,right,maxSum);
  
  free(A);
  return 0;
}