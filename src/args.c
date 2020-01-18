#include "args.h"
#include <bsd/string.h>
#include <stdio.h>
#include <stdlib.h>

void print_args(Args *args) {
  printf("Padding: %d\n", args->padding);
  printf("Max Length: %d\n", args->max_length);
  printf("Delay: %Le\n", args->delay);
  printf("String: %s\n", args->string);
  fflush(stdout);
}

// For argument parsing
Args parse_args(int argc, char **argv) {
  if (argc <= 1) {
    print_help(argv[0]);
  }
  Args args = {
      0,     // padding
      0,     // max_length
      1.0,   // delay
      NULL,  // string
      NULL,  // command
      false, // new_line
      false, // has max length
  };
  for (int i = 1; i < argc; ++i) {
    char *arg = argv[i];
    char *arg_val = argv[i + 1];
    if (strcmp(arg, "-p") == 0) {
      if (arg_val == NULL) {
        print_help(argv[0]);
      }
      args.padding = atoi(arg_val);
      ++i;
    } else if (strcmp(arg, "-m") == 0) {
      if (arg_val == NULL) {
        print_help(argv[0]);
      }
      args.max_length = atoi(arg_val);
      args.has_max_length = true;
      ++i;
    } else if (strcmp(arg, "-d") == 0) {
      if (arg_val == NULL) {
        print_help(argv[0]);
      }
      args.delay = atof(arg_val);
      ++i;
    } else if (strcmp(arg, "-c") == 0) {
      if (arg_val == NULL) {
        print_help(argv[0]);
      }
      args.command = arg_val;
      ++i;
    } else if (strcmp(arg, "-n") == 0) {
      args.new_line = true;
    } else if (strcmp(arg, "-h") == 0) {
      print_help(argv[0]);
    } else {
      if (args.string == NULL) {
        args.string = arg;
      }
    }
  }

  return args;
}

void print_help(char *command) {
  printf("usage %s [-p PADDING] [-m MAX_LENGTH] [-d DELAY] [STRING | -c "
         "COMMAND]\n",
         command);
  exit(0);
}
