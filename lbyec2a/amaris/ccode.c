#include <stdio.h>
#include <string.h>

int main() {
  char username[20], password[29];
  int attempt;

  printf("--------------------------");
  printf("\n PLEASE ENTER CREDENTIALS");
  printf("\n--------------------------");

  for (attempt = 1; attempt <= 3; attempt++) {
    printf("\n\nusername:");
    scanf("%s", username);
    printf("\npassword:");
    scanf("%s", password);

    if ((strcmp(username, "MOVIEGOER") == 0) && (strcmp(password, "POPCORN") == 0)) {
      printf("\nLogin Successful!");
    } else {
      printf("\nInvalid Input");
    }
  }

  // ENTER CHOICES OF MOVIE!

  printf("Too many failed attempts. Please try again later.");

  return 0;
}
