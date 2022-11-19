#include <dirent.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "status.h"
#include "stdio.h"

#define BUFFER_SIZE 256

static const char *STORAGE_PATH = "/tmp/shelf/";

static status_t _create_scratchpad_path(const char *filename, char *buffer) {
  // TODO: handle error
  snprintf(buffer, BUFFER_SIZE, "%s%s", STORAGE_PATH, filename);

  return ST_OK;
}

static bool _file_exists(const char *path) {
  struct stat st;

  // TODO: handle error
  return stat(path, &st) == 0;
}

status_t io_write_from_stdin_to_file(const char *filename) {
  FILE *file;
  status_t status;
  char path[BUFFER_SIZE] = {};
  char buffer[BUFFER_SIZE] = {};

  status = _create_scratchpad_path(filename, path);
  if (status != ST_OK) {
    return status;
  }

  // TODO: handle error
  file = fopen(path, "w");

  while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
    fputs(buffer, file);
  }

  fclose(file);

  return ST_OK;
}

status_t io_write_from_file_to_stdout(const char *filename) {
  FILE *file;
  status_t status;
  char path[BUFFER_SIZE] = {};
  char buffer[BUFFER_SIZE] = {};

  status = _create_scratchpad_path(filename, path);
  if (status != ST_OK) {
    return status;
  }
  if (!_file_exists(path)) {
    return ST_SCRATCHPAD_DOESNT_EXIST;
  }

  // TODO: handle error
  file = fopen(path, "r");
  while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
    fputs(buffer, stdout);
  }

  fclose(file);

  return ST_OK;
}

status_t io_remove_file(const char *filename) {
  FILE *file;
  status_t status;
  char path[BUFFER_SIZE] = {};

  status = _create_scratchpad_path(filename, path);
  if (status != ST_OK) {
    return status;
  }

  if (!_file_exists(path)) {
    return ST_SCRATCHPAD_DOESNT_EXIST;
  }

  if (remove(path) != 0) {
    return ST_FAILED_TO_REMOVE_SCRATCHPAD;
  }

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
  case ST_FAILED_TO_CREATE_STASH:
    error_message = ST_FAILED_TO_CREATE_STASH_ERROR_MESSAGE;
    break;
  case ST_SCRATCHPAD_DOESNT_EXIST:
    error_message = ST_SCRATCHPAD_DOESNT_EXIST_ERROR_MESSAGE;
    break;
  case ST_FAILED_TO_REMOVE_SCRATCHPAD:
    error_message = ST_FAILED_TO_REMOVE_SCRATCHPAD_ERROR_MESSAGE;
    break;
  default:
    return;
  }

  fputs(error_message, stderr);
  fputs("\n", stderr);
}

status_t io_create_stash_if_nonexistent(void) {
  struct stat st = {};

  if (stat(STORAGE_PATH, &st) == 0) {
    return ST_OK;
  }

  int err = mkdir(STORAGE_PATH, 0777);

  return err == 0 ? ST_OK : ST_FAILED_TO_CREATE_STASH;
}

status_t io_list_files_in_stash(void) {
  // TODO: handle errors
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
