#include <bsd/string.h>

#include "padding.h"

unsigned add_pad(struct arguments* args) {
  unsigned len = strlen(args->str);
  if (args->pad <= 0 || len <= 0) {
    return len;
  }

  for (int i = 0; i < args->pad; ++i) {
    size_t cat_len = len + (i + 2) * args->p_str_len;
    strlcat(args->str, args->pad_str, cat_len);
  }
  return len + (args->pad * args->p_str_len);
}
