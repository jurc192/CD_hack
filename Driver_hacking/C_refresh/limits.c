#include <stdio.h>
#include <float.h>
#include <limits.h>

int main() {

  int maxchar = CHAR_MAX;
  int maxint = INT_MAX;
  unsigned long long ullmax = ULLONG_MAX;   // 8byte = 64bit
  long lmax = LONG_MAX;   // 2 * int = 4byte = 32bit
  long double ldmax = LDBL_MAX;

  printf("The max value of char is %d\n", maxchar);
  printf("The max value of int is: %d\n", maxint);
  printf("The max value of usigned long long is: %Lu \n", ullmax);
  printf("The max value of long is: %ld \n", lmax);
  printf("The max value of long double is: %Lf \n", ldmax);

  return 0;
}
