#ifndef CONSTANTS_H
#define CONSTANTS_H

const char* STORAGE_PATH = "/tmp/shelf/";

const char* NEW_COMMAND_NAME         = "new";
const char* SHOW_COMMAND_NAME        = "show";
const char* REMOVE_COMMAND_NAME      = "remove";
const char* OPEN_EDITOR_COMMAND_NAME = "edit";
const char* LIST_COMMAND_NAME        = "list";

const char* NO_COMMAND_SPECIFIED_ERROR_MESSAGE             = "Please specify a command";
const char* MISSING_SCRATCHPAD_NAME_ERROR_MESSAGE          = "Please specify scratchpad name";
const char* INVALID_COMMANDS_STATUS_NAME_ERROR_MESSAGE     = "Invalid command.";
const char* FAILED_TO_READ_STASH_STATUS_NAME_ERROR_MESSAGE = "Failed to list shelved items.";

#endif // CONSTANTS_H
