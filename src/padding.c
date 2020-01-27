#include <string.h>
#include <stdlib.h>

#include "padding.h"

unsigned add_pad(struct arguments* args, char** full_pad) {
  unsigned len = strlen(args->str);
  if (args->pad <= 0 || len <= 0 || args->p_str_len <= 0) {
    return len;
  }

  if (*full_pad == NULL) {
    if (args->pad == 1) {
      *full_pad = args->pad_str;
    } else {
      *full_pad = malloc((args->pad * args->p_str_len + 1) * sizeof(char));
      (*full_pad)[0] = 0;
      for (int i = 0; i < args->pad; ++i) {
        strcat(*full_pad, args->pad_str);
      }
    }
  }

  strcat(args->str, *full_pad);

  return len + (args->pad * args->p_str_len);
}
