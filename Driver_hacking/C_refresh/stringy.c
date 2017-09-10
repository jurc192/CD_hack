#include <stdio.h>
#include <string.h>

int main()
{
  char stringy[30];
  int i;
  char c;
  printf("Type a string .\n");
  fgets(stringy, 30, stdin);
  printf("\n");

  for(i = 0; i < strlen(stringy); i++)
    printf("%c", stringy[i]);
  printf("\n");
  for(i = strlen(stringy); i >= 0; i--)
    printf("%c", stringy[i]);
  printf("\n");

  return 0;
}
