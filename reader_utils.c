#include "reader_utils.h"

unsigned int get_line_count(FILE *file) {
    char row[MAX_ROW_LENGTH_U];
    unsigned int file_len = 0;

    /* kontrola parametrů */
    if (!file)
        return 0;

    rewind(file);

    while (fgets(row, MAX_ROW_LENGTH_U, file) != NULL) {
        file_len++;
    }

    rewind(file);

    return file_len;
}
