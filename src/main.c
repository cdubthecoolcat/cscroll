#include "args.h"
#include "scroll.h"
#include <bsd/string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void handle_int(int sig) { exit(0); }

int main(int argc, char **argv) {
  signal(SIGINT, &handle_int);
  Args args = parse_args(argc, argv);
  const struct timespec delay = generate_delay(args.delay);

  if (args.command != NULL) {
    args.string = generate_command_output(args.command);
  }

  unsigned padded_length = add_padding(args.string, args.padding);

  bool empty_printed = false;
  int i = 0;
  unsigned printed_length =
      args.max_length == -1 ? padded_length : args.max_length;

  while (true) {
    if (args.command != NULL) {
      handle_output_change(&padded_length, &printed_length, &args, &i);
    }

    if (args.command == NULL || padded_length > 0) {

      printf("%.*s", printed_length, args.string + i);
      if (padded_length - i < args.max_length) {
        printf("%.*s", printed_length - (padded_length - i), args.string);
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
  }

  return 0;
}
