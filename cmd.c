#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cmd.h"
#include "io.h"
#include "status.h"

static const char *EDITOR_ENV_VAR_NAME = "EDITOR";
static const char *VISUAL_ENV_VAR_NAME = "VISUAL";

bool cmd_is_0_arg(enum command_type command) {
  switch (command) {
  case CMD_LIST:
  case CMD_HELP:
    return true;
  default:
    return false;
  }
}

bool cmd_is_1_arg(enum command_type command) {
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

enum status cmd_new(const char *scratchpad_name) {
  enum status status = io_create_stash_if_nonexistent();

  if (status != ST_OK) {
    return status;
  }

  status = io_write_from_stdin_to_file(scratchpad_name);

  return status;
}

enum status cmd_show(const char *scratchpad_name) {
  enum status status = io_write_from_file_to_stdout(scratchpad_name);

  return status;
}

enum status cmd_remove(const char *scratchpad_name) {
  enum status status = io_remove_file(scratchpad_name);

  return status;
}
enum status cmd_edit(const char *scratchpad_name) {
  char *editor;

  enum status status = io_getenv(EDITOR_ENV_VAR_NAME, &editor);

  // if failed to read EDITOR value, let's try with visual
  if (status == ST_FAILED_TO_READ_ENVVAR) {
    status = io_getenv(VISUAL_ENV_VAR_NAME, &editor);
  }
  if (status != ST_OK) {
    // TODO change to status failed to run editor
    return status;
  }

  status = io_run_editor_on_file(editor, scratchpad_name);

  return status;
}

enum status cmd_list(void) {
  enum status status = io_list_files_in_stash();

  return status;
}

enum status cmd_help(void) {
  io_write_help_message();
  return ST_OK;
}
