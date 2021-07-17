/*
** EPITECH PROJECT, 2018
** decrypt.c
** File description:
** functions for the decryption
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>

void display_key(float **key)
{
    for (int i = 0; key[i] != NULL; i++) {
        for (int j = 0; key[j] != NULL; j++) {
            printf("%.3f\t",key[i][j]);
        }
        printf("\n");
    }
}

void decrypt(char *cstr, char *ckey)
{
    int **key_int = create_key(ckey);
    float **key = matrice_invers(key_int);
    int **str = create_matrix(cstr, key_int);
    int **result = mult_matrice_f(str, key);

    printf("Key matrix:\n");
    display_key(key);
    printf("\nDecrypted message:\n");
    for (int i = 0; str[i] != NULL; i++) {
        for (int j = 0; key[j] != NULL; j++)
            if (result[i][j] >= 32)
                printf("%c", result[i][j]);
		}
    printf("\n");
}
