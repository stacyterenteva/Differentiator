#include "../include/diff.h"

tree_node_t* diff(tree_node_t* node)
{
    assert(node);

    // TODO: use switch
    if (node->type == TYPE_VAR) {
        return NUM(1);
    }
    else if (node->type == TYPE_NUM) {
        return NUM(0);
    }
    else if (node->type == TYPE_OP) {
        // TODO: dsl for copy_tree(node->left)
        tree_node_t* left = copy_tree(node->left);
        tree_node_t* right = copy_tree(node->right);
        tree_node_t* node_copy = copy_tree(node);
        if (node->val == FUNC_MUL) {
            return ADD(MUL(diff(left), right), MUL(diff(right), left));
        }
        else if (node->val == FUNC_ADD) {
            return ADD(diff(left), diff(right));
        }
        else if (node->val == FUNC_SUB) {
            return SUB(diff(left), diff(right));
        }
        else if (node->val == FUNC_DIV) {
            tree_node_t* right1 = copy_tree(right);
            tree_node_t* right2 = copy_tree(right);
            return DIV(SUB(MUL(diff(left), right), MUL(diff(right), left)), MUL(right1, right2));
        }
        else if (node->val == FUNC_SIN) {
            return MUL(COS(right), diff(right));
        }
        else if (node->val == FUNC_COS) {
            return MUL(MUL(SIN(right), NUM(-1)), diff(right));
        }
        else if (node->val == FUNC_POW) {
            if (is_var(node->left) && is_num(node->right)) {
                return MUL(MUL(NUM(right->val), POW(left, right->val - 1)), diff(left));
            }
            else if (is_num(node->left) && is_var(node->right)) {
                return MUL(MUL(node_copy, LN(left)), diff(right));
            }
            else if (is_var(node->left) && is_var(node->right)) {
                tree_node_t* right_new = copy_tree(right);
                tree_node_t* left_new = copy_tree(left);
                return MUL(node_copy, ADD(MUL(diff(left_new), LN(right)), MUL(left, DIV(diff(right_new), right))));
            }
        }
    }

    return NULL;
}


/*
tree_node_t* count_num_tree(tree_node_t* node)
{
    assert(node);

    if (
} */

void text_dump(tree_node_t* node, FILE* file)
{
    assert(node);

    if (is_op(node) && node->val == FUNC_DIV) {
        printf("DIV\n");
        fprintf(file, "\\frac{");
        text_dump(node->left, file);
        fprintf(file, "}{");
        text_dump(node->right, file);
        fprintf(file, "}");
        return;
    }

    else {

        //fprintf(file, "(");
        fprintf(file, " ");

        if (node->left != NULL) {
            text_dump(node->left, file);
        }

        switch (node->type) {
            case TYPE_OP: {
                if (node->val == FUNC_MUL) {
                    fprintf(file, " \\cdot");
                }

                else if (node->val == FUNC_SIN) {
                    fprintf(file, " \\sin");
                }
                else if (node->val == FUNC_COS) {
                    fprintf(file, " \\cos");
                }
                else if (node->val == FUNC_TG) {
                    fprintf(file, " \\tan");
                }
                else if (node->val == FUNC_LN) {
                    fprintf(file, " \\ln");
                }

                else {
                    fprintf(file, "%s", list_of_funcs[node->val].func_name);
                }
                break;
            }
            case TYPE_NUM: {
                fprintf(file, "%d", node->val);
                break;
            }
            case TYPE_VAR: {
                fprintf(file, "%c", list_of_vars[node->val].var_name);
                break;
            }
            default:
                break;
        }

        if (node->right != NULL) {
            text_dump(node->right, file);
        }
        //fprintf(file, ")");
        fprintf(file, " ");
        return;
    }
}



