#ifndef COMMANDS_H
#define COMMANDS_H

#include "types.h"

status_t create_new_scratchpad(const char* scratchpad_name);
status_t show_scratchpad(const char* scratchpad_name);
status_t remove_scratchpad(const char* scratchpad_name);
status_t edit_scratchpad(const char* scratchpad_name);
status_t list_scratchpads(void);

#endif // COMMANDS_H