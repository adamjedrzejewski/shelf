#include <sys/stat.h>
#include <sys/types.h>

#include "status.h"
#include "fs.h"

status_t create_stash() {
    int err = mkdir(STORAGE_PATH, 0777);

    return err == 0 ? OK_STATUS : FAILED_TO_CREATE_STASH;
}

status_t remove_scratchpad_file(const char* name) {
    return OK_STATUS;
}
