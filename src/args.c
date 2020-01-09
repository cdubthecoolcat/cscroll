#include "args.h"

void print_args(Args* args) {
  printf("Padding: %d\n", args->padding);
  printf("Max Length: %d\n", args->max_length);
  printf("Delay: %ld\n", args->delay);
  printf("String: %s\n", args->string);
  fflush(stdout);
}

// For argument parsing
Args parse_args(int argc, char **argv) {
  Args args = {
    0,
    0,
    1.0,
    NULL
  };
  for (int i = 1; i < argc; ++i) {
    char* arg = argv[i];
    char* arg_val = argv[i + 1];
    if (strcmp(arg, "-p") == 0) {
      args.padding = atoi(arg_val);
      ++i;
    } else if (strcmp(arg, "-m") == 0) {
      args.max_length = atoi(arg_val);
      ++i;
    } else if (strcmp(arg, "-d") == 0) {
      args.delay = atof(arg_val);
      ++i;
    } else if (strcmp(arg, "-h") == 0) {
      print_help(argv[0]);
      exit(0);
    } else {
      if (args.string == NULL) {
        args.string = arg;
      }
    }
  }
  /*print_args(&args);*/
  return args;
}

void print_help(char* command) {
  printf("usage %s [-p PADDING] [-m MAX_LENGTH] [-d DELAY] [STRING]\n", command);
}
