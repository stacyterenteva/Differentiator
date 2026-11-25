#include "../include/dsl.h"

bool is_op(tree_node_t* node) {
    return node->type == TYPE_OP;
}

bool is_num(tree_node_t* node) {
    return node->type == TYPE_NUM;
}

bool is_var(tree_node_t* node) {
    return node->type == TYPE_VAR;
}
