/*
** EPITECH PROJECT, 2018
** crypt.c
** File description:
** crypt a message
*/

#include "my.h"
#include <stdio.h>

void crypt(char *cstr, char *ckey)
{
    int **key = create_key(ckey);
    int **str = create_str(cstr, key);
    int **result = mult_matrice(str, key);

    printf("Key matrix:\n");
    for (int i = 0; key[i] != NULL; i++) {
        for (int j = 0; key[j] != NULL; j++) {
            if (j > 0)
                printf("\t");
            printf("%d", key[i][j]);
		}
        printf("\n");
    }
    printf("\nEncrypted message:\n");
    for (int i = 0; str[i] != NULL; i++)
        for (int j = 0; key[j] != NULL; j++) {
            if (i > 0 || j > 0)
                printf(" ");
            printf("%d", result[i][j]);
        }
    printf("\n");
}
