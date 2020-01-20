#include <bsd/string.h>

#include "padding.h"

unsigned add_padding(Args* args) {
  unsigned length = strlen(args->string);
  if (args->padding <= 0 || length <= 0) {
    return length;
  }

  for (int i = 0; i < args->padding; ++i) {
    unsigned cat_len = length + (i + 2) * args->p_string_len;
    strlcat(args->string, args->padding_string, cat_len);
  }
  return length + (args->padding * args->p_string_len);
}
