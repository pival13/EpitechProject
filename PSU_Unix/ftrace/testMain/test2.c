void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        my_putchar(str[i]);
}

int main()
{   
    my_putstr("Hello\n");
}