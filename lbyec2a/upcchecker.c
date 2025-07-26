#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
  char input[100] = "";
  int result = 0;  
  int modulus = 0;
  
  printf("input barcode upc (nodash): ");
  scanf("%99s", input);  
  printf("modulus: ");
  scanf("%d", &modulus);  

  for (int i = 0; i <= strlen(input) - 1; i++) {
    int digit = input[i] - '0';

    if (i % 2 == 0) {
      result += digit * 3;
    } else {
      result += digit;
    }
  }

  bool isValid = result % modulus == 0;
  printf("\nresult: %d", result);
  printf("\nis valid upc?: %s", isValid == 1 ? "true" : "false");

  return 0;
}
