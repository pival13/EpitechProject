/*
** EPITECH PROJECT, 2019
** create_champ
** File description:
** create the struct champ
*/

#include "my.h"

static int check_champ(char *filepath, unsigned char **champ)
{
    int fd = open(filepath, O_RDONLY);
    int nb;
    int size;

    if (fd == -1)
        return (0);
    size = lseek(fd, 1, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    *champ = malloc(size);
    if (champ == NULL)
        return (0);
    nb = read(fd, *champ, size-1);
    if (nb != size-1)
        return (0);
    champ[0][size - 1] = 0;
    if (nb < (int)sizeof(header_t) || get_bytes(champ[0], 0, 4) != \
COREWAR_EXEC_MAGIC)
        return (0);
    free(filepath);
    return (nb);
}

static void check_adress(virtualmachine_t *vm, unsigned char *champ, int i)
{
    int begin = sizeof(header_t);
    unsigned int size = get_bytes(champ, PROG_NAME_LENGTH + 8, 4);

    for (unsigned int a = 0; a != size; a++)
        vm->memory[(vm->champion[i].a_option + a) % MEM_SIZE] = \
champ[begin+a];
}

static int find_number_in_tab(virtualmachine_t *vm, int k)
{
    for (int a = 0; a != vm->nb_champion; a++)
        if (vm->champion[a].n_option == k)
            return (0);
    return (1);
}

static void n_option(virtualmachine_t *vm)
{
    int k = 1;

    for (int a = 0; a != vm->nb_champion; a++) {
        while (find_number_in_tab(vm, k) == 0 && \
vm->champion[a].n_option == -1)
            k++;
        if (vm->champion[a].n_option == -1)
            vm->champion[a].n_option = k;
    }
}

int create_champ(virtualmachine_t *vm, int ac, char **av)
{
    unsigned char *champ = NULL;
    int nb = 0;
    int player = 0;

    if (get_opt(ac, av, vm) == 84)
        return (84);
    n_option(vm);
    for (int i = 0; i != vm->nb_champion; i++) {
        nb = check_champ((char *)vm->champion[i].name, &champ);
        if (nb && champ) {
            vm->champion[player].nb = vm->champion[i].n_option;
            vm->champion[i].pc = vm->champion[i].a_option;
            set_bytes(vm->champion[i].reg, vm->champion[i].nb, 0, REG_SIZE);
            vm->champion[i].name = my_strcpy(&champ[4]);
            check_adress(vm, champ , i);
            free(champ);
            player++;
        }
    }
    return (0);
}
