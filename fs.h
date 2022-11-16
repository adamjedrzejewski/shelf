#ifndef FS_H
#define FS_H

#include "types.h"

status_t create_stash();
status_t remove_scratchpad_file(const char* name);

#endif // FS_H