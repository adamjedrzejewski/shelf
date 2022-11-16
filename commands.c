#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

#include "commands.h"
#include "types.h"
#include "constants.h"

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