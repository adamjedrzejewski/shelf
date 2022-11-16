#ifndef TYPES_H
#define TYPES_H

typedef enum {
    INVALID_COMMAND,
    NEW_SCRATCHPAD_COMMAND,
    SHOW_SCRATCHPAD_COMMAND,
    REMOVE_SCRATCHPAD_COMMAND,
    OPEN_EDITOR_ON_SCRATCHPAD_COMMAND,
    LIST_SCRATCHPADS_COMMAND
} command_type_t;

typedef enum {
    OK_STATUS,
    NO_COMMAND_SPECIFIED_STATUS,
    INVALID_COMMAND_STATUS,
    MISSING_SCRATCHPAD_NAME_STATUS,
    FAILED_TO_READ_STASH_STATUS, // missing/empty/unable to read storage
} status_t;

typedef struct {
    command_type_t command_type;
    const char* scratchpad_name;
} command_info_t;

#endif // TYPES_H