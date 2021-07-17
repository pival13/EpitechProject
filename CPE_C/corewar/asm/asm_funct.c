/*
** EPITECH PROJECT, 2019
** funct
** File description:
** some funct of assembler
*/

#include "my.h"

void asm_live(op_t op, asm_t *list, int fd)
{
    my_dprintf(fd, "%c", op.code);
    if (list->param[0][1] == LABEL_CHAR)
        print_label(fd, list, &list->param[0][2], 4);
    else
        print_nb(fd, my_getnbr(&list->param[0][1]), 4);
}

void asm_funct(op_t op, asm_t *list, int fd)
{
    my_dprintf(fd, "%c", op.code);
    print_type(fd, list->param);
    for (int i = 0; i != op.nbr_args; i++)
        if (list->param[i][0] == DIRECT_CHAR) {
            (list->param[i][1] == LABEL_CHAR) ? \
(print_label(fd, list, &list->param[i][2], DIR_SIZE)) : \
(print_nb(fd, my_getnbr(&list->param[i][1]), DIR_SIZE));
        } else if (list->param[i][0] == 'r')
            print_nb(fd, my_getnbr(&list->param[i][1]), 1);
        else {
            (list->param[i][0] == LABEL_CHAR) ? \
(print_label(fd, list, &list->param[i][1], IND_SIZE)) : \
(print_nb(fd, my_getnbr(list->param[i]), IND_SIZE));
        }
}

void asm_zjmp_fork(op_t op, asm_t *list, int fd)
{
    my_dprintf(fd, "%c", op.code);
    if (list->param[0][1] == LABEL_CHAR)
        print_label(fd, list, &list->param[0][2], IND_SIZE);
    else
        print_nb(fd, my_getnbr(&list->param[0][1]), IND_SIZE);
}

void asm_ldi(op_t op, asm_t *list, int fd)
{
    my_dprintf(fd, "%c", op.code);
    print_type(fd, list->param);
    for (int i = 0; i != 2; i++)
        if (list->param[i][0] == DIRECT_CHAR) {
            (list->param[i][1] == LABEL_CHAR) ? \
(print_label(fd, list, &list->param[i][2], IND_SIZE)) : \
(print_nb(fd, my_getnbr(&list->param[i][1]), IND_SIZE));
        } else if (list->param[i][0] == 'r')
            print_nb(fd, my_getnbr(&list->param[i][1]), 1);
        else {
(list->param[i][0] == LABEL_CHAR) ? \
(print_label(fd, list, &list->param[i][1], IND_SIZE)) : \
(print_nb(fd, my_getnbr(list->param[i]), IND_SIZE));
        }
    print_nb(fd, my_getnbr(&list->param[2][1]), 1);
}

void asm_sti(op_t op, asm_t *list, int fd)
{
    my_dprintf(fd, "%c", op.code);
    print_type(fd, list->param);
    print_nb(fd, my_getnbr(&list->param[0][1]), 1);
    for (int i = 1; i != 3; i++)
        if (list->param[i][0] == DIRECT_CHAR) {
            (list->param[i][1] == LABEL_CHAR) ? \
(print_label(fd, list, &list->param[i][2], IND_SIZE)) : \
(print_nb(fd, my_getnbr(&list->param[i][1]), IND_SIZE));
        } else if (list->param[i][0] == 'r')
            print_nb(fd, my_getnbr(&list->param[i][1]), 1);
        else {
            (list->param[i][0] == LABEL_CHAR) ?
(print_label(fd, list, &list->param[i][1], IND_SIZE)) : \
(print_nb(fd, my_getnbr(list->param[i]), IND_SIZE));
        }
}
