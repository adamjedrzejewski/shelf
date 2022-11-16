#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "constants.h"
  
#define BUFFER_SIZE 1024
static const char* STORAGE_PATH = "/tmp/shelf/";

/*

static const char* NEW_COMMAND_NAME         = "new";
static const char* SHOW_COMMAND_NAME        = "show";
static const char* REMOVE_COMMAND_NAME      = "remove";
static const char* OPEN_EDITOR_COMMAND_NAME = "edit";
static const char* LIST_COMMAND_NAME        = "list";


static const char* NO_COMMAND_SPECIFIED_ERROR_MESSAGE             = "Please specify a command\n";
static const char* MISSING_SCRATCHPAD_NAME_ERROR_MESSAGE          = "Please specify scratchpad name\n";
static const char* INVALID_COMMANDS_STATUS_NAME_ERROR_MESSAGE     = "Invalid command.\n";
static const char* FAILED_TO_READ_STASH_STATUS_NAME_ERROR_MESSAGE = "Failed to list shelved items.\n";
*/


typedef enum {
    INVALID_COMMAND,
    NEW_SCRATCHPAD,
    SHOW_SCRATCHPAD,
    REMOVE_SCRATCHPAD,
    OPEN_EDITOR_ON_SCRATCHPAD,
    LIST_SCRATCHPADS
} command_type_t;

typedef enum {
    OK,
    NO_COMMAND_SPECIFIED,
    INVALID_COMMAND_STATUS,
    MISSING_SCRATCHPAD_NAME_STATUS,
    FAILED_TO_READ_STASH_STATUS, // missing/empty/unable to read storage
} status_t;

typedef struct {
    command_type_t command;
    const char* scratchpad_name;
} command_info_t;


status_t create_new_scratchpad(const char* scratchpad_name) { return OK; }
status_t show_scratchpad(const char* scratchpad_name) {return OK; }
status_t remove_scratchpad(const char* scratchpad_name) {return OK; }
status_t edit_scratchpad(const char* scratchpad_name) {return OK; }

status_t list_scratchpads(void) {
    DIR *d;
    struct dirent *dir;

    d = opendir(STORAGE_PATH);
    if (!d) {
        return FAILED_TO_READ_STASH_STATUS;
    }

	while ((dir = readdir(d)) != NULL) {
		if (dir->d_type == DT_REG) {
		printf("%s\n", dir->d_name);
		}
	}
    closedir(d);

    return OK;
}


void write_error(status_t error) {
    const char* error_message;
    switch (error) {
        case NO_COMMAND_SPECIFIED:
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
}

status_t parse_command(int argc, const char** argv, command_info_t* command_info) {
    command_info->command = INVALID_COMMAND;
    command_info->scratchpad_name = NULL;

    if (argc == 1) {
        return NO_COMMAND_SPECIFIED;
    }

    const char* command = argv[1];
    if (strcmp(command, LIST_COMMAND_NAME) == 0) {
        command_info->command = LIST_SCRATCHPADS;
        return OK;
    }

    if (strcmp(command, NEW_COMMAND_NAME) == 0) {
        command_info->command = NEW_SCRATCHPAD;
    }
    if (strcmp(command, SHOW_COMMAND_NAME) == 0) {
        command_info->command = SHOW_SCRATCHPAD;
    }
    if (strcmp(command, REMOVE_COMMAND_NAME) == 0) {
        command_info->command = REMOVE_SCRATCHPAD;
    }
    if (strcmp(command, OPEN_EDITOR_COMMAND_NAME) == 0) {
        command_info->command = OPEN_EDITOR_ON_SCRATCHPAD;
    }
 
    if (command_info->command == INVALID_COMMAND) {
        return INVALID_COMMAND_STATUS;
    }

    if (argc == 2) {
        return MISSING_SCRATCHPAD_NAME_STATUS;
    }
    command_info->scratchpad_name = argv[2];

    return OK;
}


int main(int argc, const char** argv) {
    command_info_t command_info = {};
    status_t status = parse_command(argc, argv, &command_info);
    if (status != OK) {
      write_error(status);
      exit(1);
    }

    switch (command_info.command) {
        case NEW_SCRATCHPAD:
            status = create_new_scratchpad(command_info.scratchpad_name);
            break;
        case SHOW_SCRATCHPAD:
            status = show_scratchpad(command_info.scratchpad_name);
            break;
        case REMOVE_SCRATCHPAD:
            status = remove_scratchpad(command_info.scratchpad_name);
            break;
        case OPEN_EDITOR_ON_SCRATCHPAD:
            status = edit_scratchpad(command_info.scratchpad_name);
            break;
        case LIST_SCRATCHPADS:
            status = list_scratchpads();
            break;
        default:
            break;
    }

    if (status != OK) {
        write_error(status);
        exit(1);
    }

    printf("%d\n", command_info.command);
    return 0;

    char* buffer = malloc(sizeof(char) * BUFFER_SIZE);
    while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        fputs(buffer, stdout);
    }
}

