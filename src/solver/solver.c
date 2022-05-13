/*
** SYSNAV PROJECT, 2021
** sysnavTask05
** File description:
** solver.c
*/

#include "open_file.h"
#include "matrix.h"
#include "utils.h"
#include "fire.h"
#include "solver_utils.h"
#include <stdlib.h>
#include <stdio.h>

int recursive_solver(int x, int y, int endX, int endY, matrix_t *maze, matrix_t *correctPath, matrix_t *wasHere, int reset) {
    // simple path finding algorithm that finds a path, but it is not the shortest
    static int value = 1; // an integer that is used to number each cell in the path

    if (reset) // reset the value
        value = 1;
    if (x == endX && y == endY) { // when the path is found
        correctPath->matrix[x][y] = value++;
        return value;
    }
    if (maze->matrix[x][y] || wasHere->matrix[x][y])
        return 0;
    wasHere->matrix[x][y] = 1;
    // recursivly finding a path
    if (x != 0) {
        if (recursive_solver(x - 1, y, endX, endY, maze, correctPath, wasHere, 0)) {
            correctPath->matrix[x][y] = value++;
            return value;
        }
    }
    if (x != maze->xMax - 1) {
        if (recursive_solver(x + 1, y, endX, endY, maze, correctPath, wasHere, 0)) {
            correctPath->matrix[x][y] = value++;
            return value;
        }
    }
    if (y != 0) {
        if (recursive_solver(x, y - 1, endX, endY, maze, correctPath, wasHere, 0)) {
            correctPath->matrix[x][y] = value++;
            return value;
        }
    }
    if (y != maze->yMax - 1) {
        if (recursive_solver(x, y + 1, endX, endY, maze, correctPath, wasHere, 0)) {
            correctPath->matrix[x][y] = value++;
            return value;
        }
    }
    return 0;
}

int real_path(matrix_t *solvedMaze, vector_t start)
{
    // find the smallest path by using the recursive solver
    int x2 = 0;
    int y2 = 0;
    int count = 0;

    while (solvedMaze->matrix[start.x][start.y] != 1) {
        solvedMaze->matrix[start.x][start.y] *= -1;
        x2 = small_neighbour(solvedMaze, start.x, start.y, 0);
        y2 = small_neighbour(solvedMaze, start.x, start.y, 1);
        start.x = x2;
        start.y = y2;
    }
    solvedMaze->matrix[start.x][start.y] *= -1;
    for (int i = 0; i < solvedMaze->yMax; i++) {
        for (int j = 0; j < solvedMaze->xMax; j++) {
            solvedMaze->matrix[i][j] = solvedMaze->matrix[i][j] >= 0 ?
            0 : 1;
            count += solvedMaze->matrix[i][j] == 1 ? 1 : 0;
        }
    }
    return (count);
}

void solve_maze(char *map, matrix_t *maze, vector_t start, vector_t end)
{
    // solve the "maze"
    matrix_t *wasHere = create_matrix(maze->xMax, maze->yMax);
    matrix_t *correctPath = create_matrix(maze->xMax, maze->yMax);

    recursive_solver(start.x, start.y, end.x, end.y, maze, correctPath, wasHere, 1);
    real_path(correctPath, start);
    add_fire(correctPath->matrix, map);
    if (check_results(copy_matrix(correctPath), start, end)) {
        print_trajectory(correctPath, start, end);
        free_matrix(maze);
        free_matrix(wasHere);
        free_matrix(correctPath);
        free(map);
        exit(0);
    }
    free_matrix(wasHere);
    free_matrix(correctPath);
}

void solver(char **av)
{
    char *map = open_file(av);
    int nbExit = count_char(map, 'E');
    matrix_t *matrix = create_matrix(find_length(map), count_char(map, '\n'));

    fill_matrix(matrix->matrix, map);
    for (int i = 0; i < nbExit; i++)
        solve_maze(map, matrix, find_coord(map, 0, 'S'), find_coord(map, i, 'E'));
    free_matrix(matrix);
    free(map);
    exit(1);
}
