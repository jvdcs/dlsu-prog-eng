#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main() {
  char text[100] = "";
  char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  char out[100] = "";
  int shift = 0;
  
  printf("enter text: ");
  scanf("%99s", text);
  printf("enter shift: ");
  scanf("%d", &shift);

  for (int i = 0; i <= strlen(text); i++) {
    char current = text[i];  
  }
}
