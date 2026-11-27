#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <assert.h>

#include "ui.h"

enum file_state_t
{
    FILE_BEGINING,
    FILE_MIDDLE,
    FILE_END
};

FILE* open_file(const char* filename, const char* mode);

void write_beginning_of_file(FILE* report);
// void write_middle_of_file(FILE* report, array_of_trees);
void write_end_of_file(FILE* report);

#endif /* UI_H */
