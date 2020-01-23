#ifndef ARGS_H

#define ARGS_H

#include <argp.h>
#include <stdbool.h>

#define FLAG_LEN 2

struct arguments {
  int pad;
  int max_len;
  int p_str_len;
  long double delay;
  char* str;
  char* cmd;
  char* pad_str;
  bool new_line;
  bool reverse;
};

extern struct argp_option options[];
extern error_t parse_opt(int key, char* arg, struct argp_state* state);
extern struct argp argp;

#endif  // ARGS_H
