#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "error.h"
#include "padding.h"

wchar_t* gen_cmd_output(char* cmd_str, size_t pad) {
  FILE* cmd = popen(cmd_str, "r");
  char buf[BUFFER_LENGTH];
  wchar_t* output = calloc(1, sizeof(wchar_t));
  check_errors(output);
  size_t buf_len = 0;

  while (fgets(buf, sizeof(buf), cmd)) {
    size_t part_len = strlen(buf);
    buf_len += part_len;
    output = realloc(output, sizeof(wchar_t) * (buf_len + pad + 1));
    check_errors(output);
    mbstowcs(output + buf_len - part_len, buf, part_len);
  }

  if (buf_len == 0) {
    output = realloc(output, sizeof(wchar_t) * (buf_len + 1));
  }

  size_t len = wcslen(output);
  if (output[len - 1] == '\n') {
    output[len - 1] = 0;
  }

  pclose(cmd);
  return output;
}

void handle_output_change(unsigned* full_len,
                          unsigned* print_len,
                          struct arguments* args,
                          wchar_t** full_pad,
                          unsigned* scroller) {
  unsigned pad_len = args->pad * args->p_str_len;
  wchar_t* new_str = gen_cmd_output(args->cmd, pad_len);
  if (wcsncmp(args->str, new_str, *full_len - pad_len) == 0) {
    free(new_str);
    return;
  }

  *scroller = 0;

  free(args->str);
  args->str = new_str;
  *full_len = add_pad(args, full_pad);

  *print_len = args->max_len == -1 ? *full_len : args->max_len;

  if (!args->new_line) {
    CLEAR();
  }
}
