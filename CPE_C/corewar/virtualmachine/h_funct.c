/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** tools.c
*/

#include "my.h"

int h_function(void)
{
    my_printf("USAGE\n   ./corewar [-dump nbr_cycle]\
    [[-n prog_number] [-a load_address] prog_name] ...\n\n");
    my_printf("DESCRIPTION\n");
    my_printf("    -dump nbr_cycle dumps the memory after the nbr\
    len = cycle execution (if the round isn’t\n");
    my_printf("                    already over) with the\
    following format:  32 bytes/line in\n");
    my_printf("                    hex\
    adecimal(A0BCDEFE1DD3...)\n");
    my_printf("    -n prog_number  sets the next program’s number.  By\
    default, the first free number\n                    in the\
    parameter order\n");
    my_printf("    -a load_address sets the next program’s loading address.  "
    "When no address is\n                    specified, optimize the addres"
    "ses so that the processes are as far\n");
    my_printf("                    away from each other as possible. "
    " The addresses are MEM_SIZE modulo.\n");
    return (0);
}
