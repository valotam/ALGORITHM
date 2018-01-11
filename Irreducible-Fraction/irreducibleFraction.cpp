#include <stdio.h>
#ifndef IRRIDUCIBLE_FRACTION_CONST
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define CASE_MAX 160
#endif


int GCD(int p, int q){
  if (q == 0)
    return p;

  return GCD(q, p % q);

}

int main(int argc, char const *argv[]) {
  int testCases, maxNumber, Solutions;
  int i, j, k;

  freopen(INPUT_FILE, "r", stdin);

  scanf("%d", &testCases);

  for(i = 0; i < testCases; i++){
    Solutions = 0;

    scanf("%d\n", &maxNumber);

    for (j = 0; j < maxNumber; j++) {
      for (k = 0; k < maxNumber; k++) {
        if (j < k && GCD(j, k) == 1) {
          printf("Found irreducible fraction: %d/%d\n", j, k);
          Solutions++;
        }
      }
    }

    j = 1;
    k = maxNumber;
    printf("Found irreducible fraction: %d/%d\n", j, k);

    j = maxNumber;
    k = 1;
    printf("Found irreducible fraction: %d/%d\n", j, k);

    printf("Found total number of them: %d\n", Solutions + 2);
  }
  return 0;
}
