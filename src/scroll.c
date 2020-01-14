#include "scroll.h"
#include <bsd/string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned add_padding(char *string, int padding) {
  unsigned length = strlen(string);
  if (padding <= 0) {
    return length;
  }
  for (int i = length; i < (length + padding); ++i) {
    strlcat(string, " ", i + 2);
  }
  return length + padding;
}

void shift_string(char *string, unsigned length) {
  char first = string[0];
  for (int i = 0; i < length - 1; ++i) {
    string[i] = string[i + 1];
  }
  string[length - 1] = first;
}

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
  output[0] = '\0';
  unsigned buf_len = 0;
  while (fgets(buf, sizeof(buf), command) != 0) {
    buf_len += strlen(buf);
    output = realloc(output, sizeof(char) * (buf_len + 1));
    strlcat(output, buf, buf_len);
  }
  pclose(command);
  return output;
}

void handle_output_change(char **original, unsigned *padded_length,
                          Args *args) {
  char *new_string = generate_command_output(args->command);
  if (strcmp(*original, new_string) == 0) {
    free(new_string);
    return;
  }

  unsigned length = strlen(new_string);
  free(args->string);
  args->string = new_string;
  *original = realloc(*original, sizeof(char) * (length + 1));
  strlcpy(*original, new_string, length + 1);
  *padded_length = add_padding(args->string, args->padding);
}
