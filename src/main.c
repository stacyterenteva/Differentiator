#include <stdio.h>
#include <string.h>

#include "binary_tree.h"
#include "dsl.h"
#include "diff.h"
#include "ui.h"

enum argv_state_t
{
    ARGV_STATE_SUCCESS,
    ARGV_STATE_NO_ARGUMENTS,
    ARGV_STATE_TOO_MANY_ARGUMENTS,
    ARGV_STATE_HELP
};

argv_state_t process_argv(int argc, char* argv[], const char** filename);
void process_argv_state(argv_state_t state);

int main(int argc, char* argv[])
{
    const char* filename = NULL;

    argv_state_t filename_state = process_argv(argc, argv, &filename);
    if (filename_state != ARGV_STATE_SUCCESS) {
        process_argv_state(filename_state);
        return 1;
    }

    FILE* expression = open_file(filename, "r");
    if (expression == NULL) {
        return 1;
    }

    FILE* report = open_file("data/report.tex", "a");
    if (expression == NULL) {
        return 1;
    }

    write_beginning_of_file(report);

    tree_node_t* root = read_tree(expression);
    assert(root);

    fclose(expression);

    dump(root);

    fprintf(report, "$$");

    text_dump(root, report);

    fprintf(report, "$$");
    fprintf(report, "\n\n");

    tree_node_t* root_copy = copy_tree(root);

    tree_node_t* root_diff = diff(root_copy);
    dump(root_diff);

    erase_neutral_nodes(&root_diff);
    dump(root_diff);


//TODO: normalni dump
    //
    fprintf(report, "$$");

    text_dump(root_diff, report);

    fprintf(report, "$$");
    fprintf(report, "\n\n");
    //

    write_end_of_file(report);

    fclose(report);
    system("pdflatex data/report.tex");

    // destroy_tree(root_diff);
    // destroy_tree(root_copy);
    // destroy_tree(root);
}

argv_state_t process_argv(int argc, char* argv[], const char** filename)
{
    if (argc == 1) {
        return ARGV_STATE_NO_ARGUMENTS;
    }

    else if (argc == 2) {
        *filename = argv[1];
        if (strcmp(*filename, "--help") == 0) {
            return ARGV_STATE_HELP;
        }
        return ARGV_STATE_SUCCESS;
    }
    else {
        return ARGV_STATE_TOO_MANY_ARGUMENTS;
    }
}

void process_argv_state(argv_state_t state)
{
    if (state == ARGV_STATE_NO_ARGUMENTS) {
        printf("Error: no arguments\n");
        printf("Enter --help to find out the correct input format\n");
        return;
    }
    else if (state == ARGV_STATE_TOO_MANY_ARGUMENTS) {
        printf("Error: too many arguments\n");
        printf("Enter --help to find out the correct input format\n");
        return;
    }
    else {
        printf("Create a file with expression you want to differentiate\n");
        printf("Run the program by entering: ./diff.exe <your file>\n");

        return;
    }
}
