#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdbool.h>

#include "status.h"

static const char *CMD_NEW_NAME = "new";
static const char *CMD_SHOW_NAME = "show";
static const char *CMD_REMOVE_NAME = "remove";
static const char *CMD_EDIT_NAME = "edit";
static const char *CMD_LIST_NAME = "list";
static const char *CMD_HELP_NAME = "help";

typedef enum command_type {
  CMD_INVALID,
  CMD_NEW,
  CMD_SHOW,
  CMD_REMOVE,
  CMD_EDIT,
  CMD_LIST,
  CMD_HELP
} command_type_t;

typedef struct command_info {
  command_type_t command_type;
  const char *scratchpad_name;
} command_info_t;

bool cmd_is_zero_argument_command(command_type_t command);
bool cmd_is_one_argument_command(command_type_t command);

status_t cmd_create_new_scratchpad(const char *scratchpad_name);
status_t cmd_show_scratchpad(const char *scratchpad_name);
status_t cmd_remove_scratchpad(const char *scratchpad_name);
status_t cmd_edit_scratchpad(const char *scratchpad_name);
status_t cmd_list_scratchpads(void);
status_t cmd_show_help(void);

#endif // COMMANDS_H
