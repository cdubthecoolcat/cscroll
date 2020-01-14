#ifndef ARGS_H

#define ARGS_H
#include <bsd/string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  int padding;
  int max_length;
  long double delay;
  char* string;
  char* command;
  bool new_line;
} Args;

// simple argument parser
// needs some work
Args parse_args(int argc, char** argv);

// print the help dialog
void print_help(char* command);

#endif // ARGS_H
