#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "constants.h"
#include "types.h"
  
#define BUFFER_SIZE 1024


void write_error(status_t error) {
    const char* error_message;
    switch (error) {
        case NO_COMMAND_SPECIFIED_STATUS:
            error_message = NO_COMMAND_SPECIFIED_ERROR_MESSAGE;
            break;
        case MISSING_SCRATCHPAD_NAME_STATUS:
            error_message = MISSING_SCRATCHPAD_NAME_ERROR_MESSAGE;
            break;
        case INVALID_COMMAND_STATUS:
            error_message = INVALID_COMMANDS_STATUS_NAME_ERROR_MESSAGE;
            break;
        case FAILED_TO_READ_STASH_STATUS:
            error_message = FAILED_TO_READ_STASH_STATUS_NAME_ERROR_MESSAGE;
            break;
        default: return;
    }

    fputs(error_message, stderr);
    fputs("\n", stderr);
}

status_t parse_command(int argc, const char** argv, command_info_t* command_info) {
    command_info->command_type = INVALID_COMMAND;
    command_info->scratchpad_name = NULL;

    if (argc == 1) {
        return NO_COMMAND_SPECIFIED_STATUS;
    }

    const char* command = argv[1];
    if (strcmp(command, LIST_COMMAND_NAME) == 0) {
        command_info->command_type = LIST_SCRATCHPADS_COMMAND;
        return OK_STATUS;
    }

    if (strcmp(command, NEW_COMMAND_NAME) == 0) {
        command_info->command_type = NEW_SCRATCHPAD_COMMAND;
    }
    if (strcmp(command, SHOW_COMMAND_NAME) == 0) {
        command_info->command_type = SHOW_SCRATCHPAD_COMMAND;
    }
    if (strcmp(command, REMOVE_COMMAND_NAME) == 0) {
        command_info->command_type = REMOVE_SCRATCHPAD_COMMAND;
    }
    if (strcmp(command, OPEN_EDITOR_COMMAND_NAME) == 0) {
        command_info->command_type = OPEN_EDITOR_ON_SCRATCHPAD_COMMAND;
    }
 
    if (command_info->command_type == INVALID_COMMAND) {
        return INVALID_COMMAND_STATUS;
    }

    if (argc == 2) {
        return MISSING_SCRATCHPAD_NAME_STATUS;
    }
    command_info->scratchpad_name = argv[2];

    return OK_STATUS;
}


int main(int argc, const char** argv) {
    command_info_t command_info = {};
    status_t status = parse_command(argc, argv, &command_info);
    if (status != OK_STATUS) {
      write_error(status);
      exit(1);
    }

    switch (command_info.command_type) {
        case NEW_SCRATCHPAD_COMMAND:
            status = create_new_scratchpad(command_info.scratchpad_name);
            break;
        case SHOW_SCRATCHPAD_COMMAND:
            status = show_scratchpad(command_info.scratchpad_name);
            break;
        case REMOVE_SCRATCHPAD_COMMAND:
            status = remove_scratchpad(command_info.scratchpad_name);
            break;
        case OPEN_EDITOR_ON_SCRATCHPAD_COMMAND:
            status = edit_scratchpad(command_info.scratchpad_name);
            break;
        case LIST_SCRATCHPADS_COMMAND:
            status = list_scratchpads();
            break;
        default:
            break;
    }

    if (status != OK_STATUS) {
        write_error(status);
        exit(1);
    }

    printf("%d\n", command_info.command_type);
    return 0;

    char* buffer = malloc(sizeof(char) * BUFFER_SIZE);
    while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        fputs(buffer, stdout);
    }
}

