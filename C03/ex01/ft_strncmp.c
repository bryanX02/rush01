//
// Created by bryan on 23/08/2023.
//
#include <stdio.h>
#include <string.h>

int ft_strcmp(char *s1, char *s2, unsigned int n)
{
    int cmp;
    int aux_s1;
    int aux_s2;

    cmp = 0;
    aux_s1 = 0;
    aux_s2 = 0;
    while ((*s1 || *s2) && cmp != -1)
    {
        if (*s1 != *s2)
            cmp = -1;
        if (*s1 != '\0')
        {
            aux_s1 ++;
            s1 ++;
        }
        if (*s2 != '\0')
        {
            aux_s2 ++;
            s2 ++;
        }
    }
    if (aux_s1 > aux_s2)
        cmp = 1;
    else if (aux_s2 > aux_s1)
        cmp = -1;
    return (cmp);
}

int main(void)
{
    printf("%i", ft_strcmp("holaa", "holaa"));
    return (0);
}