#include "scroll.h"
#include "error.h"
#include <bsd/string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned add_padding(Args *args) {
  unsigned length = strlen(args->string);
  if (args->padding <= 0 || length <= 0) {
    return length;
  }

  unsigned padding_string_len = strlen(args->padding_string);
  for (int i = length; i < (length + args->padding); ++i) {
    strlcat(args->string, args->padding_string, i + 1 + padding_string_len);
  }
  return length + (args->padding * padding_string_len);
}

/*void shift_string(char *string, unsigned length) {*/
/*char first = string[0];*/
/*for (int i = 0; i < length - 1; ++i) {*/
/*string[i] = string[i + 1];*/
/*}*/
/*string[length - 1] = first;*/
/*}*/

const struct timespec generate_delay(long double delay) {
  unsigned seconds = 0;
  unsigned nanoseconds = 0;

  seconds = (int)floor(delay);
  nanoseconds = (delay - seconds) * NANO_MULTI;
  return (const struct timespec){seconds, nanoseconds};
}

char *generate_command_output(char *command_string) {
  FILE *command = popen(command_string, "r");
  char buf[256];
  char *output = malloc(sizeof(char));
  check_errors(output);
  output[0] = '\0';
  unsigned buf_len = 0;
  while (fgets(buf, sizeof(buf), command) != 0) {
    buf_len += strlen(buf);
    output = realloc(output, sizeof(char) * (buf_len + 1));
    check_errors(output);
    strlcat(output, buf, buf_len);
  }
  pclose(command);
  return output;
}

void handle_output_change(unsigned *padded_length, unsigned *printed_length,
                          Args *args, int *scroller) {
  char *new_string = generate_command_output(args->command);
  unsigned padding_string_len = strlen(args->padding_string);
  if (strncmp(args->string, new_string, *padded_length - (args->padding * padding_string_len)) == 0) {
    free(new_string);
    return;
  }

  *scroller = 0;

  free(args->string);
  args->string = new_string;
  *padded_length = add_padding(args);

  *printed_length = args->max_length == -1 ? *padded_length : args->max_length;

  if (!args->new_line) {
    printf("%c[2K", 27);
  }
}
