#include <bsd/string.h>
#include <locale.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "args.h"
#include "command.h"
#include "padding.h"
#include "timer.h"

bool stopped = false;

void handle_int(int sig) {
  stopped = true;
}

int main(int argc, char** argv) {
  setlocale(LC_ALL, "en_US.UTF-8");
  signal(SIGINT, &handle_int);

  // defaults
  struct arguments args = {
      0,      // padding
      -1,     // max_length
      1,      // p_string_len
      1.0,    // delay
      NULL,   // string
      NULL,   // command
      " ",    // padding string
      false,  // new_line
      false,  // reverse
  };

  argp_parse(&argp, argc, argv, 0, 0, &args);

  const struct timespec delay = generate_delay(args.delay);

  if (args.command != NULL) {
    args.string =
        generate_command_output(args.command, args.padding * args.p_string_len);
  }

  unsigned padded_length = add_padding(&args);

  bool empty_printed = false;
  unsigned i = 0, position,
           printed_length =
               args.max_length == -1 ? padded_length : args.max_length;

  setbuf(stdout, NULL);

  while (!stopped) {
    if (args.command != NULL) {
      handle_output_change(&padded_length, &printed_length, &args, &i);
    }

    position = args.reverse ? padded_length - i : i;

    if (args.command == NULL || padded_length > 0) {
      printf("%.*s%.*s%s", printed_length, args.string + position,
             padded_length - i < args.max_length
                 ? printed_length - (padded_length - position)
                 : 0,
             args.string, args.new_line ? "\n" : "\r");

      i = (i + 1) % padded_length;
      empty_printed = false;
    } else if (!empty_printed) {
      args.new_line ? printf("\n") : printf("\r");
      empty_printed = true;
    }

    nanosleep(&delay, NULL);
  }

  if (args.command != NULL) {
    free(args.string);
  }

  return 0;
}
