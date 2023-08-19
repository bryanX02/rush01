//
// Created by Bryan Xavier on 8/19/23.
//
#include <unistd.h>
#include <stdlib.h>

void            load_matrix(int **matrix, char *args, int size);
void            print_matrix(int **matrix, int size);
unsigned int    stn(char *str);

int main(int arg, char **args)
{
    int    **matrix;
    int     size;

    size = 4;
    matrix = (int**) malloc(size * sizeof(int*));
    load_matrix(matrix, args[1], size);
    print_matrix(matrix, size);
    free(matrix);
    return (arg);
}

void load_matrix(int **matrix, char *args, int size)
{
    int i;
    int j;

    i = 0;
    j = 0;

    while (i < size)
    {
        matrix[i] = (int*) malloc(size * sizeof(int));
        i ++;
    }
    i = 0;
    while (i < size) {
        while (j < size) {
            matrix[i][j] = 0;
            j++;
            args ++;
        }
        j = 0;
        i++;
    }
}

void print_matrix(int **matrix, int size)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < size) {
        while (j < size) {
            write(1, &(char){'0' + matrix[i][j]}, 1);
            j ++;
        }
        j = 0;
        i++;
    }
}

unsigned int stn(char *str)
{
    return ((int){*str - '0'});
}