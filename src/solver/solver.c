/*
** EPITECH PROJECT, 2021
** ex5
** File description:
** solver.c
*/

#include "../include/open_file.h"
#include "../include/matrix.h"
#include "../include/utils.h"
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
    if (y != 0) {
        if (recursive_solve(x, y - 1, endX, endY, maze, correctPath, wasHere, 0)) {
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

void real_path(matrix_t *solvedMaze, int x, int y)
{
    int x2 = 0;
    int y2 = 0;
    int i = 0;

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
            solvedMaze->matrix[i][j] = solvedMaze->matrix[i][j] >= 0 ? solvedMaze->matrix[i][j] = 0 : 1;
        }
    }
}

void solve_maze(matrix_t *maze, vector_t start, vector_t end)
{
    matrix_t *wasHere = create_matrix(maze->xMax, maze->yMax);
    matrix_t *correctPath = create_matrix(maze->xMax, maze->yMax);

    int b = recursive_solve(start.x, start.y, end.x, end.y, maze, correctPath, wasHere, 1);
    if (b) {
        real_path(correctPath, start.x, start.y);
        print_matrix(correctPath);
    }
    else
        printf("fail\n");
}

void solver(char **av)
{
    char *map = open_file(av);
    int nbExit = count_char(map, 'E');
    matrix_t *matrix = create_matrix(find_length(map), count_char(map, '\n'));

    // print_matrix(matrix);
    fill_matrix(matrix->matrix, map);
    for (int i = 0; i < nbExit; i++) {
        solve_maze(matrix, find_coord(map, 0, 'S'), find_coord(map, i, 'E'));
        printf("\n");
    }
}