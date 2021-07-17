/*
** EPITECH PROJECT, 2020
** log.c
** File description:
** log
*/

#include "log.h"

char *ll_msg(enum log_level llv)
{
    if (llv == ERROR)
        return "ERROR";
    if (llv == WARNING)
        return "WARNING";
    if (llv == NOTICE)
        return "NOTICE";
    if (llv == INFO)
        return "INFO";
    if (llv == DEBUG)
        return "DEBUG";
    return "";
}

int log_to_stdout(void)
{
    if (close_log_file() == 1)
        return 1;
    log_file(1);
}

int log_to_stderr(void)
{
    return close_log_file();
}

void log_msg(enum log_level llv, const char *fmt, ...)
{
    va_list list;
    time_t t = time(NULL);
    char *s = malloc(sizeof(char) * (strlen(ctime(&t)) + 1));

    if (llv < 0 || llv > 4 || llv > get_log_level() || fmt == NULL || \
s == NULL) {
        free(s);
        return;
    }
    strcpy(s, ctime(&t));
    s[strlen(ctime(&t))-1] = '\0';
    va_start(list, fmt);
    dprintf(log_file(-1), "%s [%s]: ", s, ll_msg(llv));
    vdprintf(log_file(-1), fmt, list);
    va_end(list);
    free(s);
}