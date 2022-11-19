#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "status.h"
#include "stdio.h"

#define BUFFER_SIZE 256

static const char *STORAGE_PATH = "/tmp/shelf/";

status_t io_write_from_stdin_to_file(const char *name) {
  puts("new");
  /*
  FILE *file;
  file = fopen("test.o", "w");

  char buffer[BUFFER_SIZE] = {};
  while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
    fputs(buffer, file);
  }

  fclose(file);
  */

  return ST_OK;
}

status_t io_write_from_file_to_stdout(const char *filename) {
  puts("show");
  return ST_OK;
}

status_t io_remove_file(const char *filename) {
  puts("show");
  return ST_OK;
}

void io_write_help_message(void) { puts("help"); }

void io_write_error(status_t error) {
  const char *error_message;
  switch (error) {
  case ST_NO_COMMAND_SPECIFIED:
    error_message = ST_NO_COMMAND_SPECIFIED_ERROR_MESSAGE;
    break;
  case ST_MISSING_SCRATCHPAD_NAME:
    error_message = ST_MISSING_SCRATCHPAD_NAME_ERROR_MESSAGE;
    break;
  case ST_CMD_INVALID:
    error_message = ST_CMD_INVALIDS_STATUS_NAME_ERROR_MESSAGE;
    break;
  case ST_FAILED_TO_READ_STASH:
    error_message = ST_FAILED_TO_READ_STASH_NAME_ERROR_MESSAGE;
    break;
  default:
    return;
  }

  fputs(error_message, stderr);
  fputs("\n", stderr);
}

status_t io_create_stash_if_nonexistent(void) {
  int err = mkdir(STORAGE_PATH, 0777);

  return err == 0 ? ST_OK : ST_FAILED_TO_CREATE_STASH;
}

status_t io_list_files_in_stash(void) {
  /*
  DIR *d;
  struct dirent *dir;

  d = opendir(STORAGE_PATH);
  if (!d) {
    return ST_FAILED_TO_READ_STASH;
  }

  while ((dir = readdir(d)) != NULL) {
    if (dir->d_type == DT_REG) {
      puts(dir->d_name);
    }
  }
  closedir(d);
  */
  puts("list");

  return ST_OK;
}

status_t io_getenv(const char *var_name, char *ret_val) {
  ret_val = getenv(var_name);

  if (ret_val == NULL) {
    return ST_FAILED_TO_READ_ENVVAR;
  }

  return ST_OK;
}

status_t io_run_editor_on_file(const char *editor,
                               const char *scratchpad_name) {
  puts("edit");
  return ST_OK;
}
