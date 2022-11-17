#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdbool.h>

#include "types.h"

bool is_no_argument_command(command_type_t command);

status_t create_new_scratchpad(const char* scratchpad_name);
status_t show_scratchpad(const char* scratchpad_name);
status_t remove_scratchpad(const char* scratchpad_name);
status_t edit_scratchpad(const char* scratchpad_name);
status_t list_scratchpads(void);
status_t show_help(void);

#endif // COMMANDS_H