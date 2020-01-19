#include "command.h"
#include "error.h"
#include "padding.h"
#include <bsd/string.h>
#include <stdio.h>
#include <stdlib.h>

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
  if (strncmp(args->string, new_string,
              *padded_length - (args->padding * args->p_string_len)) == 0) {
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
