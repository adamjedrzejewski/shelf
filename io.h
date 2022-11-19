#ifndef IO_H
#define IO_H

#include "status.h"

status_t io_create_stash_if_nonexistent(void);
status_t io_remove_file(const char *name);
status_t io_continious_write_from_to(const char *name);

void io_write_help_message(void);
void io_write_error(status_t error);

#endif
