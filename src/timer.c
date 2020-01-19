#include "timer.h"
#include <math.h>
#include <time.h>

const struct timespec generate_delay(long double delay) {
  unsigned seconds = 0;
  unsigned nanoseconds = 0;

  seconds = (int)floor(delay);
  nanoseconds = (delay - seconds) * NANO_MULTI;
  return (const struct timespec){seconds, nanoseconds};
}
