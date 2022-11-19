#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "commands.h"
#include "io.h"
#include "status.h"

bool cmd_is_zero_argument_command(command_type_t command) {
  switch (command) {
  case CMD_LIST:
  case CMD_HELP:
    return true;
  default:
    return false;
  }
}

bool cmd_is_one_argument_command(command_type_t command) {
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

status_t cmd_create_new_scratchpad(const char *scratchpad_name) {
  return ST_OK;
}
status_t cmd_show_scratchpad(const char *scratchpad_name) { return ST_OK; }
status_t cmd_remove_scratchpad(const char *scratchpad_name) { return ST_OK; }
status_t cmd_edit_scratchpad(const char *scratchpad_name) { return ST_OK; }

status_t cmd_list_scratchpads(void) { return ST_OK; }

status_t cmd_show_help(void) { return write_help_message_to_stdout(); }
