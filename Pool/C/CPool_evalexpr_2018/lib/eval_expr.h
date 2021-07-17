/*
** EPITECH PROJECT, 2018
** eval_expr.h
** File description:
** header of eval expr
*/

typedef struct chain_list {
    char *number;
    char operator;
    struct chain_list *next;
} struct_eval_expr;

#define CHAR_IS_OPERATOR(char) (char == '(' || char == ')' || char == '^' |\
| char == '+' || char == '-' || char == '%' || char == '*' || char == '/')

#define CHAR_ISNT_MULT(char) (char != '*' && char != '/' &\
& char != '%' && memory->next->next != NULL)

#define CHAR_ISNT_ADD(char) (char != '+' && char != '-' &\
& memory->next->next != NULL)

char *eval_expr(char const *, char const *);
void my_rev_list(struct_eval_expr **);
void print_struct(struct_eval_expr *);
char *make_operation(struct_eval_expr *);
char *infin_add(char *, char *);
char *infin_mult(char *, char *);
char *infin_div(char *, char *);
char *infin_mod(char *, char *);
