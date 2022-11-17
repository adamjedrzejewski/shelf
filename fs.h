#ifndef FS_H
#define FS_H

#include "status.h"

static const char* STORAGE_PATH = "/tmp/shelf/";

status_t create_stash();
status_t remove_scratchpad_file(const char* name);

#endif // FS_H