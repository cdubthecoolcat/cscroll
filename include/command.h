#ifndef COMMAND_H

#define COMMAND_H

#include "args.h"

#define BUFFER_LENGTH 256
#define CLEAR() printf("%c[2K", 27)

// returns output of given command
char* generate_command_output(char* command_string);

// checks if there is an output change
void handle_output_change(unsigned* padded_length,
                          unsigned* printed_length,
                          Args* args,
                          int* scroller);

#endif  // COMMAND_H
