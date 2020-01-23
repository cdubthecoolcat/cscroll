#include <bsd/string.h>
#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "error.h"
#include "padding.h"

char* gen_cmd_output(char* cmd_str, size_t pad) {
  FILE* cmd = popen(cmd_str, "r");
  char buf[BUFFER_LENGTH];
  char* output = calloc(1, sizeof(char));
  check_errors(output);
  size_t buf_len = 0;

  while (fgets(buf, sizeof(buf), cmd) != 0) {
    buf_len += strlen(buf);
    output = realloc(output, sizeof(char) * (buf_len + pad + 1));
    check_errors(output);
    strlcat(output, buf, buf_len);
  }

  pclose(cmd);
  return output;
}

void handle_output_change(unsigned* full_len,
                          unsigned* print_len,
                          struct arguments* args,
                          unsigned* scroller) {
  unsigned pad_len = args->pad * args->p_str_len;
  char* new_str = gen_cmd_output(args->cmd, pad_len);
  if (strncmp(args->str, new_str, *full_len - pad_len) == 0) {
    free(new_str);
    return;
  }

  *scroller = 0;

  free(args->str);
  args->str = new_str;
  *full_len = add_pad(args);

  *print_len = args->max_len == -1 ? *full_len : args->max_len;

  if (!args->new_line) {
    CLEAR();
  }
}
