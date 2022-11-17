#ifndef CONSTANTS_H
#define CONSTANTS_H

static const char* STORAGE_PATH = "/tmp/shelf/";

static const char* NEW_COMMAND_NAME         = "new";
static const char* SHOW_COMMAND_NAME        = "show";
static const char* REMOVE_COMMAND_NAME      = "remove";
static const char* OPEN_EDITOR_COMMAND_NAME = "edit";
static const char* LIST_COMMAND_NAME        = "list";
static const char* HELP_COMMAND_NAME        = "help";

static const char* NO_COMMAND_SPECIFIED_ERROR_MESSAGE             = "Please specify a command.";
static const char* MISSING_SCRATCHPAD_NAME_ERROR_MESSAGE          = "Please specify scratchpad name.";
static const char* INVALID_COMMANDS_STATUS_NAME_ERROR_MESSAGE     = "Invalid command.";
static const char* FAILED_TO_READ_STASH_STATUS_NAME_ERROR_MESSAGE = "Failed to list shelved items.";

#endif // CONSTANTS_H
