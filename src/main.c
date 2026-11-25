#include <stdio.h>
#include "binary_tree.h"
#include "dsl.h"
#include "diff.h"

//FIXME github

int main() //FIXME cmdLine args
{
    FILE* file = fopen("data/add.txt", "r");
    assert(file);

    FILE* file_for_dump = open_dump_file();  //openFile
    assert(file_for_dump);

    tree_node_t* root = read_tree(file);
    dump(root);

    fprintf(file_for_dump, "$$");

    text_dump(root, file_for_dump);

    fprintf(file_for_dump, "$$");
    fprintf(file_for_dump, "\n\n");

    tree_node_t* root_copy = copy_tree(root);
    dump(root_copy);

    tree_node_t* root_diff = diff(root_copy);
    dump(root_diff);


    //
    fprintf(file_for_dump, "$$");

    text_dump(root_diff, file_for_dump);

    fprintf(file_for_dump, "$$");
    fprintf(file_for_dump, "\n\n");
    //

    close_dump_file(file_for_dump);
    system("pdflatex data/text_dump.tex");

    destroy_tree(root_diff);
    destroy_tree(root_copy);
    destroy_tree(root);

    fclose(file);
}
