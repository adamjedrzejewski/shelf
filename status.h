#ifndef STATUS_H
#define STATUS_H

typedef enum status {
  OK_STATUS,

  // cmd line errors
  INVALID_COMMAND_STATUS,
  NO_COMMAND_SPECIFIED_STATUS,
  MISSING_SCRATCHPAD_NAME_STATUS,

  FAILED_TO_READ_STASH_STATUS, // missing/empty/unable to read storage
  FAILED_TO_CREATE_STASH,
} status_t;

static const char *NO_COMMAND_SPECIFIED_ERROR_MESSAGE =
    "Please specify a command.";
static const char *MISSING_SCRATCHPAD_NAME_ERROR_MESSAGE =
    "Please specify scratchpad name.";
static const char *INVALID_COMMANDS_STATUS_NAME_ERROR_MESSAGE =
    "Invalid command.";
static const char *FAILED_TO_READ_STASH_STATUS_NAME_ERROR_MESSAGE =
    "Failed to list shelved items.";

#endif // STATUS_H