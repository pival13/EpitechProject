/*
** EPITECH PROJECT, 2018
** operation.c
** File description:
** Make operation with the chain_list
*/

#include "my.h"
#include "eval_expr.h"
#include <stdlib.h>

char *if_parenth(struct_eval_expr *memory,
               struct_eval_expr *rest_op,
               struct_eval_expr *list,
               int number_parenth)
{
    while (number_parenth != 0) {
        if (memory->operator == '(')
            number_parenth--;
        if (number_parenth != 0)
            memory = memory->next;
    }
    if (memory->operator == '(') {
        memory->number = make_operation(memory->next);
        memory->operator = '\0';
        memory->next = rest_op->next;
        return (make_operation(list));
    }
}

char *make_parenth(struct_eval_expr *list, struct_eval_expr *memory)
{
    int number_parenth = 0;
    struct_eval_expr *rest_op;

    while (memory->next->operator != ')' && memory->next->next != NULL) {
        if (memory->operator == '(')
            number_parenth++;
        memory = memory->next;
    }
    if (memory->next->operator == ')') {
        rest_op = memory->next;
        memory->next = NULL;
    }
    memory = list;
    if (list->next == NULL)
        return (list->number);
    if_parenth(memory, rest_op, list, number_parenth);
}
/*
char *make_power(struct_eval_expr *list, struct_eval_expr *memory)
{
    char *a = malloc(1000000000);
    char *i = malloc(1000000000);
    
    memory = list;
    while (memory->next->operator != '^')
        memory = memory->next;
    if (memory->next->operator == '^') {
        for (i = "0"; my_strcmp(i, memory->next->next->number) < 0; i = infin_add(i, "1"))
            a = infin_mult(a, memory->number);
        memory->number = a;
        memory->next = memory->next->next->next;
    }
}
 */       
char *when_mult(struct_eval_expr *list, struct_eval_expr *memory)
{
    memory = list;
    while (CHAR_ISNT_MULT(memory->next->operator))
        memory = memory->next;
    if (memory->next->operator == '*') {
        memory->number = infin_mult(memory->number, memory->next->next->number);
        memory->operator = '\0';
        memory->next = memory->next->next->next;
        return (make_operation(list));
    }
    if (memory->next->operator == '%') {
        memory->number = infin_mod(memory->number, memory->next->next->number);
        memory->operator = '\0';
        memory->next = memory->next->next->next;
        return (make_operation(list));
    }
    if (memory->next->operator == '/') {
        memory->number = infin_div(memory->number, memory->next->next->number);
        memory->operator = '\0';
        memory->next = memory->next->next->next;
        return (make_operation(list));
    }
}

char *when_add(struct_eval_expr *list, struct_eval_expr *memory)
{
    memory = list;
    while (CHAR_ISNT_ADD(memory->next->operator))
        memory = memory->next;
    if (memory->next->operator == '+') {
        memory->number = infin_add(memory->number, memory->next->next->number);
        memory->operator = '\0';
        memory->next = memory->next->next->next;
        return (make_operation(list));
    }
    if (memory->next->operator == '-') {
        memory->number = infin_add(memory->number, infin_mult(memory->next->next->number, "-1"));
        memory->operator = '\0';
        memory->next = memory->next->next->next;
        return (make_operation(list));
    }
}

char *make_operation(struct_eval_expr *list)
{
    struct_eval_expr *memory = list;

    print_struct(list);
    if (list->next == NULL)
        return (list->number);
    make_parenth(list, memory);
    if (list->next == NULL)
        return (list->number);
    if (list->operator == '-' && list->next->operator == '\0') {
        list->number = infin_mult(list->next->number, "-1");
        list->operator = '\0';
        list->next = list->next->next;
    }/*
    if (list->next == NULL)
        return (list->number);
    make_power(list, memory);*/
    if (list->next == NULL) 
        return (list->number);
    when_mult(list, memory);
    if (list->next == NULL)
        return (list->number);
    when_add(list, memory);
    if (list->next == NULL)
        return (list->number);
}
