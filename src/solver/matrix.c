/*
** SYSNAV PROJECT, 2021
** sysnavTask05
** File description:
** matrix.c
*/

#include "matrix.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

matrix_t *create_matrix(int size_x, int size_y)
{
    // create a matrix of size x * y
    int **matrix = malloc(sizeof(int *) * size_y);
    matrix_t *res = malloc(sizeof(matrix_t));

    (matrix == NULL || res == NULL) ? exit(1) : 0;
    for (int i = 0; i < size_y; i++) {
        matrix[i] = malloc(sizeof(int) * (size_x + 1));
        matrix[i] == NULL ? exit(1) : 0;
        for (int j = 0; j < size_x; j++)
            matrix[i][j] = 0;
    }
    res->matrix = matrix;
    res->xMax = size_x;
    res->yMax = size_y;
    return (res);
}

void fill_matrix(int **matrix, char *map)
{
    // fill the matrix with the map
    int i = 0;
    int j = 0;

    for (int x = 0; map[x] != '\0'; x++) {
        while (map[x] == '\n')
            i++, j = 0, x++;
        if (map[x] == '\0')
            break;
        matrix[i][j] = (map[x] == '.' ? 0
        : map[x] == '#' ? 1
        : map[x] == 'E' ? 0
        : map[x] == 'S' ? 0
        : map[x] == 'F' ? 2
        : matrix[i][j]);
        j++;
    }
}

matrix_t *copy_matrix(matrix_t *matrix)
{
    // copy an existing matrix
    matrix_t *copy = create_matrix(matrix->xMax, matrix->yMax);

    for (int i = 0; i < matrix->yMax; i++) {
        for (int j = 0; j < matrix->xMax; j++)
            copy->matrix[i][j] = matrix->matrix[i][j];
    }
    return (copy);
}

void print_matrix(matrix_t *matrix)
{
    // print matrix
    for (int i = 0; i < matrix->yMax; i++) {
        for (int j = 0; j < matrix->xMax; j++)
            printf("%2d ", matrix->matrix[i][j]);
        printf("\n");
    }
}

void free_matrix(matrix_t *matrix)
{
    for (int i = 0; i < matrix->yMax; i++)
        free(matrix->matrix[i]);
    free(matrix->matrix);
    free(matrix);
}
