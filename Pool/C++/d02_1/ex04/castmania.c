/*
** EPITECH PROJECT, 2020
** castmania.c
** File description:
** cast mania
*/

#include "castmania.h"
#include <stdlib.h>
#include <stdio.h>

void exec_operation(instruction_type_t type, void *data)
{
    instruction_t *ins = data;
    division_t *div;

    if (data == NULL)
        return;
    if (type == ADD_OPERATION) {
        exec_add((addition_t *)ins->operation);
        if (ins->output_type == VERBOSE)
            printf("%d\n", ((addition_t *)ins->operation)->add_op.res);
    } else if (type == DIV_OPERATION) {
        div = ins->operation;
        exec_div(div);
        if (ins->output_type == VERBOSE) {
            if (div->div_type == INTEGER)
                printf("%d\n", ((integer_op_t *)div->div_op)->res);
            else
                printf("%f\n", ((decimale_op_t *)div->div_op)->res);
        }
    }
}

void exec_instruction(instruction_type_t type, void *data)
{
    if (data == NULL)
        return;
    if (type == PRINT_INT) {
        printf("%d\n", *(int *)data);
    } else if (type == PRINT_FLOAT) {
        printf("%f\n", *(float *)data);
    } else
        exec_operation(type, data);
}