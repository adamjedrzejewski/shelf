#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "commands.h"
#include "io.h"
#include "status.h"

bool is_no_argument_command(command_type_t command) {
  switch (command) {
  case LIST_SCRATCHPADS_COMMAND:
  case HELP_COMMAND:
    return true;
  default:
    return false;
  }
}

bool is_one_argument_command(command_type_t command) {
  switch (command) {
  case NEW_SCRATCHPAD_COMMAND:
  case SHOW_SCRATCHPAD_COMMAND:
  case REMOVE_SCRATCHPAD_COMMAND:
  case OPEN_EDITOR_ON_SCRATCHPAD_COMMAND:
    return true;
  default:
    return false;
  }
}

status_t create_new_scratchpad(const char *scratchpad_name) {
  return OK_STATUS;
}
status_t show_scratchpad(const char *scratchpad_name) { return OK_STATUS; }
status_t remove_scratchpad(const char *scratchpad_name) { return OK_STATUS; }
status_t edit_scratchpad(const char *scratchpad_name) { return OK_STATUS; }

status_t list_scratchpads(void) { return OK_STATUS; }

status_t show_help(void) { return write_help_message_to_stdout(); }
