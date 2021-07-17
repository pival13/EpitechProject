/*
** EPITECH PROJECT, 2019
** my_ls
** File description:
** Display the content of delivery
*/

#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/sysmacros.h>
#include "my.h"
#include "my_ls.h"

void write_detail_2(list_t f)
{
    char type[7] = {'p', 'c', 'd', 'b', '-', 'l', 's'};
    char *mode[4] = {"--", "-w", "r-", "rw"};
    char *timer = &(ctime(&(f.s.st_mtime)))[4];

    timer[my_strlen(timer)-1] = '\0';
    my_printf("%c", type[f.s.st_mode/(64*64*2)]);
    my_printf("%s%c%s%c%s%c ", mode[f.s.st_mode%512/128], MOD(f.s.st_mode% \
512/64), mode[f.s.st_mode%64/16], MOD(f.s.st_mode%64/8), mode[f.s.st_mode%8/2]\
, MODT(f.s.st_mode));
    my_printf("%d ", f.s.st_nlink);
    my_printf("%s %s ", getpwuid(f.s.st_uid)->pw_name, getgrgid(f.s.st_gid) \
->gr_name);
    if (f.s.st_mode/(64*64*2) == 1 || f.s.st_mode/(64*64*2) == 3)
        my_printf("%d, %d\t", major(f.s.st_rdev), minor(f.s.st_rdev));
    else
        my_printf("%d\t", f.s.st_size);
    my_printf("%s  ", timer);
}

void write_detail(list_t f, long long opt)
{
    if (opt % 19 == 0)
        my_printf("%d ", f.s.st_ino);
    if (opt % 17 == 0)
        my_printf("%d ", f.s.st_blocks/2);
    if (opt % 2 == 0)
        write_detail_2(f);
    my_printf(f.file);
    if (opt % 23 == 0 && f.s.st_mode/8192 == 2)
        my_printf("/");
    my_printf("\n");
}
