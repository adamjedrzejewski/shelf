#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "status.h"
#include "stdio.h"

#define BUFFER_SIZE 256

static const char *STORAGE_PATH = "/tmp/shelf/";

status_t continious_write_to_scratchpad(const char *name) {
  FILE *file;
  file = fopen("test.o", "w");

  char buffer[BUFFER_SIZE] = {};
  while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
    fputs(buffer, file);
  }

  fclose(file);

  return ST_OK;
}

status_t write_help_message_to_stdout(void) { return ST_OK; }

status_t create_stash() {
  int err = mkdir(STORAGE_PATH, 0777);

  return err == 0 ? ST_OK : ST_FAILED_TO_CREATE_STASH;
}

status_t remove_scratchpad_file(const char *name) { return ST_OK; }

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
