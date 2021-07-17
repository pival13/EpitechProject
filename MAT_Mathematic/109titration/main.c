/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** 109titration
*/

#include "my.h"

double **estimate(double **value, int middle)
{
    if (middle < 1)
        exit(84);
    int len = (value[middle+1][0] - value[middle-1][0]) * 10;
    double use = value[middle-1][0];
    double **estimate = malloc(sizeof(double *) * (len + 1));
    int size = 0;
    double ecc1 = (value[middle][0] - value[middle-1][0]) * 10;
    double ecc2 = (value[middle+1][0] - value[middle][0]) * 10;
    double ec1 = value[middle][1] - value[middle-1][1];
    double ec2 = value[middle+1][1] - value[middle][1];
    int mid = 0;

    for (; value[size] != NULL; size++);
    size -= 2;
    for (int i = 0; i <= len; i++) {
        estimate[i] = malloc(sizeof(double) * 2);
        estimate[i][0] = use + (0.1 * i);
        estimate[i][1] = estimate[i][0];
    }
    estimate[(int)len+1] = NULL;
    estimate[0][1] = value[middle-1][1];
    estimate[(int)len][1] = value[middle+1][1];
    use += 0.1;
    for (int i = 1; i < len; i++, use += 0.1) {
        if (i < ecc1)
            estimate[i][1] = value[middle-1][1] + ec1 / ecc1 * i;
        if (i == ecc1) {
            estimate[i][1] = value[middle][1];
            mid = i;
        }
        if (i > ecc1)
            estimate[i][1] = value[middle][1] + ec2 / ecc2 * (i - mid);
    }
    return (estimate);
}

double **derivate(double **value)
{
    double **deriv;
    int size = 0;

    if (value == NULL || value[0] == NULL || value[1] == NULL || value[2] == NULL)
        return (NULL);
    for (; value[size] != NULL; size++);
    if (size < 1)
        exit(84);
    deriv = malloc(sizeof(double *) * (size-1));
    deriv[size-2] = NULL;
    for (int i = 0; i != size-2; i++) {
        deriv[i] = malloc(sizeof(double) * 2);
        deriv[i][0] = value[i+1][0];
        deriv[i][1] = (value[i+2][1]-value[i][1]) / (value[i+2][0]-value[i][0]);
    }
    return (deriv);
}

void read_double(char *str, double *value, int line)
{
    int i = 0;

    for (int j = 0; j != line; i++)
        if (str[i] == '\n')
            j++;
    if (str[i] < '0' || str[i] > '9')
        exit(84);
    value[0] = atof(&str[i]);
    for (; str[i] != '\n' && str[i] != '\0' && str[i] != ';'; i++);
    if (str[i] != ';' || str[i+1] < '0' || str[i+1] > '9')
        exit(84);
    else
        i++;
    value[1] = atof(&str[i]);
}

int verify_csv(char *path)
{
    int i = 0;

    for (i = 0; path[i] != 0 && path[i+1] != 0; i++);
    if (i < 4)
        return (0);
    if (path[i] != 'v' || path[i-1] != 's'
        || path[i-2] != 'c' || path[i-3] != '.')
        return (0);
    return (1);
}

double **read_value(char *path)
{
    int fd;
    struct stat s;
    char *str;
    double **value;
    int len = 1;

    if (verify_csv(path) == 0) exit(84);
    if ((fd = open(path, O_RDONLY)) == -1) exit(84);
    if (fstat(fd, &s) == -1) exit(84);
    if ((str = malloc(sizeof(char)*(s.st_size+1))) == NULL) exit(84);
    if (read(fd, str, s.st_size) != s.st_size) exit(84);
    str[s.st_size]='\0';
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == '\n' && str[i+1] != '\0') len++;
    if ((value = malloc(sizeof(double *) * (len+1))) == NULL) exit(84);
    for (int i = 0; i != len; i++) {
        if ((value[i] = malloc(sizeof(double)*2)) == NULL) exit(84);
        read_double(str, value[i], i);
    }
    value[len] = NULL;
    return (value);
}

void print_equivalent(double **estimate)
{
    int pos = 0;
    double cmp = 0;
    double cmp_pos;

    cmp_pos = estimate[0][1];
    if (cmp_pos < 0)
        cmp_pos *= -1;
    for (int i = 0; estimate[i] != NULL; i++) {
        cmp = estimate[i][1];
        if (cmp < 0)
            cmp *= -1;
        if (cmp < cmp_pos) {
            pos = i;
            cmp_pos = cmp;
        }
    }
    printf("\nEquivalent point at %.1f ml\n", estimate[pos][0]);
}

int main(int n, char **arg)
{
    if (n != 2)
        return (84);
    double **value = read_value(arg[1]);
    double **deriv = derivate(value);
    int max = 0;
    int sens = 1;

    if (deriv == NULL)
        exit(84);
    printf("Derivative:\n");
    for (int i = 0; deriv[i] != NULL; i++) {
        printf("%.1lf ml -> %.2lf\n", deriv[i][0], deriv[i][1]);
        if (deriv[i+1] == NULL)
            sens = i+1;
    }
    if (value[sens][1] > value[0][1])
        sens = 1;
    else
        sens = -1;
    for (int i = 1; deriv[0] != NULL && deriv[i] != NULL && deriv[i+1] != NULL && deriv[i+2] != NULL; i++)
        if (sens == 1 && deriv[i][1] >= deriv[max][1])
            max = i;
        else if (sens == -1 && deriv[i][1] <= deriv[max][1])
            max = i;
    printf("\nEquivalent point at %.1f ml\n", deriv[max][0]);
    double **deriv2 = derivate(deriv);
    if (deriv2 == NULL)
        exit(0);
    printf("\nSecond derivative:\n");
    for (int i = 0; deriv2[i] != NULL; i++)
        printf("%.1lf ml -> %.2lf\n", deriv2[i][0], deriv2[i][1]);

    double **estimated = estimate(deriv2, max-1);

    printf("\nSecond derivative estimated:\n");
    for (int i = 0; estimated[i] != NULL; i++)
        printf("%.1lf ml -> %.2lf\n", estimated[i][0], estimated[i][1]);
    print_equivalent(estimated);
    return (0);
}
