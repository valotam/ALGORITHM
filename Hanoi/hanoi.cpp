#include <stdio.h>

int Cnt;

void hanoi(int n, int a, int b) {
  int temp;

  if (n == 1) {
    printf("Move plate #%d from %d to %d.\n", n, a, b);
  } else {
    temp = 6 - a - b;
    hanoi(n - 1, a, temp);
    printf("Move plate #%d from %d to %d.\n", n, a, b);
    hanoi(n - 1, temp, b);
  }

  Cnt++;
}

int main(int argc, char const *argv[]) {
  int n;
  printf("Set the number of plates.");
  scanf("%d", &n);

  hanoi(n, 1, 2);
  printf("Total movements: %d\n", Cnt);

  return 0;
}
