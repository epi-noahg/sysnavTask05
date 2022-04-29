/*
** EPITECH PROJECT, 2021
** ex5
** File description:
** matrix.c
*/

#include "../include/matrix.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

matrix_t *create_matrix(int size_x, int size_y)
{
    int **matrix = malloc(sizeof(int *) * size_y);
    matrix_t *res = malloc(sizeof(matrix_t));;

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

void propagation(matrix_t *matrix)
{
    for (int i = 0; i < matrix->yMax; i++) {
        for (int j = 0; j < matrix->xMax; j++) {
            if (matrix->matrix[i][j] == 2) {
                i - 1 >= 0 ? matrix->matrix[i - 1][j] = -2 : 0;
                i + 1 < matrix->yMax - 1 ? matrix->matrix[i + 1][j] = -2 : 0;
                j - 1 >= 0 ? matrix->matrix[i][j - 1] = -2 : 0;
                j + 1 < matrix->xMax - 1 ? matrix->matrix[i][j + 1] = -2 : 0;
            }
        }
    }
    for (int i = 0; i < matrix->yMax; i++) {
        for (int j = 0; j < matrix->xMax; j++) {
            if (matrix->matrix[i][j] == -2)
                matrix->matrix[i][j] = 2;
        }
    }

}

void print_matrix(matrix_t *matrix)
{
    for (int i = 0; i < matrix->yMax; i++) {
        for (int j = 0; j < matrix->xMax; j++) {
            printf("%2d ", matrix->matrix[i][j]);
        }
        printf("\n");
    }
}