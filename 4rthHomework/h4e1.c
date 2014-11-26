#include <stdlib.h>
#include <stdio.h>
#include <fenv.h>

typedef union {
  long long i64;
  double d64;
} dbl_64;


int main(int argc, const char* argv[]) 
{
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
      printf("Using default\n");
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
  } 
  
  printf("x=%.16e\n",x.d64);
return 0;
}

/**Output:
scuser@vm-sc:~/GIT-WiRe/WiRe$ ./h4e1 0
Using default
x=1.0000000001646365e+00
scuser@vm-sc:~/GIT-WiRe/WiRe$ ./h4e1 1
Using FE_UPWARD
x=1.0000000000000005e+00
scuser@vm-sc:~/GIT-WiRe/WiRe$ ./h4e1 2
Using FE_DOWNWARD
x=1.0000000000000004e+00
scuser@vm-sc:~/GIT-WiRe/WiRe$ ./h4e1 3
Using FE_TOWARDZERO
x=1.0000000000000004e+00

Changing the rounding behaviour leads to a smaller number s.t. x*1/x!=1.
*/

