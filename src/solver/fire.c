/*
** SYSNAV PROJECT, 2021
** sysnavTask05
** File description:
** fire.c
*/

#include "matrix.h"

void add_fire(int **matrix, char *map)
{
    int i = 0;
    int j = 0;

    // add start fire to the matrix (2)
    for (int x = 0; map[x] != '\0'; x++) {
        while (map[x] == '\n')
            i++, j = 0, x++;
        if (map[x] == '\0')
            break;
        matrix[i][j] = (map[x] == 'F' ? 2 : matrix[i][j]);
        j++;
    }
}

void propagation(matrix_t *matrix)
{
    // propagation of the fire inside the matrix
    for (int i = 0; i < matrix->yMax; i++) {
        for (int j = 0; j < matrix->xMax; j++) {
            if (matrix->matrix[i][j] == 2) { // -2 is used to prevent conflict between old and new fire
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
