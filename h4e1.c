#include <stdlib.h>
#include <stdio.h>
#include <fenv.h>

// int fegetround (void);
typedef union {
  long long i64;
  double d64;
} dbl_64;

// double machine_eps (double value)
// {
//     dbl_64 s;
//     s.d64 = value;
//     s.i64=s.i64++;
//     return s.d64 - value;
// }

int main(int argc, const char* argv[]) 
{
//   double x=1;  
//   double eps=machine_eps(1);
//   printf("%e\n",machine_eps(1));
  switch (atoi(argv[1]))
  {
    case 1:
      printf("Using FE_UPWARD\n");
      fesetround(FE_UPWARD);
      break;
    case 2:
      printf("Using FE_DOWNWARD\n");
      fesetround(FE_DOWNWARD);
      break;
    case 3:
      printf("Using FE_TOWARDZERO\n");
      fesetround(FE_TOWARDZERO);
      break;
    default:
      //printf("Using FE_UPWARD\n");
      //fesetround(FE_UPWARD);
      break;
  }    

  dbl_64 x;
  x.d64=1.0;
  double a=x.d64;
  double diva=1/a;
  
  while (a*diva==1 && x.d64<2)
  {
    a=x.d64;
    diva=1/a;
    x.i64++;
    printf("%.16e\n",x.d64);
  }

//   double x=2;
//   double divx=1/x;
//   while (x*divx==1 && x>1)
//   {
//     x=1+(x-1)/2;
//     divx=1.0/x;
//     printf("%16.16e\n",x);
//   }
    
  
  printf("x=%f\n",x.d64);
//   printf("x=%f\n",x);



return 0;
}

