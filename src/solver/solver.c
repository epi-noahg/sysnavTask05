/*
** EPITECH PROJECT, 2021
** ex5
** File description:
** solver.c
*/

#include "../include/open_file.h"
#include "../include/matrix.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <stdio.h>

int recursive_solve(int x, int y, int endX, int endY, matrix_t *maze, matrix_t *correctPath, matrix_t *wasHere, int reset) {
    static int value = 1;
    if (reset)
        value = 1;

    if (x == endX && y == endY) {
        correctPath->matrix[x][y] = value++;
        return value;
    }
    if (maze->matrix[x][y] || wasHere->matrix[x][y])
        return 0;
    wasHere->matrix[x][y] = 1;
    if (x != 0) {
        if (recursive_solve(x - 1, y, endX, endY, maze, correctPath, wasHere, 0)) {
            correctPath->matrix[x][y] = value++;
            return value;
        }
    }
    if (x != maze->xMax - 1) {
        if (recursive_solve(x + 1, y, endX, endY, maze, correctPath, wasHere, 0)) {
            correctPath->matrix[x][y] = value++;
            return value;
        }
    }
    if (y != 0) {
        if (recursive_solve(x, y - 1, endX, endY, maze, correctPath, wasHere, 0)) {
            correctPath->matrix[x][y] = value++;
            return value;
        }
    }
    if (y != maze->yMax - 1) {
        if (recursive_solve(x, y + 1, endX, endY, maze, correctPath, wasHere, 0)) {
            correctPath->matrix[x][y] = value++;
            return value;
        }
    }
    return 0;
}

int smallneighbour(matrix_t *matrix, int x, int y, int a)
{
    int value;
    int up = x - 1 < 0 ? 999999 : matrix->matrix[x - 1][y] <= 0 ? 999999 : matrix->matrix[x - 1][y];
    int down = x + 1 >= matrix->xMax ? 999999 : matrix->matrix[x + 1][y] <= 0 ? 999999 : matrix->matrix[x + 1][y];
    int left = y - 1 < 0 ? 999999 : matrix->matrix[x][y - 1] <= 0 ? 999999 : matrix->matrix[x][y - 1] <= 0 ? 999999 : matrix->matrix[x][y - 1];
    int right = y + 1 >= matrix->yMax ? 999999 : matrix->matrix[x][y + 1] <= 0 ? 999999 : matrix->matrix[x][y + 1] <= 0 ? 999999 : matrix->matrix[x][y + 1];

    value = MIN(up, down);
    value = MIN(value, left);
    value = MIN(value, right);
    if (value == up)
        return (a == 0 ? x - 1 : y);
    if (value == down)
        return (a == 0 ? x + 1 : y);
    if (value == left)
        return (a == 0 ? x : y - 1);
    if (value == right)
        return (a == 0 ? x : y + 1);
}

int real_path(matrix_t *solvedMaze, int x, int y)
{
    int x2 = 0;
    int y2 = 0;
    int count = 0;

    while (solvedMaze->matrix[x][y] != 1) {
        solvedMaze->matrix[x][y] *= -1;
        x2 = smallneighbour(solvedMaze, x, y, 0);
        y2 = smallneighbour(solvedMaze, x, y, 1);
        x = x2;
        y = y2;
    }
    solvedMaze->matrix[x][y] *= -1;
    for (int i = 0; i < solvedMaze->yMax; i++) {
        for (int j = 0; j < solvedMaze->xMax; j++) {
            solvedMaze->matrix[i][j] = solvedMaze->matrix[i][j] >= 0 ?
            0 : 1;
            count += solvedMaze->matrix[i][j] == 1 ? 1 : 0;
        }
    }
    return (count);
}

int neighbour_path(matrix_t *matrix, int i, int j)
{
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

int check_results(matrix_t *matrix, vector_t start, vector_t end)
{
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
    if (end.x == i && end.y == j)
        return (1);
    return (0);
}

void print_trajectory(matrix_t *matrix, vector_t start, vector_t end)
{
    int i = start.x;
    int j = start.y;
    int np;

    while ((np = neighbour_path(matrix, i, j)) != 0) {
        matrix->matrix[i][j] *= -1;
        np == 1 ? i++, printf("D") : 0;
        np == 2 ? i--, printf("U") : 0;
        np == 3 ? j++, printf("R") : 0;
        np == 4 ? j--, printf("L") : 0;
    }
    printf("\n");
}

void solve_maze(char *map, matrix_t *maze, vector_t start, vector_t end)
{
    matrix_t *wasHere = create_matrix(maze->xMax, maze->yMax);
    matrix_t *correctPath = create_matrix(maze->xMax, maze->yMax);

    recursive_solve(start.x, start.y, end.x, end.y, maze, correctPath, wasHere, 1);
    real_path(correctPath, start.x, start.y);
    add_fire(correctPath->matrix, map);
    if (check_results(copy_matrix(correctPath), start, end)) {
        print_trajectory(correctPath, start, end);
        exit(0);
    }
}

void solver(char **av)
{
    char *map = open_file(av);
    int nbExit = count_char(map, 'E');
    matrix_t *matrix = create_matrix(find_length(map), count_char(map, '\n'));

    fill_matrix(matrix->matrix, map);
    for (int i = 0; i < nbExit; i++)
        solve_maze(map, matrix, find_coord(map, 0, 'S'), find_coord(map, i, 'E'));
    printf("Nothing found!\n");
    exit(0);
}