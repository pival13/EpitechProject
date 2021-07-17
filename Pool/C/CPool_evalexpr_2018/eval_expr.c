/*
** EPITECH PROJECT, 2018
** eval_expr.c
** File description:
** Begin of eval_expr
*/

#include "eval_expr.h"
#include "my.h"
#include <stdlib.h>

char *convert_base(char const *, char const *, char const *);

void print_struct(struct_eval_expr *array)
{
    while (array->next != NULL) {
        if (array->operator == '\0')
            my_putstr(array->number);
        else
            my_putchar(array->operator);
        array = array->next;
        my_putchar(' ');
    }
    if (array->operator == '\0')
        my_putstr(array->number);
    else
        my_putchar(array->operator);
    array = array->next;
    my_putchar('\n');
}

struct_eval_expr *create_struct(struct_eval_expr *list,
                                char const *str,
                                struct_eval_expr *tempo,
                                char const *base)
{
    int i = my_strlen(base);
    char max = 0;
    int maxmin = 0;
    int minmax = '0';
    
    if (i >= 11) {
        maxmin = '9';
        minmax = 'A';
        max = i + 54;
    } else {
        maxmin = i + 47;
        max = i + 47;
    }
    while (str[0] != '\0') {
        if (CHAR_IS_OPERATOR(str[0])) {
            tempo = malloc(sizeof(struct_eval_expr));
            tempo->number = 0;
            tempo->operator = str[0];
            tempo->next = list;
            list = tempo;
            str++;
		} else {
            tempo = malloc(sizeof(struct_eval_expr));
            tempo->number = convert_base(str, base, "0123456789");
            tempo->operator = '\0';
            tempo->next = list;
            list = tempo;
            str++;
            for (int n = 0; n <= i; n++)
                if ((str[0] >= '0' && str[0] <= maxmin) || (str[0] >= minmax && str[0] <= max)) {
					str++;
					n = 0;
				}
	    }
    }
    return (list);
}

char *eval_expr(char const *str, char const *base)
{
    struct_eval_expr *list = malloc(sizeof(struct_eval_expr));
    struct_eval_expr *tempo;

    list = create_struct(list, str, tempo, base);
    my_rev_list(&list);
    print_struct(list);
    make_operation(list);
    return (list->number);
}
