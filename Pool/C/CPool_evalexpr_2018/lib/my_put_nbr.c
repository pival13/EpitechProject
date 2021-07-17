/*
** EPITECH PROJECT, 2018
** my_put_nbr.c
** File description:
** Display number
*/

void my_putchar(char);

void print_number(int nbr)
{
    int memory;
    int m = 1;
    int nb = nbr;

    while (nbr != 0) {
        memory = nbr % 10;
        nbr -= memory;
        nbr /= 10;
        m *= 10;
    }
    m /= 10;
    while (m > 1) {
        memory = nb % m;
        nb = (nb - memory) / m;
        my_putchar(nb + 48);
        nb = memory;
        m /= 10;
    }
    my_putchar(nb + 48);
}

int my_put_nbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb -= 2 * nb;
    };
    print_number(nb);
    return (0);
}
