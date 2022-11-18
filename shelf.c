#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "io.h"
#include "status.h"

#define foreach(item, array)                                                   \
  for (int keep = 1, count = 0, size = sizeof(array) / sizeof *(array);        \
       keep && count != size; keep = !keep, count++)                           \
    for (item = (array) + count; keep; keep = !keep)

typedef const struct {
  const command_type_t command_type;
  const char **command_name;
} defined_command_t;

defined_command_t defined_commands[] = {
    {.command_type = HELP_COMMAND, .command_name = &HELP_COMMAND_NAME},
    {.command_type = LIST_SCRATCHPADS_COMMAND,
     .command_name = &LIST_COMMAND_NAME},
    {.command_type = NEW_SCRATCHPAD_COMMAND, .command_name = &NEW_COMMAND_NAME},
    {.command_type = SHOW_SCRATCHPAD_COMMAND,
     .command_name = &SHOW_COMMAND_NAME},
    {.command_type = REMOVE_SCRATCHPAD_COMMAND,
     .command_name = &REMOVE_COMMAND_NAME},
    {.command_type = OPEN_EDITOR_ON_SCRATCHPAD_COMMAND,
     .command_name = &OPEN_EDITOR_COMMAND_NAME},
};

// TODO move to io
void write_error(status_t error) {
  const char *error_message;
  switch (error) {
  case NO_COMMAND_SPECIFIED_STATUS:
    error_message = NO_COMMAND_SPECIFIED_ERROR_MESSAGE;
    break;
  case MISSING_SCRATCHPAD_NAME_STATUS:
    error_message = MISSING_SCRATCHPAD_NAME_ERROR_MESSAGE;
    break;
  case INVALID_COMMAND_STATUS:
    error_message = INVALID_COMMANDS_STATUS_NAME_ERROR_MESSAGE;
    break;
  case FAILED_TO_READ_STASH_STATUS:
    error_message = FAILED_TO_READ_STASH_STATUS_NAME_ERROR_MESSAGE;
    break;
  default:
    return;
  }

  fputs(error_message, stderr);
  fputs("\n", stderr);
}

status_t parse_command(int argc, const char **argv,
                       command_info_t *command_info) {
  command_info->command_type = INVALID_COMMAND;
  command_info->scratchpad_name = NULL;

  if (argc == 1) {
    return NO_COMMAND_SPECIFIED_STATUS;
  }

  // match command
  const char *command = argv[1];
  foreach (defined_command_t *defined_command, defined_commands) {
    const char *defined_command_name = *defined_command->command_name;
    command_type_t command_type = defined_command->command_type;

    if (strcmp(command, defined_command_name) == 0) {
      command_info->command_type = command_type;
      break;
    }
  }

  // invalid command
  if (command_info->command_type == INVALID_COMMAND) {
    return INVALID_COMMAND_STATUS;
  }

  // exit on command with no arguments
  if (is_no_argument_command(command_info->command_type)) {
    return OK_STATUS;
  }

  // commands with argument
  if (argc == 2) {
    return MISSING_SCRATCHPAD_NAME_STATUS;
  }
  command_info->scratchpad_name = argv[2];

  return OK_STATUS;
}

int main(int argc, const char **argv) {
  command_info_t command_info = {};
  status_t status = parse_command(argc, argv, &command_info);

  switch (command_info.command_type) {
  case NEW_SCRATCHPAD_COMMAND:
    status = create_new_scratchpad(command_info.scratchpad_name);
    break;
  case SHOW_SCRATCHPAD_COMMAND:
    status = show_scratchpad(command_info.scratchpad_name);
    break;
  case REMOVE_SCRATCHPAD_COMMAND:
    status = remove_scratchpad(command_info.scratchpad_name);
    break;
  case OPEN_EDITOR_ON_SCRATCHPAD_COMMAND:
    status = edit_scratchpad(command_info.scratchpad_name);
    break;
  case LIST_SCRATCHPADS_COMMAND:
    status = list_scratchpads();
    break;
  case HELP_COMMAND:
    status = show_help();

  case INVALID_COMMAND:
  default:
    break;
  }

  if (status != OK_STATUS) {
    write_error(status);
    exit(1);
  }

  printf("%d\n", command_info.command_type);
  return 0;
}
