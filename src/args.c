#include <bsd/string.h>
#include <stdio.h>
#include <stdlib.h>

#include "args.h"

#ifdef DEBUG

void print_args(struct arguments* args) {
  printf("Padding: %d\n", args->padding);
  printf("Max Length: %d\n", args->max_length);
  printf("Delay: %Le\n", args->delay);
  printf("String: %s\n", args->string);
  fflush(stdout);
}

#endif

struct argp argp = {options, parse_opt, "", "A simple terminal text scroller"};

struct argp_option options[] = {
    {"padding", 'p', "PADDING", 0, "Amount of padding to add"},
    {"padding_str", 'P', "STRING", 0, "String to use for padding"},
    {"max_length", 'm', "LENGTH", 0, "Max length for printing"},
    {"delay", 'd', "DELAY", 0, "Delay between shifts"},
    {"string", 's', "STRING", 0, "String used to scroll"},
    {"command", 'c', "COMMAND", 0, "Shell command to get string from"},
    {"new_line", 'n', 0, 0, "Print new line after each print"},
    {0}};

error_t parse_opt(int key, char* arg, struct argp_state* state) {
  struct arguments* arguments = state->input;

  switch (key) {
    case 'p':
      arguments->padding = atoi(arg);
      break;
    case 'P':
      arguments->padding_string = arg;
      arguments->p_string_len = strlen(arg);
      break;
    case 'm':
      arguments->max_length = atoi(arg);
      break;
    case 'd':
      arguments->delay = atof(arg);
      break;
    case 's':
      arguments->string = arg;
      break;
    case 'c':
      arguments->command = arg;
      break;
    case 'n':
      arguments->new_line = true;
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}
