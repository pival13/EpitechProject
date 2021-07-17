/*
** EPITECH PROJECT, 2019
** find_size
** File description:
** find the size
*/

#include "my.h"

static int check_type(asm_t *command, int pos)
{
    char c = DIRECT_CHAR;

    if (my_strncmp(command->param[pos], "r", 1) == 0)
        return (1);
    if (my_strncmp(command->param[pos], &c, 1) == 0)
        return (DIR_SIZE);
    return (IND_SIZE);
}

static int check_parti(asm_t *command, int pos)
{
    if (my_strncmp(command->param[pos], "r", 1) == 0)
        return (1);
    return (2);
}

int find_size_asm(asm_t *command)
{
    int size = 2;
    op_t *op = op_tab;

    for (; op[0].mnemonique != NULL && my_strcmp(op[0].mnemonique, \
command->arg) != 0; op++);
    if (op[0].mnemonique == NULL)
        return (0);
    if (my_strcmp(op[0].mnemonique, "live") == 0)
        return (5);
    if (my_strcmp(op[0].mnemonique, "zjmp") == 0 || my_strcmp(op[0]
    .mnemonique, "fork") == 0 || !my_strcmp(op[0].mnemonique, "lfork"))
        return (3);
    if (my_strcmp(op[0].mnemonique, "ldi") == 0 || my_strcmp(op[0].mnemonique, \
"lldi") == 0)
        return (3 + check_parti(command, 1) + check_parti(command, 0));
    if (my_strcmp(op[0].mnemonique, "sti") == 0)
        return (3 + check_parti(command, 1) + check_parti(command, 2));
    for (int j = 0; command->param[j] != NULL; j++)
        size += check_type(command, j);
    return (size);
}

int find_size_vm(unsigned char *m, int pc)
{
    int size = 2;
    int s[3] = {1, DIR_SIZE, IND_SIZE};

    if (m[pc%MEM_SIZE] == 1)
        return (5);
    if (m[pc%MEM_SIZE] == 9 || m[pc%MEM_SIZE] == 12 || m[pc%MEM_SIZE] == 15)
        return (3);
    if (m[pc%MEM_SIZE] == 10 || m[pc%MEM_SIZE] == 14)
        return (7);
    if (m[pc%MEM_SIZE] == 11) {
        size += ((m[(pc+1) % MEM_SIZE] & 48) >> 4 == 1) ? 1 : 2;
        size += ((m[(pc+1) % MEM_SIZE] & 12) >> 2 == 1) ? 1 : 2;
        return (size + 1);
    }
    for (unsigned char j = m[(pc+1) % MEM_SIZE]; (j & 192) != 0; j = j << 2)
        size += s[(j>>6)-1];
    return (size);
}