#include "ui.h"

FILE* open_file(const char* filename, const char* mode)
{
    assert(filename);

    FILE* file = fopen(filename, mode);

    if (file == NULL) {
        perror("Error: ");
    }

    return file;
}

void write_beginning_of_file(FILE* report)
{
    fprintf(report, "\\documentclass[12pt, a4paper]{article}\n"
                   "\\usepackage[utf8]{inputenc}\n"
                   "\\usepackage[T2A]{fontenc}\n"
                   "\\usepackage[russian]{babel}\n"
                   "\\usepackage[left=2.5cm, right=2.5cm, top=2cm, bottom=2cm]{geometry}\n"
                   "\\usepackage{amsmath}\n"
                   "\\usepackage{parskip}\n\n"

                   "\\begin{document}\n"
                   "\\section*{Test dump}\n\n");
}

/*
void write_middle_of_file(FILE* report, array_of_trees)
{
    dump(array_of_trees);
} */

void write_end_of_file(FILE* report)
{
    fprintf(report, "\\end{document}\n");
}



