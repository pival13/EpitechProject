#include <stdlib.h>
#include <stdio.h>

size_t strlen(const char *);
char *strchr(const char *, int);
char *strstr(const char *, const char *);
char *strpbrk(const char *, const char *);
char *strcspn(const char *, const char *);
char *rindex(const char *, int);
void *memset (void *s, int c, size_t n);
void *memcpy (void *s, void *c, size_t n);
void *memmove (void *s, void *c, size_t n);
int strcasecmp(char *, char*);

int main(int a, char **arg)
{
    printf("[%s]\n", strstr(arg[1], arg[2]));
    //printf("%s\n", strpbrk(str, "xn"));
}