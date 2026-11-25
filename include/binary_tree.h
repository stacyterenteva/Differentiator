#ifndef BINARY_TREE_H

#define BINARY_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

const int MAX_STRLEN = 100;

enum TYPE
{
    TYPE_OP,
    TYPE_NUM,
    TYPE_VAR
};

struct tree_node_t
{
    TYPE type;
    int val;
    tree_node_t* left;
    tree_node_t* right;
};

struct tree_t
{
    tree_node_t root;
};

tree_node_t* create_node(TYPE type, int val, tree_node_t* left, tree_node_t* right);
void destroy_tree(tree_node_t* root);
void destroy_node(tree_node_t* node);

void link_right(tree_node_t* parent, tree_node_t* child);
void link_left(tree_node_t* parent, tree_node_t* child);

void node_dump(tree_node_t* node, FILE* graph);
void tree_dump(tree_node_t* node, FILE*  graph);
void dump(tree_node_t* node);

void convert_into_text(tree_node_t* node, FILE* file);
tree_node_t* read_tree(FILE* file);
int read_phrase(char* string, FILE* file);

double count_tree(tree_node_t* node);

tree_node_t* copy_tree(tree_node_t* node_old);
tree_node_t* copy_node(tree_node_t* node);

#endif /* BINARY_TREE_H */
