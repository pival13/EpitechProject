/*
** EPITECH PROJECT, 2019
** print
** File description:
** label
*/

#include "my.h"

void print_label(int fd, asm_t *r, char *label, int size)
{
    asm_t *temp = r;
    int nb = 0;
    long long n = 255;
    int correct = 0;

    for (int i = 1; i != size; i++)
        n = (n << 8) + 255;
    for (; !temp->other && !correct; temp = temp->prev, nb -= temp->size)
        if (!my_strcmp(label, temp->label)) {
            correct = 1;
            break;
        }
    if (!correct)
        nb = 0;
    for (temp = r; temp && !correct; nb += temp->size, temp = temp->next)
        if (!my_strcmp(label, temp->label))
            break;
    print_nb(fd, (n+1+nb)%(n+1), size);
}