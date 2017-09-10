#include <stdio.h>

int factorial(int number) {

  if (number <= 1) {
    return 1;
  }

  return number * factorial(number-1);
}

int main() {

int x;

printf("Vnesite željeno število za faktorski produkt:\n");
scanf("%d", &x);

printf("Rezultat je: %d\n", factorial(x));

}
