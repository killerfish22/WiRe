#include<stdlib.h>
#include<stdio.h>
#include<math.h>

float actualValue;

void int_midpointI(int n,int plusminus) {
  /**
   * This function naively implements the midpoint rule for
   * evaluating integral(e^x,-20,20) and integral(e^(-x),-20,20)
   */
  float a=-20;
  float b=20;
  float h=(b-a)/n;
  float integral=0.0;
  double integral_dbl=0.0;
  int i;
  for(i=0;i<n;i++)
  {
    integral=integral+h*exp(plusminus*(a+i*h+(h/2.0)));
    integral_dbl=integral_dbl+h*exp(plusminus*(a+i*h+(h/2.0)));
  }

  printf("N=%i, Appr. integral single: %f, Appr. integral double: %f.\n",n,integral,integral_dbl);
  printf("Error Single: %f\n",fabs(integral-actualValue));
  printf("Error Double: %f\n",fabs(integral_dbl-actualValue));
}

float int_midpointI_alt(int n,int plusminus,float a, float b) {
  /**This function also compues the integral as above,
   * but uses recursion to split the sum into one part
   * with very large values and one with very small values
   */
  float h=(b-a)/n;
  float integral=0.0;
  double integral_dbl=0.0;
  int i;
  
  if (n==1)
  {
    integral=h*exp(a+h/2.0);
  }
  else
  {
    float c=(a+b)/2;    
    integral+=int_midpointI_alt(n/2.0,plusminus,a,c);
    integral+=int_midpointI_alt(n/2.0,plusminus,c,b);
  }
  return integral;
}


  

int main(int argc, char* argv[]) {
  actualValue=exp(20)-exp(-20);
  printf("Actual Value of Integral: %f\n\n",actualValue);
  
  int i,n;
  n=2048;
  printf("e^x:\n");
  for(i=0;i<5;i++)
  {
    int_midpointI(n,1);
    n=n*2;
  }
  printf("\n");
  n=2048;
  printf("e^(-x):\n");
  for(i=0;i<5;i++)
  {
    int_midpointI(n,-1);
    n=n*2;
  }

  //Alternative recursive Approach:
  printf("~~~~Alternative, Recursive method:~~~~\n");
  float integral;
  printf("e^x:\n");
  n=2048;
  for(i=0;i<5;i++)
  {
    integral=int_midpointI_alt(n,1,-20,20);
    printf("N=%i, Appr. integral: %f Error: %f\n",n,integral,fabs(integral-actualValue));
    n=n*2;
  }
  printf("\n");
  printf("e^(-x):\n");
  n=2048;
  for(i=0;i<5;i++)
  {
    integral=int_midpointI_alt(n,-1,-20,20);
    printf("N=%i, Appr. integral: %f Error: %f\n",n,integral,fabs(integral-actualValue));
    n=n*2;
  }  
  
  n=4000;
  integral=int_midpointI_alt(n,1,-20,20);
  printf("N=%i, Appr. integral: %f Error: %f\n",n,integral,fabs(integral-actualValue));
  return 0;
}