#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdbool.h>

#include "status.h"

static const char* NEW_COMMAND_NAME         = "new";
static const char* SHOW_COMMAND_NAME        = "show";
static const char* REMOVE_COMMAND_NAME      = "remove";
static const char* OPEN_EDITOR_COMMAND_NAME = "edit";
static const char* LIST_COMMAND_NAME        = "list";
static const char* HELP_COMMAND_NAME        = "help";

typedef enum command_type {
    INVALID_COMMAND,
    NEW_SCRATCHPAD_COMMAND,
    SHOW_SCRATCHPAD_COMMAND,
    REMOVE_SCRATCHPAD_COMMAND,
    OPEN_EDITOR_ON_SCRATCHPAD_COMMAND,
    LIST_SCRATCHPADS_COMMAND,
    HELP_COMMAND
} command_type_t;

typedef struct command_info {
    command_type_t command_type;
    const char* scratchpad_name;
} command_info_t;

bool is_no_argument_command(command_type_t command);

status_t create_new_scratchpad(const char* scratchpad_name);
status_t show_scratchpad(const char* scratchpad_name);
status_t remove_scratchpad(const char* scratchpad_name);
status_t edit_scratchpad(const char* scratchpad_name);
status_t list_scratchpads(void);
status_t show_help(void);

#endif // COMMANDS_H