#include<stdlib.h>
#include<stdio.h>
#include<math.h>

void mantissa(int *t, int t_rest, int* p, int *exp, int *mant)
{
  //function to recursively compute all digit arrangements and print resulting numbers
  int digit=0;
  int i=0;
  int start=0;
  
  if(t_rest>0) 
  {
    start= (t_rest==*t) ? 1 : 0;
  for(digit=start ;digit<*p;digit++)
    {
      //set digits
      mant[*t-t_rest]=digit;
      mantissa(t,t_rest-1,p,exp,mant);
    }
  }
  else
  {
    //when last digit is set compute represented number in decimal form and print
    double number=0.0;
    for(i=0;i<*t;i++)
    {
      number=number+mant[i]*pow(*p,(-i-1)+*exp);
    }
    printf("%f\n",number);
  }
}


int main (int argc,char** argv) 
{
  //Input variables
  int p=atoi(argv[1]);
  int t=atoi(argv[2]);
  int e_min=atoi(argv[3]);
  int e_max=atoi(argv[4]);
  
  //Counter Variables
  int b;
  int i;
  int digit;
  
  //mantissa as int array
  int* mant;   
  mant=calloc(sizeof(int),t);
   
  for(b=e_min;b<=e_max;b++)
  {
    //loop through all possible exponents
    mantissa(&t,t,&p,&b,mant);
  }
  
  free(mant);
  return 0;
}