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

enum command_type {
  CMD_INVALID,
  CMD_NEW,
  CMD_SHOW,
  CMD_REMOVE,
  CMD_EDIT,
  CMD_LIST,
  CMD_HELP
};

struct command_info {
  enum command_type command_type;
  const char *scratchpad_name;
};

bool cmd_is_0_arg(enum command_type command);
bool cmd_is_1_arg(enum command_type command);

enum status cmd_new(const char *scratchpad_name);
enum status cmd_show(const char *scratchpad_name);
enum status cmd_remove(const char *scratchpad_name);
enum status cmd_edit(const char *scratchpad_name);
enum status cmd_list(void);
void cmd_help(void);

#endif // COMMANDS_H
