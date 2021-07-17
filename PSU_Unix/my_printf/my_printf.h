/*
** EPITECH PROJECT, 2018
** my_printf.h
** File description:
** Header of myprintf
*/

#ifndef MY_PRINTF_H
#define MY_PRINTF_H

int my_putchar(char c);
int put_c(va_list arg);
int put_s(va_list arg);
int put_bigs(va_list arg);
int put_d(va_list arg);
int put_u(va_list arg);
int put_b(va_list arg);
int put_o(va_list arg);
int put_x(va_list arg);
int put_bigx(va_list arg);
int put_p(va_list arg);
int put_percent(va_list arg);

#endif //_MY_PRINTF_H_
