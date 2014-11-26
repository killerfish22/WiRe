#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int n;
double* A;
double x;
double P = 0.0;

void Naive()
{
  printf("Using naive Formula:\n");
  for(int i = 0; i <= n; i++)
  {
    P += A[i]*pow((double) x,i);
    //each step has i + 1 floating point operation 
    //(i-1 in the power, 1 for multily with the coefficient and 1 to sum up).
  }
}

void Horner()
{
  printf("Using Horner-Scheme:\n");
  P = A[n];
  for(int i = n - 1; i >= 0; i--)
  {
    P = P * x + A[i];
    //each step has 2 floating point operation
  }
}

int main(int argc, const char* argv[]) 
{
  scanf("%i",&n);
  A = (double*) malloc (sizeof(double) * (n+1));

  for(int i = 0; i <= n; i++)
  {
    scanf("%lf",&A[i]);
  }
  scanf("%lf", &x);
  
  if(argc > 1)
    Horner();
  else
    Naive();
  
  printf("%lf\n", P);
  
  return 0;
}

//OUTPUT for c.)
//6 -998 -998 -998 -998 -998 -998 1 999
//Using Horner-Scheme:
//1.000000
//Using naive Formula:
//0.000000