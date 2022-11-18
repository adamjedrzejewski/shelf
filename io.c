#include <stdlib.h>

#include "status.h"
#include "stdio.h"
#include "fs.h"

#define BUFFER_SIZE 256

status_t continious_write_to_scratchpad(const char* name) {
    FILE *file;
    file = fopen("test.o", "w");

    char buffer[BUFFER_SIZE] = {};
    while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        fputs(buffer, file);
    }

    fclose(file);

    return OK_STATUS;
}

status_t write_help_message_to_stdout(void) {
    return OK_STATUS;
}