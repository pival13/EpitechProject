/*
** EPITECH PROJECT, 2020
** log.h
** File description:
** header of log
*/

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

enum log_level {
    ERROR,
    WARNING,
    NOTICE,
    INFO,
    DEBUG
};

int log_file(int new_fd);

enum log_level get_log_level(void);
enum log_level set_log_level(enum log_level);
int set_log_file(const char *);
int close_log_file(void);

int log_to_stdout(void);
int log_to_stderr(void);
void log_msg(enum log_level, const char *fmt, ...);

#endif