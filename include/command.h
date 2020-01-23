#ifndef COMMAND_H

#define COMMAND_H

#include "args.h"

#define BUFFER_LENGTH 256
#define CLEAR() printf("%c[2K", 27)

// returns output of given cmd
char* gen_cmd_output(char* cmd_str, size_t pad);

// checks if there is an output change
void handle_output_change(unsigned* full_len,
                          unsigned* print_len,
                          struct arguments* args,
                          unsigned* scroller);

#endif  // COMMAND_H
