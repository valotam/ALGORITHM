#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef MAX
#define MAX 100
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef struct _NODE {
  int Key;
  int Counter;
}NODE;

void Initialize(void);
void MakeRandomNuber(void);
void DisplayBuffer(void);
void DisplayHitBuffer(void);
void DisplayHitCounter(void);

int Buf[MAX];
NODE Hit[50];

// Initialize Data to sort
void Initialize(void) {
  for (size_t i = 0; i < MAX; i++) {
    Buf[i] = -1;
  }


  for (size_t i = 0; i < 50; i++) {
    Hit[i].Key = -1;
    Hit[i].Counter = 0;
    Hit[i].
  }
}
