/*
** EPITECH PROJECT, 2019
** my_ls
** File description:
** Display the content of delivery
*/

#include "my.h"
#include "my_ls.h"

int prepare_list(struct dirent *content, list_t *file, int j, long long opt)
{
    char *pathfile;

    if (opt % 13 == 0 || (opt % 13 != 0 && content->d_name[0] != '.')) {
        file[j].file = content->d_name;
        pathfile = my_merge(file[j].filepath, "/", file[j].file);
        if (lstat(pathfile, &(file[j].s)) == -1) {
            my_printf("%s can't be readed\n", file[j].file);
            j--;
        }
        free(pathfile);
        if ((opt % 7 == 0 && file[j].s.st_mode/(64*64*2) == 2) || opt \
            % 7 != 0)
            j++;
        file[j].file = NULL;
    }
    return (j);
}

void check_option_r(list_t *list, char *filepath, long long opt)
{
    char *str;

    if (opt % 3 == 0)
        for (int i = 0; list[i].file != NULL; i++)
            if (my_strcmp(list[i].file, ".") != 0 && my_strcmp(list[i].file, \
"..") != 0 && list[i].s.st_mode/8192 == 2) {
                str = my_merge(filepath, "/", list[i].file);
                my_printf("\n");
                if (check_file(str) != -1)
                    display_content(str, opt);
                free(str);
            }
}

void print_list(list_t *file, long long opt, char *str)
{
    if (file[0].file != NULL)
        my_printf("%s:\n", str);
    file = my_sort_list_stat(file);
    if (opt % 11 == 0)
        file = my_sort_list_time(file);
    if (opt % 5 == 0)
        file = my_sort_list_rev(file);
    for (int j = 0; file[j].file != NULL; j++)
        write_detail(file[j], opt);
    check_option_r(file, file->filepath, opt);
}

void display_content(char *str, long long opt)
{
    struct dirent *content;
    DIR *dir;
    list_t *file;

    dir = opendir(str);
    file = malloc(sizeof(list_t) * (find_nb_file(str) + 1));
    if (file == NULL) {
        my_printf("Problem with memories\n");
        exit(84);
    }
    content = readdir(dir);
    file[0].file = NULL;
    for (int j = 0; content != NULL;) {
        file[j].filepath = str;
        j = prepare_list(content, file, j, opt);
        content = readdir(dir);
    }
    print_list(file, opt, str);
    free(file);
    closedir(dir);
}
