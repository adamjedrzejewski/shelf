#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cmd.h"
#include "io.h"
#include "status.h"

static const char *EDITOR_ENV_VAR_NAME = "EDITOR";
static const char *VISUAL_ENV_VAR_NAME = "VISUAL";

bool cmd_is_0_arg(enum command_type command) {
  return command == CMD_LIST || command == CMD_HELP;
}

bool cmd_is_1_arg(enum command_type command) {
  return command == CMD_NEW || command == CMD_SHOW || command == CMD_REMOVE ||
         command == CMD_EDIT;
}

enum status_type cmd_new(const char *scratchpad_name) {
  enum status_type status = io_create_stash_if_nonexistent();

  if (status != ST_OK) {
    return status;
  }

  status = io_write_from_stdin_to_file(scratchpad_name);

  return status;
}

enum status_type cmd_show(const char *scratchpad_name) {
  enum status_type status = io_write_from_file_to_stdout(scratchpad_name);

  return status;
}

enum status_type cmd_remove(const char *scratchpad_name) {
  enum status_type status = io_remove_file(scratchpad_name);

  return status;
}
enum status_type cmd_edit(const char *scratchpad_name) {
  char *editor;
  enum status_type status_type;

  editor = getenv(EDITOR_ENV_VAR_NAME);

  // if failed to read EDITOR value, let's try with VISUAL
  if (editor == NULL) {
    editor = getenv(VISUAL_ENV_VAR_NAME);
  }
  if (editor == NULL) {
    return ST_FAILED_TO_READ_ENVVAR;
  }

  status_type = io_run_editor_on_file(editor, scratchpad_name);

  return status_type;
}

enum status_type cmd_list(void) {
  enum status_type status = io_list_files_in_stash();

  return status;
}

void cmd_help(void) { io_write_help_message(); }
