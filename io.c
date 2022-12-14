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
  enum status_type status;
  const char **erorr_message;
};

struct error_message_mapping error_message_mappings[] = {
    {ST_NO_COMMAND_SPECIFIED, &ST_NO_COMMAND_SPECIFIED_ERROR_MESSAGE},
    {ST_MISSING_ARGUMENT, &ST_MISSING_SCRATCHPAD_NAME_ERROR_MESSAGE},
    {ST_CMD_INVALID, &ST_CMD_INVALID_STATUS_NAME_ERROR_MESSAGE},
    {ST_FAILED_TO_READ_STASH, &ST_FAILED_TO_READ_STASH_NAME_ERROR_MESSAGE},
    {ST_FAILED_TO_CREATE_STASH, &ST_FAILED_TO_CREATE_STASH_ERROR_MESSAGE},
    {ST_SCRATCHPAD_DOESNT_EXIST, &ST_SCRATCHPAD_DOESNT_EXIST_ERROR_MESSAGE},
    {ST_FAILED_TO_REMOVE_SCRATCHPAD,
     &ST_FAILED_TO_REMOVE_SCRATCHPAD_ERROR_MESSAGE},
    {ST_FAILED_TO_READ_ENVVAR, &ST_FAILED_TO_READ_ENVVAR_ERROR_MESSAGE},
    {ST_FAILED_TO_RUN_EDITOR, &ST_FAILED_TO_RUN_EDITOR_ERROR_MESSAGE}};

static enum status_type __create_scratchpad_path(const char *filename,
                                            char *buffer) {
  // TODO: handle error
  snprintf(buffer, BUFFER_SIZE, "%s%s", STORAGE_PATH, filename);

  return ST_OK;
}

static bool _file_exists(const char *path) {
  struct stat st;

  // TODO: handle error
  return stat(path, &st) == 0;
}

enum status_type io_write_from_stdin_to_file(const char *filename) {
  FILE *file;
  enum status_type status;
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

enum status_type io_write_from_file_to_stdout(const char *filename) {
  FILE *file;
  enum status_type status;
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

enum status_type io_remove_file(const char *filename) {
  enum status_type status;
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

void io_write_error(enum status_type error) {
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

enum status_type io_create_stash_if_nonexistent(void) {
  struct stat st;

  if (stat(STORAGE_PATH, &st) == 0) {
    return ST_OK;
  }

  // TODO: handle error
  // change access
  int err = mkdir(STORAGE_PATH, 0777);

  return err == 0 ? ST_OK : ST_FAILED_TO_CREATE_STASH;
}

enum status_type io_list_files_in_stash(void) {
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

enum status_type io_run_editor_on_file(const char *editor,
                                  const char *scratchpad_name) {
  char path[BUFFER_SIZE];
  char command[BUFFER_SIZE];
  enum status_type status;
  int ret;

  status = __create_scratchpad_path(scratchpad_name, path);
  if (status != ST_OK) {
    return status;
  }

  snprintf(command, BUFFER_SIZE, "%s %s", editor, path);

  ret = system(command);
  if (ret != 0) {
    return ST_FAILED_TO_RUN_EDITOR;
  }

  return ST_OK;
}
