#ifndef ARGS_H

#define ARGS_H
#include <stdbool.h>

typedef struct {
  int padding;
  char* padding_string;
  int max_length;
  long double delay;
  char* string;
  char* command;
  bool new_line;
  int p_string_len;
} Args;

// simple argument parser
// needs some work
Args parse_args(int argc, char** argv);

// print the help dialog
void print_help(char* command);

#endif  // ARGS_H
