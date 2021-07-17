#include "string.h"
#include <stdio.h>

int main()
{
    string_t s;
    string_t s1;

    string_init(&s, "I am Ferdinand Von Aegir");
    string_init(&s1, "");
    s.insert_s(&s, 0, &s1);
    printf("%s\n", s.c_str(&s));
    /*s1 = s.substr(&s, 1, 10);
    printf("%s\n", s1->str);
    string_destroy(s1);
    free(s1);
    s1 = s.substr(&s, -1, -10);
    printf("%s\n", s1->str);
    string_destroy(s1);
    free(s1);
    s1 = s.substr(&s, 10, -8);
    printf("%s\n", s1->str);
    string_destroy(s1);
    free(s1);
    s1 = s.substr(&s, -10, 8);
    printf("%s\n", s1->str);
    string_destroy(s1);
    free(s1);
    s1 = s.substr(&s, 20, 10);
    printf("%s\n", s1->str);
    string_destroy(s1);
    free(s1);
    s1 = s.substr(&s, 4, -10);
    printf("%s\n", s1->str);
    string_destroy(s1);
    free(s1);
    s1 = s.substr(&s, -40, 10);
    printf("%s\n", s1->str);
    string_destroy(s1);
    free(s1);
    s1 = s.substr(&s, -40, -10);
    printf("%s\n", s1->str);
    string_destroy(s1);
    free(s1);
    s1 = s.substr(&s, 40, 10);
    printf("%s\n", s1->str);
    string_destroy(s1);
    free(s1);
    s1 = s.substr(&s, 40, -10);
    printf("%s\n", s1->str);*/
    string_destroy(&s);
    string_destroy(&s1);
    //free(s1);
}