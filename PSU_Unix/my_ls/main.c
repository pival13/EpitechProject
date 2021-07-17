/*
** EPITECH PROJECT, 2019
** main
** File description:
** main of my_ls
*/

#include "my.h"
#include "my_ls.h"

long long prepare_option(char *str, long long opt)
{
    char letter[10] = {'l', 'R', 'r', 'd', 't', 'a', 's', 'i', 'p', 'm'};
    int premium[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    int ok = 0;

    for (int i = 1; str[0] == '-' && str[i] != '\0'; i++) {
        for (int j = 0; j != 9; j++)
            if (str[i] == letter[j]) {
                opt *= premium[j];
                ok = 1;
            }
        if (ok == 1)
            ok = 0;
        else
            my_printf("Option -%c doesn't exist\n", str[i]);
    }
    return (opt);
}

int check_file(char *arg)
{
    DIR *dir;
    struct stat s;

    dir = opendir(arg);
    if (dir == NULL) {
        if (stat(arg, &s) == -1)
            my_printf("ls: impossible d'accéder à '%s': No such \
file or directory\n", arg);
        else
            my_printf("ls: impossible d'ouvrir le répertoire '%s\
': Permission denied\n", arg);
        return (-1);
    }
    closedir(dir);
    return (0);
}

long long check_params(long long opt, char *arg, char **str, int *a)
{
    opt = prepare_option(arg, opt);
    if (arg[0] != '-') {
        str[*a] = arg;
        if (check_file(arg) == -1) {
            *a -= 1;
            opt *= 97;
        }
        *a += 1;
        str[*a] = NULL;
    }
    return (opt);
}

int main(int n, char **arg)
{
    long long opt = 1;
    char *str[n];
    int a = 0;

    str[0] = NULL;
    for (int i = 1; i < n; i++) {
        opt = check_params(opt, arg[i], str, &a);
    }
    my_sort_list(str);
    if (str[0] == NULL && opt % 97 != 0)
        display_content(".", opt);
    else
        for (int i = 0; str[i] != NULL; i++) {
            display_content(str[i], opt);
            if (str[i+1] != NULL)
                my_printf("\n");
        }
}

//What's '.'
//Readlink
