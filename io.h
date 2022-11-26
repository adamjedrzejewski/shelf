#ifndef IO_H
#define IO_H

#include "status.h"

enum status_type io_create_stash_if_nonexistent(void);
enum status_type io_write_from_stdin_to_file(const char *filename);
enum status_type io_write_from_file_to_stdout(const char *filename);
enum status_type io_remove_file(const char *filename);
enum status_type io_list_files_in_stash(void);

enum status_type io_run_editor_on_file(const char *editor,
                                  const char *file);

void io_write_help_message(void);
void io_write_error(enum status_type error);

#endif
