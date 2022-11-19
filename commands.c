#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "commands.h"
#include "io.h"
#include "status.h"

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
  return ST_OK;
}
status_t cmd_show(const char *scratchpad_name) { return ST_OK; }
status_t cmd_remove(const char *scratchpad_name) { return ST_OK; }
status_t cmd_edit(const char *scratchpad_name) { return ST_OK; }

status_t cmd_list(void) { return ST_OK; }

status_t cmd_help(void) { return write_help_message_to_stdout(); }
