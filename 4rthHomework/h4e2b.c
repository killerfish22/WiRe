#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void reg1(double y)
{
    printf("y0 = %.16f\n",y);
    
    int i;
  for (i=1;i<=30;i++)
  {
    y=-10*y+(double)(1.0/i);
    printf("y%i = %.16f\n",i,y);
  }
}

void reg2(double y)
{
  int i;
  printf("y30 = %.16f\n",y);
  for (i=29;i>=0;i--)
  {
    y=(y-1/((double)i+1)/(-10));
    printf("y%i = %16e\n",i,y);
  }
}
  

int main(int argc, const char* argv[]) 
{
  int i;
  reg1(log(1.1));
  printf("\n\n");
  reg2(0);
  return 0;
}

/*Output:
 * scuser@vm-sc:~/GIT-WiRe/WiRe$ ./h4e2b 
y0 = 0.0953101798043249
y1 = 0.0468982019567507
y2 = 0.0310179804324935
y3 = 0.0231535290083985
y4 = 0.0184647099160153
y5 = 0.0153529008398472
y6 = 0.0131376582681947
y7 = 0.0114805601751960
y8 = 0.0101943982480401
y9 = 0.0091671286307100
y10 = 0.0083287136929002
y11 = 0.0076219539800890
y12 = 0.0071137935324434
y13 = 0.0057851415986427
y14 = 0.0135771554421447
y15 = -0.0691048877547808
y16 = 0.7535488775478080
y17 = -7.4766652460663154
y18 = 74.8222080162187098
y19 = -748.1694485832397277
y20 = 7481.7444858323970038
y21 = -74817.3972392763535026
y22 = 748174.0178473090054467
y23 = -7481740.1349948290735483
y24 = 74817401.3916149586439133
y25 = -748174013.8761495351791382
y26 = 7481740138.7999572753906250
y27 = -74817401387.9625396728515625
y28 = 748174013879.6611328125000000
y29 = -7481740138796.5771484375000000
y30 = 74817401387965.8125000000000000


y30 = 0.0000000000000000
y29 =     3.333333e-03
y28 =     6.781609e-03
y27 =     1.035304e-02
y26 =     1.405674e-02
y25 =     1.790290e-02
y24 =     2.190290e-02
y23 =     2.606956e-02
y22 =     3.041739e-02
y21 =     3.496284e-02
y20 =     3.972475e-02
y19 =     4.472475e-02
y18 =     4.998791e-02
y17 =     5.554346e-02
y16 =     6.142581e-02
y15 =     6.767581e-02
y14 =     7.434248e-02
y13 =     8.148534e-02
y12 =     8.917765e-02
y11 =     9.751098e-02
y10 =     1.066019e-01
y9 =     1.166019e-01
y8 =     1.277130e-01
y7 =     1.402130e-01
y6 =     1.544987e-01
y5 =     1.711654e-01
y4 =     1.911654e-01
y3 =     2.161654e-01
y2 =     2.494987e-01
y1 =     2.994987e-01
y0 =     3.994987e-01


At first the computed y_n are close to the real values. However due to error propagation the error gets larger and larger
until the computed values have nothing in common with actual results. This algorithm for computing yn for given data n is not stable. 
You can see this by looking at the reucursion formula, which increases the error by the factor 10 in every step. Since y0 is irrational
the initial data error cannot be prevented.

A non-stable algorithm cannot be numerically backward-stable.
*/
