#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "status.h"
#include "stdio.h"

#define BUFFER_SIZE 256

static const char *STORAGE_PATH = "/tmp/shelf/";

status_t io_continious_write_from_to(const char *name) {
  FILE *file;
  file = fopen("test.o", "w");

  char buffer[BUFFER_SIZE] = {};
  while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
    fputs(buffer, file);
  }

  fclose(file);

  return ST_OK;
}

void io_write_help_message(void) {}

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

status_t io_remove_file(const char *name) { return ST_OK; }

status_t list_scratchpad_files() {
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

  return ST_OK;
}
