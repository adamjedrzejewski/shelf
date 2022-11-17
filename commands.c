#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "commands.h"
#include "status.h"
#include "fs.h"
#include "io.h"

bool is_no_argument_command(command_type_t command) {
    switch (command) {
        case LIST_SCRATCHPADS_COMMAND:
        case HELP_COMMAND:
            return true;
        default:
            return false;
    }
}

status_t create_new_scratchpad(const char* scratchpad_name) { return OK_STATUS; }
status_t show_scratchpad(const char* scratchpad_name) {return OK_STATUS; }
status_t remove_scratchpad(const char* scratchpad_name) {return OK_STATUS; }
status_t edit_scratchpad(const char* scratchpad_name) {return OK_STATUS; }

status_t list_scratchpads(void) {
    DIR *d;
    struct dirent *dir;

    d = opendir(STORAGE_PATH);
    if (!d) {
        return FAILED_TO_READ_STASH_STATUS;
    }

	while ((dir = readdir(d)) != NULL) {
		if (dir->d_type == DT_REG) {
		    puts(dir->d_name);
		}
	}
    closedir(d);

    return OK_STATUS;
}

status_t show_help(void) {
    return write_help_message_to_stdout();
}