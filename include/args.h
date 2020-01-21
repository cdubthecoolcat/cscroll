#ifndef ARGS_H

#define ARGS_H

#include <argp.h>
#include <stdbool.h>

#define FLAG_LEN 2

struct arguments {
  int padding;
  char* padding_string;
  int max_length;
  long double delay;
  char* string;
  char* command;
  bool new_line;
  int p_string_len;
};

extern struct argp_option options[];
extern error_t parse_opt(int key, char* arg, struct argp_state* state);
extern struct argp argp;

// print the help dialog
void print_help(char* command);

#endif  // ARGS_H
