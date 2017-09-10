#include <stdio.h>
#define LIMIT 50


int main() {

  int age;

  printf("Hello, please enter your age!\n");
  scanf("%d", &age);

  if (age >= LIMIT) {
    printf("Your age is %d\n", age);
    printf("You are OLD!\n");
  }

  else if (age == LIMIT) {
    printf("Your age is %d\n", age);
    printf("You are in the golden middle\n");
  }

  else {
    printf("Your age is %d\n", age);
    printf("You are YOUNG!\n");
  }

  return 0;
}
