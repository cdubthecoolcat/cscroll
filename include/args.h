#ifndef ARGS_H

#define ARGS_H

#include <argp.h>
#include <stdbool.h>

#define FLAG_LEN 2

struct arguments {
  int padding;
  int max_length;
  int p_string_len;
  long double delay;
  char* string;
  char* command;
  char* padding_string;
  bool new_line;
};

extern struct argp_option options[];
extern error_t parse_opt(int key, char* arg, struct argp_state* state);
extern struct argp argp;

// print the help dialog
void print_help(char* command);

#endif  // ARGS_H
