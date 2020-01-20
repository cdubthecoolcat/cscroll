#include <bsd/string.h>
#include <stdio.h>
#include <stdlib.h>

#include "args.h"

#ifdef DEBUG

void print_args(Args* args) {
  printf("Padding: %d\n", args->padding);
  printf("Max Length: %d\n", args->max_length);
  printf("Delay: %Le\n", args->delay);
  printf("String: %s\n", args->string);
  fflush(stdout);
}

#endif

// For argument parsing
Args parse_args(int argc, char** argv) {
  if (argc <= 1) {
    print_help(argv[0]);
  }

  // defaults
  Args args = {
      0,      // padding
      " ",    // padding string
      -1,     // max_length
      1.0,    // delay
      NULL,   // string
      NULL,   // command
      false,  // new_line
      1,      // p_string_len
  };

  for (int i = 1; i < argc; ++i) {
    char* arg = argv[i];
    char* arg_val = argv[i + 1];

    if (strncmp(arg, "-p", FLAG_LEN) == 0) {  // padding
      if (arg_val == NULL) {
        print_help(argv[0]);
      }

      args.padding = atoi(arg_val);

      ++i;
    } else if (strncmp(arg, "-P", FLAG_LEN) == 0) {  // padding_string
      if (arg_val == NULL) {
        print_help(argv[0]);
      }

      args.padding_string = arg_val;
      args.p_string_len = strlen(arg_val);

      ++i;
    } else if (strncmp(arg, "-m", FLAG_LEN) == 0) {  // max_length
      if (arg_val == NULL) {
        print_help(argv[0]);
      }

      args.max_length = atoi(arg_val);

      ++i;
    } else if (strncmp(arg, "-d", FLAG_LEN) == 0) {  // delay
      if (arg_val == NULL) {
        print_help(argv[0]);
      }

      args.delay = atof(arg_val);

      ++i;
    } else if (strncmp(arg, "-c", FLAG_LEN) == 0) {  // command
      if (arg_val == NULL) {
        print_help(argv[0]);
      }

      args.command = arg_val;

      ++i;
    } else if (strncmp(arg, "-n", FLAG_LEN) == 0) {  // new_line
      args.new_line = true;
    } else if (strncmp(arg, "-h", FLAG_LEN) == 0) {  // print_help
      print_help(argv[0]);
    } else {  // string
      if (args.string == NULL) {
        args.string = arg;
      }
    }
  }

  return args;
}

void print_help(char* command) {
  printf(
      "usage %s [-p PADDING] [-m MAX_LENGTH] [-d DELAY] [STRING | -c "
      "COMMAND]\n",
      command);
  exit(0);
}
