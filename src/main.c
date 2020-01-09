#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "args.h"

#define NANO_MULTI 1e9

int nanosleep(const struct timespec *__requested_time, struct timespec *__remaining);

unsigned add_padding(char* string, int padding) {
  unsigned length = strlen(string);
  if (padding <= 0) {
    return length;
  }
  for (int i = length; i < (length + padding); ++i) {
    strlcat(string, " ", i + 2);
  }
  return length + padding;
}

void shift_string(char* string, unsigned length) {
  char first = string[0];
  for (int i = 0; i < length - 1; ++i) {
    string[i] = string[i + 1];
  }
  string[length - 1] = first;
}

const struct timespec generate_delay(long double delay) {
  unsigned seconds = 0;
  unsigned nanoseconds = 0;

  seconds = (int) floor(delay);
  nanoseconds = (delay - seconds) * NANO_MULTI;
  return (const struct timespec){ seconds, nanoseconds };
}

int main(int argc, char** argv) {
  Args args = parse_args(argc, argv);
  const struct timespec delay = generate_delay(args.delay);
  unsigned length = add_padding(args.string, args.padding);

  while (true) {
    printf("%.*s\r", args.max_length == 0 ? length : args.max_length, args.string);
    fflush(stdout);
    shift_string(args.string, length);
    nanosleep(&delay, NULL);
  }
  return 0;
}
