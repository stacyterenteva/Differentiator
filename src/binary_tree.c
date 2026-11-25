#include "../include/binary_tree.h"
#include "../include/dsl.h"

const int MAX_OP_LEN = 10;

void link_right(tree_node_t* parent, tree_node_t* child)
{
    assert(parent);

    parent->right = child;
}

void link_left(tree_node_t* parent, tree_node_t* child)
{
    assert(parent);

    parent->left = child;
}

tree_node_t* create_node(TYPE type, int val, tree_node_t* left, tree_node_t* right)
{
    tree_node_t* node = (tree_node_t*) calloc(1, sizeof(tree_node_t));
    *node = {.type = type, .val = val, .left = left, .right = right};
    return node;
}

void convert_into_text(tree_node_t* node, FILE* file)
{
    assert(node);

    if (file == NULL) {
        file = stdout;
    }

    fprintf(file, "(");

    switch (node->type) {
        case TYPE_OP: {
            fprintf(file, "<%s> ", list_of_funcs[node->val].func_name);
            break;
        }
        case TYPE_NUM: {
            fprintf(file, "<%d> ", node->val);
            break;
        }
        case TYPE_VAR: {
            fprintf(file, "<%c> ", list_of_vars[node->val].var_name);
            break;
        }
        default:
            break;
    }
    if (node->left != NULL) {
        convert_into_text(node->left, file);
    }
    if (node->right != NULL) {
        convert_into_text(node->right, file);
    }
    fprintf(file, ")");
    return;
}

// full_rework
tree_node_t* read_tree(FILE* file) // подумать над тем чем отличается от просто чтения другого дереваю Попробовать найти общие части
{
    if (file == NULL) {
        printf("Error: read tree don't get correct file, program should be stopped\n");
        return NULL;
    }

    tree_node_t* parent = NULL;
    int ch = fgetc(file);

    // FIXME copy-paste!!!!
    if (ch == '(') {
        char* string = (char*) calloc(100, sizeof(char));
        read_phrase(string, file);

        if (strcmp("+", string) == 0) {
            parent = create_node(TYPE_OP, FUNC_ADD, NULL, NULL);
        }
        else if (strcmp("-", string) == 0) {
            parent = create_node(TYPE_OP, FUNC_SUB, NULL, NULL);
        }
        else if (strcmp("*", string) == 0) {
            parent = create_node(TYPE_OP, FUNC_MUL, NULL, NULL);
        }
        else if (strcmp("/", string) == 0) {
            parent = create_node(TYPE_OP, FUNC_DIV, NULL, NULL);
        }
        else if (strcmp("SIN", string) == 0) {
            parent = create_node(TYPE_OP, FUNC_SIN, NULL, NULL);
        }
        else if (strcmp("COS", string) == 0) {
            parent = create_node(TYPE_OP, FUNC_COS, NULL, NULL);
        }
        else if (strcmp("TG", string) == 0) {
            parent = create_node(TYPE_OP, FUNC_TG, NULL, NULL);
        }
        else if (strcmp("CTG", string) == 0) {
            parent = create_node(TYPE_OP, FUNC_CTG, NULL, NULL);
        }
        else if (strcmp("ARCSIN", string) == 0) {
            parent = create_node(TYPE_OP, FUNC_ARCSIN, NULL, NULL);
        }
        else if (strcmp("ARCCOS", string) == 0) {
            parent = create_node(TYPE_OP, FUNC_ARCCOS, NULL, NULL);
        }
        else if (strcmp("ARCTG", string) == 0) {
            parent = create_node(TYPE_OP, FUNC_ARCTG, NULL, NULL);
        }
        else if (strcmp("ARCCTG", string) == 0) {
            parent = create_node(TYPE_OP, FUNC_ARCCTG, NULL, NULL);
        }
        else if (strcmp("SH", string) == 0) {
            parent = create_node(TYPE_OP, FUNC_SH, NULL, NULL);
        }
        else if (strcmp("CH", string) == 0) {
            parent = create_node(TYPE_OP, FUNC_CH, NULL, NULL);
        }
        else if (strcmp("EXP", string) == 0) {
            parent = create_node(TYPE_OP, FUNC_EXP, NULL, NULL);
        }
        else if (strcmp("POW", string) == 0) {
            parent = create_node(TYPE_OP, FUNC_POW, NULL, NULL);
        }
        else if (strcmp("LOG", string) == 0) {
            parent = create_node(TYPE_OP, FUNC_LOG, NULL, NULL);
        }
        else if (strcmp("x", string) == 0) {
            parent = create_node(TYPE_VAR, VAR_X, NULL, NULL);
        }
        else {
            parent = create_node(TYPE_NUM, atoi(string), NULL, NULL);
        }

        free(string);

        ch = fgetc(file); //read space
        ch = fgetc(file); //read brace

        if (ch == ')') {
            return parent;
        }
        ungetc(ch, file);

        tree_node_t* child = read_tree(file);
        if (is_op(parent) && (parent->val == FUNC_SIN || parent->val == FUNC_COS)) { // cringe
            link_right(parent, child);
        }
        else {
            link_left(parent, child);

            child = read_tree(file);
            link_right(parent, child);
        }

        ch = fgetc(file);

        if (ch == ')') {
            return parent;
        }
        ungetc(ch, file);
    }

    return parent;
}

void tree_dump(tree_node_t* node, FILE* graph)
{
    assert(node);
    assert(graph);

    node_dump(node, graph);

    if (node->left != NULL)
    {
        fprintf(graph, "    node%p->node%p\n", node, node->left);
        tree_dump(node->left, graph);
    }

    if (node->right != NULL)
    {
        fprintf(graph, "    node%p->node%p\n", node, node->right);
        tree_dump(node->right, graph);
    }

    return;
}


#ifdef ON_DEBUG

void node_dump(tree_node_t* node, FILE* graph)
{
    assert(node);

    switch (node->type) {
        case TYPE_OP:
            fprintf(graph, "    node%p [shape=Mrecord, style=filled, fillcolor=\"#ba0aae\", color=\"#250228\", label=\"{ptr = %p | val = %d | type = %s | {left = %p | right = %p}}\"];\n", node, node, node->val, "OP",  node->left, node->right);
            break;
        case TYPE_NUM:
            fprintf(graph, "    node%p [shape=Mrecord, style=filled, fillcolor=\"#ba0aae\", color=\"#250228\", label=\"{ptr = %p | val = %d | type = %s | {left = %p | right = %p}}\"];\n", node, node, node->val, "NUM",  node->left, node->right);
            break;
        case TYPE_VAR:
            fprintf(graph, "    node%p [shape=Mrecord, style=filled, fillcolor=\"#ba0aae\", color=\"#250228\", label=\"{ptr = %p | val = %d | type = %s | {left = %p | right = %p}}\"];\n", node, node, node->val, "VAR",  node->left, node->right);
            break;
        default:
            break;
    }
}

#else

void node_dump(tree_node_t* node, FILE* graph)
{
    assert(node);

    switch (node->type) {
        case TYPE_OP: {
            const char* op = list_of_funcs[node->val].func_name;
            fprintf(graph, "    node%p [shape=circle, style=filled, fillcolor=\"#dbef2a\", label = \"%s\"];\n", node, op);
            break;
        }
        case TYPE_NUM:
            fprintf(graph, "    node%p [shape=square, style=filled, fillcolor=\"#05bfee\", label= %d];\n", node, node->val);
            break;
        case TYPE_VAR: {
            char var = list_of_vars[node->val].var_name;
            fprintf(graph, "    node%p [shape=invtriangle, style=filled, fillcolor=\"#ba0aae\", label= %c];\n", node, var);
            break;
        }
        default:
            break;
    }
}

#endif

//NOTE: магия

void dump(tree_node_t* node)
{
    assert(node);

    static int counter = 0;
    counter++;

    char file_name[100] = {};
    snprintf(file_name, 100, "dump/graph%d.dot", counter);

    FILE* graph = fopen(file_name, "w");
    assert(graph);

    fprintf(graph, "digraph {\n");
    tree_dump(node, graph);
    fprintf(graph, "}\n");
    fclose(graph);
    char temp[100] = {};
    snprintf(temp, 100, "dot -Tsvg dump/graph%d.dot -o dump/graph%d.svg", counter, counter);
    system(temp);
}

int read_phrase(char* string, FILE* file)
{
    assert(string);
    assert(file);

    int ch = fgetc(file);
    if (ch != '<') {
        return 1;
    }

    ch = fgetc(file);
    for (int i = 0; i == MAX_STRLEN - 1 || ch != '>'; i++) {
        string[i] = (char) ch;
        ch = fgetc(file);
    }

    return 0;
}

double count_tree(tree_node_t* node)
{
    assert(node);

    if (node->type == TYPE_NUM || node->type == TYPE_VAR) {
        return node->val;
    }

    else if (is_op(node) && is_num(node->left) && is_num(node->right)) {
        switch (node->val) {
            case FUNC_ADD:
                return count_tree(node->left) + count_tree(node->right);
                break;
            case FUNC_SUB:
                return count_tree(node->left) - count_tree(node->right);
                break;
            case FUNC_MUL:
                return count_tree(node->left) * count_tree(node->right);
                break;
            case FUNC_DIV:
                return count_tree(node->left) / count_tree(node->right);
                break;
            default:
                printf("Unknown comand: %d\n", node->type);
                break;
        }
    }

    return 0;
}

void destroy_tree(tree_node_t* root)
{
    assert(root);

    if (root->left != NULL) {
        destroy_tree(root->left);
    }

    if (root->right != NULL) {
        destroy_tree(root->right);
    }

    destroy_node(root);
    return;
}

void destroy_node(tree_node_t* node)
{
    assert(node);

    free(node);
    node = NULL;
}

tree_node_t* copy_node(tree_node_t* node)
{
    return create_node(node->type, node->val, NULL, NULL);
}

tree_node_t* copy_tree(tree_node_t* node_old)
{
    // assert(node_old);

    if (node_old == NULL) {
        return NULL;
    }

    tree_node_t* node_new = copy_node(node_old);

    if (node_old->left != NULL) {
        link_left(node_new, copy_tree(node_old->left));
    }

    if (node_old->right != NULL) {
        link_right(node_new, copy_tree(node_old->right));
    }

    return node_new;
}

