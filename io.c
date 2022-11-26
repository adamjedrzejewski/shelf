#include <dirent.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "status.h"
#include "stdio.h"

#define BUFFER_SIZE 256

#define foreach(item, array)                                                   \
  for (int keep = 1, count = 0, size = sizeof(array) / sizeof *(array);        \
       keep && count != size; keep = !keep, count++)                           \
    for (item = (array) + count; keep; keep = !keep)

static const char *STORAGE_PATH = "/tmp/shelf/";

struct error_message_mapping {
  enum status status;
  const char **erorr_message;
};

struct error_message_mapping error_message_mappings[] = {
    {ST_NO_COMMAND_SPECIFIED, &ST_NO_COMMAND_SPECIFIED_ERROR_MESSAGE},
    {ST_MISSING_SCRATCHPAD_NAME, &ST_MISSING_SCRATCHPAD_NAME_ERROR_MESSAGE},
    {ST_CMD_INVALID, &ST_CMD_INVALID_STATUS_NAME_ERROR_MESSAGE},
    {ST_FAILED_TO_READ_STASH, &ST_FAILED_TO_READ_STASH_NAME_ERROR_MESSAGE},
    {ST_FAILED_TO_CREATE_STASH, &ST_FAILED_TO_CREATE_STASH_ERROR_MESSAGE},
    {ST_SCRATCHPAD_DOESNT_EXIST, &ST_SCRATCHPAD_DOESNT_EXIST_ERROR_MESSAGE},
    {ST_FAILED_TO_REMOVE_SCRATCHPAD,
     &ST_FAILED_TO_REMOVE_SCRATCHPAD_ERROR_MESSAGE},
    {ST_FAILED_TO_READ_ENVVAR, &ST_FAILED_TO_READ_ENVVAR_ERROR_MESSAGE}};

static enum status __create_scratchpad_path(const char *filename, char *buffer) {
  // TODO: handle error
  snprintf(buffer, BUFFER_SIZE, "%s%s", STORAGE_PATH, filename);

  return ST_OK;
}

static bool _file_exists(const char *path) {
  struct stat st;

  // TODO: handle error
  return stat(path, &st) == 0;
}

enum status io_write_from_stdin_to_file(const char *filename) {
  FILE *file;
  enum status status;
  char path[BUFFER_SIZE];
  char buffer[BUFFER_SIZE];

  status = __create_scratchpad_path(filename, path);
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

enum status io_write_from_file_to_stdout(const char *filename) {
  FILE *file;
  enum status status;
  char path[BUFFER_SIZE];
  char buffer[BUFFER_SIZE];

  status = __create_scratchpad_path(filename, path);
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

enum status io_remove_file(const char *filename) {
  enum status status;
  char path[BUFFER_SIZE];

  status = __create_scratchpad_path(filename, path);
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

void io_write_help_message(void) {
  puts("commands:");
  puts("new - create new scratchpad");
  puts("show - show scratchpad contents");
  puts("remove - remove scratchpad");
  puts("list - list scratchpads");
  puts("edit - edit scratchpad");
  puts("help - show help");
}

void io_write_error(enum status error) {
  const char *error_message;

  foreach (struct error_message_mapping *mapping, error_message_mappings) {

    // you can't break out of this macro loop with break
    if (mapping->status == error) {
      error_message = *mapping->erorr_message;
      goto SHOW_ERORR;
    }
  }

SHOW_ERORR:
  fputs(error_message, stderr);
  fputs("\n", stderr);
}

enum status io_create_stash_if_nonexistent(void) {
  struct stat st;

  if (stat(STORAGE_PATH, &st) == 0) {
    return ST_OK;
  }

  // TODO: handle error
  // change access
  int err = mkdir(STORAGE_PATH, 0777);

  return err == 0 ? ST_OK : ST_FAILED_TO_CREATE_STASH;
}

enum status io_list_files_in_stash(void) {
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

// TODO: error handling, what if ret_val is too big to be put in a buffer
enum status io_getenv(const char *var_name, char **ret_val) {
  char *editor = getenv(var_name);

  if (editor == NULL) {
    return ST_FAILED_TO_READ_ENVVAR;
  }

  *ret_val = editor;

  return ST_OK;
}

enum status io_run_editor_on_file(const char *editor,
                               const char *scratchpad_name) {
  char path[BUFFER_SIZE];
  char command[BUFFER_SIZE];
  enum status status;

  status = __create_scratchpad_path(scratchpad_name, path);
  if (status != ST_OK) {
    return status;
  }

  snprintf(command, BUFFER_SIZE, "%s %s", editor, path);

  system(command);

  return ST_OK;
}
