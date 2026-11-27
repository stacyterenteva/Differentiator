#ifndef DSL_H
#define DSL_H
#include "binary_tree.h"

#define NUM(val) create_node(TYPE_NUM, val, NULL, NULL)
#define VAR(val) create_node(TYPE_VAR, val, NULL, NULL)
#define ADD(val1, val2) create_node(TYPE_OP, FUNC_ADD, val1, val2)
#define SUB(val1, val2) create_node(TYPE_OP, FUNC_SUB, val1, val2)
#define MUL(val1, val2) create_node(TYPE_OP, FUNC_MUL, val1, val2)
#define DIV(val1, val2) create_node(TYPE_OP, FUNC_DIV, val1, val2)
#define SIN(val1) create_node(TYPE_OP, FUNC_SIN, NULL, val1)
#define COS(val1) create_node(TYPE_OP, FUNC_COS, NULL, val1)
#define POW(val1, val2) create_node(TYPE_OP, FUNC_POW, val1, NUM(val2))
#define LOG(val1, val2) create_node(TYPE_OP, FUNC_LOG, val1, val2)
#define LN(val1) create_node(TYPE_OP, FUNC_LN, NULL, val1)

enum func_num_t
{
    FUNC_ADD,
    FUNC_SUB,
    FUNC_MUL,
    FUNC_DIV,
    FUNC_SIN,
    FUNC_COS,
    FUNC_TG,
    FUNC_CTG,
    FUNC_ARCSIN,
    FUNC_ARCCOS,
    FUNC_ARCTG,
    FUNC_ARCCTG,
    FUNC_SH,
    FUNC_CH,
    FUNC_EXP,
    FUNC_POW,
    FUNC_LOG,
    FUNC_LN
};

struct func_t
{
    func_num_t func;
    const char* func_name;
};

const func_t list_of_funcs[] = {
    {FUNC_ADD, "+"},
    {FUNC_SUB, "-"},
    {FUNC_MUL, "*"},
    {FUNC_DIV, "/"},
    {FUNC_SIN, "SIN"},
    {FUNC_COS, "COS"},
    {FUNC_TG, "TG"},
    {FUNC_CTG, "CTG"},
    {FUNC_ARCSIN, "ARCSSIN"},
    {FUNC_ARCCOS, "ARCCOS"},
    {FUNC_ARCTG, "ARCTG"},
    {FUNC_ARCCTG, "ARCCTG"},
    {FUNC_SH, "SH"},
    {FUNC_CH, "CH"},
    {FUNC_EXP, "EXP"},
    {FUNC_POW, "^"},
    {FUNC_LOG, "LOG"},
    {FUNC_LN, "ln"}
};

struct var_t
{
    char var_name;
    int var_num;
};

const var_t list_of_vars[] =
{
    {'x', 0},
    {'y', 1},
    {'z', 2},
    {'u', 3},
    {'v', 4}
};

enum VARS {
    VAR_X,
    VAR_Y,
    VAR_Z,
    VAR_U,
    VAR_V
};

bool is_num(tree_node_t* node);
bool is_var(tree_node_t* node);
bool is_op(tree_node_t* node);
bool is_neutral_one(tree_node_t* node, func_num_t operation, bool* is_left);

#endif /* DSL_H */
