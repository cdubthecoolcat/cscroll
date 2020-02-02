#include <string.h>
#include <stdlib.h>

#include "padding.h"

unsigned add_pad(struct arguments* args, wchar_t** full_pad) {
  unsigned len = wcslen(args->str);
  if (args->pad <= 0 || len <= 0 || args->p_str_len <= 0) {
    return len;
  }

  if (*full_pad == NULL) {
    *full_pad = malloc((args->pad * args->p_str_len + 1) * sizeof(wchar_t));
    if (args->pad == 1) {
      mbstowcs(*full_pad, args->pad_str, args->p_str_len + 1);
    } else {
      for (int i = 0; i < args->pad; ++i) {
        mbstowcs(*full_pad + (args->p_str_len * i), args->pad_str, args->p_str_len);
      }
    }
  }

  wcscat(args->str, *full_pad);

  return len + (args->pad * args->p_str_len);
}
