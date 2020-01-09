#ifndef ARGS_H

#define ARGS_H
#include <bsd/string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  int padding;
  int max_length;
  long double delay;
  char* string;
} Args;

Args parse_args(int argc, char** argv);
void print_help(char* command);

#endif // ARGS_H
