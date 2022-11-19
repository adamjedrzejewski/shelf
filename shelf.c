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
    {.command_type = CMD_HELP, .command_name = &CMD_HELP_NAME},
    {.command_type = CMD_LIST,
     .command_name = &CMD_LIST_NAME},
    {.command_type = CMD_NEW, .command_name = &CMD_NEW_NAME},
    {.command_type = CMD_SHOW,
     .command_name = &CMD_SHOW_NAME},
    {.command_type = CMD_REMOVE,
     .command_name = &CMD_REMOVE_NAME},
    {.command_type = CMD_EDIT,
     .command_name = &CMD_EDIT_NAME},
};

// TODO move to io
void write_error(status_t error) {
  const char *error_message;
  switch (error) {
  case ST_NO_COMMAND_SPECIFIED:
    error_message = ST_NO_COMMAND_SPECIFIED_ERROR_MESSAGE;
    break;
  case ST_MISSING_SCRATCHPAD_NAME:
    error_message = ST_MISSING_SCRATCHPAD_NAME_ERROR_MESSAGE;
    break;
  case ST_CMD_INVALID:
    error_message = ST_CMD_INVALIDS_STATUS_NAME_ERROR_MESSAGE;
    break;
  case ST_FAILED_TO_READ_STASH:
    error_message = ST_FAILED_TO_READ_STASH_NAME_ERROR_MESSAGE;
    break;
  default:
    return;
  }

  fputs(error_message, stderr);
  fputs("\n", stderr);
}

status_t parse_command(int argc, const char **argv,
                       command_info_t *command_info) {
  command_info->command_type = CMD_INVALID;
  command_info->scratchpad_name = NULL;

  if (argc == 1) {
    return ST_NO_COMMAND_SPECIFIED;
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
  if (command_info->command_type == CMD_INVALID) {
    return ST_CMD_INVALID;
  }

  // exit on command with no arguments
  if (cmd_is_zero_argument_command(command_info->command_type)) {
    return ST_OK;
  }

  // commands with argument
  if (argc == 2) {
    return ST_MISSING_SCRATCHPAD_NAME;
  }
  printf("scratch that");
  command_info->scratchpad_name = argv[2];

  return ST_OK;
}

int main(int argc, const char **argv) {
  command_info_t command_info = {};
  status_t status = parse_command(argc, argv, &command_info);
  if (status != ST_OK) {
    write_error(status);
    exit(1);
  }

  switch (command_info.command_type) {
  case CMD_NEW:
    status = cmd_create_new_scratchpad(command_info.scratchpad_name);
    break;
  case CMD_SHOW:
    status = cmd_show_scratchpad(command_info.scratchpad_name);
    break;
  case CMD_REMOVE:
    status = cmd_remove_scratchpad(command_info.scratchpad_name);
    break;
  case CMD_EDIT:
    status = cmd_edit_scratchpad(command_info.scratchpad_name);
    break;
  case CMD_LIST:
    status = cmd_list_scratchpads();
    break;
  case CMD_HELP:
    status = cmd_show_help();

  case CMD_INVALID:
  default:
    break;
  }

  if (status != ST_OK) {
    write_error(status);
    exit(1);
  }

  printf("%d\n", command_info.command_type);
  return 0;
}
