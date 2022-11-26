#ifndef STATUS_H
#define STATUS_H

enum status {
  ST_OK,

  // cmd line errors
  ST_CMD_INVALID,
  ST_NO_COMMAND_SPECIFIED,
  ST_MISSING_SCRATCHPAD_NAME,

  ST_FAILED_TO_READ_STASH, // missing/empty/unable to read storage
  ST_FAILED_TO_CREATE_STASH,

  ST_SCRATCHPAD_DOESNT_EXIST,
  ST_FAILED_TO_REMOVE_SCRATCHPAD,

  ST_FAILED_TO_READ_ENVVAR
};

static const char *ST_NO_COMMAND_SPECIFIED_ERROR_MESSAGE =
    "Please specify a command.";
static const char *ST_MISSING_SCRATCHPAD_NAME_ERROR_MESSAGE =
    "Please specify scratchpad name.";
static const char *ST_CMD_INVALID_STATUS_NAME_ERROR_MESSAGE =
    "Invalid command.";
static const char *ST_FAILED_TO_READ_STASH_NAME_ERROR_MESSAGE =
    "Failed to list shelved items.";
static const char *ST_FAILED_TO_CREATE_STASH_ERROR_MESSAGE =
    "Failed to create stash.";
static const char *ST_SCRATCHPAD_DOESNT_EXIST_ERROR_MESSAGE =
    "Scratchpad doesn't exist.";
static const char *ST_FAILED_TO_REMOVE_SCRATCHPAD_ERROR_MESSAGE =
    "Failed to remove scratchpad.";
static const char *ST_FAILED_TO_READ_ENVVAR_ERROR_MESSAGE =
    "Failed to read environment variable.";

#endif // STATUS_H
