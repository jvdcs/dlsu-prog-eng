#include <stdio.h>
int main(int argc, char *argv[]) {
  // GUESS THE NUMBER
  int correctGuess = 66;
  while (1) {
    int guess = 0;
    printf("- [Guessing Game] -\n");
    printf("Im thinking of number from 1 to 100, can you guess it?\n");
    printf("My guess is: ");
    scanf("%d", &guess);
    if (guess != correctGuess) {
      if (guess < correctGuess) {
        printf("\nToo low! Try again.\n\n");
      } else if (guess > correctGuess) {
        printf("\nToo high! Try again.\n\n");
      }
    } else {
      printf("\nCongratulations! You guessed the correct number.\n\n");
      break;
    }
  }
  // COLLATZ CONJECTURE
  int prev = 0, count = 0, cur = 0, input = 0;
  printf("- [Collatz Calculator] -\n");
  printf("Enter a positive integer (0 < x <= 32000): ");
  scanf("%d", &input);
  if (input <= 0 || input > 32000) {
    printf("\nInvalid Input! It must be 0 < x <= 32000!\n");
    return 0;
  }
  printf("\ncount | f(current) = result\n\n");
  cur = input;
  while (cur != 1) {
    prev = cur;
    if (cur % 2 == 0) {
      cur = cur / 2;
    } else {
      cur = (3 * cur) + 1;
    }
    count++;
    printf("%d | f(%d) = %d\n", count, prev, cur);
  }
  printf("\nIt took %d applications of the Collatz Function on the positive "
         "integer %d to reach 1\n",
         count, input);
  // PYRAMID 2.0
  cur = 0;
  input = 0;
  printf("\n- [PYRAMID 2.0] -\n");
  printf("Enter pyramid height: ");
  scanf("%d", &input);
  for (int i = 1; i <= input; i++) {
    for (int j = (input - i); j >= 1; j--) {
      printf(" ");
    }
    for (int j = 1; j <= i; j++) {
      printf("%d ", j);
    }
    printf("\n");
  }
  return 0;
}
