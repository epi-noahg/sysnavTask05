/*
** SYSNAV PROJECT, 2021
** sysnavTask05
** File description:
** solver_utils.c
*/

#include "fire.h"
#include "matrix.h"
#include "utils.h"
#include <stdio.h>

int small_neighbour(matrix_t *matrix, int x, int y, int a)
{
    // find the smallest neighbour of a cell
    int value;
    // check if the cell is inside the matrix if not, the value of the cell becomes infinity
    int up = x - 1 < 0 ? INF : matrix->matrix[x - 1][y] <= 0 ? INF : matrix->matrix[x - 1][y];
    int down = x + 1 >= matrix->xMax ? INF : matrix->matrix[x + 1][y] <= 0 ? INF : matrix->matrix[x + 1][y];
    int left = y - 1 < 0 ? INF : matrix->matrix[x][y - 1] <= 0 ? INF : matrix->matrix[x][y - 1] <= 0 ? INF : matrix->matrix[x][y - 1];
    int right = y + 1 >= matrix->yMax ? INF : matrix->matrix[x][y + 1] <= 0 ? INF : matrix->matrix[x][y + 1] <= 0 ? INF : matrix->matrix[x][y + 1];

    value = MIN(up, down);
    value = MIN(value, left);
    value = MIN(value, right);
    // return the coordinates of the smallest neighbour
    if (value == up)
        return (a == 0 ? x - 1 : y);
    if (value == down)
        return (a == 0 ? x + 1 : y);
    if (value == left)
        return (a == 0 ? x : y - 1);
    if (value == right)
        return (a == 0 ? x : y + 1);
}

int neighbour_path(matrix_t *matrix, int i, int j)
{
    // return the correct cell for the function check result
    if (i + 1 < matrix->xMax && matrix->matrix[i + 1][j] == 1)
        return (1);
    if (i - 1 >= 0 && matrix->matrix[i - 1][j] == 1)
        return (2);
    if (j + 1 < matrix->yMax && matrix->matrix[i][j + 1] == 1)
        return (3);
    if (j - 1 >= 0 && matrix->matrix[i][j - 1] == 1)
        return (4);
    return (0);
}

void print_trajectory(matrix_t *matrix, vector_t start, vector_t end)
{
    int i = start.x;
    int j = start.y;
    int np;

    // print the trajectory if the result is correct
    while ((np = neighbour_path(matrix, i, j)) != 0) {
        matrix->matrix[i][j] *= -1;
        np == 1 ? i++, printf("D") : 0;
        np == 2 ? i--, printf("U") : 0;
        np == 3 ? j++, printf("R") : 0;
        np == 4 ? j--, printf("L") : 0;
    }
    printf("\n");
}

int check_results(matrix_t *matrix, vector_t start, vector_t end)
{
    // check the path with the propagation of the fire
    int i = start.x;
    int j = start.y;
    int np;

    propagation(matrix);
    while ((np = neighbour_path(matrix, i, j)) != 0) {
        matrix->matrix[i][j] *= -1;
        np == 1 ? i++ : 0;
        np == 2 ? i-- : 0;
        np == 3 ? j++ : 0;
        np == 4 ? j-- : 0;
        propagation(matrix);
    }
    free_matrix(matrix);
    if (end.x == i && end.y == j)
        return (1);
    return (0);
}
