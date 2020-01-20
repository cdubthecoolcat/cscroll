#include <time.h>

#include "timer.h"

const struct timespec generate_delay(long double delay) {
  unsigned seconds = 0;
  unsigned nanoseconds = 0;

  seconds = (int)delay;
  nanoseconds = (delay - seconds) * NANO_MULTI;
  return (const struct timespec){seconds, nanoseconds};
}
