#include <time.h>

#include "timer.h"

const struct timespec gen_delay(long double delay) {
  __time_t seconds = 0;
  __syscall_slong_t nanoseconds = 0;

  seconds = (__time_t)delay;
  nanoseconds = (delay - seconds) * NANO_MULTI;
  return (const struct timespec){seconds, nanoseconds};
}
