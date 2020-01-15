#include "args.h"
#include "scroll.h"
#include <bsd/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
  Args args = parse_args(argc, argv);
  const struct timespec delay = generate_delay(args.delay);
  char *original;

  if (args.command != NULL) {
    args.string = generate_command_output(args.command);
    unsigned raw_length = strlen(args.string);
    original = malloc(sizeof(char) * (raw_length + 1));
    strlcpy(original, args.string, raw_length + 1);
  }

  unsigned padded_length = add_padding(args.string, args.padding);
  if (args.max_length == 0) {
    args.max_length = padded_length;
  }

  bool empty_printed = false;
  int i = 0;
  while (true) {
    if (args.command != NULL) {
      handle_output_change(&original, &padded_length, &args);
    }

    if (args.command == NULL || strlen(original) > 0) {
      printf("%.*s", args.max_length, args.string + i);
      if (padded_length - i < args.max_length) {
        printf("%.*s", args.max_length - (padded_length - i), args.string);
      }
      i = (i + 1) % padded_length;
      args.new_line ? printf("\n") : printf("\r");
      empty_printed = false;
    } else if (!empty_printed) {
      args.new_line ? printf("\n") : printf("\r");
      empty_printed = true;
    }

    fflush(stdout);
    nanosleep(&delay, NULL);
  }

  if (args.command != NULL) {
    free(args.string);
    free(original);
  }

  return 0;
}
