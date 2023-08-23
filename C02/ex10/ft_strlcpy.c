//
// Created by bryan on 22/08/2023.
//

#include <stdio.h>

unsigned int ft_strlcpy(char *dest, char *src, unsigned int size)
{
    unsigned int src_lenght;

}

int main(void)
{
    char *str;
    char dest[100];

    str = "hola";
    printf("%i", ft_strlcpy(dest, str, 3));
    printf("%s", dest);
    return (0);
}