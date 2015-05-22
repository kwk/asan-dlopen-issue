#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

void say_hello() {
  int * not_freed = (int*) malloc(sizeof(int));
  (void) not_freed;
  printf("Hello! %p\n", not_freed);
}
