/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** jsonCreater
*/

#include "json.h"

json_t *new_json_as_empty_list()
{
    return new_json_as_list(NULL);
}

json_t *new_json_as_list(json_t *values[])
{
    json_t *json = new_json();
    json_set_as_list(json, values);
    return json;
}

json_t *new_json_as_empty_dict()
{
    return new_json_as_dict(NULL, NULL);
}

json_t *new_json_as_dict(const char *keys[], json_t *values[])
{
    json_t *json = new_json();
    json_set_as_dict(json, keys, values);
    return json;
}

json_t *read_json_from_file(const char *file)
{
    int fd = open(file, O_RDONLY);
    struct stat s = {0};

    if (fd == -1 || fstat(fd, &s))
        return NULL;
    char *str = (char *)malloc(s.st_size+1);
    str[s.st_size] = '\0';
    if (read(fd, str, s.st_size) != s.st_size || !json_is_valid(str)) {
        free(str);
        close(fd);
        return NULL;
    }
    close(fd);
    json_clean_str(str);

    json_t *json = new_json();
    char *tmp = str;
    parse_json((const char **)(&tmp), json);
    free(str);
    return json;
}