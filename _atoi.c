#include <stdio.h>

/**
 * This function prints the Fibonacci sequence up to a given number.
 *
 * @param n The number of Fibonacci numbers to print.
 */
void print_fibonacci(int n) {
  int a = 0, b = 1, c;

  for (int i = 0; i < n; i++) {
    c = a + b;
    printf("%d\n", c);
    a = b;
    b = c;
  }
}

int main() {
  int n;

  printf("Enter the number of Fibonacci numbers to print: ");
  scanf("%d", &n);

  print_fibonacci(n);

  return 0;
}
