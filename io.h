#ifndef IO_H
#define IO_H

#include "types.h"

status_t continious_write_to_scratchpad(const char* name);
status_t write_help_message_to_stdout(void);

#endif