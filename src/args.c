#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "args.h"

#ifdef DEBUG

void print_args(struct arguments* args) {
  printf("Padding: %d\n", args->pad);
  printf("Max Length: %d\n", args->max_len);
  printf("Delay: %Le\n", args->delay);
  printf("String: %s\n", args->str);
  fflush(stdout);
}

#endif

struct argp argp = {options, parse_opt, "", "A simple terminal text scroller"};

struct argp_option options[] = {
    {"pad", 'p', "PADDING", 0, "Amount of pad to add"},
    {"pad_str", 'P', "STRING", 0, "String to use for pad"},
    {"max_len", 'm', "LENGTH", 0, "Max len for printing"},
    {"delay", 'd', "DELAY", 0, "Delay between shifts"},
    {"str", 's', "STRING", 0, "String used to scroll"},
    {"cmd", 'c', "COMMAND", 0, "Shell cmd to get str from"},
    {"new_line", 'n', 0, 0, "Print new line after each print"},
    {"reverse", 'r', 0, 0, "Reverse scrolling"},
    {0}};

error_t parse_opt(int key, char* arg, struct argp_state* state) {
  struct arguments* arguments = state->input;

  switch (key) {
    case 'p':
      arguments->pad = atoi(arg);
      break;
    case 'P':
      arguments->pad_str = arg;
      arguments->p_str_len = strlen(arg);
      break;
    case 'm':
      arguments->max_len = atoi(arg);
      break;
    case 'd':
      arguments->delay = atof(arg);
      break;
    case 's':
      mbstowcs(arguments->str, arg, 0);
      break;
    case 'c':
      arguments->cmd = arg;
      break;
    case 'n':
      arguments->new_line = true;
      break;
    case 'r':
      arguments->reverse = true;
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}
