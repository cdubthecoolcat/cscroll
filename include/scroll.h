#ifndef SCROLL_H

#define SCROLL_H

#include "args.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define NANO_MULTI 1e9

unsigned add_padding(char* string, int padding);
void shift_string(char* string, unsigned padded_length);
const struct timespec generate_delay(long double delay);
char* generate_command_output(char* command_string);
void handle_output_change(char** original, unsigned* padded_length, Args* args);

#endif // SCROLL_H
