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


bool is_neutral_one(tree_node_t* node, func_num_t operation, bool* is_num_in_left) {
    bool is_one_in_right = is_op(node) && node->val == (int) operation && is_num(node->right) && node->right->val == 1;
    bool is_one_in_left = is_op(node) && node->val == (int) operation && is_num(node->left) && node->left->val == 1;

    if (is_one_in_left) {
        *is_num_in_left = true;
        return true;
    }

    else if (is_one_in_right) {
        *is_num_in_left = false;
        return true;
    }

    else {
        return false;
    }
}


/*
bool is_neutral_zero(
*/
