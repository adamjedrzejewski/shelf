#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmd.h"
#include "io.h"
#include "status.h"

#define foreach(item, array)                                                   \
  for (int keep = 1, count = 0, size = sizeof(array) / sizeof *(array);        \
       keep && count != size; keep = !keep, count++)                           \
    for (item = (array) + count; keep; keep = !keep)

struct defined_command {
  const enum command_type command_type;
  const char **command_name;
};

struct defined_command defined_commands[] = {
    {CMD_HELP, &CMD_HELP_NAME},     {CMD_LIST, &CMD_LIST_NAME},
    {CMD_NEW, &CMD_NEW_NAME},       {CMD_SHOW, &CMD_SHOW_NAME},
    {CMD_REMOVE, &CMD_REMOVE_NAME}, {CMD_EDIT, &CMD_EDIT_NAME},
};

enum status_type parse_command(int argc, const char **argv,
                          struct command_info *command_info) {
  command_info->command_type = CMD_INVALID;
  command_info->scratchpad_name = NULL;

  // if no command specified show help
  if (argc == 1) {
    command_info->command_type = CMD_HELP;

    return ST_OK;
  }

  // match command
  const char *command = argv[1];
  foreach (struct defined_command *defined_command, defined_commands) {
    const char *defined_command_name = *defined_command->command_name;
    enum command_type command_type = defined_command->command_type;

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
  if (cmd_is_0_arg(command_info->command_type)) {
    return ST_OK;
  }

  // commands with argument
  if (argc == 2) {
    return ST_MISSING_ARGUMENT;
  }
  command_info->scratchpad_name = argv[2];

  return ST_OK;
}

int main(int argc, const char **argv) {
  struct command_info command_info;
  enum status_type status = parse_command(argc, argv, &command_info);
  if (status != ST_OK) {
    io_write_error(status);
    exit(1);
  }

  switch (command_info.command_type) {
  case CMD_NEW:
    status = cmd_new(command_info.scratchpad_name);
    break;
  case CMD_SHOW:
    status = cmd_show(command_info.scratchpad_name);
    break;
  case CMD_REMOVE:
    status = cmd_remove(command_info.scratchpad_name);
    break;
  case CMD_EDIT:
    status = cmd_edit(command_info.scratchpad_name);
    break;
  case CMD_LIST:
    status = cmd_list();
    break;
  case CMD_HELP:
    cmd_help();
    status = ST_OK;
    break;

  case CMD_INVALID:
  default:
    break;
  }

  if (status != ST_OK) {
    io_write_error(status);
    exit(1);
  }

  return 0;
}
