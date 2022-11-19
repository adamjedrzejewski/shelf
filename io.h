#ifndef IO_H
#define IO_H

#include "status.h"

status_t create_stash();
status_t cmd_remove_file(const char *name);
status_t continious_write_to_scratchpad(const char *name);
status_t write_help_message_to_stdout(void);

#endif
