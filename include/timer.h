#ifndef TIMER_H

#define TIMER_H

#define NANO_MULTI 1e9

// split delay into seconds/nanoseconds
const struct timespec generate_delay(long double delay);

#endif // TIMER_H
