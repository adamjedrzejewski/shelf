#ifndef STATUS_H
#define STATUS_H

typedef enum status {
  ST_OK,

  // cmd line errors
  ST_CMD_INVALID,
  ST_NO_COMMAND_SPECIFIED,
  ST_MISSING_SCRATCHPAD_NAME,

  ST_FAILED_TO_READ_STASH, // missing/empty/unable to read storage
  ST_FAILED_TO_CREATE_STASH,

  ST_FAILED_TO_READ_ENVVAR
} status_t;

static const char *ST_NO_COMMAND_SPECIFIED_ERROR_MESSAGE =
    "Please specify a command.";
static const char *ST_MISSING_SCRATCHPAD_NAME_ERROR_MESSAGE =
    "Please specify scratchpad name.";
static const char *ST_CMD_INVALIDS_STATUS_NAME_ERROR_MESSAGE =
    "Invalid command.";
static const char *ST_FAILED_TO_READ_STASH_NAME_ERROR_MESSAGE =
    "Failed to list shelved items.";

#endif // STATUS_H
