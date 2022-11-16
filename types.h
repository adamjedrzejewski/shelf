#ifndef TYPES_H
#define TYPES_H

typedef enum command_type {
    INVALID_COMMAND,
    NEW_SCRATCHPAD_COMMAND,
    SHOW_SCRATCHPAD_COMMAND,
    REMOVE_SCRATCHPAD_COMMAND,
    OPEN_EDITOR_ON_SCRATCHPAD_COMMAND,
    LIST_SCRATCHPADS_COMMAND
} command_type_t;

typedef enum status {
    OK_STATUS,

    // cmd line errors
    INVALID_COMMAND_STATUS,
    NO_COMMAND_SPECIFIED_STATUS,
    MISSING_SCRATCHPAD_NAME_STATUS,

    FAILED_TO_READ_STASH_STATUS, // missing/empty/unable to read storage
    FAILED_TO_CREATE_STASH,
} status_t;

typedef struct command_info {
    command_type_t command_type;
    const char* scratchpad_name;
} command_info_t;

#endif // TYPES_H