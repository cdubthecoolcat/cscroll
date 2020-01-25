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
      0,      // pad
      -1,     // max_len
      1,      // p_str_len
      1.0,    // delay
      NULL,   // str
      NULL,   // cmd
      " ",    // pad str
      false,  // new_line
      false,  // reverse
  };

  argp_parse(&argp, argc, argv, 0, 0, &args);

  const struct timespec delay = gen_delay(args.delay);

  if (args.cmd != NULL) {
    args.str = gen_cmd_output(args.cmd, args.pad * args.p_str_len);
  }

  char* full_pad = NULL;
  unsigned full_len = add_pad(&args, &full_pad);

  bool empty_printed = false;
  unsigned i = 0;
  unsigned pos;
  unsigned print_len = args.max_len == -1 ? full_len : args.max_len;

  setvbuf(stdout, NULL, _IOFBF, BUFSIZ);

  while (!stopped) {
    if (args.cmd != NULL) {
      handle_output_change(&full_len, &print_len, &args, &full_pad, &i);
    }

    pos = args.reverse ? full_len - i : i;

    if (full_len != 0) {
      printf("%.*s%.*s%s", print_len, args.str + pos,
             full_len - pos < print_len ? print_len - (full_len - pos) : 0,
             args.str, args.new_line ? "\n" : "\r");

      i = (i + 1) % full_len;
      empty_printed = false;
    } else if (!empty_printed) {
      args.new_line ? printf("\n") : printf("\r");
      empty_printed = true;
    }

    fflush(stdout);

    nanosleep(&delay, NULL);
  }

  if (args.cmd != NULL) {
    free(args.str);
  }

  return 0;
}
