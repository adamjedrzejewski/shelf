#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "commands.h"
#include "io.h"
#include "status.h"

static const char *EDITOR_ENV_VAR_NAME = "EDITOR";
static const char *VISUAL_ENV_VAR_NAME = "VISUAL";

bool cmd_is_0_arg(command_type_t command) {
  switch (command) {
  case CMD_LIST:
  case CMD_HELP:
    return true;
  default:
    return false;
  }
}

bool cmd_is_1_arg(command_type_t command) {
  switch (command) {
  case CMD_NEW:
  case CMD_SHOW:
  case CMD_REMOVE:
  case CMD_EDIT:
    return true;
  default:
    return false;
  }
}

status_t cmd_new(const char *scratchpad_name) {
  status_t status = io_create_stash_if_nonexistent();

  if (status != ST_OK) {
    return status;
  }

  status = io_write_from_stdin_to_file(scratchpad_name);

  return status;
}

status_t cmd_show(const char *scratchpad_name) {
  status_t status = io_write_from_file_to_stdout(scratchpad_name);

  return status;
}

status_t cmd_remove(const char *scratchpad_name) {
  status_t status = io_remove_file(scratchpad_name);

  return status;
}
status_t cmd_edit(const char *scratchpad_name) {
  char *editor;

  status_t status = io_getenv(EDITOR_ENV_VAR_NAME, editor);

  // if failed to read EDITOR value, let's try with visual
  if (status == ST_FAILED_TO_READ_ENVVAR) {
    status = io_getenv(VISUAL_ENV_VAR_NAME, editor);
  }
  if (status != ST_OK) {
    return status;
  }

  status = io_run_editor_on_file(editor, scratchpad_name);

  return status;
}

status_t cmd_list(void) {
  status_t status = io_list_files_in_stash();

  return status;
}

status_t cmd_help(void) {
  io_write_help_message();
  return ST_OK;
}
