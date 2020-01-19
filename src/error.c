#include "error.h"
#include <stdio.h>
#include <stdlib.h>

void check_errors(void *pointer) {
  if (pointer == NULL) {
    fprintf(stderr, "error allocating memory");
    exit(-1);
  }
}
