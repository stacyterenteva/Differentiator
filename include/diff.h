#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include "binary_tree.h"
#include "dsl.h"

// git!!!

tree_node_t* diff(tree_node_t* node);

tree_node_t* count_num_tree(tree_node_t* node);
tree_node_t* erase_neutral_nodes(tree_node_t* node);

void text_dump(tree_node_t* node, FILE* file);

#endif
