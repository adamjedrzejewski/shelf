#ifndef IO_H
#define IO_H

#include "status.h"

status_t io_create_stash_if_nonexistent(void);
status_t io_write_from_stdin_to_file(const char *filename);
status_t io_write_from_file_to_stdout(const char *filename);
status_t io_remove_file(const char *filename);
status_t io_list_files_in_stash(void);

status_t io_getenv(const char *envname, char *ret_val);

status_t io_run_editor_on_file(const char *editor, const char *scratchpad_name);

void io_write_help_message(void);
void io_write_error(status_t error);

#endif
