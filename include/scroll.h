#ifndef SCROLL_H

#define SCROLL_H

#include "args.h"

#define NANO_MULTI 1e9

// adds padding to string
unsigned add_padding(char *string, int padding);

// shifts string by one. may switch to printing manip
void shift_string(char *string, unsigned padded_length);

// split delay into seconds/nanoseconds
const struct timespec generate_delay(long double delay);

// returns output of given command
char *generate_command_output(char *command_string);

// checks if there is an output change
void handle_output_change(char **original, unsigned *padded_length, Args *args);

#endif // SCROLL_H
